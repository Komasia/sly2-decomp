typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct PATH {char pad[0xE8];int count;int padEC;float*dist;U*pos;};
struct S {char pad[0x48];PATH*path;int active;int pad50;U*a;U*b;float*time;char pad60[0x84-0x60];int capacity;float step;};
extern float D_002C3678;
extern "C" void func_001E6330(PATH*);
extern "C" void func_001E95B0(S*,float);
static inline qword Scalar(float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));return q;}
static inline qword PublishScalar(U&s,qword q){s.q=q;return s.q;}
static inline qword ReadLeft(const U&v){register qword q __asm__("vf2");__asm__("lqc2 %0,%1":"=j"(q):"m"(v.q));return q;}
static inline qword ReadRight(const U&v){register qword q __asm__("vf1");__asm__("lqc2 %0,%1":"=j"(q):"m"(v.q));return q;}
static inline qword Blend(const U&a,const U&b,float f,float cf,U&s){qword fraction=Scalar(f),inverse=Scalar(cf);qword one=PublishScalar(s,inverse),left=ReadLeft(a),k=PublishScalar(s,fraction),right=ReadRight(b);__asm__("vmulax.xyzw $ACC,%0,%2x\n\tvmaddx.xyzw %0,%3,%1x":"+j"(left):"j"(k),"j"(one),"j"(right));return left;}
static inline qword BlendLast(const U&a,const U&b,float f,float cf,U&s){qword fraction=Scalar(f),inverse=Scalar(cf);qword one=PublishScalar(s,inverse),left=ReadLeft(a),k=PublishScalar(s,fraction),right=ReadRight(b);__asm__("vmulax.xyzw $ACC,%1,%0x\n\tvmaddx.xyzw %0,%2,%3x":"+j"(one):"j"(left),"j"(right),"j"(k));return one;}
static inline void BlendLastInto(U*out,const U&a,const U&b,float f,float cf,U&s){out->q=BlendLast(a,b,f,cf,s);}
static inline PATH *GetPath(const S*p){
    register PATH *result __asm__("$6");
    __asm__("lw %0,%1":"=r"(result):"m"(p->path));return result;
}
static inline int Count(const PATH*p){
 register int result __asm__("$5");
 __asm__("lw %0,%1":"=r"(result):"m"(p->count));return result;
}
void func_001E95B0(S*p,float time){
 PATH *path=GetPath(p);
 int count=Count(path);
 int n;
 if(time<p->time[count-1]){
  int i=count;
  register PATH *reversePath __asm__("$5")=path;
  for(;;){--i;if(i<0)break;if(p->time[i]<time)break;}
  i++;
  reversePath->count=i+1;
  p->time[i]=time;
  goto refresh;
 }
 n=count;
 if(time<p->time[count-2]+D_002C3678*p->step){p->time[count-1]=time;goto finished;}
repeat:
 if(n<p->capacity){
  n++;
  p->a[n-1]=p->a[n-2];
  p->b[n-1]=p->b[n-2];
  p->time[n-1]=time;
  p->path->pos[n-1]=p->path->pos[n-2];
  p->path->dist[n-1]=p->path->dist[n-2];
  p->time[n-2]=p->time[n-3]+p->step;
  float f=(p->time[n-2]-p->time[n-3])/(p->time[n-1]-p->time[n-3]);
  float cf=1-f;
  U scalar;
  p->a[n-2].q=Blend(p->a[n-3],p->a[n-1],f,cf,scalar);
  p->b[n-2].q=Blend(p->b[n-3],p->b[n-1],f,cf,scalar);
  BlendLastInto(&p->path->pos[n-2],p->path->pos[n-3],p->path->pos[n-1],f,cf,scalar);
  p->path->dist[n-2]=cf*p->path->dist[n-3]+f*p->path->dist[n-1];
  if(time<p->time[n-2]+D_002C3678*p->step)p->time[n-1]=time;
  else goto repeat;
 }else p->active=0;
finished:
 p->path->count=n;
refresh:
 func_001E6330(p->path);
}

typedef char layout_pointer[(sizeof(void*)==4)?1:-1];
typedef char layout_int[(sizeof(int)==4)?1:-1];
typedef char layout_float[(sizeof(float)==4)?1:-1];
typedef char layout_qword[(sizeof(qword)==16)?1:-1];
typedef char layout_U[(sizeof(U)==16)?1:-1];
typedef char layout_U_alignment[(__alignof__(U)==16)?1:-1];
typedef char layout_PATH_prefix[(sizeof(PATH)==0xF8)?1:-1];
typedef char layout_S_prefix[(sizeof(S)==0x8C)?1:-1];
typedef char layout_PATH_count[((unsigned)&((PATH*)0)->count==0xe8)?1:-1];
typedef char layout_PATH_dist[((unsigned)&((PATH*)0)->dist==0xf0)?1:-1];
typedef char layout_PATH_pos[((unsigned)&((PATH*)0)->pos==0xf4)?1:-1];
typedef char layout_S_path[((unsigned)&((S*)0)->path==0x48)?1:-1];
typedef char layout_S_active[((unsigned)&((S*)0)->active==0x4c)?1:-1];
typedef char layout_S_a[((unsigned)&((S*)0)->a==0x54)?1:-1];
typedef char layout_S_b[((unsigned)&((S*)0)->b==0x58)?1:-1];
typedef char layout_S_time[((unsigned)&((S*)0)->time==0x5c)?1:-1];
typedef char layout_S_capacity[((unsigned)&((S*)0)->capacity==0x84)?1:-1];
typedef char layout_S_step[((unsigned)&((S*)0)->step==0x88)?1:-1];
