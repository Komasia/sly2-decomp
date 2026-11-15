/* A controller's slot back to the controller slot heap D_003E123C (SafeHouse xfhandle.cpp: "delete pe; // 0x12E210"). */
extern char D_003E123C[];
void func_0011CD98(void *pslotheap, void *pv);   /* the slot heap's free */

void func_0012E210(void *pctrl)
{
    func_0011CD98(D_003E123C, pctrl);
}
