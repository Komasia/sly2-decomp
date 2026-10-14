
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M3 {U a,b,c;};
struct M4 {qword a,b,c,d;};
struct E {int n;char pad4[8];U*vertices;char pad10[0x1C-0x10];U*samples;};
struct MESH {char pad[0x14];};
struct OWNER {char pad[0x40];M4 mat;};
struct STATE {int pad;OWNER*object;char pad8[0x28-8];};
struct NODE {MESH*mesh;int n;E*entries;NODE*next;};
struct CONFIG {void*owner;char pad4[0xC];U zero;float limit;char pad24[0x18];MESH*meshes;STATE*states;void*ae;};
struct S {char pad[0x80];CONFIG config;char padD0[0xDC-0xD0];NODE*head;char padE0[0x150-0xE0];void*path;};
struct AL {int cb,align;AL(int c,int a){cb=c;align=a;}};
extern char D_002C44F0;
extern "C" {
void func_001F36A8(S*);
M3*func_001A6318(S*);
void func_0016EF00(CONFIG*,int);
void func_001AE5A0(void*,const void*,unsigned);
void*func_001AE1D0(AL*);
void func_001E6F60(void*,qword,void*,qword*,qword*,float*,float*);
M3*func_0011B830(M3*,qword,qword);
void func_001E9858(S*);
}
static inline qword Point(M4*m,qword v){qword r=m->a;__asm__("vmulax.xyz $ACC,%0,%4x\n\tvmadday.xyz $ACC,%1,%4y\n\tvmaddaz.xyz $ACC,%2,%4z\n\tvmaddw.xyz %0,%3,$vf0w":"+j"(r):"j"(m->b),"j"(m->c),"j"(m->d),"j"(v));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Transform(const M3&m,qword v){__asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z":"+j"(v):"j"(m.a.q),"j"(m.b.q),"j"(m.c.q));return v;}
static inline qword PextL(qword a,qword b){qword r;__asm__("pextlw %0,%1,%2":"=r"(r):"r"(a),"r"(b));return r;}
static inline qword PextH(qword a,qword b){qword r;__asm__("pextuw %0,%1,%2":"=r"(r):"r"(a),"r"(b));return r;}
static inline qword CopyL(qword a,qword b){qword r;__asm__("pcpyld %0,%1,%2":"=r"(r):"r"(a),"r"(b));return r;}
static inline qword CopyH(qword a,qword b){qword r;__asm__("pcpyud %0,%1,%2":"=r"(r):"r"(a),"r"(b));return r;}
static inline qword PextL0(qword b){qword r;__asm__("pextlw %0,$zero,%1":"=r"(r):"r"(b));return r;}
static inline qword PextH0(qword b){qword r;__asm__("pextuw %0,$zero,%1":"=r"(r):"r"(b));return r;}
static inline M3 Transpose(const M3&m) return r{
 qword lo=PextL(m.b.q,m.a.q),hi=PextH(m.b.q,m.a.q);
 qword lo1=PextL0(m.c.q),hi1=PextH0(m.c.q);
 r.a.q=CopyL(lo1,lo);
 r.b.q=CopyH(lo,lo1);
 r.c.q=CopyL(hi1,hi);
}
void func_001E9858(S*p){
 U vertices[128];
 func_001F36A8(p);
 if(!p->path||!p->head)return;
 qword axis=func_001A6318(p)->c.q;
 NODE*node;
 for(node=p->head;node;node=node->next){
  int index=node->mesh-p->config.meshes;
  STATE*state=&p->config.states[index];
  OWNER*object=state->object;
  state->object=(OWNER*)&D_002C44F0;
  int j=0;
  func_0016EF00(&p->config,index);
  while(j<node->n){
   E*e=&node->entries[j++];
   int k=0;
   func_001AE5A0(vertices,e->vertices,e->n*16);
   U*out=(U*)func_001AE1D0(&AL(e->n*16,16));
   e->samples=out;
   for(k=0;k<e->n;k++){
    U pos,dir;
    M3 m;
    float distance;
    qword world;
    world=Point(&object->mat,vertices[k].q);
    func_001E6F60(p->path,world,0,&pos.q,&dir.q,&distance,0);
    M3 tmp;func_0011B830(&tmp,dir.q,axis);
    m=tmp;
    M3 transposed;transposed=Transpose(m);
    out->q=Transform(transposed,Sub(world,pos.q));
    out->f[3]=distance;
    out++;
   }
  }
 }
}

#define OFF(T,f) ((unsigned)&((T*)0)->f)
typedef char mesh_guard0[(sizeof(void*)==4)?1:-1];
typedef char mesh_guard1[(sizeof(int)==4)?1:-1];
typedef char mesh_guard2[(sizeof(float)==4)?1:-1];
typedef char mesh_guard3[(sizeof(qword)==16)?1:-1];
typedef char mesh_guard4[(sizeof(U)==16)?1:-1];
typedef char mesh_guard5[(sizeof(M3)==0x30)?1:-1];
typedef char mesh_guard6[(sizeof(M4)==0x40)?1:-1];
typedef char mesh_guard7[(sizeof(MESH)==20)?1:-1];
typedef char mesh_guard8[(sizeof(STATE)==40)?1:-1];
typedef char mesh_guard9[(sizeof(E)==0x20)?1:-1];
typedef char mesh_guard10[(sizeof(NODE)==16)?1:-1];
typedef char mesh_guard11[(sizeof(CONFIG)==0x50)?1:-1];
typedef char mesh_guard12[(sizeof(AL)==8)?1:-1];
typedef char mesh_guard13[(OFF(OWNER,mat)==0x40)?1:-1];
typedef char mesh_guard14[(OFF(STATE,object)==4)?1:-1];
typedef char mesh_guard15[(OFF(E,n)==0)?1:-1];
typedef char mesh_guard16[(OFF(E,vertices)==0xC)?1:-1];
typedef char mesh_guard17[(OFF(E,samples)==0x1C)?1:-1];
typedef char mesh_guard18[(OFF(NODE,mesh)==0)?1:-1];
typedef char mesh_guard19[(OFF(NODE,n)==4)?1:-1];
typedef char mesh_guard20[(OFF(NODE,entries)==8)?1:-1];
typedef char mesh_guard21[(OFF(NODE,next)==0xC)?1:-1];
typedef char mesh_guard22[(OFF(S,config)==0x80)?1:-1];
typedef char mesh_guard23[(OFF(S,config.meshes)==0xBC)?1:-1];
typedef char mesh_guard24[(OFF(S,config.states)==0xC0)?1:-1];
typedef char mesh_guard25[(OFF(S,head)==0xDC)?1:-1];
typedef char mesh_guard26[(OFF(S,path)==0x150)?1:-1];
typedef char mesh_guard27[(OFF(CONFIG,owner)==0)?1:-1];
typedef char mesh_guard28[(OFF(CONFIG,zero)==0x10)?1:-1];
typedef char mesh_guard29[(OFF(CONFIG,limit)==0x20)?1:-1];
typedef char mesh_guard30[(OFF(CONFIG,meshes)==0x3C)?1:-1];
typedef char mesh_guard31[(OFF(CONFIG,states)==0x40)?1:-1];
typedef char mesh_guard32[(OFF(CONFIG,ae)==0x44)?1:-1];
typedef char mesh_guard33[(OFF(AL,cb)==0)?1:-1];
typedef char mesh_guard34[(OFF(AL,align)==4)?1:-1];
