################################################################################
#                                   MAKEFILE                                   #
################################################################################

OPENGL_LIBS =  -lglfw -lGLEW -lGL

LIBS = $(OPENGL_LIBS)

INC = -I /usr/include/

VENDOR_O = ../vendor/stb_image/stb_image.o ../vendor/imgui/imgui.o ../vendor/imgui/imgui_impl_glfw.o ../vendor/imgui/imgui_impl_opengl3.o \
	../vendor/imgui/imgui_widgets.o ../vendor/imgui/imgui_draw.o ../vendor/imgui/imgui_demo.o

LOCAL = Renderer.o VertexBuffer.o IndexBuffer.o VertexArray.o VertexBufferLayout.o Shader.o Texture.o TextureManager.o ShaderManager.o

all: $(LOCAL)

ShaderManager.o: ShaderManager.cpp ShaderManager.h
	$(CXX) -c ShaderManager.cpp $(INC)

TextureManager.o: TextureManager.cpp TextureManager.h
	$(CXX) -c TextureManager.cpp $(INC)

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

clean :
	rm -f *.o