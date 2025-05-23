#ifndef USB_SERIAL_H
#define USB_SERIAL_H

#include <cstdio>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>


class USBSerial {
 private:
  int fd_;
  int baud_rate_{B115200};
  termios tio_config_;
  std::string dev_file_;
  bool available_;

 public:
  USBSerial(char* dev_file);
  // void setBaudRate();
  bool available();
  bool sendData(void *buf, int size);
  bool receiveData(void *buf, int size);
  
  template <typename T>
  bool sendData(T *buf) {
    int len = write(fd_, buf, sizeof(T));
    
    if (len < 0) {
      return false;
    }
    else {
      return true;
    }
  }

  template <typename T>
  bool receiveData(T *buf) {
    int len = read(fd_, buf, sizeof(T));

    if (len < 0) {
      return false;
    }
    else {
      return true;
    }
  }
};

#endif // USB_SERIAL_H