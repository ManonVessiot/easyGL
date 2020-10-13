################################################################################
#                                   MAKEFILE                                   #
################################################################################

OPENGL_LIBS =  -lglfw -lGLEW -lGL

LIBS = $(OPENGL_LIBS)

INC = -I /usr/include/

VENDOR_O = ../vendor/stb_image/stb_image.o ../vendor/imgui/imgui.o ../vendor/imgui/imgui_impl_glfw.o ../vendor/imgui/imgui_impl_opengl3.o \
	../vendor/imgui/imgui_widgets.o ../vendor/imgui/imgui_draw.o ../vendor/imgui/imgui_demo.o


TESTS = Test.o TestClearColor.o TestTriangle.o TestSquare.o TestSquareAnimatedColor.o TestTexture2D.o TestMVP.o TestCube.o \
	TestBatching.o TestBatchingDynamic.o TestModel.o #TestTemplate.o

all: $(TESTS)

Test.o: Test.cpp Test.h
	$(CXX) -c Test.cpp $(INC)

TestClearColor.o: TestClearColor.cpp TestClearColor.h Test.h
	$(CXX) -c TestClearColor.cpp $(INC)

TestTriangle.o: TestTriangle.cpp TestTriangle.h Test.h
	$(CXX) -c TestTriangle.cpp $(INC)

TestSquare.o: TestSquare.cpp TestSquare.h Test.h
	$(CXX) -c TestSquare.cpp $(INC)

TestSquareAnimatedColor.o: TestSquareAnimatedColor.cpp TestSquareAnimatedColor.h Test.h
	$(CXX) -c TestSquareAnimatedColor.cpp $(INC)

TestTexture2D.o: TestTexture2D.cpp TestTexture2D.h Test.h
	$(CXX) -c TestTexture2D.cpp $(INC)

TestMVP.o: TestMVP.cpp TestMVP.h Test.h
	$(CXX) -c TestMVP.cpp $(INC)

TestCube.o: TestCube.cpp TestCube.h Test.h
	$(CXX) -c TestCube.cpp $(INC)

TestBatching.o: TestBatching.cpp TestBatching.h Test.h
	$(CXX) -c TestBatching.cpp $(INC)

TestBatchingDynamic.o: TestBatchingDynamic.cpp TestBatchingDynamic.h Test.h
	$(CXX) -c TestBatchingDynamic.cpp $(INC)

TestModel.o: TestModel.cpp TestModel.h Test.h
	$(CXX) -c TestModel.cpp $(INC)

#TestTemplate.o: TestTemplate.cpp TestTemplate.h Test.h
#	$(CXX) -c TestTemplate.cpp $(INC)

clean :
	rm -f *.o
	clear