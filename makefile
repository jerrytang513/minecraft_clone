CXX = g++
CXXFLAGS = -std=c++14
LDFLAGS = -lGL -lGLU -lglut
EXEC = a

MATH_DIR_OBJ = $(wildcard src/math/*.cc)
OTHER_OBJ = $(wildcard src/*.cc)

OBJECTS = $(MATH_DIR_OBJ:.cc=.o) $(OTHER_OBJ:.cc=.o) main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${LDFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm -rf ${OBJECTS} ${EXEC} ${DEPENDS}


