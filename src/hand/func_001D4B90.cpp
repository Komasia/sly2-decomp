/* class: VEHICLE (SafeHouse vehicle.h attachments, max 8): create a vehicle attachment (class 0x99 VEHICLEATTACH,
 * 0xB0 bytes, vtable D_002C94A0), initialise it for this vehicle (func_001D4D30) and append it with its index,
 * object id, mesh id and anchor id. Field names: SafeHouse port (vehicle.h VEHICLEATTACH). */
extern char D_002C94A0[];
struct VEHICLE;
struct VEHICLEATTACH;
extern "C" void func_001D4D30(VEHICLEATTACH *,VEHICLE *);
extern "C" void *__builtin_new(int);
struct A { int unk_0x0; };
struct B : A {           /* the BASIC part: vtable at +0xC */
    int unk_0x4;
    int x8;
    char *vt;
};
struct VEHICLEATTACH : B {
    VEHICLE *powner;     /* set by func_001D4D30 */
    int index;
    int oid;
    char pad1c[0x2C - 0x1C];
    int oidMesh;          /* +0x2C */
    int pad30[2];
    int oidAnchor;        /* +0x38 */
    char pad[0xB0 - 0x3C];
};
struct VEHICLE { char pad[0x4F8]; unsigned int cattach; VEHICLEATTACH *apattach[8]; };
static inline VEHICLEATTACH *CreateItem(VEHICLE *owner) {
 void *allocated=__builtin_new(sizeof(VEHICLEATTACH));
 register VEHICLEATTACH *item __asm__("$16");
 register unsigned page __asm__("$3");
 __asm__("lui %0,%%hi(%3)\n\tdaddu %1,%2,$zero"
         : "=&r"(page), "=r"(item) : "r"(allocated), "i"(D_002C94A0));
 register char *vtable __asm__("$3");
 __asm__("addiu %0,%1,%%lo(%2)":"=r"(vtable):"r"(page),"i"(D_002C94A0));
 item->unk_0x0=0;
 __asm__("sw %1,%0":"=m"(item->vt):"r"(vtable):"memory");
 register VEHICLEATTACH*receiver __asm__("$4");__asm__ __volatile__("daddu %0,%2,$zero\n\tsw $zero,%1":"=&r"(receiver),"=m"(item->unk_0x4):"r"(item));func_001D4D30(receiver,owner);return item;
}
extern "C" void func_001D4B90(VEHICLE *p, int index, int oid, int inputMesh, int inputAnchor)
{
    register int oidMesh __asm__("$20")=inputMesh;
    register int oidAnchor __asm__("$21")=inputAnchor;
    if (p->cattach < 8) {
        VEHICLEATTACH *it = CreateItem(p);
        unsigned int iattach=p->cattach;
        it->index=index;
        it->oid=oid;
        p->apattach[iattach]=it;
        p->cattach=iattach+1;
        it->oidAnchor=oidAnchor;
        it->oidMesh=oidMesh;
    }
}

#define OFF(T,F) ((unsigned int)&((T*)0)->F)
typedef char native_layout_0[(sizeof(int)==4)?1:-1];
typedef char native_layout_1[(sizeof(unsigned)==4)?1:-1];
typedef char native_layout_2[(sizeof(void*)==4)?1:-1];
typedef char native_layout_3[(sizeof(A)==4)?1:-1];
typedef char native_layout_4[(sizeof(B)==0x10)?1:-1];
typedef char native_layout_5[(sizeof(VEHICLEATTACH)==0xB0)?1:-1];
typedef char native_layout_6[(OFF(VEHICLEATTACH,unk_0x0)==0)?1:-1];
typedef char native_layout_7[(OFF(VEHICLEATTACH,unk_0x4)==4)?1:-1];
typedef char native_layout_8[(OFF(VEHICLEATTACH,vt)==0xC)?1:-1];
typedef char native_layout_9[(OFF(VEHICLEATTACH,powner)==0x10)?1:-1];
typedef char native_layout_10[(OFF(VEHICLEATTACH,index)==0x14)?1:-1];
typedef char native_layout_11[(OFF(VEHICLEATTACH,oid)==0x18)?1:-1];
typedef char native_layout_12[(OFF(VEHICLEATTACH,oidMesh)==0x2C)?1:-1];
typedef char native_layout_13[(OFF(VEHICLEATTACH,oidAnchor)==0x38)?1:-1];
typedef char native_layout_14[(OFF(VEHICLE,cattach)==0x4F8)?1:-1];
typedef char native_layout_15[(OFF(VEHICLE,apattach)==0x4FC)?1:-1];
