struct G { char pad[0x4070]; int f4070; };
extern struct G D_003DD490;
void *func_0015E3A8(struct G *, int);
void func_0011A118(void *, void *);
void func_0011CD98(void *, void *);
void func_00139318(void *p) {
    func_0011A118(func_0015E3A8(&D_003DD490, 0x1c), p);
    func_0011CD98(&D_003DD490.f4070, p);
}
