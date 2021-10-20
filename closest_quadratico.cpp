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
#include<algorithm>
#include <chrono>

#define MAX 112345
#define INF 1123456
using namespace std;
using namespace std::chrono;

struct Point{
    double x,y;
    Point(double x, double y):x(x),y(y){}
    void to_string(bool end_line=false){printf("%lf %lf%s", x, y,end_line?"\n":"");}
    bool operator<(Point a) const{
        if(x<a.x)return true;
        return false;
    }

};
struct Par{
    Point a, b;
    double dist;
    Par(Point a, Point b):a(a),b(b) {dist = sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}
    Par():a(Point(-INF, -INF)),b(Point(INF,INF)) {dist = sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}
    void to_string(){
        printf("%lf ", dist);
        a.to_string();
        printf(" ");
        b.to_string();
        printf("\n");
    }
};

Par menor_par(Par a, Par b){
    if(a.dist<b.dist) return a;
    return b;
}

int n_points;

// ==================== Solução Quadrática =====================
Par minDistBruto(Point* points, int n){
    Par menor = Par(points[0],points[1]);   

    for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++)
            menor = menor_par(menor, Par(points[i],points[j]));
    return menor;
}
// =============================================================

// ---------------- LEITURA DO ARQUIVO --------------------
Point* read_points(char *file_name){
    Point* vector_points;
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL)
	{
		fprintf(stderr, "Falha ao criar input.txt.\n");
		return vector_points;
	}
    fscanf(fp,"%d", &n_points);
    vector_points = (Point*)malloc(n_points*sizeof(Point));

    for(int i=0; i<n_points; i++){
        double x, y;
        fscanf(fp,"%lf %lf", &x, &y);
        vector_points[i]=Point(x,y);
    }

    fclose(fp); 
    return vector_points;
}
// ------------------------------------------------------


int main(int argc, char *argv[]){
    double seconds;

    if (argc != 2) {
		fprintf(stderr, "Uso: %s input.txt\n", argv[0]);
		return 1;
	}
    

    Point* points = read_points(argv[1]);
    if(n_points<2){
        return 1;
    }
    
    /*for(int i=0;i<n_points;i++){
        points[i].to_string(true);
    }*/

    Par menor = minDistBruto(points, n_points);    //Solução O(n²)

    menor.to_string();
    

    return 0;
}