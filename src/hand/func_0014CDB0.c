typedef int qword __attribute__((mode(TI)));
struct LSG { char pad[0x60]; };
int func_0014C6A0(void *pso, qword a, qword b, int c, struct LSG *plsg);
int func_0014C9F8(int c, struct LSG *alsg, int n, struct LSG *plsg, int cMax, struct LSG *alsg2, int f);
int func_0014CDB0(qword a, qword b, int cso, void **apso, int cMax, struct LSG *alsg)
{
    int c = 0;
    int i;
    for (i = 0; i < cso; i++) {
        struct LSG *plsg = &alsg[c];
        int n = func_0014C6A0(apso[i], a, b, cMax - c, plsg);
        if (n)
            c = func_0014C9F8(c, alsg, n, plsg, cMax, alsg, 0);
    }
    return c;
}
