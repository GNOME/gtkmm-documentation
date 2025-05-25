/* gtkmm example Copyright (C) 2013 gtkmm development team
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

#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm.h>
#include "examplerow.h"

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();

private:
  // Signal handlers.
  void on_selection_mode_changed();
  void on_single_click_toggled();
  void on_row_selected(Gtk::ListBoxRow* row);
  void on_row_activated(Gtk::ListBoxRow* row);
  void on_sort_clicked();
  void on_reverse_sort_clicked();
  void on_change_clicked();
  void on_filter_clicked();
  //void on_unfilter_clicked();
  void on_add_clicked();
  void on_separate_clicked();
  void on_unseparate_clicked();
  void on_visibility_clicked();

  static int sort_func(Gtk::ListBoxRow* row1, Gtk::ListBoxRow* row2);
  static void update_header_func(Gtk::ListBoxRow* row, Gtk::ListBoxRow* before);

  // Member data.
  Gtk::Box m_HBox;
  Gtk::Box m_VBox1;
  Gtk::Box m_VBox2;
  Gtk::ListBox m_ListBox;
  Gtk::DropDown m_DropDown;
  Gtk::CheckButton m_CheckButton_SingleClick;
  Gtk::ScrolledWindow m_ScrolledWindow;
  ExampleRow m_Row3;
  Gtk::Box m_VBox_Row;
  Gtk::Box m_HBox_Row;
  Gtk::Label m_Label_Row;
  Gtk::CheckButton m_CheckButton_Row1;
  Gtk::CheckButton m_CheckButton_Row2;
  Gtk::Button m_Button_Row1;
  Gtk::Button m_Button_Row2;
  Gtk::Button m_Button_Sort;
  Gtk::Button m_Button_ReverseSort;
  Gtk::Button m_Button_Change;
  Gtk::Button m_Button_Filter;
  Gtk::Button m_Button_Unfilter;
  Gtk::Button m_Button_Add;
  Gtk::Button m_Button_Separate;
  Gtk::Button m_Button_Unseparate;
  Gtk::Button m_Button_Visibility;
};

#endif // GTKMM_EXAMPLEWINDOW_H
