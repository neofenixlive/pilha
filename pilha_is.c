#include "pilha.h"

void __push(pilha *p, i32 value)          { pilha_push(p, value); }
void __pop(pilha *p, i32 value)           { pilha_pop(p); }
void __pushat(pilha *p, i32 value)        { pilha_push(p, p->vvariable[value]); }
void __popat(pilha *p, i32 value)         { p->vvariable[value] = pilha_pop(p); }
void __copy(pilha *p, i32 value)          { i32 a = pilha_pop(p); pilha_push(p, a); pilha_push(p, a); }
void __swap(pilha *p, i32 value)          { i32 a = pilha_pop(p), b = pilha_pop(p); pilha_push(p, a); pilha_push(p, b); }
void __add(pilha *p, i32 value)           { i32 a = pilha_pop(p), b = pilha_pop(p); pilha_push(p, b + a); }
void __subtract(pilha *p, i32 value)      { i32 a = pilha_pop(p), b = pilha_pop(p); pilha_push(p, b - a); }
void __multiply(pilha *p, i32 value)      { i32 a = pilha_pop(p), b = pilha_pop(p); pilha_push(p, b * a); }
void __divide(pilha *p, i32 value)        { i32 a = pilha_pop(p), b = pilha_pop(p); pilha_push(p, a ? (b / a) : 0); }
void __modulo(pilha *p, i32 value)        { i32 a = pilha_pop(p), b = pilha_pop(p); pilha_push(p, a ? (b % a) : 0); }
void __increment(pilha *p, i32 value)     { pilha_push(p, pilha_pop(p) + 1); }
void __decrement(pilha *p, i32 value)     { pilha_push(p, pilha_pop(p) - 1); }
void __absolute(pilha *p, i32 value)      { i32 a = pilha_pop(p); pilha_push(p, (a > 0) ? a : -a); }
void __negate(pilha *p, i32 value)        { i32 a = pilha_pop(p); pilha_push(p, -a); }
void __maximum(pilha *p, i32 value)       { i32 a = pilha_pop(p), b = pilha_pop(p); pilha_push(p, (b > a) ? b : a); }
void __minimum(pilha *p, i32 value)       { i32 a = pilha_pop(p), b = pilha_pop(p); pilha_push(p, (b < a) ? b : a); }
void __equal(pilha *p, i32 value)         { i32 a = pilha_pop(p), b = pilha_pop(p); pilha_push(p, b == a); }
void __more(pilha *p, i32 value)          { i32 a = pilha_pop(p), b = pilha_pop(p); pilha_push(p, b > a); }
void __less(pilha *p, i32 value)          { i32 a = pilha_pop(p), b = pilha_pop(p); pilha_push(p, b < a); }
void __notequal(pilha *p, i32 value)      { i32 a = pilha_pop(p), b = pilha_pop(p); pilha_push(p, b != a); }
void __moreequal(pilha *p, i32 value)     { i32 a = pilha_pop(p), b = pilha_pop(p); pilha_push(p, b >= a); }
void __lessequal(pilha *p, i32 value)     { i32 a = pilha_pop(p), b = pilha_pop(p); pilha_push(p, b <= a); }
void __and(pilha *p, i32 value)           { i32 a = pilha_pop(p), b = pilha_pop(p); pilha_push(p, b && a); }
void __or(pilha *p, i32 value)            { i32 a = pilha_pop(p), b = pilha_pop(p); pilha_push(p, b || a); }
void __not(pilha *p, i32 value)           { pilha_push(p, !pilha_pop(p)); }
void __jump(pilha *p, i32 value)          { p->bytecode_index = p->vvariable[value]; }
void __exit(pilha *p, i32 value)          { p->bytecode_index = p->bytecode_size; }
void __iftrue(pilha *p, i32 value)        { if(!pilha_pop(p)) p->bytecode_index++; }
void __iffalse(pilha *p, i32 value)       { if(pilha_pop(p)) p->bytecode_index++; }

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

pilha_token pilha_mnemonic[] = {
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
    {"NEGATE",    __negate},
    {"MINIMUM",   __minimum},
    {"MAXIMUM",   __maximum},
    {"EQUAL",     __equal},
    {"MOREEQUAL", __moreequal},
    {"MORE",      __more},
    {"LESSEQUAL", __lessequal},
    {"LESS",      __less},
    {"NOTEQUAL",  __notequal},
    {"AND",       __and},
    {"OR",        __or},
    {"NOT",       __not},
    {"JUMP",      __jump},
    {"EXIT",      __exit},
    {"IFTRUE",    __iftrue},
    {"IFFALSE",   __iffalse},
    {"CALL",      __call},
    {"RETURN",    __return},
    {NULL,        NULL}
};
