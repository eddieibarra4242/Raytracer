CMAKE = cmake

all:
	echo "Run 'make deps' to install dependencies."
	cd src && ${MAKE}

deps: glfw glm

glfw: mkf
	mkdir -p glfw/build
	cd glfw/build && ${CMAKE} -S.. -DCMAKE_BUILD_TYPE=Release
	cd glfw/build && ${MAKE} -j4
	cp glfw/build/src/libglfw3.a bin/
	cp -r glfw/include/GLFW include/

glm: mkf
	cp -r glm/glm include/

mkf:
	mkdir -p bin
	mkdir -p include

clean:
	rm -rf include
	rm -rf bin
	rm -rf debug
	cd glfw && git clean -fdx
