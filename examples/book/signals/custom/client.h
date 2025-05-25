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

#ifndef GTKMM_EXAMPLE_CLIENT_H
#define GTKMM_EXAMPLE_CLIENT_H

#include <sigc++/sigc++.h>

//Client must inherit from sigc::trackable.
//because libsigc++ needs to keep track of the lifetime of signal handlers.
class Client : public sigc::trackable
{
public:
  Client();
  virtual ~Client();

  //Signal handler:
  void on_server_something(bool a, int b);
};

#endif //GTKMM_EXAMPLE_CLIENT_H
