################################################################################
#                                   MAKEFILE                                   #
################################################################################

OPENGL_LIBS =  -lglfw -lGLEW -lGL

LIBS = $(OPENGL_LIBS)

INC = -I /usr/include/


all: exc

stb_image.o: ./vendor/stb_image/stb_image.cpp ./vendor/stb_image/stb_image.h
	$(CXX) -c ./vendor/stb_image/stb_image.cpp $(INC)

Texture.o: Texture.cpp Texture.h Renderer.h
	$(CXX) -c Texture.cpp $(INC)

Shader.o: Shader.cpp Shader.h Renderer.h
	$(CXX) -c Shader.cpp $(INC)

VertexBufferLayout.o: VertexBufferLayout.cpp VertexBufferLayout.h
	$(CXX) -c VertexBufferLayout.cpp $(INC)

VertexArray.o: VertexArray.cpp VertexArray.h VertexBuffer.h VertexBufferLayout.h Renderer.h 
	$(CXX) -c VertexArray.cpp $(INC)

IndexBuffer.o: IndexBuffer.cpp IndexBuffer.h Renderer.h
	$(CXX) -c IndexBuffer.cpp $(INC)

VertexBuffer.o: VertexBuffer.cpp VertexBuffer.h Renderer.h
	$(CXX) -c VertexBuffer.cpp $(INC)

Renderer.o: Renderer.cpp Renderer.h VertexArray.h IndexBuffer.h Shader.h
	$(CXX) -c Renderer.cpp $(INC)

main.o: main.cpp Renderer.h VertexBuffer.h IndexBuffer.h VertexArray.h Shader.h Texture.h
	$(CXX) -c main.cpp $(INC)

exc : main.o Renderer.o VertexBuffer.o IndexBuffer.o VertexArray.o VertexBufferLayout.o Shader.o Texture.o stb_image.o 
	$(CXX) -o exc main.o Renderer.o VertexBuffer.o IndexBuffer.o VertexArray.o VertexBufferLayout.o Shader.o Texture.o stb_image.o $(LIBS) 

clean :
	rm -f *.o exc
	clear