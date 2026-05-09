#include "pilha.h"

pilha *pilha_new() {
    pilha *p = malloc(sizeof(pilha));
    
    p->dstack_top = 0;
    p->cstack_top = 0;
    p->bytecode_index = 0;
    
    p->dstack_size = 128;
    p->cstack_size = 16;
    p->variable_size = 0;
    p->bytecode_size = 0;
    
    p->dstack = malloc(p->dstack_size * sizeof(i32));
    p->cstack = malloc(p->cstack_size * sizeof(i32));
    p->vvariable = NULL;
    p->kvariable = NULL;
    p->bytecode = NULL;
    
    return p;
}

void pilha_delete(pilha *p) {
    free(p->dstack);
    free(p->cstack);
    
    free(p->vvariable);
    for(int i = 0; i < p->variable_size; i++)
        free(p->kvariable[i]);
    free(p->kvariable);
    
    free(p->bytecode);
    free(p);
}

void pilha_run(pilha *p) {
    p->bytecode_index = 0;
    
    while(p->bytecode_index < p->bytecode_size) {
        u32 token = p->bytecode[p->bytecode_index].token;
        i32 value = p->bytecode[p->bytecode_index].value;
        
        pilha_mnemonic[token].function(p, value);
        p->bytecode_index++;
    }
}

void pilha_wipe(pilha *p) {
    free(p->dstack);
    free(p->vvariable);
    for(int i = 0; i < p->variable_size; i++)
        free(p->kvariable[i]);
    free(p->kvariable);
    
    p->dstack_top = 0;
    p->dstack_size = 128;
    p->variable_size = 0;
    
    p->dstack = malloc(p->dstack_size * sizeof(i32));
    p->vvariable = NULL;
    p->kvariable = NULL;
}