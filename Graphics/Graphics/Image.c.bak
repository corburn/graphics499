//
//  Image.c
//  Graphics
//
//  Created by jr2339 on 10/3/16.
//  Copyright © 2016 jr2339. All rights reserved.
//

#include "Image.h"
#define RATIO 4

pthread_mutex_t lock;
int readMagicNumber(FILE *fp) {
    int magic_number;
    if (!fscanf(fp, "P%d\n", &magic_number)){
        fprintf(stderr,"file is not in PPM format, we can't read it");
        exit(1);
    }
    return magic_number;
}
/**************************************************************************************************************
 **************************************************************************************************************/

// readPPMHeader help us to detemine which format is our source image
Image *readHeader(FILE *f_source, Image *buffer){
    char ch;
    /*skip the comments*/
    ch = getc(f_source); // ch is int
    /*
     gets the next character (an unsigned char) from the specified
     stream and advances the position indicator for the stream.
     */
    while(ch =='#'){
        do{
            ch=getc(f_source);
        }
        while(ch!='\n'); //read to the end of the line
        ch=getc(f_source);
    }
    if(!isdigit(ch)){
        fprintf(stderr,"can't read header information from PPM format\n");
    }
    else{
        ungetc(ch, f_source); //put that digital back
    }
    //read the width, height,amd maximum value for a pixel
    fscanf(f_source, "%d %d %d\n",&buffer->width,&buffer->height,&buffer->maxval);
    buffer->pixel = (u_char *)malloc(buffer->width*buffer->height*3);// G, R, B three colors
    if(buffer->maxval >= 65336 ||buffer->maxval <= 0){
        fprintf(stderr,"image is not ture-color(8byte), read failed\n");
        exit(1);
    }
    return buffer;
    
}

/**************************************************************************************************************
 **************************************************************************************************************/

Image *ImageRead(const char *filename){
    FILE *fp = fopen(filename,"r");
    if(!fp){
        fprintf(stderr,"can't open file for reading \n");
        exit(1);
    }
    Image *buffer = (Image *)malloc(sizeof(Image));
    if(!buffer){
        fprintf(stderr,"Can't allocate memory for new image");
        exit(1);
    }
    buffer->magic_number = readMagicNumber(fp);
    buffer->pixel = (u_char *)malloc(buffer->width*buffer->height*3);// G, R, B three colors and A
    if(buffer->magic_number==3){
        readHeader(fp,buffer);
        buffer->pixel = (u_char *)malloc(buffer->width*buffer->height*3);
        int i,j, pixel[4];
        //In P3 file, we use nested loop, to copy image content to buffer
        for(i=0;i<buffer->height;i++){
            for(j=0;j<buffer->width;j++){
                fscanf(fp, "%d\n",pixel);
                buffer->pixel[i*buffer->width*3+3*j] = *pixel;//R
                fscanf(fp, "%d\n",pixel);
                buffer->pixel[i*buffer->width*3+3*j+1] = *pixel;//G
                fscanf(fp, "%d\n",pixel);
                buffer->pixel[i*buffer->width*3+3*j+2] = *pixel;//B
            }
        }
    }
    else if(buffer->magic_number==6){
        readHeader(fp,buffer);
        buffer->pixel = (u_char *)malloc(buffer->width*buffer->height*3);
        //int size1 = buffer->width * buffer->height*4;
        int size = buffer->height*buffer->width*3;//give the times for our for loop
        char c='A';//init
        int k=0;
        // for each llop we copy R, G, B to the buffer and let A =255
        for(int m=0;m<size;m+=3){
            fread(&c, 1, 1, fp);
            buffer->pixel[k] = c;
            k += 1;
            fread(&c, 1, 1, fp);
            buffer->pixel[k] = c;
            k += 1;
            fread(&c, 1, 1, fp);
            buffer->pixel[k] = c;
            k += 1;
            //buffer->data[k] = 255;
            //k += 1;
        }
        
        if (k!= size) {
            printf("n is %d, size is %d \n",k,size);
            fprintf(stderr,"cannot read image datat from file \n");
            exit(1);
        }
        
    }

    
    return buffer;
}

void ImageWrite(Image *buffer, const char *filename,int format){
    int size = buffer->width * buffer->height * 3;
    FILE *f_des = fopen(filename, "w");
    if (!f_des){
        fprintf(stderr,"cannot open file for writing");
    }
    if(format==6){
        fprintf(f_des, "P%d\n%d %d\n%d\n",format,buffer->width, buffer->height, buffer->maxval);
        for(int i=0; i<size;i++){    // for each for slots we skip it,
            char ch=buffer->pixel[i];
            fwrite(&ch, 1, 1, f_des);  // which means we skip A at here

        }
    }
    else if(format==3){
        fprintf(f_des, "P%d\n%d %d\n%d\n",format,buffer->width, buffer->height, buffer->maxval);
        int i,j;
        for(i=0;i<buffer->height;i++){
            for(j=0;j<buffer->width;j++){
                fprintf(f_des, "%d ",buffer->pixel[i*buffer->width*3+3*j]);
                fprintf(f_des, "%d ",buffer->pixel[i*buffer->width*3+3*j+1]);
                fprintf(f_des, "%d ",buffer->pixel[i*buffer->width*3+3*j+2]);
            }
            
            fprintf(f_des, "\n");
        }
    }
    fclose(f_des);

   
}
/***********************************************This is DowmSampling**********************************/

