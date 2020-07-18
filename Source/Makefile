default: exec

exec: 371A1.cpp GridModel.o AxesModel.o GroupModel.o NormalsModel.o UnitCubeModel.o SimpleModel.o Model.o Shader.o Camera.o
	g++ -g -Wall -o exec 371A1.cpp GridModel.o AxesModel.o NormalsModel.o GroupModel.o SimpleModel.o UnitCubeModel.o Model.o Shader.o Camera.o -lGL -lGLEW -lglfw

UnitCubeModel.o: UnitCubeModel.cpp
	g++ -c -g -Wall UnitCubeModel.cpp -lGL -lGLEW -lglfw

GroupModel.o: GroupModel.cpp
	g++ -c -g -Wall GroupModel.cpp -lGL -lGLEW -lglfw

GridModel.o: GridModel.cpp
	g++ -c -g -Wall GridModel.cpp -lGL -lGLEW -lglfw

AxesModel.o: AxesModel.cpp
	g++ -c -g -Wall AxesModel.cpp -lGL -lGLEW -lglfw

SimpleModel.o: SimpleModel.cpp
	g++ -c -g -Wall SimpleModel.cpp -lGL -lGLEW -lglfw

Model.o: Model.cpp
	g++ -c -g -Wall Model.cpp -lGL -lGLEW -lglfw
	
NormalsModel.o : NormalsModel.cpp
	g++ -c -g -Wall NormalsModel.cpp -lGL -lGLEW -lglfw

Shader.o: Shader.cpp
	g++ -c -g -Wall Shader.cpp -lGL -lGLEW -lglfw

Camera.o: Camera.cpp
	g++ -c -g -Wall Camera.cpp -lGL -lGLEW -lglfw

clean :
	rm *.o