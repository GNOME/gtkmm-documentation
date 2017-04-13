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

#include "packbox.h"

PackBox::PackBox(bool homogeneous, int spacing, Gtk::PackOptions options,
        int margin)
: Gtk::Box(Gtk::Orientation::HORIZONTAL, spacing),
  m_button1("box.pack_start("),
  m_button2("button,"),
  m_button3((options == Gtk::PACK_SHRINK) ? "Gtk::PACK_SHRINK);" :
            ((options == Gtk::PACK_EXPAND_PADDING) ?
             "Gtk::PACK_EXPAND_PADDING);" : "Gtk::PACK_EXPAND_WIDGET);"))
{
  set_homogeneous(homogeneous);

  m_button1.set_margin_start(margin);
  m_button1.set_margin_end(margin);
  pack_start(m_button1, options);

  m_button2.set_margin_start(margin);
  m_button2.set_margin_end(margin);
  pack_start(m_button2, options);

  m_button3.set_margin_start(margin);
  m_button3.set_margin_end(margin);
  pack_start(m_button3, options);

  m_pbutton4 = new Gtk::Button("margin=" + Glib::ustring::format(margin));
  m_pbutton4->set_margin_start(margin);
  m_pbutton4->set_margin_end(margin);
  pack_start(*m_pbutton4, options);
}

PackBox::~PackBox()
{
  delete m_pbutton4;
}

