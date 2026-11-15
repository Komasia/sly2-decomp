/* func_0016D698: note where in a GIF packet a register setting is (the packet's qword count so far, + 0x23), for
 * patching it later: one {id, iqw} entry appended. */
struct GIFS { int x0; char *pbStart; int x8; char *pbCur; };
struct PATCH { short id; short iqw; };
void func_0016D698(int id, struct GIFS *pgifs, struct PATCH **pppatch)
{
    struct PATCH *ppatch = (*pppatch)++;
    ppatch->id = id;
    ppatch->iqw = ((pgifs->pbCur - pgifs->pbStart) >> 4) + 0x23;
}
