//$Id: main.cc 836 2007-05-09 03:02:38Z jjongsma $ -*- c++ -*-

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

#include <giomm.h>
#include <iostream>
#include <cstring>



Glib::RefPtr<Glib::MainLoop> mainloop;
Glib::RefPtr<Gio::File> file;
Glib::RefPtr<Gio::FileInputStream> stream;
gchar buffer[1000]; //TODO: This is unpleasant.

void on_stream_read_async_ready(Glib::RefPtr<Gio::AsyncResult>& result)
{
  std::cout << "Stream Async handler called." << std::endl;

  try
  {
    const gsize bytes_read = stream->read_finish(result);
    
    if(bytes_read)
      std::cout << "File contents read: " << buffer << std::endl;
    else
      std::cerr << "Gio::InputStream::read() read 0 bytes." << std::endl;

  }
  catch(const Glib::Exception& ex)
  {
    std::cerr << "Exception caught: " << ex.what() << std::endl; 
  }

  mainloop->quit();
}

void on_file_read_async_ready(Glib::RefPtr<Gio::AsyncResult>& result)
{
  std::cout << "File Async handler called." << std::endl;

  try
  {
    stream = file->read_finish(result);
    if(!stream)
      std::cerr << "Gio::File::read() returned an empty RefPtr." << std::endl;
  }
  catch(const Glib::Exception& ex)
  {
    std::cerr << "Exception caught: " << ex.what() << std::endl;
    mainloop->quit(); 
  }

  if(stream)
  {
    memset(buffer, 0, 1000);
    stream->read_async(buffer, 1000, sigc::ptr_fun(&on_stream_read_async_ready));
  }
}

int main(int /* argc */, char** /* argv */)
{
  Gio::init();

  try
  {
    file = Gio::File::create_for_path("/etc/fstab");
    if(!file)
      std::cerr << "Gio::File::create_for_path() returned an empty RefPtr." << std::endl;
  }
  catch(const Glib::Exception& ex)
  {
    std::cerr << "Exception caught: " << ex.what() << std::endl; 
  }

  mainloop = Glib::MainLoop::create();

  file->read_async( sigc::ptr_fun(&on_file_read_async_ready) );
  mainloop->run();

  return 0;
}

