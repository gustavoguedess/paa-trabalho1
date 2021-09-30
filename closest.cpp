/**************************************************************
 *                                                            *
 *      Trabalho 1 de Projeto e Análise de Algoritmo          *
 *      Escrito por:                                          *
 *          Gustavo Inacio Pereira Guedes - 2088860           *
 *          Franziska Romani Furtado - 2024551                *
 *          Rafael Rosa da Silva - 2024551                    *
 *                                                            *
 * ************************************************************
*/

#include<stdio.h>
#include<vector>

#define MAX 112345

using namespace std;

struct Point{
    double x,y;
    Point(double x, double y):x(x),y(y){}
};

int n_points;

    
vector<Point> read_points(char *file_name){
    vector<Point> vector_points;
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL)
	{
		fprintf(stderr, "Falha ao criar input.txt.\n");
		return vector_points;
	}
    fscanf(fp,"%d", &n_points);
    for(int i=0; i<n_points; i++){
        double x, y;
        fscanf(fp,"%lf %lf", &x, &y);
        vector_points.push_back(Point(x,y));
    }

    fclose(fp); 
    return vector_points;
}

int main(int argc, char *argv[]){
    if (argc != 2) {
		fprintf(stderr, "Uso: %s input.txt\n", argv[0]);
		return 1;
	}
    

    vector<Point> points = read_points(argv[1]);
    if(points.size()==0){
        return 1;
    }

    //Teste para conferir se está funcionando
    for(auto &p:points){
        printf("Ponto: (%lf,%lf)\n", p.x, p.y);
    }
    

    return 0;
}