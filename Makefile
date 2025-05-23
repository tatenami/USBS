SRCS = test.cpp
LIBSRCS = USBSerial.cpp
TARGET = ${SRCS:.cpp=}

${TARGET}: ${SRCS}
	g++ -o $@ $< ${LIBSRCS}


clean:
	rm ${TARGET}