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
#include <fstream>
#include <iostream>
#include <string>
#include <locale>
#include <clocale>
#include <glibmm/i18n.h>

const char* GETTEXT_PACKAGE = "myapp";
const char* PROGRAMNAME_LOCALEDIR = "locale";

int main(int argc, char* argv[])
{
  std::ifstream myfile(ExampleWindow::config_file_name);
  if (myfile.is_open())
  {
    // Set the configured locale.
    std::string line;
    std::getline(myfile, line);
    std::cout <<"Preference settings: "<< line << std::endl;
    // Don't use the user's preferred locale.
    Glib::set_init_to_users_preferred_locale(false);
    Glib::setenv("LANG", line, true);
    std::cout << "getenv(LANG)= " << Glib::getenv("LANG") << '\n';
    std::setlocale(LC_ALL, line.c_str());
    myfile.close();
  }
  // If the configuration file does not exist, the user's preferred locale is used.

  bindtextdomain(GETTEXT_PACKAGE, PROGRAMNAME_LOCALEDIR);
  bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
  textdomain(GETTEXT_PACKAGE);

  // Gtk::Application::create() calls Glib::init(), which sets the C++ global locale.
  auto app = Gtk::Application::create("org.gtkmm.example");

  // On startup, when std::cout is created, the global locale is the "C" locale,
  // AKA the classic locale.
  std::cout << _("English App is Running") << ", "
    << std::cout.getloc().name() << " locale: " << 1234.56 << '\n';

  // Use the new global locale for future output to std::cout.
  std::cout.imbue(std::locale());

  std::cout << _("English App is Running") << ", "
    << std::cout.getloc().name() << " locale: " << 1234.56 << '\n';
  std::cout << "Force unicode German text: Gr\xC3\xBC\xC3\x9F Gott\n";

  // Shows the window and returns when it is closed.
  return app->make_window_and_run<ExampleWindow>(argc, argv);
}
