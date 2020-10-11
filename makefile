################################################################################
#                                   MAKEFILE                                   #
################################################################################

OPENGL_LIBS =  -lglfw -lGLEW -lGL

LIBS = $(OPENGL_LIBS)

INC = -I /usr/include/

VENDOR_O = ./vendor/stb_image/stb_image.o ./vendor/imgui/imgui.o ./vendor/imgui/imgui_impl_glfw.o ./vendor/imgui/imgui_impl_opengl3.o ./vendor/imgui/imgui_widgets.o ./vendor/imgui/imgui_draw.o ./vendor/imgui/imgui_demo.o

all: exc

TESTS = Test.o TestClearColor.o TestTriangle.o TestSquare.o TestSquareAnimatedColor.o TestTexture2D.o TestMVP.o TestCube.o #TestTemplate.o

#TestTemplate.o: ./tests/TestTemplate.cpp ./tests/TestTemplate.h ./tests/Test.h
#	$(CXX) -c ./tests/TestTemplate.cpp $(INC)

Test.o: ./tests/Test.cpp ./tests/Test.h
	$(CXX) -c ./tests/Test.cpp $(INC)

TestClearColor.o: ./tests/TestClearColor.cpp ./tests/TestClearColor.h ./tests/Test.h
	$(CXX) -c ./tests/TestClearColor.cpp $(INC)

TestTriangle.o: ./tests/TestTriangle.cpp ./tests/TestTriangle.h ./tests/Test.h
	$(CXX) -c ./tests/TestTriangle.cpp $(INC)

TestSquare.o: ./tests/TestSquare.cpp ./tests/TestSquare.h ./tests/Test.h
	$(CXX) -c ./tests/TestSquare.cpp $(INC)

TestSquareAnimatedColor.o: ./tests/TestSquareAnimatedColor.cpp ./tests/TestSquareAnimatedColor.h ./tests/Test.h
	$(CXX) -c ./tests/TestSquareAnimatedColor.cpp $(INC)

TestTexture2D.o: ./tests/TestTexture2D.cpp ./tests/TestTexture2D.h ./tests/Test.h
	$(CXX) -c ./tests/TestTexture2D.cpp $(INC)

TestMVP.o: ./tests/TestMVP.cpp ./tests/TestMVP.h ./tests/Test.h
	$(CXX) -c ./tests/TestMVP.cpp $(INC)

TestCube.o: ./tests/TestCube.cpp ./tests/TestCube.h ./tests/Test.h
	$(CXX) -c ./tests/TestCube.cpp $(INC)




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

exc : main.o Renderer.o VertexBuffer.o IndexBuffer.o VertexArray.o VertexBufferLayout.o Shader.o Texture.o $(TESTS) $(VENDOR_O)
	$(CXX) -o exc main.o Renderer.o VertexBuffer.o IndexBuffer.o VertexArray.o VertexBufferLayout.o Shader.o Texture.o $(TESTS) $(VENDOR_O) $(LIBS) 

clean :
	rm -f *.o
	clear