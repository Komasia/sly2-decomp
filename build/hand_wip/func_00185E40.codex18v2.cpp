typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];int i[4];};
struct M3{U r[3];M3(){}M3(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];}M3&operator=(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];return*this;}};
inline void*operator new(unsigned,void*p){return p;}
struct M4{U r[4];};
struct VTE{short delta,pad;void*fn;};
struct PARAMS{float a,b,duration;};
struct CONTROL{char pad0[0x10];float y,z;int pad18;float speed;};
struct REQUEST{char pad0[0x78];float multiplier;};
struct AXIS{float weight;int active;char pad8[8];U direction;};
struct TRIREF{int index;float u,v;};
struct LIST{int count;qword planes[8];};
struct P{char pad0[0xC];VTE*vt;char pad10[0x140];CONTROL*control;char pad154[0x3C];U acceleration;char pad1A0[0x10];M3 basis;char pad1E0[0x1C30];AXIS axes[8];REQUEST*request;int pad1F14;void*mesh;TRIREF triangle;U points[3];};
struct CLOCK{float time,dt;};
struct ROWS{U r[3];};
union PHASE{ROWS facing;struct{U angular,linear,movement,scalar;}u;};
struct WORK{U closest,normal;M4 frame;U closestSamples[3];PHASE phase;LIST planes;U samples[3];M3 matrix,inverse,product;U position,target,negative;qword*samplePointer;U projected;};
extern "C"{
extern U D_002A2DC0;extern M3 D_002DDFA0;extern CLOCK D_002DDED0;extern PARAMS D_002BE920,D_002BE930,D_002BE940;
qword func_001A62E8(P*);M4*func_001A6318(P*);
void func_00185310(void*,qword,TRIREF*,TRIREF*,qword*,qword*);
M3 func_0011B830(qword,qword);M3 func_0011B340(M3*);qword*func_00256D18(qword*,qword);
void func_0011C950(M4*,M3*,PARAMS*,M3*,qword*,float);
qword func_0011F088(qword,qword,PARAMS*,qword*,float);
void func_001856B8(void*,LIST*);void func_001856C0(void*,LIST*,int,qword*,PARAMS*,float);
qword func_00185A80(void*,LIST*,qword);
void func_0018C250(P*,int,int);void func_001A0450(P*,AXIS*,REQUEST*);
}
static inline qword Scale(qword a,qword k){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(k));return r;}
static inline qword Divide(qword a,qword length){qword r;__asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=j"(r):"j"(a),"j"(length));return r;}
static inline void Set(P*p,int slot,qword q){VTE*e=&p->vt[slot];((void(*)(void*,qword))e->fn)((char*)p+e->delta,q);}
extern "C" void func_00185E40(P*argument){
 register P*p __asm__("$17");
 __asm__("daddu %0,%1,$zero":"=r"(p):"r"(argument));
 WORK w;
 {
  register qword returned __asm__("$2")=func_001A62E8(argument);
  register TRIREF*input __asm__("$6"),*output __asm__("$7");
  __asm__("sq %3,%0\n\taddiu %1,%4,0x1f1c\n\tdaddu %2,%1,$zero":"=m"(w.position.q),"=r"(input),"=r"(output):"r"(returned),"r"(p));
  func_00185310(p->mesh,returned,input,output,&w.closest.q,&w.normal.q);
 }
 register qword difference __asm__("vf3"),length __asm__("vf4"),direction __asm__("vf2"),fallback __asm__("vf1"),minusOne __asm__("vf2");
 register float distance __asm__("$f1"),epsilon __asm__("$f2");
 __asm__("lqc2 $vf1,%6\n\tlqc2 $vf2,%7\n\tvsub.xyzw %0,$vf1,$vf2\n\t.set noat\n\tlui $1,0xbf80\n\tmtc1 $1,$f0\n\t.set at\n\tvmul.xyz $vf1,%0,%0\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,$vf2,$vf1z\n\t.set noat\n\tlui $1,0x38d1\n\tori $1,$1,0xb717\n\tmtc1 $1,%3\n\t.set at\n\tvsqrt Q,$vf1x\n\tvwaitq\n\tvaddq.x %1,$vf0,Q\n\tmfc1 $2,$f0\n\tqmfc2.ni $3,%1\n\tqmtc2.ni $2,%5\n\tmtc1 $3,%2\n\tlqc2 %4,%8"
  :"=j"(difference),"=j"(length),"=f"(distance),"=f"(epsilon),"=j"(fallback),"=j"(minusOne):"m"(w.closest.q),"m"(w.position.q),"m"(w.normal.q):"$1","$2","$3","$f0");
 fallback=Scale(fallback,minusOne);
 w.phase.u.angular.q=minusOne;
 if(distance<epsilon)direction=fallback;else direction=Divide(difference,length);
 register TRIREF*triangle __asm__("$22");register M3*basis __asm__("$21");register U*points __asm__("$18");register int remaining __asm__("$20");
 {
  register float x __asm__("$f0");register qword origin __asm__("vf1"),upArgument __asm__("$6"),directionArgument __asm__("$5");
  register long scalarWord __asm__("$4");register qword scalar __asm__("vf3");register M3*result __asm__("$4");
  __asm__("lwc1 %0,%4\n\tlui $2,%%hi(%6)\n\taddiu $2,$2,%%lo(%6)\n\tlqc2 %1,%5\n\tneg.s %0,%0\n\tlq %2,0($2)\n\tqmfc2.ni %3,%7"
   :"=f"(x),"=j"(origin),"=r"(upArgument),"=r"(directionArgument):"m"(p->points[0].f[0]),"m"(w.closest.q),"i"(&D_002A2DC0),"j"(direction):"$2","memory");
  __asm__("addiu %0,%5,0x1f1c\n\taddiu %1,%5,0x1b0\n\taddiu %2,%5,0x1f30\n\tmfc1 %3,%6\n\tli %4,2":"=r"(triangle),"=r"(basis),"=r"(points),"=r"(scalarWord),"=r"(remaining):"r"(p),"f"(x));
  __asm__("qmtc2.ni %3,%0\n\tvadda.xyzw ACC,%4,$vf0\n\tvmaddx.xyzw $vf4,%5,%0x\n\taddiu %1,%6,0xa0\n\tsqc2 $vf4,%2"
   :"=j"(scalar),"=r"(result),"=m"(w.target.q):"r"(scalarWord),"j"(origin),"j"(direction),"p"(&w):"vf4");
  w.phase.u.angular.q=scalar;
  new(result)M3(func_0011B830(directionArgument,upArgument));
 }
 register U*angular __asm__("$23");register LIST*planes __asm__("$30");
 {
  register M4*frame __asm__("$16");
  __asm__("addiu %0,%1,0x20":"=r"(frame):"p"(&w));
  (void)func_00256D18(&w.frame.r[3].q,w.target.q);
  register U*out __asm__("$19");register float one __asm__("$f0");
  __asm__("addiu $2,%4,0x160\n\tlq $3,0xb0(%4)\n\tsw $2,0x250(%4)\n\taddiu %0,%4,0x90\n\tlq $2,0xa0(%4)\n\taddiu %1,%4,0xd0\n\t.set noat\n\tlui $1,0x3f80\n\tmtc1 $1,%3\n\t.set at\n\taddiu %2,%4,0x60\n\tsq $2,0x20(%4)\n\tsq $3,0x10(%5)\n\tlq $2,0xc0(%4)\n\tsq $2,0x20(%5)"
   :"=r"(angular),"=r"(planes),"=r"(out),"=f"(one):"p"(&w),"r"(frame):"$1","$2","$3","memory");
  __asm__ __volatile__("sw $zero,%0\n\tsw $zero,%1\n\tsw $zero,%2\n\tswc1 %4,%3":"=m"(w.frame.r[2].i[3]),"=m"(w.frame.r[1].i[3]),"=m"(w.frame.r[0].i[3]),"=m"(frame->r[3].f[3]):"f"(one));
  do{
   register qword point __asm__("vf5"),row0 __asm__("vf4"),row1 __asm__("vf3"),row2 __asm__("vf2"),row3 __asm__("vf1");
   register qword*sampleOutput __asm__("$8"),*nullOutput __asm__("$9");register TRIREF*triangleArgument __asm__("$6"),*nullTriangle __asm__("$7");
   point=points->q;
   __asm__("daddu %0,%6,$zero\n\tlqc2 %1,%4\n\tdaddu %2,%7,$zero\n\tlqc2 %3,%5":"=r"(sampleOutput),"=j"(row0),"=r"(triangleArgument),"=j"(row1):"m"(w.frame.r[0].q),"m"(w.frame.r[1].q),"r"(out),"r"(triangle));
   __asm__("daddu %0,$zero,$zero\n\tlqc2 %1,%5\n\tdaddu %2,$zero,$zero\n\tlqc2 %3,%6\n\taddiu %4,%4,0x10":"=r"(nullTriangle),"=j"(row2),"=r"(nullOutput),"=j"(row3),"+r"(out):"m"(w.frame.r[2].q),"m"(w.frame.r[3].q));
   /* Each query consumes the real current VF6.W after the preceding callback. */
   register qword world __asm__("vf6");register void*mesh __asm__("$4");
   __asm__ volatile("vmulax.xyz ACC,%2,%6x\n\tvmadday.xyz ACC,%3,%6y\n\tvmaddaz.xyz ACC,%4,%6z\n\tvmaddw.xyz %0,%5,$vf0w\n\tlw %1,%7":"=&j"(world),"=r"(mesh):"j"(row0),"j"(row1),"j"(row2),"j"(row3),"j"(point),"m"(p->mesh));
   points++;--remaining;
   func_00185310(mesh,world,triangleArgument,nullTriangle,sampleOutput,nullOutput);
  }while(remaining>=0);
 }
 register CLOCK*clock __asm__("$16");register float halfZero __asm__("$f20");
 {
  register qword upArgument __asm__("$6"),surfaceArgument __asm__("$5");register M3*result __asm__("$4");
  register qword difference __asm__("vf1");
  __asm__("lqc2 $vf3,%3\n\tlui $3,%%hi(%6)\n\tlqc2 %0,%4\n\taddiu $2,$3,%%lo(%6)\n\tlqc2 $vf2,%5\n\tvsub.xyzw %0,%0,$vf3\n\tvsub.xyzw $vf2,$vf2,$vf3\n\tlq %1,0($2)\n\tvopmula.xyz ACC,%0,$vf2\n\tvopmsub.xyz %0,$vf2,%0\n\tdaddu %2,%7,$zero"
   :"=j"(difference),"=r"(upArgument),"=r"(result):"m"(w.closestSamples[0].q),"m"(w.closestSamples[2].q),"m"(w.closestSamples[1].q),"i"(&D_002A2DC0),"r"(angular):"$2","$3","vf2","vf3","memory");
  __asm__("vmul.xyz $vf2,%3,%3\n\tvaddw.x $vf3,$vf0,$vf0w\n\tvadday.x ACC,$vf2,$vf2y\n\tvmaddz.x $vf2,$vf3,$vf2z\n\tlui %0,%%hi(%4)\n\tvsqrt Q,$vf2x\n\tvwaitq\n\tvaddq.x $vf2,$vf0,Q\n\taddiu %0,%0,%%lo(%4)\n\tvdiv Q,$vf0w,$vf2x\n\tvwaitq\n\tvmulq.xyzw $vf3,%3,Q\n\t.set noat\n\tlui $1,0x3f00\n\tmtc1 $1,%1\n\t.set at\n\tqmfc2.ni %2,$vf3"
   :"=r"(clock),"=f"(halfZero),"=r"(surfaceArgument):"j"(difference),"i"(&D_002DDED0):"$1","vf2","vf3");
  new(result)M3(func_0011B830(surfaceArgument,upArgument));
  remaining=2;
 }
 {
  register qword middle __asm__("$2");register P*receiver __asm__("$4");
  __asm__("lq $5,%4\n\tdaddu %1,%7,$zero\n\tlq $3,%5\n\tlq %0,%6\n\tsq $3,%2\n\tsq $5,%3":"=r"(middle),"=r"(receiver),"=m"(p->basis.r[2].q),"=m"(p->basis.r[0].q):"m"(w.phase.facing.r[0].q),"m"(w.phase.facing.r[2].q),"m"(w.phase.facing.r[1].q),"r"(p):"$3","$5");
  p->basis.r[1].q=middle;
  M4*current=func_001A6318(receiver);
  func_0011C950(current,basis,&D_002BE920,0,&angular->q,clock->dt*halfZero);
 }
 {
  register qword argument __asm__("$5");register int adjustment __asm__("$4");register void(*writer)(void*,qword) __asm__("$3");
  __asm__("lw $2,%3\n\tlq %0,%4\n\tlh %1,0x120($2)\n\tlw %2,0x124($2)":"=r"(argument),"=r"(adjustment),"=r"(writer):"m"(p->vt),"m"(w.phase.u.angular.q):"$2","memory");
  writer((char*)p+adjustment,argument);
 }
 (void)func_0011F088(w.position.q,w.target.q,&D_002BE930,&w.phase.u.linear.q,clock->dt*halfZero);
 {
  register qword target __asm__("vf5"),row0 __asm__("vf4");
  register M3*matrix __asm__("$4");register U*point __asm__("$3"),*out __asm__("$2");
  __asm__("lqc2 %0,%5\n\tdaddu %1,%6,$zero\n\tlqc2 %2,0x1b0(%7)\n\taddiu %3,%7,0x1f30\n\taddiu %4,%8,0x160"
   :"=j"(target),"=r"(matrix),"=j"(row0),"=r"(point),"=r"(out):"m"(w.target.q),"r"(basis),"r"(p),"p"(&w):"memory");
  do{
   register qword transformed __asm__("vf1");
   __asm__("lqc2 %0,%6\n\taddiu %1,%1,-1\n\tlqc2 $vf3,0x10(%7)\n\taddiu %2,%2,0x10\n\tlqc2 $vf2,0x20(%7)\n\tvmulax.xyz ACC,%5,%0x\n\tvmadday.xyz ACC,$vf3,%0y\n\tvmaddz.xyz %0,$vf2,%0z\n\tvadd.xyzw %0,%4,%0\n\tsqc2 %0,%3"
    :"=j"(transformed),"+r"(remaining),"+r"(point),"=m"(out->q):"j"(target),"j"(row0),"m"(point->q),"r"(matrix):"vf2","vf3","memory");
   out++;
  }while(remaining>=0);
 }
 halfZero=0.0f;
 func_001856B8(p->mesh,planes);
 func_001856C0(p->mesh,planes,3,w.samplePointer,&D_002BE940,10.0f);
 register CONTROL*movementControl __asm__("$2")=p->control;
 register M3*inverseResult __asm__("$4")=&w.inverse;
 if(halfZero<movementControl->speed){
  register float y __asm__("$f0");register M3*inverseInput __asm__("$5");
  __asm__("lwc1 %0,0x10(%4)\n\tlwc1 $f1,0x14(%4)\n\tdaddu %1,%5,$zero\n\tneg.s %0,%0\n\tswc1 %6,%2\n\tswc1 $f1,%3":"=f"(y),"=r"(inverseInput),"=m"(w.phase.u.movement.f[0]),"=m"(w.phase.u.movement.f[2]):"r"(movementControl),"r"(basis),"f"(halfZero):"$f1","memory");
  w.phase.u.movement.f[1]=y;
  new(inverseResult) M3(func_0011B340(inverseInput));
  register qword inverse0 __asm__("vf5"),inverse1 __asm__("vf3"),inverse2 __asm__("vf2");
  register qword product0 __asm__("vf6"),product2 __asm__("vf7"),camera1 __asm__("vf4");
  register U*up __asm__("$3");
  register qword movement __asm__("vf1");
  __asm__("lui $2,%%hi(%8)\n\tlqc2 %1,0x1d0(%7)\n\taddiu $2,$2,%%lo(%8)\n\tlqc2 %2,0x1e0(%7)\n\tlqc2 %4,0x20($2)\n\tlui $4,%%hi(%9)\n\tlqc2 %3,0($2)\n\taddiu %6,$4,%%lo(%9)\n\tlqc2 %0,0x1c0(%7)\n\tlqc2 %5,0x10($2)"
   :"=j"(inverse0),"=j"(inverse1),"=j"(inverse2),"=j"(product0),"=j"(product2),"=j"(camera1),"=r"(up):"p"(&w),"i"(&D_002DDFA0),"i"(&D_002A2DC0):"$2","$4","memory");
  __asm__("vmulax.xyz ACC,%2,%1x\n\tvmadday.xyz ACC,%3,%1y\n\tvmaddz.xyz %1,%4,%1z\n\tvmulax.xyz ACC,%2,%0x\n\tvmadday.xyz ACC,%3,%0y\n\tvmaddz.xyz %0,%4,%0z"
   :"+j"(product0),"+j"(product2):"j"(inverse0),"j"(inverse1),"j"(inverse2));
  __asm__("lqc2 %1,%5\n\tvmulax.xyz ACC,%0,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z"
   :"+j"(inverse0),"=j"(movement):"j"(inverse1),"j"(inverse2),"j"(camera1),"m"(w.phase.u.movement.q));
  __asm__("sqc2 %4,%0\n\tvmulax.xyz ACC,%4,%3x\n\tvmadday.xyz ACC,%5,%3y\n\tvmaddz.xyz %3,%6,%3z\n\tsqc2 %5,%1\n\tsqc2 %3,%2"
   :"=m"(w.matrix.r[0].q),"=m"(w.matrix.r[1].q),"=m"(w.phase.u.movement.q),"+j"(movement):"j"(product0),"j"(inverse0),"j"(product2));
  w.phase.u.movement.f[0]=0.0f;
  __asm__ __volatile__("sqc2 %1,%0":"=m"(w.matrix.r[2].q):"j"(product2));
  register qword raw __asm__("vf3"),length __asm__("vf1"),unit __asm__("vf1"),speed __asm__("vf2");
  register float lengthValue __asm__("$f0"),epsilonValue __asm__("$f1");register CONTROL*control __asm__("$2");register qword fallback __asm__("$2");
  __asm__("lqc2 %0,%5\n\tvmul.xyz %1,%0,%0\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x ACC,%1,%1y\n\tvmaddz.x %1,$vf2,%1z\n\t.set noat\n\tlui $1,0x38d1\n\tori $1,$1,0xb717\n\tmtc1 $1,%3\n\t.set at\n\tvsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %1,$vf0,Q\n\tqmfc2.ni $2,%1\n\tmtc1 $2,%2\n\tlw %4,%6"
   :"=j"(raw),"=j"(length),"=f"(lengthValue),"=f"(epsilonValue),"=r"(control):"m"(w.phase.u.movement.q),"m"(p->control):"$1");
  __asm__("lw $2,0x1c(%5)\n\tqmtc2.ni $2,%0\n\tlq %1,0(%6)\n\tsqc2 %7,%2\n\tsqc2 %8,%3\n\tsqc2 %9,%4"
   :"=j"(speed),"=r"(fallback),"=m"(w.product.r[0].q),"=m"(w.product.r[1].q),"=m"(w.product.r[2].q):"r"(control),"r"(up),"j"(product0),"j"(inverse0),"j"(product2):"memory");
  w.phase.u.scalar.q=speed;
  if(lengthValue<epsilonValue)unit=fallback;else unit=Divide(raw,length);
  unit=Scale(unit,speed);
  {
   register qword axis1 __asm__("vf2"),axis2 __asm__("vf1"),y __asm__("vf3"),z __asm__("vf4");register REQUEST*request __asm__("$2");
   __asm__("lqc2 %0,%6\n\tsqc2 %5,%4\n\tlqc2 %1,%7\n\tlw $3,%8\n\tlw $4,%9\n\tqmtc2.ni $3,%2\n\tqmtc2.ni $4,%3"
    :"=j"(axis1),"=j"(axis2),"=j"(y),"=j"(z),"=m"(w.phase.u.movement.q):"j"(unit),"m"(p->axes[1].direction.q),"m"(p->axes[2].direction.q),"m"(w.phase.u.movement.i[1]),"m"(w.phase.u.movement.i[2]):"$3","$4");
   __asm__("lw %0,%5\n\tvmulax.xyzw ACC,%1,%3x\n\tvmaddx.xyzw %1,%4,%6x\n\tsqc2 %1,%2":"=r"(request),"+j"(axis1),"=m"(p->acceleration.q):"j"(y),"j"(axis2),"m"(p->request),"j"(z));
   register qword multiplier __asm__("vf1");
   __asm__("lw $2,0x78(%4)\n\tqmtc2.ni $2,%0\n\tsqc2 %5,%1\n\tsqc2 %6,%1\n\tvmulx.xyzw %2,%2,%0x\n\tsqc2 %2,%3"
    :"=j"(multiplier),"=m"(w.phase.u.scalar.q),"+j"(axis1),"=m"(p->acceleration.q):"r"(request),"j"(y),"j"(z):"$2","memory");
   w.phase.u.scalar.q=multiplier;
  }
 }else{
  register U*output __asm__("$2");__asm__("addiu %0,%1,0x190":"=r"(output):"r"(p));
  output->f[1]=halfZero;output->f[2]=halfZero;p->acceleration.f[0]=halfZero;
 }
 register int planeCount __asm__("$2")=w.planes.count;
 if(planeCount>0){
  /* MFC1 preserves the inherited upper half of the actual V0 carrier. */
  register qword negativeWord __asm__("$2");
  /* The native world XYZ transform retains the current architectural VF5.W. */
  register qword world __asm__("vf5");
  register LIST*solverPlanes __asm__("$5");register void*mesh __asm__("$4");register qword argument __asm__("$6");
  __asm__ volatile(".set noat\n\tlui $1,0xbf80\n\tmtc1 $1,$f0\n\t.set at\n\tdaddu %1,%5,$zero\n\tmfc1 %0,$f0\n\tsq %0,%2\n\tqmtc2.ni %0,$vf2\n\tlqc2 $vf1,0x190(%6)\n\tvmulx.xyzw $vf1,$vf1,$vf2x\n\tlqc2 $vf4,0x1b0(%6)\n\tlqc2 $vf3,0x10(%7)\n\tlqc2 $vf2,0x20(%7)\n\tvmulax.xyz ACC,$vf4,$vf1x\n\tvmadday.xyz ACC,$vf3,$vf1y\n\tvmaddz.xyz %3,$vf2,$vf1z\n\tlw %4,0x1f18(%6)"
   :"=r"(negativeWord),"=r"(solverPlanes),"=m"(w.negative.q),"=&j"(world),"=r"(mesh):"r"(planes),"r"(p),"r"(basis):"$1","$f0","vf1","vf2","vf3","vf4","memory");
  __asm__("qmfc2.ni %0,%1":"=r"(argument):"j"(world));
  w.phase.u.movement.q=negativeWord;
  register qword returned __asm__("$2")=func_00185A80(mesh,solverPlanes,argument);
  register M3*result __asm__("$4");
  __asm__("qmtc2.ni %2,$vf2\n\taddiu %0,%3,0x190\n\tsqc2 $vf2,%1":"=r"(result),"=m"(w.projected.q):"r"(returned),"p"(&w):"vf2");
  new(result)M3(func_0011B340(basis));
  __asm__("lqc2 $vf6,0x240(%2)\n\tlqc2 $vf2,0x260(%2)\n\tlqc2 $vf4,0x190(%2)\n\tvmulx.xyzw $vf2,$vf2,$vf6x\n\tlqc2 $vf3,0x1a0(%2)\n\tlqc2 $vf1,0x1b0(%2)\n\tqmfc2.ni $2,$vf6\n\tvmulax.xyz ACC,$vf4,$vf2x\n\tvmadday.xyz ACC,$vf3,$vf2y\n\tvmaddz.xyz $vf2,$vf1,$vf2z\n\tsq $2,%0\n\tsqc2 $vf2,%1":"=m"(w.phase.u.movement.q),"=m"(p->acceleration.q):"p"(&w):"$2","vf1","vf2","vf3","vf4","vf6","memory");
 }
 register qword squared __asm__("vf1")=p->acceleration.q;
 register int active __asm__("$3");register float accelerationSquared __asm__("$f0"),one __asm__("$f1");
 __asm__("daddu %0,$zero,$zero\n\tvmul.xyz %2,%2,%2\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x ACC,%2,%2y\n\tvmaddz.x %2,$vf2,%2z\n\t.set noat\n\tlui $1,0x3f80\n\tmtc1 $1,%1\n\t.set at":"=r"(active),"=f"(one),"+j"(squared): :"$1","vf2");
 __asm__("qmfc2.ni $4,%1\n\tmtc1 $4,%0":"=f"(accelerationSquared):"j"(squared):"$4");
 if(one<accelerationSquared)active=1;
 else if(p->control->speed!=0.0f)active=1;
 if(active){
  func_0018C250(p,21,11);func_001A0450(p,p->axes,p->request);
  register qword scalar __asm__("vf5"),vector __asm__("vf2");register VTE*vtable __asm__("$3");
  __asm__(".set noat\n\tlui $1,0xbf80\n\tmtc1 $1,$f0\n\t.set at\n\tlqc2 $vf2,0x190(%3)\n\tmfc1 $2,$f0\n\tqmtc2.ni $2,%0\n\tlw %1,0xc(%3)\n\tlqc2 $vf3,0x1b0(%3)\n\tvmulx.xyzw $vf2,$vf2,%0x\n\tlqc2 $vf1,0x10(%4)\n\tlqc2 $vf4,0x20(%4)\n\tvmulax.xyz ACC,$vf3,$vf2x\n\tvmadday.xyz ACC,$vf1,$vf2y\n\tvmaddz.xyz %2,$vf4,$vf2z"
   :"=j"(scalar),"=r"(vtable),"=j"(vector):"r"(p),"r"(basis):"$1","$2","$f0","vf1","vf3","vf4","memory");
  register void*receiver __asm__("$4");register void(*writer)(void*,qword) __asm__("$2");register qword output __asm__("$5");
  __asm__("lh %0,0x118(%3)\n\tlqc2 $vf1,%4\n\tlw %1,0x11c(%3)\n\tvadd.xyzw $vf3,$vf1,%6\n\taddu %0,%5,%0\n\tqmfc2.ni %2,$vf3":"=r"(receiver),"=r"(writer),"=r"(output):"r"(vtable),"m"(w.phase.u.linear.q),"r"(p),"j"(vector):"vf1","vf3");
  w.phase.u.movement.q=scalar;
  writer(receiver,output);
 }else{func_0018C250(p,21,10);Set(p,35,w.phase.u.linear.q);}
}


typedef char qword_Size[(sizeof(qword)==16)?1:-1];
typedef char Pointer_Size[(sizeof(void*)==4)?1:-1];
typedef char U_Size[(sizeof(U)==16)?1:-1];
typedef char M3_Size[(sizeof(M3)==0x30)?1:-1];
typedef char M4_Size[(sizeof(M4)==0x40)?1:-1];
typedef char VTE_Size[(sizeof(VTE)==8)?1:-1];
typedef char PARAMS_Size[(sizeof(PARAMS)==12)?1:-1];
typedef char CONTROL_Size[(sizeof(CONTROL)==0x20)?1:-1];
typedef char REQUEST_Size[(sizeof(REQUEST)==0x7C)?1:-1];
typedef char AXIS_Size[(sizeof(AXIS)==0x20)?1:-1];
typedef char TRIREF_Size[(sizeof(TRIREF)==12)?1:-1];
typedef char LIST_Size[(sizeof(LIST)==0x90)?1:-1];
typedef char ROWS_Size[(sizeof(ROWS)==0x30)?1:-1];
typedef char PHASE_Size[(sizeof(PHASE)==0x40)?1:-1];
typedef char CLOCK_Size[(sizeof(CLOCK)==8)?1:-1];
typedef char WORK_Size[(sizeof(WORK)==0x270)?1:-1];
typedef char Sample_Buffer_Size[(sizeof(U[3])==0x30)?1:-1];
typedef char Plane_Buffer_Size[(sizeof(qword[8])==0x80)?1:-1];
typedef char VTE_delta_Offset[((unsigned)&((VTE*)0)->delta==0)?1:-1];
typedef char VTE_fn_Offset[((unsigned)&((VTE*)0)->fn==4)?1:-1];
typedef char PARAMS_a_Offset[((unsigned)&((PARAMS*)0)->a==0)?1:-1];
typedef char PARAMS_b_Offset[((unsigned)&((PARAMS*)0)->b==4)?1:-1];
typedef char PARAMS_duration_Offset[((unsigned)&((PARAMS*)0)->duration==8)?1:-1];
typedef char CONTROL_y_Offset[((unsigned)&((CONTROL*)0)->y==16)?1:-1];
typedef char CONTROL_z_Offset[((unsigned)&((CONTROL*)0)->z==20)?1:-1];
typedef char CONTROL_speed_Offset[((unsigned)&((CONTROL*)0)->speed==28)?1:-1];
typedef char REQUEST_multiplier_Offset[((unsigned)&((REQUEST*)0)->multiplier==120)?1:-1];
typedef char AXIS_weight_Offset[((unsigned)&((AXIS*)0)->weight==0)?1:-1];
typedef char AXIS_active_Offset[((unsigned)&((AXIS*)0)->active==4)?1:-1];
typedef char AXIS_direction_Offset[((unsigned)&((AXIS*)0)->direction==16)?1:-1];
typedef char TRIREF_index_Offset[((unsigned)&((TRIREF*)0)->index==0)?1:-1];
typedef char TRIREF_u_Offset[((unsigned)&((TRIREF*)0)->u==4)?1:-1];
typedef char TRIREF_v_Offset[((unsigned)&((TRIREF*)0)->v==8)?1:-1];
typedef char LIST_count_Offset[((unsigned)&((LIST*)0)->count==0)?1:-1];
typedef char LIST_planes_Offset[((unsigned)&((LIST*)0)->planes==16)?1:-1];
typedef char CLOCK_time_Offset[((unsigned)&((CLOCK*)0)->time==0)?1:-1];
typedef char CLOCK_dt_Offset[((unsigned)&((CLOCK*)0)->dt==4)?1:-1];
typedef char P_vt_Offset[((unsigned)&((P*)0)->vt==12)?1:-1];
typedef char P_control_Offset[((unsigned)&((P*)0)->control==336)?1:-1];
typedef char P_acceleration_Offset[((unsigned)&((P*)0)->acceleration==400)?1:-1];
typedef char P_basis_Offset[((unsigned)&((P*)0)->basis==432)?1:-1];
typedef char P_axes_Offset[((unsigned)&((P*)0)->axes==7696)?1:-1];
typedef char P_request_Offset[((unsigned)&((P*)0)->request==7952)?1:-1];
typedef char P_mesh_Offset[((unsigned)&((P*)0)->mesh==7960)?1:-1];
typedef char P_triangle_Offset[((unsigned)&((P*)0)->triangle==7964)?1:-1];
typedef char P_points_Offset[((unsigned)&((P*)0)->points==7984)?1:-1];
typedef char PHASE_facing_Offset[((unsigned)&((PHASE*)0)->facing==0)?1:-1];
typedef char PHASE_u_angular_Offset[((unsigned)&((PHASE*)0)->u.angular==0)?1:-1];
typedef char PHASE_u_linear_Offset[((unsigned)&((PHASE*)0)->u.linear==16)?1:-1];
typedef char PHASE_u_movement_Offset[((unsigned)&((PHASE*)0)->u.movement==32)?1:-1];
typedef char PHASE_u_scalar_Offset[((unsigned)&((PHASE*)0)->u.scalar==48)?1:-1];
typedef char WORK_closest_Offset[((unsigned)&((WORK*)0)->closest==0)?1:-1];
typedef char WORK_normal_Offset[((unsigned)&((WORK*)0)->normal==16)?1:-1];
typedef char WORK_frame_Offset[((unsigned)&((WORK*)0)->frame==32)?1:-1];
typedef char WORK_closestSamples_Offset[((unsigned)&((WORK*)0)->closestSamples==96)?1:-1];
typedef char WORK_phase_Offset[((unsigned)&((WORK*)0)->phase==144)?1:-1];
typedef char WORK_planes_Offset[((unsigned)&((WORK*)0)->planes==208)?1:-1];
typedef char WORK_samples_Offset[((unsigned)&((WORK*)0)->samples==352)?1:-1];
typedef char WORK_matrix_Offset[((unsigned)&((WORK*)0)->matrix==400)?1:-1];
typedef char WORK_inverse_Offset[((unsigned)&((WORK*)0)->inverse==448)?1:-1];
typedef char WORK_product_Offset[((unsigned)&((WORK*)0)->product==496)?1:-1];
typedef char WORK_position_Offset[((unsigned)&((WORK*)0)->position==544)?1:-1];
typedef char WORK_target_Offset[((unsigned)&((WORK*)0)->target==560)?1:-1];
typedef char WORK_negative_Offset[((unsigned)&((WORK*)0)->negative==576)?1:-1];
typedef char WORK_samplePointer_Offset[((unsigned)&((WORK*)0)->samplePointer==592)?1:-1];
typedef char WORK_projected_Offset[((unsigned)&((WORK*)0)->projected==608)?1:-1];
