/* gtkmm example Copyright (C) 2024 gtkmm development team
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

#include "examplewindow.h"
#include <iostream>
#include <glibmm/i18n.h>

const char* GETTEXT_PACKAGE = "myapp";
const char* PROGRAMNAME_LOCALEDIR = "locale";

int main(int argc, char* argv[])
{
  bindtextdomain(GETTEXT_PACKAGE, PROGRAMNAME_LOCALEDIR);
  bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
  textdomain(GETTEXT_PACKAGE);

  // Gtk::Application::create() sets the locale of C and C++ code
  // to the user's locale. If the user's locale supports UTF-8,
  // the following German text can then be printed.
  auto app = Gtk::Application::create("org.gtkmm.example");

  std::cout << Glib::ustring(_("English App is Running\n"));
  std::cout << Glib::ustring("Force unicode German text: Gr\xC3\xBC\xC3\x9F Gott\n");

  // Shows the window and returns when it is closed.
  return app->make_window_and_run<ExampleWindow>(argc, argv);
}
