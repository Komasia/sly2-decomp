typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];};
struct TRI{char d[12];};
union NODE{qword plane;struct{char pad[12];unsigned short child[2];}e;};
struct GRAPH{char pad[12];TRI*leaves;int count;NODE*nodes;};
struct STATE{NODE*node;TRI*leaf;float t;U plane;};
struct ROW{U a,b,planeA,planeB;float t0,t1;int flags;TRI*leaf;char tail[16];};
extern "C" void*func_002333B4(void*,int,unsigned int);
extern "C" int func_001BF398(float);
static inline float GetX(qword q){float x;__asm__("mtc1 %1,%0":"=f"(x):"r"(q));return x;}
static inline float GetY(qword q){float y;__asm__("prot3w %0,%1":"=r"(y):"r"(q));return y;}
static inline qword Make(float x,float y,float z){qword q,t;__asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0":"=&r"(q),"=&r"(t):"f"(x),"f"(y),"f"(z));return q;}
static inline float Dot(qword a,qword b){qword d,one;float f;__asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z":"=j"(d),"=&j"(one):"j"(a),"j"(b));__asm__("qmfc2.ni %0, %1":"=r"(f):"j"(d));return f;}
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
static inline qword VecCombo(VU_FLOAT f1, VU_VECTOR v1, VU_FLOAT f2, VU_VECTOR v2)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %2, %1x\n\tvmaddx.xyzw %0, %4, %3x" : "=j"(r) : "j"(f1.q), "j"(v1.q), "j"(f2.q), "j"(v2.q));
    return r;
}
static inline qword Lerp(const qword&a,const qword&b,float t){return VecCombo(VU_FLOAT(1.0f-t),VU_VECTOR(a),VU_FLOAT(t),VU_VECTOR(b));}
static inline void SetState(STATE*s,unsigned child,NODE*nodes,NODE*end,TRI*leaves,int mask){
 if(child&0x8000){s->node=end;if(child&mask)s->leaf=leaves+(child&0x3FFF);else s->leaf=0;}
 else{s->leaf=0;s->node=nodes+child;}
}
extern "C" int func_001BF3D8(GRAPH*g,qword from,qword to,int capacity,ROW*out,int flags){
 STATE st[33];
 STATE*cur=&st[0];
 STATE*stack=&st[1];
 STATE*top=stack;
 ROW*prev=0;
 int count=0;
 int mask;
 NODE*nodes=g->nodes;
 NODE*end=nodes+g->count;
 TRI*leaves=g->leaves;
 qword fromPlane,toPlane;
 mask=0x4000;
 if(flags&1)mask=0x8000;
 func_002333B4(cur,0,sizeof(STATE));
 func_002333B4(top,0,sizeof(STATE));
 cur->node=nodes;
 fromPlane=Make(GetX(from),GetY(from),-1.0f);
 top->t=1.0f;
 toPlane=Make(GetX(to),GetY(to),-1.0f);
 for(;;){
  if(cur->node==end){
   do{
    if(cur->leaf){
     if(prev&&cur->t==prev->t1&&((flags&2)||cur->leaf==prev->leaf)){
      prev->b.q=Lerp(from,to,top->t);
      prev->t1=top->t;
      prev->planeB=top->plane;
     }else{
      float lo,hi;
      if(count>=capacity)return capacity;
      prev=out+count;
      count++;
      func_002333B4(prev,0,sizeof(ROW));
      lo=cur->t;hi=top->t;
      prev->a.q=Lerp(from,to,lo);
      prev->b.q=Lerp(from,to,hi);
      prev->t0=lo;prev->t1=hi;prev->flags=3;
      prev->planeA=cur->plane;prev->planeB=top->plane;
      prev->leaf=cur->leaf;
     }
    }
    if(!(stack<top))return count;
    *cur=*top;
    top--;
   }while(cur->node==end);
  }
  {
   NODE*n=cur->node;
   float d0=Dot(n->plane,fromPlane);
   float d1=Dot(n->plane,toPlane);
   int s0=func_001BF398(d0);
   int s1=func_001BF398(d1);
   int neg=s0==1||s1==1;
   int pos=s0==0||s1==0;
   unsigned child;
   if(neg&&pos){
    float cross=d0/(d0-d1);
    float lo=cur->t,hi=top->t;
    float dl=(1.0f-lo)*d0+lo*d1;
    float dh=(1.0f-hi)*d0+hi*d1;
    int nearNeg;
    if(lo<cross&&cross<hi){
     top++;
     top->t=cross;
     top->plane.f[0]=((U&)n->plane).f[0];
     top->plane.f[1]=((U&)n->plane).f[1];
     top->plane.f[2]=0;
     top->plane.f[3]=((U&)n->plane).f[2];
     SetState(top,n->e.child[dl<=0.0f],nodes,end,leaves,mask);
    }
    nearNeg=dl<0.0f||(dl==0.0f&&dh<=0.0f);
    child=n->e.child[!nearNeg];
   }else child=n->e.child[pos];
   SetState(cur,child,nodes,end,leaves,mask);
  }
 }
}
