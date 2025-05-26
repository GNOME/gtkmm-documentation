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

#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm.h>
#include "canvas.h"

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  virtual ~ExampleWindow();

private:

  void load_icon_items();
  void load_toggle_items();
  void load_special_items();

  //Signal handlers:
  void on_combo_orientation_changed();
  void on_combo_style_changed();

  //Tree model columns:
  class ModelColumnsOrientation : public Gtk::TreeModel::ColumnRecord
  {
  public:

    ModelColumnsOrientation()
    { add(m_col_value); add(m_col_name); }

    Gtk::TreeModelColumn<Gtk::Orientation> m_col_value;
    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
  };

  ModelColumnsOrientation m_ColumnsOrientation;

  //Tree model columns:
  class ModelColumnsStyle : public Gtk::TreeModel::ColumnRecord
  {
  public:

    ModelColumnsStyle()
    { add(m_col_value); add(m_col_name); }

    Gtk::TreeModelColumn<int> m_col_value; //We use int to also allow -1
    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
  };

  ModelColumnsStyle m_ColumnsStyle;


  //Child widgets:
  Gtk::Box m_VBox;
  Gtk::Box m_HBox;
  Gtk::ComboBox m_ComboOrientation;
  Glib::RefPtr<Gtk::ListStore> m_refTreeModelOrientation;
  Gtk::ComboBox m_ComboStyle;
  Glib::RefPtr<Gtk::ListStore> m_refTreeModelStyle;
  Gtk::ToolPalette m_ToolPalette;
  Gtk::ScrolledWindow m_ScrolledWindowPalette;
  Gtk::ScrolledWindow m_ScrolledWindowCanvas;
  Canvas m_Canvas;
};

#endif //GTKMM_EXAMPLEWINDOW_H
