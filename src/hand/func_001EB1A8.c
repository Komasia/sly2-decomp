struct AR { int cb; int cbAlign; };
struct E28 { char pad[0x28]; };
struct E20 { char pad[0x20]; };
struct Z { int a; short b; unsigned char c1; unsigned char c2; int pad8; struct E28 **ap1; struct E20 **ap2; };
extern struct E28 *D_003DCFF4;
extern struct E20 *D_003DCFFC;
void Read__18CBinaryInputStreamiPv(void *pbis, int cb, void *pv);
int U16Read(void *pbis) asm("U16Read__18CBinaryInputStream");
void *PvAllocSwImpl__Fi(struct AR *par);
// name: SafeHouse port (LoadTexFromBrx)
void LoadTexFromBrx__FP18CBinaryInputStreamP3TEX(void *pbis, struct Z *pz)
{
    struct AR ar;
    int i;
    Read__18CBinaryInputStreamiPv(pbis, 8, pz);
    if (pz->c1) {
        ar.cb = pz->c1 * 4;
        ar.cbAlign = 0x10;
        pz->ap1 = PvAllocSwImpl__Fi(&ar);
        for (i = 0; i < pz->c1; i++)
            pz->ap1[i] = &D_003DCFF4[U16Read(pbis)];
    }
    if (pz->c2) {
        ar.cb = pz->c2 * 4;
        ar.cbAlign = 0x10;
        pz->ap2 = PvAllocSwImpl__Fi(&ar);
        for (i = 0; i < pz->c2; i++) {
            int k = U16Read(pbis);
            if (k == 0xFFFF) pz->ap2[i] = 0;
            else pz->ap2[i] = &D_003DCFFC[k];
        }
    }
}
