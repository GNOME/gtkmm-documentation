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
#include <iostream>

DnDWindow::DnDWindow()
: m_Button_Drag("Drag Here\n"),
  m_Label_Drop("Drop here\n")
{
  set_title("DnD example");

  add(m_HBox);

  //Drag site:

  //Make m_Button_Drag a DnD drag source:
  m_Button_Drag.drag_source_set(Glib::RefPtr<Gdk::ContentFormats>());
  m_Button_Drag.drag_source_add_text_targets();

  //Connect signals:
  m_Button_Drag.signal_drag_data_get().connect(sigc::mem_fun(*this,
              &DnDWindow::on_button_drag_data_get));

  m_HBox.add(m_Button_Drag);
  m_Button_Drag.set_expand(true);

  //Drop site:

  //Make m_Label_Drop a DnD drop destination:
  // Don't do this: m_Label_Drop.drag_dest_set({}).
  // It would call the wrong overload of drag_dest_set() with the wrong
  // default values of flags and actions (wrong in this simple example).
  m_Label_Drop.drag_dest_set(Glib::RefPtr<Gdk::ContentFormats>());
  m_Label_Drop.drag_dest_add_text_targets();

  //Connect signals:
  m_Label_Drop.signal_drag_data_received().connect(sigc::mem_fun(*this,
              &DnDWindow::on_label_drop_drag_data_received) );

  m_HBox.add(m_Label_Drop);
  m_Label_Drop.set_expand(true);
}

DnDWindow::~DnDWindow()
{
}

void DnDWindow::on_button_drag_data_get(
        const Glib::RefPtr<Gdk::Drag>&,
        Gtk::SelectionData& selection_data)
{
  selection_data.set(selection_data.get_target(), 8 /* 8 bits format */,
          (const guchar*)"I'm Data!",
          9 /* the length of I'm Data! in bytes */);
}

void DnDWindow::on_label_drop_drag_data_received(
        const Glib::RefPtr<Gdk::Drop>& drop,
        const Gtk::SelectionData& selection_data)
{
  const int length = selection_data.get_length();
  if((length >= 0) && (selection_data.get_format() == 8))
  {
    std::cout << "Received \"" << selection_data.get_data_as_string()
        << "\" in label " << std::endl;
  }

  drop->failed();
}
