/* gtkmm example Copyright (C) 2009 gtkmm development team
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
: m_VBox(Gtk::Orientation::VERTICAL, 6),
  m_Button_Quit("_Quit", true),
  m_Button_Clear("_Clear", true)
{
  set_title("Gtk::InfoBar example");
  set_default_size(400, 200);

  m_VBox.set_margin(6);
  set_child(m_VBox);

  // Add the message label to the InfoBar:
  m_InfoBar.add_child(m_Message_Label);

  // Add an ok button to the InfoBar:
  m_InfoBar.add_button("_OK", 0);

  // Add the InfoBar to the vbox:
  m_VBox.append(m_InfoBar);

  // Create the buffer and set it for the TextView:
  m_refTextBuffer = Gtk::TextBuffer::create();
  m_TextView.set_buffer(m_refTextBuffer);

  // Add the TreeView, inside a ScrolledWindow:
  m_ScrolledWindow.set_child(m_TextView);

  // Show the scrollbars only when they are necessary:
  m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_ScrolledWindow.set_expand();

  m_VBox.append(m_ScrolledWindow);

  // Add button box:
  m_VBox.append(m_ButtonBox);

  m_ButtonBox.append(m_Button_Clear);
  m_ButtonBox.append(m_Button_Quit);
  m_ButtonBox.set_spacing(6);
  m_Button_Clear.set_hexpand(true);
  m_Button_Clear.set_halign(Gtk::Align::END);

  // Connect signals:
  m_InfoBar.signal_response().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_infobar_response) );
  m_Button_Quit.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_quit) );
  m_Button_Clear.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_clear) );
  m_refTextBuffer->signal_changed().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_textbuffer_changed) );

  // Keep the InfoBar hidden until a message needs to be shown:
  m_InfoBar.hide();

  // Make the clear button insensitive until text is typed in the buffer.  When
  // the button is sensitive and it is pressed, the InfoBar is displayed with a
  // message.
  m_Button_Clear.set_sensitive(false);
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_infobar_response(int)
{
  // Clear the message and hide the info bar:
  m_Message_Label.set_text("");
  m_InfoBar.hide();
}

void ExampleWindow::on_button_quit()
{
  hide();
}

void ExampleWindow::on_button_clear()
{
  m_refTextBuffer->set_text("");
  m_Message_Label.set_text("Cleared the text.");
  m_InfoBar.set_message_type(Gtk::MessageType::INFO);
  m_InfoBar.show();
}

void ExampleWindow::on_textbuffer_changed()
{
  m_Button_Clear.set_sensitive(m_refTextBuffer->size() > 0);
}
