/* func_001A61E0 (0x1A61E0): a splice method handler: the base handler (func_001331F8), then for messages 5 / 6 the
 * task events 0x1A / 0x1B about the object. */
struct CRef {
    int kind;
    union { int integer; float scalar; void *pointer; } value;
};
extern char g_game[];
void func_001331F8(void *p, int n, int deferred, int argumentCount,
                   void *const *arguments, struct CRef *output);
void BroadcastTaskEvent__FP2SWiP2LO(void *p, int n, void *q);
#define FIELD_OFFSET(t,m) ((unsigned int)&(((struct t*)0x10000)->m)-0x10000)
typedef char CRef_KindOffset[FIELD_OFFSET(CRef,kind)==0?1:-1];
typedef char CRef_ValueOffset[FIELD_OFFSET(CRef,value)==4?1:-1];
typedef char CRef_Size[sizeof(struct CRef)==8?1:-1];
typedef char Pointer_Size[sizeof(void*)==4?1:-1];
typedef char Int_Size[sizeof(int)==4?1:-1];
void func_001A61E0(void *plo, int nMsg, int deferred, int argumentCount,
                   void *const *arguments, struct CRef *output)
{
    func_001331F8(plo, nMsg, deferred, argumentCount, arguments, output);
    switch (nMsg) {
    case 5:
        BroadcastTaskEvent__FP2SWiP2LO(g_game, 0x1A, plo);
        break;
    case 6:
        BroadcastTaskEvent__FP2SWiP2LO(g_game, 0x1B, plo);
        break;
    }
}
