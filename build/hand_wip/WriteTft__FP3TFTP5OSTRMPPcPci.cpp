// Complete WIP: physical argument slots, every conversion and used loop state.
struct TFT {int fLeft,fPlus,fSpace,fPrefix,fZero,fPrec0,width,precision,cbits,rowItems,rowCount;unsigned char conversion;int fUpper;};
class OSTRM {public:char *buffer;int capacity,used;char unknownC[4];int count,buffered;int CbWrite(void *,int);};
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
        if(f->rowItems){
            float *p=*(float **)Next(args);
            if(f->rowCount>1)out->CbWrite((char *)"\n",func_0021ED28("\n"));
            char *rowSep=",\n",*rowOpen="{ ",*itemSep=", ",*rowClose=" }";
            int i=0;
            while(i<f->rowCount){
                if(i)WritePchz(out,rowSep);
                int nextRow=i+1;
                WritePchz(out,rowOpen);
                for(i=0;i<f->rowItems;++i){
                    if(i)WritePchz(out,itemSep);
                    WriteTftDouble(f,out,(double)*p++);
                }
                i=nextRow;
                WritePchz(out,rowClose);
            }
            if(f->rowCount>1)out->CbWrite((char *)"\n",func_0021ED28("\n"));
        }else WriteTftDouble(f,out,*(double *)Next(args));
        break;
    case 'n':
        switch(f->cbits){
        case 0:{int *destination=*(int **)Next(args);*destination=out->count;}break;
        case 1:{short *destination=*(short **)Next(args);*destination=out->count;}break;
        case 2:{long *destination=*(long **)Next(args);*destination=out->count;}break;
        }
        break;
    default:out->CbWrite(text,count);break;
    }
}
