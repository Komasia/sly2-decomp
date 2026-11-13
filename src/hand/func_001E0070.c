struct SGG { char pad[0x84]; int calarm; void *apalarm[8]; };
void *s1_memmove(void *d, void *s, int cb);
void func_001E0070(struct SGG *psgg, void *palarm)
{
    int i;
    for (i = 0; i < psgg->calarm; i++) {
        if (psgg->apalarm[i] == palarm) {
            s1_memmove(psgg->apalarm + i, psgg->apalarm + i + 1, (psgg->calarm - i) * 4 - 4);
            psgg->calarm--;
            return;
        }
    }
}
