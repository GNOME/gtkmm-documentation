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

#include <gtkmm/cellrenderertext.h>
#include <gtkmm/window.h>
#include <gdkmm.h>

class PopupEntry;


class CellRendererPopup : public Gtk::CellRendererText
{
public:
  CellRendererPopup();
  virtual ~CellRendererPopup();

  PopupEntry*  get_popup_entry();
  Gtk::Window* get_popup_window();

  void set_focus_widget(Gtk::Widget& focus_widget);
  Gtk::Widget* get_focus_widget();

  typedef sigc::signal<void,const Glib::ustring&,int,int,int,int> SignalShowPopup;
  SignalShowPopup& signal_show_popup();

  typedef sigc::signal<void> SignalHidePopup;
  SignalHidePopup& signal_hide_popup();

  void hide_popup();

protected:

  //TODO: Port this to gtkmm 3:
  /*
  void get_preferred_size_vfunc(Gtk::Widget& widget,
                              const Gdk::Rectangle* cell_area,
                              int* x_offset, int* y_offset,
                              int* width,    int* height) const  override;
  */

  Gtk::CellEditable* start_editing_vfunc(GdkEvent* event,
                                                 Gtk::Widget& widget,
                                                 const Glib::ustring& path,
                                                 const Gdk::Rectangle& background_area,
                                                 const Gdk::Rectangle& cell_area,
                                                 Gtk::CellRendererState flags) override;

  virtual void on_show_popup(const Glib::ustring& path, int x1, int y1, int x2, int y2);
  void on_hide_popup();

private:
  typedef CellRendererPopup Self;

  SignalShowPopup  signal_show_popup_;
  SignalHidePopup signal_hide_popup_;

  mutable int   button_width_; //mutable because it is just a cache.
  Gtk::Window   popup_window_;
  Gtk::Widget*  focus_widget_;
  PopupEntry*   popup_entry_;
  bool          shown_;
  bool          editing_canceled_;

  bool on_button_press_event(GdkEventButton* event);
  bool on_key_press_event(GdkEventKey* event);
  void on_style_changed(const Glib::RefPtr<Gtk::Style>& previous_style);

  void on_popup_editing_done();
  void on_popup_arrow_clicked();
  void on_popup_hide();
};
