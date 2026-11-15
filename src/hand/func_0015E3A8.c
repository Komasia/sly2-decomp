/* func_0015E3A8: the world's list of the objects of a class (SW +0x3038, by cid). */
struct BUCKET { void *plo; int unk_0x4, unk_0x8; };
struct BUCKET *func_0015E3A8(char *psw, int cid)
{
    return &((struct BUCKET *)(psw + 0x3038))[cid];
}
