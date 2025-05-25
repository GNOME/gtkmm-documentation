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

#include "idleexample.h"

IdleExample::IdleExample() :
  m_Box(Gtk::Orientation::VERTICAL, 5),
  m_ButtonQuit("_Quit", true)
{
  m_Box.set_margin(5);

  // Put buttons into container

  // Adding a few widgets:
  set_child(m_Box);
  m_Box.append(*Gtk::make_managed<Gtk::Label>("Formatting Windows drive C:"));
  m_Box.append(*Gtk::make_managed<Gtk::Label>("100 MB"));
  m_Box.append(m_ProgressBar_c);
  m_ProgressBar_c.set_expand();

  m_Box.append(*Gtk::make_managed<Gtk::Label>(""));

  m_Box.append(*Gtk::make_managed<Gtk::Label>("Formatting Windows drive D:"));
  m_Box.append(*Gtk::make_managed<Gtk::Label>("5000 MB"));
  m_Box.append(m_ProgressBar_d);
  m_ProgressBar_d.set_expand();

  auto hbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL,10);
  m_Box.append(*hbox);
  hbox->append(m_ButtonQuit);
  m_ButtonQuit.set_expand();
  m_ButtonQuit.set_halign(Gtk::Align::END);
  m_ButtonQuit.set_valign(Gtk::Align::END);

  // Connect the signal handlers:
  m_ButtonQuit.signal_clicked().connect( sigc::mem_fun(*this,
              &IdleExample::on_button_clicked) );

  // formatting drive c in timeout signal handler - called once every 50ms
  Glib::signal_timeout().connect( sigc::mem_fun(*this, &IdleExample::on_timer),
          50 );

  // formatting drive d in idle signal handler - called as quickly as possible
  Glib::signal_idle().connect( sigc::mem_fun(*this, &IdleExample::on_idle) );
}


void IdleExample::on_button_clicked()
{
  set_visible(false);
}

// this timer callback function is executed once every 50ms (set in connection
// above).  Use timeouts when speed is not critical. (ie periodically updating
// something).
bool IdleExample::on_timer()
{
  double value = m_ProgressBar_c.get_fraction();

  // Update progressbar 1/500th each time:
  m_ProgressBar_c.set_fraction(value + 0.002);

  return value < 0.99;  // return false when done
}


// This idle callback function is executed as often as possible, hence it is
// ideal for processing intensive tasks.
bool IdleExample::on_idle()
{
  double value = m_ProgressBar_d.get_fraction();

  // Update progressbar 1/5000th each time:
  m_ProgressBar_d.set_fraction(value + 0.0002);

  return value < 0.99;  // return false when done
}
