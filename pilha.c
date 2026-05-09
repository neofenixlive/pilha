#include "pilha.h"

void push(pilha *p, i32 value) {
    p->dstack[p->dstack_top] = value;
    p->dstack_top++;
    if(p->dstack_top == p->dstack_size) {
        p->dstack_size *= 2;
        p->dstack = realloc(p->dstack, sizeof(i32) * p->dstack_size);
    }
}

i32 pop(pilha *p) {
    if(p->dstack_top == 0) {
        printf("ERROR! Tried to pop, but the stack is empty.\n");
        exit(1);
    }
    p->dstack_top--;
    return p->dstack[p->dstack_top];
}

i32 table(pilha *p, char* key) {
    for(int i = 0; i < p->variable_size; i++) {
        if(strcmp(key, p->kvariable[i]) == 0)
            return i;
    }
    p->vvariable = realloc(p->vvariable, sizeof(i32) * (p->variable_size + 1));
    p->kvariable = realloc(p->kvariable, sizeof(char*) * (p->variable_size + 1));
    p->vvariable[p->variable_size] = 0;
    p->kvariable[p->variable_size] = malloc(strlen(key) + 1);
    strcpy(p->kvariable[p->variable_size], key);
    return p->variable_size++;
}

void __push(pilha *p, i32 value)          { push(p, value); }
void __pushat(pilha *p, i32 value)        { push(p, p->vvariable[value]); }
void __pop(pilha *p, i32 value)           { pop(p); }
void __popat(pilha *p, i32 value)         { p->vvariable[value] = pop(p); }
void __copy(pilha *p, i32 value)          { i32 a = pop(p); push(p, a); push(p, a); }
void __swap(pilha *p, i32 value)          { i32 a = pop(p), b = pop(p); push(p, a); push(p, b); }
void __add(pilha *p, i32 value)           { i32 a = pop(p), b = pop(p); push(p, b + a); }
void __subtract(pilha *p, i32 value)      { i32 a = pop(p), b = pop(p); push(p, b - a); }
void __multiply(pilha *p, i32 value)      { i32 a = pop(p), b = pop(p); push(p, b * a); }
void __divide(pilha *p, i32 value)        { i32 a = pop(p), b = pop(p); push(p, a ? (b / a) : 0); }
void __modulo(pilha *p, i32 value)        { i32 a = pop(p), b = pop(p); push(p, a ? (b % a) : 0); }
void __increment(pilha *p, i32 value)     { push(p, pop(p) + 1); }
void __decrement(pilha *p, i32 value)     { push(p, pop(p) - 1); }
void __absolute(pilha *p, i32 value)      { i32 a = pop(p); push(p, (a > 0) ? a : -a); }
void __maximum(pilha *p, i32 value)       { i32 a = pop(p), b = pop(p); push(p, (b > a) ? b : a); }
void __minimum(pilha *p, i32 value)       { i32 a = pop(p), b = pop(p); push(p, (b < a) ? b : a); }
void __equal(pilha *p, i32 value)         { i32 a = pop(p), b = pop(p); push(p, b == a); }
void __more(pilha *p, i32 value)          { i32 a = pop(p), b = pop(p); push(p, b > a); }
void __moreequal(pilha *p, i32 value)     { i32 a = pop(p), b = pop(p); push(p, b >= a); }
void __less(pilha *p, i32 value)          { i32 a = pop(p), b = pop(p); push(p, b < a); }
void __lessequal(pilha *p, i32 value)     { i32 a = pop(p), b = pop(p); push(p, b <= a); }
void __and(pilha *p, i32 value)           { i32 a = pop(p), b = pop(p); push(p, b && a); }
void __or(pilha *p, i32 value)            { i32 a = pop(p), b = pop(p); push(p, b || a); }
void __not(pilha *p, i32 value)           { push(p, !pop(p)); }
void __jump(pilha *p, i32 value)          { p->bytecode_index = p->vvariable[value]; }
void __iftrue(pilha *p, i32 value)        { if(!pop(p)) p->bytecode_index++; }
void __iffalse(pilha *p, i32 value)       { if(pop(p)) p->bytecode_index++; }
void __exit(pilha *p, i32 value)          { p->bytecode_index = p->bytecode_size; }

void __call(pilha *p, i32 value) {
    p->cstack[p->cstack_top] = p->bytecode_index;
    p->cstack_top++;
    p->bytecode_index =  p->vvariable[value];
    if(p->cstack_top == p->cstack_size) {
        p->cstack_size *= 2;
        p->cstack = realloc(p->cstack, p->cstack_size * sizeof(i32));
    }
}

