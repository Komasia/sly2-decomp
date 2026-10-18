
typedef int qword __attribute__((mode(TI)));
typedef union U{qword q;float f[4];int i[4];}U;
typedef struct M4{U r[4];}M4;typedef struct M3{U r[3];}M3;
typedef struct VTE{short delta,pad;void*fn;}VTE;
typedef struct I3{int index[3];}I3;
typedef struct MESH{char pad0[0xC];VTE*vt;char pad10[0xD4];qword*vertices;int triangleCount;I3*triangles,*neighbors;}MESH;
typedef struct LIST{int count;char pad4[0xC];qword planes[0];}LIST;
typedef struct PARAMS{float a,b,duration;}PARAMS;
typedef struct IO{float distance,clamped;int count;qword*points;}IO;
typedef struct WORK{M4 matrix;U vertices[3],closest,plane;IO query;U triangleNormal,edgeStart,edgeEnd;int nextTriangle,twiceTriangle;U normal,edgePlane,point;}WORK;
extern float D_002DDED4,D_002A5688;
extern void func_0011EE08(qword,qword,qword,qword*,float*,float*);
extern float func_0011D018(PARAMS*,float,float,float,float*);
extern void func_001193C0(qword*,qword,float);
void func_001856C0(MESH*meshInput,LIST*outInput,int count,qword*points,PARAMS*paramsInput,float radiusInput){
 register MESH*mesh __asm__("$21")=meshInput;register LIST*out __asm__("$22")=outInput;
 register PARAMS*params __asm__("$30")=paramsInput;register float radius __asm__("$f21")=radiusInput;
 WORK w;register int i __asm__("$19")=0;
 VTE*e=&mesh->vt[31];M4*m;
 register float stopping __asm__("$f22"),step __asm__("$f23");register qword lastRow __asm__("$3");register int firstCount __asm__("$5");
 w.query.count=count;w.query.points=points;
 m=((M4*(*)(void*))e->fn)((char*)mesh+e->delta);
 __asm__("lq %3,0(%5)\n\tlui $4,%%hi(%8)\n\tlwc1 $f0,4(%6)\n\tlwc1 $f1,0(%6)\n\tsq %3,0(%9)\n\tlwc1 $f2,%%lo(%8)($4)\n\tadd.s $f1,$f1,$f0\n\tlq %3,16(%5)\n\tli.s $f3,5.00000000000000000000e-1\n\tsq %3,16(%9)\n\tmul.s $f1,$f1,$f3\n\tlq $4,32(%5)\n\tmul.s %1,$f2,$f3\n\tlwc1 $f0,8(%6)\n\tlw %4,0xE8(%7)\n\tsq $4,32(%9)\n\tmul.s %0,$f0,$f1\n\tlq %3,48(%5)"
  :"=f"(stopping),"=f"(step),"=m"(*(M3*)&w.matrix),"=&r"(lastRow),"=&r"(firstCount)
  :"r"(m),"r"(params),"r"(mesh),"i"(&D_002DDED4),"p"(&w.matrix):"$4","$f0","$f1","$f2","$f3","at","memory");
 w.matrix.r[3].q=lastRow;
 if(firstCount>0){register int stride __asm__("$3")=12;do{
  register int edge __asm__("$5"),limit __asm__("$20");
  register I3*indices __asm__("$4");register I3*neighbors __asm__("$5");register int neighbor __asm__("$2");
  __asm__("lw %0,0xF0(%4)\n\tmult %3,%5,%3\n\tlw %1,0xEC(%4)\n\taddu %2,%3,%0\n\taddu %1,%1,%3\n\tlw %0,0(%2)"
   :"=&r"(neighbor),"=&r"(indices),"=&r"(neighbors),"+&r"(stride):"r"(mesh),"r"(i):"hi","lo","memory");
  stride=-1;
  if(neighbor!=stride&&neighbors->index[1]!=stride){
   int nextTriangle=i+1;
   __asm__("lw %0,%1":"=r"(neighbor):"m"(neighbors->index[2]));
   w.nextTriangle=nextTriangle;if(neighbor!=stride)goto nextTriangle;
  }
  {
   register unsigned firstAddress __asm__("$2")=(unsigned)indices->index[0];register qword*vertexBase __asm__("$3");
   __asm__("sll $6,%4,1\n\tlw %1,0xE4(%5)\n\tdaddu %2,$zero,$zero\n\tsw $6,%3\n\tsll %0,%0,4\n\taddu %0,%0,%1"
    :"+&r"(firstAddress),"=&r"(vertexBase),"=r"(edge),"=m"(w.twiceTriangle):"r"(i),"r"(mesh):"$6","memory");
   __asm__("lqc2 $vf4,0(%8)\n\tlqc2 $vf3,0(%4)\n\taddiu %3,$zero,3\n\tlqc2 $vf7,16(%8)\n\taddiu %4,%7,1\n\tlqc2 $vf6,32(%8)\n\tlqc2 $vf5,48(%8)\n\tvmulax.xyz $ACC,$vf4,$vf3x\n\tvmadday.xyz $ACC,$vf7,$vf3y\n\tvmaddaz.xyz $ACC,$vf6,$vf3z\n\tvmaddw.xyz $vf3,$vf5,$vf0w\n\tsw %4,0xD0(%8)\n\tsqc2 $vf3,0x40(%8)\n\tlw %4,4(%5)\n\tsll %4,%4,4\n\taddu %4,%4,%6\n\tlqc2 $vf2,0(%4)\n\tvmulax.xyz $ACC,$vf4,$vf2x\n\tvmadday.xyz $ACC,$vf7,$vf2y\n\tvmaddaz.xyz $ACC,$vf6,$vf2z\n\tvmaddw.xyz $vf2,$vf5,$vf0w\n\tsqc2 $vf2,0x50(%8)\n\tvsub.xyzw $vf2,$vf2,$vf3\n\tlw %4,8(%5)\n\tsll %4,%4,4\n\taddu %4,%4,%6\n\tlqc2 $vf1,0(%4)\n\tvmulax.xyz $ACC,$vf4,$vf1x\n\tvmadday.xyz $ACC,$vf7,$vf1y\n\tvmaddaz.xyz $ACC,$vf6,$vf1z\n\tvmaddw.xyz $vf4,$vf5,$vf0w\n\tvsub.xyzw $vf3,$vf4,$vf3\n\tsqc2 $vf4,0x60(%8)\n\tvopmula.xyz $ACC,$vf2,$vf3\n\tvopmsub.xyz $vf1,$vf3,$vf2\n\tsqc2 $vf1,0xA0(%8)"
    :"=m"(w.vertices),"=m"(w.triangleNormal.q),"=m"(w.nextTriangle),"=&r"(limit),"+&r"(firstAddress)
    :"r"(indices),"r"(vertexBase),"r"(i),"p"(&w):"vf1","vf2","vf3","vf4","vf5","vf6","vf7","memory");
  }
  {register int edgeWord __asm__("$3")=w.twiceTriangle;do{
   register int next __asm__("$18");register qword bestPlane __asm__("$23");register float best __asm__("$f20");
   register int minusOne __asm__("$6");
   __asm__("lw $4,0xF0(%2)\n\taddiu %1,$zero,-1\n\taddu $2,%0,%3\n\taddu $2,$2,%4\n\tsll $2,$2,2\n\taddu $2,$2,$4\n\tlw %0,0($2)"
    :"+r"(edgeWord),"=&r"(minusOne):"r"(mesh),"r"(i),"r"(edge):"$2","$4","memory");
   next=edge+1;
   if(edgeWord==minusOne){
    register int ia __asm__("$3")=next%limit;register qword start __asm__("$3"),end __asm__("$4");
    register int pointCount __asm__("$2");register int plusTwo __asm__("$2"),ib __asm__("$4");
    __asm__("addiu %0,%1,2":"=r"(plusTwo):"r"(edge));ib=plusTwo%limit;
    __asm__("sll %0,%4,4\n\taddu %0,%0,%5\n\tlui $2,%%hi(%6)\n\tlq %0,0x40(%0)\n\tlwc1 %1,%%lo(%6)($2)\n\tsq %0,%2\n\tlw %3,%7"
     :"=r"(start),"=f"(best),"=m"(w.edgeStart.q),"=&r"(pointCount):"r"(ia),"p"(&w),"i"(&D_002A5688),"m"(w.query.count):"memory");
    __asm__("sll %0,%1,4\n\taddu %0,%0,%2\n\tlq %0,0x40(%0)":"=r"(end):"r"(ib),"p"(&w):"memory");
    w.edgeEnd.q=end;
    if(pointCount>0){
     register int remaining __asm__("$16");register qword*cursor __asm__("$17");
     /* The cross updates XYZ and preserves the current architectural VF4.W. */
     register qword plane __asm__("vf4");
     __asm__("qmtc2.ni %3,$vf2\n\tlw %0,%5\n\tqmtc2.ni %4,$vf3\n\tdaddu %1,%6,$zero\n\tvsub.xyzw $vf1,$vf2,$vf3\n\tlqc2 $vf2,%7\n\tvopmula.xyz $ACC,$vf2,$vf1\n\tvopmsub.xyz %2,$vf1,$vf2"
      :"=&r"(cursor),"=r"(remaining),"+j"(plane):"r"(end),"r"(start),"m"(w.query.points),"r"(pointCount),"m"(w.triangleNormal.q):"vf1","vf2","vf3");
     do{
      register qword point __asm__("vf5"),arg __asm__("$4"),a __asm__("$5"),b __asm__("$6");
      register qword*closest __asm__("$7");register float*parameter __asm__("$8"),*distanceOut __asm__("$9");
      __asm__("lqc2 %0,0(%6)\n\taddiu %1,%7,0x70\n\tlq %2,0xB0(%7)\n\tdaddu %3,$zero,$zero\n\tlq %4,0xC0(%7)\n\taddiu %5,%7,0x90"
       :"=j"(point),"=&r"(closest),"=&r"(a),"=&r"(parameter),"=&r"(b),"=r"(distanceOut):"r"(cursor),"p"(&w):"memory");
      __asm__("qmfc2.ni %0,%2\n\tsqc2 %3,%1":"=r"(arg),"=m"(w.edgePlane.q):"j"(point),"j"(plane));
      w.point.q=point;
      func_0011EE08(arg,a,b,closest,parameter,distanceOut);
      {
       register float distance __asm__("$f0"),threshold __asm__("$f1");
       __asm__("add.s %0,%3,%4\n\tlwc1 %1,%5\n\tlqc2 %2,%6":"=f"(threshold),"=f"(distance),"=j"(plane):"f"(radius),"f"(stopping),"m"(w.query.distance),"m"(w.edgePlane.q));
       if(distance<threshold){
        register qword normal __asm__("vf2"),delta __asm__("vf3");register float signedDistance __asm__("$f13"),actualRadius __asm__("$f12"),actualStep __asm__("$f14");
        point=w.point.q;
        __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x $vf1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,$vf1,%0z\n\tlqc2 %1,%3\n\tvsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q\n\tvsub.xyzw %1,%4,%1\n\tvdiv Q,$vf0w,%0x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q"
         :"=&j"(normal),"=&j"(delta):"j"(plane),"m"(w.closest.q),"j"(point):"vf1");
        {
         register int bits __asm__("$2");
         __asm__("mov.s %0,%4\n\tvmul.xyz %1,%5,%1\n\tvaddw.x $vf1,$vf0,$vf0w\n\tvadday.x $ACC,%1,%1y\n\tvmaddz.x %1,$vf1,%1z\n\tsqc2 %5,%2\n\tqmfc2.ni %3,%1"
          :"=f"(actualRadius),"+&j"(delta),"=m"(w.normal.q),"=r"(bits):"f"(radius),"j"(normal):"vf1");
         __asm__("mov.s %0,%2\n\tmtc1 %3,%1":"=f"(actualStep),"=f"(signedDistance):"f"(step),"r"(bits));
        }
        func_0011D018(params,actualRadius,signedDistance,actualStep,&w.query.clamped);
        {
         register float candidate __asm__("$f0");
         __asm__("lwc1 %0,%2\n\tlqc2 %1,%3":"=f"(candidate),"=j"(normal):"m"(w.query.clamped),"m"(w.normal.q));
         plane=w.edgePlane.q;
         if(candidate<best){
          register qword packedNormal __asm__("$5");
          best=candidate;
          __asm__("qmfc2.ni %0,%1":"=r"(packedNormal):"j"(normal));
          func_001193C0(&w.plane.q,packedNormal,best);
          plane=w.edgePlane.q;bestPlane=w.plane.q;
         }
        }
       }
      }
      remaining--;cursor++;
     }while(remaining);
    }
    {register float sentinel __asm__("$f0");register void*upper __asm__("$3");
    __asm__("lui %0,%%hi(%2)\n\tlwc1 %1,%%lo(%2)(%0)":"=&r"(upper),"=f"(sentinel):"i"(&D_002A5688):"memory");
    if(best!=sentinel){
     __asm__("lw $2,0(%1)\n\tsll $3,$2,4\n\taddiu $2,$2,1\n\taddu $3,$3,%1\n\tsw $2,0(%1)\n\tsq %2,16($3)":"+m"(out->count):"r"(out),"r"(bestPlane):"$2","$3","memory");
    }
    }
   }
   edge=next;edgeWord=w.twiceTriangle;
  }while(edge<3);}
 nextTriangle:{register int currentCount __asm__("$2");
 __asm__("lw %0,%2\n\tlw %1,%3":"=r"(currentCount),"=r"(i):"m"(mesh->triangleCount),"m"(w.nextTriangle));
 currentCount=i<currentCount;
 if(!currentCount)break;}
 stride=12;
 }while(1);

 }
}

