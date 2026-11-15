/* A blip group freed: off the world's list 0x1C and back to the world's slot heap +0x4070 (the inverse of PblipgNew). */
struct SW { char pad[0x4070]; int slotheapBlipg; };
extern struct SW g_sw;
void *func_0015E3A8(struct SW *, int);
void func_0011A118(void *, void *);
void func_0011CD98(void *, void *);
void func_00139318(void *pblipg) {
    func_0011A118(func_0015E3A8(&g_sw, 0x1c), pblipg);
    func_0011CD98(&g_sw.slotheapBlipg, pblipg);
}