void DownSampling(Image *buffer, const char *filename,int format){
    FILE *f_des = fopen(filename, "w");
    if (!f_des){
        fprintf(stderr,"cannot open file for writing");
    }
    int des_height, des_width;
    des_height = buffer->height/RATIO;
    des_width = buffer->width/RATIO;
    if (format==6) {
        fprintf(f_des, "P%d\n%d %d\n%d\n",format,des_width, des_height, buffer->maxval);
        for (int i=0; i<buffer->height; i+=RATIO) {
            for (int j =0; j<buffer->width; j+=RATIO) {
                char r,g,b;
                r = buffer->pixel[i*buffer->width*3+3*j];
                fwrite(&r, 1, 1, f_des);
                g = buffer->pixel[i*buffer->width*3+3*j+1];
                fwrite(&g, 1, 1, f_des);
                b = buffer->pixel[i*buffer->width*3+3*j+2];
                fwrite(&b, 1, 1, f_des);
            }
        }
    }
    else if(format==3){
        fprintf(f_des, "P%d\n%d %d\n%d\n",format,des_width, des_height, buffer->maxval);
        int i,j;
        for(i=0;i<buffer->height;i+=RATIO){
            for(j=0;j<buffer->width;j+=RATIO){
                fprintf(f_des, "%d ",buffer->pixel[i*buffer->width*3+3*j]);
                fprintf(f_des, "%d ",buffer->pixel[i*buffer->width*3+3*j+1]);
                fprintf(f_des, "%d ",buffer->pixel[i*buffer->width*3+3*j+2]);
            }
            
            fprintf(f_des, "\n");
        }
    }
    fclose(f_des);
}


/*******************************I try to use thread ******************************************/
void *thread_Read(Image *buffer,FILE *fp,int counter){
    if(buffer->magic_number==3){
        readHeader(fp,buffer);
        buffer->pixel = (u_char *)malloc(buffer->width*buffer->height*3);
        int i,j, pixel[4];
        //In P3 file, we use nested loop, to copy image content to buffer
        for(i=0;i<buffer->height;i++){
            for(j=0+(counter-1)*buffer->width/RATIO;j<(buffer->width/RATIO)*counter;j++){
                fscanf(fp, "%d\n",pixel);
                buffer->pixel[i*(buffer->width/RATIO)*3*counter+3*j] = *pixel;//R
                fscanf(fp, "%d\n",pixel);
                buffer->pixel[i*(buffer->width/RATIO)*3*counter+3*j+1] = *pixel;//G
                fscanf(fp, "%d\n",pixel);
                buffer->pixel[i*(buffer->width/RATIO)*3*counter+3*j+2] = *pixel;//B
            }
        }
    }
    else if(buffer->magic_number==6){
        readHeader(fp,buffer);
        buffer->pixel = (u_char *)malloc(buffer->width*buffer->height*3);
        int size = buffer->height*buffer->width*3;//give the times for our for loop
        char c='A';//init
        int k=0;
        // for each llop we copy R, G, B to the buffer and let A =255
        /*
        for(int m=0;m<size;m+=3){
            fread(&c, 1, 1, fp);
            buffer->pixel[k] = c;
            k += 1;
            fread(&c, 1, 1, fp);
            buffer->pixel[k] = c;
            k += 1;
            fread(&c, 1, 1, fp);
            buffer->pixel[k] = c;
            k += 1;
            //buffer->data[k] = 255;
            //k += 1;
        }
        */
        int i,j;
        for(i=0;i<buffer->height;i++){
            for(j=0+(counter-1)*buffer->width/RATIO;j<(buffer->width/RATIO)*counter;j++){
                fread(&c, 1, 1, fp);
                k++;
            }
        }

        if (k!= size) {
            printf("n is %d, size is %d \n",k,size);
            fprintf(stderr,"cannot read image datat from file \n");
            exit(1);
        }
        
    }
    
    
    return 0;
}


/******************************************************************************************************************/

Image* threadSampling(const char *filename){
    FILE *fp = fopen(filename,"r");
    Image *buffer = (Image *)malloc(sizeof(Image));
    if(!buffer){
        fprintf(stderr,"Can't allocate memory for new image");
        exit(1);
    }
    buffer->magic_number = readMagicNumber(fp);
    buffer->pixel = (u_char *)malloc(buffer->width*buffer->height*3);// G, R, B three colors
    if(!fp){
        fprintf(stderr,"can't open file for reading \n");
        exit(1);
    }
    pthread_t thread[RATIO];

    for (int i=0; i<RATIO; i++) {
        pthread_create(&thread[i], NULL,thread_Read(buffer,fp,i+1) , &i);
    }
    //join the thread
    for (int i=0; i<RATIO; i++) {
        pthread_join(thread[i], NULL);
    }
    
    return buffer;
}


















