#define bool char
#define true 1
#define false 0

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <time.h>

const char hex_asc[] = "0123456789abcdef";
#define hex_asc_lo(x)	hex_asc[((x) & 0x0f)]
#define hex_asc_hi(x)	hex_asc[((x) & 0xf0) >> 4]

static inline char *hex_byte_pack(char *buf, uint8_t byte)
{
	*buf++ = hex_asc_hi(byte);
	*buf++ = hex_asc_lo(byte);
	return buf;
}

/**
* bin2hex - convert binary data to an ascii hexadecimal string
* @dst: ascii hexadecimal result
* @src: binary data
* @count: binary data length
*/
char *bin2hex(char *dst, const void *src, size_t count)
{
	const unsigned char *_src = src;

	while (count--)
	{
		dst = hex_byte_pack(dst, *_src++);
	}

	return dst;
}

static void hex_output(const char* buf, size_t len)
{
	size_t i;
	printf("---- Hex output start ----\n");
	for(i=0; i<len; i++)
	{
		if( i!=0 && 0==i%16) printf("\n");
		printf("%02x ", (unsigned char)buf[i]);
	}

	printf("\n---- Hex output end ----\n");
}

void hex_dump(const void* data, size_t size) {
	char ascii[17];
	size_t i, j;
	ascii[16] = '\0';
	for (i = 0; i < size; ++i) {
		printf("%02X ", ((unsigned char*)data)[i]);
		if (((unsigned char*)data)[i] >= ' ' && ((unsigned char*)data)[i] <= '~') {
			ascii[i % 16] = ((unsigned char*)data)[i];
		} else {
			ascii[i % 16] = '.';
		}
		if ((i+1) % 8 == 0 || i+1 == size) {
			printf(" ");
			if ((i+1) % 16 == 0) {
				printf("|  %s \n", ascii);
			} else if (i+1 == size) {
				ascii[(i+1) % 16] = '\0';
				if ((i+1) % 16 <= 8) {
					printf(" ");
				}
				for (j = (i+1) % 16; j < 16; ++j) {
					printf("   ");
				}
				printf("|  %s \n", ascii);
			}
		}
	}
}

int main(int argc, char argv[])
{
	char buf[32] = "1234567890abcdef1234";

	hex_output(buf, 20);
	hex_dump(buf, 20);
	return 1;
}


