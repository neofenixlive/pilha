#include "pilha.h"

void pilha_push(pilha *p, i32 value) {
    p->dstack[p->dstack_top] = value;
    p->dstack_top++;
    if(p->dstack_top == p->dstack_size) {
        p->dstack_size *= 2;
        p->dstack = realloc(p->dstack, sizeof(i32) * p->dstack_size);
    }
}

i32 pilha_pop(pilha *p) {
    if(p->dstack_top == 0) {
        printf("ERROR! Tried to pop, but the stack is empty.\n");
        exit(1);
    }
    p->dstack_top--;
    return p->dstack[p->dstack_top];
}

i32 pilha_table(pilha *p, char *key) {
    for(int i = 0; i < p->variable_size; i++) {
        if(!strcmp(key, p->kvariable[i]))
            return i;
    }
    p->vvariable = realloc(p->vvariable, sizeof(i32) * (p->variable_size + 1));
    p->kvariable = realloc(p->kvariable, sizeof(char*) * (p->variable_size + 1));
    p->vvariable[p->variable_size] = 0;
    p->kvariable[p->variable_size] = malloc(strlen(key) + 1);
    strcpy(p->kvariable[p->variable_size], key);
    return p->variable_size++;
}

i32 *pilha_variable(pilha *p, char *key) {
    return &p->vvariable[pilha_table(p, key)];
}