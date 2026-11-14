/* func_001FE5E0 (called by UpdateSoundMgr): whether the record's state (+0x68) is 3. */
typedef struct REC68 {
    /* 0x00 */ char pad0[0x68];
    /* 0x68 */ int state;
} REC68;

int func_001FE5E0(REC68 *prec)
{
    return prec->state == 3;
}
