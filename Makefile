all:
	gcc genpoints.c -o genpoints -lm
	g++ closest.cpp -o closest -lm
	g++ closest_quadratico.cpp -o closest_quadratico -lm

gen:
	./genpoints 10000

run:
	time ./closest input.txt
	time ./closest_quadratico input.txt
	
clean:
	rm -f genpoints;
	rm -f closest_quadratico;
	rm -f closest;
	rm -f input.txt;

