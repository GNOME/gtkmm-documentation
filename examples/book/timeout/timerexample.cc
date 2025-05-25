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

#include "timerexample.h"

TimerExample::TimerExample() :
  m_Box(Gtk::Orientation::HORIZONTAL, 10),
  m_ButtonAddTimer("_Add", true),
  m_ButtonDeleteTimer("_Remove", true),
  m_ButtonQuit("_Quit", true),
  m_timer_number(0), // start numbering the timers at 0
  count_value(5), // each timer will count down 5 times before disconnecting
  timeout_value(1500) // 1500 ms = 1.5 seconds
{
  m_Box.set_margin(10);
  set_child(m_Box);
  m_Box.append(m_ButtonAddTimer);
  m_Box.append(m_ButtonDeleteTimer);
  m_Box.append(m_ButtonQuit);
  m_ButtonAddTimer.set_expand();
  m_ButtonDeleteTimer.set_expand();
  m_ButtonQuit.set_expand();

  // Connect the three buttons:
  m_ButtonQuit.signal_clicked().connect(sigc::mem_fun(*this,
              &TimerExample::on_button_quit));
  m_ButtonAddTimer.signal_clicked().connect(sigc::mem_fun(*this,
              &TimerExample::on_button_add_timer));
  m_ButtonDeleteTimer.signal_clicked().connect(sigc::mem_fun(*this,
              &TimerExample::on_button_delete_timer));
}

void TimerExample::on_button_quit()
{
  set_visible(false);
}

void TimerExample::on_button_add_timer()
{
  // Creation of a new object prevents long lines and shows us a little
  // how slots work.  We have 0 parameters and bool as a return value
  // after calling sigc::bind.
  sigc::slot<bool()> my_slot = sigc::bind(sigc::mem_fun(*this,
              &TimerExample::on_timeout), m_timer_number);

  // This is where we connect the slot to the Glib::signal_timeout()
  auto conn = Glib::signal_timeout().connect(my_slot,
          timeout_value);

  // Remember the connection:
  m_timers[m_timer_number] = conn;

  // Initialize timer count:
  m_counters[m_timer_number] = count_value + 1;

  // Print some info to the console for the user:
  std::cout << "added timeout " << m_timer_number++ << std::endl;
}

void TimerExample::on_button_delete_timer()
{
  // any timers?
  if(m_timers.empty())
  {
    // no timers left
    std::cout << "Sorry, there are no timers left." << std::endl;
  }
  else
  {
    // get the number of the first timer
    int timer_number = m_timers.begin()->first;

    // Give some info to the user:
    std::cout << "manually disconnecting timer " << timer_number
        << std::endl;

    // Remove the entry in the counter values
    m_counters.erase(timer_number);

    // Diconnect the signal handler:
    m_timers[timer_number].disconnect();

    // Forget the connection:
    m_timers.erase(timer_number);
  }
}

bool TimerExample::on_timeout(int timer_number)
{
  // Print the timer:
  std::cout << "This is timer " << timer_number;

  // decrement and check counter value
  if (--m_counters[timer_number] == 0)
  {
    std::cout << " being disconnected" <<  std::endl;

    // delete the counter entry in the STL MAP
    m_counters.erase(timer_number);

    // delete the connection entry in the STL MAP
    m_timers.erase(timer_number);

    // Note that we do not have to explicitly call disconnect() on the
    // connection since Gtk::Main does this for us when we return false.
    return false;
  }

  // Print the timer value
  std::cout << " - " << m_counters[timer_number] << "/"
      << count_value << std::endl;

 // Keep going (do not disconnect yet):
  return true;
}
