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
    float radius=p->radius;
    register qword positive __asm__("vf1"),negative __asm__("vf3");
    register qword forwardValue __asm__("vf4"),rightValue __asm__("vf6"),center __asm__("vf6");
    register qword forwardPositive __asm__("vf2"),rightPositive __asm__("vf1");
    register qword forwardNegative __asm__("vf4"),rightNegative __asm__("vf5");
    __asm__("qmtc2.ni %1,%0":"=j"(positive):"r"(radius));
    __asm__("lqc2 %0,%1":"=j"(forwardValue):"m"(forward));
    __asm__("vmulx.xyzw %0,%1,%2x":"=j"(forwardPositive):"j"(forwardValue),"j"(positive));
    __asm__("lqc2 %0,%1":"=j"(rightValue):"m"(right));
    __asm__("qmtc2.ni %2,%0\n\tsqc2 %3,%1":"=j"(negative),"=m"(scalar.q):"r"(-radius),"j"(positive));
    __asm__("vmulx.xyzw %0,%1,%2x":"=j"(rightNegative):"j"(rightValue),"j"(negative));
    __asm__("vmulx.xyzw %0,%1,%2x":"=j"(rightPositive):"j"(rightValue),"j"(positive));
    __asm__("lqc2 %0,%1":"=j"(center):"m"(origin));
    __asm__("vmulx.xyzw %0,%1,%2x":"=j"(forwardNegative):"j"(forwardValue),"j"(negative));
    __asm__("vadd.xyzw %0,%1,%2":"=j"(forwardNegative):"j"(center),"j"(forwardNegative));
    __asm__("vadd.xyzw %0,%1,%2":"=j"(rightPositive):"j"(center),"j"(rightPositive));
    __asm__("vadd.xyzw %0,%1,%2":"=j"(forwardPositive):"j"(center),"j"(forwardPositive));
    __asm__("vadd.xyzw %0,%2,%3\n\tsqc2 %4,%1":"=j"(rightNegative),"=m"(scalar.q):"j"(center),"j"(rightNegative),"j"(negative));
    point[1]=rightPositive;
    point[2]=forwardPositive;
    point[3]=rightNegative;
    point[4]=forwardNegative;
    for (unsigned i = 0; i < 2; i++) {
        for (unsigned j = 0; j < 3; j++) {
            register qword *source __asm__("$2")=(qword *)((D_002C3CC8[i][j]<<4)+(unsigned int)point);register qword value __asm__("$3");__asm__("lq %0,%1":"=r"(value):"m"(*source));out[i][j]=value;
        }
    }
}
