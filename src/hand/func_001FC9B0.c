typedef int qword __attribute__((mode(TI)));
struct LO {char pad28[0x28];unsigned long flags;};
struct RANGE {float low,high;};
struct E {struct LO *object;struct RANGE limits;float gain;};
struct P {char pad1C[0x1C];struct LO *object;qword position;char pad30[0x70];int counts[6];struct E entries[6][8];};
extern qword D_002A2DD0;
int FFloatsNear(float,float,float) asm("FFloatsNear__Ffff");
void Update3D__4CSnd(struct P *);
qword PosOfLo__FP2LO(struct LO *);
void func_001FB778(struct P *,qword,const struct RANGE *,float *,int *);
void SetVoicePan__9CSndVoiceii(struct P *,int,int);
void SetVoiceVolume__9CSndVoiceif(struct P *,int,float);
static inline float X(qword q) { float f; __asm__("mtc1 %1, %0" : "=f"(f) : "r"(q)); return f; }
static inline float Y(qword q) { float f; __asm__("prot3w %0, %1" : "=r"(f) : "r"(q)); return f; }
static inline float Z(qword q) { float f; __asm__("pextuw %0, $0, %1" : "=r"(f) : "r"(q)); return f; }
static inline int FNear(qword a, qword b)
{
    return FFloatsNear(X(a), X(b), 0.0001f) && FFloatsNear(Y(a), Y(b), 0.0001f) && FFloatsNear(Z(a), Z(b), 0.0001f);
}
// name: SafeHouse port (CSndVoice::Update3D)
void Update3D__9CSndVoice(struct P *p)
{
    int group;
    if (p->object || !FNear(D_002A2DD0, p->position))
        Update3D__4CSnd(p);
    for (group = 0; group < 6; group++) {
        int count = p->counts[group];
        if (count) {
            float maximum = 0.0f;
            int flags = 0, active = 0, i;
            int *pflags = &flags;
            float fade;
            for (i = 0; i < count; i++) {
                struct E *entry = &p->entries[group][i];
                struct LO *object = entry->object;
                if (object && ((object->flags >> 60) & 1) == 1) {
                    active++;
                    func_001FB778(p, PosOfLo__FP2LO(object), &entry->limits, &fade, pflags);
                    pflags = 0;
                    { float gain = fade * entry->gain; maximum = maximum > gain ? maximum : gain; }
                }
            }
            SetVoicePan__9CSndVoiceii(p, group, active == 1 ? flags : 0);
            SetVoiceVolume__9CSndVoiceif(p, group, maximum);
        }
    }
}
