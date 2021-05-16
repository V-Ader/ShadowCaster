CXX = g++

SRC_DIR = src
SOURCES = main.cpp player.cpp window.cpp line.cpp system.cpp

INCLUDE_DIR = include
HEADERS = player.hpp window.hpp line.hpp system.hpp

SFML_DIR = <sfml path>

EXEC_NAME = ShadowCaster.exe
BUILD_DIR = build
BIN_DIR = bin

OBJ = $(SOURCES:%.cpp=${BUILD_DIR}/%.o)
INCLUDES = $(HEADERS:%=${INCLUDE_DIR}/%)

COMP_FLAGS = -c -I ${INCLUDE_DIR} -Wall -I${SFML_DIR}/include
LINK_FLAGS = -L${SFML_DIR}/lib -lsfml-graphics -lsfml-window -lsfml-system 

${BUILD_DIR}/%.o: ${SRC_DIR}/%.cpp ${INCLUDES}
	${CXX} -o $@ $< ${COMP_FLAGS}

${BIN_DIR}/${EXEC_NAME}: ${OBJ}
	${CXX} -o $@ $^ ${LINK_FLAGS}

all: ${BIN_DIR}/${EXEC_NAME}

clean:
	-${RM} -rf ${BUILD_DIR}/*

