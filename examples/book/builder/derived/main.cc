/* libglademm example Copyright (C) 2003 libglademm development team
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

#include "deriveddialog.h"
#include <iostream>
#include <cstring>

// Not really used anywhere, but force an instance to be created.
DerivedButton* my_globally_accessible_button = nullptr;

int main(int argc, char** argv)
{
  bool show_icon = false;
  bool is_glad = true;
  int argc1 = argc;
  if (argc > 1)
  {
    if (std::strcmp(argv[1], "--glad") == 0)
    {
      show_icon = true;
      is_glad = true;
      argc1 = 1; // Don't give the command line arguments to Gtk::Application.
    }
    else if (std::strcmp(argv[1], "--sad") == 0)
    {
      show_icon = true;
      is_glad = false;
      argc1 = 1; // Don't give the command line arguments to Gtk::Application.
    }
  }

  auto app = Gtk::Application::create("org.gtkmm.example");

  // The application must be registered when the builder adds widgets from
  // the derived.glade file.
  // Calling Gio::Application::register_application() explicitly is necessary
  // in this example because the .glade file is loaded in the main() function.
  // There are better ways. See other examples, such as examples/book/buildapp/,
  // and examples/book/menus/ and examples/book/menus_and_toolbars/.
  app->register_application();

  // Create a dummy instance before the call to refBuilder->add_from_file().
  // This creation registers DerivedButton's class in the GType system.
  my_globally_accessible_button = new DerivedButton();

  //Load the Glade file and instantiate its widgets:
  auto refBuilder = Gtk::Builder::create();
  try
  {
    refBuilder->add_from_file("derived.glade");
  }
  catch(const Glib::FileError& ex)
  {
    std::cerr << "FileError: " << ex.what() << std::endl;
    return 1;
  }
  catch(const Glib::MarkupError& ex)
  {
    std::cerr << "MarkupError: " << ex.what() << std::endl;
    return 1;
  }
  catch(const Gtk::BuilderError& ex)
  {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
    return 1;
  }

  //Get the GtkBuilder-instantiated dialog:
  DerivedDialog* pDialog = nullptr;
  if (show_icon)
    pDialog = Gtk::Builder::get_widget_derived<DerivedDialog>(refBuilder, "DialogDerived", is_glad);
  else
    pDialog = Gtk::Builder::get_widget_derived<DerivedDialog>(refBuilder, "DialogDerived");

  int status = 1;
  if (pDialog)
  {
    // All widgets must be deleted before app->run() returns.
    // This is yet another reason why you should usually not use the builder
    // in the main() function.
    pDialog->signal_hide().connect([pDialog, &refBuilder] ()
    {
      delete pDialog;
      refBuilder.reset();
    });

    // We can call add_window() before run() because we have registered the
    // application. (run() registers the application, if it has not been done.)
    app->add_window(*pDialog);
    pDialog->show();
    status = app->run(argc1, argv);
  }

  return status;
}
