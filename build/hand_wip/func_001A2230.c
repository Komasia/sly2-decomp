/* WIP: 4/73 differ: only case 8..17 'n==0x4000' test: target puts 0x4000 in v1 and uses beq (v0=1 delay); ours v0/bne. Jump tables 0x2A6830/0x2A6870 decoded. */
struct P { char pad[0x298]; int x298; char pad2[0x2DC - 0x29C]; int x2DC; char pad3[0x4C8 - 0x2E0]; int x4C8; char pad4[0xDF4 - 0x4CC]; int xDF4; };
struct S { struct P *x0; int x4; char pad[0x88]; int x90; };
extern int D_002E1E00;
extern char D_003DD490[];
int func_0020F0B0(void *g);
int func_001A2230(struct S *s, int n)
{
    struct P *p;
    if (s->x0->x298)
        return 1;
    if (n == 0x2000 || n == 0x4000) {
        switch (s->x0->xDF4) {
        case -1:
            switch (s->x0->x4C8) {
            case -1:
                switch (s->x0->x2DC) {
                case -1:
                    goto ret0;
                case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17:
                    if (n != 0x4000)
                        goto ret0;
                    goto ret1;
                }
                return 0;
            case 1: case 2: case 5: case 6: case 9:
                goto ret0;
            }
            goto ret1;
        case 3: case 5: case 10: case 11:
            goto ret1;
        }
        goto ret0;
    }
    if (s->x4 != -1)
        return 1;
    if (s->x90 == 1)
        return 1;
    if (D_002E1E00 & 1)
        return 1;
    if (!func_0020F0B0(D_003DD490))
        goto ret0;
ret1:
    return 1;
ret0:
    return 0;
}
