/* gtkmm example Copyright (C) 2004 gtkmm development team
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

#include "examplewindow.h"

ExampleWindow::ExampleWindow()
: m_VBox(Gtk::Orientation::VERTICAL),
  m_Button_Child("Child button"),
  m_Label_Child("Child label", Gtk::Align::END, Gtk::Align::CENTER),
  m_Button_Quit("Quit")
{
  set_title("Custom Container example");
  set_default_size(400, 200);

  m_VBox.set_margin(6);
  set_child(m_VBox);

  //Add the child widgets to the custom container:
  m_MyContainer.append(m_Button_Child);
  m_MyContainer.append(m_Label_Child);
  m_MyContainer.prepend(*Gtk::make_managed<Gtk::Label>(
    "First line\nSecond line\nThird line"));
  m_MyContainer.set_expand();
  m_VBox.append(m_MyContainer);

#if HAS_SIGNAL_DESTROY
  // A managed custom container.
  auto container = Gtk::make_managed<MyContainer>();
  container->prepend(*Gtk::make_managed<Gtk::Label>("Second custom container"));
  container->set_expand();
  m_VBox.append(*container);
#endif
  m_VBox.append(m_ButtonBox);

  m_ButtonBox.append(m_Button_Quit);
  m_ButtonBox.set_margin(6);
  m_Button_Quit.set_hexpand(true);
  m_Button_Quit.set_halign(Gtk::Align::END);
  m_Button_Quit.signal_clicked().connect( sigc::mem_fun(*this,
              &ExampleWindow::on_button_quit) );
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit()
{
  set_visible(false);
}
