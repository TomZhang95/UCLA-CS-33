#include <limits.h>

/* Addition that saturates to TMin or TMax */
int saturating_add(int x, int y) {

  int sum = x + y;
  int w = (sizeof(int) << 3) - 1;
  int x_neg_mask = (x >> w); //if x is negetive x_neg_mask would be 111111.... otherwise 00000....
  int y_neg_mask = (y >> w); //same as above
  int sum_neg_mask = (sum >> w);
  int pos_overflow = ~x_neg_mask & ~y_neg_mask & sum_neg_mask; //if positive overflow happen, pos_overflow = 11111.. otherwise 0000...
  int neg_overflow = x_neg_mask & y_neg_mask & ~sum_neg_mask; //same idea as pos_overflow
  int overflow_happen = pos_overflow | neg_overflow;
  int result = (INT_MAX & pos_overflow) | (INT_MIN & neg_overflow) | (sum & ~overflow_happen);
  return result;
}
