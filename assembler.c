// Geovanny Quiroz

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * ltrim(char * s) {
    while ( * s == ' ' || * s == '\t') s++;
    return s;
}

char getRegister(char * text) {
    if ( * text == 'r' || * text == 'R') text++;
    return atoi(text);
}

int assembleLine(char * text, unsigned char * bytes) {
    text = ltrim(text);
    char * keyWord = strtok(text, " ");
    if (strcmp("add", keyWord) == 0) {
        bytes[0] = 0x10;
        bytes[0] |= getRegister(strtok(NULL, " "));
        bytes[1] = getRegister(strtok(NULL, " ")) << 4 | getRegister(strtok(NULL, " "));
        return 2;
    } else if (strcmp("and", keyWord) == 0) {
        bytes[0] = 0x20;
        bytes[0] |= getRegister(strtok(NULL, " "));
        bytes[1] = getRegister(strtok(NULL, " ")) << 4 | getRegister(strtok(NULL, " "));
        return 2;
    } else if (strcmp("divide", keyWord) == 0) {
        bytes[0] = 0x30;
        bytes[0] |= getRegister(strtok(NULL, " "));
        bytes[1] = getRegister(strtok(NULL, " ")) << 4 | getRegister(strtok(NULL, " "));
        return 2;
    } else if (strcmp("halt", keyWord) == 0) {
        bytes[0] = 0x00;
        bytes[0] |= getRegister(strtok(NULL, " "));
        bytes[1] = getRegister(strtok(NULL, " ")) << 4 | getRegister(strtok(NULL, " "));
        return 2;
    } else if (strcmp("multiply", keyWord) == 0) {
        bytes[0] = 0x40;
        bytes[0] |= getRegister(strtok(NULL, " "));
        bytes[1] = getRegister(strtok(NULL, " ")) << 4 | getRegister(strtok(NULL, " "));
        return 2;
    } else if (strcmp("or", keyWord) == 0) {
        bytes[0] = 0x60;
        bytes[0] |= getRegister(strtok(NULL, " "));
        bytes[1] = getRegister(strtok(NULL, " ")) << 4 | getRegister(strtok(NULL, " "));
        return 2;
    } else if (strcmp("subtract", keyWord) == 0) {
        bytes[0] = 0x50;
        bytes[0] |= getRegister(strtok(NULL, " "));
        bytes[1] = getRegister(strtok(NULL, " ")) << 4 | getRegister(strtok(NULL, " "));
        return 2;
    } else if (strcmp("addimmediate", keyWord) == 0) {
        bytes[0] = 0x90;
        bytes[0] |= getRegister(strtok(NULL, " "));
        bytes[1] = atoi(strtok(NULL, " "));
        return 2;
    } else if (strcmp("branchifequal", keyWord) == 0) {
        bytes[0] = 0xa0;
        bytes[0] |= getRegister(strtok(NULL, " "));
        
        bytes[1] = getRegister(strtok(NULL, " ")) << 4;
        
        // offset address
        char * temp = (strtok(NULL, " "));
        
        bytes[1] |= atoi(temp) << 4;
        bytes[2] = atoi(temp) << 8;
        bytes[3] = atoi(temp) & 8;
        return 4;
        
    } else if (strcmp("branchifless", keyWord) == 0) {
        bytes[0] = 0xb0;
        bytes[0] |= getRegister(strtok(NULL, " "));
        
        bytes[1] = getRegister(strtok(NULL, " ")) << 4;
        
        // offset address
        char * temp = (strtok(NULL, " "));
        bytes[1] |= atoi(temp) << 4;
        bytes[2] = atoi(temp) << 8;
        bytes[3] = atoi(temp) & 8;
        return 4;
        
    } else if (strcmp("interrupt", keyWord) == 0) {
        bytes[0] = 0x80;
        bytes[0] |= atoi(strtok(NULL, " ")) << 4;
        bytes[1] = atoi(strtok(NULL, " ")) & 8;
        return 2;
        
    } else if (strcmp("rightshift", keyWord) == 0) {
        bytes[0] = 0x70;
        bytes[0] |= getRegister(strtok(NULL, " "));
        int bitShift = atoi(strtok(NULL, " "));
        bytes[1] = 0x01 << 5;
        bytes[1] = bitShift;
        return 2;
    } else if (strcmp("leftshift", keyWord) == 0) {
        bytes[0] = 0x70;
        bytes[0] |= getRegister(strtok(NULL, " "));
        int bitShift = atoi(strtok(NULL, " "));
        bytes[1] = 0x00 << 5;
        bytes[1] = bitShift;
        return 2;
    } else if (strcmp("jump", keyWord) == 0) {
        bytes[0] = 0xc0;
        // offset address
        char * temp = (strtok(NULL, " "));
        bytes[0] |= atoi(temp) << 4;
        bytes[1] = atoi(temp) << 4;
        bytes[2] = atoi(temp) << 8;
        bytes[3] = atoi(temp) & 8;
        return 4;
    } else if (strcmp("load", keyWord) == 0) {
        bytes[0] = 0xe0;
        bytes[0] |= getRegister(strtok(NULL, " "));
        bytes[1] = getRegister(strtok(NULL, " ")) << 4;
        bytes[1] |= atoi(strtok(NULL, " "));
        return 2;
    } else if (strcmp("store", keyWord) == 0) {
        bytes[0] = 0xf0;
        bytes[0] |= getRegister(strtok(NULL, " "));
        bytes[1] = getRegister(strtok(NULL, " ")) << 4;
        bytes[1] |= atoi(strtok(NULL, " "));
        return 2;
    } else if (strcmp("iterateover", keyWord) == 0) {
        bytes[0] = 0xd0;
        bytes[0] |= getRegister(strtok(NULL, " "));
        bytes[1] = atoi(strtok(NULL, " "));
        // offset address
        int temp = atoi(strtok(NULL, " "));
        bytes[2] = temp << 8;
        bytes[3] = temp & 8;
        
        return 4;
        
    }
    return 0;
}

int main(int argc, char ** argv) {
    FILE * src = fopen(argv[1], "r");
    FILE * dst = fopen(argv[2], "w");
    while (!feof(src)) {
        unsigned char bytes[4];
        char line[1000];
        printf("about to read\n");
        if (NULL != fgets(line, 1000, src)) {
            printf("read: %s\n", line);
            int byteCount = assembleLine(line, bytes);
            fwrite(bytes, byteCount, 1, dst);
        }
    }
    fclose(src);
    fclose(dst);
    return 0;
}
