struct TFT {int fLeft,fPlus,fSpace,fPrefix,fZero,fPrec0,width,precision,cbits;char pad24[8];unsigned char conversion;char pad2d[3];int fUpper;};
extern "C" {
char *s1_strcpy(char *,const char *) asm("strcpy");
unsigned int s1_strlen(const char *) asm("strlen");
int ExpFirstFromG(double) asm("ExpFirstFromG__Fd");
unsigned char ChDigitFromG(double,int,int) asm("ChDigitFromG__Fdii");
double pow(double,double) asm("pow");
extern char D_002A94F0[],D_002A94F8[];
extern char D_002C40C8[];
}
int CchAchFromDouble(char *buffer,int capacity,TFT *f,double value){
    union {double d;unsigned long u;} bits;
    bits.d=value;
    if((bits.u&0x7FF0000000000000UL)==0x7FF0000000000000UL){
        s1_strcpy(buffer,(bits.u&0xFFFFFFFFFFFFFUL)?D_002A94F0:D_002A94F8);
        return s1_strlen(buffer);
    }
    int exponent=ExpFirstFromG(value);
    char *p=buffer;
    int scientific=f->conversion=='e';
    if(f->conversion=='g'){
        if(exponent<-4 || exponent>=f->precision){scientific=1;f->precision--;}
    }
    int roundExponent=scientific?exponent:0;
    double rounded=value+0.5*pow(10.0,(double)(roundExponent-f->precision));
    int roundedExponent=ExpFirstFromG(rounded);
    if(exponent<ExpFirstFromG(rounded))exponent=roundedExponent;
    int digit,count;
    if(scientific){count=1;digit=exponent;}
    else if(exponent>=0){count=exponent+1;digit=exponent;}
    else {count=1;digit=0;}
    while(count-- >0)*p++=ChDigitFromG(rounded,exponent,digit--);
    if(!f->fPrec0){
        *p++='.';
        count=f->precision;
        while(count-- >0)*p++=ChDigitFromG(rounded,exponent,digit--);
        if(f->conversion=='g'){
            while(p>buffer && ((unsigned char *)p)[-1]=='0')--p;
            if(p>buffer && ((unsigned char *)p)[-1]=='.')--p;
        }
    }
    if(scientific){
        *p++='e';
        if(exponent<0){*p++='-';exponent=-exponent;}
        else *p++='+';
        int divisor=(int)pow(10.0,2.0);
        for(int i=2;i>=0;--i){
            *p++=D_002C40C8[exponent/divisor];
            exponent=(exponent%divisor)*10;
        }
    }
    return p-buffer;
}
