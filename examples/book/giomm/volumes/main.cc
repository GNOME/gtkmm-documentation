#include <giomm.h>
#include <iostream>

int main(int argc, char** argv)
{
  Gio::init();

  try
  {
    Glib::RefPtr<Gio::VolumeMonitor> volume_monitor = Gio::VolumeMonitor::get();
    if(!volume_monitor)
      std::cerr << "Gio::VolumeMonitor::get() failed." << std::endl;

    typedef std::list< Glib::RefPtr<Gio::Drive> > type_list_drives;
    type_list_drives list_drives = volume_monitor->get_connected_drives();

    if(list_drives.empty())
      std::cout << "No drives are connected." << std::endl;

    for(type_list_drives::iterator iter = list_drives.begin(); iter != list_drives.end(); ++iter)
    {
      Glib::RefPtr<Gio::Drive> drive = *iter;
      std::cout << "drive: " << drive->get_name() << std::endl;

      //TODO: get the volumes in the drive.
    }
  }
  catch(const Glib::Exception& ex)
  {
    std::cerr << "Exception caught: " << ex.what() << std::endl; 
  }



  return 0;
}

