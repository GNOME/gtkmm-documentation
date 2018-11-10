/* gtkmm example Copyright (C) 2002 gtkmm development team
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
#include <iostream>

ExampleWindow::ExampleWindow()
:
  m_VBox_Top(Gtk::Orientation::VERTICAL, 0),
  m_VBox2(Gtk::Orientation::VERTICAL, 20),
  m_VBox_HScale(Gtk::Orientation::VERTICAL, 10),
  m_HBox_Scales(Gtk::Orientation::HORIZONTAL, 10),
  m_HBox_Combo(Gtk::Orientation::HORIZONTAL, 10),
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

  add(m_VBox_Top);
  m_VBox_Top.pack_start(m_VBox2, Gtk::PackOptions::EXPAND_WIDGET);
  m_VBox2.set_margin(10);
  m_VBox2.pack_start(m_HBox_Scales, Gtk::PackOptions::EXPAND_WIDGET);

  //Put VScale and HScale (above scrollbar) side-by-side.
  m_HBox_Scales.pack_start(m_VScale, Gtk::PackOptions::EXPAND_WIDGET);
  m_HBox_Scales.pack_start(m_VBox_HScale, Gtk::PackOptions::EXPAND_WIDGET);

  m_VBox_HScale.pack_start(m_HScale, Gtk::PackOptions::EXPAND_WIDGET);

  //Scrollbar:
  m_VBox_HScale.pack_start(m_Scrollbar, Gtk::PackOptions::EXPAND_WIDGET);

  //CheckButton:
  m_CheckButton.set_active();
  m_CheckButton.signal_toggled().connect( sigc::mem_fun(*this,
    &ExampleWindow::on_checkbutton_toggled) );
  m_VBox2.pack_start(m_CheckButton, Gtk::PackOptions::SHRINK);

  //Position ComboBox:
  //Create the Tree model:
  m_refTreeModel = Gtk::ListStore::create(m_Columns);
  m_ComboBox_Position.set_model(m_refTreeModel);
  m_ComboBox_Position.pack_start(m_Columns.m_col_title);

  //Fill the ComboBox's Tree Model:
  auto row = *(m_refTreeModel->append());
  row[m_Columns.m_col_position_type] = Gtk::PositionType::TOP;
  row[m_Columns.m_col_title] = "Top";
  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_position_type] = Gtk::PositionType::BOTTOM;
  row[m_Columns.m_col_title] = "Bottom";
  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_position_type] = Gtk::PositionType::LEFT;
  row[m_Columns.m_col_title] = "Left";
  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_position_type] = Gtk::PositionType::RIGHT;
  row[m_Columns.m_col_title] = "Right";

  m_VBox2.pack_start(m_HBox_Combo, Gtk::PackOptions::SHRINK);
  m_HBox_Combo.pack_start(
    *Gtk::make_managed<Gtk::Label>("Scale Value Position:", 0), Gtk::PackOptions::SHRINK);
  m_HBox_Combo.pack_start(m_ComboBox_Position, Gtk::PackOptions::EXPAND_WIDGET);
  m_ComboBox_Position.signal_changed().connect( sigc::mem_fun(*this, &ExampleWindow::on_combo_position) );
  m_ComboBox_Position.set_active(0); // Top

  //Digits:
  m_HBox_Digits.pack_start(
    *Gtk::make_managed<Gtk::Label>("Scale Digits:", 0), Gtk::PackOptions::SHRINK);
  m_Scale_Digits.set_digits(0);
  m_adjustment_digits->signal_value_changed().connect(sigc::mem_fun(*this,
    &ExampleWindow::on_adjustment1_value_changed));
  m_HBox_Digits.pack_start(m_Scale_Digits, Gtk::PackOptions::EXPAND_WIDGET);

  //Page Size:
  m_HBox_PageSize.pack_start(
    *Gtk::make_managed<Gtk::Label>("Scrollbar Page Size:", 0), Gtk::PackOptions::SHRINK);
  m_Scale_PageSize.set_digits(0);
  m_adjustment_pagesize->signal_value_changed().connect(sigc::mem_fun(*this,
    &ExampleWindow::on_adjustment2_value_changed));
  m_HBox_PageSize.pack_start(m_Scale_PageSize, Gtk::PackOptions::EXPAND_WIDGET);

  m_VBox2.pack_start(m_HBox_Digits, Gtk::PackOptions::SHRINK);
  m_VBox2.pack_start(m_HBox_PageSize, Gtk::PackOptions::SHRINK);
  m_VBox_Top.pack_start(m_Separator, Gtk::PackOptions::SHRINK);
  m_VBox_Top.pack_start(m_Button_Quit, Gtk::PackOptions::SHRINK);

  m_Button_Quit.set_can_default();
  m_Button_Quit.grab_default();
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

void ExampleWindow::on_combo_position()
{
  const auto iter = m_ComboBox_Position.get_active();
  if(!iter)
    return;

  const auto row = *iter;
  if(!row)
    return;

  const auto postype = row[m_Columns.m_col_position_type];

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
  hide();
}
