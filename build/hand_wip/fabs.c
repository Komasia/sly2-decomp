// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
typedef union { double value; struct { unsigned int lsw; unsigned int msw; } parts; } ieee_double_shape_type;
double fabs(double x)
{
  unsigned int high;
  ieee_double_shape_type gh; gh.value = x; high = gh.parts.msw;
  { ieee_double_shape_type sh; sh.value = x; sh.parts.msw = high & 0x7fffffff; x = sh.value; }
  return x;
}
