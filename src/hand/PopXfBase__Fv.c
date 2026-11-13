/* PopXfBase: the base for transform references of kind 0x2000 popped (the stack depth D_004437A0; PushXfBase is
 * 0x22D670). Source: SafeHouse port (alo.cpp). */
extern int D_004437A0;   /* the base stack's depth */

// name: SafeHouse port (PopXfBase, alo.cpp)
void PopXfBase__Fv(void)
{
    D_004437A0 -= 1;
}
