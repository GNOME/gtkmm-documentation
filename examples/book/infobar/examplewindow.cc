/* gtkmm example Copyright (C) 2009 gtkmm development team
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
#include <iostream>

// The Gtk::InfoBar widget is deprecated since gtk/gtkmm 4.10.
// A Box with a Label and Button is often a good replacement.
// If you don't care about its background color, it's even easier
// than the InfoBar replacement in this example program.

ExampleWindow::ExampleWindow()
: m_VBox(Gtk::Orientation::VERTICAL, 6),
  m_InfoBar(Gtk::Orientation::HORIZONTAL, 6),
  m_Button_OK("_OK", true),
  m_ButtonBox(Gtk::Orientation::HORIZONTAL, 6),
  m_Button_Quit("_Quit", true),
  m_Button_Clear("_Clear", true)
{
  set_title("Infobar example");
  set_default_size(400, 200);

  m_VBox.set_margin(6);
  set_child(m_VBox);

  // Add the message label to the InfoBar:
  m_InfoBar.append(m_Message_Label);
  m_Message_Label.set_margin_start(5);
  m_Message_Label.set_hexpand(true);
  m_Message_Label.set_halign(Gtk::Align::START);

  // Add an ok button to the InfoBar:
  m_InfoBar.append(m_Button_OK);
  m_Button_OK.set_margin(5);

  // Add the InfoBar to the vbox:
  m_VBox.append(m_InfoBar);

  // Create the buffer and set it for the TextView:
  m_refTextBuffer = Gtk::TextBuffer::create();
  m_TextView.set_buffer(m_refTextBuffer);

  // Add the TextView, inside a ScrolledWindow:
  m_ScrolledWindow.set_child(m_TextView);

  // Show the scrollbars only when they are necessary:
  m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_ScrolledWindow.set_expand();

  m_VBox.append(m_ScrolledWindow);

  // Add button box:
  m_VBox.append(m_ButtonBox);

  m_ButtonBox.append(m_Button_Clear);
  m_ButtonBox.append(m_Button_Quit);
  m_Button_Clear.set_hexpand(true);
  m_Button_Clear.set_halign(Gtk::Align::END);

  // Connect signals:
  m_Button_OK.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_infobar_ok) );
  m_Button_Quit.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_quit) );
  m_Button_Clear.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_clear) );
  m_refTextBuffer->signal_changed().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_textbuffer_changed) );

  // Keep the InfoBar hidden until a message needs to be shown:
  m_InfoBar.set_visible(false);
  set_infobar_background();

  // Make the clear button insensitive until text is typed in the buffer.  When
  // the button is sensitive and it is pressed, the InfoBar is displayed with a
  // message.
  m_Button_Clear.set_sensitive(false);
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_infobar_ok()
{
  // Clear the message and hide the info bar:
  m_Message_Label.set_text("");
  m_InfoBar.set_visible(false);
}

void ExampleWindow::on_button_quit()
{
  set_visible(false);
}

void ExampleWindow::on_button_clear()
{
  m_refTextBuffer->set_text("");
  m_Message_Label.set_text("Cleared the text.");
  m_InfoBar.set_visible(true);
}

void ExampleWindow::on_textbuffer_changed()
{
  m_Button_Clear.set_sensitive(m_refTextBuffer->size() > 0);
}

void ExampleWindow::set_infobar_background()
{
  // Concerning color in CSS files, see https://www.w3.org/TR/css-color-3.
  const std::string css = "#infobarbox { background-color: beige; }";

  m_InfoBar.set_name("infobarbox");
  auto css_provider = Gtk::CssProvider::create();
  Gtk::StyleProvider::add_provider_for_display(
    m_InfoBar.get_display(), css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  css_provider->load_from_data(css);
  css_provider->signal_parsing_error().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_parsing_error));
}

void ExampleWindow::on_parsing_error(const Glib::RefPtr<const Gtk::CssSection>& section,
  const Glib::Error& error)
{
  std::cerr << "on_parsing_error(): " << error.what() << std::endl;
  if (section)
  {
    const auto file = section->get_file();
    if (file)
    {
      std::cerr << "  URI = " << file->get_uri() << std::endl;
    }

    auto start_location = section->get_start_location();
    auto end_location = section->get_end_location();
    std::cerr << "  start_line = " << start_location.get_lines()+1
              << ", end_line = " << end_location.get_lines()+1 << std::endl;
    std::cerr << "  start_position = " << start_location.get_line_chars()
              << ", end_position = " << end_location.get_line_chars() << std::endl;
  }
}
