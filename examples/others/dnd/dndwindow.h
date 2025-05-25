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

#ifndef GTKMM_EXAMPLE_DNDWINDOW_H
#define GTKMM_EXAMPLE_DNDWINDOW_H

#include <gtkmm.h>
#include <list>

class DnDWindow : public Gtk::Window
{
public:
  DnDWindow();
  virtual ~DnDWindow();

protected:
  void create_popup();

  //Signal handlers and callback functions:
  bool on_label_drop_drop(const Glib::ValueBase& value, double x, double y);

  void on_label_popup_enter(double x, double y);
  void on_label_popup_leave();

  Gdk::DragAction on_button_popup_enter(double x, double y);
  void on_button_popup_leave();
  bool on_button_popup_drop(const Glib::ValueBase& value, double x, double y);

  Gdk::DragAction on_image_drag_enter(const Glib::RefPtr<Gdk::Drop>& drop, double x, double y);
  void on_image_drag_leave(const Glib::RefPtr<Gdk::Drop>& drop);
  bool on_image_drop(const Glib::RefPtr<Gdk::Drop>& drop, double x, double y);

  void on_label_drag_drag_end(const Glib::RefPtr<Gdk::Drag>& drag, bool delete_data);

  bool on_popdown_timeout();
  bool on_popup_timeout();

  static Gdk::DragAction action_make_unique(Gdk::DragAction actions, bool print);

  //Member widgets:
  Gtk::Grid m_Grid;
  Gtk::Label m_Label_Drop;
  Gtk::Image m_Image;
  Gtk::Label m_Label_Drag;
  Gtk::Label m_Label_Popup;

  Glib::RefPtr<Gdk::Pixbuf> m_drag_icon;
  Glib::RefPtr<Gdk::Pixbuf> m_trashcan_open;
  Glib::RefPtr<Gdk::Pixbuf> m_trashcan_closed;

  bool m_have_drag = false;

  Gtk::Window m_PopupWindow;  //This is a candidate for being a separate class.
  bool m_popped_up = false;
  bool m_in_popup = false;
  sigc::connection m_popdown_timer;
  sigc::connection m_popup_timer;

  //Targets:
  std::vector<Glib::ustring> m_listTargets;
  std::vector<Glib::ustring> m_listTargetsNoRoot;
};

#endif // GTKMM_EXAMPLE_DNDWINDOW_H
