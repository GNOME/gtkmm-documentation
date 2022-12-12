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

#ifndef GTKMM_EXAMPLE_RANGEWIDGETS_H
#define GTKMM_EXAMPLE_RANGEWIDGETS_H

#include <gtkmm.h>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  ~ExampleWindow() override;

protected:
  //Signal handlers:
  void on_checkbutton_toggled();
  void on_dropdown_position();
  void on_adjustment1_value_changed();
  void on_adjustment2_value_changed();
  void on_button_quit();

  //Child widgets:
  Gtk::Box m_VBox_Top, m_VBox2, m_VBox_HScale;
  Gtk::Box m_HBox_Scales, m_HBox_DropDown, m_HBox_Digits, m_HBox_PageSize;

  Glib::RefPtr<Gtk::Adjustment> m_adjustment, m_adjustment_digits, m_adjustment_pagesize;

  Gtk::Scale m_VScale;
  Gtk::Scale m_HScale, m_Scale_Digits, m_Scale_PageSize;

  Gtk::Separator m_Separator;

  Gtk::CheckButton m_CheckButton;

  Gtk::Scrollbar m_Scrollbar;

  Gtk::DropDown m_DropDown_Position;
  Gtk::Button m_Button_Quit;
};

#endif //GTKMM_EXAMPLE_RANGEWIDGETS_H
