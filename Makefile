CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = quadris
OBJECTS = level.o iblock.o jblock.o lblock.o oblock.o sblock.o tblock.o zblock.o grid.o window.o graphics.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
