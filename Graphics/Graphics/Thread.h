//
//  Thread.h
//  Graphics
//
//  Created by jr2339 on 10/6/16.
//  Copyright © 2016 jr2339. All rights reserved.
//

#ifndef Thread_h
#define Thread_h

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>



typedef struct Image{
    int width;
    int height;
    int magic_number;
    u_char *pixel;
    int maxval;
}Image;
int readMagicNumber(FILE *fp);
Image *readHeader(FILE *f_source, Image *buffer);
//Image *ImageRead(const char *filename);
//void DownSampling(Image *buffer, const char *filename,int format);
void ImageWrite(Image *buffer, const char *filename,int format);
void *thread_Read(Image *buffer,FILE *fp,int counter);
Image* threadSampling(const char *filename);
#endif /* Thread_h */
