struct SLOT { int plo; int a[11]; };
struct SPAWNER { char pad[0x5C]; int cslot; struct SLOT *aslot; };
void OnLoRemove__FP2LO(struct SPAWNER *pspawner);
void ReleaseSlot__FP7SPAWNERP4SLOTii(struct SPAWNER *pspawner, struct SLOT *pslot, int a, int b);
/* OnRemoveSpawner: when a spawner leaves the world, release its used slots. */
// name: SafeHouse port (OnRemoveSpawner)
void OnRemoveSpawner__FP2LO(struct SPAWNER *pspawner) {
    int i;
    OnLoRemove__FP2LO(pspawner);
    if (!pspawner->aslot) return;
    for (i = 0; i < pspawner->cslot; i++) {
        struct SLOT *pslot = &pspawner->aslot[i]; if (pslot->plo) ReleaseSlot__FP7SPAWNERP4SLOTii(pspawner, pslot, 0, 0);
    }
}
