#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "aes.h"

static void phex(uint8_t* str);
static void test_encrypt_cbc(void);
static void test_decrypt_cbc(void);


int main(void)
{
    test_encrypt_cbc();
    test_decrypt_cbc();

    return 0;
}



// prints string as hex
static void phex(uint8_t* str)
{
    unsigned char i;
    for(i = 0; i < 16; ++i)
        printf("%.2x", str[i]);
    printf("\n");
}


static void test_decrypt_cbc(void)
{
    // Example "simulating" a smaller buffer...

    uint8_t key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
    uint8_t iv[]  = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
    FILE* inf = fopen("test500MB.ct", "r");
    long length;
    uint8_t * in;
    uint8_t * buffer;
    clock_t start, stop;

    if (inf) {
        fseek(inf, 0, SEEK_END);
        length = ftell(inf);
        fseek(inf, 0, SEEK_SET);
        in = malloc(length);
        if (in)
            fread(in, 1, length, inf);
        buffer = malloc(length);
        if(buffer) { 
            start = clock();
            AES128_CBC_decrypt_buffer(buffer, in, length, key, iv);
            stop = clock();
            printf("DEC = %lf\n", (stop-start)/(float)CLOCKS_PER_SEC);
            printf("DECRYPT DONE\n");
        }
    fclose(inf);
    }

}

static void test_encrypt_cbc(void)
{
    uint8_t key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
    uint8_t iv[]  = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

    FILE* inf = fopen("test500MB.pt", "r");
    long length;
    uint8_t * in;
    uint8_t * buffer;
    clock_t start, stop;

    if (inf) {
        fseek(inf, 0, SEEK_END);
        length = ftell(inf);
        fseek(inf, 0, SEEK_SET);
        in = malloc(length);
        if (in)
            fread(in, 1, length, inf);
        buffer = malloc(length);
        if(buffer) { 
            start = clock();
            AES128_CBC_encrypt_buffer(buffer, in, length, key, iv);
            stop = clock();
            printf("ENC = %lf\n", (stop-start)/(float)CLOCKS_PER_SEC);
            printf("ENCRYPT DONE\n");
        }
        fclose(inf);
    }

}


