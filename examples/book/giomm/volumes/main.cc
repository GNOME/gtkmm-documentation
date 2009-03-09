#include <giomm.h>
#include <iostream>

int main(int /* argc */, char** /* argv */)
{
  Gio::init();

  try
  {
    Glib::RefPtr<Gio::VolumeMonitor> volume_monitor = Gio::VolumeMonitor::get();
    if(!volume_monitor)
      std::cerr << "Gio::VolumeMonitor::get() failed." << std::endl;

    //Get the drives:
    typedef std::list< Glib::RefPtr<Gio::Drive> > type_list_drives;
    type_list_drives list_drives = volume_monitor->get_connected_drives();

    if(list_drives.empty())
      std::cout << "No drives are connected." << std::endl;

    for(type_list_drives::iterator iter = list_drives.begin(); iter != list_drives.end(); ++iter)
    {
      Glib::RefPtr<Gio::Drive> drive = *iter;
      std::cout << "Drive: " << drive->get_name() << std::endl;

      //Get the volumes in the drive:
      typedef std::list< Glib::RefPtr<Gio::Volume> > type_list_volumes;
      type_list_volumes list_volumes = volume_monitor->get_volumes();

      for(type_list_volumes::iterator iter = list_volumes.begin(); iter != list_volumes.end(); ++iter)
      {
        Glib::RefPtr<Gio::Volume> volume = *iter;
        std::cout << "  Volume: " << volume->get_name() << std::endl;
      }
    }
  }
  catch(const Glib::Exception& ex)
  {
    std::cerr << "Exception caught: " << ex.what() << std::endl; 
  }



  return 0;
}

