/* CFrame::AddParent: append a parent to a script frame's parent list (+0xC, count +0x8); func_00256EE0 sets the
 * slot's reference. */
struct CFrame {
    /* 0x0 */ char pad0[8];
    /* 0x8 */ int cpframeParent;
    /* 0xc */ struct CFrame *apframeParent[1];
};
void func_00256EE0(struct CFrame **ppframe, struct CFrame *pframe);

// name: SafeHouse port (CFrame::AddParent)
void AddParent__6CFrameP6CFrame(struct CFrame *pframe, struct CFrame *pframeParent)
{
    int i = pframe->cpframeParent;
    pframe->cpframeParent = i + 1;
    /* the slot &pframe->apframeParent[i], with the address arithmetic in the order the original compiles to */
    func_00256EE0((struct CFrame **)((i * 4 + (int)pframe) + 0xC), pframeParent);
}
