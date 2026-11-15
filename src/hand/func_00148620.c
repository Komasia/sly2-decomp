/* class: a trigger state's animation list (SafeHouse trigger.cpp "0x148620: at most eight entries in each list"):
 * an entry (the ASEG's oid, its argument) appended; false when the list is full. */
#define CTRIGASEG_MAX 8
struct TRIGASEG { int oidAseg; int n; };
struct TRIGASEGLIST {
    /* 0x00 */ unsigned int c;
    /* 0x04 */ struct TRIGASEG a[CTRIGASEG_MAX];
};
int func_00148620(struct TRIGASEGLIST *plist, int oidAseg, int n)
{
    if (plist->c >= CTRIGASEG_MAX) return 0;
    plist->a[plist->c].oidAseg = oidAseg;
    plist->a[plist->c].n = n;
    plist->c++;
    return 1;
}
