/* ShutdownSwSplice: the world has no script table any more (SW +0x3A14). */
struct SW {
    /* 0x0000 */ char pad0[0x3A14];
    /* 0x3a14 */ void *psplicetable;   /* the current script table (LoadSwSpliceFromBrx) */
};

// name: SafeHouse port (ShutdownSwSplice)
void ShutdownSwSplice__FP2SW(struct SW *psw)
{
    psw->psplicetable = 0;
}
