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

#include "dndwindow.h"
#include <gdkmm/contentprovider.h>
#include <gtkmm/dragsource.h>
#include <gtkmm/droptarget.h>
#include <iostream>

DnDWindow::DnDWindow()
: m_Label_Drag("Drag Here\n"),
  m_Button_Drop("Drop here\n")
{
  set_title("DnD example");

  set_child(m_HBox);

  //Drag site:

  //Make m_Label_Drag a DnD drag source:
  auto source = Gtk::DragSource::create();
  source->set_actions(Gdk::DragAction::COPY);
  source->signal_prepare().connect(
    sigc::mem_fun(*this, &DnDWindow::on_label_drag_prepare_data), false);
  m_Label_Drag.add_controller(source);

  m_HBox.append(m_Label_Drag);
  m_Label_Drag.set_expand(true);

  //Drop site:

  //Make m_Button_Drop a DnD drop destination:
  const GType ustring_type = Glib::Value<Glib::ustring>::value_type();
  auto target = Gtk::DropTarget::create(ustring_type, Gdk::DragAction::COPY);
  target->signal_drop().connect(
    sigc::mem_fun(*this, &DnDWindow::on_button_drop_drop_data), false);
  m_Button_Drop.add_controller(target);

  m_HBox.append(m_Button_Drop);
  m_Button_Drop.set_expand(true);
}

DnDWindow::~DnDWindow()
{
}

// In this simple example where just a small amount of data is copied,
// it would be reasonable to store the ContentProvider in the DragSource.
// Then this signal handler would be unnecessary.
Glib::RefPtr<Gdk::ContentProvider> DnDWindow::on_label_drag_prepare_data(double, double)
{
  Glib::Value<Glib::ustring> ustring_value;
  ustring_value.init(ustring_value.value_type());
  ustring_value.set("I'm Data!");
  return Gdk::ContentProvider::create(ustring_value);
}

bool DnDWindow::on_button_drop_drop_data(const Glib::ValueBase& value, double, double)
{
  if (G_VALUE_HOLDS(value.gobj(), Glib::Value<Glib::ustring>::value_type()))
  {
    // We got the value type that we expected.
    Glib::Value<Glib::ustring> ustring_value;
    ustring_value.init(value.gobj());
    const Glib::ustring dropped_string = ustring_value.get();

    std::cout << "Received \"" << dropped_string << "\" in button " << std::endl;
    return true;
  }
  else
  {
    std::cout << "Received unexpected data type \""
      << G_VALUE_TYPE_NAME(value.gobj()) << "\" in button " << std::endl;
    return false;
  }
}
