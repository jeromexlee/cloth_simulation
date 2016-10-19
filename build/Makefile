all: 
	g++ -c ../utils/Vector3D.cpp
	g++ -c ../utils/matrix44.cpp
	g++ -c ../utils/matrix.cpp
	g++ -c ../utils/cube.cpp
	g++ -c ../src/skeleton.cpp
	g++ -c ../src/fowardkinematics.cpp
	g++ -c ../src/animation.cpp
	g++ -c ../src/cloth_src/particle.cpp
	g++ -c ../src/cloth_src/spring.cpp
	g++ -c ../src/cloth.cpp
	g++ -c ../src/main.cpp
	g++ -framework OpenGL -framework GLUT Vector3D.o matrix44.o skeleton.o cube.o matrix.o fowardkinematics.o animation.o particle.o spring.o cloth.o main.o -o simulation

clean:
	rm *o simulation