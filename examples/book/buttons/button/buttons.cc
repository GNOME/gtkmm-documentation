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

#include "buttons.h"
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>
#include <iostream>

Buttons::Buttons()
{
  // This corresponds to Gtk::Bin::add_pixlabel("info.xpm", "cool button") in gtkmm3.
  //Create Image and Label widgets:
  auto pmap = Gtk::make_managed<Gtk::Image>("info.xpm");
  auto label = Gtk::make_managed<Gtk::Label>("cool button");
  label->set_expand(true);

  //Put them in a Box:
  auto hbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 5);
  hbox->append(*pmap);
  hbox->append(*label);

  //And put that Box in the button:
  m_button.set_child(*hbox);

  set_title("Pixmap'd buttons!");

  m_button.signal_clicked().connect( sigc::mem_fun(*this,
              &Buttons::on_button_clicked) );

  m_button.set_margin(10);
  set_child(m_button);
}

Buttons::~Buttons()
{
}

void Buttons::on_button_clicked()
{
  std::cout << "The Button was clicked." << std::endl;
}
