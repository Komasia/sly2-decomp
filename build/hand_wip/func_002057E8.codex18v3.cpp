typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct M3 { qword r[3]; };
struct S { char pad[0x218]; qword *origin; int pad21C; float radius; };
extern "C" {
struct M3 *func_001A6318(struct S *p);
qword func_001A62E8(struct S *p);
extern int D_002C3CC8[2][3];
}
extern "C" void func_002057E8(struct S *p, qword out[2][3])
{
    qword point[5];
    U scalar, origin, right, forward;
    register qword *originPointer __asm__("$2")=p->origin;
    register qword originBits __asm__("$2")=*originPointer;
    origin.q=originBits;
    register M3 *matrix __asm__("$2")=func_001A6318(p);
    register qword rightBits __asm__("$2")=matrix->r[0];
    right.q=rightBits;
    M3 *nextMatrix=func_001A6318(p);
    {register qword forwardBits __asm__("vf4");
     __asm__("lqc2 %0,%1":"=j"(forwardBits):"m"(nextMatrix->r[1]));
     forward.q=forwardBits;}
    point[0] = func_001A62E8(p);
    register float radius __asm__("$f0")=p->radius;
    register qword positive __asm__("vf1"),negative __asm__("vf3");
    register qword forwardValue __asm__("vf4"),rightValue __asm__("vf6"),center __asm__("vf6");
    register qword forwardPositive __asm__("vf2"),rightPositive __asm__("vf1");
    register qword forwardNegative __asm__("vf4"),rightNegative __asm__("vf5");
    register float positiveWord __asm__("$4")=radius;
    radius=-radius;
    __asm__("qmtc2.ni %2,%0\n\tlqc2 %1,%3":"=j"(positive),"=j"(forwardValue):"r"(positiveWord),"m"(forward));
    __asm__("vmulx.xyzw %0,%2,%3x\n\tlqc2 %1,%4":"=&j"(forwardPositive),"=j"(rightValue):"j"(forwardValue),"j"(positive),"m"(right));
    __asm__("qmtc2.ni %2,%0\n\tsqc2 %3,%1":"=j"(negative),"=m"(scalar.q):"r"(radius),"j"(positive));
    center=rightValue;rightPositive=positive;forwardNegative=forwardValue;
    __asm__("vmulx.xyzw %0,%2,%4x\n\tvmulx.xyzw %1,%2,%1x\n\tlqc2 %2,%5\n\tvmulx.xyzw %3,%3,%4x"
        :"=&j"(rightNegative),"+j"(rightPositive),"+j"(center),"+j"(forwardNegative)
        :"j"(negative),"m"(origin));
    __asm__("vadd.xyzw %0,%4,%0\n\tvadd.xyzw %1,%4,%1\n\tvadd.xyzw %2,%4,%2\n\tvadd.xyzw %3,%4,%3"
        :"+&j"(forwardNegative),"+&j"(rightPositive),"+&j"(forwardPositive),"+&j"(rightNegative)
        :"j"(center));
    __asm__("sqc2 %5,%0\n\tsqc2 %6,%1\n\tsqc2 %7,%2\n\tsqc2 %8,%3\n\tsqc2 %9,%4"
        :"=m"(scalar.q),"=m"(point[1]),"=m"(point[2]),"=m"(point[3]),"=m"(point[4])
        :"j"(negative),"j"(rightPositive),"j"(forwardPositive),"j"(rightNegative),"j"(forwardNegative));
    for (unsigned i=0;i<2;++i) {
        int *indices=D_002C3CC8[i];
        qword *destination=out[i];
        for(unsigned j=0;j<3;++j) {
            register qword *source __asm__("$2")=(qword *)((*indices++<<4)+(unsigned int)point);
            register qword value __asm__("$3");
            __asm__("lq %0,%1":"=r"(value):"m"(*source));
            *destination++=value;
        }
    }
}
