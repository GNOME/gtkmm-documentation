/* gtkmm example Copyright (C) 2014 gtkmm development team
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

#include <vector>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  virtual ~ExampleWindow();

protected:
  // Slots

  // Widgets
  std::vector<Gtk::Button*> m_color_swatches;
  std::vector<Gtk::DrawingArea*> m_color_drawing_areas;

  // Containers
  Gtk::ScrolledWindow m_scrolled_window;
  Gtk::FlowBox m_flow_box;

private:
  void fill_color_names();
  Gtk::Button* create_color_swatch(int swatch_i);

  std::vector<Glib::ustring> m_color_names;
};

#endif // GTKMM_EXAMPLEWINDOW_H
