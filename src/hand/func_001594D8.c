/* class: PO (SafeHouse po.cpp: 0x1594D8 -> 0x1C4848 on the world, not bound; no script was seen calling it). */
struct SW;
struct PO;
extern struct SW g_sw;
void func_001C4848(struct SW *psw, struct PO *ppo);

void func_001594D8(struct PO *ppo)
{
    func_001C4848(&g_sw, ppo);
}
