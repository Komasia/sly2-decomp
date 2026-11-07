// Dispatch sprite actions and manage sound slots.
struct O;
struct VT { char pad[0x40]; short d; short pd; int (*kind)(void *); };
struct M { char pad[0xC]; struct VT *vt; };
struct E { char pad[0x14]; struct M *pm; };
struct R { char pad[8]; struct E *ae; };
struct A { int kind; int id; };
struct F { char pad[0x18]; unsigned char count; char pad1[3]; struct A *aa; };
struct S { char pad[4]; struct F *af; char pad1[8]; struct R *r; };
extern char D_003DD040[];
extern "C" struct M *PsndNewPlain(int id) asm("PsndNewPlain__Fi");
extern "C" void SetSource(struct M *, struct O *) asm("SetSource__4CSndPv");
extern "C" void Stop(struct M *, float) asm("Stop__4CSndf");
extern "C" void func_00258040(struct M **pp, struct M *m);
extern "C" void *PsndStartDialog(void *p,int a,int b) asm("PsndStartDialog__FP8SOUNDMGRii");
extern "C" void StopDialog(void *p) asm("StopDialog__FP8SOUNDMGR");
static inline M *SlotSound(M *const &slot){register M *value asm("$4");asm("lw %0,0(%1)":"=r"(value):"r"(&slot),"m"(slot));return value;}
static inline void Stop(M **pp){if(pp){M *sound=SlotSound(*pp);if(sound){Stop(sound,0.0f);func_00258040(pp,0);}}}
static inline unsigned int Presence(M *const &slot){register unsigned int value asm("$3");__asm__("lw %0,%1":"=r"(value):"m"(slot));return value;}
static inline int EntryOffset(int index,int stride){int value;__asm__("mult %0,%1,%2":"=r"(value):"r"(index),"r"(stride):"hi","lo");return value;}
static inline int ActionKind(const A &action){register int value asm("$3");asm("lw %0,%1":"=r"(value):"m"(action.kind));return value;}
static inline int StopOffset(int index,int stride){register int value asm("$5");asm("mult %0,%1,%2":"=r"(value):"r"(index),"r"(stride):"hi","lo");return value;}
static inline R *StopReceiver(const S *owner){register R *value asm("$3");asm("lw %0,%1":"=r"(value):"m"(owner->r));return value;}
static inline E *StopArray(const R *receiver){register E *value asm("$4");asm("lw %0,%1":"=r"(value):"m"(receiver->ae));return value;}
static inline M **SlotAddress(E *entry){M **value;asm("addiu %0,%0,%2":"=r"(value):"0"(entry),"i"(sizeof(E)-sizeof(M *)));return value;}
static inline E *StopEntry(E *array,int offset){register E *value asm("$2");asm("addu %0,%1,%2":"=r"(value):"r"(offset),"r"(array));return value;}
extern "C" void func_00219190(struct S *p,int fi,int i) {
    struct F *f=&p->af[fi];
    int j=0;
    if(!f->count)return;
    int stride=sizeof(E);
    int createOffset=EntryOffset(i,stride);
    do {
        struct A *a=(struct A *)(j*sizeof(A)+(int)f->aa);
        switch(ActionKind(*a)) {
        case 0: {
            struct M *m=PsndNewPlain(a->id);
            SetSource(m,0);
            if(m->vt->kind((char *)m+m->vt->d)==2)
                func_00258040(&((E *)(createOffset+(int)p->r->ae))->pm,m);
            break;
        }
        case 1: {
            R *receiver=StopReceiver(p);int offset=StopOffset(i,stride);
            E *e=StopEntry(StopArray(receiver),offset);
            if(Presence(e->pm)) Stop(SlotAddress(e));
            break;
        }
        case 2: PsndStartDialog(D_003DD040,a->id,0); break;
        case 3: StopDialog(D_003DD040); break;
        }
    } while(++j<f->count);
}
