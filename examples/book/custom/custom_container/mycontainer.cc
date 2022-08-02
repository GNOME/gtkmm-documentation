/* gtkmm example Copyright (C) 2004 gtkmm development team
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

#include "mycontainer.h"

// This example container is a simplified vertical Box.
//
// It can't be used as a managed widget, managed by another container
// unless Gtk::Widget::signal_destroy() exists.
// It would cause an error like
// Gtk-WARNING **: 08:31:48.137: Finalizing gtkmm__GtkWidget 0x561b777462c0, but it still has children left:

MyContainer::MyContainer()
{
#if HAS_SIGNAL_DESTROY
  signal_destroy().connect(sigc::mem_fun(*this, &MyContainer::on_container_destroy));
#endif
}

MyContainer::~MyContainer()
{
  // If MyContainer is a managed widget, the underlying C object is destructed
  // before this C++ destructor is executed.
  if (!gobj())
    return;

  // If MyContainer is not a managed widget, unparent all children here.
  while (Widget* child = get_first_child())
    child->unparent();
}

#if HAS_SIGNAL_DESTROY
// This signal handler is called only if MyContainer is a managed widget.
void MyContainer::on_container_destroy()
{
  while (Widget* child = get_first_child())
    child->unparent();
}
#endif

// Get number of visible children.
int MyContainer::get_nvis_children() const
{
  int nvis_children = 0;
  for (const Widget* child = get_first_child(); child; child = child->get_next_sibling())
    if (child->get_visible())
      ++nvis_children;

  return nvis_children;
}

Gtk::SizeRequestMode MyContainer::get_request_mode_vfunc() const
{
  return Gtk::SizeRequestMode::HEIGHT_FOR_WIDTH;
}

// Discover the total amount of minimum space and natural space needed by
// this container and its children.
void MyContainer::measure_vfunc(Gtk::Orientation orientation, int for_size,
  int& minimum, int& natural, int& minimum_baseline, int& natural_baseline) const
{
  // Don't use baseline alignment.
  minimum_baseline = -1;
  natural_baseline = -1;

  minimum = 0;
  natural = 0;

  int dummy_minimum_baseline = 0;
  int dummy_natural_baseline = 0;

  if (orientation == Gtk::Orientation::HORIZONTAL)
  {
    int height_per_child = for_size;

    if (for_size >= 0)
    {
      // Number of visible children.
      const int nvis_children = get_nvis_children();

      // Divide the height equally among the visible children.
      if (nvis_children > 0)
        height_per_child = for_size / nvis_children;
    }

    // Request a width equal to the width of the widest visible child.
    for (const Widget* child = get_first_child(); child; child = child->get_next_sibling())
      if (child->get_visible())
      {
        int child_minimum_width = 0;
        int child_natural_width = 0;
        child->measure(orientation, height_per_child, child_minimum_width,
          child_natural_width, dummy_minimum_baseline, dummy_natural_baseline);
        if (child_minimum_width > minimum)
          minimum = child_minimum_width;
        if (child_natural_width > natural)
          natural = child_natural_width;
      }
  }
  else // Gtk::Orientation::VERTICAL
  {
    // The allocated height will be divided equally among the visible children.
    // Request a height equal to the number of visible children times the height
    // of the highest child.
    int nvis_children = 0;
    for (const Widget* child = get_first_child(); child; child = child->get_next_sibling())
      if (child->get_visible())
      {
        ++nvis_children;
        int child_minimum_height = 0;
        int child_natural_height = 0;
        child->measure(orientation, for_size, child_minimum_height,
          child_natural_height, dummy_minimum_baseline, dummy_natural_baseline);
        if (child_minimum_height > minimum)
          minimum = child_minimum_height;
        if (child_natural_height > natural)
          natural = child_natural_height;
      }
    minimum *= nvis_children;
    natural *= nvis_children;
  }
}

void MyContainer::size_allocate_vfunc(int width, int height, int baseline)
{
  //Do something with the space that we have actually been given:
  //(We will not be given heights or widths less than we have requested, though
  //we might get more.)

  // Number of visible children.
  const int nvis_children = get_nvis_children();

  if (nvis_children <= 0)
  {
    // No visible child.
    return;
  }

  //Assign space to the children:
  Gtk::Allocation child_allocation;
  const int height_per_child = height / nvis_children;

  //Place the first visible child at the top-left:
  child_allocation.set_x(0);
  child_allocation.set_y(0);

  //Make it take up the full width available:
  child_allocation.set_width(width);
  child_allocation.set_height(height_per_child);

  //Divide the height equally among the visible children.
  for (Widget* child = get_first_child(); child; child = child->get_next_sibling())
    if (child->get_visible())
    {
      child->size_allocate(child_allocation, baseline);
      child_allocation.set_y(child_allocation.get_y() + height_per_child);
    }
}

void MyContainer::append(Gtk::Widget& child)
{
   child.insert_at_end(*this);
}

void MyContainer::prepend(Gtk::Widget& child)
{
   child.insert_at_start(*this);
}

void MyContainer::remove(Gtk::Widget& child)
{
  child.unparent();
}
