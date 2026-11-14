/* class: a reference-counted Splice pointer (CRefPtr; the 4-entry array of 0x257078's object is destroyed with it):
 * its deleting destructor - the last reference destroys the object (0x257078 with 3: free it too), then the pointer
 * itself is deleted when bit 0 of the flags asks. */
typedef struct REFC { int cref; } REFC;

void func_00257078(REFC *p, int grfDelete);
void __builtin_delete(void *pv);

void func_002572E0(REFC **pp, int grfDelete)
{
    REFC *p = *pp;

    if (p != 0) {
        if (--p->cref == 0) {
            func_00257078(p, 3);
        }
    }
    if (grfDelete & 1) {
        __builtin_delete(pp);
    }
}
