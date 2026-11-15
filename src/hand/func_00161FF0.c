/* func_00161FF0: the state mask of a list of task states. */
int func_00161FC8(int nState);
int func_00161FF0(int cnState, int *anState)
{
    int grfState = 0;
    int i;
    for (i = 0; i < cnState; i++)
        grfState |= func_00161FC8(anState[i]);
    return grfState;
}
