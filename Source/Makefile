default: exec

CFLAGS = -g -Wall
LIBS = -lGL -lX11 -lGLEW `pkg-config glfw3 --static --libs`
OBJFILES = FastNoise.o Terrain.o Skybox.o LoadTexture.o SphereModel.o PlaneModel.o AxesModel.o GridModel.o WorldModel.o UnitCubeModel.o SimpleModel.o Model.o Shader.o Camera.o

exec: 371A1.cpp $(OBJFILES)
	g++ $(CFLAGS) -o exec 371A1.cpp $(OBJFILES) $(LIBS)

FastNoise.o: ../ThirdParty/FastNoise.cpp
	g++ -c $(CFLAGS) $< $(LIBS)

%.o: %.cpp
	g++ -c $(CFLAGS) $< $(LIBS)

clean :
	rm *.o
