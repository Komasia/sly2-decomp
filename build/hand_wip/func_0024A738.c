// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
typedef union { double value; struct { unsigned int lsw; unsigned int msw; } parts; } ieee_double_shape_type;
double func_0024A738(double x, double y)
{
  unsigned int hx, hy;
  { ieee_double_shape_type gh; gh.value = x; hx = gh.parts.msw; }
  { ieee_double_shape_type gh; gh.value = y; hy = gh.parts.msw; }
  { ieee_double_shape_type sh; sh.value = x; sh.parts.msw = (hx & 0x7fffffff) | (hy & 0x80000000); x = sh.value; }
  return x;
}
