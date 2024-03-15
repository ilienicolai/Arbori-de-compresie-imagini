#NICOLAI Ilie - 313CB
build:
	gcc -g -o quadtree main.c build_img.c build_arb.c task1si2.c task3.c freemem.c
run:
	./quadtree
clean:
	rm quadtree
valgrind:
	valgrind --leak-check=yes --track-origins=yes ./quadtree