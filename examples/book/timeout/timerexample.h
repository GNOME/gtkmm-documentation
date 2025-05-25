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

#ifndef GTKMM_EXAMPLE_TIMEREXAMPLE_H
#define GTKMM_EXAMPLE_TIMEREXAMPLE_H

#include <gtkmm.h>
#include <iostream>
#include <map>

class TimerExample : public Gtk::Window
{
public:
  TimerExample();

protected:
  // signal handlers
  void on_button_add_timer();
  void on_button_delete_timer();
  void on_button_quit();

  // This is the callback function the timeout will call
  bool on_timeout(int timer_number);

  // Member data:

  Gtk::Box m_Box;
  Gtk::Button m_ButtonAddTimer, m_ButtonDeleteTimer, m_ButtonQuit;

  // Keep track of the timers being added:
  int m_timer_number;

  // These two constants are initialized in the constructor's member initializer:
  const int count_value;
  const int timeout_value;

  // STL map for storing our connections
  std::map<int, sigc::connection> m_timers;

  // STL map for storing our timer values.
  // Each timer counts back from COUNT_VALUE to 0 and is removed when it reaches 0
  std::map<int, int> m_counters;
};

#endif // GTKMM_EXAMPLE_TIMEREXAMPLE_H
