/*******************************************************************************
 *  Copyright (c) 2007 Jonathon Jongsma
 *
 *  This file is part of gtkmm
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>
 *
 *******************************************************************************/
#include <giomm.h>
#include <iostream>
#include <iomanip>
#include <string>

/* This is just a simple example to show you how to read a line of text at a
 * time, similar to using std::istream::getline()
 */
int main(int /* argc */, char** /* argv */)
{
  Gio::init();
  auto f = Gio::File::create_for_path("/etc/profile");
  auto file_stream = f->read();
  auto data_stream = Gio::DataInputStream::create(file_stream);

  std::string line;
  int line_num = 1;
  while (data_stream->read_line(line))
  {
    // print each line out prefixed with the line number
    std::cout << std::setw (5) << line_num++ << ": >" << line << std::endl;
  }
  return 0;
}
