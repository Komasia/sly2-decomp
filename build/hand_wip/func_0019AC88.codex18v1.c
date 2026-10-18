typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct X { char pad[0x80]; qword v80; };
struct O { char pad[0xE8]; struct X *xE8; char pad2[0x1F30-0xEC]; float f1F30; };
struct A { struct O *p; };
struct P { struct A *a; void *p4; int pad[2]; qword v10; };
qword func_001A62E8(void *p);
struct TRIREF{int triangle;float s,t;};
int func_00185D18(void *a, qword p, qword v, qword x, float f, float t, struct TRIREF *r0, qword *r1, qword *r2);
void func_00117120(float tMax, float t, float s, qword a, qword va, qword b, qword vb, qword *position, qword *velocity, qword *acceleration);
static inline float Len(qword v) {
 qword l, one; float r;
 __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(l), "=&j"(one) : "0"(v));
 __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "=j"(l) : "0"(l));
 __asm__("qmfc2.ni %0,%1" : "=r"(r) : "j"(l));
 return r;
}
float func_0019AC88(struct P *p, float t)
{
 struct TRIREF a;U b,c,d,e;
 qword pos,vel;
 struct O *o;
 void *pv;
 float g;
 pv=p->p4;
 o=p->a->p;
 pos=func_001A62E8(o);
 vel=p->v10;
 {
 register qword pp __asm__("$5");
 register qword vv __asm__("$6");
 __asm__("por %0,$zero,%2\n\tpor %1,$zero,%3":"=&r"(pp),"=&r"(vv):"r"(pos),"r"(vel));
 func_00185D18(pv, pp, vv, o->xE8->v80, o->f1F30, t, &a, &b.q, &c.q);
 }
 func_00117120(t,0.0f,1.0f,pos,vel,b.q,c.q,0,0,&d.q);
 g=Len(d.q);
 func_00117120(t,t,1.0f,pos,vel,b.q,c.q,0,0,&e.q);
 g += Len(e.q);
 t *= 0.5f;
 g *= t;
 return g<1000000.0f?g:1000000.0f;
}

typedef char qword_Size[(sizeof(qword)==16)?1:-1];
typedef char Unsigned_Size[(sizeof(unsigned)==4)?1:-1];
typedef char Pointer_Size[(sizeof(void*)==4)?1:-1];
typedef char Float_Size[(sizeof(float)==4)?1:-1];
typedef char Int_Size[(sizeof(int)==4)?1:-1];
typedef char U_Size[(sizeof(U)==16)?1:-1];
typedef char U_Align[(__alignof__(U)==16)?1:-1];
typedef char TRIREF_Size[(sizeof(struct TRIREF)==12)?1:-1];
typedef char TRIREF_Align[(__alignof__(struct TRIREF)==4)?1:-1];
typedef char TRIREF_triangle_Offset[((unsigned)&((struct TRIREF*)0)->triangle==0)?1:-1];
typedef char TRIREF_s_Offset[((unsigned)&((struct TRIREF*)0)->s==4)?1:-1];
typedef char TRIREF_t_Offset[((unsigned)&((struct TRIREF*)0)->t==8)?1:-1];
typedef char X_Prefix_Size[(sizeof(struct X)==0x90)?1:-1];
typedef char X_response_Offset[((unsigned)&((struct X*)0)->v80==0x80)?1:-1];
typedef char O_Prefix_Size[(sizeof(struct O)==0x1f34)?1:-1];
typedef char O_physics_Offset[((unsigned)&((struct O*)0)->xE8==0xe8)?1:-1];
typedef char O_radius_Offset[((unsigned)&((struct O*)0)->f1F30==0x1f30)?1:-1];
typedef char A_Prefix_Size[(sizeof(struct A)==4)?1:-1];
typedef char A_actor_Offset[((unsigned)&((struct A*)0)->p==0)?1:-1];
typedef char P_Prefix_Size[(sizeof(struct P)==0x20)?1:-1];
typedef char P_Align[(__alignof__(struct P)==16)?1:-1];
typedef char P_state_Offset[((unsigned)&((struct P*)0)->a==0)?1:-1];
typedef char P_mesh_Offset[((unsigned)&((struct P*)0)->p4==4)?1:-1];
typedef char P_velocity_Offset[((unsigned)&((struct P*)0)->v10==0x10)?1:-1];
