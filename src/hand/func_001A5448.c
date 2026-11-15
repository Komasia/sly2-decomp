/* func_001A5448 (0x1A5448): an LO's sibling list and its "first removed child" link: the parent's (+0x64 / +0x70;
 * the added children come first, the removed after), or for a root the world's (D_003DD4A0 / +0xC).
 * SafeHouse activate.cpp. */
struct DLROOTS { int a[4]; };  /* the roots' list and its first removed root (+0xC) */
extern struct DLROOTS g_dlRoots __asm__("D_003DD4A0");
#define IB_DL_CHILD 0x64
#define IB_PLO_FIRST_REMOVED 0x70
void func_001A5448(char *psoParent, void **ppdl, void **ppploFirstRemoved)
{
    if (psoParent) { *ppdl = psoParent + IB_DL_CHILD; *ppploFirstRemoved = psoParent + IB_PLO_FIRST_REMOVED; }
    else { *ppdl = &g_dlRoots; *ppploFirstRemoved = (char *)&g_dlRoots + 0xC; }
}
