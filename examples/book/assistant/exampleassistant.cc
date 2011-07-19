/* gtkmm example Copyright (C) 2010 Openismus GmbH
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
 * along with this program; if not, write to the Free Software Foundation,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <iostream>
#include "exampleassistant.h"

ExampleAssistant::ExampleAssistant()
: m_box(Gtk::ORIENTATION_HORIZONTAL, 12),
  m_label1("Type text to allow the assistant to continue:"),
  m_label2("Confirmation page"),
  m_check("Optional extra information")
{
  set_title("Gtk::Assistant example");
  set_border_width(12);
  set_default_size(400, 300);

  m_box.pack_start(m_label1);
  m_box.pack_start(m_entry);

  append_page(m_box);
  append_page(m_check);
  append_page(m_label2);

  set_page_title(*get_nth_page(0), "Page 1");
  set_page_title(*get_nth_page(1), "Page 2");
  set_page_title(*get_nth_page(2), "Confirmation");

  set_page_complete(m_check, true);
  set_page_complete(m_label2, true);

  set_page_type(m_box, Gtk::ASSISTANT_PAGE_INTRO);
  set_page_type(m_label2, Gtk::ASSISTANT_PAGE_CONFIRM);

  signal_apply().connect(sigc::mem_fun(*this,
    &ExampleAssistant::on_assistant_apply));
  signal_cancel().connect(sigc::mem_fun(*this,
    &ExampleAssistant::on_assistant_cancel));
  signal_close().connect(sigc::mem_fun(*this,
    &ExampleAssistant::on_assistant_close));
  signal_prepare().connect(sigc::mem_fun(*this,
    &ExampleAssistant::on_assistant_prepare));

  m_entry.signal_changed().connect(sigc::mem_fun(*this,
    &ExampleAssistant::on_entry_changed));

  show_all_children();
}

ExampleAssistant::~ExampleAssistant()
{
}

void ExampleAssistant::get_result(bool& check_state, Glib::ustring& entry_text)
{
  check_state = m_check.get_active();
  entry_text = m_entry.get_text();
}

void ExampleAssistant::on_assistant_apply()
{
  std::cout << "Apply was clicked";
  print_status();
}

void ExampleAssistant::on_assistant_cancel()
{
  std::cout << "Cancel was clicked";
  print_status();
  hide();
}

void ExampleAssistant::on_assistant_close()
{
  std::cout << "Assistant was closed";
  print_status();
  hide();
}

void ExampleAssistant::on_assistant_prepare(Gtk::Widget* /* widget */)
{
  set_title(Glib::ustring::compose("Gtk::Assistant example (Page %1 of %2)",
    get_current_page() + 1, get_n_pages()));
}

void ExampleAssistant::on_entry_changed()
{
  // The page is only complete if the entry contains text.
  if(m_entry.get_text_length())
    set_page_complete(m_box, true);
  else
    set_page_complete(m_box, false);
}

void ExampleAssistant::print_status()
{
  std::cout << ", entry contents: \"" << m_entry.get_text()
    << "\", checkbutton status: " << m_check.get_active() << std::endl;
}
