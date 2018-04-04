CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -MMD
EXEC = chess
OBJECTS = main.o bishop.o board.o humanPlayer.o king.o knight.o pawn.o piece.o player.o queen.o rook.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
