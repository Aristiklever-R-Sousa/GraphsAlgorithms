#include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include "GRAPHmatrix.h"
#include "GRAPHlists.h"

int main() {
    int V, v = 1, w = 1;

    scanf("%d", &V);
    Graph g = GRAPHinit(V);

    while(v > -1 && w > -1) {
        scanf("%d %d", &v, &w);
        if(v > -1 && w > -1)
            GRAPHinsertArc(g, v, w);
    }

    GRAPHshow(g);
    // GRAPHsimplePaths(g, 4);

    // printf("%ld\n", RAND_MAX+1);
}