#include "pilha.h"

int main(int argc, char **argv) {
    pilha *p = pilha_new();
    pilha_file(p, argv[1]);
    
    while((int)p->dstack_top + 2 < argc)
        pilha_push(p, atoi(argv[p->dstack_top + 2]));
    pilha_run(p);
    while(p->dstack_top > 0)
        printf("%d: %d\n", p->dstack_top-1, pilha_pop(p));
    
    pilha_delete(p);
    return 0;
}
