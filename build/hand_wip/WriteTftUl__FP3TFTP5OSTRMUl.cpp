struct TFT {int fLeft,fPlus,fSpace,fPrefix,fZero,fPrec0,width,precision,cbits;char pad24[8];unsigned char conversion;char pad2d[3];int fUpper;};
union UL {unsigned short us;short s;unsigned int u;int i;unsigned long ul;long l;};
class OSTRM {public:int CbWrite(void *,int);};
int FNegTftUl(TFT *,UL *);
int CchAchFromUl(char *,int,unsigned long,unsigned int);
int UnRadixFromChConversion(unsigned char) __asm__("UnRadixFromChConversion__Fc");
extern "C" unsigned int func_0021ED28(const char *);
extern "C" void func_0021EE30(char *);
static inline void WritePad(OSTRM *out,char ch,int count){char b=ch;while(count-- >0)if(out->CbWrite(&b,1)!=1)break;}
void WriteTftUl(TFT *f,OSTRM *out,unsigned long n){
    char digits[0x50];
    char prefix[0x10];
    int cPrefix,cDigits,cZero;
    char *pPrefix=prefix;
    if(!f->fPrec0 && f->precision)f->fZero=0;
    if(f->fPrec0 && n==0){cPrefix=cZero=cDigits=0;goto padding;}
    {
        int negative=FNegTftUl(f,(UL *)&n);
        cZero=f->precision;
        prefix[0]=0;
        switch(f->conversion){
        case 'd':case 'i':
            if(negative)pPrefix=(char *)__builtin_memcpy(prefix,"-",2);
            else if(f->fPlus)pPrefix=(char *)__builtin_memcpy(prefix,"+",2);
            else if(f->fSpace)pPrefix=(char *)__builtin_memcpy(prefix," ",2);
            cZero-=func_0021ED28(prefix);
            break;
        case 'b':if(f->fPrefix)pPrefix=(char *)__builtin_memcpy(prefix,"0b",3);break;
        case 'o':if(f->fPrefix)pPrefix=(char *)__builtin_memcpy(prefix,"0",2);break;
        case 'x':if(f->fPrefix)pPrefix=(char *)__builtin_memcpy(prefix,"0x",3);break;
        }
        cPrefix=func_0021ED28(pPrefix);
        cDigits=CchAchFromUl(digits,0x40,n,UnRadixFromChConversion(f->conversion));
        cZero-=cDigits;
        if(cZero<0)cZero=0;
        digits[cDigits]=0;
        if(f->fUpper){func_0021EE30(pPrefix);func_0021EE30(digits);}
    }
    padding:
    int total=cPrefix+cZero+cDigits;
    int left=0,right=0;
    if(total<f->width){
        int padding=f->width-total;
        if(f->fLeft)right=padding;
        else if(f->fZero && cDigits)cZero+=padding;
        else left=padding;
    }
    WritePad(out,' ',left);
    out->CbWrite(pPrefix,cPrefix);
    WritePad(out,'0',cZero);
    out->CbWrite(digits,cDigits);
    WritePad(out,' ',right);
}
