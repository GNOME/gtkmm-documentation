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
#include <array>
#include <iostream>

namespace
{
struct PositionTypeStruct
{
  Gtk::PositionType position;
  Glib::ustring text;
};

const std::array<PositionTypeStruct, 4> positionTypes =
{
  PositionTypeStruct{Gtk::PositionType::TOP,    "Top"},
  PositionTypeStruct{Gtk::PositionType::BOTTOM, "Bottom"},
  PositionTypeStruct{Gtk::PositionType::LEFT,   "Left"},
  PositionTypeStruct{Gtk::PositionType::RIGHT,  "Right"}
};

} // anonymous namespace


ExampleWindow::ExampleWindow()
:
  m_VBox_Top(Gtk::Orientation::VERTICAL, 0),
  m_VBox2(Gtk::Orientation::VERTICAL, 20),
  m_VBox_HScale(Gtk::Orientation::VERTICAL, 10),
  m_HBox_Scales(Gtk::Orientation::HORIZONTAL, 10),
  m_HBox_DropDown(Gtk::Orientation::HORIZONTAL, 10),
  m_HBox_Digits(Gtk::Orientation::HORIZONTAL, 10),
  m_HBox_PageSize(Gtk::Orientation::HORIZONTAL, 10),

  // Value, lower, upper, step_increment, page_increment, page_size:
  // Note that the page_size value only makes a difference for
  // scrollbar widgets, and the highest value you'll get is actually
  // (upper - page_size).
  m_adjustment( Gtk::Adjustment::create(0.0, 0.0, 101.0, 0.1, 1.0, 1.0) ),
  m_adjustment_digits( Gtk::Adjustment::create(1.0, 0.0, 5.0, 1.0, 2.0) ),
  m_adjustment_pagesize( Gtk::Adjustment::create(1.0, 1.0, 101.0) ),

  m_VScale(m_adjustment, Gtk::Orientation::VERTICAL),
  m_HScale(m_adjustment, Gtk::Orientation::HORIZONTAL),
  m_Scale_Digits(m_adjustment_digits),
  m_Scale_PageSize(m_adjustment_pagesize),

  // A checkbutton to control whether the value is displayed or not:
  m_CheckButton("Display value on scale widgets", 0),

  // Reuse the same adjustment again.
  // Notice how this causes the scales to always be updated
  // continuously when the scrollbar is moved.
  m_Scrollbar(m_adjustment),

  m_Button_Quit("Quit")
{
  set_title("range controls");
  set_default_size(300, 350);

  //VScale:
  m_VScale.set_digits(1);
  m_VScale.set_value_pos(Gtk::PositionType::TOP);
  m_VScale.set_draw_value();
  m_VScale.set_inverted(); // highest value at top

  //HScale:
  m_HScale.set_digits(1);
  m_HScale.set_value_pos(Gtk::PositionType::TOP);
  m_HScale.set_draw_value();

  set_child(m_VBox_Top);
  m_VBox_Top.append(m_VBox2);
  m_VBox2.set_expand(true);
  m_VBox2.set_margin(10);
  m_VBox2.append(m_HBox_Scales);
  m_HBox_Scales.set_expand(true);

  //Put VScale and HScale (above scrollbar) side-by-side.
  m_HBox_Scales.append(m_VScale);
  m_VScale.set_expand(true);
  m_HBox_Scales.append(m_VBox_HScale);
  m_VBox_HScale.set_expand(true);

  m_VBox_HScale.append(m_HScale);
  m_HScale.set_expand(true);

  //Scrollbar:
  m_VBox_HScale.append(m_Scrollbar);
  m_Scrollbar.set_expand(true);

  //CheckButton:
  m_CheckButton.set_active();
  m_CheckButton.signal_toggled().connect( sigc::mem_fun(*this,
    &ExampleWindow::on_checkbutton_toggled) );
  m_VBox2.append(m_CheckButton);

  //Position DropDown:
  //Create the StringList:
  auto string_list = Gtk::StringList::create({});
  m_DropDown_Position.set_model(string_list);

  // Fill the DropDown's list model:
  for (const auto& positionType : positionTypes)
    string_list->append(positionType.text);

  m_VBox2.append(m_HBox_DropDown);
  m_HBox_DropDown.append(*Gtk::make_managed<Gtk::Label>("Scale Value Position:", 0));
  m_HBox_DropDown.append(m_DropDown_Position);
  m_DropDown_Position.property_selected().signal_changed().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_dropdown_position));
  m_DropDown_Position.set_selected(0); // Top
  m_DropDown_Position.set_expand(true);

  //Digits:
  m_HBox_Digits.append(*Gtk::make_managed<Gtk::Label>("Scale Digits:", 0));
  m_Scale_Digits.set_digits(0);
  m_Scale_Digits.set_expand(true);
  m_adjustment_digits->signal_value_changed().connect(sigc::mem_fun(*this,
    &ExampleWindow::on_adjustment1_value_changed));
  m_HBox_Digits.append(m_Scale_Digits);

  //Page Size:
  m_HBox_PageSize.append(*Gtk::make_managed<Gtk::Label>("Scrollbar Page Size:", 0));
  m_Scale_PageSize.set_digits(0);
  m_Scale_PageSize.set_expand(true);
  m_adjustment_pagesize->signal_value_changed().connect(sigc::mem_fun(*this,
    &ExampleWindow::on_adjustment2_value_changed));
  m_HBox_PageSize.append(m_Scale_PageSize);

  m_VBox2.append(m_HBox_Digits);
  m_VBox2.append(m_HBox_PageSize);
  m_VBox_Top.append(m_Separator);
  m_VBox_Top.append(m_Button_Quit);

  set_default_widget(m_Button_Quit);
  m_Button_Quit.signal_clicked().connect(sigc::mem_fun(*this,
    &ExampleWindow::on_button_quit));
  m_Button_Quit.set_margin(10);
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_checkbutton_toggled()
{
  m_VScale.set_draw_value(m_CheckButton.get_active());
  m_HScale.set_draw_value(m_CheckButton.get_active());
}

void ExampleWindow::on_dropdown_position()
{
  const auto selected = m_DropDown_Position.get_selected();
  if (selected == GTK_INVALID_LIST_POSITION)
    return;

  const auto postype = positionTypes[selected].position;
  m_VScale.set_value_pos(postype);
  m_HScale.set_value_pos(postype);
}

void ExampleWindow::on_adjustment1_value_changed()
{
  const double val = m_adjustment_digits->get_value();
  m_VScale.set_digits((int)val);
  m_HScale.set_digits((int)val);
}

void ExampleWindow::on_adjustment2_value_changed()
{
  const double val = m_adjustment_pagesize->get_value();
  m_adjustment->set_page_size(val);
  m_adjustment->set_page_increment(val);

  // Note that we don't have to emit the "changed" signal
  // because gtkmm does this for us.
}

void ExampleWindow::on_button_quit()
{
  set_visible(false);
}
