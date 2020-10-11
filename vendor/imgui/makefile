
################################################################################
#                                   MAKEFILE                                   #
################################################################################

OPENGL_LIBS =  -lglfw -lGLEW -lGL

LIBS = $(OPENGL_LIBS)

INC = -I /usr/include/

all: imgui.o imgui_impl_opengl3.o imgui_impl_glfw.o imgui_widgets.o imgui_draw.o imgui_demo.o

imgui.o: imgui.cpp imgui.h
	$(CXX) -c imgui.cpp $(INC)

imgui_impl_opengl3.o: imgui_impl_opengl3.cpp imgui_impl_opengl3.h
	$(CXX) -c imgui_impl_opengl3.cpp $(INC)

imgui_impl_glfw.o: imgui_impl_glfw.cpp imgui_impl_glfw.h
	$(CXX) -c imgui_impl_glfw.cpp $(INC)

imgui_widgets.o: imgui_widgets.cpp
	$(CXX) -c imgui_widgets.cpp $(INC)

imgui_draw.o: imgui_draw.cpp
	$(CXX) -c imgui_draw.cpp $(INC)

imgui_demo.o: imgui_demo.cpp
	$(CXX) -c imgui_demo.cpp $(INC)