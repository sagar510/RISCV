#include <stdio.h>
#include <stdlib.h>
#include "parsed.h"

void print_yaml_escaped(const char *key, const char *value) {
    printf("%s: \"", key);
    for (const char *p = value; *p; p++) {
        switch (*p) {
            case '\n': printf("\\n"); break;
            case '"':  printf("\\\""); break;
            case '\\': printf("\\\\"); break;
            default:   putchar(*p);
        }
    }
    printf("\"\n");
}

int main(){
    for(int i=0; mystruct[i].key != NULL; i++){
        print_yaml_escaped(mystruct[i].key, mystruct[i].value);
    }
    fprintf(stderr, "[OK] Generated YAML from C header.\n");
    return 0;
}