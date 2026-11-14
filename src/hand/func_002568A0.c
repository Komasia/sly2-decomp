/* class: a Splice library object (vtable entry at 0x2CA62C): its +0x14 hash table emptied (0x2567D0: every entry
 * freed through the table's heap, then the bucket array). */
typedef struct HASH HASH;
void func_002567D0(HASH *phash);

void func_002568A0(char *p)
{
    func_002567D0((HASH *)(p + 0x14));
}
