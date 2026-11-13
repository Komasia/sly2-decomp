/* PshdOfId: the shader draw record of an id (0x1EC880 over the shaders flagged 0x40), else the first one
 * (D_003E1590). Source: SafeHouse port (emitter.cpp). */
struct SHD;
extern struct SHD *D_003E1590;   /* the first draw record */
struct SHD *func_001EC880(int id);

// name: SafeHouse port (PshdOfId)
struct SHD *PshdOfId__Fi(int id)
{
    struct SHD *pshd = func_001EC880(id);
    if (pshd == 0)
        pshd = D_003E1590;
    return pshd;
}
