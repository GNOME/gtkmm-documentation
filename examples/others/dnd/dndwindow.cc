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

DnDWindow::DnDWindow()
: m_Label_Drop("Drop here\n"), m_Label_Popup("Popup\n"),
  m_Button("Drag Here\n"),
  m_have_drag(false),
  m_PopupWindow(Gtk::WindowType::POPUP)
{
  m_popped_up = false;
  m_in_popup = false;

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

  m_Label_Drop.drag_dest_set(Gdk::ContentFormats::create(m_listTargetsNoRoot), Gtk::DestDefaults::ALL, Gdk::DragAction::COPY | Gdk::DragAction::MOVE);

  m_Label_Drop.signal_drag_data_received().connect( sigc::mem_fun(*this, &DnDWindow::on_label_drop_drag_data_received) );

  m_Grid.attach(m_Label_Drop, 0, 0);
  m_Label_Drop.set_hexpand(true);
  m_Label_Drop.set_vexpand(true);

  m_Label_Popup.drag_dest_set(Gdk::ContentFormats::create(m_listTargetsNoRoot), Gtk::DestDefaults::ALL, Gdk::DragAction::COPY | Gdk::DragAction::MOVE);

  m_Grid.attach(m_Label_Popup, 1, 1);
  m_Label_Popup.set_hexpand(true);
  m_Label_Popup.set_vexpand(true);

  m_Label_Popup.signal_drag_motion().connect( sigc::mem_fun(*this, &DnDWindow::on_label_popup_drag_motion), true );
  m_Label_Popup.signal_drag_leave().connect( sigc::mem_fun(*this, &DnDWindow::on_label_popup_drag_leave) );

  m_Image.set(m_trashcan_closed);
  m_Image.drag_dest_set();

  m_Grid.attach(m_Image, 1, 0);
  m_Image.set_hexpand(true);
  m_Image.set_vexpand(true);

  m_Image.signal_drag_leave().connect( sigc::mem_fun(*this, &DnDWindow::on_image_drag_leave) );
  m_Image.signal_drag_motion().connect( sigc::mem_fun(*this, &DnDWindow::on_image_drag_motion), true );
  m_Image.signal_drag_drop().connect( sigc::mem_fun(*this, &DnDWindow::on_image_drag_drop), true );
  m_Image.signal_drag_data_received().connect( sigc::mem_fun(*this, &DnDWindow::on_image_drag_data_received) );

  /* Drag site */

  m_Button.drag_source_set(Gdk::ContentFormats::create(m_listTargets), Gdk::ModifierType::BUTTON1_MASK | Gdk::ModifierType::BUTTON3_MASK,
                           Gdk::DragAction::COPY | Gdk::DragAction::MOVE);

  m_Button.drag_source_set_icon(Gdk::Texture::create_for_pixbuf(m_drag_icon));

  m_Grid.attach(m_Button, 0, 1);
  m_Button.set_hexpand(true);
  m_Button.set_vexpand(true);

  m_Button.signal_drag_data_get().connect( sigc::mem_fun(*this, &DnDWindow::on_button_drag_data_get));
  m_Button.signal_drag_data_delete().connect( sigc::mem_fun(*this, &DnDWindow::on_button_drag_data_delete));

  create_popup();
}

DnDWindow::~DnDWindow()
{
}


void DnDWindow::on_label_drop_drag_data_received(const Glib::RefPtr<Gdk::Drop>& drop, const Gtk::SelectionData& selection_data)
{
  const int length = selection_data.get_length();
  const guchar* data = selection_data.get_data();

  if((length >= 0) && (selection_data.get_format() == 8))
  {
    g_print ("Received \"%s\" in label\n", (gchar *)data);
  }

  drop->failed();
}

bool DnDWindow::on_label_popup_drag_motion(const Glib::RefPtr<Gdk::Drop>&, int, int)
{
  if(!m_popup_timer)
    m_popup_timer = Glib::signal_timeout().connect( sigc::mem_fun(*this, &DnDWindow::on_popup_timeout), 500);

  return true;
}

void DnDWindow::on_label_popup_drag_leave(const Glib::RefPtr<Gdk::Drop>&)
{
 if(m_in_popup)
 {
   m_in_popup = false;
   if(!m_popdown_timer)
   {
     g_print ("added popdown\n");
     m_popdown_timer = Glib::signal_timeout().connect( sigc::mem_fun(*this, &DnDWindow::on_popdown_timeout), 500);
   }
 }
}

