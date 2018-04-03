//
//  loop.c
//  hw2
//
//  Created by Tom Zhang on 4/18/17.
//  Copyright © 2017 Tom Zhang. All rights reserved.
//

/*
 A. %rdi = x, %rsi = n, %rdx = mask, %rax = result
 B. result = 0, mask = 1
 C. mask != 0
 D. mask will be left shift by amount of least significant 8 bits of n
 E. result will equal to it self OR the result of mask AND x
 F.
 */

long loop(long x, int n) {
    long result = 0;
    long mask;
    for (mask = 1; mask != 0; mask = (mask << (n & 0xFF))) {
        result |= (mask & x);
    }
    return result;
}
