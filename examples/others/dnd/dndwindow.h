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

  //Signal handlers and callback functions:
  bool on_label_drop_drag_drop(const Glib::RefPtr<Gdk::Drop>& drop, int x, int y);
  void on_label_drop_got_data(Glib::RefPtr<Gio::AsyncResult>& result,
    const Glib::RefPtr<Gdk::Drop>& drop);

  bool on_label_popup_accept(const Glib::RefPtr<Gdk::Drop>& drop);
  void on_label_popup_drag_enter(const Glib::RefPtr<Gdk::Drop>& drop);
  void on_label_popup_drag_leave(const Glib::RefPtr<Gdk::Drop>& drop);

  bool on_button_popup_accept(const Glib::RefPtr<Gdk::Drop>& drop);
  void on_button_popup_drag_enter(const Glib::RefPtr<Gdk::Drop>& drop);
  void on_button_popup_drag_leave(const Glib::RefPtr<Gdk::Drop>& drop);
  bool on_button_popup_drag_drop(const Glib::RefPtr<Gdk::Drop>& drop, int x, int y);

  bool on_image_accept(const Glib::RefPtr<Gdk::Drop>& drop);
  void on_image_drag_leave(const Glib::RefPtr<Gdk::Drop>& drop);
  bool on_image_drag_drop(const Glib::RefPtr<Gdk::Drop>& drop, int x, int y);
  void on_image_got_data(Glib::RefPtr<Gio::AsyncResult>& result,
    const Glib::RefPtr<Gdk::Drop>& drop);

  void on_label_drag_drag_end(const Glib::RefPtr<Gdk::Drag>& drag, bool delete_data);

  bool on_popdown_timeout();
  bool on_popup_timeout();

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
