/* class: CID_2C, the camera object (vt slots 43..45 are 0x12E738 / 0x12E740 / 0x12E750; SafeHouse cmworld.cpp: an
 * ASEG's scalar channel drives its lens +0x128, counted in +0x12C while in use). Slot 43: the driven value. */
struct CMOBJ {
    /* 0x000 */ char pad0[0x128];
    /* 0x128 */ float gLens;   /* field: SafeHouse port - the value an ASEG channel drives */
    /* 0x12c */ int cDrive;    /* field: SafeHouse port - the channels driving it */
};

float *func_0012E738(struct CMOBJ *pcmobj)
{
    return &pcmobj->gLens;
}
