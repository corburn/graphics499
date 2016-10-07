//
//  processing.c
//  Graphics
//
//  Created by jr2339 on 10/5/16.
//  Copyright © 2016 jr2339. All rights reserved.
//

#include "processing.h"
#define RATIO 2
/*Split memory in to parts, e.g. if memory = 10 and parts = 4, we will have 0, 2, 4, 6,10
 *if possible the function will split memory into equal chuncks
 *if not, the last chunck will be slightly larger
 */
/*
int* bounds(int mem){
    int bnd[RATIO];
    int delta = mem/RATIO;
    int reminder = mem % RATIO;
    int N1=0, N2=0;
    for (int i=0; i<RATIO; i++) {
        
        N2 = N1 + delta;
        if (i == RATIO-1) {
            N2 += reminder;
        }
        bnd[i] = N2;
        N1 = N2;
    }
    return bnd; // USE IT IN WRITE function
}

*/
void *Write(Image *buffer, const char *filename,int format,int count){
    FILE *f_des = fopen(filename, "w");
    if (!f_des){
        fprintf(stderr,"cannot open file for writing");
    }
    int des_height, des_width;

    if (format==6) {
        fprintf(f_des, "P%d\n%d %d\n%d\n",format,buffer->width, buffer->height, buffer->maxval);
        for (int i=0; i<(buffer->height/RATIO); i+=RATIO) {
            for (int j =0; j<(buffer->width/RATIO); j+=RATIO) {
                char r,g,b;
                r = buffer->pixel[i*buffer->width*3*count+3*j];
                fwrite(&r, 1, 1, f_des);
                g = buffer->pixel[i*buffer->width*3*count+3*j+1];
                fwrite(&g, 1, 1, f_des);
                b = buffer->pixel[i*buffer->width*3*count+3*j+2];
                fwrite(&b, 1, 1, f_des);
            }
        }
    }
    else if(format==3){
        fprintf(f_des, "P%d\n%d %d\n%d\n",format,des_width, des_height, buffer->maxval);
        int i,j;
        for(i=0;i<buffer->height;i+=RATIO){
            for(j=0;j<buffer->width;j+=RATIO){
                fprintf(f_des, "%d ",buffer->pixel[i*buffer->width*3*count+3*j]);
                fprintf(f_des, "%d ",buffer->pixel[i*buffer->width*3*count+3*j+1]);
                fprintf(f_des, "%d ",buffer->pixel[i*buffer->width*3*count+3*j+2]);
            }
            
            fprintf(f_des, "\n");
        }
    }
    fclose(f_des);
    return 0;
}


void processing(Image *buffer, const char *filename,int format){
    pthread_t thread[RATIO];
    for (int i=1; i<RATIO; i++) {
        pthread_create(&thread[i], NULL, Write(buffer, filename,format,i), &i);
    }
    //join the thread
    for (int i=0; i<RATIO; i++) {
        pthread_join(thread[i], NULL);
    }

    
}

