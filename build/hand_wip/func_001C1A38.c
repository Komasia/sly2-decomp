struct E { float t; unsigned short k; unsigned short bit; };
void *func_002332B8(void *dst, const void *src, unsigned int cb);
static inline unsigned ByteLength(unsigned count){register unsigned length __asm__("$6");__asm__("sll %0,%1,3":"=r"(length):"r"(count));return length;}
void func_001C1A38(int c, struct E *ae, int bit, float g0, float g1)
{
    int i, j;
    for (i = 0; i < c; i++)
        if (g0 <= ae[i].t) break;
    for (j = i; j < c; j++)
        if (g1 < ae[j].t) break;
    func_002332B8(&ae[j + 2], &ae[j], (unsigned)(c-j)*8U);
    ae[j + 1].t = g1;
    ae[j + 1].bit = bit;
    ae[j + 1].k = 0;
    func_002332B8(&ae[i + 1], &ae[i], ByteLength((unsigned)(j-i)));
    ae[i].bit = bit;
    ae[i].t = g0;
    ae[i].k = 1;
}

#define OFF(T,F) ((unsigned long)&((T*)0)->F)
typedef char event_layout[(sizeof(struct E)==8 && OFF(struct E,t)==0 && OFF(struct E,k)==4 && OFF(struct E,bit)==6 && sizeof(unsigned)==4 && sizeof(unsigned short)==2 && sizeof(float)==4 && sizeof(int)==4 && sizeof(void*)==4 && __alignof__(struct E)==4)?1:-1];
