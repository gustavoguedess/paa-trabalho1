all:
	gcc genpoints.c -o genpoints -lm
	g++ closest.cpp -o closest -lm
	
run:
	time ./closest input.txt
	time ./closest_quadratico input.txt
	
clean:
	rm -f genpoints;
	rm -f closest_quadratico;
	rm -f closest;
	rm -f input.txt;

