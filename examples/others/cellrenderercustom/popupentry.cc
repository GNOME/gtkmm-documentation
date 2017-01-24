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

// 2014-09-06: The pan-[up,down,start,end]-symbolic icons are new.
// See https://bugzilla.gnome.org/show_bug.cgi?id=729565
// If they are not available in your selected icon theme, perhaps you can
// use the go-[up,down,previous,next]-symbolic icons.

PopupEntry::PopupEntry(const Glib::ustring& path)
:
  Glib::ObjectBase  (typeid(PopupEntry)),
  Gtk::CellEditable (),
  Gtk::EventBox     (),
  path_             (path),
  button_           (nullptr),
  entry_            (nullptr),
  editing_canceled_ (false)
{
  Gtk::Box *const hbox = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL);
  add(*Gtk::manage(hbox));

  entry_ = new Gtk::Entry();
  hbox->pack_start(*Gtk::manage(entry_), Gtk::PACK_EXPAND_WIDGET);
  entry_->set_has_frame(false);

  button_ = new Gtk::Button();
  hbox->pack_start(*Gtk::manage(button_), Gtk::PACK_SHRINK);
  button_->set_image_from_icon_name("pan-down-symbolic", Gtk::ICON_SIZE_BUTTON, true);

  set_can_focus();
  add_events(Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK);
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
  Gtk::Window window (Gtk::WINDOW_POPUP);

  Gtk::Button *const button = new Gtk::Button();
  window.add(*Gtk::manage(button));

  button->set_image_from_icon_name("pan-down-symbolic", Gtk::ICON_SIZE_BUTTON, true);

  // Urgh.  Hackish :/
  window.move(-500, -500);

  //TODO: Support natural-size:
  Gtk::Requisition requisition_min, requisition_natural;
  window.get_preferred_size(requisition_min, requisition_natural);

  return requisition_min.width;
}

PopupEntry::type_signal_arrow_clicked& PopupEntry::signal_arrow_clicked()
{
  return signal_arrow_clicked_;
}

bool PopupEntry::on_key_press_event(GdkEventKey* key_event)
{
  if(key_event->keyval == GDK_KEY_Escape)
  {
    editing_canceled_ = true;

    editing_done();
    remove_widget();

    return true;
  }

  entry_->grab_focus();

  // Hackish :/ Synthesize a key press event for the entry.

  GdkEvent synth_event;
  synth_event.key = *key_event;

  synth_event.key.window = Glib::unwrap(entry_->get_window()); // TODO: Use a C++ Gdk::Event.
  synth_event.key.send_event = true;

  entry_->event(&synth_event);

  return Gtk::EventBox::on_key_press_event(key_event);
}

void PopupEntry::start_editing_vfunc(GdkEvent*)
{
  entry_->select_region(0, -1);

  // Although this is a key-binding signal, it's acceptable to use it in applications.
  entry_->signal_activate().connect(sigc::mem_fun(*this, &Self::on_entry_activate));
  entry_->signal_key_press_event().connect(sigc::mem_fun(*this, &Self::on_entry_key_press_event), false);

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

bool PopupEntry::on_entry_key_press_event(GdkEventKey* key_event)
{
  if(key_event->keyval == GDK_KEY_Escape)
  {
    editing_canceled_ = true;

    editing_done();
    remove_widget();

    return true;
  }

  return false;
}
