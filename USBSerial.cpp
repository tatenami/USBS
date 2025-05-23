#include "USBSerial.hpp"
#include <cstdio>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

USBSerial::USBSerial(char *dev_file) {
  dev_file_ = dev_file;

  tio_config_.c_cflag += CREAD;  // 受信有効化
  tio_config_.c_cflag += CLOCAL; 
  tio_config_.c_cflag += CS8;    // データ長を 8Bit に

  cfsetispeed(&tio_config_, baud_rate_); // 受信速度設定
  cfsetospeed(&tio_config_, baud_rate_); // 送信速度設定

  cfmakeraw(&tio_config_);

  fd_ = open(dev_file, O_RDWR);
  if (fd_ < 0) {
    available_ = false;
  }
  else {
    available_ = true;
  }

  // 設定を反映
  tcsetattr(fd_, TCSANOW, &tio_config_);
}

bool USBSerial::available() {
  return available_;
}

bool USBSerial::sendData(void *buf, int size) {
  int len = write(fd_, buf, size);
  
  if (len < 0) {
    return false;
  }
  else {
    return true;
  }
}


bool USBSerial::receiveData(void *buf, int size) {
  int len = read(fd_, buf, size);

  if (len < 0) {
    return false;
  }
  else {
    return true;
  }
}

