/* (Claude agent, 2026-10-17) frame pointer copy pf used only for the push call reproduces the a0->s5 copy. */
struct REF{int tag;union{int n;float g;};};
struct G{char pad[0x3A18];char object[0x104];void*primary;int pad20[2];void*fallback;};
struct B{char data[0x5464];};
extern "C" {
 extern G g_sw;
 extern B D_002E6604[];
 extern char D_003D9ED0[],D_002A6EE0[],D_002A6EC8[];
 void*NProgress(REF*,void*,void*);
 void Decref(REF*) asm("Decref__4CRef");
 void*__10STACKSCOPE(void*);
 void _$_10STACKSCOPE(void*,int);
 void*func_001D89A8(void*,...);
 int func_001DDD40(int);
 void*func_0013E368(void*,int);
 int func_001D82B8(void*,void*);
 int fiprintf(char*,const char*,...) asm("fiprintf");
 char*s1_strcpy(char*,const char*) asm("s1_strcpy");
 int KindDataAccess(void*) asm("KindDataAccess__FP4MENU");
}
struct FRAME{FRAME()__asm__("__10STACKSCOPE");~FRAME(){_$_10STACKSCOPE(this,2);}};
static inline float GetG(REF&r,void*a,B*b){NProgress(&r,a,b);float g=r.g;Decref(&r);return g;}
static inline int GetN(REF&r,void*a,B*b){NProgress(&r,a,b);int n=r.n;Decref(&r);return n;}
extern "C" void func_001ADC40(char*buf,int idx){
 REF ref;
 G*pg=&g_sw;
 B*pb=&D_002E6604[idx];
 if(GetG(ref,pg->primary,pb)!=0.0f){
  int frame[4];int*pf=frame;__10STACKSCOPE(pf);
  void*value=func_001D89A8(D_002A6EE0,0);
  int tag;
  if(value)tag=GetN(ref,value,pb);else tag=GetN(ref,pg->fallback,pb);
  fiprintf(buf,D_002A6EC8,(char*)func_0013E368(&g_sw,func_001DDD40(tag)),func_001D82B8(g_sw.object,pb));
  _$_10STACKSCOPE(frame,2);
 }else{
  switch(KindDataAccess(D_003D9ED0)){
   case 0x1E:case 0x1F:s1_strcpy(buf,(char*)func_0013E368(pg,0x44));break;
   case 0x19:s1_strcpy(buf,(char*)func_0013E368(pg,0x45));break;
  }
 }
}
