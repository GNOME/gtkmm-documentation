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

#include "packbox.h"
#include <map>

namespace
{
  const std::map<Gtk::Align, Glib::ustring> align_string = {
    {Gtk::Align::FILL, "Gtk::Align::FILL"},
    {Gtk::Align::START, "Gtk::Align::START"},
    {Gtk::Align::END, "Gtk::Align::END"},
    {Gtk::Align::CENTER, "Gtk::Align::CENTER"},
    {Gtk::Align::BASELINE, "Gtk::Align::BASELINE"},
  };
}

PackBox::PackBox(bool homogeneous, int spacing, bool expand, Gtk::Align align, int margin)
: Gtk::Box(Gtk::Orientation::HORIZONTAL, spacing)
{
  set_homogeneous(homogeneous);

  m_buttons[0].set_label("box.append(button);");
  m_buttons[1].set_label("expand=" + Glib::ustring(expand ? "true" : "false"));
  m_buttons[2].set_label(align_string.at(align));
  m_buttons[3].set_label("margin=" + Glib::ustring::format(margin));

  for (auto& button : m_buttons)
  {
    append(button);
    button.set_hexpand(expand);
    button.set_halign(align);
    button.set_margin_start(margin);
    button.set_margin_end(margin);
  }
}