void __return(pilha *p, i32 value) {
    if(p->cstack_top == 0) {
        printf("ERROR! Tried to return, but no call was executed.\n");
        exit(1);
    }
    p->cstack_top--;
    p->bytecode_index = p->cstack[p->cstack_top];
}

pilha_command __default[] = {
    {"PUSHAT",    __pushat},
    {"PUSH",      __push},
    {"POPAT",     __popat},
    {"POP",       __pop},
    {"COPY",      __copy},
    {"SWAP",      __swap},
    {"ADD",       __add},
    {"SUBTRACT",  __subtract},
    {"MULTIPLY",  __multiply},
    {"DIVIDE",    __divide},
    {"MODULO",    __modulo},
    {"INCREMENT", __increment},
    {"DECREMENT", __decrement},
    {"ABSOLUTE",  __absolute},
    {"MINIMUM",   __minimum},
    {"MAXIMUM",   __maximum},
    {"EQUAL",     __equal},
    {"MOREEQUAL", __moreequal},
    {"MORE",      __more},
    {"LESSEQUAL", __lessequal},
    {"LESS",      __less},
    {"AND",       __and},
    {"OR",        __or},
    {"NOT",       __not},
    {"JUMP",      __jump},
    {"IFTRUE",    __iftrue},
    {"IFFALSE",   __iffalse},
    {"EXIT",      __exit},
    {"CALL",      __call},
    {"RETURN",    __return}
};

pilha *pilha_new() {
    pilha *p = malloc(sizeof(pilha));
    
    p->mnemonic_size = sizeof(__default) / sizeof(pilha_command);
    p->mnemonic = __default;
    
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

void pilha_file(pilha *p, char *file) {
    free(p->cstack);
    free(p->bytecode);
    
    p->cstack_size = 16;
    p->bytecode_size = 0;
    
    p->cstack = malloc(p->cstack_size * sizeof(i32));
    p->bytecode = NULL;

    FILE* f = fopen(file, "r");
    if(!f) {
        printf("ERROR! Failed to open file.");
        exit(1);
    }
    
    char buffer[512];
    while(fgets(buffer, 512, f) != NULL) {
        char format[512];
        int i1 = 0;
        int i2 = 0;
        
        while(buffer[i1] != '\0' && buffer[i1] != '\n' && buffer[i1] != ';') {
            if(buffer[i1] != ' ') {
                if(buffer[i1] >= 'a' && buffer[i1] <= 'z')
                    buffer[i1] -= 'a' - 'A';
                format[i2++] = buffer[i1];
                format[i2] = '\0';
            }
            i1++;
        }
        
        if(i2 == 0) continue;
        if(format[i2 - 1] == ':') {
            format[i2 - 1] = '\0';
            p->vvariable[table(p, format)] = p->bytecode_size - 1;
            continue;
        }
        
        for(i1 = 0; i1 < p->mnemonic_size; i1++) {
            i2 = strlen(p->mnemonic[i1].key);
            if(strncmp(p->mnemonic[i1].key, format, i2) == 0) {
                p->bytecode = realloc(p->bytecode, sizeof(pilha_instruction) * (p->bytecode_size + 1));
                u32 *index = &p->bytecode[p->bytecode_size].index;
                i32 *value = &p->bytecode[p->bytecode_size].value;
                char *end;
                
                *index = i1;
                *value = 0;
                if(format[i2] != '\0') {
                    *value = strtol(format + i2, &end, 10);
                    if(format + i2 == end)
                        *value = table(p, format + i2);
                }
                
                p->bytecode_size++;
                break;
            }
        }
        
        if(p->mnemonic_size == i1) {
            printf("ERROR! Invalid \"%s\", didn't find any known command.\n", format);
            exit(1);
        }
    }
    fclose(f);
}

void pilha_run(pilha *p) {
    p->bytecode_index = 0;
    
    while(p->bytecode_index < p->bytecode_size) {
        u32 index = p->bytecode[p->bytecode_index].index;
        i32 value = p->bytecode[p->bytecode_index].value;
        
        p->mnemonic[index].function(p, value);
        p->bytecode_index++;
    }
}

void pilha_wipe(pilha *p) {
    free(p->dstack);
    free(p->vvariable);
    for(int i = 0; i < p->variable_size; i++)
        free(p->kvariable[i]);
    free(p->kvariable);

    p->dstack_size = 128;
    p->variable_size = 0;
    
    p->dstack = malloc(p->dstack_size * sizeof(i32));
    p->vvariable = NULL;
    p->kvariable = NULL;
}

void pilha_push(pilha *p, i32 value)     { push(p, value); }
i32 pilha_pop(pilha *p)                  { return pop(p); }
i32 *pilha_variable(pilha *p, char *key) { return &p->vvariable[table(p, key)]; }
