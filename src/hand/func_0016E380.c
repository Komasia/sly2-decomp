/* func_0016E380: a render pass's finish: the common finish, then (with queued packets) the GIF settings D_002DF010
 * sent (0x25 qwords, func_0016E318). */
extern int D_003DCFA0;
extern char D_002DF010[];
void func_0016E228(void *p);
void func_0016E318(void *p, int n, void *pv);
void func_0016E380(void *p)
{
    func_0016E228(p);
    if (D_003DCFA0 > 0)
        func_0016E318(p, 0x25, D_002DF010);
}
