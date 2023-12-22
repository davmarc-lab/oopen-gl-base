FLAGS = 
LIBS = -lglfw -lGLU -lGL -lX11 -lfreetype -lXrandr -lpthread -lXi -ldl

glad = ./include/glad/glad.c
gladh = ./include/glad/glad.h
camera = ./Camera/Camera.cpp
camerah = ./Camera/Camera.hpp
game = ./Game/Game.cpp
gameh = ./Game/Game.cpp
win = ./Window/Window.cpp
winh = ./Window/Window.hpp
intsh = ./Shape/Mesh.hpp
transf = ./Shape/Model/Transform.cpp
transfh = ./Shape/Model/Transform.hpp
texture = ./Shape/Textures/Texture.cpp
textureh = ./Shape/Textures/Texture.hpp
cube = ./Shape/Cube.cpp
cubeh = ./Shape/Cube.hpp
scene = ./Scene/Scene.cpp
sceneh = ./Scene/Scene.hpp
shader = ./Shader/Shader.cpp
shaderh = ./Shader/Shader.hpp
herm = ./Math/Hermite.cpp
hermh = ./Math/Hermite.hpp
curve = ./Shape/Curve.cpp
curveh = ./Shape/Curve.hpp
libh = Lib.hpp
imageh = ./include/texture/stb_image.hpp
util = ./Utils/utils.cpp
utilh = ./Utils/utils.hpp

all: main.exe

# These lines are used for opengl.cpp
###---START---###
opengl: opengl.o shader.o glad.o
	g++ ${FLAGS} -o opengl.exe opengl.o shader.o glad.o ${LIBS}

opengl.o: main.cpp ${imageh} ${libh}
	gcc -c ${FLAGS} main.cpp -o opengl.o
###---END---###

main.exe: main.o window.o camera.o shader.o scene.o game.o transf.o texture.o cube.o glad.o
	g++ ${FLAGS} -o main.exe main.o window.o camera.o transf.o texture.o cube.o game.o glad.o shader.o scene.o ${LIBS}

main.o: main.cpp ${gladh} ${libh} ${intsh} ${gameh}
	gcc -c ${FLAGS} main.cpp -o main.o

window.o: ${win} ${winh} ${libh} ${gladh}
	gcc -c ${FLAGS} ${win} -o window.o

camera.o: ${camera} ${camerah} ${libh}
	gcc -c ${FLAGS} ${camera} -o camera.o

shape.o: ${shape} ${shapeh} ${libh} ${gladh} ${intsh} ${shaderh}
	gcc -c ${FLAGS} ${shape} -o shape.o

transf.o: ${transf} ${transfh} ${libh}
	gcc -c ${FLAGS} ${transf} -o transf.o

texture.o: ${texture} ${textureh} ${libh} ${imageh}
	gcc -c ${FLAGS} ${texture} -o texture.o

game.o: ${game} ${gameh}
	gcc -c ${FLAGS} ${game} -o game.o

shader.o: ${shader} ${shaderh} ${shapeh} ${gladh}
	gcc -c ${FLAGS} ${shader} -o shader.o

scene.o: ${scene} ${sceneh} ${libh} ${gladh}
	gcc -c ${FLAGS} ${scene} -o scene.o

cube.o: ${cube} ${cubeh} ${libh} ${gladh} ${intsh} ${shaderh}
	gcc -c ${FLAGS} ${cube} -o cube.o

curve.o: ${curve} ${curveh} ${libh} ${gladh} ${intsh} ${shaderh}
	gcc -c ${FLAGS} ${curve} -o curve.o

helper.o: ${util} ${utilh}
	gcc -c ${FLAGS} ${util} -o helper.o

glad.o: ${glad} ${gladh}
	gcc -c ${FLAGS} ${glad} -o glad.o

.PHONY:	clean

clean:
	-rm -f *.o *.exe

