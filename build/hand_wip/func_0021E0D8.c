// Complete WIP: skipped digits return table entry0, not NUL.
extern unsigned char D_002C40C8[];
double func_002452C0(double, double);
double func_0011D740(double);
double func_0023D808(double,double);
double func_0023D7A0(double,double);
double func_0023DD80(int);
int func_0023DE38(double);
typedef unsigned long F64BITS;
union IEEE64 {double value;F64BITS bits;};
static inline F64BITS Bits(double f){union IEEE64 u;u.value=f;return u.bits;}
static inline double Real(F64BITS b){union IEEE64 u;u.bits=b;return u.value;}
unsigned char func_0021E0D8(double g,int a,int b){
    int i;
    F64BITS value=Bits(g);
    if(a<b)goto calculate;
    if((int)((unsigned int)a-15U)<b)goto calculate;
    i=0;goto lookup;
calculate:{
        value=Bits(func_0011D740(func_0023D808(Real(value),func_002452C0(10.0,func_0023DD80(-b)))));
        i=func_0023DE38(func_0023D7A0(Real(value),func_0023D808(func_0011D740(func_0023D808(Real(value),0.1)),10.0)));
    }
lookup:
    return D_002C40C8[i];
}
