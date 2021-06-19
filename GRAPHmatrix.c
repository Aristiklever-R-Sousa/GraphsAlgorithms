#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
Graph GRAPHrand( int V, int A )
{ 
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

int isTopoNumbering( Graph G, int topo[])
{
    for (vertex v = 0; v < G->V; ++v)
        for (vertex w = 0; w < G->V; w++)
            if (G->adj[v][w] && topo[v] >= topo[w])
                return 0;

   return 1;
}

static int visited[1000];

static void reachR( Graph G, vertex v)
{ 
   visited[v] = 1;

    for (vertex w = 0; w < G->V; ++w)
        if (G->adj[v][w] && visited[w] == 0)
            reachR(G, w);
}

int GRAPHreach( Graph G, vertex s, vertex t)
{ 
    for (vertex v = 0; v < G->V; ++v)
        visited[v] = 0;

    reachR(G, s);

    if (visited[t] == 0)
        return 0;
    
    return 1;
}

static int cnt, indent, pre[1000], post[1000], pa[1000];

static void dfsR(Graph G, vertex v)
{
    pre[v] = cnt++; 

    for (vertex w = 0; w < G->V; w++) {
        if (G->adj[v][w]) {
            for(int i = 0; i < indent; i++)
                printf(". ");
            printf("%d-%d", v, w);
            
            if(pre[w] == -1) {
                printf(" dfsR(G,%d)\n", w);
                indent++;
                dfsR(G, w);
            }
            else
                printf("\n");
            
        }
    }

    for(int i = 0; i < indent; i++)
        printf(". ");
    printf("%d\n", v);

    indent--;
}

void GRAPHdfs(Graph G)
{
    cnt = 0;

    for (vertex v = 0; v < G->V; ++v) 
        pre[v] = -1;

    for (vertex v = 0; v < G->V; ++v)
        if (pre[v] == -1) {
            indent = 0;
            printf("%d dfsR(G,%d)\n", v, v);
            dfsR( G, v);
            printf("\n");   
        }

}

static void dfsRForest(Graph G, vertex v)
{
    pre[v] = cnt++; 

    for (vertex w = 0; w < G->V; w++) {
        if (G->adj[v][w]) {
            for(int i = 0; i < indent; i++)
                printf(". ");
            printf("%d-%d", v, w);
            
            if(pre[w] == -1) {
                pa[w] = v;
                printf(" dfsRForest(G,%d)\n", w);
                indent++;
                dfsRForest(G, w);
            }
            else
                printf("\n");
            
        }
    }

    for(int i = 0; i < indent; i++)
        printf(". ");
    printf("%d\n", v);

    indent--;

    post[v] = cnt++;
}

void GRAPHdfsForest(Graph G)
{
    cnt = 0;

    for (vertex v = 0; v < G->V; ++v) 
        pre[v] = pa[v] = -1;

    for (vertex v = 0; v < G->V; ++v)
        if (pre[v] == -1) {
            indent = 0;
            printf("%d dfsRForest(G,%d)\n", v, v);
            pa[v] = v;
            dfsRForest( G, v);
            printf("\n"); 
        }

    printf("\n\n"); 
}

char paren[1000];

static void dfsRForest2(Graph G, vertex v)
{
    paren[cnt] = '(';
    pre[v] = cnt++; 

    printf("%d ", v);

    for (vertex w = 0; w < G->V; w++) {
        if (G->adj[v][w]) {
            if(pre[w] == -1) {
                pa[w] = v;
                dfsRForest2(G, w);
            }
        }
    }

    printf("%d ", v);

    paren[cnt] = ')';
    post[v] = cnt++;
}

void GRAPHdfsForest2(Graph G)
{
    cnt = 0;

    for (vertex v = 0; v < G->V; ++v) 
        pre[v] = pa[v] = -1;

    for (vertex v = 0; v < G->V; ++v)
        if (pre[v] == -1) {
            pa[v] = v;
            dfsRForest2(G, v);
        }

    printf("\n");

    for(int i = 0; i < cnt; i++)
        printf("%c ", paren[i]);

    printf("\n\n"); 
}

void whatIsTheType(Graph G) {
    cnt = 0;

    for (vertex v = 0; v < G->V; ++v) 
        pre[v] = post[v] = pa[v] = -1;

    for (vertex v = 0; v < G->V; ++v)
        if (pre[v] == -1) {
            pa[v] = v;
            dfsRForest( G, v);
        }

    printf("\n");

    for (vertex v = 0; v < G->V; ++v)
        for (vertex w = 0; w < G->V; ++w)
            if(G->adj[v][w]) {
                if(pa[w] == v)
                    printf("%d-%d floresta\n", v, w);

                else if(pre[v] < pre[w] && post[v] > post[w])
                    printf("%d-%d avanço\n", v, w);

                else if(pre[v] > pre[w] && post[v] < post[w])
                    printf("%d-%d retorno\n", v, w);

                else
                    printf("%d-%d cruzado\n", v, w);
            }
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

int GRAPHisIsolated(Graph G, vertex v) {
     for(vertex w = 0; w < G->V; w++)
        if(G->adj[v][w] || G->adj[w][v])
            return 0;
    
    return 1;
}

int GRAPHthereIsArkBetween( Graph G, vertex v, vertex w ) {
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
                    arcs += 2;

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
        emptyArcVisited(G->V, -1);
    }
}