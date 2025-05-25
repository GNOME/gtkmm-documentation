/* gtkmm example Copyright (C) 2003 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <https://www.gnu.org/licenses/>.
 */

#include "deriveddialog.h"
#include <iostream>
#include <cstring>

namespace
{
bool show_icon = false;
bool is_glad = true;

DerivedDialog* pDialog = nullptr;
Glib::RefPtr<Gtk::Application> app;

void on_app_activate()
{
  // Create a dummy instance before the call to refBuilder->add_from_file().
  // This creation registers DerivedButton's class in the GType system.
  // This is necessary because DerivedButton contains user-defined properties
  // (Glib::Property) and is created by Gtk::Builder.
  static_cast<void>(DerivedButton());

  // Load the GtkBuilder file and instantiate its widgets:
  auto refBuilder = Gtk::Builder::create();
  try
  {
    refBuilder->add_from_file("derived.ui");
  }
  catch(const Glib::FileError& ex)
  {
    std::cerr << "FileError: " << ex.what() << std::endl;
    return;
  }
  catch(const Glib::MarkupError& ex)
  {
    std::cerr << "MarkupError: " << ex.what() << std::endl;
    return;
  }
  catch(const Gtk::BuilderError& ex)
  {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
    return;
  }

  // Get the GtkBuilder-instantiated dialog:
  if (show_icon)
    pDialog = Gtk::Builder::get_widget_derived<DerivedDialog>(refBuilder, "DialogDerived", is_glad);
  else
    pDialog = Gtk::Builder::get_widget_derived<DerivedDialog>(refBuilder, "DialogDerived");

  if (!pDialog)
  {
    std::cerr << "Could not get the dialog" << std::endl;
    return;
  }

  // It's not possible to delete widgets after app->run() has returned.
  // Delete the dialog with its child widgets before app->run() returns.
  pDialog->signal_hide().connect([] () { delete pDialog; });

  app->add_window(*pDialog);
  pDialog->set_visible(true);
}
} // anonymous namespace

int main(int argc, char** argv)
{
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

  app = Gtk::Application::create("org.gtkmm.example");

  // Instantiate a dialog when the application has been activated.
  // This can only be done after the application has been registered.
  // It's possible to call app->register_application() explicitly, but
  // usually it's easier to let app->run() do it for you.
  app->signal_activate().connect([] () { on_app_activate(); });

  return app->run(argc1, argv);
}
