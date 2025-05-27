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

void USBSerial::setLowLatency() {
  // カーネルのデータ受信時の待ち時間を無効化
  serial_struct serial_setting;
  ioctl(fd_, TIOCGSERIAL, &serial_setting);
  serial_setting.flags |= ASYNC_LOW_LATENCY;
  ioctl(fd_, TIOCSSERIAL, &serial_setting);
}

int USBSerial::getBufSize() {
  int available_size = 0;
  ioctl(fd_, FIONREAD, &available_size);
  return available_size;
}

bool USBSerial::available() {
  return available_;
}

bool USBSerial::sendData(void *buf, int size) {
  int len = write(fd_, buf, size);
  return len >= 0;
}


bool USBSerial::receiveData(void *buf, int size) {
  int len = read(fd_, buf, size);
  return len >= 0;
}

