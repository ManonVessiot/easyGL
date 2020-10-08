################################################################################
#                                   MAKEFILE                                   #
################################################################################

OPENGL_LIBS =  -lglfw -lGLEW -lGL

LIBS = $(OPENGL_LIBS)

INC = -I /usr/include/


all: exc


Shader.o: Shader.cpp Shader.h
	$(CXX) -c Shader.cpp $(INC)

VertexBufferLayout.o: VertexBufferLayout.cpp VertexBufferLayout.h
	$(CXX) -c VertexBufferLayout.cpp $(INC)

VertexArray.o: VertexArray.cpp VertexArray.h
	$(CXX) -c VertexArray.cpp $(INC)

IndexBuffer.o: IndexBuffer.cpp IndexBuffer.h
	$(CXX) -c IndexBuffer.cpp $(INC)

VertexBuffer.o: VertexBuffer.cpp VertexBuffer.h Renderer.h
	$(CXX) -c VertexBuffer.cpp $(INC)

Renderer.o: Renderer.cpp Renderer.h
	$(CXX) -c Renderer.cpp $(INC)

main.o: main.cpp main.h Renderer.h VertexBuffer.h IndexBuffer.h
	$(CXX) -c main.cpp $(INC)

exc : main.o Renderer.o VertexBuffer.o IndexBuffer.o VertexArray.o VertexBufferLayout.o Shader.o
	$(CXX) -o exc main.o Renderer.o VertexBuffer.o IndexBuffer.o VertexArray.o VertexBufferLayout.o Shader.o $(LIBS) 

clean :
	rm -f *.o exc
	clear