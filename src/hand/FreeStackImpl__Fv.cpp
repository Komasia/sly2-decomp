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
