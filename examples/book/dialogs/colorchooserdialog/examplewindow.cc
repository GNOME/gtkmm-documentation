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
: m_VBox(Gtk::Orientation::VERTICAL, 5),
  m_Button_Dialog("Choose Color")
{
  set_title("Gtk::ColorChooserDialog example");
  set_default_size(200, 200);

  add(m_VBox);

  m_VBox.add(m_ColorButton);
  m_ColorButton.signal_color_set().connect(sigc::mem_fun(*this,
    &ExampleWindow::on_color_button_color_set) );

  m_VBox.add(m_Button_Dialog);
  m_Button_Dialog.signal_clicked().connect(sigc::mem_fun(*this,
    &ExampleWindow::on_button_dialog_clicked) );

  //Set start color:
  m_Color.set_red(0.0);
  m_Color.set_green(0.0);
  m_Color.set_blue(1.0);
  m_Color.set_alpha(1.0); //opaque
  m_ColorButton.set_rgba(m_Color);

  m_VBox.add(m_DrawingArea);
  m_DrawingArea.set_expand(true);
  m_DrawingArea.set_draw_func(sigc::mem_fun(*this, &ExampleWindow::on_drawing_area_draw));
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
    case Gtk::ResponseType::OK:
    {
      //Store the chosen color:
      m_Color = dialog.get_rgba();
      m_ColorButton.set_rgba(m_Color);
      break;
    }
    case Gtk::ResponseType::CANCEL:
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

void ExampleWindow::on_drawing_area_draw(const Cairo::RefPtr<Cairo::Context>& cr, int, int)
{
  Gdk::Cairo::set_source_rgba(cr, m_Color);
  cr->paint();
}
