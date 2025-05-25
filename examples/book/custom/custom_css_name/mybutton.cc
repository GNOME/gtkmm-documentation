/* gtkmm example Copyright (C) 2022 gtkmm development team
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

#include "mybutton.h"
#include <gtk/gtk.h> // For GTK_IS_BUTTON()
#include <iostream>

MyButton::MyButton(const Glib::ustring& label, bool mnemonic)
  :
  // The GType name will actually be gtkmm__CustomObject_MyButton
  Glib::ObjectBase("MyButton"),
  MyExtraInit("my-button"), // CSS node name, which must be used in the CSS file.
  Gtk::Button(label, mnemonic)
{
  // This shows the GType name:
  std::cout << "GType name: " << G_OBJECT_TYPE_NAME(gobj()) << std::endl;

  // This shows that the GType still derives from GtkButton:
  std::cout << "Gtype is a GtkButton?: " << GTK_IS_BUTTON(gobj()) << std::endl;

  // The CSS name can be set either
  // - for a GType (in this case for your custom class) with gtk_widget_class_set_css_name(), or
  // - for a widget instance with gtk_widget_set_name() (Gtk::Widget::set_name()).
  //
  // gtk_widget_class_set_css_name(), if used, must be called in the class init function.
  // It has not been wrapped in a C++ function.
  // Gtk::Widget::set_name() can be called in a C++ constructor.
  //
  // Another alternative: The custom button inherits the CSS name "button" from
  // GtkButton. That name can be used in the CSS file.
}

MyButton::~MyButton()
{
}
