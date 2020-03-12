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

#ifndef GTKMM_EXAMPLE_DNDWINDOW_H
#define GTKMM_EXAMPLE_DNDWINDOW_H

#include <gdkmm/drop.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>

class DnDWindow : public Gtk::Window
{

public:
  DnDWindow();
  virtual ~DnDWindow();

protected:
  //Signal handlers:
  Glib::RefPtr<Gdk::ContentProvider> on_label_drag_prepare_data(double x, double y);
  bool on_button_drop_drop_data(const Glib::ValueBase& value, double x, double y);

  //Member widgets:
  Gtk::Box m_HBox;
  Gtk::Label m_Label_Drag;
  Gtk::Button m_Button_Drop;
};

#endif // GTKMM_EXAMPLE_DNDWINDOW_H
