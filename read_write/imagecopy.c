#include <stdio.h>
#include<stdlib.h>




int main() 
{

	FILE *input = fopen("images/cameraman.bmp", "rb");
	
	FILE *copied= fopen("images/cameraman_copy.bmp","wb");

	if (input == (FILE*)0)
	{
		printf("Unable to open file \n");

	}

	unsigned char header[54]; // for storing the image data 
	unsigned char colors[1024]; // for pixels

	for (int i = 0; i < 54; i++)
	{
		header[i] = getc(input);
	}

	int width = *(int *) &header[18]; // 18 is offset value of width (bitmap default offset values)
	int height = *(int *) &header[22]; // 22 is offset value of height (bitmap default offset values)
	int bitdepth = *(int *) &header[28]; // depth means number of bits per pixel

	if (bitdepth <= 8)
	{
		fread(colors, sizeof(unsigned char), 1024, input);
	}

	fwrite(header, sizeof(unsigned char), 54, copied);
	
	unsigned char *buf = malloc(height * width);
	

	fread(buf, sizeof(unsigned char),(height * width),input);

	if (bitdepth <= 8)
	{
		fwrite(colors, sizeof(unsigned char), 1024,copied);
	}

	fwrite(buf, sizeof(unsigned char), (height * width), copied);

	fclose(copied);
	fclose(input);



	free(buf);




	return 0;

}