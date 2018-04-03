#include <stdio.h>
#include <limits.h>

/* Addition that saturates to TMin or TMax */
int saturating_add(int x, int y) {
    
  int sum;
  int w = (sizeof(int) << 3) - 1;
  int overflow_happen = __builtin_add_overflow(x, y, &sum);
  /* if overflow happen, overflow_happen == 1, otherwise 0. 
     The result of x+y is stored in variable 'sum'*/
    
  int overflow_mask = (overflow_happen << w) >> w;
  /*if overflow_happen == 0000..001 which means overflow happend, the result would be
     1111...1111, if overflow_happen == 0 which means no overflow, result would be
     0000...0000*/
    
  int x_neg_mask = (x >> w);
  //if x is negetive x_neg_mask would be 111111.... otherwise 00000....
    
  int y_neg_mask = (y >> w); //same as above
  int sum_neg_mask = (sum >> w);
  int pos_overflow = ~x_neg_mask & ~y_neg_mask & sum_neg_mask;
  //if positive overflow happen, pos_overflow = 11111.. otherwise 0000...
    
  int neg_overflow = x_neg_mask & y_neg_mask & ~sum_neg_mask; //same idea as pos_overflow
  int result = (INT_MAX & pos_overflow) | (INT_MIN & neg_overflow) | (sum & ~overflow_mask);
  return result;
}
