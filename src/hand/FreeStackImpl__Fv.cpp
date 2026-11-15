/* FreeStackImpl (0x1AE428, Sly 1 memory.c): closes a stack-heap frame: pops the stack bottom and leaves the critical
 * section. */
struct CRITSECT { int a[3]; };
extern CRITSECT s_critsectStack;
extern int s_ipvStackCur;
extern void *s_pvStackMin;
extern void *s_apvStackMin[];
void LeaveCritSect(CRITSECT *p);
void FreeStackImpl()
{
    s_pvStackMin = s_apvStackMin[s_ipvStackCur--];
    LeaveCritSect(&s_critsectStack);
}
