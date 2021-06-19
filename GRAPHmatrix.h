#define vertex int
typedef struct graph *Graph;

/*
	* Graph Theory functions root
*/
Graph GRAPHinit(vertex V );
static int **MATRIXint( int r, int c, int val );
void GRAPHinsertArc( Graph G, vertex v, vertex w );
void GRAPHremoveArc( Graph G, vertex v, vertex w );
void GRAPHshow( Graph G );
Graph GRAPHrand( int V, int A );

int isTopoNumbering( Graph, int []);

/*
    * A função GRAPHreach() recebe vértices s e t de um grafo G e decide se t está ao alcance de s ou não.
    * A função estática reachR() é recursiva e servirá para determinar se s realmente alcança t em algum momento.
*/
static void reachR( Graph, vertex);
int GRAPHreach( Graph, vertex, vertex);

/*
	* A função GRAPHdfs() faz uma busca em profundidade no grafo G. Ela atribui um número de ordem pre[x]
	* a cada vértice x de modo que o k-ésimo vértice descoberto receba o número de ordem k.
	* (Código inspirado no programa 18.3 de Sedgewick.)
*/
static void dfsR(Graph, vertex);
void GRAPHdfs(Graph);

/*
	* A função GRAPHdfs2() faz uma busca em profundidade no grafo G. Ela atribui um número de ordem pre[x]
	* a cada vértice x (o k-ésimo vértice descoberto recebe o número de ordem k)
	* e registra a correspondente floresta DFS no vetor de pais pa[].
	* (Código inspirado no programa 18.3 de Sedgewick.)
*/
static void dfsRForest(Graph, vertex);
void GRAPHdfsForest(Graph);

static void dfsRForest2(Graph, vertex);
void GRAPHdfsForest2(Graph);

void GRAPHgetDoublePermutationNotation(Graph G);

void GRAPHgetPreVector(Graph);

void GRAPHgetPostVector(Graph);

void GRAPHgetPaVector(Graph);

void whatIsTheType(Graph);

/*
	* Exercicise List 1
*/
static int isSink( int V, vertex **m, vertex v );
void GRAPHsinks( Graph G );
static int isSource( int V, vertex **m, vertex v );
void GRAPHsources( Graph G );

int GRAPHindeg( Graph G, vertex v );
int GRAPHoutdeg( Graph G, vertex v );

int GRAPHisIsolated( Graph G, vertex v );

int GRAPHthereIsArkBetween( Graph G, vertex v, vertex w );

int GRAPHIsUndirected( Graph G );

int *UGRAPHdegrees( Graph G );

int isRootedForest( Graph G, int top[] );

void GRAPHsimplePaths( Graph G, int lenghtPath );