/* gtkmm example Copyright (C) 2013 gtkmm development team
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

#include "examplewindow.h"
#include <iostream>

ExampleWindow::ExampleWindow() :
  m_VBox(Gtk::Orientation::VERTICAL, 5),
  m_ButtonBox(Gtk::Orientation::HORIZONTAL),
  m_ButtonStart("Start work"),
  m_ButtonStop("Stop work"),
  m_ButtonQuit("_Quit", /* mnemonic= */ true),
  m_ProgressBar(),
  m_ScrolledWindow(),
  m_TextView(),
  m_Dispatcher(),
  m_Worker(),
  m_WorkerThread(nullptr)
{
  set_title("Multi-threaded example");
  set_default_size(300, 300);

  m_VBox.set_margin(5);
  set_child(m_VBox);

  // Add the ProgressBar.
  m_VBox.append(m_ProgressBar);

  m_ProgressBar.set_text("Fraction done");
  m_ProgressBar.set_show_text();

  // Add the TextView, inside a ScrolledWindow.
  m_ScrolledWindow.set_child(m_TextView);

  // Only show the scrollbars when they are necessary.
  m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_ScrolledWindow.set_expand();

  m_VBox.append(m_ScrolledWindow);

  m_TextView.set_editable(false);

  // Add the buttons to the ButtonBox.
  m_VBox.append(m_ButtonBox);

  m_ButtonBox.append(m_ButtonStart);
  m_ButtonBox.append(m_ButtonStop);
  m_ButtonBox.append(m_ButtonQuit);
  m_ButtonBox.set_margin(5);
  m_ButtonBox.set_spacing(5);
  m_ButtonStart.set_hexpand(true);
  m_ButtonStart.set_halign(Gtk::Align::END);

  // Connect the signal handlers to the buttons.
  m_ButtonStart.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_start_button_clicked));
  m_ButtonStop.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_stop_button_clicked));
  m_ButtonQuit.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_quit_button_clicked));

  // Connect the handler to the dispatcher.
  m_Dispatcher.connect(sigc::mem_fun(*this, &ExampleWindow::on_notification_from_worker_thread));

  // Create a text buffer mark for use in update_widgets().
  auto buffer = m_TextView.get_buffer();
  buffer->create_mark("last_line", buffer->end(), /* left_gravity= */ true);

  update_start_stop_buttons();
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
    m_WorkerThread = new std::thread(
      [this]
      {
        m_Worker.do_work(this);
      });
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
  const bool thread_is_running = m_WorkerThread != nullptr;

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
    auto buffer = m_TextView.get_buffer();
    buffer->set_text(message_from_worker_thread);

    // Scroll the last inserted line into view. That's somewhat complicated.
    auto iter = buffer->end();
    iter.set_line_offset(0); // Beginning of last line
    auto mark = buffer->get_mark("last_line");
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
    if (m_WorkerThread->joinable())
      m_WorkerThread->join();
  }
  set_visible(false);
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
    if (m_WorkerThread->joinable())
      m_WorkerThread->join();
    delete m_WorkerThread;
    m_WorkerThread = nullptr;
    update_start_stop_buttons();
  }
  update_widgets();
}
