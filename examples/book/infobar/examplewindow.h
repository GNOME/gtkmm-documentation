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

#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm.h>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  ~ExampleWindow() override;

protected:
  //Signal handlers:
  void on_infobar_ok();
  void on_button_quit();
  void on_button_clear();
  void on_textbuffer_changed();
  void on_parsing_error(const Glib::RefPtr<const Gtk::CssSection>& section,
    const Glib::Error& error);

  void set_infobar_background();

  //Child widgets:
  Gtk::Box m_VBox;

  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::TextView m_TextView;

  Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;

  Gtk::Box m_InfoBar;
  Gtk::Label m_Message_Label;
  Gtk::Button m_Button_OK;

  Gtk::Box m_ButtonBox;
  Gtk::Button m_Button_Quit;
  Gtk::Button m_Button_Clear;
};

#endif //GTKMM_EXAMPLEWINDOW_H
