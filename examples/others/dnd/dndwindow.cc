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

#include "dndwindow.h"
#include "dnd_images.h"
#include <gtkmm/application.h>
#include <iostream>

// This example is similar to gtk+/tests/testdnd.

DnDWindow::DnDWindow()
: m_Label_Drop("Drop here\n"),
  m_Label_Drag("Drag Here\n"),
  m_Label_Popup("Popup\n"),
  m_PopupWindow(Gtk::WindowType::POPUP)
{
  set_title("Drag-and-drop example");
  set_default_size(300, 150);

  add(m_Grid);

  m_drag_icon = Gdk::Pixbuf::create_from_xpm_data(drag_icon_xpm);
  m_trashcan_open = Gdk::Pixbuf::create_from_xpm_data(trashcan_open_xpm);
  m_trashcan_closed = Gdk::Pixbuf::create_from_xpm_data(trashcan_closed_xpm);

  //Targets:
  m_listTargets.push_back("STRING");
  m_listTargets.push_back("text/plain");
  m_listTargets.push_back("text/plain;charset=utf-8");
  if (!Glib::get_charset())
  {
    std::string charset;
    Glib::get_charset(charset);
    m_listTargets.push_back("text/plain;charset=" + charset);
  }
  m_listTargets.push_back("application/x-rootwin-drop");

  //Targets without rootwin:
  m_listTargetsNoRoot.assign(m_listTargets.begin(), --m_listTargets.end());

  // Drop site

  auto formats = Gdk::ContentFormats::create(m_listTargetsNoRoot);
  auto dest = Gtk::DropTarget::create(formats, Gdk::DragAction::COPY | Gdk::DragAction::MOVE);
  dest->signal_drag_drop().connect(sigc::mem_fun(*this, &DnDWindow::on_label_drop_drag_drop), false);
  m_Label_Drop.add_controller(dest);

  m_Grid.attach(m_Label_Drop, 0, 0);
  m_Label_Drop.set_expand(true);

  // Popup site

  dest = Gtk::DropTarget::create(formats, Gdk::DragAction::COPY | Gdk::DragAction::MOVE);
  dest->signal_accept().connect(sigc::mem_fun(*this, &DnDWindow::on_label_popup_accept), false);
  dest->signal_drag_enter().connect(sigc::mem_fun(*this, &DnDWindow::on_label_popup_drag_enter));
  dest->signal_drag_leave().connect(sigc::mem_fun(*this, &DnDWindow::on_label_popup_drag_leave));
  m_Label_Popup.add_controller(dest);

  m_Grid.attach(m_Label_Popup, 1, 1);
  m_Label_Popup.set_expand(true);

  // Image

  formats = Gdk::ContentFormats::create();
  dest = Gtk::DropTarget::create(formats, Gdk::DragAction::MOVE);
  dest->signal_accept().connect(sigc::mem_fun(*this, &DnDWindow::on_image_accept), false);
  dest->signal_drag_leave().connect(sigc::mem_fun(*this, &DnDWindow::on_image_drag_leave));
  dest->signal_drag_drop().connect(sigc::mem_fun(*this, &DnDWindow::on_image_drag_drop), false);
  m_Image.add_controller(dest);

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

      auto dest = Gtk::DropTarget::create(formats, Gdk::DragAction::COPY | Gdk::DragAction::MOVE);
      dest->signal_accept().connect(sigc::mem_fun(*this, &DnDWindow::on_button_popup_accept), false);
      dest->signal_drag_enter().connect(sigc::mem_fun(*this, &DnDWindow::on_button_popup_drag_enter));
      dest->signal_drag_leave().connect(sigc::mem_fun(*this, &DnDWindow::on_button_popup_drag_leave));
      dest->signal_drag_drop().connect(sigc::mem_fun(*this, &DnDWindow::on_button_popup_drag_drop), false);
      pButton->add_controller(dest);
    }
  }

  m_PopupWindow.add(*pGrid);
}

bool DnDWindow::on_label_drop_drag_drop(const Glib::RefPtr<Gdk::Drop>& drop, int, int)
{
  drop->read_text_async(sigc::bind(sigc::mem_fun(*this, &DnDWindow::on_label_drop_got_data), drop));
  return true;
}

