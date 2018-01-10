#ifndef _BMP_UTILS_H_
#define _BMP_UTILS_H_


const int BYTES_PER_PIXEL = 3; /// red, green, blue
const int FILE_HEADER_SIZE = 14;
const int INFO_HEADER_SIZE = 40;

void generateBitmapImage(const unsigned char *image, int height, int width, const char* imageFileName);
unsigned char* createBitmapFileHeader(int height, int width);
unsigned char* createBitmapInfoHeader(int height, int width);


#endif
