// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
typedef enum { CLASS_SNAN, CLASS_QNAN, CLASS_ZERO, CLASS_NUMBER, CLASS_INFINITY } fp_class_type;
typedef struct { int class; unsigned int sign; int normal_exp; unsigned int fraction; } fp_number_type;
float __pack_f(fp_number_type *);
/* __make_fp (libgcc fp-bit): build a float from class, sign, exponent and fraction. */
float __make_fp(int class, unsigned int sign, int exp, unsigned int frac)
{
    fp_number_type in;
    in.class = class;
    in.sign = sign;
    in.normal_exp = exp;
    in.fraction = frac;
    return __pack_f(&in);
}
