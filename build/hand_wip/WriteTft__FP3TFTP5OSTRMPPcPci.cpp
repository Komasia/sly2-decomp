struct TFT {int fLeft,fPlus,fSpace,fPrefix,fZero,fPrec0,width,precision,cbits,columns,rows;unsigned char conversion;char pad2d[3];int fUpper;};
class OSTRM {public:char pad[0x10];int count;int CbWrite(void *,int);};
void WriteTftPchz(TFT *,OSTRM *,char *);
void WriteTftUl(TFT *,OSTRM *,unsigned long);
void WriteTftDouble(TFT *,OSTRM *,double);
extern "C" unsigned int func_0021ED28(const char *);
static inline char *Next(char **args){char *p=*args;*args=p+8;return p;}
static inline void WritePchz(OSTRM *out,char *s){out->CbWrite(s,func_0021ED28(s));}
void WriteTft(TFT *f,OSTRM *out,char **args,char *text,int count){
    switch(f->conversion){
    case '%':out->CbWrite(&f->conversion,1);break;
    case 'c':{unsigned char c=*(unsigned char *)Next(args);out->CbWrite(&c,1);break;}
    case 's':WriteTftPchz(f,out,*(char **)Next(args));break;
    case 'p':f->precision=8;f->conversion='x';f->cbits=0;
    case 'b':case 'd':case 'i':case 'o':case 'u':case 'x':{
        unsigned long n;
        switch(f->cbits){
        case 0:case 1:n=*(unsigned int *)Next(args);break;
        case 2:n=*(unsigned long *)Next(args);break;
        }
        WriteTftUl(f,out,n);break;
    }
    case 'e':case 'f':case 'g':
        if(f->columns){
            float *p=*(float **)Next(args);
            char *rowOpen="{ ",*rowSep=",\n",*itemSep=", ",*rowClose=" }";
            if(f->rows>1)WritePchz(out,"\n");
            for(int row=0;row<f->rows;++row){
                if(row)WritePchz(out,rowSep);
                WritePchz(out,rowOpen);
                for(int column=0;column<f->columns;++column){
                    if(column)WritePchz(out,itemSep);
                    WriteTftDouble(f,out,(double)*p++);
                }
                WritePchz(out,rowClose);
            }
            if(f->rows>1)WritePchz(out,"\n");
        }else WriteTftDouble(f,out,*(double *)Next(args));
        break;
    case 'n':
        switch(f->cbits){
        case 0:**(int **)Next(args)=out->count;break;
        case 1:{int n=out->count;**(short **)Next(args)=n;}break;
        case 2:**(long **)Next(args)=out->count;break;
        }
        break;
    default:out->CbWrite(text,count);break;
    }
}
