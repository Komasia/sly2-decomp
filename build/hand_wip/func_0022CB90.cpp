typedef int qword __attribute__((mode(TI)));
extern "C" void *func_0023320C(void *,const void *,int);
struct M4 { qword r[4]; M4() {} M4(const M4 &s) { func_0023320C(this,&s,0x40); } };
extern "C" qword func_0022CAD0(qword,qword);
extern "C" M4 func_0022CCD0(void *,void *,qword);
extern "C" M4 func_0022CB90(void *a,void *b,qword c,qword d) {
    M4 m=func_0022CCD0(a,b,func_0022CAD0(c,d));
    return m;
}
