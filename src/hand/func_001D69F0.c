typedef int qword __attribute__((mode(TI)));
extern qword g_normalZ;
static inline float Z(qword q) { float f; __asm__("pextuw %0, $zero, %1" : "=r"(f) : "r"(q)); return f; }
static inline qword Bc(float g) {
    union { qword q; float f; } u;
    qword k;
    __asm__("qmtc2.ni %1, %0" : "=j"(k) : "r"(g));
    u.q=k;
    return k;
}
/* class: launcher, class 0x70 (SafeHouse launcher.cpp): the launch velocity that takes an object from posStart to
 * posEnd in dt seconds under the vertical acceleration acc: the horizontal part of the offset / dt plus, along
 * g_normalZ, (dz - acc.z dt^2 / 2) / dt. */
qword func_001D69F0(qword posStart, qword posEnd, qword acc, float dt)
{
    float halfdt = dt * 0.5f;
    float accz = Z(acc);
    qword delta, axis, dot, one, proj, flat, inv, vz, vel;
    float z, invdt;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(delta) : "j"(posEnd), "j"(posStart));
    z = Z(delta) - (dt * halfdt) * accz;
    invdt = 1.0f / dt;
    axis = g_normalZ;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(dot), "=&j"(one) : "j"(delta), "j"(axis));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(proj) : "j"(axis), "j"(dot));
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(flat) : "j"(delta), "j"(proj));
    inv = Bc(invdt);
    vz = Bc(z / dt);
    __asm__("vmulax.xyzw $ACC, %1, %2x\n\tvmaddx.xyzw %0, %3, %4x" : "=j"(vel) : "j"(flat), "j"(inv), "j"(axis), "j"(vz));
    return vel;
}
