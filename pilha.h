#ifndef __PILHA_CORE
#define __PILHA_CORE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef int32_t i32;
typedef uint32_t u32;

typedef struct pilha pilha;
typedef struct pilha_token pilha_token;
typedef struct pilha_instruction pilha_instruction;

struct pilha {
    i32 *dstack;
    i32 *cstack;
    i32 *vvariable;
    char **kvariable;
    pilha_instruction *bytecode;
    
    u32 dstack_size;
    u32 cstack_size;
    u32 variable_size;
    u32 bytecode_size;
    
    u32 dstack_top;
    u32 cstack_top;
    u32 bytecode_index;
};

struct pilha_token {
    char* name;
    void (*function)(pilha*, i32);
};

struct pilha_instruction {
    u32 token;
    i32 value;
};

extern pilha_token pilha_mnemonic[];

void pilha_push(pilha*, i32);
i32 pilha_pop(pilha*);
i32 pilha_table(pilha*, char*);
i32 *pilha_variable(pilha*, char*);

pilha *pilha_new();
void pilha_delete(pilha*);
void pilha_run(pilha*);
void pilha_wipe(pilha*);

void pilha_file(pilha*, char*);

#endif
