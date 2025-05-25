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
#include <cstring>


int main(int /* argc */, char** /* argv */)
{
  Gio::init();

  try
  {
    auto file = Gio::File::create_for_path("/etc/fstab");
    if(!file)
      std::cerr << "Gio::File::create_for_path() returned an empty RefPtr." << std::endl;

    auto stream = file->read();
    if(!stream)
      std::cerr << "Gio::File::read() returned an empty RefPtr." << std::endl;

    gchar buffer[1000]; //TODO: This is unpleasant.
    memset(buffer, 0, 1000);
    const gsize bytes_read = stream->read(buffer, 1000);

    if(bytes_read)
      std::cout << "File contents read: " << buffer << std::endl;
    else
      std::cerr << "Gio::InputStream::read() read 0 bytes." << std::endl;

  }
  catch(const Glib::Error& ex)
  {
    std::cerr << "Exception caught: " << ex.what() << std::endl;
  }


  return 0;
}

