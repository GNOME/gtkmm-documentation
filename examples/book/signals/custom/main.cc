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

#include "server.h"
#include "client.h"
#include <iostream>

int main(int, char**)
{
  Server server;
  Client client;

  //Connect a Server signal to the signal handler in Client.
  server.signal_something().connect(sigc::mem_fun(client,
              &Client::on_server_something) );

  std::cout << "Before Server::do_something()" << std::endl;

  //Tell the server to do something that will eventually cause it to emit the
  //"something" signal.
  server.do_something();    // Client::on_server_something() will run before
                            // Server::do_something() has completed.

  std::cout << "After Server::do_something()" << std::endl;

  return 0;
}
