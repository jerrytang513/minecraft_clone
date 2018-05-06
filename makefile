CXX = g++
INCLUDES = /usr/include/libdrm
CXXFLAGS = -std=c++14
LDFLAGS = -lGLEW -lGL -lGLU -lglfw -ldl -lrt -ldrm -lxcb-glx -lX11-xcb -lpthread -lXdamage -lm -lxcb-glx -lxcb-dri2 -lxcb-dri3 -lxcb-present -lxcb-sync -lxshmfence -lXxf86vm -lXfixes -lXext -lXau -lxcb -lXdmcp -lXinerama -lXcursor -lX11 -lXrandr -lXi
EXEC = a

MATH_DIR_OBJ = $(wildcard src/math/*.cc)
OTHER_OBJ = $(wildcard src/*.cc)
GRAPHICS_DIR_OBJ = $(wildcard src/graphics/*.cc)
GRAPHICS_ASSET_DIR_OBJ = $(wildcard src/graphics/asset/*.cc)

OBJECTS = $(MATH_DIR_OBJ:.cc=.o) $(OTHER_OBJ:.cc=.o) $(GRAPHICS_DIR_OBJ:.cc=.o) $(GRAPHICS_ASSET_DIR_OBJ:.cc=.o) main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC} : ${OBJECTS}
	${CXX} -I${INCLUDES} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${LDFLAGS}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm -rf ${OBJECTS} ${EXEC} ${DEPENDS}


