/*******************************************************************************
 *
 *  Copyright(c) 2008 Jonathon Jongsma
 *
 *  This file is part of gtkmm
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>
 *
 *******************************************************************************/
#include <giomm.h>
#include <iostream>

static goffset get_size_recursively(const Glib::RefPtr<Gio::File>& file)
{
  goffset total = 0;
  g_return_val_if_fail(file, total);

  try
  {
    auto info = file->query_info();
    if(info->get_file_type() == Gio::FileType::DIRECTORY)
    {
      auto children = file->enumerate_children();
      Glib::RefPtr<Gio::FileInfo> child_info;

      while((child_info = children->next_file()))
      {
        goffset size = get_size_recursively(
            file->get_child(child_info->get_name()));
        total += size;
      }

      //std::cout << file->get_path() << ": " << total << std::endl;
    }
    else
    {
      total = info->get_size();
    }
  }
  catch(const Glib::Error& error)
  {
    std::cerr << error.what() << std::endl;
  }
  return total;
}

int main(int argc, char** argv)
{
  std::string root_dir = ".";
  if(argc > 1)
    root_dir = argv[1];

  Gio::init();

  auto file = Gio::File::create_for_path(root_dir);
  std::cout << "Gathering disk usage information for '" << file->get_path() << "'" << std::endl;

  const goffset total = get_size_recursively(file);
  std::cout << "Total: " << total << std::endl;

  return 0;
}
