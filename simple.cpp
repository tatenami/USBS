#include <cstdint>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  uint8_t msg[] = "serial port open...\n";
  // uint8_t buf[255];

  char *serial_port = argv[1];
  int fd;
  termios port;
  int baud_rate = B115200;

  fd = open(serial_port, O_RDWR);
  if (fd < 0)  {
    printf("open error\n");
    return -1;
  }

  port.c_cflag += CREAD;
  port.c_cflag += CLOCAL;
  port.c_cflag += CS8;
  port.c_cflag += 0;
  port.c_cflag += 0;

  cfsetospeed(&port, baud_rate);
  cfsetispeed(&port, baud_rate);

  cfmakeraw(&port);

  tcsetattr(fd, TCSANOW, &port);

  int int_buf;

  while (1) {
    int len = read(fd, &int_buf, sizeof(int));
    if (len > 0) {
      printf("size: %d val: %d\n", len, int_buf);
    }
  }

  close(fd);

  return 0;
}