void DnDWindow::on_image_drag_data_received(const Glib::RefPtr<Gdk::Drop>& drop, const Gtk::SelectionData& selection_data)
{
  const int length = selection_data.get_length();
  const guchar* data = selection_data.get_data();

  if( (length >= 0) && (selection_data.get_format() == 8) )
  {
    g_print ("Received \"%s\" in trashcan\n", (gchar*)data);
  }

  drop->failed();
}

bool DnDWindow::on_image_drag_motion(const Glib::RefPtr<Gdk::Drop>& drop, int, int)
{
  if(!m_have_drag)
  {
    m_have_drag = true;
    m_Image.set(m_trashcan_open);
  }

  auto source_widget = Gtk::Widget::drag_get_source_widget(drop->get_drag());
  g_print ("motion, source %s\n", source_widget ?
           G_OBJECT_TYPE_NAME (source_widget) :
           "NULL");

  for(const auto& name : drop->get_formats()->get_mime_types())
  {
    g_print ("%s\n", name.c_str());
  }

  drop->status(drop->get_drag()->get_suggested_action());
  return true;
}

void DnDWindow::on_image_drag_leave(const Glib::RefPtr<Gdk::Drop>&)
{
  g_print("leave\n");
  m_have_drag = false;
  m_Image.set(m_trashcan_closed);
}

bool DnDWindow::on_image_drag_drop(const Glib::RefPtr<Gdk::Drop>& drop, int, int)
{
  g_print("drop\n");
  m_have_drag = false;

  m_Image.set(m_trashcan_closed);

  const auto targets = drop->get_formats()->get_mime_types();
  if(!targets.empty())
  {
    m_Image.drag_get_data(drop, targets[0]);
  }

  return true;
}


void DnDWindow::on_button_drag_data_get(const Glib::RefPtr<Gdk::Drag>&, Gtk::SelectionData& selection_data)
{
  if(selection_data.get_target() == "application/x-rootwin-drop")
    g_print ("I was dropped on the rootwin\n");
  else
    selection_data.set(selection_data.get_target(),
                       8 /* 8-bits format */, (const guchar*)"I'm Data!", 9 /* The length of I'm Data in bytes */);
}

void DnDWindow::on_button_drag_data_delete(const Glib::RefPtr<Gdk::Drag>&)
{
  g_print ("Delete the data!\n");
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
  if(!m_popped_up)
  {
    m_PopupWindow.show();
    m_popped_up = true;
  }

  m_popdown_timer = Glib::signal_timeout().connect( sigc::mem_fun(*this, &DnDWindow::on_popdown_timeout), 500);
  g_print ("added popdown\n");

  m_popup_timer.disconnect();

  return false;
}

void DnDWindow::create_popup()
{
  m_PopupWindow.set_position(Gtk::WindowPosition::MOUSE);

  //Create Grid and fill it:
  auto pGrid = Gtk::manage(new Gtk::Grid());

  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      char buffer[128];
      g_snprintf(buffer, sizeof(buffer), "%d,%d", i, j);
      auto pButton = Gtk::manage(new Gtk::Button(buffer));
      pGrid->attach(*pButton, i, j, 1, 1);

      pButton->drag_dest_set(Gdk::ContentFormats::create(m_listTargetsNoRoot), Gtk::DestDefaults::ALL, Gdk::DragAction::COPY | Gdk::DragAction::MOVE);
      pButton->signal_drag_motion().connect( sigc::mem_fun(*this, &DnDWindow::on_popup_button_drag_motion), true );
      pButton->signal_drag_leave().connect( sigc::mem_fun(*this, &DnDWindow::on_popup_button_drag_leave) );
    }
  }

  m_PopupWindow.add(*pGrid);
}

bool DnDWindow::on_popup_button_drag_motion(const Glib::RefPtr<Gdk::Drop>&, int, int)
{
  if(!m_in_popup)
  {
    m_in_popup = true;
    if(m_popdown_timer)
    {
      g_print ("removed popdown\n");
      m_popdown_timer.disconnect();
    }
  }

  return true;
}

void DnDWindow::on_popup_button_drag_leave(const Glib::RefPtr<Gdk::Drop>&)
{
 if(m_in_popup)
 {
   m_in_popup = false;
   if(!m_popdown_timer)
   {
     g_print ("added popdown\n");
     m_popdown_timer = Glib::signal_timeout().connect( sigc::mem_fun(*this, &DnDWindow::on_popdown_timeout), 500);
   }
 }
}
