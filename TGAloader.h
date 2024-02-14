#include <stdlib.h>
#include <stdio.h>
#include "types.h"
unsigned char* load(char* path){
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
    headerTemp.colorMapOrigin = headerBytes[3] + (headerBytes[4] << 8);
    headerTemp.colorMapLength = headerBytes[5] + (headerBytes[6] << 8);
    headerTemp.colorMapDepth = headerBytes[7];
    headerTemp.xOrigin = headerBytes[8] + (headerBytes[9] << 8);
    headerTemp.yOrigin = headerBytes[10] + (headerBytes[11] << 8);
    headerTemp.width =  headerBytes[12] + (headerBytes[13] << 8);
    headerTemp.height = headerBytes[14] + (headerBytes[15] << 8); 
    headerTemp.bitDepth = headerBytes[16];
    headerTemp.imageDescriptor = headerBytes[17];
    if (headerTemp.bitDepth != 24 && headerTemp.bitDepth != 32) {
        printf("This currently only supports 24 and 32 bit color, which this file isn't, sorry\n");
        return NULL;
    }
    int dataSize = headerTemp.width * headerTemp.height * (headerTemp.bitDepth/8);
    unsigned char* result = malloc(dataSize);
    fread(result, sizeof(char), dataSize, file);
    return result;
}