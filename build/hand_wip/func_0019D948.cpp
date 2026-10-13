/* WIP: 19/76 instructions differ; game-pointer copy and minus-one allocation remain. */
struct FRAME;
extern "C" FRAME*func_001AE478(FRAME*);
extern "C" void func_001AE4A0(FRAME*,int);
struct FRAME {int a;FRAME(){(void)func_001AE478(this);}~FRAME(){func_001AE4A0(this,2);}};
struct X {char pad0[0x5C];int x5C;char pad1[0x6C-0x60];int x6C;char pad2[0x7C-0x70];X*x7C;};
struct T {char pad[0xCC];int tags[2];};
struct P {int a,b;T*t;};
struct G {char pad[0x3B0C];X*x;};
extern "C" G D_003DD490;
extern "C" void func_00165C98(int*,X***);
extern "C" void func_002338C0(void*,int,int,int(*)(const void*,const void*));
extern "C" int func_00165C28(const void*,const void*);
extern "C" int func_00164030(X*);
extern "C" void func_0019D948(P*p){
 T*pt=p->t;
 if(!pt)return;
 pt->tags[0]=pt->tags[1]=-1;
 G*pg=&D_003DD490;
 if(!pg->x || pg->x->x6C==-1)return;
 p->t->tags[0]=pg->x->x6C;
 int n=1,i=0;
 register G*pgLoop __asm__("$20")=pg;
 FRAME fr;
 int c;
 X**ap;
 func_00165C98(&c,&ap);
 func_002338C0(ap,c,4,func_00165C28);
 for(;i<c;i++){
  X*x=ap[i];
  if(pgLoop->x==x->x7C && x->x5C!=-1 && !func_00164030(x)){
   p->t->tags[n++]=x->x5C;
   break;
  }
 }
}
