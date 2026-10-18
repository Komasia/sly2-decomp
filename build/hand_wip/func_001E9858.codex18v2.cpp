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
struct AL {int cb,align;};
union PHASE {AL request;U hit;};
struct WORK {PHASE phase;U direction;M3 basis,temporary,inverse;float distance;U axis;int nextEntry;U world;};
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
static inline qword Point(M4*m,qword v){register qword r __asm__("vf3")=m->a;__asm__("vmulax.xyz $ACC,%0,%4x\n\tvmadday.xyz $ACC,%1,%4y\n\tvmaddaz.xyz $ACC,%2,%4z\n\tvmaddw.xyz %0,%3,$vf0w":"+j"(r):"j"(m->b),"j"(m->c),"j"(m->d),"j"(v));return r;}
static inline qword Transform(const M3&m,qword v){__asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z":"+j"(v):"j"(m.a.q),"j"(m.b.q),"j"(m.c.q));return v;}
static inline qword PointDifference(const U&world,const U&hit){
 register qword value __asm__("vf3")=world.q,point __asm__("vf1")=hit.q;
 __asm__("vsub.xyzw %0,%0,%1":"+j"(value):"j"(point));
 return value;
}
static inline void TransposeInto(M3&r,const M3&m){
 register qword lo __asm__("$5"),hi __asm__("$4"),lo1 __asm__("$3"),hi1 __asm__("$2");
 register qword a __asm__("$9"),b __asm__("$10"),d __asm__("$11");
 __asm__("pextlw %0,%8,%7\n\tpextuw %1,%8,%7\n\tpextlw %2,$zero,%9\n\tpextuw %3,$zero,%9\n\tpcpyld %4,%2,%0\n\tpcpyud %5,%0,%2\n\tpcpyld %6,%3,%1"
 :"=&r"(lo),"=&r"(hi),"=&r"(lo1),"=&r"(hi1),"=r"(a),"=r"(b),"=r"(d):"r"(m.a.q),"r"(m.b.q),"r"(m.c.q));
 r.a.q=a;r.b.q=b;r.c.q=d;
}
static inline qword ReadAxis(const M3*matrix){register qword value __asm__("$2");__asm__("lq %0,%1":"=r"(value):"m"(matrix->c.q));return value;}
static inline NODE*PublishAxisAndHead(WORK&w,qword axis,const S*p){register NODE*head __asm__("$20");__asm__("sq %2,%0\n\tlw %1,%3":"=m"(w.axis.q),"=r"(head):"r"(axis),"m"(p->head));return head;}
static inline E*ReadEntries(const NODE*node){register E*r __asm__("$3");__asm__("lw %0,%1":"=r"(r):"m"(node->entries));return r;}
void func_001E9858(S*p){
 U vertices[128];WORK w;
 func_001F36A8(p);
 if(!p->path||!p->head)return;
 NODE*head=PublishAxisAndHead(w,ReadAxis(func_001A6318(p)),p);
 for(NODE*node=head;node;node=node->next){
  int index=node->mesh-p->config.meshes;
  STATE*state=&p->config.states[index];OWNER*object=state->object;
  state->object=(OWNER*)&D_002C44F0;
  int j=0;func_0016EF00(&p->config,index);
  if(j<node->n){
   register PHASE*phase __asm__("$23");__asm__("la %0,%a1":"=r"(phase):"p"(&w.phase));
   do{
   E*e=&ReadEntries(node)[j];w.nextEntry=++j;int k=0;
   func_001AE5A0(vertices,e->vertices,e->n*16);
   w.phase.request.cb=e->n*16;phase->request.align=16;
   U*out=(U*)func_001AE1D0(&phase->request);e->samples=out;
   for(k=0;k<e->n;k++){
    w.world.q=Point(&object->mat,vertices[k].q);
    func_001E6F60(p->path,w.world.q,0,&phase->hit.q,&w.direction.q,&w.distance,0);
    func_0011B830(&w.temporary,w.direction.q,w.axis.q);
    qword difference=PointDifference(w.world,phase->hit);
    w.basis=w.temporary;
    TransposeInto(w.temporary,w.basis);
    w.inverse=w.temporary;
    out->q=Transform(w.inverse,difference);out->f[3]=w.distance;out++;
   }
   j=w.nextEntry;
   }while(j<node->n);
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

typedef char actual_mesh_work_0[(sizeof(PHASE)==16)?1:-1];
typedef char actual_mesh_work_1[(sizeof(WORK)==0xF0)?1:-1];
typedef char actual_mesh_work_2[(OFF(WORK,phase)==0)?1:-1];
typedef char actual_mesh_work_3[(OFF(WORK,direction)==0x10)?1:-1];
typedef char actual_mesh_work_4[(OFF(WORK,basis)==0x20)?1:-1];
typedef char actual_mesh_work_5[(OFF(WORK,temporary)==0x50)?1:-1];
typedef char actual_mesh_work_6[(OFF(WORK,inverse)==0x80)?1:-1];
typedef char actual_mesh_work_7[(OFF(WORK,distance)==0xB0)?1:-1];
typedef char actual_mesh_work_8[(OFF(WORK,axis)==0xC0)?1:-1];
typedef char actual_mesh_work_9[(OFF(WORK,nextEntry)==0xD0)?1:-1];
typedef char actual_mesh_work_10[(OFF(WORK,world)==0xE0)?1:-1];
