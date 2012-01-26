//$Id: examplewindow.h 705 2006-07-19 02:55:32Z jjongsma $ -*- c++ -*-

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

#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm.h>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  virtual ~ExampleWindow();

protected:
  //Signal handlers:
  void on_checkbutton_text();
  void on_checkbutton_activity();
  void on_checkbutton_inverted();
  virtual bool on_timeout();
  void on_button_close();

  //Child widgets:
  Gtk::Box m_VBox;
  Gtk::Alignment m_Alignment;
  Gtk::Grid m_Grid;
  Gtk::ProgressBar m_ProgressBar;
  Gtk::Separator m_Separator;
  Gtk::CheckButton m_CheckButton_Text, m_CheckButton_Activity, m_CheckButton_Inverted;
  Gtk::Button m_Button_Close;

  int m_connection_id_timeout;
  bool m_bActivityMode;
};

#endif //GTKMM_EXAMPLEWINDOW_H
