#include <gtkmm/application.h>
#include <glibmm/main.h>
#include <glibmm/iochannel.h>
#include <fcntl.h>
#include <iostream>

#include <unistd.h> //The SUN Forte compiler puts F_OK here.

//The SUN Forte compiler needs these for mkfifo:
#include <sys/types.h>
#include <sys/stat.h>

Glib::RefPtr<Gtk::Application> app;

int read_fd;
Glib::RefPtr<Glib::IOChannel> iochannel;

/*
  send to the fifo with:
  echo "Hello" > testfifo

  quit the program with:
  echo "Q" > testfifo
*/

// this will be our signal handler for read operations
// it will print out the message sent to the fifo
// and quit the program if the message was 'Q'.
bool MyCallback(Glib::IOCondition io_condition)
{
  if ((io_condition & Glib::IOCondition::IO_IN) != Glib::IOCondition::IO_IN)
  {
    std::cerr << "Invalid fifo response" << std::endl;
  }
  else
  {
   Glib::ustring buf;

   iochannel->read_line(buf);
   std::cout << buf;
   if (buf == "Q\n")
     app->quit();
  }
  return true;
}

int main(int argc, char *argv[])
{
  app = Gtk::Application::create("org.gtkmm.example");

  if (access("testfifo", F_OK) == -1)
  {
    // fifo doesn't exist - create it
    #ifndef DONT_HAVE_MKFIFO
    if (mkfifo("testfifo", 0666) != 0)
    {
      std::cerr << "error creating fifo" << std::endl;
      return -1;
    }
    #else
      std::cerr << "error creating fifo: This platform does not have mkfifo()"
          << std::endl;
    #endif //DONT_HAVE_MKFIFO
  }

  // Although we will only read from the fifo, we open it in read/write mode.
  // Due to a peculiarity with the poll() system call, used deep down in glib,
  // this small program will use all available CPU time, if the fifo is opened
  // as O_RDONLY. See a discussion on the gtkmm-list, e.g.
  // https://mail.gnome.org/archives/gtkmm-list/2015-September/msg00034.html
  // and the link from there to stackoverflow.
  read_fd = open("testfifo", O_RDWR);
  if (read_fd == -1)
  {
    std::cerr << "error opening fifo" << std::endl;
    return -1;
  }

  // connect the signal handler
  Glib::signal_io().connect(
    [](Glib::IOCondition io_condition){ return MyCallback(io_condition); },
    read_fd, Glib::IOCondition::IO_IN);

  // Creates a iochannel from the file descriptor
  iochannel = Glib::IOChannel::create_from_fd(read_fd);

  // and last but not least - run the application main loop
  app->hold(); // keep the application running without a window
  app->run(argc, argv);

  // now remove the temporary fifo
  if(unlink("testfifo"))
    std::cerr << "error removing fifo" << std::endl;

  return 0;
}
