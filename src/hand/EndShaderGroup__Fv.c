/* EndShaderGroup (after a group's objects are loaded): the group's tables of CLUTs, BMPs, shader animations and
 * shaders forgotten (each a count and an array); the records live on. Source: SafeHouse port (shd.cpp). */
extern int D_003DCFE8;   /* the shader animations or the shaders (count, array) */
extern int D_003DCFEC;
extern int D_003DCFF0;   /* the BMPs (count, array; see RelocateBulkRecords) */
extern int D_003DCFF4;
extern int D_003DCFF8;   /* the CLUTs (count, array) */
extern int D_003DCFFC;
extern int D_003DD000;   /* the shaders or the shader animations (count, array) */
extern int D_003DD004;

// name: SafeHouse port (EndShaderGroup)
void EndShaderGroup__Fv(void)
{
    D_003DCFE8 = 0;
    D_003DCFEC = 0;
    D_003DCFF0 = 0;
    D_003DCFF4 = 0;
    D_003DCFF8 = 0;
    D_003DCFFC = 0;
    D_003DD000 = 0;
    D_003DD004 = 0;
}
