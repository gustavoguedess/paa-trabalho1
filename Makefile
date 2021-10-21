all:
	gcc genpoints.c -o genpoints -lm
	g++ closest.cpp -o closest -lm

run:
	./closest input.txt
	
clean:
	rm -f genpoints;
	rm -f closest;
	rm -f input.txt;

