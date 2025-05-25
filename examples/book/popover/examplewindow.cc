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

#include "examplewindow.h"

ExampleWindow::ExampleWindow()
 : m_format_buttons_box(Gtk::Orientation::HORIZONTAL),
   m_menu_button(),
   m_toggle_form_label("Non-modal Popover"),
   m_toggle_form_drop_down_label("Popover position:"),
   m_calendar_popover_label("Label:")
{
  // Window properties
  set_title("Popover Example");
  set_default_size(500, -1);

  // Button
  m_menu_button.set_label("Button");
  m_menu_button.set_popover(m_toggle_form_popover);

  // Form popover
  configure_form_popover();

  // Calendar
  m_calendar.set_expand();

  // Calendar popover
  configure_cal_popover();

  // Layout
  m_grid.set_row_spacing(6);
  m_grid.attach(m_menu_button, 0, 0, 1, 1);
  m_grid.attach(m_calendar, 0, 1, 6, 1);
  m_grid.set_margin(12);
  set_child(m_grid);
}

ExampleWindow::~ExampleWindow()
{
  m_calendar_popover.unparent();
}

void ExampleWindow::configure_form_popover()
{
  configure_form_buttons();
  configure_form_drop_down();

  m_toggle_form_grid.set_row_spacing(6);
  m_toggle_form_grid.set_column_spacing(6);
  m_toggle_form_grid.attach(m_toggle_form_label, 0, 0, 2, 1);
  m_toggle_form_grid.attach(m_format_buttons_box, 0, 1, 2, 1);
  m_toggle_form_grid.attach(m_toggle_form_drop_down_label, 0, 2, 1, 1);
  m_toggle_form_grid.attach(m_toggle_form_drop_down, 1, 2, 1, 1);

  m_toggle_form_popover.set_child(m_toggle_form_grid);
  m_toggle_form_popover.set_position(Gtk::PositionType::BOTTOM);
  m_toggle_form_popover.set_margin(6);
  m_toggle_form_popover.set_autohide(false);
}

void ExampleWindow::configure_form_buttons()
{
  m_toggle_form_buttons[0].set_image_from_icon_name("format-justify-left-symbolic", Gtk::IconSize::INHERIT, true);
  m_toggle_form_buttons[1].set_image_from_icon_name("format-justify-center-symbolic", Gtk::IconSize::INHERIT, true);
  m_toggle_form_buttons[2].set_image_from_icon_name("format-justify-right-symbolic", Gtk::IconSize::INHERIT, true);

  m_toggle_form_buttons[0].set_active();
  m_toggle_form_buttons[1].set_group(m_toggle_form_buttons[0]);
  m_toggle_form_buttons[2].set_group(m_toggle_form_buttons[0]);

  for (auto& button : m_toggle_form_buttons)
  {
    button.set_expand(true);
    m_format_buttons_box.append(button);
  }

  // Group format buttons so that they appear that they belong together
  m_format_buttons_box.add_css_class("raised");
  m_format_buttons_box.add_css_class("linked");
}

void ExampleWindow::configure_form_drop_down()
{
  const std::vector<Glib::ustring> strings{"Bottom", "Right"};
  m_toggle_form_drop_down.set_model(Gtk::StringList::create(strings));

  m_toggle_form_drop_down.set_selected(0);

  m_toggle_form_drop_down.property_selected().signal_changed().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_drop_down_changed));
}

void ExampleWindow::on_drop_down_changed()
{
  const auto active_entry = m_toggle_form_drop_down.get_selected();

  if (active_entry == 0)
  {
    m_toggle_form_popover.set_position(Gtk::PositionType::BOTTOM);
  }
  else if (active_entry == 1)
  {
    m_toggle_form_popover.set_position(Gtk::PositionType::RIGHT);
  }
}

void ExampleWindow::configure_cal_popover()
{
  m_calendar_event_controller = Gtk::GestureClick::create();
  m_calendar_event_controller->signal_pressed().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_pressed));
  m_calendar_event_controller->signal_released().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_released));
  m_calendar.add_controller(m_calendar_event_controller);

  m_calendar.signal_day_selected().connect(sigc::mem_fun(*this, &ExampleWindow::on_day_selected));

  m_calendar_form_grid.set_column_spacing(6);
  m_calendar_form_grid.attach(m_calendar_popover_label, 0, 0);
  m_calendar_form_grid.attach(m_calendar_popover_entry, 1, 0);

  m_calendar_popover.set_parent(m_calendar);
  m_calendar_popover.set_child(m_calendar_form_grid);
  m_calendar_popover.set_margin(6);
}

void ExampleWindow::on_day_selected()
{
  if (m_button_pressed_called)
  {
    // on_button_pressed() was called before on_day_selected().
    show_calendar_popover(m_button_pressed_x, m_button_pressed_y);
    m_button_pressed_called = false;
  }
  else
  {
    m_day_selected_called = true;
  }
}

void ExampleWindow::on_button_pressed(int, double x, double y)
{
  if (m_day_selected_called)
  {
    // on_day_selected() was called before on_button_pressed().
    show_calendar_popover(x, y);
    m_day_selected_called = false;
  }
  else
  {
    m_button_pressed_x = x;
    m_button_pressed_y = y;
    m_button_pressed_called = true;
  }
}

void ExampleWindow::on_button_released(int, double, double)
{
  m_button_pressed_called = false;
}

void ExampleWindow::show_calendar_popover(double x, double y)
{
  const Gdk::Rectangle rect(x, y, 1, 1);
  m_calendar_popover.set_pointing_to(rect);
  m_calendar_popover.set_visible(true);

  m_calendar_popover_entry.set_text("");
}
