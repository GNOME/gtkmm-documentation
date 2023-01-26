/* libglademm example Copyright (C) 2003 libglademm development team
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

#ifndef GTKMM_EXAMPLE_DERIVED_DIALOG_H
#define GTKMM_EXAMPLE_DERIVED_DIALOG_H

#include <gtkmm.h>
#include "derivedbutton.h"

class DerivedDialog : public Gtk::Window
{
public:
  DerivedDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);
  DerivedDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder,
    bool is_glad);
  ~DerivedDialog() override;

protected:
  //Signal handlers:
  void on_button_quit();

  Glib::RefPtr<Gtk::Builder> m_refBuilder;
  DerivedButton* m_pButton;
};

#endif //GTKMM_EXAMPLE_DERIVED_DIALOG_H
