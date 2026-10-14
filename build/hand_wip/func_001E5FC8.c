/* Full draft: 43/110 literal instruction differences. */
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f;};
struct M4 {qword a,b,c,d;};
struct S {char pad[0xEC];float *times,*dist;qword *v;char padF8[8];struct M4 mat;qword *in,*out;int segment;float lengths[11];};
void func_00117120(float,float,float,qword,qword,qword,qword,qword*,qword*,qword*);
static inline void StoreQ(qword *out,qword value){__asm__("sqc2 %1,%0":"=m"(*out):"j"(value));}
static inline float ReadTime0(const float *time){register const float *cursor __asm__("$4")=time;register float value __asm__("$f1");__asm__("lwc1 %0,0(%1)":"=f"(value):"r"(cursor),"m"(time[0]));return value;}
static inline float ReadTime1(const float *time){register const float *cursor __asm__("$4")=time;register float value __asm__("$f0");__asm__("lwc1 %0,4(%1)":"=f"(value):"r"(cursor),"m"(time[1]));return value;}
static inline float Mul(float a,float b){float r;__asm__("mul.s %0,%1,%2":"=f"(r):"f"(a),"f"(b));return r;}
static inline qword PointKept(qword keep,qword m0,qword m1,qword m2,qword m3,qword a){__asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"+j"(keep):"j"(m0),"j"(m1),"j"(m2),"j"(m3),"j"(a));return keep;}
static inline qword Dir(qword m0,qword m1,qword m2,qword a){register qword r __asm__("vf9");__asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"+j"(r):"j"(m0),"j"(m1),"j"(m2),"j"(a));return r;}
static inline qword DirKept(qword keep,qword m0,qword m1,qword m2,qword a){__asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"+j"(keep):"j"(m0),"j"(m1),"j"(m2),"j"(a));return keep;}
static inline qword Sub(qword a,qword b) {qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline float Len(qword a){qword one;float f;__asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z\n\tvsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(a),"=&j"(one));__asm__("mtc1 %1,%0":"=f"(f):"r"(a));return f;}
void func_001E5FC8(struct S*p,int i) {
 union U prev,cur,start,end,a,b;
 int j;
 float duration,firstTime;
 const float *time;
 register struct M4 *m __asm__("a1")=&p->mat;
 typedef char layout_local_prev[(sizeof(prev)==16 && __alignof__(prev)==16)?1:-1];
 typedef char layout_local_cur[(sizeof(cur)==16 && __alignof__(cur)==16)?1:-1];
 typedef char layout_local_start[(sizeof(start)==16 && __alignof__(start)==16)?1:-1];
 typedef char layout_local_end[(sizeof(end)==16 && __alignof__(end)==16)?1:-1];
 typedef char layout_local_a[(sizeof(a)==16 && __alignof__(a)==16)?1:-1];
 typedef char layout_local_b[(sizeof(b)==16 && __alignof__(b)==16)?1:-1];

 if(i==p->segment)return;
 {qword v0=p->v[i],v1=p->v[i+1],t0=p->out[i],t1=p->in[i+1];
 qword m1=m->b,m2=m->c,m3=m->d;
 p->lengths[0]=0;
 {qword m0=p->mat.a;
 time=p->times+i; firstTime=ReadTime0(time);
 {
 qword incoming=Dir(m0,m1,m2,t1);
 StoreQ(&b.q,incoming);
 end.q=PointKept(t1,m0,m1,m2,m3,v1);
 start.q=PointKept(incoming,m0,m1,m2,m3,v0);
 a.q=DirKept(v0,m0,m1,m2,t0);
 }}}
 duration=ReadTime1(time)-firstTime;
 for(j=0;j<11;j++) {
  func_00117120(duration,Mul((float)j*0.1f,duration),1.0f,start.q,a.q,end.q,b.q,&cur.q,0,0);
  if(j>0)p->lengths[j]=p->lengths[j-1]+Len(Sub(prev.q,cur.q));
  prev.q=cur.q;
 }
 p->segment=i;
}

typedef char layout_qword[(sizeof(qword)==16)?1:-1];
typedef char layout_union[(sizeof(union U)==16)?1:-1];
typedef char layout_matrix[(sizeof(struct M4)==64)?1:-1];
typedef char layout_float[(sizeof(float)==4)?1:-1];
typedef char layout_int[(sizeof(int)==4)?1:-1];
typedef char layout_pointer[(sizeof(void*)==4)?1:-1];
typedef char layout_union_align[(__alignof__(union U)==16)?1:-1];
typedef char layout_qword_align[(__alignof__(qword)==16)?1:-1];
typedef char layout_matrix_align[(__alignof__(struct M4)==16)?1:-1];
typedef char layout_receiver_align[(__alignof__(struct S)==16)?1:-1];
typedef char layout_receiver_prefix[(sizeof(struct S)==0x180)?1:-1];
typedef char layout_M4_a[((unsigned)&((struct M4*)0)->a==0x0)?1:-1];
typedef char layout_M4_b[((unsigned)&((struct M4*)0)->b==0x10)?1:-1];
typedef char layout_M4_c[((unsigned)&((struct M4*)0)->c==0x20)?1:-1];
typedef char layout_M4_d[((unsigned)&((struct M4*)0)->d==0x30)?1:-1];
typedef char layout_S_times[((unsigned)&((struct S*)0)->times==0xec)?1:-1];
typedef char layout_S_dist[((unsigned)&((struct S*)0)->dist==0xf0)?1:-1];
typedef char layout_S_v[((unsigned)&((struct S*)0)->v==0xf4)?1:-1];
typedef char layout_S_mat[((unsigned)&((struct S*)0)->mat==0x100)?1:-1];
typedef char layout_S_in[((unsigned)&((struct S*)0)->in==0x140)?1:-1];
typedef char layout_S_out[((unsigned)&((struct S*)0)->out==0x144)?1:-1];
typedef char layout_S_segment[((unsigned)&((struct S*)0)->segment==0x148)?1:-1];
typedef char layout_S_lengths[((unsigned)&((struct S*)0)->lengths==0x14c)?1:-1];
typedef char layout_length_span[(sizeof(((struct S*)0)->lengths)==44)?1:-1];
typedef char layout_union_qword[((unsigned)&((union U*)0)->q==0)?1:-1];
typedef char layout_union_float[((unsigned)&((union U*)0)->f==0)?1:-1];
