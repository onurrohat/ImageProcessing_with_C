#include<stdio.h>
#include<stdlib.h>

int main ()
{
    FILE *input =fopen("test_images/lena_color.bmp","rb");
    FILE *output = fopen("results/lena_grayscale.bmp","wb");

    unsigned char imgHeader[54];
    unsigned char colorTable[1024];
    
    if (input ==NULL)
    {

        printf("error when openning the image\n");

    }

    for(int i=0 ; i <54 ; i++){

        imgHeader[i]=getc(input);

    }

    fwrite(imgHeader,sizeof (unsigned char),54,output);
    
    int height = *(int*)&imgHeader[22];
    int width = *(int*)&imgHeader[18];
    int depth = *(int*)&imgHeader[28];

    if (depth <=8)
    {
        fread(colorTable,sizeof(unsigned char),1024,input);
        fwrite(colorTable,sizeof(unsigned char),1024,output);
    }
    int size =  height * width ;

    unsigned char **buf = (unsigned char **) malloc(size * sizeof(unsigned char *));

    for (int i = 0; i < size; ++i) {
    buf[i] = (unsigned char *)malloc(3 * sizeof(unsigned char)); // 3(r,g,b) *2 matris 
    }
    


    for(int i=0;i<size;i++)
    {
        buf[i][0]=getc(input); //r
        buf[i][1]=getc(input); //g
        buf[i][2]=getc(input); //b
        int temp = 0;

        temp= (buf[i][0]*0.3)+ (buf[i][0]*0.59)+(buf[i][2]*0.11); //rgb to grayscale formula

        putc(temp,output);
        putc(temp,output);
        putc(temp,output);

    }
    
    for (int i = 0; i < size; ++i) {
    free(buf[i]);
    }
    free(buf);  


    printf("Succes");
    fclose(input);
    fclose(output);

    return 0;

}