/* gtkmm example Copyright (C) 2003 gtkmm development team
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

#ifndef GTKMM_EXAMPLE_IDLEEXAMPLE_H
#define GTKMM_EXAMPLE_IDLEEXAMPLE_H

#include <gtkmm.h>
#include <iostream>

class IdleExample : public Gtk::Window
{
public:
  IdleExample();

protected:
  // Signal Handlers:
  bool on_timer();
  bool on_idle();
  void on_button_clicked();

  // Member data:
  Gtk::Box m_Box;
  Gtk::Button m_ButtonQuit;
  Gtk::ProgressBar m_ProgressBar_c;
  Gtk::ProgressBar m_ProgressBar_d;
};

#endif // GTKMM_EXAMPLE_IDLEEXAMPLE_H
