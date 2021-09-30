all:
	gcc genpoints.c -o genpoints -lm
	g++ closest.cpp -o closest -lm

clean:
	rm -f genpoints;
