/* gtkmm example Copyright (C) 2024 gtkmm development team
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
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include "examplewindow.h"
#include <glibmm/i18n.h>

ExampleWindow::ExampleWindow()
{
  set_title(_("English i18n example"));
  set_default_size(500, 300);

  // Add the TextView, inside a ScrolledWindow.
  m_ScrolledWindow.set_child(m_TextView);
  set_child(m_ScrolledWindow);

  fill_text_tag_table();
  fill_buffer();
  m_TextView.set_buffer(m_refTextBuffer);
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::fill_text_tag_table()
{
  m_refTextTagTable = Gtk::TextTagTable::create();
  auto textTag = Gtk::TextTag::create("plain-text");
  textTag->property_wrap_mode() = Gtk::WrapMode::WORD;
  m_refTextTagTable->add(textTag);

  textTag = Gtk::TextTag::create("script");
  textTag->property_wrap_mode() = Gtk::WrapMode::NONE;
  textTag->property_indent() = 20;
  textTag->property_family() = "Monospace";
  textTag->property_background() = "rgb(92%, 92%, 92%)"; // Light gray
  m_refTextTagTable->add(textTag);
}

void ExampleWindow::fill_buffer()
{
  m_refTextBuffer = Gtk::TextBuffer::create(m_refTextTagTable);

  // Get beginning of buffer; each insertion will revalidate the
  // iterator to point to just after the inserted text.
  auto iter = m_refTextBuffer->begin();

  iter = m_refTextBuffer->insert_with_tag(iter,
    "To build myapp with messages in a different language, e.g. German,"
    " do this in a terminal window:\n\n",
    "plain-text");
  iter = m_refTextBuffer->insert_with_tag(iter,
    "g++ -o myapp main.cc examplewindow.cc `pkg-config --cflags --libs gtkmm-4.0` -std=c++17\n\n",
    "script");
  iter = m_refTextBuffer->insert_with_tag(iter,
    "Before you run myapp, create the files with translated texts:\n\n", "plain-text");
  iter = m_refTextBuffer->insert_with_tag(iter,
    "mkdir po\n"
    "cd po\n"
    "cat >POTFILES.in <<EOF\n"
    "# List of source files containing translatable strings.\n"
    "main.cc\n"
    "examplewindow.cc\n"
    "EOF\n\n", "script");
  iter = m_refTextBuffer->insert_with_tag(iter,
    "Export all quoted texts from source code: _(\"text\") to file myapp.pot:\n\n",
    "plain-text");
  iter = m_refTextBuffer->insert_with_tag(iter,
    "intltool-update --pot --gettext-package myapp\n\n", "script"); 
  iter = m_refTextBuffer->insert_with_tag(iter,
    "Create the de.po file:\n\n", "plain-text");
  iter = m_refTextBuffer->insert_with_tag(iter,
    "msginit --no-translator --locale de_DE.UTF-8\n\n", "script");
  iter = m_refTextBuffer->insert_with_tag(iter,
    "Now run poedit or some other editor, open file de.po and translate texts of messages."
    " Write the translations after 'msgstr'."
    " If charset is not UTF-8 in the .po file, change to UTF-8."
    " Then save the de.po file. Still in the po directory, create myapp.mo from de.po:\n\n",
    "plain-text");
  iter = m_refTextBuffer->insert_with_tag(iter,
    "mkdir --parents ../locale/de/LC_MESSAGES\n"
    "msgfmt --check --verbose --output-file ../locale/de/LC_MESSAGES/myapp.mo de.po\n\n",
    "script");
  iter = m_refTextBuffer->insert_with_tag(iter,
    "Run myapp with specified language:\n\n", "plain-text");
  iter = m_refTextBuffer->insert_with_tag(iter,
    "cd ..\n"
    "LANG=de_DE.UTF-8 ./myapp\n\n", "script");
}
