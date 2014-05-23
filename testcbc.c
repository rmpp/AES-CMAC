#include "aes_cbc.h"
#include <sys/types.h>
#include <inttypes.h>

int main(int argc, const char *argv[])
{                                	
	
	uint8_t data[] = 
{ 
    0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 
    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
    
    0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 
    0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
    
    0x00, 0x11};
	
	uint8_t key[] = 
	{ 
		0x11, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80,
		0x90, 0xa0, 0xb0, 0xc0, 0xd0, 0xe0, 0xf0, 0x00};
		
	uint8_t k1[] = 
	{ 
		0x12, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80,
		0x90, 0xa0, 0xb0, 0xc0, 0xd0, 0xe0, 0xf0, 0x00};
		
	uint8_t k2[] = 
	{ 
		0x13, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80,
		0x90, 0xa0, 0xb0, 0xc0, 0xd0, 0xe0, 0xf0, 0x00};		
		
	uint8_t iv[]=
	{
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	uint8_t iv2[]=
	{
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	uint8_t iv3[]=
	{
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	unsigned char mac[16];
	unsigned char mac_rev[16];
	
	int len = sizeof(data);
	int e = 0;

/*	
	printf("\n DATA \n");
	for(e = 0; e < len; e++){
		printf("%02x, ",data[e] & 0xff);
		}
*/

	int finallen=16;
	if (len % 16 != 0) {
	finallen = len % 16;
	}
		
	uint8_t newdata[len+(16-finallen)];
	uint8_t newdata1[len+(16-finallen)];
	
	memcpy(newdata,data,len);
	aes_cbc_encript(newdata,len,key,iv,k1,k2,mac);
/*	
	printf("print MAC \n"); 
	for(e = 0; e <16 ; e++){
		printf("%02x",mac[e] & 0xff);
		}
*/
	int lenNew = sizeof(newdata);
	printf("\n Criptograma \n");
	for(e = 0; e < lenNew ; e++){
		printf("%02x, ",newdata[e] & 0xff);
		}
	
	//printf("\n sizeof %d\n",len);
	
	aes_cbc_decript(newdata,lenNew,key,iv2,k1);
	
/*	printf("\n DATA \n");
	for(e = 0; e < lenNew; e++){
		printf("%02x, ",newdata[e] & 0xff);
		}
*/
	
	memcpy(newdata1,newdata,len);
	
	aes_cbc_encript(newdata1,len,key,iv3,k1,k2,mac_rev);
/*	
	printf("print MAC \n"); 
	for(e = 0; e <16 ; e++){
		printf("%02x",mac[e] & 0xff);
		}
*/

	printf("\n DATA \n");
	for(e = 0; e < lenNew; e++){
		printf("%02x, ",newdata[e] & 0xff);
		}
	
	if(memcmp(data,newdata,len)==0){
		printf("\n Equals \n");
		}
	
	if(memcmp(mac,mac_rev,16)==0){
		printf(" MAC Equals \n");
		}
return 0;
}
