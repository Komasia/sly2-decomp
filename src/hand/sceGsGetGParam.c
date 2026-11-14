/* sceGsGetGParam (0x2405F0; libgraph): the address of the static graphics parameters (D_002C66F0); sceGsResetGraph,
 * sceGsPutDispEnv and sceGsSetDefDBuff call it by this name in src/lib. */
// name: libgraph (sceGsGetGParam, the public API; src/lib's libgraph functions already call it by name)
extern char D_002C66F0[];   /* sceGsGParam */

void *sceGsGetGParam(void)
{
    return D_002C66F0;
}
