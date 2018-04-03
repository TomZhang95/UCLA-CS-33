/* 
 * CS:APP Data Lab 
 * 
 * <Tianyang Zhang : 404743024>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
    x = x | (x >> 1); //making every lower bit 1, if x is not 0, then the least significan bit of x will become 1
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >> 16);
    x = x ^ 1; //if x is 0, the least significan bit of x will become 1, otherwise the least significan bit will become 0
    x = x & 1; //ignoring all other bit, but only remain the least significan bit
  return x;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
    int sum;
    int mask;
    int fourBitSum;
    mask = 17 | (17 << 8);
    mask = mask | (mask << 16);
    fourBitSum = mask & x;
    fourBitSum = fourBitSum + (mask & (x >> 1));
    fourBitSum = fourBitSum + (mask & (x >> 2));
    fourBitSum = fourBitSum + (mask & (x >> 3));
    fourBitSum = fourBitSum + (fourBitSum >> 16);
    sum = fourBitSum & 15;
    sum = sum + ((fourBitSum >> 4) & 15);
    sum = sum + ((fourBitSum >> 8) & 15);
    sum = sum + ((fourBitSum >> 12) & 15);
    return sum;
    
}
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
    /*reverse all bit of x and y then AND them, the '1 bit' in the result are the bits that should be
     0, and the '0 bit' are the bits that should be 1, reverse the result and return*/
    return ~(~x & ~y);
}
/*
 * bitRepeat - repeat x's low-order n bits until word is full.
 *   Can assume that 1 <= n <= 32.
 *   Examples: bitRepeat(1, 1) = -1
 *             bitRepeat(7, 4) = 0x77777777
 *             bitRepeat(0x13f, 8) = 0x3f3f3f3f
 *             bitRepeat(0xfffe02, 9) = 0x10080402
 *             bitRepeat(-559038737, 31) = -559038737
 *             bitRepeat(-559038737, 32) = -559038737
 *   Legal ops: int and unsigned ! ~ & ^ | + - * / % << >>
 *             (This is more general than the usual integer coding rules.)
 *   Max ops: 40
 *   Rating: 4
 */
int bitRepeat(int x, int n) {
    int startingMask;
    int mask;
    int overFlowCheck;
    startingMask = (x & ((1 << n) - 1)) | ((~(!!(n & 32)) + 1) & x); /*
                                                                      if n == 32, then startingMask = x, otherwise for
                                                                      1 <= n < 32, startingMask would be the last n bits
                                                                      of x, which are the bits that will be reapeated
                                                                      */
    mask = startingMask | (startingMask << n);
    n = n * 2;
    overFlowCheck = ((n - 32) >> 31) & 1;
    mask = mask | ((mask << n) * overFlowCheck); /*
                                                  repeat n*2 4 times to make sure every bit in mask is filled, each time
                                                  check if n >= 32. if n >= 32, mask would remain the same value, otherwise
                                                  do the left shift and OR operation
                                                  */
    n = n * 2;
    overFlowCheck = ((n - 32) >> 31) & 1;
    mask = mask | ((mask << n) * overFlowCheck);
    n = n * 2;
    overFlowCheck = ((n - 32) >> 31) & 1;
    mask = mask | ((mask << n) * overFlowCheck);
    n = n * 2;
    overFlowCheck = ((n - 32) >> 31) & 1;
    mask = mask | ((mask << n) * overFlowCheck);
    
    return mask;
}
/*
 * fitsBits - return 1 if x can be represented as an
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
    int mask;
    n = n + ~0; // n = n - 1 in case n = 32
    mask = x >> 31;
    mask = x ^ mask;
    return !(mask >> n);
    /*no matter sign bit of x is 1 or 0, mask would always be 0000...0000 if x fits in n bits after mask >> n,
     if mask != 0, mask would be non-zero after mask >> n*/
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  return (x >> (n << 3)) & 255;
    /*since each byte is 8 bits, left shift n with 3(equal to n * 8). Then right shift x with it, and get
      the least significant 8 bits by & 255
     */
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    int isLessForSure;
    int isGreaterForSure;
    int isZero;
    int isLess;
    isLessForSure = (!((x >> 31) + 1)) & ((y >> 31) + 1);
    /*
     if x is negative and y is positive then x is less than y for
     sure, then isLessForSure = 1, otherwise isLessForSure = 0.
     This is use for the situation of overflow
     */
    
    isGreaterForSure = !(((x >> 31) + 1) & !((y >> 31) + 1));
    /*
     if x is positive and y is negative, then x is greater than
     y for sure, then isGreaterForSure = 0, otherwise = 1.
     This is also use for the situation of overflow.
     */
    
    isLess = x + 1 + ~y; //Equal to x-y
    isZero = !isLess; //isZero = 0 if x-y != 0, isZero = 1 if x-y = 0
    isLess = !((isLess >> 31) + 1); //After right shift and + 1, if x-y < 0, isLess = 1; if x-y >= 0, isLess = 0
    return (isLess | isZero | isLessForSure) & isGreaterForSure;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
    int sign = !!x; //if x is 0, sign = 0, otherwise sign = 1
    int PosOrNeg = !(x >> 31); //if x is positive, PosOrNeg = 1, if x is negative, PosOrNeg = 0
  return sign & PosOrNeg;
    /*return 1 only if sign is zero and x is possitive, which means x is positive. Otherwise x
     is 0 or negative, return 0. */
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
    int mask = ~(1 << 31 >> n << 1); // turn the right most n digit to zero and others 1
    // for example if n is 2, the mask would be 001111...11
    return (mask & (x >> n));    // turn the left most n digit to 0
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    return 1 << 31; // tMin = 10000000...0000, therefore left shift 00000...0001 31 bits
}
