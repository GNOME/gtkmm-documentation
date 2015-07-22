//$Id: mycontainer.cc 836 2007-05-09 03:02:38Z jjongsma $ -*- c++ -*-

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
  set_has_window(false);
  set_redraw_on_allocate(false);
}

MyContainer::~MyContainer()
{
/*
  // These calls to Gtk::Widget::unparent() are necessary if MyContainer is
  // deleted before its children. But if you use a version of gtkmm where bug
  // https://bugzilla.gnome.org/show_bug.cgi?id=605728
  // has not been fixed (gtkmm 3.7.10 or earlier) and the children are deleted
  // before the container, these calls can make the program crash.
  // That's because on_remove() is not called, when the children are deleted.
  if (m_child_one)
    m_child_one->unparent();

  if (m_child_two)
    m_child_two->unparent();
*/
}

void MyContainer::set_child_widgets(Gtk::Widget& child_one,
        Gtk::Widget& child_two)
{
  m_child_one = &child_one;
  m_child_two = &child_two;

  m_child_one->set_parent(*this);
  m_child_two->set_parent(*this);
}

//This example container is a simplified VBox with at most two children.
Gtk::SizeRequestMode MyContainer::get_request_mode_vfunc() const
{
  return Gtk::SIZE_REQUEST_HEIGHT_FOR_WIDTH;
}

//Discover the total amount of minimum space and natural space needed by
//this container and its children.
void MyContainer::get_preferred_width_vfunc(int& minimum_width, int& natural_width) const
{
  int child_minimum_width[2] = {0, 0};
  int child_natural_width[2] = {0, 0};

  if(m_child_one && m_child_one->get_visible())
    m_child_one->get_preferred_width(child_minimum_width[0], child_natural_width[0]);

  if(m_child_two && m_child_two->get_visible())
    m_child_two->get_preferred_width(child_minimum_width[1], child_natural_width[1]);

  //Request a width equal to the width of the widest visible child.
  minimum_width = std::max(child_minimum_width[0], child_minimum_width[1]);
  natural_width = std::max(child_natural_width[0], child_natural_width[1]);
}

void MyContainer::get_preferred_height_for_width_vfunc(int width,
   int& minimum_height, int& natural_height) const
{
  int child_minimum_height[2] = {0, 0};
  int child_natural_height[2] = {0, 0};
  int nvis_children = 0;

  if(m_child_one && m_child_one->get_visible())
  {
    ++nvis_children;
    m_child_one->get_preferred_height_for_width(width, child_minimum_height[0],
                                                child_natural_height[0]);
  }

  if(m_child_two && m_child_two->get_visible())
  {
    ++nvis_children;
    m_child_two->get_preferred_height_for_width(width, child_minimum_height[1],
                                                child_natural_height[1]);
  }

  //The allocated height will be divided equally among the visible children.
  //Request a height equal to the number of visible children times the height
  //of the highest child.
  minimum_height = nvis_children * std::max(child_minimum_height[0],
                                            child_minimum_height[1]);
  natural_height = nvis_children * std::max(child_natural_height[0],
                                            child_natural_height[1]);
}

void MyContainer::get_preferred_height_vfunc(int& minimum_height, int& natural_height) const
{
  int child_minimum_height[2] = {0, 0};
  int child_natural_height[2] = {0, 0};
  int nvis_children = 0;

  if(m_child_one && m_child_one->get_visible())
  {
    ++nvis_children;
    m_child_one->get_preferred_height(child_minimum_height[0], child_natural_height[0]);
  }

  if(m_child_two && m_child_two->get_visible())
  {
    ++nvis_children;
    m_child_two->get_preferred_height(child_minimum_height[1], child_natural_height[1]);
  }

  //The allocated height will be divided equally among the visible children.
  //Request a height equal to the number of visible children times the height
  //of the highest child.
  minimum_height = nvis_children * std::max(child_minimum_height[0],
                                            child_minimum_height[1]);
  natural_height = nvis_children * std::max(child_natural_height[0],
                                            child_natural_height[1]);
}

void MyContainer::get_preferred_width_for_height_vfunc(int height,
   int& minimum_width, int& natural_width) const
{
  int child_minimum_width[2] = {0, 0};
  int child_natural_width[2] = {0, 0};
  int nvis_children = 0;

  //Get number of visible children.
  if(m_child_one && m_child_one->get_visible())
    ++nvis_children;
  if(m_child_two && m_child_two->get_visible())
    ++nvis_children;

  if(nvis_children > 0)
  {
    //Divide the height equally among the visible children.
    const int height_per_child = height / nvis_children;

    if(m_child_one && m_child_one->get_visible())
      m_child_one->get_preferred_width_for_height(height_per_child,
                   child_minimum_width[0], child_natural_width[0]);

    if(m_child_two && m_child_two->get_visible())
      m_child_two->get_preferred_width_for_height(height_per_child,
                   child_minimum_width[1], child_natural_width[1]);
  }

  //Request a width equal to the width of the widest child.
  minimum_width = std::max(child_minimum_width[0], child_minimum_width[1]);
  natural_width = std::max(child_natural_width[0], child_natural_width[1]);
}

void MyContainer::on_size_allocate(Gtk::Allocation& allocation)
{
  //Do something with the space that we have actually been given:
  //(We will not be given heights or widths less than we have requested, though
  //we might get more.)

  //Use the offered allocation for this container:
  set_allocation(allocation);

  //Get number of visible children.
  int nvis_children = 0;
  if(m_child_one && m_child_one->get_visible())
    ++nvis_children;
  if(m_child_two && m_child_two->get_visible())
    ++nvis_children;

  if(nvis_children <= 0)
    return;

  //Assign space to the children:
  Gtk::Allocation child_allocation_one;
  Gtk::Allocation child_allocation_two;

  //Place the first child at the top-left:
  child_allocation_one.set_x( allocation.get_x() );
  child_allocation_one.set_y( allocation.get_y() );

  //Make it take up the full width available:
  child_allocation_one.set_width( allocation.get_width() );

  if(m_child_one && m_child_one->get_visible())
  {
    //Divide the height equally among the visible children.
    child_allocation_one.set_height( allocation.get_height() / nvis_children);
    m_child_one->size_allocate(child_allocation_one);
  }
  else
    child_allocation_one.set_height(0);

  //Place the second child below the first child:
  child_allocation_two.set_x( allocation.get_x() );
  child_allocation_two.set_y( allocation.get_y() +
          child_allocation_one.get_height());

  //Make it take up the full width available:
  child_allocation_two.set_width( allocation.get_width() );

  //Make it take up the remaining height:
  child_allocation_two.set_height( allocation.get_height() -
          child_allocation_one.get_height());

  if(m_child_two && m_child_two->get_visible())
    m_child_two->size_allocate(child_allocation_two);
}

void MyContainer::forall_vfunc(gboolean, GtkCallback callback, gpointer callback_data)
{
  if(m_child_one)
    callback(m_child_one->gobj(), callback_data);

  if(m_child_two)
    callback(m_child_two->gobj(), callback_data);
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
