/* gtkmm example Copyright (C) 2011 gtkmm development team
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

#include "exampleoptiongroup.h"
#include <iostream>

ExampleOptionGroup::ExampleOptionGroup()
: Glib::OptionGroup("example_group", "description of example group", "help description of example group"),
  m_arg_foo(0)
{
  //These are just two pointless command-line arguments to show the use 
  //of the API:
  Glib::OptionEntry entry1;
  entry1.set_long_name("foo");
  entry1.set_short_name('f');
  entry1.set_description("Enable foo.");
  add_entry(entry1, m_arg_foo);
      
  Glib::OptionEntry entry2;
  entry2.set_long_name("goo");
  entry2.set_short_name('g');
  entry2.set_description("The name of goo to use.");
  add_entry_filename(entry2, m_arg_goo);
}

void ExampleOptionGroup::on_error(Glib::OptionContext& /* context */, Glib::OptionGroup& /* group */)
{
  std::cout << "on_error called" << std::endl;
}
