//
//  Image.h
//  Graphics
//
//  Created by jr2339 on 10/3/16.
//  Copyright © 2016 jr2339. All rights reserved.
//

#ifndef Image_h
#define Image_h

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>




typedef struct Image{
    int width;
    int height;
    int magic_number;
    u_char *pixel;
    int maxval;
}Image;
int readMagicNumber(FILE *fp);
Image *readHeader(FILE *f_source, Image *buffer);
Image *ImageRead(const char *filename);
void ImageWrite(Image *buffer, const char *filename,int format);


#endif /* Image_h */
