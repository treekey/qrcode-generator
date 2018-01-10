#include <string>
#include <iostream>
#include <cstring>
#include "qrencode.h"
#include "bmp_utils.h"

const int OUT_FILE_PIXEL_PRESCALER = 8;

using namespace std;
int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "usage: qrcode-generator string_to_encode output_file_path" << endl;
	return -1;
    }

    string string_to_encode = argv[1];
    string output_file_path = argv[2];
    QRcode* qrcode = QRcode_encodeString(string_to_encode.c_str(), 0, QR_ECLEVEL_H, QR_MODE_8, 1);
    if (qrcode)
    {
	unsigned int adjusted_width = qrcode->width * OUT_FILE_PIXEL_PRESCALER * 3;
	unsigned int data_bytes = adjusted_width * qrcode->width * OUT_FILE_PIXEL_PRESCALER;
	
	unsigned char* pRGB = new unsigned char[data_bytes];
	memset(pRGB, 0xff, data_bytes);

	unsigned char* source_data = qrcode->data;
	for (int i = 0; i < qrcode->width; ++i)
	{
	    unsigned char* dest_data = pRGB + adjusted_width * i * OUT_FILE_PIXEL_PRESCALER;
	    for (int j = 0; j < qrcode->width; ++j)
	    {
		if ((*source_data) & 1)
		{
		    for (int k = 0; k < OUT_FILE_PIXEL_PRESCALER; ++k)
		    {                  
			int offset = adjusted_width * k;
			for (int l = 0; l < OUT_FILE_PIXEL_PRESCALER; ++l)
			{
			    *(dest_data + l * 3     + offset) = 0; // B
			    *(dest_data + l * 3 + 1 + offset) = 0; // G
			    *(dest_data + l * 3 + 2 + offset) = 0; // R
			}
		    }
		}
		dest_data += 3 * OUT_FILE_PIXEL_PRESCALER;
		source_data++;
	    }
	}

	int length = qrcode->width * OUT_FILE_PIXEL_PRESCALER;
	generateBitmapImage(pRGB, length, length, output_file_path.c_str());

	if (pRGB)
	{
	    delete [] pRGB;
	}
	QRcode_free(qrcode);
    }

    return 0;
}
