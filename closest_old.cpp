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
    void to_string(){printf("%lf %lf", x, y);}
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

//-------------- SORT -----------------------
bool compareX(Point p1, Point p2){
    return p1.x<p2.x;
}
vector<Point> sortX(vector<Point> points){
    sort(points.begin(), points.end(), compareX);
    return points;
}
bool compareY(Point p1, Point p2){
    return p1.y<p2.y;
}
vector<Point> sortY(vector<Point> points){
    sort(points.begin(), points.end(), compareY);
    return points;
}
//------------------------------------------

// ==================== Solução Quadrática =====================
Par minDistBruto(vector<Point> points){
    int n = points.size();
    Par menor = Par(points[0],points[1]);   

    for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++)
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
Par minDistFrente(vector<Point>& points, Par d){
    points = sortY(points);
    int n = points.size();
    for(int i=0; i<n-1; i++)
        for(int j=i+1; (j<n) && (points[j].y-points[i].y<d.dist); j++)
            d = menor_par(d, Par(points[i], points[j]));
    
    return d;
}
Par minDist(vector<Point>& points, int ini, int fin){
    if (fin-ini<=2) return Par(points[ini],points[ini+1]);
    //if (fin-ini<=3) return minDistBruto(points);
    int mid = (fin+ini)/2;
    
    Par de = minDist(points, ini, mid);
    Par dd = minDist(points, mid, fin);
    Par d = menor_par(de, dd);
    
    vector<Point> S;
    int midx = points[mid].x;

    for(int i=ini,j=0; i<fin; i++){
        if (points[i].x-midx<d.dist && (points[i].x-midx)>-
        d.dist)
            S.push_back(points[i]);
    }
    Par df = minDistFrente(points, d);
    
    return menor_par(d, df);
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ---------------- LEITURA DO ARQUIVO --------------------
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
// ------------------------------------------------------


int main(int argc, char *argv[]){
    double seconds;

    if (argc != 2) {
		fprintf(stderr, "Uso: %s input.txt\n", argv[0]);
		return 1;
	}
    

    vector<Point> points = read_points(argv[1]);
    if(points.size()<2){
        return 1;
    }


    printf("Quadrática: ");
    auto start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    Par menor = minDistBruto(points);    //Solução O(n²)
    auto end = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    auto milli = end - start; 
    printf("%lf ", milli/1000.0);
    menor.to_string();
    

    printf("Otimizada: ");
    start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    points = sortX(points);
    Par r = minDist(points, 0, n_points);  //Solução O(n log n)
    end = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    milli = end - start; 
    printf("%lf ", milli/1000.0);
    r.to_string();

    return 0;
}