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
: m_VBox(Gtk::ORIENTATION_VERTICAL, 5),
  m_Button_Dialog("Choose Color")
{
  set_title("Gtk::ColorChooserDialog example");
  set_default_size(200, 200);

  add(m_VBox);

  m_VBox.pack_start(m_ColorButton, Gtk::PACK_SHRINK);
  m_ColorButton.signal_color_set().connect(sigc::mem_fun(*this,
    &ExampleWindow::on_color_button_color_set) );

  m_VBox.pack_start(m_Button_Dialog, Gtk::PACK_SHRINK);
  m_Button_Dialog.signal_clicked().connect(sigc::mem_fun(*this,
    &ExampleWindow::on_button_dialog_clicked) );

  //Set start color:
  m_Color.set_red(0.0);
  m_Color.set_green(0.0);
  m_Color.set_blue(1.0);
  m_Color.set_alpha(1.0); //opaque
  m_ColorButton.set_rgba(m_Color);

  m_VBox.pack_start(m_DrawingArea);
  m_DrawingArea.signal_draw().connect(sigc::mem_fun(*this,
    &ExampleWindow::on_drawing_area_draw));

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_color_button_color_set()
{
  //Store the chosen color:
  m_Color = m_ColorButton.get_rgba();
}

void ExampleWindow::on_button_dialog_clicked()
{
  Gtk::ColorChooserDialog dialog("Please choose a color");
  dialog.set_transient_for(*this);

  //Get the previously selected color:
  dialog.set_rgba(m_Color);

  const int result = dialog.run();

  //Handle the response:
  switch(result)
  {
    case Gtk::RESPONSE_OK:
    {
      //Store the chosen color:
      m_Color = dialog.get_rgba();
      m_ColorButton.set_rgba(m_Color);
      break;
    }
    case Gtk::RESPONSE_CANCEL:
    {
      std::cout << "Cancel clicked." << std::endl;
      break;
    }
    default:
    {
      std::cout << "Unexpected button clicked: " << result << std::endl;
      break;
    }
  }
}

bool ExampleWindow::on_drawing_area_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  Gdk::Cairo::set_source_rgba(cr, m_Color);
  cr->paint();

  return true;
}
