/* func_0015E380: the world's object hash bucket of an oid (SW +0x38, 512 buckets). */
struct BUCKET { void *plo; int unk_0x4, unk_0x8; };
struct BUCKET *func_0015E380(char *psw, int oid)
{
    return &((struct BUCKET *)(psw + 0x38))[(oid * 0x95675) & 0x1FF];
}
