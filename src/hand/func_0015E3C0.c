/* func_0015E3C0: the world's alias hash bucket of an oid (SW +0x1838, 512 buckets: the instances' aliases,
 * SafeHouse spliceglue.cpp). */
struct BUCKET { void *pent; int unk_0x4, unk_0x8; };
struct BUCKET *func_0015E3C0(char *psw, int oid)
{
    return &((struct BUCKET *)(psw + 0x1838))[(oid * 0x95675) & 0x1FF];
}
