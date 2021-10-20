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
#include<iostream>
#include <string>

#include <algorithm>

#define MAX 112345
#define INF 1123456
using namespace std;


struct Point{
    double x,y;
    Point(double x, double y):x(x),y(y){}
    Point():x(0),y(0){}
    string to_string(bool end_line=false){
        string saida = std::to_string(x) +" "+ std::to_string(y) ;
        return saida;
    }
    bool operator<(Point a) const{
        if(x<a.x)return true;
        return false;
    }
    /*Point& operator=(const Point& a)
    {
        x=a.x;
        y=a.y;
        return *this;
    }*/


};
struct Par{
    Point a, b;
    double dist;
    Par(Point a, Point b):a(a),b(b) {dist = sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}
    Par():a(Point(-INF, -INF)),b(Point(INF,INF)) {dist = sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}
    string to_string(){
        string saida = std::to_string(dist)+" "+a.to_string()+" "+b.to_string();
        return saida;
    }
};

Par menor_par(Par a, Par b){
    if(a.dist<b.dist) return a;
    return b;
}
int n_points;

//-------------- SORT -----------------------
void merge(Point* points, int ini, int fin, bool (*cmp)(Point,Point)){
    int mid = (ini+fin)/2;
    int n = fin-ini;
    Point aux[n];

    int t=0, j=mid;
    for (int i=ini; i<mid;)
        if( cmp(points[i], points[j]) || j==fin )
            aux[t++]=points[i++];
        else 
            aux[t++]=points[j++];
    while( j<fin )
        aux[t++]=points[j++];
    
    for(int i=0; i<t; i++)
        points[i+ini]=aux[i];
}
void mergesort(Point* points, int ini, int fin, bool (*cmp)(Point,Point)){
    if ( ini+1>=fin ) return;
    int mid = (ini+fin)/2;
    mergesort(points, ini, mid, cmp);
    mergesort(points, mid, fin, cmp);
    merge(points, ini, fin, cmp);
}

bool compareX(Point p1, Point p2){
    return p1.x<p2.x;
}
vector<Point> sortX(vector<Point> points){
    //mergesort(points, 0, n, compareX);
    sort(points.begin(), points.end(), compareX);
    return points;
}

bool compareY(Point p1, Point p2){
    return p1.y<p2.y;
}
vector<Point> sortY(vector<Point> points){
    //mergesort(points, 0, n, compareY);
    sort(points.begin(), points.end(), compareY);
    //sort(points, points+n, compareY);
    return points;
}
//------------------------------------------

// ==================== Solução Quadrática =====================
Par maisProximoBruto(vector<Point> points, int ini, int fin){
    Par menor = Par(points[ini],points[ini+1]);   

    for(int i=ini; i<fin; i++)
        for(int j=i+1; j<fin; j++)
            menor = menor_par(menor, Par(points[i],points[j]));
    return menor;
}
// =============================================================


//-=-=-=-=-=-=-=-=-=-=-=    SOLUÇÃO OTIMIZADA   =-=-=-=-=-=-=-=-=-=-=-=-=-=

Par maisProximoDelta(vector<Point> Y, int n, Par d){    
    for(int i=0; i<n-1; i++)
        for(int j=i+1; (j<n) && (Y[j].y-Y[i].y<d.dist); j++)
            d = menor_par(d, Par(Y[i], Y[j])); 

    return d;
}
Par maisProximo(vector<Point> X, vector<Point> Y, int ini, int fin){
    if (fin-ini<=3) return maisProximoBruto(X, ini, fin);
    int mid = (fin+ini)/2;
    int n = fin-ini;

    vector<Point> Yl; 
    vector<Point> Yr;
    int l=0, r=0;
    for (int i=0; i<n; i++)
        if (Y[i].x<=X[mid].x)
            Yl.push_back(Y[i]);
        else
            Yr.push_back(Y[i]);

    Par dl = maisProximo(X, Yl, ini, mid);
    Par dr = maisProximo(X, Yr, mid, fin);
    Par d = menor_par(dl, dr);

    vector<Point> Pd;
    int id=0;
    double midx = X[mid].x;

    for(int i=0; i<n; i++){
        if ( abs(Y[i].x-midx) < d.dist )
            Pd.push_back(Point(Y[i].x, Y[i].y));
    }
    Par df = maisProximoDelta(Pd, id, d);

    return menor_par(d, df);
}

Par parMaisProximo(vector<Point> points){
    vector<Point> X = sortX(points);
    vector<Point> Y = sortY(points);

    return maisProximo(X, Y, 0, points.size());
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
    if(n_points<2){
        return 1;
    }
    
    clock_t t;
    t = clock();
    Par r = parMaisProximo(points);  //Solução O(n log n)
    t = clock()-t;
    
    cout << (float)t/CLOCKS_PER_SEC << " " << r.to_string() << endl;
    
    return 0;
}