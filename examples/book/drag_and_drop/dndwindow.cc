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
#include <gdkmm/contentformats.h>
#include <gdkmm/contentprovider.h>
#include <gtkmm/dragsource.h>
#include <gtkmm/droptarget.h>
#include <iostream>

DnDWindow::DnDWindow()
: m_Label_Drag("Drag Here\n"),
  m_Button_Drop("Drop here\n")
{
  set_title("DnD example");

  add(m_HBox);

  //Drag site:

  //Make m_Label_Drag a DnD drag source:
  const GType ustring_type = Glib::Value<Glib::ustring>::value_type();
  auto source = Gtk::DragSource::create();
  source->signal_prepare().connect(
    sigc::mem_fun(*this, &DnDWindow::on_label_drag_prepare_data), false);
  m_Label_Drag.add_controller(source);

  m_HBox.add(m_Label_Drag);
  m_Label_Drag.set_expand(true);

  //Drop site:

  //Make m_Button_Drop a DnD drop destination:
  auto formats = Gdk::ContentFormats::create(ustring_type);
  auto target = Gtk::DropTarget::create(formats, Gdk::DragAction::COPY);
  target->signal_drag_drop().connect(
    sigc::mem_fun(*this, &DnDWindow::on_button_drop_drag_drop), false);
  m_Button_Drop.add_controller(target);

  m_HBox.add(m_Button_Drop);
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

bool DnDWindow::on_button_drop_drag_drop(const Glib::RefPtr<Gdk::Drop>& drop, int, int)
{
  drop->read_text_async(sigc::bind(sigc::mem_fun(*this, &DnDWindow::on_button_drop_got_data), drop));
  return true;
}

void DnDWindow::on_button_drop_got_data(Glib::RefPtr<Gio::AsyncResult>& result,
  const Glib::RefPtr<Gdk::Drop>& drop)
{
  try
  {
    const Glib::ustring dropped_string = drop->read_text_finish(result);
    std::cout << "Received \"" << dropped_string << "\" in button " << std::endl;
    drop->finish(Gdk::DragAction::COPY);
  }
  catch (const std::exception& ex)
  {
    std::cout << "Drop failed: " << ex.what() << std::endl;
    drop->failed();
  }
}
