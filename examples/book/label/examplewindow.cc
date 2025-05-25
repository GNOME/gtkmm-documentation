/* gtkmm example Copyright (C) 2002 gtkmm development team
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

ExampleWindow::ExampleWindow()
:
  m_HBox(Gtk::Orientation::HORIZONTAL, 5),
  m_VBox(Gtk::Orientation::VERTICAL, 5),
  m_VBox2(Gtk::Orientation::VERTICAL, 5),
  m_Frame_Normal("Normal Label"),
  m_Frame_Multi("Multi-line Label"),
  m_Frame_Left("Left Justified Label"),
  m_Frame_Right("Right Justified Label"),
  m_Frame_LineWrapped("Line wrapped label"),
  m_Frame_FilledWrapped("Filled, wrapped label"),
  m_Frame_Underlined("Underlined label"),
  m_Label_Normal("_This is a Normal label", true),
  m_Label_Multi("This is a Multi-line label.\nSecond line\nThird line"),
  m_Label_Left("This is a Left-Justified\nMulti-line label.\nThird line"),
  m_Label_Right("This is a Right-Justified\nMulti-line label.\nThird line"),
  m_Label_Underlined("<u>This label is underlined!</u>\n"
          "<u>T</u>h<u>is one is</u> <u>u</u>n<u>derlin</u>ed "
          "in<u> q</u>u<u>ite a f</u>u<u>nky</u> fashion")
{
  set_title("Label");

  m_HBox.set_margin(5);
  set_child(m_HBox);

  m_HBox.append(m_VBox);

  m_Frame_Normal.set_child(m_Label_Normal);
  m_VBox.append(m_Frame_Normal);

  m_Frame_Multi.set_child(m_Label_Multi);
  m_VBox.append(m_Frame_Multi);

  m_Label_Left.set_justify(Gtk::Justification::LEFT);
  m_Frame_Left.set_child(m_Label_Left);
  m_VBox.append(m_Frame_Left);

  m_Label_Right.set_justify(Gtk::Justification::RIGHT);
  m_Frame_Right.set_child(m_Label_Right);
  m_VBox.append(m_Frame_Right);

  m_HBox.append(m_VBox2);

  m_Label_LineWrapped.set_text(
          "This is an example of a line-wrapped label.  It "
          /* add a big space to the next line to test spacing */
          "should not be taking up the entire             "
          "width allocated to it, but automatically "
          "wraps the words to fit.  "
          "The time has come, for all good men, to come to "
          "the aid of their party.  "
          "The sixth sheik's six sheep's sick.\n"
          "     It supports multiple paragraphs correctly, "
          "and  correctly   adds "
          "many          extra  spaces. ");
  m_Label_LineWrapped.set_wrap();
  m_Frame_LineWrapped.set_child(m_Label_LineWrapped);
  m_VBox2.append(m_Frame_LineWrapped);

  m_Label_FilledWrapped.set_text(
          "This is an example of a line-wrapped, filled label.  "
          "It should be taking "
          "up the entire              width allocated to it.  "
          "Here is a sentence to prove "
          "my point.  Here is another sentence. "
          "Here comes the sun, do de do de do.\n"
          "    This is a new paragraph.\n"
          "    This is another newer, longer, better "
          "paragraph.  It is coming to an end, "
          "unfortunately.");
  m_Label_FilledWrapped.set_justify(Gtk::Justification::FILL);
  m_Label_FilledWrapped.set_wrap();
  m_Frame_FilledWrapped.set_child(m_Label_FilledWrapped);
  m_VBox2.append(m_Frame_FilledWrapped);

  m_Label_Underlined.set_justify(Gtk::Justification::LEFT);
  m_Label_Underlined.set_use_markup(true);
  m_Frame_Underlined.set_child(m_Label_Underlined);
  m_VBox2.append(m_Frame_Underlined);
}

ExampleWindow::~ExampleWindow()
{
}
