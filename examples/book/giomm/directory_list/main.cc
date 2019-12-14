//$Id: main.cc 836 2007-05-09 03:02:38Z jjongsma $ -*- c++ -*-

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

