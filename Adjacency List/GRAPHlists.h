#define vertex int
typedef struct graph *Graph;
typedef struct node *link;

Graph GRAPHinit( int V );
static link NEWnode( vertex w, link next );
void GRAPHinsertArc( Graph G, vertex v, vertex w );
void GRAPHremoveArc( Graph G, vertex v, vertex w );
void GRAPHshow( Graph G );
Graph GRAPHrand( int V, int A );

bool isTopoNumbering( Graph, int []);

/*
    * A função GRAPHreach() recebe vértices s e t de um grafo G e decide se t está ao alcance de s ou não.
    * A função estática reachR() é recursiva e servirá para determinar se s realmente alcança t em algum momento.
*/
static void reachR( Graph G, vertex v);
bool GRAPHreach( Graph G, vertex s, vertex t);

/*
	* A função GRAPHdfs() faz uma busca em profundidade no grafo G. Ela atribui um número de ordem pre[x]
	* a cada vértice x de modo que o k-ésimo vértice descoberto receba o número de ordem k.
	* (Código inspirado no programa 18.3 de Sedgewick.)
*/
static void dfsR(Graph, vertex);
void GRAPHdfs(Graph);

/*
	* Exercicise List 1
*/
static int isSink( int V, link *l, vertex v );
void GRAPHsinks( Graph G );
static int isSource( int V, link *l, vertex v );
void GRAPHsources( Graph G );

int GRAPHindeg( Graph G, vertex v );
int GRAPHoutdeg( Graph G, vertex v );

int isIsolated( Graph G, vertex v );

int GRAPHIsUndirected( Graph G );

int *UGRAPHdegrees( Graph G );

int isRootedForest( Graph G, int top[] );

void GRAPHsimplePaths( Graph G, int lenghtPath );

/*
	* Exercicise List 2
*/
void GRAPHbfs( Graph G, vertex s);
