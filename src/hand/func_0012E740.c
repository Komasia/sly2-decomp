/* class: CID_2C, the camera object (vt slot 44, SafeHouse cmworld.cpp): one more ASEG channel driving its lens. */
struct CMOBJ {
    /* 0x000 */ char pad0[0x128];
    /* 0x128 */ float gLens;   /* field: SafeHouse port */
    /* 0x12c */ int cDrive;    /* field: SafeHouse port - the channels driving gLens */
};

void func_0012E740(struct CMOBJ *pcmobj)
{
    pcmobj->cDrive++;
}
