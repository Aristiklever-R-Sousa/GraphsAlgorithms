#include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
#include "GRAPHmatrix.h"
// #include "GRAPHlists.h"

int main() {
    int V, v, w;

    scanf("%d", &V);
    Graph g = GRAPHinit(V);

    while(v > -1 && w > -1) {
        scanf("%d %d", &v, &w);
        if(v > -1 && w > -1)
            GRAPHinsertArc(g, v, w);
    }

    GRAPHdfsForest2(g);

    // whatIsTheType(g);

    // GRAPHshow(g);

    // printf("%ld\n", RAND_MAX+1);
}