struct h8900
{
	unsigned int magic;
	unsigned char version[3];
	unsigned char encrypted;
	unsigned int u;
	unsigned int dataSize;
	unsigned int sigOffset;
	unsigned int certOffset;
	unsigned int certSize;
	unsigned char sig1[32];
	unsigned int epoch;
	unsigned char sig2[16];
	unsigned char unknown3[1968];
};

struct f8900
{
	unsigned char sig[0x80];
	unsigned char cert[0xc0a];
};

struct hKernel
{
  unsigned int magic;
  unsigned int compress_type;
  unsigned int adler32;
  unsigned int uncompressed_size;
  unsigned int compressed_size;
  unsigned int reserved[11];
  char platform_name[64];
  char root_path[256];
  unsigned char data[0];
};

struct hImg2
{
	unsigned int magic;
	unsigned int name;
	unsigned int u1;
	unsigned int u2;
	unsigned int dataLenPadded;
	unsigned int dataLen;
	unsigned int u3;
	unsigned int u4;
	unsigned char sig1[64];
	unsigned int u5;
	unsigned int crc;
	unsigned int u6;
	unsigned int u7;
	unsigned int srev;
	unsigned int u8;
	char text[872];
	unsigned char sig2[32];
}; 

struct hBootIm
{
	char magic[8];
	unsigned int checksum;
	unsigned int comp;
	unsigned int type;
	unsigned short width;
	unsigned short height;
	unsigned int u[10];
};

typedef struct h8900 h8900; 
typedef struct f8900 f8900;
typedef struct hKernel hKernel; 
typedef struct hImg2 hImg2; 
typedef struct hBootIm hBootIm; 

#define Encrypted8900	0x3

#define IsImg2File		0x1
#define IsBootImFile	0x2
#define IsKernelFile	0x4
#define IsPlainFile 	0x8

int parse8900(const char* filename, h8900* pHeader8900, f8900* pFooter8900, hKernel* pHeaderKernel, hImg2* pHeaderImg2, hBootIm* pHeaderBootIm, int* pFlags, int extract, const char* output);
int extractFile(unsigned char* p, unsigned int size, hKernel* pHeaderKernel, hImg2* pHeaderImg2, hBootIm* pHeaderBootIm, int* pFlags, const char* filename);

int doKernelFile(const char* filename, h8900* pHeader8900, f8900* pFooter8900, hKernel* pHeaderKernel, const char* output);
int doPlainFile(const char* filename, h8900* pHeader8900, f8900* pFooter8900, const char* output);
int doImg2File(const char* filename, h8900* pHeader8900, f8900* pFooter8900, hImg2* pHeaderImg2, const char* output);
int doBootImFile(const char* filename, h8900* pHeader8900, f8900* pFooter8900, hImg2* pHeaderImg2, hBootIm* pHeaderBootIm, const char* output);

void resignHeader8900(h8900* pHeader8900);
unsigned int endian_swap(unsigned int x); 

unsigned char* read_png(FILE *fp, unsigned int *width, unsigned int *height, unsigned int *gray);
