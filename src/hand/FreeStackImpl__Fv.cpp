struct CRITSECT { int a[3]; };
extern CRITSECT D_002F6390;
extern int D_002F639C;
extern void *D_002F6388;
extern void *D_002F63A0[];
void LeaveCritSect(CRITSECT *p);
void FreeStackImpl()
{
    D_002F6388 = D_002F63A0[D_002F639C--];
    LeaveCritSect(&D_002F6390);
}
