/* gtkmm example Copyright (C) 2020 gtkmm development team
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
#include "exampletreemodel.h"

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  virtual ~ExampleWindow();

protected:
  // Signal handlers:
  void on_realize() override;
  void on_button_add();
  void on_button_remove();
  void on_button_quit();

  void fill_memory(int n_top_level_rows);

  // Child widgets:
  Gtk::Box m_VBox;
  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::Label m_Label;
  Gtk::TreeView m_TreeView;
  Gtk::Box m_ButtonBox;
  Gtk::Button m_Button_Add;
  Gtk::Button m_Button_Remove;
  Gtk::Button m_Button_Quit;

  MemoryColumns m_Columns;
  Glib::RefPtr<MemoryTreeModel> m_refTreeModel;

  Memory m_Memory;
};

#endif // GTKMM_EXAMPLEWINDOW_H
