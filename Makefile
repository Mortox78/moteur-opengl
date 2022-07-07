MAKEFLAGS+=--no-builtin-rules --no-builtin-variables

CXXFLAGS=-O0 -g -Wall -MMD -Wno-unused-function
CXXFLAGS+=-Iinclude
CFLAGS=$(CXXFLAGS)
CC=gcc
CXX=g++

SRCSC = $(wildcard src/*.c)
SRCSCXX = $(wildcard src/*.cpp)

LDLIBS=-Llib -lglfw -lGL -lGLU -ldl -lSDL2
OBJS = $(SRCSC:.c=.o)
OBJS+= $(SRCSCXX:.cpp=.o)

DEPS=$(OBJS:.o=.d)

.PHONY: all clean

all: bin/gl

-include $(DEPS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

bin/gl: $(OBJS)
	$(CXX) -o $@ $(LDFLAGS) $^ $(LDLIBS)

clean:
	rm -f $(OBJS) $(DEPS) bin/gl
