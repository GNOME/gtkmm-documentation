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

#ifndef GTKMM_EXAMPLE_PACKBOX_H
#define GTKMM_EXAMPLE_PACKBOX_H

#include <gtkmm.h>

class PackBox : public Gtk::Box
{
public:
  PackBox(bool homogeneous, int spacing, Gtk::PackOptions options, int padding = 0);
  virtual ~PackBox();

protected:
  Gtk::Button m_button1, m_button2, m_button3;
  Gtk::Button* m_pbutton4;
};

#endif //GTKMM_EXAMPLE_PACKBOX_H
