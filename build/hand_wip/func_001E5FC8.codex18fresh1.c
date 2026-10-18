// Cache eleven world-space segment samples and cumulative distances.
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f;};
struct M4 {qword a,b,c,d;};
struct PAIR {qword a,b;};
struct S {char pad[0xEC];float *times,*dist;qword *v;char padF8[8];struct M4 mat;qword *in,*out;int segment;float lengths[11];};
void func_00117120(float,float,float,qword,qword,qword,qword,qword*,qword*,qword*);
static inline float Len(qword a){qword one;float f;__asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z\n\tvsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(a),"=&j"(one));__asm__("mtc1 %1,%0":"=f"(f):"r"(a));return f;}
void func_001E5FC8(struct S*p,int index) {
 union U prev,cur,start,end,a,b;
 typedef char cache_local_prev[(sizeof(prev)==16 && __alignof__(prev)==16)?1:-1];
 typedef char cache_local_cur[(sizeof(cur)==16 && __alignof__(cur)==16)?1:-1];
 typedef char cache_local_start[(sizeof(start)==16 && __alignof__(start)==16)?1:-1];
 typedef char cache_local_end[(sizeof(end)==16 && __alignof__(end)==16)?1:-1];
 typedef char cache_local_a[(sizeof(a)==16 && __alignof__(a)==16)?1:-1];
 typedef char cache_local_b[(sizeof(b)==16 && __alignof__(b)==16)?1:-1];

 register int i __asm__("$19")=index,j __asm__("$18");
 register float duration __asm__("$f20"),tenth __asm__("$f21");
 register float *length __asm__("$16");
 register qword *destination __asm__("$20");
 register struct M4*m __asm__("$5")=&p->mat;
 if(i==p->segment)return;
 {
 register qword *points __asm__("$6"),*outgoing __asm__("$3"),*incoming __asm__("$4");
 register unsigned offset __asm__("$2");
 register qword m0 __asm__("vf1"),m1 __asm__("vf3"),m2 __asm__("vf2"),m3 __asm__("vf6");
 register qword p0 __asm__("vf4"),p1 __asm__("vf7"),t0 __asm__("vf8"),t1 __asm__("vf5"),direction __asm__("vf9");
 register qword *incomingPoint __asm__("$2");
 register unsigned timeOffset __asm__("$4");
 register float *timeBase __asm__("$2"),*time __asm__("$4");
 register float firstTime __asm__("$f1"),lastTime __asm__("$f0");
 __asm__("lw %0,%4\n\tsll %1,%7,%8\n\tlw %2,%5\n\tlw %3,%6\n\taddu %0,%1,%0\n\taddu %2,%1,%2"
  :"=&r"(points),"=&r"(offset),"=&r"(outgoing),"=r"(incoming):"m"(p->v),"m"(p->out),"m"(p->in),"r"(i),"I"(4));
 __asm__("lqc2 %0,0x10(%4)\n\taddu %1,%2,%3":"=j"(m1),"=r"(incomingPoint):"r"(offset),"r"(incoming),"r"(m),"m"(m->b));
 __asm__("lqc2 %0,0x20(%5)\n\tlqc2 %1,%7\n\tsll %2,%8,%9\n\tlqc2 %3,0x30(%5)\n\tdaddu %4,$zero,$zero"
  :"=j"(m2),"=j"(t1),"=&r"(timeOffset),"=j"(m3),"=r"(j):"r"(m),"m"(*(const struct PAIR*)&m->c),"m"(incomingPoint[1]),"r"(i),"I"(2));
 __asm__("lqc2 %0,%1":"=j"(p0):"m"(points[0]));
 destination=&cur.q;
 __asm__("lqc2 %0,%1":"=j"(p1):"m"(points[1]));
 length=p->lengths;
 __asm__("lqc2 %0,%1":"=j"(t0):"m"(*outgoing));
 __asm__("lw %0,%3\n\tsw %z5,%1\n\tlqc2 %2,%4":"=&r"(timeBase),"=m"(p->lengths[0]),"=j"(m0):"m"(p->times),"m"(p->mat.a),"rJ"(0));
 time=(float*)(timeOffset+(unsigned)timeBase);
 __asm__("lwc1 %0,0(%1)":"=f"(firstTime):"r"(time),"m"(time[0]));
 __asm__("vmulax.xyz ACC,%2,%5x\n\tvmadday.xyz ACC,%3,%5y\n\tvmaddz.xyz %0,%4,%5z\n\tsqc2 %0,%1":"+j"(direction),"=m"(b.q):"j"(m0),"j"(m1),"j"(m2),"j"(t1));
 __asm__("vmulax.xyz ACC,%2,%6x\n\tvmadday.xyz ACC,%3,%6y\n\tvmaddaz.xyz ACC,%4,%6z\n\tvmaddw.xyz %0,%5,$vf0w\n\tvmulax.xyz ACC,%2,%7x\n\tvmadday.xyz ACC,%3,%7y\n\tvmaddaz.xyz ACC,%4,%7z\n\tvmaddw.xyz %1,%5,$vf0w":"+&j"(t1),"+j"(direction):"j"(m0),"j"(m1),"j"(m2),"j"(m3),"j"(p1),"j"(p0));
 __asm__("li.s %0,%1":"=f"(tenth):"F"(0.1f):"$1");
 __asm__("vmulax.xyz ACC,%2,%5x\n\tvmadday.xyz ACC,%3,%5y\n\tvmaddz.xyz %0,%4,%5z\n\tlwc1 %1,4(%6)":"+j"(p0),"=f"(lastTime):"j"(m0),"j"(m1),"j"(m2),"j"(t0),"r"(time),"m"(time[1]));
 __asm__("sqc2 %4,%0\n\tsqc2 %5,%1\n\tsub.s %2,%7,%8\n\tsqc2 %6,%3":"=m"(end.q),"=m"(start.q),"=f"(duration),"=m"(a.q):"j"(t1),"j"(direction),"j"(p0),"f"(lastTime),"f"(firstTime));
 }
 do {
  {
   register float parameter __asm__("$f13"),unit __asm__("$f14"),whole __asm__("$f12");
   register qword arg0 __asm__("$4"),arg1 __asm__("$5"),arg2 __asm__("$6"),arg3 __asm__("$7");
   register qword *result __asm__("$8"),*derivative __asm__("$9"),*acceleration __asm__("$10");
   __asm__("mtc1 %2,%0\n\tcvt.s.w %0,%0\n\tli.s %1,%3":"=f"(parameter),"=f"(unit):"r"(j),"F"(1.0f):"$1");
   __asm__("lq %0,%4\n\tmov.s %1,%6\n\tlq %2,%5\n\tdaddu %3,%7,$zero":"=&r"(arg0),"=f"(whole),"=&r"(arg1),"=r"(result):"m"(start.q),"m"(a.q),"f"(duration),"r"(destination));
   __asm__("mul.s %0,%0,%8\n\tlq %1,%5\n\tlq %2,%6\n\tdaddu %3,%z7,$zero\n\tdaddu %4,%z7,$zero":"+f"(parameter),"=r"(arg2),"=r"(arg3),"=r"(derivative),"=r"(acceleration):"m"(end.q),"m"(b.q),"rJ"(0),"f"(tenth));
   func_00117120(whole,parameter*duration,unit,arg0,arg1,arg2,arg3,result,derivative,acceleration);
  }
  if(j>0){
   register qword old __asm__("vf1")=prev.q,current __asm__("vf2")=cur.q;
   register float accumulated __asm__("$f1");
   __asm__("vsub.xyzw %0,%0,%2\n\tlwc1 %1,-4(%4)":"+j"(old),"=f"(accumulated):"j"(current),"m"(length[-1]),"r"(length));
   *length=accumulated+Len(old);
  }
  prev.q=cur.q;++j;++length;
 }while(j<11);
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

typedef char cache_pair_size[(sizeof(struct PAIR)==32)?1:-1];
typedef char cache_pair_align[(__alignof__(struct PAIR)==16)?1:-1];
