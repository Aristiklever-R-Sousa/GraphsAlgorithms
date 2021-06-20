#define vertex int
/* Este módulo implementa uma fila de vértices. A fila reside no segmento queue[begin..end-1] de um vetor queue[0..N-1]. Vamos supor que temos sempre 0 ≤ begin ≤ end ≤ N. (O código abaixo é uma adaptação do programa 4.11 do volume 1 do livro de Sedgewick.) */
static vertex *queue; 
static int begin, end;

void QUEUEinit( int N) { 
   queue = malloc( N * sizeof (vertex));
   begin = end = 0; 
}

int QUEUEempty( void) { 
   return begin == end; 
}

void QUEUEput( vertex v) {
   queue[end++] = v;
}

vertex QUEUEget( void) { 
   return queue[begin++];
}

void QUEUEfree( void) {
   free( queue);
}
