extern int D_002DFB4C;
extern int D_002DFB58;
extern "C" void func_00234A60(int sid);
void SyncVBlank()
{
    D_002DFB58 = 1;
    func_00234A60(D_002DFB4C);
}
