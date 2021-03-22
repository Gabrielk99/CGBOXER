CC =g++
CFLAGS =-lGL\
		 -lGLU\
		 -lglut\

all: trabalhocg

trabalhocg: *.cpp
	$(CC) -o  trabalhocg *.cpp $(CFLAGS)
clean:
	rm -rf  trabalhocg
