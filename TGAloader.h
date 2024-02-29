#include <stdlib.h>
#include <stdio.h>
#include "TGAloader_private_functions.h"
rgbArray* loadTGA(char* path){
    FILE* file = fopen(path, "r");
    if(file == NULL){
        printf("no file :(");
        fclose(file);
        return NULL;
    }
    unsigned char headerBytes[18];
    fread(headerBytes, sizeof(unsigned char), 18, file);
    header headerTemp;
    headerTemp.idLength = headerBytes[0];
    headerTemp.colorMapType = headerBytes[1];
    headerTemp.dataTypeCode = headerBytes[2];
    printf("%i\n", headerTemp.colorMapType);
    headerTemp.colorMapOrigin = headerBytes[3] + (headerBytes[4] << 8);
    headerTemp.colorMapLength = headerBytes[5] + (headerBytes[6] << 8);
    headerTemp.colorMapDepth = headerBytes[7];
    printf("%i\n", headerTemp.colorMapDepth);
    headerTemp.xOrigin = headerBytes[8] + (headerBytes[9] << 8);
    headerTemp.yOrigin = headerBytes[10] + (headerBytes[11] << 8);
    headerTemp.width =  headerBytes[12] + (headerBytes[13] << 8);
    headerTemp.height = headerBytes[14] + (headerBytes[15] << 8); 
    headerTemp.bitDepth = headerBytes[16];
    headerTemp.imageDescriptor = headerBytes[17];
    printf("%i\n", headerTemp.colorMapLength);
    if(headerTemp.dataTypeCode == 2){
        return parseRGB(&headerTemp, file);
    }
    if(headerTemp.dataTypeCode == 1){
        return parseUncompressedColorMap(&headerTemp, file);
    }
    else{
        printf("this file is in a currently unsupported format\n");
        fclose(file);
        return NULL;
    }
    
}