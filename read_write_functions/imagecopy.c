#include <stdio.h>
#include<stdlib.h>


#define	BMP_HEADER_SIZE 54
#define BMP_COLORS_SIZE 1024
#define CUSTOM_IMG_SIZE 1024*1024

void imageReader(const char *imgName, int *_height,int *_width,int *_bitDepth,unsigned char *_header,unsigned char *_colors,unsigned char *_buf);

void imageWriter (const char *newimgName,unsigned char *header,unsigned char *colors,unsigned char *buf,int bitDepth);


int main() 
{
		

	int width ,height,depth ;
	unsigned char imgHeader[BMP_HEADER_SIZE];
	unsigned char imgColors[BMP_COLORS_SIZE];
	unsigned char imgBuffer [CUSTOM_IMG_SIZE];

	const char img[] = "images/man.bmp";
	const char newimg[] ="images/copied.bmp";

	imageReader(img,&width,&height,&depth,&imgHeader[0],&imgColors[0],&imgBuffer[0]);
	imageWriter(newimg,imgHeader,imgColors,imgBuffer,depth);

	printf("Success");


	return 0;

}

void imageReader(const char *imgName, int *_height,int *_width,int *_bitDepth,unsigned char *_header,unsigned char *_colors,unsigned char *_buf)


{

	int i ;
	FILE *input;
	input =fopen(imgName,"rb");

	if (input ==(FILE*)0)
	{
		printf("Image cannot read ");

	}

	for ( i=0 ; i <54;i++){

		_header[i]=getc(input);
	}

	*_width = *(int *)&_header[18];
	*_height = *(int *)&_header[22];
	*_bitDepth == *(int *)&_header[28];


	if(*_bitDepth <=8){

		fread(_colors,sizeof(unsigned char),1024,input);
	}

	fread(_buf,sizeof(unsigned char),CUSTOM_IMG_SIZE,input);
	fclose(input);


}


void imageWriter (const char *newimgName,unsigned char *header,unsigned char *colors,unsigned char *buf,int bitDepth)


{
	FILE *fout= fopen(newimgName,"wb");
	fwrite(header,sizeof(unsigned char),54,fout);

	if(bitDepth <=8){

		fwrite(colors,sizeof(unsigned char),1024,fout);
	}

	fwrite(buf,sizeof(unsigned char),CUSTOM_IMG_SIZE,fout);
	fclose(fout);

}