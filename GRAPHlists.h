#define vertex int
typedef struct graph *Graph;
typedef struct node *link;

Graph GRAPHinit( int V );
static link NEWnode( vertex w, link next );
void GRAPHinsertArc( Graph G, vertex v, vertex w );
void GRAPHremoveArc( Graph G, vertex v, vertex w );
void GRAPHshow( Graph G );
Graph GRAPHrand( int V, int A );

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