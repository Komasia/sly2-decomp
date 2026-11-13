/* CFrame::SetSingleParent: a script frame keeps one parent: the parent count (+0x8) becomes 1 and func_00256EE0
 * is called on the first parent slot (+0xC). */
struct CFrame {
    /* 0x0 */ char pad0[8];
    /* 0x8 */ int cpframeParent;
    /* 0xc */ void *apframeParent[1];
};
void func_00256EE0(void *ppv);

// name: SafeHouse port (CFrame::SetSingleParent)
void SetSingleParent__6CFrame(struct CFrame *pframe)
{
    pframe->cpframeParent = 1;
    func_00256EE0(pframe->apframeParent);
}
