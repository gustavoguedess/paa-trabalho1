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
#include<math.h>

#define MAX 112345

using namespace std;

struct Point{
    double x,y;
    Point(double x, double y):x(x),y(y){}
    void to_string(){printf("%lf %lf", x, y);}
};
struct Par{
    Point a, b;
    double dist;
    Par(Point a, Point b):a(a),b(b){
        dist = sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)); //Distância Euclidiana
    }
    void to_string(){
        printf("%lf ", dist);
        a.to_string();
        printf(" ");
        b.to_string();
    }
};

Par menor_par(Par a, Par b){
    if(a.dist<b.dist) return a;
    return b;
}

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


double par_mais_proximo(){
    return 1;
}


int main(int argc, char *argv[]){
    if (argc != 2) {
		fprintf(stderr, "Uso: %s input.txt\n", argv[0]);
		return 1;
	}
    

    vector<Point> points = read_points(argv[1]);
    if(points.size()<2){
        return 1;
    }

    //Teste para conferir se está funcionando
    for(auto &p:points){
        printf("Ponto: (%lf,%lf)\n", p.x, p.y);
    }
    
    Par menor = Par(points[0],points[1]);
    for(int i=0; i<n_points; i++)
        for(int j=i+1; j<n_points; j++)
            menor = menor_par(menor, Par(points[i],points[j]));
    
    menor.to_string();
    printf("\n");

    return 0;
}