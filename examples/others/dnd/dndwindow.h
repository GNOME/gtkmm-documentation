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

#include <gtkmm.h>
#include <list>

class DnDWindow : public Gtk::Window
{

public:
  DnDWindow();
  virtual ~DnDWindow();

protected:
  void create_popup();

  //Signal handlers:
  void on_label_drop_drag_data_received(const Glib::RefPtr<Gdk::Drop>& drop, const Gtk::SelectionData& selection_data);
  bool on_label_popup_drag_motion(const Glib::RefPtr<Gdk::Drop>& drop, int x, int y);
  void on_label_popup_drag_leave(const Glib::RefPtr<Gdk::Drop>& drop);

  void on_image_drag_data_received(const Glib::RefPtr<Gdk::Drop>& drop, const Gtk::SelectionData& selection_data);
  bool on_image_drag_motion(const Glib::RefPtr<Gdk::Drop>& drop, int x, int y);
  void on_image_drag_leave(const Glib::RefPtr<Gdk::Drop>& drop);
  bool on_image_drag_drop(const Glib::RefPtr<Gdk::Drop>& drop, int x, int y);

  void on_button_drag_data_get(const Glib::RefPtr<Gdk::Drag>& drag, Gtk::SelectionData& selection_data);
  void on_button_drag_data_delete(const Glib::RefPtr<Gdk::Drag>& drag);

  bool on_popdown_timeout();
  bool on_popup_timeout();

  bool on_popup_button_drag_motion(const Glib::RefPtr<Gdk::Drop>& drop, int x, int y);
  void on_popup_button_drag_leave(const Glib::RefPtr<Gdk::Drop>& drop);


  //Member widgets:
  Gtk::Grid m_Grid;
  Gtk::Label m_Label_Drop, m_Label_Popup;
  Gtk::Image m_Image;
  Gtk::Button m_Button;

  Glib::RefPtr<Gdk::Pixbuf> m_drag_icon;
  Glib::RefPtr<Gdk::Pixbuf> m_trashcan_open;
  Glib::RefPtr<Gdk::Pixbuf> m_trashcan_closed;

  bool m_have_drag;

  Gtk::Window m_PopupWindow;  //This is a candidate for being a separate class.
  bool m_popped_up;
  bool m_in_popup;
  sigc::connection m_popdown_timer;
  sigc::connection m_popup_timer;

  //Targets:
  std::vector<Glib::ustring> m_listTargets, m_listTargetsNoRoot;
};

#endif // GTKMM_EXAMPLE_DNDWINDOW_H
