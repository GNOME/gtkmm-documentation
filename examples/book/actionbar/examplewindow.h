/* gtkmm example Copyright (C) 2013 gtkmm development team
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
  // Slots

  // Widgets
  Gtk::Image m_face_image;
  Gtk::ActionBar m_action_bar;
  Gtk::ToggleButton m_gallery_button;
  Gtk::Button m_prev_button;
  Gtk::Button m_next_button;
  Gtk::Button m_photo_button;
  Gtk::ToggleButton m_effects_button;

  // Containers
  Gtk::Box m_box;
  Gtk::Box m_photo_box;

private:
};

#endif // GTKMM_EXAMPLEWINDOW_H
