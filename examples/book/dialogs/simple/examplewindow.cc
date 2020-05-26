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
#include <gtkmm/dialog.h>

ExampleWindow::ExampleWindow()
: m_Button("Show Dialog"),
  m_Dialog("The Dialog")
{
  set_title("Gtk::Dialog example");

  set_child(m_Button);
  m_Button.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_clicked) );

  m_Dialog.set_default_size(150, 100);
  m_Dialog.set_transient_for(*this);
  m_Dialog.set_modal();
  m_Dialog.set_hide_on_close();
  m_Dialog.signal_response().connect(
    sigc::hide(sigc::mem_fun(m_Dialog, &Gtk::Widget::hide)));
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_clicked()
{
  m_Dialog.show();
}
