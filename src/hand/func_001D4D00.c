/* class: VEHICLE (SafeHouse vehiclebindings.cpp: the splice method 0x1107B8): a resource's count. */
typedef struct RESOURCE {      /* field: SafeHouse port (vehiclebindings.cpp resources) */
    /* 0x0 */ int count;
    /* 0x4 */ int maximum;
    /* 0x8 */ float priority;
} RESOURCE;
typedef struct VEHICLE {
    /* 0x000 */ char pad0[0x574];
    /* 0x574 */ RESOURCE aresource[1];
} VEHICLE;

int func_001D4D00(VEHICLE *pvehicle, int iresource)
{
    return pvehicle->aresource[iresource].count;
}
