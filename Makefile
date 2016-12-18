
CC=clang++
INCLUDE=-I src/glm/glm -I src/
CFLAGS=-std=c++1y -stdlib=libc++ -O3 -Wall -Wextra

build: bin/graph

movie: bin/graph
	ffmpeg -i out/output_%05d.ppm -c:v libx264 out/out.mp4

bin/graph: obj/main.o obj/netppm.o obj/color.o
	${CC} obj/*.o -o bin/graph

obj/main.o: src/main.cpp
	${CC} ${CFLAGS} ${INCLUDE} -c src/main.cpp -o obj/main.o

obj/netppm.o: src/netppm/netppm.cpp
	${CC} ${CFLAGS} ${INCLUDE} -c src/netppm/netppm.cpp -o obj/netppm.o

obj/color.o: src/color/color.cpp
	${CC} ${CFLAGS} ${INCLUDE} -c src/color/color.cpp -o obj/color.o

clean:
	rm -f bin/graph
	rm -f obj/*.o
