#include "pilha.h"

void pilha_file(pilha *p, char *file) {
    free(p->cstack);
    free(p->bytecode);
    
    p->cstack_top = 0;
    p->cstack_size = 16;
    p->bytecode_size = 0;
    
    p->cstack = malloc(p->cstack_size * sizeof(i32));
    p->bytecode = NULL;

    FILE* f = fopen(file, "r");
    if(!f) {
        printf("ERROR! Failed to open file.");
        exit(1);
    }
    
    char buffer[1024];
    while(fgets(buffer, 1024, f) != NULL) {
        char format[1024], *end;
        int i1 = 0, i2 = 0;
        
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
            p->vvariable[pilha_table(p, format)] = p->bytecode_size - 1;
            continue;
        }
        
        for(i1 = 0; pilha_mnemonic[i1].name != NULL; i1++) {
            i2 = strlen(pilha_mnemonic[i1].name);
            if(!strncmp(pilha_mnemonic[i1].name, format, i2)) {
                p->bytecode = realloc(p->bytecode, sizeof(pilha_instruction) * (p->bytecode_size + 1));
                u32 *token = &p->bytecode[p->bytecode_size].token;
                i32 *value = &p->bytecode[p->bytecode_size].value;
                
                *token = i1;
                *value = 0;
                if(format[i2] != '\0') {
                    *value = strtol(format + i2, &end, 10);
                    if(format + i2 == end)
                        *value = pilha_table(p, format + i2);
                }
                
                p->bytecode_size++;
                break;
            }
        }
        
        if(pilha_mnemonic[i1].name == NULL) {
            printf("ERROR! Invalid \"%s\", didn't find any known token.\n", format);
            exit(1);
        }
    }
    fclose(f);
}