typedef char qword_Size[(sizeof(qword)==16)?1:-1];
typedef char Pointer_Size[(sizeof(void*)==4)?1:-1];
typedef char U_Size[(sizeof(U)==16)?1:-1];
typedef char M4_Size[(sizeof(M4)==0x40)?1:-1];
typedef char VTE_Size[(sizeof(VTE)==8)?1:-1];
typedef char I3_Size[(sizeof(I3)==12)?1:-1];
typedef char PARAMS_Size[(sizeof(PARAMS)==12)?1:-1];
typedef char IO_Size[(sizeof(IO)==16)?1:-1];
typedef char WORK_Size[(sizeof(WORK)==0x110)?1:-1];
typedef char Triangle_Buffer_Size[(sizeof(U[3])==0x30)?1:-1];
typedef char VTE_delta_Offset[((unsigned)&((VTE*)0)->delta==0)?1:-1];
typedef char VTE_fn_Offset[((unsigned)&((VTE*)0)->fn==4)?1:-1];
typedef char MESH_vt_Offset[((unsigned)&((MESH*)0)->vt==12)?1:-1];
typedef char MESH_vertices_Offset[((unsigned)&((MESH*)0)->vertices==228)?1:-1];
typedef char MESH_triangleCount_Offset[((unsigned)&((MESH*)0)->triangleCount==232)?1:-1];
typedef char MESH_triangles_Offset[((unsigned)&((MESH*)0)->triangles==236)?1:-1];
typedef char MESH_neighbors_Offset[((unsigned)&((MESH*)0)->neighbors==240)?1:-1];
typedef char LIST_count_Offset[((unsigned)&((LIST*)0)->count==0)?1:-1];
typedef char LIST_planes_Offset[((unsigned)&((LIST*)0)->planes==16)?1:-1];
typedef char PARAMS_a_Offset[((unsigned)&((PARAMS*)0)->a==0)?1:-1];
typedef char PARAMS_b_Offset[((unsigned)&((PARAMS*)0)->b==4)?1:-1];
typedef char PARAMS_duration_Offset[((unsigned)&((PARAMS*)0)->duration==8)?1:-1];
typedef char IO_distance_Offset[((unsigned)&((IO*)0)->distance==0)?1:-1];
typedef char IO_clamped_Offset[((unsigned)&((IO*)0)->clamped==4)?1:-1];
typedef char IO_count_Offset[((unsigned)&((IO*)0)->count==8)?1:-1];
typedef char IO_points_Offset[((unsigned)&((IO*)0)->points==12)?1:-1];
typedef char WORK_matrix_Offset[((unsigned)&((WORK*)0)->matrix==0)?1:-1];
typedef char WORK_vertices_Offset[((unsigned)&((WORK*)0)->vertices==64)?1:-1];
typedef char WORK_closest_Offset[((unsigned)&((WORK*)0)->closest==112)?1:-1];
typedef char WORK_plane_Offset[((unsigned)&((WORK*)0)->plane==128)?1:-1];
typedef char WORK_query_Offset[((unsigned)&((WORK*)0)->query==144)?1:-1];
typedef char WORK_triangleNormal_Offset[((unsigned)&((WORK*)0)->triangleNormal==160)?1:-1];
typedef char WORK_edgeStart_Offset[((unsigned)&((WORK*)0)->edgeStart==176)?1:-1];
typedef char WORK_edgeEnd_Offset[((unsigned)&((WORK*)0)->edgeEnd==192)?1:-1];
typedef char WORK_nextTriangle_Offset[((unsigned)&((WORK*)0)->nextTriangle==208)?1:-1];
typedef char WORK_twiceTriangle_Offset[((unsigned)&((WORK*)0)->twiceTriangle==212)?1:-1];
typedef char WORK_normal_Offset[((unsigned)&((WORK*)0)->normal==224)?1:-1];
typedef char WORK_edgePlane_Offset[((unsigned)&((WORK*)0)->edgePlane==240)?1:-1];
typedef char WORK_point_Offset[((unsigned)&((WORK*)0)->point==256)?1:-1];

typedef char Int_Width[sizeof(int)==4?1:-1];
typedef char Unsigned_Width[sizeof(unsigned)==4?1:-1];
typedef char Short_Width[sizeof(short)==2?1:-1];
typedef char Float_Width[sizeof(float)==4?1:-1];
typedef char M3_Size[sizeof(M3)==0x30?1:-1];
typedef char LIST_Prefix_Size[sizeof(LIST)==0x10?1:-1];
typedef char U_Alignment[__alignof__(U)==16?1:-1];
typedef char WORK_Alignment[__alignof__(WORK)==16?1:-1];
typedef char PARAMS_Alignment[__alignof__(PARAMS)==4?1:-1];
typedef char MESH_Prefix_Size[sizeof(MESH)==0xF4?1:-1];
