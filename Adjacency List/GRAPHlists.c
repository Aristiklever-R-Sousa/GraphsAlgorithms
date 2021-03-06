#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "GRAPHlists.h"

struct graph {
    int V;
    int A;
    link *adj;
};

struct node {
    vertex w;
    link next;
};


Graph GRAPHinit( int V) { 
    Graph G = (Graph) calloc(1, sizeof(Graph));
    
    G->V = V; 
    G->A = 0;
    G->adj = (link*) calloc( V, sizeof(link) );
    
    for (vertex v = 0; v < V; ++v)
        G->adj[v] = NULL;
    
    return G;
}

static link NEWnode( vertex w, link next ) {
    link l = (link) calloc(1, sizeof(link) );

    l->w = w;
    l->next = next;

    return l;
}

void GRAPHinsertArc( Graph G, vertex v, vertex w ) {
    for (link a = G->adj[v]; a != NULL; a = a->next) 
        if (a->w == w) return;
    
    G->adj[v] = NEWnode( w, G->adj[v]);
    G->A++;
    
}

void GRAPHremoveArc( Graph G, vertex v, vertex w) {
    link a = G->adj[v], last = NULL;
    
    while(a != NULL) {
        if (a->w == w) break;
        last = a;
        a = a->next;
    }

    if(a == NULL) return;

    if(G->adj[v] == a)
        G->adj[v] == a->next;
    else if(a->next == NULL)
        last->next = NULL;
    else
        last->next = a->next;
    
    G->A--;
}

void GRAPHshow( Graph G ) {
    for (vertex v = 0; v < G->V; v++)
    {
        printf("%2d:", v);

        link aux = G->adj[v];
        while (aux)
        {
            printf(" %2d", aux->w);
            aux = aux->next;
        }
      
        printf( "\n");
   }
}

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


bool isTopoNumbering( Graph G, int topo[]) {
   for (vertex v = 0; v < G->V; ++v)
      for (link a = G->adj[v]; a != NULL; a = a->next) 
         if (topo[v] >= topo[a->w]) 
            return false;

   return true;
}


// static int visited[1000];

static void reachR( Graph G, vertex v)
{
    visited[v] = 1;

    for (link a = G->adj[v]; a != NULL; a = a->next)
        if (visited[a->w] == 0)
            reachR(G, a->w);
}

bool GRAPHreach( Graph G, vertex s, vertex t)
{
    for (vertex v = 0; v < G->V; ++v)
        visited[v] = 0;

    reachR(G, s);

    if (visited[t] == 0)
        return false;
    else
        return true;
}


static int cnt, pre[1000];

static void dfsR(Graph G, vertex v)
{
    pre[v] = cnt++;
    
    for (link a = G->adj[v]; a != NULL; a = a->next) {
        vertex w = a->w;
        if (pre[w] == -1)
            dfsR( G, w);
    }
}

void GRAPHdfs(Graph)
{
    cnt = 0;

    for (vertex v = 0; v < G->V; ++v) 
        pre[v] = -1;

    for (vertex v = 0; v < G->V; ++v)
        if (pre[v] == -1) 
            dfsR( G, v);
}


static int isSink( int V, link *l, vertex v ) {
    // Testa se o v??rtice especificado possui algum arco de sa??da
    // Se sim, ele sai, pois n??o ?? sorvedouro
    if(l[v])
        return 0;

    link aux = NULL;
    // Testa se v possui algum arco de entrada
    for(int i = 0; i < V; i++)
        if(i != v) {
            aux = l[i];

            while(aux) {
                if(aux->w == v) return 1;
                aux = aux->next;
            }
        }

    return 0;
}

void GRAPHsinks( Graph G ) {
    int notHaveSink = 1;
    for(int i = 0; i < G->V; i++) {
        if(isSink(G->V, G->adj, i)) {
            printf("V??rtice %d ?? sorvedouro.\n", i);
            notHaveSink = 0;
        }
    }

    if(notHaveSink) printf("Este grafo n??o possui sorvedouro!\n");
}

static int isSource( int V, link *l, vertex v ) {
    // Verifica se existe algum arco de entrada no v??rtice especificado
    // Se sim, retorna falso, pois ele n??o ser?? um fonte
    link aux = NULL;
    for(int i = 0; i < V; i++)
        if(i != v) {
            aux = l[i];

            while(aux) {
                if(aux->w == v) return 0;
                aux = aux->next;
            }
        }

    // Verifica se ele possui, pelo menos, um arco de sa??da
    if(l[v])
        return 1;

    return 0;
}

