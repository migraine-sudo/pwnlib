# Makefile for Pwnlib

CC := gcc
CXX := g++

#PWN
pwn: main.cc
	$(CXX) main.cc -o pwn --std=c++11 -D__DEBUG__ -w	

#Demo
demo_auto_debug: demo_auto.cc
	$(CXX) demo_auto.cc -o auto_pwn --std=c++11 -D__DEBUG__ -w

demo_auto_release: demo_auto.cc
	$(CXX) demo_auto.cc -o auto_pwn --std=c++11 -w

demo_half_auto_debug: demo_half_auto.cc
	$(CXX) demo_half_auto.cc -o half_auto_pwn --std=c++11 -D__DEBUG__ -w


clean:
	rm *.o pwn auto_pwn half_auto_pwn
