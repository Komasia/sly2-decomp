/* FUN_0018b910 (0x1AAB48): a memory card result's message id: 0x1D for 0, 0x1E for a positive result, 0x1F for a
 * negative one. */
int FUN_0018b910(int n)
{
    if (n != 0) return n <= 0 ? 0x1F : 0x1E;
    return 0x1D;
}