void DnDWindow::on_label_drop_got_data(Glib::RefPtr<Gio::AsyncResult>& result,
  const Glib::RefPtr<Gdk::Drop>& drop)
{
  try
  {
    const Glib::ustring dropped_string = drop->read_text_finish(result);
    std::cout << "Received \"" << dropped_string << "\" in label " << std::endl;
    drop->finish(Gdk::DragAction::COPY);
  }
  catch (const std::exception& ex)
  {
    std::cout << "Drop failed: " << ex.what() << std::endl;
    drop->failed();
  }
}

bool DnDWindow::on_label_popup_accept(const Glib::RefPtr<Gdk::Drop>& /* drop */)
{
  return true;
}

void DnDWindow::on_label_popup_drag_enter(const Glib::RefPtr<Gdk::Drop>& /* drop */)
{
  std::cout << "popsite enter" << std::endl;
  if (!m_popup_timer)
    m_popup_timer = Glib::signal_timeout().connect(sigc::mem_fun(*this, &DnDWindow::on_popup_timeout), 500);
}

void DnDWindow::on_label_popup_drag_leave(const Glib::RefPtr<Gdk::Drop>& /* drop */)
{
  std::cout << "popsite leave" << std::endl;
  if (m_popup_timer)
    m_popup_timer.disconnect();
}

bool DnDWindow::on_button_popup_accept(const Glib::RefPtr<Gdk::Drop>& drop)
{
  drop->status(Gdk::DragAction::COPY);
  return true;
}

void DnDWindow::on_button_popup_drag_enter(const Glib::RefPtr<Gdk::Drop>& /* drop */)
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
}

void DnDWindow::on_button_popup_drag_leave(const Glib::RefPtr<Gdk::Drop>& /* drop */)
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

bool DnDWindow::on_button_popup_drag_drop(const Glib::RefPtr<Gdk::Drop>& drop, int, int)
{
  drop->finish(Gdk::DragAction::COPY);
  on_popdown_timeout();
  return true;
}

bool DnDWindow::on_image_accept(const Glib::RefPtr<Gdk::Drop>& drop)
{
  if (!m_have_drag)
  {
    m_have_drag = true;
    m_Image.set(m_trashcan_open);
  }

  std::cout << drop->get_formats()->to_string() << std::endl;

  drop->status(Gdk::DragAction::MOVE);
  return true;
}

void DnDWindow::on_image_drag_leave(const Glib::RefPtr<Gdk::Drop>& /* drop */)
{
  std::cout << "trashcan leave" << std::endl;
  m_have_drag = false;
  m_Image.set(m_trashcan_closed);
}

bool DnDWindow::on_image_drag_drop(const Glib::RefPtr<Gdk::Drop>& drop, int, int)
{
  std::cout << "trashcan drop" << std::endl;
  m_have_drag = false;

  m_Image.set(m_trashcan_closed);

  const auto targets = drop->get_formats()->get_mime_types();
  if (!targets.empty())
  {
    drop->read_text_async(sigc::bind(sigc::mem_fun(*this, &DnDWindow::on_image_got_data), drop));
    return true;
  }
  drop->status(static_cast<Gdk::DragAction>(0));
  return false;
}

void DnDWindow::on_image_got_data(Glib::RefPtr<Gio::AsyncResult>& result,
  const Glib::RefPtr<Gdk::Drop>& drop)
{
  try
  {
    const Glib::ustring dropped_string = drop->read_text_finish(result);
    std::cout << "Received \"" << dropped_string << "\" in trashcan " << std::endl;
    drop->finish(Gdk::DragAction::MOVE);
  }
  catch (const std::exception& ex)
  {
    std::cout << "Drop failed: " << ex.what() << std::endl;
    drop->failed();
  }
}

void DnDWindow::on_label_drag_drag_end(const Glib::RefPtr<Gdk::Drag>& /* drag */,
  bool delete_data)
{
  if (delete_data)
    std::cout << "Delete the data!" << std::endl;
}

bool DnDWindow::on_popdown_timeout()
{
  m_popdown_timer.disconnect();

  m_PopupWindow.hide();
  m_popped_up = false;

  return false;
}

bool DnDWindow::on_popup_timeout()
{
  if (!m_popped_up)
  {
    m_PopupWindow.set_transient_for(*this);
    m_PopupWindow.show();
    m_popped_up = true;
  }

  m_popup_timer.disconnect();

  return false;
}
