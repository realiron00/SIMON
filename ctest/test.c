#include <stdio.h>
#include <stdint.h>

int main()
{
    uint64_t z=0b10101111011100000011010010011000101000010001111110010110110011;
    printf("sizeof(uint8_t) = %lu\n", sizeof(uint8_t));
    printf("sizeof(z) = %lu\n", sizeof(z));
    //맨 앞부터 한 비트씩 추출
    uint8_t temp = 0;
    for(int i = 0; i < 64; i++)
    {
        printf("0b%d, ", (z >> (63 - i)) & 1);
    }
}