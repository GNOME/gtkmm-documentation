/* gtkmm example Copyright (C) 2013 gtkmm development team
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
#include <iostream>

ExampleWindow::ExampleWindow() :
  m_VBox(Gtk::ORIENTATION_VERTICAL, 5),
  m_ButtonBox(Gtk::ORIENTATION_HORIZONTAL),
  m_ButtonStart("Start work"),
  m_ButtonStop("Stop work"),
  m_ButtonQuit("_Quit", /* mnemonic= */ true),
  m_ProgressBar(),
  m_ScrolledWindow(),
  m_TextView(),
  m_Dispatcher(),
  m_Worker(),
  m_WorkerThread(0)
{
  set_title("Multi-threaded example");
  set_border_width(5);
  set_default_size(300, 300);

  add(m_VBox);

  // Add the ProgressBar.
  m_VBox.pack_start(m_ProgressBar, Gtk::PACK_SHRINK);

  m_ProgressBar.set_text("Fraction done");
  m_ProgressBar.set_show_text();

  // Add the TextView, inside a ScrolledWindow.
  m_ScrolledWindow.add(m_TextView);

  // Only show the scrollbars when they are necessary.
  m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

  m_VBox.pack_start(m_ScrolledWindow);

  m_TextView.set_editable(false);

  // Add the buttons to the ButtonBox.
  m_VBox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);

  m_ButtonBox.pack_start(m_ButtonStart, Gtk::PACK_SHRINK);
  m_ButtonBox.pack_start(m_ButtonStop, Gtk::PACK_SHRINK);
  m_ButtonBox.pack_start(m_ButtonQuit, Gtk::PACK_SHRINK);
  m_ButtonBox.set_border_width(5);
  m_ButtonBox.set_spacing(5);
  m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);

  // Connect the signal handlers to the buttons.
  m_ButtonStart.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_start_button_clicked));
  m_ButtonStop.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_stop_button_clicked));
  m_ButtonQuit.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_quit_button_clicked));

  // Connect the handler to the dispatcher.
  m_Dispatcher.connect(sigc::mem_fun(*this, &ExampleWindow::on_notification_from_worker_thread));

  // Create a text buffer mark for use in update_widgets().
  Glib::RefPtr<Gtk::TextBuffer> buffer = m_TextView.get_buffer();
  buffer->create_mark("last_line", buffer->end(), /* left_gravity= */ true);

  update_start_stop_buttons();

  show_all_children();
}

void ExampleWindow::on_start_button_clicked()
{
  if (m_WorkerThread)
  {
    std::cout << "Can't start a worker thread while another one is running." << std::endl;
  }
  else
  {
    // Start a new worker thread.
    m_WorkerThread = Glib::Threads::Thread::create(
      sigc::bind(sigc::mem_fun(m_Worker, &ExampleWorker::do_work), this));
  }
  update_start_stop_buttons();
}

void ExampleWindow::on_stop_button_clicked()
{
  if (!m_WorkerThread)
  {
    std::cout << "Can't stop a worker thread. None is running." << std::endl;
  }
  else
  {
   // Order the worker thread to stop.
    m_Worker.stop_work();
    m_ButtonStop.set_sensitive(false);
  }
}

void ExampleWindow::update_start_stop_buttons()
{
  const bool thread_is_running = m_WorkerThread != 0;

  m_ButtonStart.set_sensitive(!thread_is_running);
  m_ButtonStop.set_sensitive(thread_is_running);
}

void ExampleWindow::update_widgets()
{
  double fraction_done;
  Glib::ustring message_from_worker_thread;
  m_Worker.get_data(&fraction_done, &message_from_worker_thread);

  m_ProgressBar.set_fraction(fraction_done);

  if (message_from_worker_thread != m_TextView.get_buffer()->get_text())
  {
    Glib::RefPtr<Gtk::TextBuffer> buffer = m_TextView.get_buffer();
    buffer->set_text(message_from_worker_thread);

    // Scroll the last inserted line into view. That's somewhat complicated.
    Gtk::TextIter iter = buffer->end();
    iter.set_line_offset(0); // Beginning of last line
    Glib::RefPtr<Gtk::TextMark> mark = buffer->get_mark("last_line");
    buffer->move_mark(mark, iter);
    m_TextView.scroll_to(mark);
    // TextView::scroll_to(iter) is not perfect.
    // We do need a TextMark to always get the last line into view.
  }
}

void ExampleWindow::on_quit_button_clicked()
{
  if (m_WorkerThread)
  {
    // Order the worker thread to stop and wait for it to stop.
    m_Worker.stop_work();
    m_WorkerThread->join();
  }
  hide();
}

// notify() is called from ExampleWorker::do_work(). It is executed in the worker
// thread. It triggers a call to on_notification_from_worker_thread(), which is
// executed in the GUI thread.
void ExampleWindow::notify()
{
  m_Dispatcher.emit();
}

void ExampleWindow::on_notification_from_worker_thread()
{
  if (m_WorkerThread && m_Worker.has_stopped())
  {
    // Work is done.
    m_WorkerThread->join();
    m_WorkerThread = 0;
    update_start_stop_buttons();
  }
  update_widgets();
}
