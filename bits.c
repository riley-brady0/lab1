/* 
 * <Riley Brady rpb4838 N13725426>
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
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  //Xor returns high if and only if the inputs are different 
  int a = (x & y); //x&y gives high only when inputs are both positive
  int b = (~x & ~y); //~x&~y gives high only when the inputs are both negative
  int z = (~a & ~b); //the cross product of the inverse of these operations 
  //provides a positive output if and only if the inputs are different
  return z;
}

/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  int a = ~ (~0u >> 1); 
  //~turns on all bits in the unsigned zero
  //>>1 shifts right making the highest bit a zero
  //then ~ again turns the number into a 1 followed by all 0s 
  return a;
}

//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 2
 */
int isTmax(int x) {
  int neg1;
  neg1 = !(~x); // if x == -1, neg1 == 1, else, neg1 == 0
  return !((~(x+1)^x)|neg1); // add 1, flip, and xor, becomes 0 if Tmax (or if -1)
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  int A = 0xAA + (0xAA<<8) + (0xAA<<16) + (0xAA<<24);
  return !((x&A) ^ A);
  /* all odd-numbered bits are set to 1 only in 0xAAAAAAAA, which
     corresponds to 10101010101010101010101010101010 in binary.
     we check this by constructing this number by left shifting
     and adding 8 bits at a time 
     Then we do x&A, which checks if x and A have the same bits.
     if they have the same bits, it results in A. then we do
     result ^ A, which returns 0 if all the bits are equal
     and 1 otherwise. then we do !(result) so that it returns
     1 if the bits are equal
   */
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  int y = ~x+1;
  return y;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
   int sign = 1 << 31;
   int upper = ~(sign | 0x39); /*if > 0x39 is added, result goes negative*/
   int lower = ~0x30;/*when < 0x30 is added, result is negative*/

   /*now add x and check sign bit*/
   upper = sign & (upper+x) >> 31;
   lower = sign & (lower+1+x) >> 31; 
   /*if either result is negative, it is not in desired range*/
   return !(upper | lower); 
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  x = !!x; /*puts x in 0 or 1 form*/
  x = ~x+1; /*x is now either all 1's or all 0's*/
  return (x & y) | (~x & z); 
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int diff_sign = !(x>>31)^!(y>>31);      //is 1 when signs are different
  int a = diff_sign & (x>>31);            //diff signs and x is neg, gives 1
  int b = !diff_sign & !((y+(~x+1))>>31); //same signs and difference is pos or = 0, gives 1
  int f = a | b;
  return f;
}

//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  // zero is the only number that complemented
  // and inversed-and-complemented is the
  // same: (-1) ~ check for signbit sameness
  return (((~x) & (~(~x+1))) >> 31) & 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {

  int sign, bit0, bit1, bit2, bit4, bit8, bit16;

  sign = x >> 31;
    
  /* Bit invert x as needed */
  x = (sign & ~x) | (~sign & x);
    
  /* Binary Search on bit level */
  bit16 = !!(x >> 16) << 4;
  x = x >> bit16;
    
  bit8 = !!(x >> 8) << 3;
  x = x >> bit8;
    
  bit4 = !!(x >> 4) << 2;
  x = x >> bit4;
    
  bit2 = !!(x >> 2) << 1;
  x = x >> bit2;
    
  bit1 = !!(x >> 1);
  x = x >> bit1;
    
  bit0 = x;

  return bit16 + bit8 + bit4 + bit2 + bit1 + bit0 + 1;
}

//float
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  // Case-by-case.
  int e = (uf >> 23) & 0xFF;
  // Denormalized Case
  if(!e)
  {
    e = 0xFF;
    // Significand overflow is okay; Automatically managed as Normalized Case.
    uf = (uf & 0x80000000) | (uf << 1);
  }
  // Overflow Case
  if(!(e ^ 0xFE))
  {
    e = 0xFF;
    // Set Infinite, not NaN
    uf = (uf & 0x80000000) | (e << 23);
  }
  // Nothing to process if Exp = 0xFF
  if(e ^ 0xFF)
  {
    uf = uf + (1 << 23);
  }
  return uf;
}


/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  int b = 0, s = 0, c = 0;
  unsigned int r = 0x00000000;
  unsigned int t = x, f = x;
  // Use absolute value if negative.
  if(x >> 31)
  {
    r = 0x80000000;
    t = f = (~x) + 1;
  }
  // Count digits.
  while(t)
  {
    b = b + 1;
    t = t >> 1;
  }
  s = 24 - b;
  // Check digit loss (in terms of precision).
  if(s < 0)
  {
    s = 0;
    while(f >> 25)
    {
      c = c | (f & 1);
      f = f >> 1;
    }
    f = (f >> 1) + (f & (c | (f >> 1)) & 1);
    if(f >> 24)
    {
      b = b + 1;
    }
  }
  // Make Exp 0 if x is 0.
  if(!b)
  {
    b = -126;
  }
  r = r | ((f << s) & 0x007FFFFF);
  r = r | ((b + 126) << 23);
  return r;
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
  int flag = uf & (1 << 31);
  uf = uf & ~(1 << 31);
  int exp = (uf >> 23);
  int num = exp + ~126;
  if( !exp || (num & (1 << 31)))
    return 0;
  else if(!(exp ^ 0xFF))
  {
    return (1 << 31);
  }
  else
  {
    num = 1 << num;
  if(flag)
    return ~num + 1;
  else
    return num;
  }
}
