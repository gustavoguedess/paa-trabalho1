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
Point* copy(Point* points, int n){
    Point* duplicate = (Point*)malloc(n*sizeof(Point));
    for (int i=0; i<n; i++)
        duplicate[i]=points[i];
    return duplicate;
}
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
Point* sortX(Point* points, int n){
    //mergesort(points, 0, n, compareX);
    sort(points, points+n, compareX);
    return points;
}

bool compareY(Point p1, Point p2){
    return p1.y<p2.y;
}
Point* sortY(Point* points, int n){
    //mergesort(points, 0, n, compareY);
    sort(points, points+n, compareY);
    return points;
}
//------------------------------------------

// ==================== Solução Quadrática =====================
Par maisProximoBruto(Point* points, int ini, int fin){
    Par menor = Par(points[ini],points[ini+1]);   

    for(int i=ini; i<fin; i++)
        for(int j=i+1; j<fin; j++)
            menor = menor_par(menor, Par(points[i],points[j]));
    return menor;
}
// =============================================================


//-=-=-=-=-=-=-=-=-=-=-=    SOLUÇÃO OTIMIZADA   =-=-=-=-=-=-=-=-=-=-=-=-=-=

Par maisProximoDelta(Point* Y, int n, Par d){    
    for(int i=0; i<n-1; i++)
        for(int j=i+1; (j<n) && (Y[j].y-Y[i].y<d.dist); j++)
            d = menor_par(d, Par(Y[i], Y[j])); 

    return d;
}
Par maisProximo(Point* X, Point* Y, int ini, int fin){
    if (fin-ini<=3) return maisProximoBruto(X, ini, fin);
    int mid = (fin+ini)/2;
    int n = fin-ini;
    
    Point* Yl = (Point*)malloc((mid-ini+1)*sizeof(Point)); 
    Point* Yr = (Point*)malloc((fin-mid)*sizeof(Point)); 
    
    int l=0, r=0;
    for (int i=0; i<n; i++)
        if (Y[i].x<=X[mid].x)
            Yl[l++]=Y[i];
        else
            Yr[r++]=Y[i];
            
    Par dl = maisProximo(X, Yl, ini, mid);
    Par dr = maisProximo(X, Yr, mid, fin);
    Par d = menor_par(dl, dr);
    
    double midx = X[mid].x;
    int il=0;
    for (int i=0; i<l; i++){
        if ( abs(Yl[i].x-midx) < d.dist )
            Yl[il++] = Yl[i];
    }

    int ir=0;
    for (int i=0; i<r; i++){
        if ( abs(Yr[i].x-midx) < d.dist )
            Yr[ir++] = Yr[i];
    }
    r=ir;
    l=il;
    int minj=0;
    for(int i=0; i<l; i++){
        for(int j=minj; j<r && Yl[j].y<=Yr[i].y+d.dist ; j++){
            if(Yr[j].y<Yl[i].y-d.dist){
                minj++;
                continue;
            }
            d = menor_par( d, Par(Yl[i], Yr[j]) );
        }
    }
    free(Yl);
    free(Yr);
    return d;
}

Par parMaisProximo(Point* points, int n){
    Point* X = sortX(copy(points, n), n);
    Point* Y = sortY(copy(points, n), n);
    
    Par par = maisProximo(X, Y, 0, n);
    free(X);
    free(Y);
    return par;
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ---------------- LEITURA DO ARQUIVO --------------------
Point* read_points(char *file_name){
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL)
	{
		fprintf(stderr, "Falha ao criar input.txt.\n");
		return NULL;
	}
    fscanf(fp,"%d", &n_points);
    Point* vector_points = (Point*)(malloc(n_points*sizeof(Point)));
    
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
    
    clock_t t;
    t = clock();
    Par r = parMaisProximo(points, n_points);  //Solução O(n log n)
    t = clock()-t;
    
    cout << (float)t/CLOCKS_PER_SEC << " " << r.to_string() << endl;
    
    return 0;
}