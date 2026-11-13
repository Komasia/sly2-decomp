/* The game's pending state (SafeHouse task.cpp "TODO(M4): 0x1A4E70 / 0x1A4E80"): +0x1C4 below the first word. */
struct GAMEQUEUE {
    /* 0x000 */ int c;
    /* 0x004 */ char pad4[0x1c4 - 4];
    /* 0x1c4 */ int i;
};

int func_001A4E70(struct GAMEQUEUE *pq)
{
    return pq->i < pq->c;
}
