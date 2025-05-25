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

#ifndef GTKMM_EXAMPLE_SERVER_H
#define GTKMM_EXAMPLE_SERVER_H

#include <sigc++/sigc++.h>

class Server
{
public:
  Server();
  virtual ~Server();

  void do_something();

  //signal accessor:
  using type_signal_something = sigc::signal<void(bool, int)>;
  type_signal_something signal_something();

protected:
  type_signal_something m_signal_something;
};

#endif //GTKMM_EXAMPLE_SERVER_H
