/* load_sly_icon_from_disc: the memory card icon loaded with the two built-in icon tables. */
extern char D_002A38E8[];
extern char D_002A6CA0[];
void func_001AC260(int a0, int a1, char *p2, char *p3);

void load_sly_icon_from_disc(int a0, int a1)
{
    func_001AC260(a0, a1, D_002A38E8, D_002A6CA0);
}
