CPP = g++
OBJDUMP = objdump

CFLAGS = -Wall -Wextra -Werror -I../include -std=c++23

LINK_FLAGS = -L../bin -lglfw3 -lGLEW -lGL -lm

CFLAGS += -ggdb
LINK_FLAGS += -ggdb

# CFLAGS += -O2 -DNDEBUG
# LINK_FLAGS += -O2

OUTPUT_NAME = raytracer

OBJ_FILES = main.o Window.o Bitmap.o Camera.o shapes/Sphere.o shapes/Plane.o
OBJ_FILES += Scene.o Renderer.o materials/Lambertian.o materials/Metal.o
OBJ_FILES += materials/Dielectric.o materials/Emissive.o sas/AABB.o sas/BVH.o
OBJ_FILES += log.o

all: mkdirs $(OBJ_FILES)
	$(CPP) $(OBJ_FILES:%=../bin/int/%) -o ../bin/$(OUTPUT_NAME) $(LINK_FLAGS)
	$(OBJDUMP) -dCM intel ../bin/$(OUTPUT_NAME) > ../debug/$(OUTPUT_NAME).dump

%.o: %.cpp
	$(CPP) -c $(CFLAGS) $< -o ../bin/int/$@

mkdirs:
	mkdir -p ../debug
	mkdir -p ../bin/int/shapes
	mkdir -p ../bin/int/materials
	mkdir -p ../bin/int/sas
