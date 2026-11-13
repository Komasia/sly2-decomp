/* PostLoadBinoc: the binoculars' post-load is their BINOC record's (+0x24, func_0019D540). */
struct ACTOR;
struct BINOC;
void func_0019D540(struct BINOC *pbinoc);

// name: SafeHouse port (PostLoadBinoc)
void PostLoadBinoc__FP5ACTOR(struct ACTOR *pactor)
{
    func_0019D540((struct BINOC *)((char *)pactor + 0x24));
}
