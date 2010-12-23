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

#include <iostream>

#include "examplewindow.h"

ExampleWindow::ExampleWindow(const Glib::RefPtr<Gio::File>& file)
{
  set_title("Gio::Application example");

  add(scrolled);
  scrolled.add(view);

  if (!file)
    return;

  try
  {
    char* contents = 0;
    gsize length = 0;

    if (file->load_contents(contents, length))
    {
      if(contents && length)
      {
        const Glib::ustring text(contents);
        Glib::RefPtr<Gtk::TextBuffer> buffer;
        buffer = view.get_buffer();
        buffer->set_text(text);
      }
      g_free(contents);
    }
  } catch (const Glib::Error& e)
  {
    std::cerr << e.what() << std::endl;
  };

  show_all_children();
}
