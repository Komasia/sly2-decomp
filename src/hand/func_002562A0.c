/* class: CM, the camera (SafeHouse spliceglue.cpp case 35, orig 0x2562A0: its rotation matrix +0x60). */
struct CM {
    /* 0x00 */ char pad0[0x60];
    /* 0x60 */ float mat[12];
};

float *func_002562A0(struct CM *pcm)
{
    return pcm->mat;
}
