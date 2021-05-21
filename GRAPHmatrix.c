#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "GRAPHmatrix.h"

struct graph {
    vertex V;
    int A;
    int **adj;
};

Graph GRAPHinit( vertex V ) {
    Graph G = (Graph) calloc(1, sizeof(Graph));

    G->V = V; 
    G->A = 0;
    G->adj = MATRIXint( V, V, 0 );
   
   return G;
}

static int **MATRIXint( int r, int c, int val ) { 
   int **m = (int**) calloc(r, sizeof(int *));

   for (vertex i = 0; i < r; ++i) 
        m[i] = (int*) calloc( c, sizeof (int) );
   
   for (vertex i = 0; i < r; ++i)
        for (vertex j = 0; j < c; ++j)
            m[i][j] = val;
   
   return m;
}

void GRAPHinsertArc( Graph G, vertex v, vertex w ) { 
    if (G->adj[v][w] == 0)
    {
        G->adj[v][w] = 1;
        G->A++;
    }
}

void GRAPHremoveArc( Graph G, vertex v, vertex w ) { 
   if (G->adj[v][w] == 1)
   {
      G->adj[v][w] = 0;
      G->A--;
   }
}

void GRAPHshow( Graph G ) { 
    for (vertex v = 0; v < G->V; ++v)
    {
        printf("%2d:", v);
      
        for (vertex w = 0; w < G->V; ++w)
            if (G->adj[v][w] == 1) 
                printf(" %2d", w);
      
        printf( "\n");
   }

   printf( "\n");
}

/*
    * Essa função inicializa um grafo aleatório;
    * Ela leva em consideração que o valor informado a A sempre será A <= V*(V-1)
*/

Graph GRAPHrand( int V, int A ) { 
    Graph G = GRAPHinit( V );
    
    srand(time( NULL ));

    while (G->A < A) {
        vertex v = rand() % V;
        vertex w = rand() % V;
        if (v != w)
            GRAPHinsertArc( G, v, w );
    }
    
    return G;
}

static int isSink(int V, vertex **m, vertex v) {
    
    // Testa se o vértice especificado possui algum arco de saída
    // Se sim, ele sai, pois não é sorvedouro
    for(vertex w = 0; w < V; w++)
        if(m[v][w])
            return 0;

    // Testa se v possui algum arco de entrada
    for(vertex w = 0; w < V; w++)
        if(m[w][v])
            return 1;

    return 0;
}

void GRAPHsinks( Graph G ) {
    int notHaveSink = 1;
    for(int i = 0; i < G->V; i++) {
        if(isSink(G->V, G->adj, i)) {
            printf("Vértice %d é sorvedouro.\n", i);
            notHaveSink = 0;
        }
    }

    if(notHaveSink) printf("Este grafo não possui sorvedouro!\n");
}

static int isSource(int V, vertex **m, vertex v) {
    
    // Verifica se existe algum arco de entrada no vértice especificado
    for(vertex w = 0; w < V; w++)
        if(m[w][v])
            return 0;
    
    // Verifica se ele possui, pelo menos, um arco de saída
    for(vertex w = 0; w < V; w++)
        if(m[v][w])
            return 1;

    return 0;
}

void GRAPHsources( Graph G ) {
    int notHaveSource = 1;
    for(int i = 0; i < G->V; i++) {
        if(isSource(G->V, G->adj, i)) {
            printf("Vértice %d é fonte.\n", i);
            notHaveSource = 0;
        }
    }

    if(notHaveSource) printf("Este grafo não possui fontes!\n");
}

int GRAPHindeg( Graph G, vertex v ) {
    int in = 0;

    for(vertex w = 0; w < G->V; w++)
        if(G->adj[w][v])
            in++;
    
    return in;
}

int GRAPHoutdeg( Graph G, vertex v ) {
    int out = 0;

    for(vertex w = 0; w < G->V; w++)
        if(G->adj[v][w])
            out++;

    return out;
}

int isIsolated(Graph G, vertex v) {
     for(vertex w = 0; w < G->V; w++)
        if(G->adj[v][w] || G->adj[w][v])
            return 0;
    
    return 1;
}

int thereIsArkBetween( Graph G, vertex v, vertex w ) {
    return G->adj[v][w];
}

int GRAPHIsUndirected(Graph G) {
    int arcs = 0;
    
    for(vertex v = 0; v < G->V && arcs < G->A; v++)
        for(vertex w = 0; w < G->V && arcs < G->A; w++)
            if( v > w )
                if(G->adj[v][w] && G->adj[w][v] == 0)
                    return 0;
                else
                    arcs+=2;

    return 1;
}

int *UGRAPHdegrees( Graph G ) {
    int *degrees = calloc(G->V, sizeof(int));
    int arcs = 0;

    for(vertex v = 0; v < G->V && arcs < G->V ; v++)
        for(vertex w = 0; w < G->V; w++)
            if(v > w && G->adj[v][w]) {
                degrees[v]++;
                degrees[w]++;
                arcs+=2;
            }
    
    return degrees;
}

/*
    * Vai visitar todas as linhas de uma determinada coluna para achar os graus de entrada.
    * Se houver algum maior que 1, retornará 0 (false)
    * Senão, retorna 1 (true)
*/
int isRootedForest(Graph G, int top[]) {
    int sources = 0, inQtt;

    for(vertex v = 0; v < G->V; v++)
        if(top[v] == 0) sources++;

    if(sources <= 1)
        return 0;

    for(vertex w = 0; w < G->V; w++) {
        inQtt = 0;

        for(vertex v = 0; v < G->V; w++)
            if(G->adj[v][w]) {
                if(inQtt)
                    return 0;
                else
                    inQtt++;
            }
        
    }

    return 1;
}

static int path[4], step, visited[1000], archVisited[1000][1000];

static void emptyVertVisited(int V) {
    for(int i = 0; i < V; i++)
        visited[i] = 0;
}

static void emptyArcVisited(int V, int vEspec) {
    if(vEspec == -1)
        for(vertex v = 0; v < V; v++)
            for(vertex w = 0; w < V; w++)
                archVisited[v][w] = 0;
    else {
        for(vertex v = 0; v < V; v++)
            for(vertex w = 0; w < V; w++)
                if(v != vEspec)
                    archVisited[v][w] = 0;
    }
}

static void pathConstruct( Graph G, vertex v ) {
    step++;
    path[step] = v;
    
    if(step == 3) {
        for(int i = 0; i < 4; i++)
            printf("%d ", path[i]);
        printf("\n");

        step--;
        return;
    }

    visited[v] = 1;
    
    for (vertex w = 0; w < G->V; w++) {
        if (G->adj[v][w] && (visited[w] == 0 || archVisited[v][w] == 0)) {
            archVisited[v][w] = 1;
            pathConstruct( G, w );

            if(step == 0)
                
        }
    }

    step--;

}

void GRAPHsimplePaths(Graph G, int lenghtPath) {
    for(int i = 0; i < lenghtPath - 1; i++)
        path[i] = -1;
    
    emptyVertVisited(G->V);
    emptyArcVisited(G->V, -1);

    printf("Caminhos simples: \n");
    for(vertex v = 0; v < G->V; v++) {
        step = -1;
        pathConstruct(G, v);
        emptyVertVisited(G->V);
        emptyArcVisited(G->V);
    }
}