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

int main (int argc, char **argv)
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

  auto app = Gtk::Application::create(argc1, argv, "org.gtkmm.example");

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
    // This call to get_widget_derived() requires gtkmm 3.19.7 or higher.
    refBuilder->get_widget_derived("DialogDerived", pDialog, is_glad);
  else
    refBuilder->get_widget_derived("DialogDerived", pDialog);
  if(pDialog)
  {
    //Start:
    app->run(*pDialog);
  }

  delete pDialog;

  return 0;
}
