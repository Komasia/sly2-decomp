/* PostLoadBentley: the actor parts' post-load, the record of tag 0xB kind 1 (the swing's hand), the two root blends
 * and the two gaits bound, the sub-object (+0x1710: the square button's swing) set up with its height range [-50, 50],
 * the head's look controller attached (part 0x16), then state 0. Layout: SafeHouse port (gang.h BENTLEY). */
typedef int ti128 __attribute__((mode(TI)));
struct BENTLEY { char pad[0x10b8]; int pxf10B8; char pad2[0x1320 - 0x10bc]; char gaitWalk[0xc0]; char rb13E0[0x100]; char pblRb13E0[0x10];
    char rb14F0[0x100]; char pblRb14F0[0x10]; char gaitRun[0x110]; char sub[0x10]; };   /* field: SafeHouse port (gang.h BENTLEY) */
extern ti128 D_002BC920;   /* the sub-object's vector {175, 0, 0, 0} */
void PostLoadActorParts__FP5ACTOR(struct BENTLEY *);
int func_001F4C58(struct BENTLEY *, int, int);
void BindRootBlend__FP9ROOTBLENDP3ALOPP5MULTI(struct BENTLEY *, void *, void *);
void BindGait__FP4GAIT(void *);
void InitBentleySub__FP10BENTLEYSUBP3ALOG9VU_VECTORff(void *, struct BENTLEY *, ti128, float, float);
void AttachActorLook__FP5ACTORi(struct BENTLEY *, int);
void SetBentleyState__FP7BENTLEYi(struct BENTLEY *, int);
// name: SafeHouse port (PostLoadBentley)
void PostLoadBentley__FP7BENTLEY(struct BENTLEY *pbentley) {
    PostLoadActorParts__FP5ACTOR(pbentley);
    pbentley->pxf10B8 = func_001F4C58(pbentley, 0xb, 1);
    BindRootBlend__FP9ROOTBLENDP3ALOPP5MULTI(pbentley, pbentley->rb13E0, pbentley->pblRb13E0);
    BindRootBlend__FP9ROOTBLENDP3ALOPP5MULTI(pbentley, pbentley->rb14F0, pbentley->pblRb14F0);
    BindGait__FP4GAIT(pbentley->gaitWalk);
    BindGait__FP4GAIT(pbentley->gaitRun);
    InitBentleySub__FP10BENTLEYSUBP3ALOG9VU_VECTORff(pbentley->sub, pbentley, D_002BC920, -50.0f, 50.0f);
    AttachActorLook__FP5ACTORi(pbentley, 0x16);
    SetBentleyState__FP7BENTLEYi(pbentley, 0);
}
