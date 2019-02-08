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

#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm.h>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  virtual ~ExampleWindow();

protected:
  //Signal handlers:
  void on_button_quit();

  void on_filter_modify(const Gtk::TreeModel::iterator& iter, Glib::ValueBase& value, int column);

  //Tree model columns:
  //These are the types of the columns in the child model:
  class ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
  public:

    ModelColumns()
    { add(m_col_id); add(m_col_name); add(m_col_something); }

    Gtk::TreeModelColumn<unsigned int> m_col_id;
    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
    Gtk::TreeModelColumn<bool> m_col_something;
  };

  ModelColumns m_Columns;

  //These are the types of the model that will be shown.
  //The values will be generated dynamically, based on values in the child model.
  //
  //Remember, if you just want to hide some columns, then you should just not add them to the view,
  //and if you just want to change how some columns are displayed then use set_cell_data_func().
  class ModelColumnsDisplay : public Gtk::TreeModel::ColumnRecord
  {
  public:

    ModelColumnsDisplay()
    { add(m_col_name_uppercase); add(m_col_something_text); }

    Gtk::TreeModelColumn<Glib::ustring> m_col_name_uppercase;
    Gtk::TreeModelColumn<Glib::ustring> m_col_something_text;
  };

  ModelColumnsDisplay m_ColumnsDisplay;

  //Child widgets:
  Gtk::Box m_VBox;

  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::TreeView m_TreeView;
  Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
  Glib::RefPtr<Gtk::TreeModelFilter> m_refTreeModelFilter;

  Gtk::Box m_ButtonBox;
  Gtk::Button m_Button_Quit;
};

#endif //GTKMM_EXAMPLEWINDOW_H
