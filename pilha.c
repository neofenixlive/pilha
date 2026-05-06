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

void _push(pilha *p, i32 value)      { push(p, value); }
void _pop(pilha *p, i32 value)       { pop(p); }
void _push_v(pilha *p, i32 value)    { push(p, p->vvariable[value]); }
void _pop_v(pilha *p, i32 value)     { p->vvariable[value] = pop(p); }
void _copy(pilha *p, i32 value)      { i32 a = pop(p); push(p, a); push(p, a); }
void _swap(pilha *p, i32 value)      { i32 a = pop(p), b = pop(p); push(p, a); push(p, b); }
void _add(pilha *p, i32 value)       { i32 a = pop(p), b = pop(p); push(p, b + a); }
void _subtract(pilha *p, i32 value)  { i32 a = pop(p), b = pop(p); push(p, b - a); }
void _multiply(pilha *p, i32 value)  { i32 a = pop(p), b = pop(p); push(p, b * a); }
void _divide(pilha *p, i32 value)    { i32 a = pop(p), b = pop(p); push(p, a ? (b / a) : 0); }
void _modulo(pilha *p, i32 value)    { i32 a = pop(p), b = pop(p); push(p, a ? (b % a) : 0); }
void _increment(pilha *p, i32 value) { push(p, pop(p) + 1); }
void _decrement(pilha *p, i32 value) { push(p, pop(p) - 1); }
void _equal(pilha *p, i32 value)     { i32 a = pop(p), b = pop(p); push(p, b == a); }
void _more(pilha *p, i32 value)      { i32 a = pop(p), b = pop(p); push(p, b > a); }
void _less(pilha *p, i32 value)      { i32 a = pop(p), b = pop(p); push(p, b < a); }
void _and(pilha *p, i32 value)       { i32 a = pop(p), b = pop(p); push(p, b && a); }
void _or(pilha *p, i32 value)        { i32 a = pop(p), b = pop(p); push(p, b || a); }
void _not(pilha *p, i32 value)       { push(p, !pop(p)); }
void _jump(pilha *p, i32 value)      { p->bytecode_index = p->vvariable[value]; }
void _branch(pilha *p, i32 value)    { if (pop(p)) p->bytecode_index = p->vvariable[value]; }
void _halt(pilha *p, i32 value)      { p->bytecode_index = p->bytecode_size; }

void _call(pilha *p, i32 value) {
    p->cstack[p->cstack_top] = p->bytecode_index;
    p->cstack_top++;
    p->bytecode_index =  p->vvariable[value];
    if(p->cstack_top == p->cstack_size) {
        p->cstack_size *= 2;
        p->cstack = realloc(p->cstack, p->cstack_size * sizeof(i32));
    }
}

void _return(pilha *p, i32 value) {
    if(p->cstack_top == 0) {
        printf("ERROR! Tried to return, but no call was executed.\n");
        exit(1);
    }
    p->cstack_top--;
    p->bytecode_index = p->cstack[p->cstack_top];
}

pilha_command _default[] = {
    {"PUSH",      NULL, _push, _push_v},
    {"POP",       _pop, NULL, _pop_v},
    {"COPY",      _copy, NULL, NULL},
    {"SWAP",      _swap, NULL, NULL},
    {"ADD",       _add, NULL, NULL},
    {"SUBTRACT",  _subtract, NULL, NULL},
    {"MULTIPLY",  _multiply, NULL, NULL},
    {"DIVIDE",    _divide, NULL, NULL},
    {"INCREMENT", _increment, NULL, NULL},
    {"DECREMENT", _decrement, NULL, NULL},
    {"MODULO",    _modulo, NULL, NULL},
    {"EQUAL",     _equal, NULL, NULL},
    {"MORE",      _more, NULL, NULL},
    {"LESS",      _less, NULL, NULL},
    {"AND",       _and, NULL, NULL},
    {"OR",        _or, NULL, NULL},
    {"NOT",       _not, NULL, NULL},
    {"JUMP",      NULL, NULL, _jump},
    {"BRANCH",    NULL, NULL, _branch},
    {"HALT",      _halt, NULL, NULL},
    {"CALL",      NULL, NULL, _call},
    {"RETURN",    _return, NULL, NULL}
};

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

pilha *pilha_new() {
    pilha *p = malloc(sizeof(pilha));
    
    p->mnemonic_size = sizeof(_default) / sizeof(pilha_command);
    p->mnemonic = _default;
    
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
    FILE* f = fopen(file, "r");
    if(!f) {
        printf("ERROR! Failed to open file.");
        exit(1);
    }
    
    free(p->bytecode);
    p->bytecode = NULL;
    p->bytecode_size = 0;
    
    char buffer[512];
    while(fgets(buffer, 512, f) != NULL) {
        char format[512];
        int i1 = 0, i2 = 0;
        while(buffer[i1] != '\0' && buffer[i1] != '\n' && buffer[i1] != ';') {
            if(buffer[i1] != ' ') {
                if(buffer[i1] >= 'a' && buffer[i1] <= 'z') buffer[i1] -= 'a' - 'A';
                format[i2] = buffer[i1];
                format[i2 + 1] = '\0';
                i2++;
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
                if(format[i2] != '\0') {
                    char *end;
                    i32 value = strtol(format + i2, &end, 10);
                    if(format + i2 != end) {
                        p->bytecode[p->bytecode_size].command = p->mnemonic[i1].function_n;
                        p->bytecode[p->bytecode_size].value = value;
                    } else {
                        p->bytecode[p->bytecode_size].command = p->mnemonic[i1].function_v;
                        p->bytecode[p->bytecode_size].value = table(p, format + i2);
                    }
                } else {
                    p->bytecode[p->bytecode_size].command = p->mnemonic[i1].function;
                    p->bytecode[p->bytecode_size].value = 0;
                }
                if(p->bytecode[p->bytecode_size].command == NULL) {
                    printf("ERROR! Invalid \"%s\", can't run with these values.\n", p->mnemonic[i1].key);
                    exit(1);
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
        p->bytecode[p->bytecode_index].command(p, p->bytecode[p->bytecode_index].value);
        p->bytecode_index++;
    }
}

void pilha_push(pilha *p, i32 value)     { push(p, value); }
i32 pilha_pop(pilha *p)                  { return pop(p); }
i32 *pilha_variable(pilha *p, char* key) { return &p->vvariable[table(p, key)]; }