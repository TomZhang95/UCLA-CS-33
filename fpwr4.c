//
//  main.c
//  fpwr4
//
//  Created by Tom Zhang on 5/10/17.
//  Copyright © 2017 Tom Zhang. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static float u2f(unsigned u) {
    int exp = u >> 23;
    int frac = u & 0x007FFFFF;
    if(exp != 0){
        frac = frac | 0x00800000;
    }
    float result = frac;
    
    if (exp == 0 && frac == 0)
        return 0;
    
    if (exp == 255 && frac == 0)
        result = __FLT_HAS_INFINITY__;
    else if (exp == 0){
        for (int i = 0; i < 149; i++)
            result /= 2;
    }
    else if (exp <= 149){
        for (int i = 0; i < 150 - exp; i++)
            result /= 2;
    }
    else {
        for (int i = 0; i < exp - 150; i++)
            result *= 2;
    }
    return result;
}


float fpwr4(int x) {
    /* Result exponent and fraction */
    unsigned exp, frac;
    unsigned u;
    
    if (x < -74) {
        /* Too small. Return 0.0 */
        exp = 0;
        frac = 0;
    } else if (x < -63) {
        /* Denormalized result */
        exp = 0;
        frac = 1 << (2*(74 + x));
    } else if (x < 64) {
        /* Normalized result. */
        exp = 2*x + 127;
        frac = 0;
    } else {
        /* Too big. Return +oo */
        exp = 255;
        frac = 0;
    }
    
    /*Pack exp and frac into 32 bits */
    u = exp << 23 | frac;
    /* Return as float */
    return u2f(u);
}
