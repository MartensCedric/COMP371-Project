default: exec

CFLAGS = -g -Wall
LIBS = -lGL -lX11 -lGLEW `pkg-config glfw3 --static --libs`
OBJFILES = Shader.o CabinModel.o ConeModel.o StonehengeModel.o TreeModel.o WaterModel.o FastNoise.o Terrain.o Skybox.o LoadTexture.o WorldModel.o UnitCubeModel.o SimpleModel.o Model.o Camera.o

exec: Main.cpp $(OBJFILES)
	g++ $(CFLAGS) -o exec Main.cpp $(OBJFILES) $(LIBS)

FastNoise.o: ../ThirdParty/FastNoise.cpp
	g++ -c $(CFLAGS) $< $(LIBS)

%.o: %.cpp
	g++ -c $(CFLAGS) $< $(LIBS)

clean :
	rm *.o
