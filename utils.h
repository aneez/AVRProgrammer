#ifndef UTILS_H
#define UTILS_H
struct hexLine{
	uint32_t size;
	uint32_t address;
    uint32_t page;
	uint32_t* dataArray;
	struct hexLine* pNextLine;
}; 
typedef struct hexLine HEX_LINE;

void Usleep(uint16_t);
uint32_t* parseLine(char *,int);
HEX_LINE* parseHexFile(char*);
void printHexfile(HEX_LINE*);
void deleteHexfile(HEX_LINE*);
#endif
