/* gtkmm example Copyright (C) 2002 gtkmm development team
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

#include <giomm.h>
#include <iostream>


int main(int /* argc */, char** /* argv */)
{
  Gio::init();

  try
  {
    auto directory = Gio::File::create_for_path("/etc");
    if(!directory)
      std::cerr << "Gio::File::create_for_path() returned an empty RefPtr." << std::endl;

    auto enumerator = directory->enumerate_children();
    if(!enumerator)
      std::cerr << "Gio::File::enumerate_children() returned an empty RefPtr." << std::endl;

    auto file_info = enumerator->next_file();
    while(file_info)
    {
      std::cout << "file: " << file_info->get_name() << std::endl;
      file_info = enumerator->next_file();
    }

  }
  catch(const Glib::Error& ex)
  {
    std::cerr << "Exception caught: " << ex.what() << std::endl;
  }


  return 0;
}

