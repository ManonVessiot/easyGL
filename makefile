################################################################################
 #    MAKEFILE
################################################################################

OPENGL_LIBS = -lglut -lGL -lGLU -lglfw

LIBS = $(OPENGL_LIBS)

INC = -I /usr/include/


all: exc

main.o: main.cpp main.h
	$(CXX) -c main.cpp $(INC)

exc : main.o
	$(CXX) -o exc main.o $(LIBS) 

clean :
	rm -f *.o exc
	clear