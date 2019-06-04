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

#include <gtkmm/cellrenderertext.h>
#include <gtkmm/window.h>
#include <gdkmm.h>

class PopupEntry;


class CellRendererPopup : public Gtk::CellRendererText
{
public:
  CellRendererPopup();
  ~CellRendererPopup() override;

  PopupEntry*  get_popup_entry();
  Gtk::Window* get_popup_window();

  void set_focus_widget(Gtk::Widget& focus_widget);
  Gtk::Widget* get_focus_widget();

  using SignalShowPopup = sigc::signal<void(const Glib::ustring&,int,int,int,int)>;
  SignalShowPopup& signal_show_popup();

  using SignalHidePopup = sigc::signal<void()>;
  SignalHidePopup& signal_hide_popup();

  void hide_popup();

protected:
  void get_preferred_width_vfunc(Gtk::Widget& widget,
    int& minimum_width, int& natural_width) const override;
  void get_preferred_width_for_height_vfunc(Gtk::Widget& widget, int height,
    int& minimum_width, int& natural_width) const override;

  Gtk::CellEditable* start_editing_vfunc(const Glib::RefPtr<const Gdk::Event>& event,
                                         Gtk::Widget& widget,
                                         const Glib::ustring& path,
                                         const Gdk::Rectangle& background_area,
                                         const Gdk::Rectangle& cell_area,
                                         Gtk::CellRendererState flags) override;

  virtual void on_show_popup(const Glib::ustring& path, int x1, int y1, int x2, int y2);
  void on_hide_popup();

private:
  using Self = CellRendererPopup;

  SignalShowPopup signal_show_popup_;
  SignalHidePopup signal_hide_popup_;

  mutable int   button_width_; //mutable because it is just a cache.
  Gtk::Window   popup_window_;
  Gtk::Widget*  focus_widget_;
  PopupEntry*   popup_entry_;
  bool          shown_;
  bool          editing_canceled_;
  Glib::RefPtr<Gtk::GestureClick> gesture_;

  void on_popup_window_pressed(int n_press, double x, double y);
  bool on_popup_window_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state);
  void on_style_updated();

  void on_popup_editing_done();
  void on_popup_arrow_clicked();
  void on_popup_hide();
};
