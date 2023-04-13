#include <stdio.h>
#include <stdlib.h>

#define WHITE 255
#define BLACK 0 
#define THRESHOLD 140 // this value is not specifically set

int main (){

    FILE *input = fopen("test_images/zelda.bmp","rb");
    FILE *output = fopen("results/output.bmp","wb");

    unsigned char imgHeader[54];
    unsigned char colors[1024];

    if (input ==NULL)
    {
        printf("Image cannot opened");
    }

    for(int i=0;i<54;i++)
    {
        imgHeader[i]=getc(input);
    }

    fwrite(imgHeader,sizeof(unsigned char),54,output);

    int height = *(int*)&imgHeader[22];
    int width = *(int*)&imgHeader[18];
    int bitDepth = *(int*)&imgHeader[28];


    if(bitDepth <= 8)
    {
        fread(colors,sizeof(unsigned char),1024,input);
        fwrite(colors,sizeof(unsigned char),1024,output);

    }

    unsigned char *buf = malloc(height * width);
	

	fread(buf, sizeof(unsigned char),(height * width),input);

    for(int i=0 ; i<height*width ; i++ )
    {
        buf[i] = (buf[i]> THRESHOLD )? WHITE :BLACK ;
    }

    
    fwrite(buf,sizeof(unsigned char),height*width,output);
    free(buf);
    fclose(input);
    fclose(output);


}