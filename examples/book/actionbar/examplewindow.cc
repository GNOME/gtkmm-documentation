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

#include "examplewindow.h"

ExampleWindow::ExampleWindow()
: m_gallery_button("Gallery"),
  m_effects_button("Effects"),
  m_box(Gtk::Orientation::VERTICAL),
  m_photo_box(Gtk::Orientation::HORIZONTAL)
{
  // Window properties
  set_title("ActionBar Example");
  set_default_size(600, 400);

  // Prefer dark theme
  auto settings = Gtk::Settings::get_default();
  settings->property_gtk_application_prefer_dark_theme().set_value(true);

  // Face
  m_face_image.set_from_icon_name("face-cool");
  m_face_image.set_icon_size(Gtk::IconSize::LARGE);

  // Center widget layout
  m_prev_button.set_image_from_icon_name("go-previous-symbolic", Gtk::IconSize::INHERIT, true);
  m_next_button.set_image_from_icon_name("go-next-symbolic", Gtk::IconSize::INHERIT, true);
  m_photo_button.set_image_from_icon_name("media-record-symbolic", Gtk::IconSize::INHERIT, true);
  m_photo_box.append(m_prev_button);
  m_photo_box.append(m_photo_button);
  m_photo_box.append(m_next_button);
  auto style_context = m_photo_box.get_style_context();
  style_context->add_class("raised");
  style_context->add_class("linked");

  // ActionBar layout
  m_action_bar.pack_start(m_gallery_button);
  m_action_bar.set_center_widget(m_photo_box);
  m_action_bar.pack_end(m_effects_button);

  // Layout
  m_box.set_homogeneous(false);
  m_face_image.set_expand();
  m_box.append(m_face_image);
  m_box.append(m_action_bar);
  set_child(m_box);
}

ExampleWindow::~ExampleWindow()
{
}
