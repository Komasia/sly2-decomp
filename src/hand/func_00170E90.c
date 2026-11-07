typedef int qword __attribute__((mode(TI)));
typedef union {qword q;float f[4];} U;
struct N{int kind,tag;qword*position;char padC[0xC];struct N*next;};
struct P{char pad[0x50];struct N*head;};
struct CHOICE{struct N*node;struct P*object;float value;};
extern char g_sw[];
extern float D_002A52B0;
struct P*PloFindSwNearest__FP2LO3OIDii(void*,int,int,struct P*);
void GetCmdAim__FP5GUARDG9VU_VECTORP2LOP6VECTORPf(struct P*,qword,struct P*,qword*,float*);
void NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(struct P*,qword,void*,qword*,qword*,float*,float*);
void NearestCrvS__FP3CRVG9VU_VECTORPvP6VECTORT3PfT5f(struct P*,qword,void*,qword*,qword*,float*,float*,float);
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline float Length(qword v){qword d,one;float f;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"0"(v));__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(d):"0"(d));__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(d));return f;}
// Choose the closest eligible point while walking the selector chain.
// name: SafeHouse port (RefindSavedScript)
void RefindSavedScript__FP7CMDLISTG9VU_VECTORP11SAVEDSCRIPT(struct P*root,qword pos,struct CHOICE*out){
 struct CHOICE choice;
 U hit;
 float value;
 struct P*current=root;
 struct N*node;
 int stopped=0;
 float best=D_002A52B0;
 for(node=current->head;node;node=node->next){
  switch(node->kind){
  case 11:stopped=1;break;
  case 12:stopped=0;break;
  case 3:case 7:
   if(stopped)break;
   if(node->tag!=-1){struct P*object=PloFindSwNearest__FP2LO3OIDii(g_sw,4,node->tag,current);GetCmdAim__FP5GUARDG9VU_VECTORP2LOP6VECTORPf(root,pos,object,&hit.q,0);}
   else if(node->position)hit.q=*node->position;
   {float d=Length(Sub(pos,hit.q));if(d<best){best=d;choice.node=node;choice.object=current;}}
   break;
  case 6:
   if(stopped)break;
   {struct P*object=PloFindSwNearest__FP2LO3OIDii(g_sw,4,node->tag,current);
    if(out && out->node==node)NearestCrvS__FP3CRVG9VU_VECTORPvP6VECTORT3PfT5f(object,pos,0,&hit.q,0,0,&value,out->value);
    else NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(object,pos,0,&hit.q,0,0,&value);
    {float d=Length(Sub(pos,hit.q));if(d<best){best=d;choice.node=node;choice.value=value;choice.object=current;}}
   }
   break;
  case 0:{int kind=5;if(current)kind=4;current=PloFindSwNearest__FP2LO3OIDii(g_sw,kind,node->tag,current);break;}
  case 1:case 2:case 4:case 5:case 8:case 9:case 10:break;
  }
 }
 if(out)*out=choice;
}
