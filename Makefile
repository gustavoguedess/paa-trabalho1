all:
	gcc genpoints.c -o genpoints -lm
	g++ closest.cpp -o closest -lm

run:
	./genpoints 10
	./closest input.txt
	
clean:
	rm -f genpoints;
