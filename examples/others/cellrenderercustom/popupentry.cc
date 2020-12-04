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

#include <gtkmm.h>
#include "popupentry.h"

#include <gdk/gdkkeysyms.h>

PopupEntry::PopupEntry(const Glib::ustring& path)
:
  Glib::ObjectBase  (typeid(PopupEntry)),
  Gtk::CellEditable (),
  Gtk::Box          (Gtk::Orientation::HORIZONTAL),
  path_             (path),
  button_           (nullptr),
  entry_            (nullptr),
  editing_canceled_ (false)
{
  entry_ = new Gtk::Entry();
  append(*Gtk::manage(entry_));
  entry_->set_has_frame(false);
  entry_->set_expand(true);

  button_ = new Gtk::Button();
  append(*Gtk::manage(button_));
  button_->set_image_from_icon_name("pan-down-symbolic", Gtk::IconSize::INHERIT, true);

  set_can_focus();

  auto controller = Gtk::EventControllerKey::create();
  controller->signal_key_pressed().connect(
    sigc::mem_fun(*this, &Self::on_popup_key_pressed), false);
  add_controller(controller);
}

PopupEntry::~PopupEntry()
{}

Glib::ustring PopupEntry::get_path() const
{
  return path_;
}

void PopupEntry::set_text(const Glib::ustring& text)
{
  entry_->set_text(text);
}

Glib::ustring PopupEntry::get_text() const
{
  return entry_->get_text();
}

void PopupEntry::select_region(int start_pos, int end_pos)
{
  entry_->select_region(start_pos, end_pos);
}

bool PopupEntry::get_editing_canceled() const
{
  return editing_canceled_;
}

// static
int PopupEntry::get_button_width()
{
  Gtk::Window window;

  Gtk::Button *const button = new Gtk::Button();
  window.set_child(*Gtk::manage(button));

  button->set_image_from_icon_name("pan-down-symbolic", Gtk::IconSize::INHERIT, true);

  // Urgh.  Hackish :/
  //window.move(-500, -500);

  //TODO: Support natural-size:
  Gtk::Requisition requisition_min, requisition_natural;
  window.get_preferred_size(requisition_min, requisition_natural);

  return requisition_min.get_width();
}

PopupEntry::type_signal_arrow_clicked& PopupEntry::signal_arrow_clicked()
{
  return signal_arrow_clicked_;
}

bool PopupEntry::on_popup_key_pressed(guint keyval, guint, Gdk::ModifierType)
{
  if (keyval == GDK_KEY_Escape)
  {
    editing_canceled_ = true;

    editing_done();
    remove_widget();

    return true;
  }

  entry_->grab_focus();

  // Hackish :/ Synthesize a key press event for the entry.

/*
 * Can't do this now (2017-10-06).
 * GdkEvent and its subclasses are now opaque structures. We can't directly
 * access their data. There is a gdk_event_get_surface() to get the GDK surface,
 * but there is no gdk_event_set_surface() to set a surface.

  Gdk::EventKey synth_event(key_event);

  GdkEventKey* const synth_event_gobj = synth_event.gobj();
  if (synth_event_gobj->window)
    g_object_unref(synth_event_gobj->surface);
  synth_event_gobj->surface = Glib::unwrap(entry_->get_surface());
  if (synth_event_gobj->surface)
    g_object_ref(synth_event_gobj->surface);
  synth_event_gobj->send_event = true;

  entry_->event(synth_event);
*/
  return false;
}

void PopupEntry::start_editing_vfunc(const Glib::RefPtr<const Gdk::Event>&)
{
  entry_->select_region(0, -1);

  // Although this is a key-binding signal, it's acceptable to use it in applications.
  // 2019-03-07: No longer true in gtk4.
  //entry_->signal_activate().connect(sigc::mem_fun(*this, &Self::on_entry_activate));

  auto controller = Gtk::EventControllerKey::create();
  controller->signal_key_pressed().connect(
    sigc::mem_fun(*this, &Self::on_entry_key_pressed), false);
  entry_->add_controller(controller);

  //TODO: Doesn't this mean that we have multiple connection, because this is never disconnected?
  button_->signal_clicked().connect(sigc::mem_fun(*this, &Self::on_button_clicked));
}

void PopupEntry::on_button_clicked()
{
  signal_arrow_clicked_.emit();
}

void PopupEntry::on_entry_activate()
{
  editing_done();
  //remove_widget(); // TODO: this line causes the widget to be removed twice -- dunno why
}

bool PopupEntry::on_entry_key_pressed(guint keyval, guint, Gdk::ModifierType)
{
  if (keyval == GDK_KEY_Escape)
  {
    editing_canceled_ = true;

    editing_done();
    remove_widget();

    return true;
  }

  return false;
}
