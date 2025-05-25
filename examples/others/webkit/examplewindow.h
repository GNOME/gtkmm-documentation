/* gtkmm example Copyright (C) 2025 gtkmm development team
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

#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

// https://gitlab.gnome.org/GNOME/gtkmm-documentation/-/issues/26

// g++ -o app main.cc examplewindow.cc `pkg-config --cflags --libs gtkmm-4.0 webkitgtk-6.0` -std=c++17

// If you get this execution error:
//   bwrap: setting up uid map: Permission denied
// see instructions at https://funos.org/solve-bwrap-permission-denied/
// 1. Add file /etc/apparmor.d/bwrap with contents:
//      abi <abi/4.0>,
//      include <tunables/global>
//
//      profile bwrap /usr/bin/bwrap flags=(unconfined) {
//        userns,
//
//        # Site-specific additions and overrides. See local/README for details.
//        include if exists <local/bwrap>
//      }
// 2. Restart AppArmor:
//      sudo systemctl restart apparmor.service

#include <gtkmm.h>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  ~ExampleWindow() override;

protected:
};

#endif // GTKMM_EXAMPLEWINDOW_H
