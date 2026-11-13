/* A plane set from its normal and distance (SafeHouse climbsurf.cpp: "plane = glm::vec4(unit, best); // 0x1193C0"):
 * the normal's qword, then the distance as its fourth float. */
typedef int qword __attribute__((mode(TI)));
typedef struct PLANE {
    /* 0x0 */ union {
        qword qw;
        struct { float x, y, z, g; } v;   /* normal x, y, z; g the distance */
    } u;
} PLANE;

void func_001193C0(PLANE *pplane, qword normal, float g)
{
    pplane->u.qw = normal;
    pplane->u.v.g = g;
}
