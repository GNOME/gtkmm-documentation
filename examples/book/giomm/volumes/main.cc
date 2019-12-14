#include <giomm.h>
#include <iostream>

int main(int /* argc */, char** /* argv */)
{
  Gio::init();

  try
  {
    auto volume_monitor = Gio::VolumeMonitor::get();
    if(!volume_monitor)
      std::cerr << "Gio::VolumeMonitor::get() failed." << std::endl;

    //Get the drives:
    for(const auto& drive : volume_monitor->get_connected_drives())
    {
      std::cout << "Drive: " << drive->get_name() << std::endl;

      //Get the volumes in the drive:
      //TODO: This doesn't seem to be per-drive:
      for(const auto& volume : volume_monitor->get_volumes())
      {
        std::cout << "  Volume: " << volume->get_name() << std::endl;
      }
    }
  }
  catch(const Glib::Error& ex)
  {
    std::cerr << "Exception caught: " << ex.what() << std::endl;
  }



  return 0;
}

