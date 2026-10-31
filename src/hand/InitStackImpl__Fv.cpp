struct CRITSECT { int a[3]; };
extern CRITSECT s_critsectStack;
extern int s_ipvStackCur;
extern void *s_pvStackMin;
extern void *s_apvStackMin[];
void EnterCritSect(CRITSECT *p);
void InitStackImpl()
{
    EnterCritSect(&s_critsectStack);
    s_apvStackMin[++s_ipvStackCur] = s_pvStackMin;
}
