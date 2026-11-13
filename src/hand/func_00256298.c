/* class: CM, the camera (vt slot; SafeHouse spliceglue.cpp case 34, orig 0x256298: its position). */
typedef int qword __attribute__((mode(TI)));
struct CM {
    /* 0x00 */ char pad0[0x90];
    /* 0x90 */ qword pos;
};

qword func_00256298(struct CM *pcm)
{
    return pcm->pos;
}
