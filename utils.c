#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "utils.h"
void Usleep(uint16_t usec)
{
  volatile uint32_t i;
  for(i=0;i<usec*10000;i++);
}

uint32_t* parseLine(char *Data,int size)
{
	int i=0;	
	uint32_t *pData=(uint32_t*)malloc(sizeof(uint32_t)*size);
	while(i<size)
	{
		sscanf(Data,"%2x",pData+i);
		Data=Data+2;
		i=i+1;
	}
	printf("\n");
	return pData;
}

HEX_LINE* parseHexFile(char *fInput)
{
	FILE* fp;
	fp = fopen(fInput, "r");
	char line[512];
        uint32_t iTemp;
	HEX_LINE *pHexfile=NULL,*pTemp1=NULL,*pTemp2=NULL;
	
	if(!fp){
		printf("File not Found!!. Exiting...");
		exit(1);
	}	
	else
	{
	   while(fgets(line,sizeof(line),fp))
	   {
              int recordType;
              sscanf(line+7,"%2x",&recordType);
              if(recordType!=0x00)
                 continue;
	      pTemp1=(HEX_LINE*)malloc(sizeof(HEX_LINE));
	      pTemp1->pNextLine = NULL;
	      sscanf(line+1,"%2x",&iTemp);
              pTemp1->size=iTemp>>1;
	      sscanf(line+3,"%4x",&iTemp);
              iTemp>>=1; //2 byte memory address at AVR
              pTemp1->page=(iTemp>>6)&0xff;            
              pTemp1->address=iTemp&0x3f;
	      pTemp1->dataArray = parseLine(line+9,2*pTemp1->size);
			
	      if(!pHexfile)
	         pHexfile=pTemp1;
	      else
              {
                 pTemp2=pHexfile;
                 while((pTemp2->pNextLine)!=NULL)
                    pTemp2=(pTemp2->pNextLine);           
                 pTemp2->pNextLine=pTemp1;
	      }
	    }
    }
    return pHexfile;
}

void printHexfile(HEX_LINE *pHex)
{
	uint32_t i;
	printf("Size\tPage\tAddress\tData\n");
	while(pHex)
	{
		printf("%02x\t%02x\t%02x\t",pHex->size,pHex->page,pHex->address);
		for(i=0;i<(pHex->size);i++)
			printf("%02x%02x\t",(pHex->dataArray)[2*i],(pHex->dataArray)[2*i+1]);		
		printf("\n");
		pHex=pHex->pNextLine;
	}
}

void deleteHexfile(HEX_LINE *pHex)
{
	HEX_LINE* ptemp;
	while(pHex)
	{
		ptemp=pHex->pNextLine;
		free(pHex->dataArray);
		free(pHex);
		pHex=ptemp;
	}	
}
