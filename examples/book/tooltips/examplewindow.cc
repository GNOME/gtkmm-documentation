/* gtkmm example Copyright (C) 2007 gtkmm development team
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
#include <vector>

const Glib::ustring app_title = "gtkmm tooltips example";
const Glib::ustring non_markedup_tip = "A tooltip without markup.";
const Glib::ustring markedup_tip = "<i>Markup</i> in a tooltip.";

ExampleWindow::ExampleWindow()
  :
  m_vbox(Gtk::Orientation::VERTICAL, 3),
  m_checkbutton("Click to alternate markup in tooltip"),
  m_label("A label"),
  m_button("Button with a custom tooltip widget")
{
  //Set up window and the top-level container:
  set_title(app_title);

  m_vbox.set_margin(10);
  set_child(m_vbox);

  //Check button with markup in tooltip:
  m_checkbutton.set_tooltip_text(non_markedup_tip);
  m_vbox.append(m_checkbutton);

  //Label:
  m_label.set_tooltip_text("Another tooltip");
  m_vbox.append(m_label);

  //Textview:
  prepare_textview();

  //Button:
  //When only connecting to the query-tooltip signal, and not using any
  //of set_tooltip_text() or set_tooltip_markup(), we need to explicitly
  //tell GTK that the widget has a tooltip which we'll show.
  m_button.set_has_tooltip();
  m_vbox.append(m_button);

  //Button's custom tooltip widget:
  auto label = Gtk::make_managed<Gtk::Label>("A label in a custom tooltip widget");
  m_button_tooltip_widget.append(*label);

  connect_signals();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::prepare_textview()
{
  Gtk::TextIter iter;
  std::vector<Glib::RefPtr<Gtk::TextTag>> tags;

  //Set up a scrolled window:
  m_scrolled_window.set_child(m_text_view);
  m_scrolled_window.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_scrolled_window.set_expand();
  m_vbox.append(m_scrolled_window);

  //Create a text buffer with some text:
  m_ref_text_buffer = Gtk::TextBuffer::create();

  iter = m_ref_text_buffer->end();
  m_ref_text_buffer->insert(iter, "Hover over the text ");

  //Insert some text with a tag.
  //In the tooltip signal handler below, we will show a tooltip
  //when mouse pointer is above this tagged text.
  m_ref_bold_tag = m_ref_text_buffer->create_tag("bold");
  m_ref_bold_tag->set_property("weight", Pango::Weight::BOLD);

  tags.push_back(m_ref_bold_tag);

  iter = m_ref_text_buffer->end();
  m_ref_text_buffer->insert_with_tags(iter, "in bold", tags);

  iter = m_ref_text_buffer->end();
  m_ref_text_buffer->insert(iter, " to see its tooltip");

  m_text_view.set_buffer(m_ref_text_buffer);

  m_text_view.set_size_request(320, 50);

  //When only connecting to the query-tooltip signal, and not using any
  //of set_tooltip_text() or set_tooltip_markup(), we need to explicitly
  //tell GTK that the widget has a tooltip which we'll show.
  m_text_view.set_has_tooltip();
}

void ExampleWindow::connect_signals()
{
  m_checkbutton.signal_toggled().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_markup_checkbutton_toggled));

  m_text_view.signal_query_tooltip().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_textview_query_tooltip), true);

  m_button.signal_query_tooltip().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_button_query_tooltip), true);
}

void ExampleWindow::on_markup_checkbutton_toggled()
{
  if (m_checkbutton.get_active())
  {
    m_checkbutton.set_tooltip_markup(markedup_tip);
  }
  else
  {
    m_checkbutton.set_tooltip_markup(non_markedup_tip);
  }
}

bool ExampleWindow::on_textview_query_tooltip(int x, int y, bool keyboard_tooltip, const Glib::RefPtr<Gtk::Tooltip>& tooltip)
{
  Gtk::TextIter iter;

  if (keyboard_tooltip)
  {
    int offset = m_ref_text_buffer->property_cursor_position().get_value();
    iter = m_ref_text_buffer->get_iter_at_offset(offset);
  }
  else
  {
    int mouse_x, mouse_y, trailing;
    m_text_view.window_to_buffer_coords(Gtk::TextWindowType::TEXT,
                                        x, y, mouse_x, mouse_y);
    m_text_view.get_iter_at_position(iter, trailing, mouse_x, mouse_y);
  }

  if (!iter.has_tag(m_ref_bold_tag))
    return false;

  //Show a tooltip if the cursor or mouse pointer is over the text
  //with the specific tag:
  tooltip->set_markup("<b>Information</b> attached to a text tag");
  tooltip->set_icon("dialog-information");
  return true;
}

bool ExampleWindow::on_button_query_tooltip(int, int, bool, const Glib::RefPtr<Gtk::Tooltip>& tooltip)
{
  tooltip->set_custom(m_button_tooltip_widget);
  return true;
}
