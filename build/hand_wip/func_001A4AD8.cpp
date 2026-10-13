struct Q { int a[4]; };
struct M3 { struct Q q[3]; };
struct P { char pad[0x120]; struct M3 m; };
struct G { int x0, x4, x8; int *p; };
struct O { char pad[0x14]; int x14; int *x18; };
extern struct G D_002DEA28;
extern struct M3 D_002BFC60;
extern "C" void func_001A3968(struct P *p);
static inline int* Write(struct G*g,int x){int*d;*g->p=x;d=g->p+1;g->p=d;return d;}
static inline void Copy(int*d,const int*s,int words){int j;for(j=words-4;j>=0;j-=4){int a=s[0],b=s[1],c=s[2],e=s[3];d[0]=a;d[1]=b;d[2]=c;d[3]=e;s+=4;d+=4;}}
extern "C" void func_001A4AD8(void *a0, int n, struct P **ap, struct O *o)
{
    int i;
    o->x18 = D_002DEA28.p;
    for (i = 0; i < n; i++) {
        struct P *p = ap[i];
        func_001A3968(p);
        int*d=Write(&D_002DEA28,0x6C03C000 | (i*3+0x15));
        Copy(d,(int*)&p->m,12);
        D_002DEA28.p += 12;
    }
    for (; i < 4; i++) {
        int*d=Write(&D_002DEA28,0x6C03C000 | (i*3+0x15));
        Copy(d,(int*)&D_002BFC60,12);
        D_002DEA28.p += 12;
    }
    o->x14 = ((char *)D_002DEA28.p - (char *)o->x18) >> 4;
}
