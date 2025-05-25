/* gtkmm example Copyright (C) 2025 gtkmm development team
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
#include <webkit/webkit.h>

ExampleWindow::ExampleWindow()
{
  set_title("Webkit Frame");
  set_default_size(600, 400);

  WebKitWebView* wkwv =  WEBKIT_WEB_VIEW(webkit_web_view_new());

  Gtk::Widget* gwkwv = Glib::wrap(GTK_WIDGET(wkwv));

  set_child(*gwkwv);

  webkit_web_view_load_uri(wkwv, "http://www.webkitgtk.org/");
}

ExampleWindow::~ExampleWindow()
{
}
