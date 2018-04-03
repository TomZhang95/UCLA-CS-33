/* Return 1 when any odd bit of x equals 1; 0 otherwise.
   Assume .w=32 */
int any_odd_one(unsigned int x) {
  return !!(x & 2863311530); //2863311530 is 101010....101010(32bits total) in binary (assume the first bit count as even bit)
}
