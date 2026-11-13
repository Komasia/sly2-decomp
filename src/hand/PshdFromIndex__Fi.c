/* PshdFromIndex: the shader at an index of the world's shader array (D_003DCFEC, 0x2C bytes each). */
struct SHD {
    char ab[0x2c];
};
extern struct SHD *D_003DCFEC;   /* the shaders */

// name: SafeHouse port (PshdFromIndex)
struct SHD *PshdFromIndex__Fi(int ishd)
{
    return &D_003DCFEC[ishd];
}
