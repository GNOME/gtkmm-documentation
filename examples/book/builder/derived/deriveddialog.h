/* gtkmm example Copyright (C) 2003 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <https://www.gnu.org/licenses/>.
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
