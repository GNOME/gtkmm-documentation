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

/** A simplistic implementation of a function similar to std::istream::getline()
 * which reads a 'line' of data from a file.  A line is defined as text
 * separated by the given delimiter character, which defaults to the newline
 * character.  If no delimiter is found before we read size-1 characters, just
 * return the data read so far, even though it's not a full line.
 * This function always appends a NULL character to the end of the string
 *
 * returns true if any data was read, false if no data was read (e.g. the end of
 * the stream was reached)
 */
bool getline (const Glib::RefPtr<Gio::InputStream>& stream,
              char* buf,
              size_t size, char delim = '\n')
{
    g_return_val_if_fail (stream, false);
    char* cur = buf;
    // read a single character at a time until we read the delimiter
    while (stream->read (cur, 1) && (cur < (buf + size - 1))) {
        if (*cur == delim) {
            *cur++ = 0;  // discard the delimiter, add a NULL char
            break;
        }
        ++cur;  // advance to next character
    }
    *cur = 0;    // append a NULL
    return (cur > buf); // if any data was read, cur will be > buf
}

int main(int argc, char** argv)
{
    Gio::init();
    Glib::RefPtr<Gio::File> f = Gio::File::create_for_path ("/etc/profile");
    Glib::RefPtr<Gio::Cancellable> cancellable = Gio::Cancellable::create ();
    Glib::RefPtr<Gio::FileInputStream> stream = f->read (cancellable);
    char buf[100];
    int line_num = 1;
    while (getline (stream, buf, 100)) {
        std::cout << std::setw (5) << line_num++ << ": >" << buf << std::endl;
    }
    return 0;
}
