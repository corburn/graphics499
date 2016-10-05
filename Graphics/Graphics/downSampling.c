//
//  downSampling.c
//  Graphics
//
//  Created by jr2339 on 10/2/16.
//  Copyright © 2016 jr2339. All rights reserved.
//
/*
 *The final purpose for me to find stochastic sampling algorithm
 *In this function, I will try to let the width and height to be half
 *of the original width and original height.
 *For example, if the original width is W and origianl height is H
 *Now, by we using downSampling the width is W/2, and the height is
 *H/2. No matter the width and height at here is odd or vevn
*/
/*******************************************************************/
/*******************************************************************/
/*
 *If I can use 1D Arrry, I don't use 2D Array
 *Because the continue data is stored by linear
 *If I can use pointer, I don't use Array
 *Compare by using Array, using pointer is more efficiency
 */
#include "downSampling.h"
/*If you want, you also can pass the scale Ratio at here
 *at here I justed use 2 to let it simple
 */

#define RATIO 2
char* downSampling(char *source, int width, int height){
    int des_width = width/RATIO;
    int des_height = height/RATIO;
    char *destanation = (char*)malloc(sizeof(char)*des_width*des_height);
   

    
    char *Ps_Cur = source;
    //char *Ps_End = source + width*height;
    char *Pd_Cur = destanation;
    char *Pd_End = destanation + des_width*des_height;

    while (Pd_Cur < Pd_End) {
        *Pd_Cur = *Ps_Cur;
        Ps_Cur++;
        Pd_Cur += RATIO;
        }

    return destanation;
}