void GRAPHsources( Graph G ) {
    int notHaveSource = 1;
    for(int i = 0; i < G->V; i++) {
        if(isSource(G->V, G->adj, i)) {
            printf("V??rtice %d ?? fonte.\n", i);
            notHaveSource = 0;
        }
    }

    if(notHaveSource) printf("Este grafo n??o possui fontes!\n");
}

int GRAPHindeg( Graph G, vertex v ) {
    int in = 0;
    link aux = NULL;
    
    for(int i = 0; i < G->V; i++)
        if(i != v) {
            aux = G->adj[i];
            
            while(aux) {
                if(aux->w == v)
                    in++;
                aux = aux->next;
            }

        }
    
    return in;
}

int GRAPHoutdeg( Graph G, vertex v ) {
    int out = 0;
    link aux = G->adj[v];

    while(aux) {
        out++;
        aux = aux->next;
    }

    return out;
}

int isIsolated( Graph G, vertex v ) {
    if(G->adj[v]) return 0;

    link aux = NULL;
    for(int i = 0; i < G->V; i++)
        if(i != v) {
            aux = G->adj[i];

            while(aux) {
                if(aux->w == v) return 0;
                aux = aux->next;
            }
        }

    return 1;
}

int GRAPHIsUndirected( Graph G ) {
    int arcs = 0;
    link aux = NULL, aux2 = NULL;

    for(int v = 0; v < G->V && arcs < G->A; v++) {
        aux = G->adj[v];

        while(aux && arcs < G->A) {
            aux2 = G->adj[aux->w];
            
            // Procurando no v??rtice w se h?? alguma ocorr??ncia de v rec??proca
            while(aux2) {
                if(aux2->w == v) break;
                aux2 = aux2->next;
            }

            if(aux2 == NULL) return 0;

            arcs+=2;
            aux = aux->next;
        }
    }

    return 1;
}

int *UGRAPHdegrees( Graph G ) {
    int *degrees = calloc(G->V, sizeof(int));
    int arcs = 0;
    link aux = NULL;

    for(int i = 0; i < G->V && arcs < G->V ; i++) {
        aux = G->adj[i];

        while(aux) {
            degrees[i]++;
            degrees[aux->w]++;
            aux = aux->next;
            arcs+=2;
        }
    }
    
    return degrees;
}

int isRootedForest(Graph G, int top[]) {
    int sources = 0, inQtt;

    for(vertex v = 0; v < G->V; v++)
        if(top[v] == 0) sources++;

    if(sources <= 1)
        return 0;

    for(int vActu = 0; vActu < G->V; vActu++) {
        inQtt = 0;

        for(vertex v = 0; v < G->V; v++) {
            link aux = G->adj[v];

            while(aux) {
                if(aux->w == vActu) {
                    if(inQtt)
                        return 0;
                    else
                        inQtt++;
                }

                aux = aux->next;
            }   
        }
    }


    return 1;

}

static int path[4], step, visited[1000], archVisited[1000][1000];

static void emptyVisited(int V) {
    for(int i = 0; i < V; i++)
        visited[i] = 0;
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
    
    link aux = G->adj[v];
    while(aux) {
        
        if(visited[aux->w] == 0 || archVisited[v][aux->w] == 0) {
            archVisited[v][aux->w] = 1;
            pathConstruct( G, aux->w);
        }
        
        aux = aux->next;
    }

    step--;

}

void GRAPHsimplePaths(Graph G, int lenghtPath) {
    for(int i = 0; i < lenghtPath - 1; i++)
        path[i] = -1;
    
    printf("Caminhos simples: \n");
    for(vertex v = 0; v < G->V; v++) {
        step = -1;
        pathConstruct(G, v);
        emptyVisited(G->V);
    }
}


/*
	* Exercicise List 2
*/

void GRAPHbfs( Graph G, vertex s) 
{ 
   int cnt = 0;
   for (vertex v = 0; v < G->V; ++v)
      num[v] = -1;
   QUEUEinit( G->V);
   num[s] = cnt++; 
   QUEUEput( s); 

   while (!QUEUEempty( )) {
      vertex v = QUEUEget( ); 
      for (link a = G->adj[v]; a != NULL; a = a->next)
         if (num[a->w] == -1) {
            num[a->w] = cnt++; 
            QUEUEput( a->w); 
         }
   }
   QUEUEfree( ); 
}
