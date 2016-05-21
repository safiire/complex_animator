
CC=clang++
INCLUDE=-I src/glm/glm -I src/
CFLAGS=-std=c++1y -stdlib=libc++ -O3 -Wall -Wextra

build: bin/graph

bin/graph: obj/main.o obj/netppm.o obj/maybe.o
	${CC} obj/*.o -o bin/graph

obj/main.o: src/main.cpp
	${CC} ${CFLAGS} ${INCLUDE} -c src/main.cpp -o obj/main.o

obj/maybe.o: src/maybe/maybe.cpp
	${CC} ${CFLAGS} ${INCLUDE} -c src/maybe/maybe.cpp -o obj/maybe.o

obj/netppm.o: src/netppm/netppm.cpp
	${CC} ${CFLAGS} ${INCLUDE} -c src/netppm/netppm.cpp -o obj/netppm.o

clean:
	rm -f bin/graph
	rm -f obj/*.o
