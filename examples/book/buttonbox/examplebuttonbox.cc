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

#include "examplebuttonbox.h"

ExampleButtonBox::ExampleButtonBox(bool horizontal,
       const Glib::ustring& title,
       gint spacing,
       Gtk::ButtonBoxStyle layout)
: Gtk::Frame(title),
  m_Button_OK("OK"),
  m_Button_Cancel("Cancel"),
  m_Button_Help("Help")
{
  Gtk::ButtonBox* bbox = nullptr;

  if(horizontal)
    bbox = Gtk::make_managed<Gtk::ButtonBox>(Gtk::ORIENTATION_HORIZONTAL);
  else
    bbox = Gtk::make_managed<Gtk::ButtonBox>(Gtk::ORIENTATION_VERTICAL);

  bbox->set_border_width(5);

  add(*bbox);

  /* Set the appearance of the Button Box */
  bbox->set_layout(layout);
  bbox->set_spacing(spacing);

  bbox->add(m_Button_OK);
  bbox->add(m_Button_Cancel);
  bbox->add(m_Button_Help);
}

