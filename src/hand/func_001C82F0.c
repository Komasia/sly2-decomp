/* class: VAULT (cid 0x4E, vt slot 15 = PostLoad; SafeHouse vault.cpp): the base post-load, its 0x18 parts bound
 * (D_002C0EC8), +0x204 found (oid 0x645), then state 5 when the vault is already open, else 0. */
struct VAULT {
    /* 0x000 */ char pad0[0x204];
    /* 0x204 */ int n204;
};
extern char D_002C0EC8[];   /* the parts' table */
void func_001F36A8(struct VAULT *plo);   /* the base post-load */
void BindLoParts__FP3ALOiPv(struct VAULT *palo, int c, void *pv);
int func_001F4C58(struct VAULT *palo, int oid, int n);
int FVaultOpened__Fv(void);
void SetVaultState__FP2LOi(struct VAULT *plo, int state);

void func_001C82F0(struct VAULT *pvault)
{
    func_001F36A8(pvault);
    BindLoParts__FP3ALOiPv(pvault, 0x18, D_002C0EC8);
    pvault->n204 = func_001F4C58(pvault, 0x645, 1);
    SetVaultState__FP2LOi(pvault, FVaultOpened__Fv() == 0 ? 0 : 5);
}
