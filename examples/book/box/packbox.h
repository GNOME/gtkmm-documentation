/* gtkmm example Copyright (C) 2002 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef GTKMM_EXAMPLE_PACKBOX_H
#define GTKMM_EXAMPLE_PACKBOX_H

#include <gtkmm.h>

class PackBox : public Gtk::Box
{
public:
  PackBox(bool homogeneous = false, int spacing = 0, bool expand = false,
    Gtk::Align align = Gtk::Align::FILL, int margin = 0);

protected:
  Gtk::Button m_buttons[4];
};

#endif //GTKMM_EXAMPLE_PACKBOX_H
