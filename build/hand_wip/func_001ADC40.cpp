/* WIP 92/107: game-state caching, temporary/branch scheduling. */
struct REF{int tag;union{int n;float g;};};
struct G{char pad[0x3A18];char object[0x104];void*primary;int pad20[2];void*fallback;};
struct B{char data[0x5464];};
extern "C" {
 extern G D_003DD490;
 extern B D_002E6604[];
 extern char D_003D9ED0[],D_002A6EE0[],D_002A6EC8[];
 void*func_002581C0(REF*,void*,void*);
 void func_00129EC8(REF*);
 void*func_001AE478(void*);
 void func_001AE4A0(void*,int);
 void*func_001D89A8(void*,...);
 int func_001DDD40(int);
 void*func_0013E368(void*,int);
 int func_001D82B8(void*,void*);
 int func_0021ECD8(char*,const char*,...);
 char*func_0021ED58(char*,const char*);
 int func_001B0078(void*);
}
struct FRAME{FRAME()__asm__("func_001AE478");~FRAME(){func_001AE4A0(this,2);}};
extern "C" void func_001ADC40(char*buf,int idx){
 REF ref;
 G*pg=&D_003DD490;
 B*pb=&D_002E6604[idx];
 func_002581C0(&ref,pg->primary,pb);
 float g=ref.g;
 func_00129EC8(&ref);
 if(g!=0.0f){
  FRAME frame;
  void*value=func_001D89A8(D_002A6EE0,0);
  func_002581C0(&ref,value?value:pg->fallback,pb);
  int tag=ref.n;
  func_00129EC8(&ref);
  char*label=(char*)func_0013E368(&D_003DD490,func_001DDD40(tag));
  func_0021ECD8(buf,D_002A6EC8,label,func_001D82B8(D_003DD490.object,pb));
 }else{
  switch(func_001B0078(D_003D9ED0)){
   case 0x1E:case 0x1F:func_0021ED58(buf,(char*)func_0013E368(&D_003DD490,0x44));break;
   case 0x19:func_0021ED58(buf,(char*)func_0013E368(&D_003DD490,0x45));break;
  }
 }
}
