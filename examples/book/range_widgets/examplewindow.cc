//$Id: examplewindow.cc 836 2007-05-09 03:02:38Z jjongsma $ -*- c++ -*-

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
  m_VBox2(false, 20),
  m_VBox_HScale(false, 10),
  m_HBox_Scales(false, 10),
  m_HBox_Digits(false, 10),
  m_HBox_PageSize(false, 10),

  // Value, lower, upper, step_increment, page_increment, page_size:
  // Note that the page_size value only makes a difference for
  // scrollbar widgets, and the highest value you'll get is actually
  // (upper - page_size).
  m_adjustment( Gtk::Adjustment::create(0.0, 0.0, 101.0, 0.1, 1.0, 1.0) ),
  m_adjustment_digits( Gtk::Adjustment::create(1.0, 0.0, 5.0) ),
  m_adjustment_pagesize( Gtk::Adjustment::create(1.0, 1.0, 101.0) ),

  m_VScale(m_adjustment),
  m_HScale(m_adjustment),
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

  //VScale:
  m_VScale.set_update_policy(Gtk::UPDATE_CONTINUOUS);
  m_VScale.set_digits(1);
  m_VScale.set_value_pos(Gtk::POS_TOP);
  m_VScale.set_draw_value();

  //HScale:
  m_HScale.set_update_policy(Gtk::UPDATE_CONTINUOUS);
  m_HScale.set_digits(1);
  m_HScale.set_value_pos(Gtk::POS_TOP);
  m_HScale.set_draw_value();
  m_HScale.set_size_request(200, 30);

  add(m_VBox_Top);
  m_VBox_Top.pack_start(m_VBox2);
  m_VBox2.set_border_width(10);
  m_VBox2.pack_start(m_HBox_Scales);

  //Put VScale and HScale (above scrollbar) side-by-side.
  m_HBox_Scales.pack_start(m_VScale);
  m_HBox_Scales.pack_start(m_VBox_HScale);

  m_VBox_HScale.pack_start(m_HScale);

  //Scrollbar:
  m_Scrollbar.set_update_policy(Gtk::UPDATE_CONTINUOUS);
  m_VBox_HScale.pack_start(m_Scrollbar);

  //CheckButton:
  m_CheckButton.set_active();
  m_CheckButton.signal_toggled().connect( sigc::mem_fun(*this,
    &ExampleWindow::on_checkbutton_toggled) );
  m_VBox2.pack_start(m_CheckButton);

  //Menus:
  Gtk::MenuItem* item = Gtk::manage(new Gtk::MenuItem("Top"));
  item->signal_activate().connect(
    sigc::bind(sigc::mem_fun(*this,
      &ExampleWindow::on_menu_position), Gtk::POS_TOP));
  m_Menu_Position.append(*item);

  item = Gtk::manage(new Gtk::MenuItem("Bottom"));
  item->signal_activate().connect(
    sigc::bind(sigc::mem_fun(*this,
      &ExampleWindow::on_menu_position), Gtk::POS_BOTTOM));
  m_Menu_Position.append(*item);

  item = Gtk::manage(new Gtk::MenuItem("Left"));
  item->signal_activate().connect(
    sigc::bind(sigc::mem_fun(*this,
      &ExampleWindow::on_menu_position), Gtk::POS_LEFT));
  m_Menu_Position.append(*item);

  item = Gtk::manage(new Gtk::MenuItem("Right"));
  item->signal_activate().connect(
    sigc::bind(sigc::mem_fun(*this,
      &ExampleWindow::on_menu_position), Gtk::POS_RIGHT));
  m_Menu_Position.append(*item);


  item = Gtk::manage(new Gtk::MenuItem("Continuous"));
  item->signal_activate().connect(
    sigc::bind(sigc::mem_fun(*this,
      &ExampleWindow::on_menu_policy), Gtk::UPDATE_CONTINUOUS));
  m_Menu_Policy.append(*item);

  item = Gtk::manage(new Gtk::MenuItem("Discontinuous"));
  item->signal_activate().connect(
    sigc::bind(sigc::mem_fun(*this,
      &ExampleWindow::on_menu_policy), Gtk::UPDATE_DISCONTINUOUS));
  m_Menu_Policy.append(*item);

  item = Gtk::manage(new Gtk::MenuItem("Delayed"));
  item->signal_activate().connect(
    sigc::bind(sigc::mem_fun(*this,
      &ExampleWindow::on_menu_policy), Gtk::UPDATE_DELAYED));
  m_Menu_Policy.append(*item);

  //Digits:
  m_HBox_Digits.pack_start(
    *Gtk::manage(new Gtk::Label("Scale Digits:", 0)), Gtk::PACK_SHRINK);
  m_Scale_Digits.set_digits(0);
  m_adjustment_digits->signal_value_changed().connect(sigc::mem_fun(*this,
    &ExampleWindow::on_adjustment1_value_changed));
  m_HBox_Digits.pack_start(m_Scale_Digits);

  //Page Size:
  m_HBox_PageSize.pack_start(
    *Gtk::manage(new Gtk::Label("Scrollbar Page Size:", 0)),
    Gtk::PACK_SHRINK);
  m_Scale_PageSize.set_digits(0);
  m_adjustment_pagesize->signal_value_changed().connect(sigc::mem_fun(*this,
    &ExampleWindow::on_adjustment2_value_changed));
  m_HBox_PageSize.pack_start(m_Scale_PageSize);

  m_VBox2.pack_start(m_HBox_Digits);
  m_VBox2.pack_start(m_HBox_PageSize);
  m_VBox_Top.pack_start(m_Separator, Gtk::PACK_SHRINK);
  m_VBox_Top.pack_start(m_Button_Quit, Gtk::PACK_SHRINK);

  m_Button_Quit.set_can_default();
  m_Button_Quit.grab_default();
  m_Button_Quit.signal_clicked().connect(sigc::mem_fun(*this,
    &ExampleWindow::on_button_quit));
  m_Button_Quit.set_border_width(10);

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_checkbutton_toggled()
{
  m_VScale.set_draw_value(m_CheckButton.get_active());
  m_HScale.set_draw_value(m_CheckButton.get_active());
}

void ExampleWindow::on_menu_position(Gtk::PositionType postype)
{
  m_VScale.set_value_pos(postype);
  m_HScale.set_value_pos(postype);
}

void ExampleWindow::on_menu_policy(Gtk::UpdateType type)
{
  m_VScale.set_update_policy(type);
  m_HScale.set_update_policy(type);
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
