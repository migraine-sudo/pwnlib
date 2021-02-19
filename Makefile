# Makefile for Pwnlib
CROSS =
CC := $(CROSS)gcc
CXX := $(CROSS)g++
DEBUG = -D__DEBUG__
CFLAGS = $(DEBUG) --std=c++11 -w
RM = rm -rf

VERSION = 0.0.2
TARGET = pwn.$(VERSION)
OBJS = main.cc
INCLUDE = -I include/
LIB = lib/libyaml-cpp.a
#PWN
$(TARGET): 
	$(CXX) $(OBJS) $(CFLAGS) -o $@ $(INCLUDE) $(LIB)

#Demo
demo_auto_debug: demo_auto.cc
	$(CXX) demo_auto.cc -o auto_pwn --std=c++11 -D__DEBUG__ -w

demo_auto_release: demo_auto.cc
	$(CXX) demo_auto.cc -o auto_pwn --std=c++11 -w

demo_half_auto_debug: demo_half_auto.cc
	$(CXX) demo_half_auto.cc -o half_auto_pwn --std=c++11 -D__DEBUG__ -w


clean:
	$(RM) $(TARGET) *.o
