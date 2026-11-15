/* The world's text of that id (LoadTextFromBrx), the default text when there is none (or id -1). */
struct TEXT { int id; void *pch; };
struct SW { char pad[0x4640]; int ctext; struct TEXT *atext; };
extern char D_002A4BE0[];   /* the default (empty) text */
void *func_0013E368(struct SW *psw, int id) {
    int i;
    if (id == -1) return D_002A4BE0;
    for (i = 0; i < psw->ctext; i++) {
        if (psw->atext[i].id == id) return psw->atext[i].pch;
    }
    return D_002A4BE0;
}
