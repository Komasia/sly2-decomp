typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct PATH {char pad[0xE8];int count;int padEC;float*dist;U*pos;};
struct S {char pad[0x48];PATH*path;int active;int pad50;U*a;U*b;float*time;char pad60[0x84-0x60];int capacity;float step;};
extern float D_002C3678;
extern "C" void func_001E6330(PATH*);
extern "C" void func_001E95B0(S*,float);
static inline qword Bc(float f){qword q;U s;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));s.q=q;return s.q;}
static inline qword Blend(const U&a,const U&b,float f,float cf){qword k=Bc(f),one=Bc(cf),r=a.q;__asm__("vmulax.xyzw $ACC,%0,%2x\n\tvmaddx.xyzw %0,%3,%1x":"+j"(r):"j"(k),"j"(one),"j"(b.q));return r;}
static inline qword BlendLast(const U&a,const U&b,float f,float cf){
    qword k=Bc(f),one=Bc(cf);
    __asm__("vmulax.xyzw $ACC,%1,%0x\n\tvmaddx.xyzw %0,%2,%3x"
        :"+j"(one):"j"(a.q),"j"(b.q),"j"(k));
    return one;
}
static inline PATH *GetPath(const S*p){
    register PATH *result __asm__("$6");
    __asm__("lw %0,%1":"=r"(result):"m"(p->path));return result;
}
void func_001E95B0(S*p,float time){
 PATH *path=GetPath(p);
 int count=path->count;
 if(time<p->time[count-1]){
  int i=count;
  for(;;){--i;if(i<0)break;if(p->time[i]<time)break;}
  i++;
  path->count=i+1;
  p->time[i]=time;
  return;
 }
 if(time<p->time[count-2]+D_002C3678*p->step){p->time[count-1]=time;return;}
 int n=count;
 for(;;){
  if(n>=p->capacity){p->active=0;break;}
  n++;
  p->a[n-1]=p->a[n-2];
  p->b[n-1]=p->b[n-2];
  p->time[n-1]=time;
  p->path->pos[n-1]=p->path->pos[n-2];
  p->path->dist[n-1]=p->path->dist[n-2];
  p->time[n-2]=p->time[n-3]+p->step;
  float f=(p->time[n-2]-p->time[n-3])/(p->time[n-1]-p->time[n-3]);
  float cf=1-f;
  p->a[n-2].q=Blend(p->a[n-3],p->a[n-1],f,cf);
  p->b[n-2].q=Blend(p->b[n-3],p->b[n-1],f,cf);
  p->path->pos[n-2].q=BlendLast(p->path->pos[n-3],p->path->pos[n-1],f,cf);
  p->path->dist[n-2]=cf*p->path->dist[n-3]+f*p->path->dist[n-1];
  if(time<p->time[n-2]+D_002C3678*p->step){p->time[n-1]=time;break;}
 }
 p->path->count=n;
 func_001E6330(p->path);
}
