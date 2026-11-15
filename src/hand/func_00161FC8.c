/* func_00161FC8: the state mask bit of a task state (0 for none). */
int func_00161FC8(int nState)
{
    if (nState == -1) return 0;
    return (int)(1L << nState);
}
