#ifndef USB_SERIAL_H
#define USB_SERIAL_H

#include <cstdio>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/serial.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>


class USBSerial {
 private:
  int fd_;
  int baud_rate_{B115200};
  bool available_;
  termios tio_config_;
  std::string dev_file_;

 private:
  void setLowLatency();

 public:
  USBSerial(char* dev_file);
  // void setBaudRate();
  int getBufSize();
  bool available();
  bool sendData(void *buf, int size);
  bool receiveData(void *buf, int size);
  
  template <typename T>
  bool sendData(T *buf) {
    int len = write(fd_, buf, sizeof(T));
    return len >= 0;
  }

  template <typename T>
  bool receiveData(T *buf) {
    int len = read(fd_, buf, sizeof(T));
    return len >= 0;
  }
};

#endif // USB_SERIAL_H