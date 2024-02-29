#include "types.h"

rgbArray* parseRGB(header* headerTemp, FILE* file){
    int dataSize = (headerTemp->width) * (headerTemp->height) * (headerTemp->bitDepth/8);
    unsigned char* result = malloc(dataSize);
    fread(result, sizeof(char), dataSize, file);
    rgbArray* arr = malloc(sizeof(rgbArray));
    arr->values = result;
    arr->height = headerTemp->height;
    arr->width = headerTemp->width;
    arr->stride = headerTemp->bitDepth/8;
    return arr;
}

rgbArray* parseUncompressedColorMap(header* headerTemp, FILE* file){
    short indexWidth;
    if(headerTemp->colorMapLength <= 256) indexWidth = 8;
    else indexWidth = 16;
    rgbArray* arr = malloc(sizeof(rgbArray));
    arr->height = headerTemp->height;
    arr->width = headerTemp->width;
    arr->stride = headerTemp->bitDepth/8;


    unsigned char* palette = malloc(sizeof(unsigned char) * headerTemp->colorMapLength * arr->stride);
    fread(palette, sizeof(unsigned char), headerTemp->colorMapLength * arr->stride, file);
    int dataSize = (headerTemp->width) * (headerTemp->height) * (indexWidth/8);
    arr->values = malloc(sizeof(char)* 3 * dataSize);
    if(indexWidth == 8){
        unsigned char* indices = malloc(sizeof(unsigned char) * dataSize);
        fread(indices, sizeof(unsigned char), dataSize, file);
        for(int i = 0; i < dataSize; i++){
            //this doesn't account for 3 bytes i think
            arr->values[i] = palette[indices[i]*3];
            arr->values[i + 1] = palette[(indices[i]*3) + 1];
            arr->values[i + 2] = palette[(indices[i]*3) + 2];
        }
        fclose(file);
        return arr;
    }
    if(indexWidth == 16){
        short* indices = malloc(sizeof(short) * dataSize);
        fread(indices, sizeof(short), dataSize, file);
        for(int i = 0; i < dataSize; i++){
            arr->values[i] = palette[(indices[i]*3)];
            arr->values[i + 1] = palette[(indices[i]*3) + 1];
            arr->values[i + 2] = palette[(indices[i]*3) + 2];
        }
        fclose(file);
        return arr;
    }
    fclose(file);
    printf("you tried to parse a file of unsupported size, which is my fault, if this happens lmk and I'll update this program");
    return NULL;
}