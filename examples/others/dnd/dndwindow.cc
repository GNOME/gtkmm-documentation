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
#include "dnd_images.h"
#include <gtkmm/application.h>
#include <iostream>
#include <map>
#include <initializer_list>

// This example is similar to gtk/tests/testdnd.

DnDWindow::DnDWindow()
: m_Label_Drop("Drop here\n"),
  m_Label_Drag("Drag Here\n"),
  m_Label_Popup("Popup\n"),
  m_PopupWindow()
{
  set_title("Drag-and-drop example");
  set_default_size(300, 150);

  set_child(m_Grid);

  m_drag_icon = Gdk::Pixbuf::create_from_xpm_data(drag_icon_xpm);
  m_trashcan_open = Gdk::Pixbuf::create_from_xpm_data(trashcan_open_xpm);
  m_trashcan_closed = Gdk::Pixbuf::create_from_xpm_data(trashcan_closed_xpm);

  // Drop site

  const GType ustring_type = Glib::Value<Glib::ustring>::value_type();
  auto dest = Gtk::DropTarget::create(ustring_type, Gdk::DragAction::COPY | Gdk::DragAction::MOVE);
  dest->signal_drop().connect(sigc::mem_fun(*this, &DnDWindow::on_label_drop_drop), false);
  m_Label_Drop.add_controller(dest);

  m_Grid.attach(m_Label_Drop, 0, 0);
  m_Label_Drop.set_expand(true);

  // Popup site

  auto controller = Gtk::DropControllerMotion::create();
  controller->signal_enter().connect(sigc::mem_fun(*this, &DnDWindow::on_label_popup_enter));
  controller->signal_leave().connect(sigc::mem_fun(*this, &DnDWindow::on_label_popup_leave));
  m_Label_Popup.add_controller(controller);

  m_Grid.attach(m_Label_Popup, 1, 1);
  m_Label_Popup.set_expand(true);

  // Image

  auto async = Gtk::DropTargetAsync::create(
    Gdk::ContentFormats::create(ustring_type), Gdk::DragAction::COPY | Gdk::DragAction::MOVE);
  async->signal_drag_enter().connect(sigc::mem_fun(*this, &DnDWindow::on_image_drag_enter), false);
  async->signal_drag_leave().connect(sigc::mem_fun(*this, &DnDWindow::on_image_drag_leave));
  async->signal_drop().connect(sigc::mem_fun(*this, &DnDWindow::on_image_drop), false);
  m_Image.add_controller(async);

  m_Image.set(m_trashcan_closed);

  m_Grid.attach(m_Image, 1, 0);
  m_Image.set_expand(true);

  // Drag site

  auto source = Gtk::DragSource::create();
  Glib::Value<Glib::ustring> value;
  value.init(value.value_type());
  value.set("I'm data!");
  auto content = Gdk::ContentProvider::create(value);
  source->set_content(content);
  source->set_actions(Gdk::DragAction::COPY | Gdk::DragAction::MOVE);
  source->set_icon(Gdk::Texture::create_for_pixbuf(m_drag_icon), 0, 0);
  source->signal_drag_end().connect(sigc::mem_fun(*this, &DnDWindow::on_label_drag_drag_end));
  m_Label_Drag.add_controller(source);

  m_Grid.attach(m_Label_Drag, 0, 1);
  m_Label_Drag.set_expand(true);

  create_popup();
}

DnDWindow::~DnDWindow()
{
}

void DnDWindow::create_popup()
{
  //Create Grid and fill it:
  auto pGrid = Gtk::make_managed<Gtk::Grid>();

  auto formats = Gdk::ContentFormats::create(Glib::Value<Glib::ustring>::value_type());

  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      char buffer[128];
      g_snprintf(buffer, sizeof(buffer), "%d,%d", i, j);
      auto pButton = Gtk::make_managed<Gtk::Button>(buffer);
      pButton->set_expand(true);
      pGrid->attach(*pButton, i, j);

      const GType ustring_type = Glib::Value<Glib::ustring>::value_type();
      auto dest = Gtk::DropTarget::create(ustring_type, Gdk::DragAction::COPY | Gdk::DragAction::MOVE);
      dest->signal_enter().connect(sigc::mem_fun(*this, &DnDWindow::on_button_popup_enter), false);
      dest->signal_leave().connect(sigc::mem_fun(*this, &DnDWindow::on_button_popup_leave));
      dest->signal_drop().connect(sigc::mem_fun(*this, &DnDWindow::on_button_popup_drop), false);
      pButton->add_controller(dest);
    }
  }

  m_PopupWindow.set_child(*pGrid);
}

