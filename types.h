typedef struct{
    char  idLength;
    char  colorMapType;
    char  dataTypeCode;
    short int colorMapOrigin;
    short int colorMapLength;
    char  colorMapDepth;
    short int xOrigin;
    short int yOrigin;
    short width;
    short height;
    char  bitDepth;
    char  imageDescriptor;
}header;
typedef struct{
    unsigned char* values;
    short width;
    short height;
    short stride;
}rgbArray;