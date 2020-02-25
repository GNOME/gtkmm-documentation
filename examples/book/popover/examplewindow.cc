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
 : m_format_buttons_box(Gtk::Orientation::HORIZONTAL),
   m_toggle_button("Button"),
   m_toggle_form_popover(m_toggle_button),
   m_toggle_form_label("Non-modal Popover"),
   m_toggle_form_combo_label("Popover position:"),
   m_calendar_popover(m_calendar),
   m_calendar_popover_label("Label:")
{
  // Window properties
  set_title("Popover Example");
  set_default_size(500, -1);

  // Button
  m_toggle_button.signal_toggled().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_toggled));

  // Form popover
  configure_form_popover();

  // Calendar
  m_calendar.set_expand();

  // Calendar popover
  configure_cal_popover();

  // Layout
  m_grid.set_row_spacing(6);
  m_grid.attach(m_toggle_button, 0, 0, 1, 1);
  m_grid.attach(m_calendar, 0, 1, 6, 1);
  m_grid.set_margin(12);
  add(m_grid);
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_toggled()
{
  bool active = m_toggle_button.get_active();
  m_toggle_form_popover.set_visible(active);
}

void ExampleWindow::configure_form_popover()
{
  configure_form_buttons();
  configure_form_combo();

  m_toggle_form_grid.set_row_spacing(6);
  m_toggle_form_grid.set_column_spacing(6);
  m_toggle_form_grid.attach(m_toggle_form_label, 0, 0, 2, 1);
  m_toggle_form_grid.attach(m_format_buttons_box, 0, 1, 2, 1);
  m_toggle_form_grid.attach(m_toggle_form_combo_label, 0, 2, 1, 1);
  m_toggle_form_grid.attach(m_toggle_form_combo, 1, 2, 1, 1);

  m_toggle_form_popover.add(m_toggle_form_grid);
  m_toggle_form_popover.set_position(Gtk::PositionType::BOTTOM);
  m_toggle_form_popover.set_margin(6);
  m_toggle_form_popover.set_autohide(false);
}

void ExampleWindow::configure_form_buttons()
{
  m_toggle_form_buttons[0].set_image_from_icon_name("format-justify-left-symbolic", Gtk::IconSize::INHERIT, true);
  m_toggle_form_buttons[1].set_image_from_icon_name("format-justify-center-symbolic", Gtk::IconSize::INHERIT, true);
  m_toggle_form_buttons[2].set_image_from_icon_name("format-justify-right-symbolic", Gtk::IconSize::INHERIT, true);

  m_toggle_form_buttons[1].join_group(m_toggle_form_buttons[0]);
  m_toggle_form_buttons[2].join_group(m_toggle_form_buttons[0]);

  for (auto& button : m_toggle_form_buttons)
  {
    button.set_draw_indicator(false);
    button.set_expand(true);
    m_format_buttons_box.add(button);
  }

  // Group format buttons so that they appear that they belong together
  auto style_context = m_format_buttons_box.get_style_context();
  style_context->add_class("raised");
  style_context->add_class("linked");
}

void ExampleWindow::configure_form_combo()
{
  m_toggle_form_combo.append("Bottom");
  m_toggle_form_combo.append("Right");

  m_toggle_form_combo.set_active(0);

  m_toggle_form_combo.signal_changed().connect(sigc::mem_fun(*this, &ExampleWindow::on_combo_changed));
}

void ExampleWindow::on_combo_changed()
{
  int active_entry = m_toggle_form_combo.get_active_row_number();

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
  m_calendar.signal_day_selected().connect(sigc::mem_fun(*this, &ExampleWindow::on_day_selected));

  m_calendar_form_grid.set_column_spacing(6);
  m_calendar_form_grid.attach(m_calendar_popover_label, 0, 0, 1, 1);
  m_calendar_form_grid.attach(m_calendar_popover_entry, 1, 0, 1, 1);

  m_calendar_popover.add(m_calendar_form_grid);
  m_calendar_popover.set_margin(6);
}

void ExampleWindow::on_day_selected()
{
  const auto current_event = Glib::wrap(gtk_get_current_event(), false);

  if (current_event->get_event_type() != Gdk::Event::Type::BUTTON_PRESS)
    return;

  double x = 0.0;
  double y = 0.0;
  current_event->get_position(x, y);
  Gdk::Rectangle rect;
  auto allocation = m_calendar.get_allocation();
  rect.set_x(x - allocation.get_x());
  rect.set_y(y - allocation.get_y());
  rect.set_width(1);
  rect.set_height(1);

  m_calendar_popover.set_pointing_to(rect);
  m_calendar_popover.set_visible(true);

  m_calendar_popover_entry.set_text("");
}

