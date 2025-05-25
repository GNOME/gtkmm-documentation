/* GTK - The GIMP Toolkit
 * Copyright(C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or(at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, see <https://www.gnu.org/licenses/>.
 */
#include <gtkmm.h>
#include <gtkmm/grid.h>
#include <gtkmm/togglebutton.h>
#include "tictactoe.h"

TicTacToe::TicTacToe()
: Gtk::Box(Gtk::Orientation::VERTICAL)
{
  auto grid = Gtk::make_managed<Gtk::Grid>();
  grid->set_row_homogeneous(true);
  grid->set_column_homogeneous(true);
  append(*grid);

  for(int i=0;i<3; i++)
  {
    for(int j=0;j<3; j++)
    {
      Gtk::ToggleButton* button = nullptr;
      buttons[i][j] = button = Gtk::make_managed<Gtk::ToggleButton>();
      grid->attach(*button, i, j);
      button->signal_toggled().connect( sigc::bind(
                                     sigc::mem_fun(*this, &TicTacToe::toggle),
                                     button));
      button->set_size_request(20, 20);
    }
  }
  clear();
}

TicTacToe::~TicTacToe()
{}

void
TicTacToe::clear()
{
  freeze();

  for(int i=0; i<3; i++)
    for(int j=0; j<3; j++)
      buttons[i][j]->set_active(false);

  thaw();
}

void
TicTacToe::toggle(Gtk::ToggleButton *button)
{
  if(frozen)
    return;

  static int rwins[8][3] = { { 0, 0, 0 }, { 1, 1, 1 }, { 2, 2, 2 },
                 { 0, 1, 2 }, { 0, 1, 2 }, { 0, 1, 2 },
                 { 0, 1, 2 }, { 0, 1, 2 } };
  static int cwins[8][3] = { { 0, 1, 2 }, { 0, 1, 2 }, { 0, 1, 2 },
                 { 0, 0, 0 }, { 1, 1, 1 }, { 2, 2, 2 },
                 { 0, 1, 2 }, { 2, 1, 0 } };

  bool success, found;

  for(int k=0; k<8; k++)
  {
    success = true;
    found = false;

    for(int i=0; i<3; i++)
    {
      success &= buttons[rwins[k][i]][cwins[k][i]]->get_active();
      found |= buttons[rwins[k][i]][cwins[k][i]] == button;
    }

    if(success && found)
    {
      tictactoe();
      break;
    }
  }
}

