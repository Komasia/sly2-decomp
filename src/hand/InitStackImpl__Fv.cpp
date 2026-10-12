struct CRITSECT { int a[3]; };
extern CRITSECT D_002F6390;
extern int D_002F639C;
extern void *D_002F6388;
extern void *D_002F63A0[];
void EnterCritSect(CRITSECT *p);
void InitStackImpl()
{
    EnterCritSect(&D_002F6390);
    D_002F63A0[++D_002F639C] = D_002F6388;
}
