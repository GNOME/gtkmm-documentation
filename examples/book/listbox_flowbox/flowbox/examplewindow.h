/* gtkmm example Copyright (C) 2014 gtkmm development team
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

#include <vector>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  virtual ~ExampleWindow();

protected:
  // Draw function
  void on_drawing_area_draw(const Cairo::RefPtr<Cairo::Context>& cr,
    int width, int height, int swatch_i);

  // Containers
  Gtk::ScrolledWindow m_scrolled_window;
  Gtk::FlowBox m_flow_box;

private:
  void fill_color_names();
  Gtk::Button* create_color_swatch(int swatch_i);

  std::vector<Glib::ustring> m_color_names;
};

#endif // GTKMM_EXAMPLEWINDOW_H
