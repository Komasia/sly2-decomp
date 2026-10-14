extern "C" {
struct S { unsigned char *start; unsigned char *cur; void *font; char pad[0x74-0xC]; float width; char pad1[0x88-0x78]; float scale; };
extern unsigned char D_002AA6A1[];
void func_00215CA8(struct S *,unsigned char *);
int func_00215D40(struct S *);
float func_00216B80(void *,int);
static inline void StoreByte(unsigned char *p,unsigned char c){*p=c;}
int func_00215F40(struct S *p) {
    float width=0.0f;
    int lines=1;
    long c;
    func_00215CA8(p,0);
    while ((c=func_00215D40(p))!=0) {
        if(c=='\n') { width=0.0f; lines++; }
        else {
            width+=func_00216B80(p->font,c)*p->scale;
        }
        if(p->width!=0.0f && p->width<width) {
                unsigned char *q=p->cur-1;
                while(q>=p->start && *q!='\n') {
                    if((*q==' ' || *q=='\t') && !(D_002AA6A1[q[1]]&0x10)) {
                        p->cur=q+1;
                        StoreByte(q,'\n');
                        lines++;
                        width=0.0f;
                        break;
                    }
                    q--;
                }
                if(width!=0.0f && *p->cur) {
                    StoreByte(p->cur,'\n'); lines++; width=0.0f;
                }
            }

    }
    return lines;
}

}