bool DnDWindow::on_label_drop_drop(const Glib::ValueBase& value, double, double)
{
  if (G_VALUE_HOLDS(value.gobj(), Glib::Value<Glib::ustring>::value_type()))
  {
    // We got the value type that we expected.
    Glib::Value<Glib::ustring> ustring_value;
    ustring_value.init(value.gobj());
    const Glib::ustring dropped_string = ustring_value.get();

    std::cout << "Received \"" << dropped_string << "\" in label " << std::endl;
    return true;
  }
  else
  {
    std::cout << "Received unexpected data type \""
      << G_VALUE_TYPE_NAME(value.gobj()) << "\" in label " << std::endl;
    return false;
  }
}

void DnDWindow::on_label_popup_enter(double, double)
{
  std::cout << "popsite enter" << std::endl;
  if (!m_popup_timer)
    m_popup_timer = Glib::signal_timeout().connect(sigc::mem_fun(*this, &DnDWindow::on_popup_timeout), 500);
}

void DnDWindow::on_label_popup_leave()
{
  std::cout << "popsite leave" << std::endl;
  if (m_popup_timer)
    m_popup_timer.disconnect();
}

Gdk::DragAction DnDWindow::on_button_popup_enter(double, double)
{
  std::cout << "popup enter" << std::endl;
  if (!m_in_popup)
  {
    m_in_popup = true;
    if (m_popdown_timer)
    {
      std::cout << "removed popdown" << std::endl;
      m_popdown_timer.disconnect();
    }
  }
  return Gdk::DragAction::COPY;
}

void DnDWindow::on_button_popup_leave()
{
  std::cout << "popup leave" << std::endl;
  if (m_in_popup)
  {
    m_in_popup = false;
    if (!m_popdown_timer)
    {
      std::cout << "added popdown" << std::endl;
      m_popdown_timer = Glib::signal_timeout().connect(sigc::mem_fun(*this, &DnDWindow::on_popdown_timeout), 500);
    }
  }
}

bool DnDWindow::on_button_popup_drop(const Glib::ValueBase& /* value */, double, double)
{
  on_popdown_timeout();
  return true;
}

Gdk::DragAction DnDWindow::on_image_drag_enter(const Glib::RefPtr<Gdk::Drop>& drop, double, double)
{
  std::cout << "trashcan enter: " << drop->get_formats()->to_string() << std::endl;

  if (!m_have_drag)
  {
    m_have_drag = true;
    m_Image.set(m_trashcan_open);
  }

  return action_make_unique(drop->get_actions(), true);
}

void DnDWindow::on_image_drag_leave(const Glib::RefPtr<Gdk::Drop>& drop)
{
  std::cout << "trashcan leave: " << drop->get_formats()->to_string() << std::endl;

  m_have_drag = false;
  m_Image.set(m_trashcan_closed);
}

bool DnDWindow::on_image_drop(const Glib::RefPtr<Gdk::Drop>& drop, double, double)
{
  std::cout << "trashcan drop: " << drop->get_formats()->to_string() << std::endl;
  m_have_drag = false;

  m_Image.set(m_trashcan_closed);

  drop->finish(action_make_unique(drop->get_actions(), true));
  return true;
}

void DnDWindow::on_label_drag_drag_end(const Glib::RefPtr<Gdk::Drag>& /* drag */,
  bool delete_data)
{
  std::cout << (delete_data ? "D" : "Don't d") << "elete the data!" << std::endl;
}

bool DnDWindow::on_popdown_timeout()
{
  m_popdown_timer.disconnect();

  m_PopupWindow.set_visible(false);
  m_popped_up = false;

  return false;
}

bool DnDWindow::on_popup_timeout()
{
  if (!m_popped_up)
  {
    m_PopupWindow.set_transient_for(*this);
    m_PopupWindow.set_visible(true);
    m_popped_up = true;
  }

  m_popup_timer.disconnect();

  return false;
}

//static
Gdk::DragAction DnDWindow::action_make_unique(Gdk::DragAction actions, bool print)
{
  if (!print && Gdk::Drag::action_is_unique(actions))
    return actions;

  if (print)
    std::cout << "Possible actions:";

  std::map<Gdk::DragAction, Glib::ustring> action_strings;
  action_strings[Gdk::DragAction::COPY] = " COPY";
  action_strings[Gdk::DragAction::MOVE] = " MOVE";
  action_strings[Gdk::DragAction::LINK] = " LINK";

  auto unique_action = static_cast<Gdk::DragAction>(0);

  for (const auto tested_action :
      {Gdk::DragAction::COPY, Gdk::DragAction::MOVE, Gdk::DragAction::LINK})
  {
    if (static_cast<int>(actions & tested_action))
    {
      if (print)
        std::cout << action_strings[tested_action];
      else
        return tested_action;
      if (static_cast<int>(unique_action) == 0)
        unique_action = tested_action;
    }
  }
  if (print)
    std::cout << "; Selected action:" << action_strings[unique_action] << std::endl;
  return unique_action;
}
