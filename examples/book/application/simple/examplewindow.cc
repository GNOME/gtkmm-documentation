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

ExampleWindow::ExampleWindow()
{
  set_title("Gtk::Application example");

  add(m_scrolledwindow);
  m_scrolledwindow.add(m_view);
}

bool ExampleWindow::load_file(const Glib::RefPtr<Gio::File>& file)
{
  if(!file)
    return false;

  try
  {
    char* contents = nullptr;
    gsize length = 0;

    if(file->load_contents(contents, length))
    {
      if(contents && length)
      {
        const Glib::ustring text(contents);
        auto buffer = m_view.get_buffer();
        buffer->set_text(text);
      }
      g_free(contents);
    }
  }
  catch (const Glib::Error& ex)
  {
    std::cerr << G_STRFUNC << ": exception while opening file: " << file->get_uri() <<  std::endl <<
      "  exception: " << ex.what() << std::endl;

    //Tell the application that this window can no longer be useful to
    //this application, so it can forget about it. The instance might then exit
    //if this is its last open window.
    //Note that we must be careful that the caller only calls this method _after_
    //calling show(), or this would be useless:
    hide();
    return false;
  }

  show_all_children();
  return true;
}
