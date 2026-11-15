typedef int qword __attribute__((mode(TI)));
struct EDGE {unsigned short aipos[2];int pad;struct EDGE*pedgeNext;};   /* Sly 1 geom.h EDGE */
struct Poly {char pad[0x10];struct EDGE*edges;};
struct Entry {int a,b;struct Poly*poly;};
struct GEOM {int pad;qword *apos;};
struct BSPREF {int pad,cnode;void *pad8;void *pbsp;};
struct REQ {int cb,kind;REQ(int cb_,int kind_):cb(cb_),kind(kind_) {}};
struct FRAME {int pad[4];};
extern "C" struct FRAME *__10STACKSCOPE(struct FRAME*);
extern "C" void _$_10STACKSCOPE(struct FRAME*,int);
extern "C" void *PvAllocStackImpl(struct REQ*) asm("PvAllocStackImpl__Fi");
extern "C" int ClipBspPlane(void*,int,qword,int*,struct Entry**,float) asm("ClipBspPlane__FP6BSPREFP6VECTORG9VU_VECTORfPiPP4NODE");
static inline int Min(int a,int b){return a<b?a:b;}
// func_001665F0: collect (up to cMax) the distinct edges touching point ipos of a geometry: the BSP nodes at the point
// (ClipBspPlane), then each node's edges that have the point as an end.
extern "C" int func_001665F0(struct GEOM*pgeom,struct BSPREF*pbspref,int ipos,int cMax,struct EDGE**apedge){
 struct FRAME frame;int capacity,limit,cedge,i;struct Entry*first,*end;
 __10STACKSCOPE(&frame);
 capacity=Min(pbspref->cnode,0x1555);limit=capacity;struct REQ req(capacity*12,16);
 end=first=(struct Entry*)PvAllocStackImpl(&req);
 if(ClipBspPlane(pbspref->pbsp,0x7FFFFFFF,pgeom->apos[ipos],&limit,&end,1.0f)!=2){_$_10STACKSCOPE(&frame,2);return 0;}
 int cnode=end-first;
 cedge=0;
 for(i=0;i<cnode;i++){
  struct EDGE*pedge=first[i].poly->edges;struct EDGE**dst;
  if(!pedge)continue;
  dst=(struct EDGE**)((cedge<<2)+(int)apedge);
  for(;pedge;pedge=pedge->pedgeNext){
   int j;
   if(ipos!=pedge->aipos[0] && ipos!=pedge->aipos[1])continue;
   for(j=0;j<cedge;j++){if(pedge==apedge[j])break;}
   if(j>=cedge && cedge<cMax){*dst++=pedge;cedge++;}
  }
 }
 _$_10STACKSCOPE(&frame,2);
 return cedge;
}
