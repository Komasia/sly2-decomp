/* CGc::AddRootFrame: a frame made a root of the garbage collector: unlinked from its list (0x255770), pushed on the
 * root list D_002DD2AC (0x255588) and flagged as a root. */
typedef struct FRAME {
    /* 0x0 */ int x0;
    /* 0x4 */ unsigned prev : 13;     /* the list links: a node index and its page (D_004520E8) */
    unsigned prevpg : 2;
    unsigned fRoot : 1;
    unsigned next : 13;
    unsigned nextpg : 2;
    unsigned fMark : 1;
} FRAME;
extern FRAME *D_002DD2AC;   /* the root frames */
void func_00255770(FRAME *pframe);                    /* unlink */
void func_00255588(FRAME *pframe, FRAME **ppframeHead);  /* push */

// name: SafeHouse port (CGc::AddRootFrame)
void AddRootFrame__3CGc(FRAME *pframe)
{
    func_00255770(pframe);
    func_00255588(pframe, &D_002DD2AC);
    pframe->fRoot = 1;
}
