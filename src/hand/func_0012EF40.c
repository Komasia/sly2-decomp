/* The ambient sound object's EOPID 100 option (SafeHouse soundglue.cpp: 0x101848 -> 0x12EF40): one more falloff
 * record {target id, falloff start / end, volume} for the resident ambience, 8 at most. */
typedef struct FALL { int id; float sFalloffMin; float sFalloffMax; float g; } FALL;   /* field: SafeHouse port */
typedef struct AMB { char pad[0xF0]; int cfall; FALL *afall; } AMB;
#define CFALL_AMB_MAX 8
void func_0012EF40(AMB *pamb, int id, int sFalloffMin, int sFalloffMax, float g)
{
    if (pamb->cfall < CFALL_AMB_MAX) {
        FALL *pfall = &pamb->afall[pamb->cfall++];
        pfall->id = id;
        pfall->sFalloffMin = sFalloffMin;
        pfall->sFalloffMax = sFalloffMax;
        pfall->g = g;
    }
}
