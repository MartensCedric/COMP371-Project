default: exec

CFLAGS = -g -Wall
LIBS = -lGL -lX11 -lGLEW `pkg-config glfw3 --static --libs`
OBJFILES = LoadTexture.o PlaneModel.o WorldModel.o SphereModel.o GridModel.o AxesModel.o UnitCubeModel.o SimpleModel.o Model.o Shader.o Camera.o

exec: 371A1.cpp $(OBJFILES)
	g++ $(CFLAGS) -o exec 371A1.cpp $(OBJFILES) $(LIBS)

%.o: %.cpp
	g++ -c $(CFLAGS) $< $(LIBS)

clean :
	rm *.o