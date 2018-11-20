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

#include <iostream>
#include <algorithm> // std::max
#include "mycontainer.h"

MyContainer::MyContainer()
: m_child_one(nullptr), m_child_two(nullptr)
{
  set_has_surface(false);
}

MyContainer::~MyContainer()
{
  if (m_child_one)
    m_child_one->unparent();

  if (m_child_two)
    m_child_two->unparent();
}

void MyContainer::set_child_widgets(Gtk::Widget& child_one,
        Gtk::Widget& child_two)
{
  m_child_one = &child_one;
  m_child_two = &child_two;

  m_child_one->set_parent(*this);
  m_child_two->set_parent(*this);
}

// This example container is a simplified vertical Box with at most two children.
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

  int dummy_minimum_baseline = 0;
  int dummy_natural_baseline = 0;

  if (orientation == Gtk::Orientation::HORIZONTAL)
  {
    int height_per_child = for_size;

    if (for_size >= 0)
    {
      int nvis_children = 0;

      // Get number of visible children.
      if (m_child_one && m_child_one->get_visible())
        ++nvis_children;
      if (m_child_two && m_child_two->get_visible())
        ++nvis_children;

      // Divide the height equally among the visible children.
      if (nvis_children > 0)
        height_per_child = for_size / nvis_children;
    }

    int child_minimum_width[2] = {0, 0};
    int child_natural_width[2] = {0, 0};

    if (m_child_one && m_child_one->get_visible())
      m_child_one->measure(orientation, height_per_child, child_minimum_width[0],
        child_natural_width[0], dummy_minimum_baseline, dummy_natural_baseline);

    if (m_child_two && m_child_two->get_visible())
      m_child_two->measure(orientation, height_per_child, child_minimum_width[1],
        child_natural_width[1], dummy_minimum_baseline, dummy_natural_baseline);

    // Request a width equal to the width of the widest visible child.
    minimum = std::max(child_minimum_width[0], child_minimum_width[1]);
    natural = std::max(child_natural_width[0], child_natural_width[1]);
  }
  else // Gtk::Orientation::VERTICAL
  {
    int child_minimum_height[2] = {0, 0};
    int child_natural_height[2] = {0, 0};
    int nvis_children = 0;

    if (m_child_one && m_child_one->get_visible())
    {
      ++nvis_children;
      m_child_one->measure(orientation, for_size, child_minimum_height[0],
        child_natural_height[0], dummy_minimum_baseline, dummy_natural_baseline);
    }

    if (m_child_two && m_child_two->get_visible())
    {
      ++nvis_children;
      m_child_two->measure(orientation, for_size, child_minimum_height[1],
        child_natural_height[1], dummy_minimum_baseline, dummy_natural_baseline);
    }

    // The allocated height will be divided equally among the visible children.
    // Request a height equal to the number of visible children times the height
    // of the highest child.
    minimum = nvis_children * std::max(child_minimum_height[0],
                                       child_minimum_height[1]);
    natural = nvis_children * std::max(child_natural_height[0],
                                       child_natural_height[1]);
  }
}

void MyContainer::on_size_allocate(int width, int height, int  baseline)
{
  //Do something with the space that we have actually been given:
  //(We will not be given heights or widths less than we have requested, though
  //we might get more.)

  //Get number of visible children.
  const bool visible_one = m_child_one && m_child_one->get_visible();
  const bool visible_two = m_child_two && m_child_two->get_visible();
  int nvis_children = 0;
  if (visible_one)
    ++nvis_children;
  if (visible_two)
    ++nvis_children;

  if (nvis_children <= 0)
  {
    // No visible child.
    return;
  }

  //Assign space to the children:
  Gtk::Allocation child_allocation_one;
  Gtk::Allocation child_allocation_two;

  //Place the first child at the top-left:
  child_allocation_one.set_x(0);
  child_allocation_one.set_y(0);

  //Make it take up the full width available:
  child_allocation_one.set_width(width);

  if (visible_one)
  {
    //Divide the height equally among the visible children.
    child_allocation_one.set_height(height / nvis_children);
    m_child_one->size_allocate(child_allocation_one, baseline);
  }
  else
    child_allocation_one.set_height(0);

  //Place the second child below the first child:
  child_allocation_two.set_x(0);
  child_allocation_two.set_y(child_allocation_one.get_height());

  //Make it take up the full width available:
  child_allocation_two.set_width(width);

  //Make it take up the remaining height:
  child_allocation_two.set_height(height - child_allocation_one.get_height());

  if (visible_two)
  {
    m_child_two->size_allocate(child_allocation_two, baseline);
  }
}

void MyContainer::forall_vfunc(const ForeachSlot& slot)
{
  if (m_child_one)
    slot(*m_child_one);

  if (m_child_two)
    slot(*m_child_two);
}

void MyContainer::on_add(Gtk::Widget* child)
{
  if(!m_child_one)
  {
    m_child_one = child;
    m_child_one->set_parent(*this);
  }
  else if(!m_child_two)
  {
    m_child_two = child;
    m_child_two->set_parent(*this);
  }
}

void MyContainer::on_remove(Gtk::Widget* child)
{
  if(child)
  {
    const bool visible = child->get_visible();
    bool found = false;

    if(child == m_child_one)
    {
      m_child_one = nullptr;
      found = true;
    }
    else if(child == m_child_two)
    {
      m_child_two = nullptr;
      found = true;
    }

    if(found)
    {
      child->unparent();

      if(visible)
        queue_resize();
    }
  }
}

GType MyContainer::child_type_vfunc() const
{
  //If there is still space for one widget, then report the type of widget that
  //may be added.
  if(!m_child_one || !m_child_two)
    return Gtk::Widget::get_type();
  else
  {
    //No more widgets may be added.
    return G_TYPE_NONE;
  }
}
