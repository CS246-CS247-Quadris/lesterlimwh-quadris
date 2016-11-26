CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = quadris
OBJECTS = level.o iblock.o jblock.o lblock.o oblock.o sblock.o zblock.o grid.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
