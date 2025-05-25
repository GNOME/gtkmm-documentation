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
    auto file = Gio::File::create_for_path("test_output.txt");
    if(!file)
      std::cerr << "Gio::File::create_for_path() returned an empty RefPtr." << std::endl;

    Glib::RefPtr<Gio::FileOutputStream> stream;

    //If the file exists already then replace it.
    //Otherwise, create it:
    if(file->query_exists())
      stream = file->replace();
    else
      stream = file->create_file();

    if(!stream)
      std::cerr << "Gio::File::create_file() returned an empty RefPtr." << std::endl;

    Glib::ustring contents = "This is some test output";
    const gsize bytes_read = stream->write(contents.raw());

    if(bytes_read)
      std::cout << "File contents written: " << contents << std::endl;
    else
      std::cerr << "Gio::InputStream::write() wrote 0 bytes." << std::endl;

    //Close the stream to make sure that changes are written now,
    //instead of just when the stream goes out of scope,
    //though that's the same time in this simple example.
    //For instance, when using Gio::File::replace(), the file is only
    //actually replaced during close() or when the stream is destroyed.
    stream->close();
    stream.reset(); //Stream can't be used after we have closed it.
  }
  catch(const Glib::Error& ex)
  {
    std::cerr << "Exception caught: " << ex.what() << std::endl;
  }

  return 0;
}

