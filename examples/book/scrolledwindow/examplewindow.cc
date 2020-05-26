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

#include "examplewindow.h"
#include <iostream>

ExampleWindow::ExampleWindow()
{
  set_title("Gtk::ScrolledWindow example");
  set_size_request(300, 300);

  m_ScrolledWindow.set_margin(10);

  /* the policy is one of Gtk::PolicyType::AUTOMATIC, or Gtk::PolicyType::ALWAYS.
   * Gtk::PolicyType::AUTOMATIC will automatically decide whether you need
   * scrollbars, whereas Gtk::PolicyType::ALWAYS will always leave the scrollbars
   * there.  The first one is the horizontal scrollbar, the second,
   * the vertical. */
  m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::ALWAYS);
  m_ScrolledWindow.set_expand();

  get_content_area()->append(m_ScrolledWindow);

  /* set the spacing to 10 on x and 10 on y */
  m_Grid.set_row_spacing(10);
  m_Grid.set_column_spacing(10);

  /* pack the grid into the scrolled window */
  m_ScrolledWindow.set_child(m_Grid);

  /* this simply creates a grid of toggle buttons
   * to demonstrate the scrolled window. */
  for(int i = 0; i < 10; i++)
  {
     for(int j = 0; j < 10; j++)
     {
        char buffer[32];
        sprintf(buffer, "button (%d,%d)\n", i, j);
        auto pButton = Gtk::make_managed<Gtk::ToggleButton>(buffer);
        m_Grid.attach(*pButton, i, j, 1, 1);
     }
  }

  /* Add a "close" button to the bottom of the dialog */
  add_button("_Close", Gtk::ResponseType::CLOSE);
  signal_response().connect(sigc::mem_fun(*this, &ExampleWindow::on_dialog_response));

  /* This makes it so the button is the default.
   * Simply hitting the "Enter" key will cause this button to activate. */
  set_default_response(Gtk::ResponseType::CLOSE);
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_dialog_response(int response_id)
{
  switch (response_id)
  {
  case Gtk::ResponseType::CLOSE:
  case Gtk::ResponseType::DELETE_EVENT:
    hide();
    break;
  default:
    std::cout << "Unexpected response_id=" << response_id << std::endl;
    break;
  }
}
