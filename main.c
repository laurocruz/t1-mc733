#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "aes.h"

struct timespec diff(struct timespec start, struct timespec end);
static void test_encrypt_cbc(char arq[]);
static void test_decrypt_cbc(char arq[]);


int main(int argc, char* argv[])
{
    if (argc == 1 || argc > 3)
        printf("How to use:\n./aes arq_enc.pt [arq_dec.ct]\n");
    else { 
        test_encrypt_cbc(argv[1]);
        if (argc == 3)
            test_decrypt_cbc(argv[2]);
    }

    return 0;
}

struct timespec diff(struct timespec start, struct timespec end)
{
    struct timespec temp;
    if ((end.tv_nsec-start.tv_nsec)<0) {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp;
}

static void test_decrypt_cbc(char arq[])
{

    uint8_t key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
    uint8_t iv[]  = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
    FILE* inf = fopen(arq, "r");
    long length;
    uint8_t * in;
    uint8_t * buffer;
    struct timespec cpu_t1, cpu_t2, r_t1, r_t2;

    if (inf) {
        fseek(inf, 0, SEEK_END);
        length = ftell(inf);
        fseek(inf, 0, SEEK_SET);
        in = malloc(length);
        if (in)
            fread(in, 1, length, inf);
        buffer = malloc(length);
        if(buffer) {
            clock_gettime(CLOCK_REALTIME, &r_t1);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &cpu_t1);
            AES128_CBC_decrypt_buffer(buffer, in, length, key, iv);
            clock_gettime(CLOCK_REALTIME, &r_t2);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &cpu_t2);
            cpu_t1 = diff(cpu_t1, cpu_t2);
            r_t1 = diff(r_t1, r_t2);
            printf("DEC REAL TIME = %ld.%ld\n", r_t1.tv_sec, r_t1.tv_nsec);
            printf("DEC CPU TIME = %ld.%ld\n", cpu_t1.tv_sec, cpu_t1.tv_nsec);
        }
        fclose(inf);
    }

}

static void test_encrypt_cbc(char arq[])
{
    uint8_t key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
    uint8_t iv[]  = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

    FILE* inf = fopen(arq, "r");
    long length;
    uint8_t * in;
    uint8_t * buffer;
    struct timespec cpu_t1, cpu_t2, r_t1, r_t2;

    if (inf) {
        fseek(inf, 0, SEEK_END);
        length = ftell(inf);
        fseek(inf, 0, SEEK_SET);
        in = malloc(length);
        if (in)
            fread(in, 1, length, inf);
        buffer = malloc(length);
        if(buffer) { 
            clock_gettime(CLOCK_REALTIME, &r_t1);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &cpu_t1);
            AES128_CBC_encrypt_buffer(buffer, in, length, key, iv);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &cpu_t2);
            clock_gettime(CLOCK_REALTIME, &r_t2);
            cpu_t1 = diff(cpu_t1, cpu_t2);
            r_t1 = diff(r_t1, r_t2);
            printf("ENC REAL TIME = %ld.%ld\n", r_t1.tv_sec, r_t1.tv_nsec);
            printf("ENC CPU TIME = %ld.%ld\n", cpu_t1.tv_sec, cpu_t1.tv_nsec);
        }
        fclose(inf);
    }

}


