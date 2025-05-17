SRCS = simple.cpp
TARGET = ${SRCS:.cpp=}

${TARGET}: ${SRCS}
	g++ -o $@ $<


clean:
	rm ${TARGET}