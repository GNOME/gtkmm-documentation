/* gtkmm example Copyright (C) 2002 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "exampleapplication.h"
#include "examplewindow.h"
#include <iostream>

ExampleApplication::ExampleApplication()
: Gtk::Application("org.gtkmm.examples.application",
    Gio::ApplicationFlags(Gio::APPLICATION_HANDLES_OPEN | Gio::APPLICATION_HANDLES_COMMAND_LINE))
{
  Glib::set_application_name("Gtk::Application Example");

  signal_handle_local_options().connect(
    sigc::mem_fun(*this, &ExampleApplication::on_handle_local_options), false);

  //These are just pointless command-line arguments to show the use of the API:

  //A bool.
  add_main_option_entry(Gio::Application::OPTION_TYPE_BOOL, "foo", 'f', "Enable foo.");

  //A std::string.
  add_main_option_entry(Gio::Application::OPTION_TYPE_FILENAME, "goo", 'g', "The file name of goo to use.", "file");

  //A Glib::ustring.
  add_main_option_entry(Gio::Application::OPTION_TYPE_STRING, "hoo", 'h', "The hoo to use.", "", Glib::OptionEntry::FLAG_HIDDEN);

  //An int.
  add_main_option_entry(Gio::Application::OPTION_TYPE_INT, "bar", 'b', "The bar to use.", "number");

  //A bool.
  add_main_option_entry(Gio::Application::OPTION_TYPE_BOOL, "version", 'v', "Show the application version.");


  //A std::vector<std::string>.
  add_main_option_entry(Gio::Application::OPTION_TYPE_FILENAME_VECTOR, G_OPTION_REMAINING);

  //Custom-decoded arguments
  add_main_option_entry(sigc::mem_fun(*this, &ExampleApplication::on_option_arg_string),
    "string", 's', "The string to use", "string", Glib::OptionEntry::FLAG_OPTIONAL_ARG);
  add_main_option_entry_filename(sigc::mem_fun(*this, &ExampleApplication::on_option_arg_filename),
    "name", 'n', "The filename to use", "file");
}

Glib::RefPtr<ExampleApplication> ExampleApplication::create()
{
  return Glib::RefPtr<ExampleApplication>( new ExampleApplication() );
}

void ExampleApplication::create_window(const Glib::RefPtr<Gio::File>& file)
{
  auto window = new ExampleWindow();

  //Make sure that the application runs for as long this window is still open:
  add_window(*window);

  //Delete the window when it is hidden.
  //That's enough for this simple example.
  window->signal_hide().connect(sigc::bind<Gtk::Window*>(sigc::mem_fun(*this,
    &ExampleApplication::on_window_hide), window));

  window->show();

  if(!file)
  {
    //This is probably an new empty file, as a result of an activation rather
    //than an open.
    return;
  }

  const bool loaded = window->load_file(file);
  if(!loaded)
    std::cerr << "This file could not be loaded: " << file->get_path() << std::endl;
}

void ExampleApplication::on_window_hide(Gtk::Window* window)
{
  delete window;
}

void ExampleApplication::on_activate()
{
  //std::cout << "debug1: " << G_STRFUNC << std::endl;
  // The application has been started, so let's show a window.
  // A real application might want to reuse this "empty" window in on_open(),
  // when asked to open a file, if no changes have been made yet.
  create_window();
}

void ExampleApplication::on_open(const Gio::Application::type_vec_files& files,
  const Glib::ustring& hint)
{
  // The application has been asked to open some files,
  // so let's open a new window for each one.
  //std::cout << "debug: files.size()=" << files.size() << std::endl;
  for(std::size_t i = 0; i < files.size(); i++)
  {
    auto file = files[i];
    if(!file)
    {
      std::cerr << G_STRFUNC << ": file is null." << std::endl;
    }
    else
      create_window(file);
  }

  //Call the base class's implementation:
  Gtk::Application::on_open(files, hint);
}

template <typename T_ArgType>
static bool get_arg_value(const Glib::RefPtr<Glib::VariantDict>& options, const Glib::ustring& arg_name, T_ArgType& arg_value)
{
  arg_value = T_ArgType();
  if(options->lookup_value(arg_name, arg_value))
  {
    //std::cout << "The \"" << arg_name << "\" value was in the options VariantDict." << std::endl;
    return true;
  }
  else
  {
    auto gvariant = g_variant_dict_lookup_value(options->gobj(), arg_name.c_str(), nullptr);
    if(!gvariant)
    {
      std::cerr << "The \"" << arg_name << "\" value was not in the options VariantDict." << std::endl;
    }
    else
    {
      std::cerr <<
        "The \"" << arg_name <<"\" value was of type " << g_variant_get_type_string(gvariant) <<
        " instead of " << Glib::Variant<T_ArgType>::variant_type().get_string() << std::endl;
    }
  }

  return false;
}

int ExampleApplication::on_command_line(const Glib::RefPtr<Gio::ApplicationCommandLine>& command_line)
{
  const auto options = command_line->get_options_dict();
  if(!options)
    std::cerr << G_STRFUNC << ": options is null." << std::endl;

  //Parse command-line arguments that were passed either to the primary (first) instance
  //or to subsequent instances.
  //Note that this parsing is happening in the primary (not local) instance.
  bool foo_value = false;
  get_arg_value(options, "foo", foo_value);
  std::string goo_value;
  get_arg_value(options, "goo", goo_value);
  Glib::ustring hoo_value;
  get_arg_value(options, "hoo", hoo_value);
  int bar_value = 0;
  get_arg_value(options, "bar", bar_value);
  bool version_value = false;
  get_arg_value(options, "version", version_value);

  //The remaining filenames:
  std::vector<std::string> vec_remaining;
  get_arg_value(options, G_OPTION_REMAINING, vec_remaining);

  //Note that "foo" and "goo" will not be false/empty here because we
  //handled them in on_handle_local_options() and therefore removed them from
  //the options VariantDict.
  std::cout << "on_command_line(), parsed values: " << std::endl <<
    "  foo = " << (foo_value ? "true" : "false") << std::endl <<
    "  goo = " << goo_value << std::endl <<
    "  hoo = " << hoo_value << std::endl <<
    "  bar = " << bar_value << std::endl <<
    "  version = " << (version_value ? "true" : "false") << std::endl <<
    "  remaining =";
  for (std::size_t i = 0; i < vec_remaining.size(); ++i)
    std::cout << ' ' << vec_remaining[i];
  std::cout << std::endl;


  if(vec_remaining.empty())
  {
    //Open a new "document" instead:
    activate();
    return EXIT_SUCCESS;
  }

  Gio::Application::type_vec_files vec_files;
  for (std::size_t i = 0; i < vec_remaining.size(); ++i)
    vec_files.push_back(Gio::File::create_for_path(vec_remaining[i]));
  open(vec_files);

  //The local instance will eventually exit with this status code:
  return EXIT_SUCCESS;
}

int ExampleApplication::on_handle_local_options(const Glib::RefPtr<Glib::VariantDict>& options)
{
  if(!options)
    std::cerr << G_STRFUNC << ": options is null." << std::endl;

  bool foo_value = false;
  get_arg_value(options, "foo", foo_value);
  std::string goo_value;
  get_arg_value(options, "goo", goo_value);
  Glib::ustring hoo_value;
  get_arg_value(options, "hoo", hoo_value);
  int bar_value = 0;
  get_arg_value(options, "bar", bar_value);
  bool version_value = false;
  get_arg_value(options, "version", version_value);

  std::cout << "on_handle_local_options(), parsed values: " << std::endl <<
    "  foo = " << (foo_value ? "true" : "false") << std::endl <<
    "  goo = " << goo_value << std::endl <<
    "  hoo = " << hoo_value << std::endl <<
    "  bar = " << bar_value << std::endl <<
    "  version = " << (version_value ? "true" : "false") << std::endl;

  //Remove some options to show that we have handled them in the local instance,
  //so they won't be passed to the primary (remote) instance:
  options->remove("foo");
  options->remove("goo");

  //If --version was requested,
  //just output the version number and exit with a success code:
  if(version_value)
  {
    std::cout << "Version: 1.2.3" << std::endl;

    //Any non-negative return value here means stop the program.
    //The local instance will eventually exit with this status code.
    return EXIT_SUCCESS;
  }

  //If the command line parameters were invalid,
  //complain and exist with a failure code:
  if(goo_value == "ungoo")
  {
     std::cerr << "goo cannot be ungoo." << std::endl;

     //Any non-negative return value here means stop the program.
     //The local instance will eventually exit with this status code.
     return EXIT_FAILURE;
  }

  return -1;
}

bool ExampleApplication::on_option_arg_string(const Glib::ustring& option_name,
  const Glib::ustring& value, bool has_value)
{
  std::cout << "on_option_arg_string(), parsed value: " << std::endl <<
    "  " << option_name << " = " << value << (has_value ? "" : "(no value)") << std::endl;
  return true;
}

bool ExampleApplication::on_option_arg_filename(const Glib::ustring& option_name,
  const std::string& value, bool has_value)
{
  std::cout << "on_option_arg_filename(), parsed value: " << std::endl <<
    "  " << option_name << " = " << value << (has_value ? "" : "(no value)") << std::endl;
  return true;
}
