/**************************************************************
 *                                                            *
 *      Trabalho 1 de Projeto e Análise de Algoritmo          *
 *      Escrito por:                                          *
 *          Gustavo Inacio Pereira Guedes - 2088860           *
 *          Franziska Romani Furtado - 1248006                *
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


struct Point{
    double x,y;
    Point(double x, double y):x(x),y(y){}
    Point():x(0),y(0){}
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
Point* copy(Point* points, int ini, int fim){
    Point* points_copy = (Point*) malloc((fim-ini)*sizeof(Point));
    for(int i=ini; i<fim; i++)
        points_copy[i-ini] = points[i];
    return points_copy; 
}

int n_points;

//-------------- SORT -----------------------
bool compareX(Point p1, Point p2){
    return p1.x<p2.x;
}
Point* sortX(Point* points, int n){
    sort(points, points+n, compareX);
    return points;
}

bool compareY(Point p1, Point p2){
    return p1.y<p2.y;
}
Point* sortY(Point* points, int n){
    sort(points, points+n, compareY);
    return points;
}
//------------------------------------------

// ==================== Solução Quadrática =====================
Par minDistBruto(Point* points, int ini, int fin){
    Par menor = Par(points[ini],points[ini+1]);   

    for(int i=ini; i<fin; i++)
        for(int j=i+1; j<fin; j++)
            menor = menor_par(menor, Par(points[i],points[j]));
    return menor;
}
// =============================================================


//-=-=-=-=-=-=-=-=-=-=-=    SOLUÇÃO OTIMIZADA   =-=-=-=-=-=-=-=-=-=-=-=-=-=
Par par_mais_proximo_entre_lados(vector<Point> points, int ini, int fin) {
    int mid = (fin+ini)/2;
    Par menor = Par(points[ini], points[ini+1]);

    for(int i=ini; i<mid; i++)
        for(int j=mid; j<fin; j++)
            menor = menor_par(menor, Par(points[i], points[j]));
    return menor;
}
Par minDistFrente(Point* Y, int n, Par d){    
    for(int i=0; i<n-1; i++)
        for(int j=i+1; (j<n) && (Y[j].y-Y[i].y<d.dist); j++)
            d = menor_par(d, Par(Y[i], Y[j])); 

    return d;
}
Par minDist(Point* X, Point* Y, int ini, int fin){
    if (fin-ini<=3) return minDistBruto(X, ini, fin);
    int mid = (fin+ini)/2;
    int n = fin-ini;

    Point Yl[mid-ini+1];
    Point Yr[fin-mid];

    int l=0;
    int r=0;

    for (int i=0; i<n; i++)
        if (Y[i].x<=X[mid].x)
            Yl[l++]=Y[i];
        else
            Yr[r++]=Y[i];

    Par dl = minDist(X, Yl, ini, mid);
    Par dr = minDist(X, Yr, mid, fin);
    Par d = menor_par(dl, dr);
    
    Point Pd[n];
    int id=0;
    int midx = X[mid].x;

    
    for(int i=0; i<n; i++){
        if ( abs(Y[i].x-midx) < d.dist )
            Pd[id++]=Y[i];
    }
    Par df = minDistFrente(Pd, id, d);
    
    return menor_par(d, df);
}

Par parMaisProximo(Point* points, int n){
    Point* X = sortX(copy(points, 0, n), n);
    Point* Y = sortY(copy(points, 0, n), n);
    
    Par min_par = minDist(X, Y, 0, n);
    
    /*
    for(int i=0;i<n_points;i++){
        X[i].to_string(true);
    }
    */
    return min_par;
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

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

    points = sortX(points, n_points);
    Par r = parMaisProximo(points, n_points);  //Solução O(n log n)
    
    
    r.to_string();

    return 0;
}