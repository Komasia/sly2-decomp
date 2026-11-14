/* class: VEHICLE (SafeHouse vehiclebindings.cpp: the splice method 0x110838): a resource's count set. */
typedef struct RESOURCE {      /* field: SafeHouse port (vehiclebindings.cpp resources) */
    /* 0x0 */ int count;
    /* 0x4 */ int maximum;
    /* 0x8 */ float priority;
} RESOURCE;
typedef struct VEHICLE {
    /* 0x000 */ char pad0[0x574];
    /* 0x574 */ RESOURCE aresource[1];
} VEHICLE;

void func_001D4D18(VEHICLE *pvehicle, int iresource, int count)
{
    pvehicle->aresource[iresource].count = count;
}
