struct EMITTER { char pad[0xE0]; int fDirty; char pad2[0xC]; int k; int c; };
void PauseEmitterIndefinite(EMITTER *pemitter);
void UnpauseEmitter(EMITTER *pemitter);
void SetEmitterParticleCount(EMITTER *pemitter, int c)
{
    switch (pemitter->k) {
    case 0:
        if (c == 0)
            PauseEmitterIndefinite(pemitter);
        else if (c == -1)
            UnpauseEmitter(pemitter);
        else
            pemitter->c = c;
        break;
    case -1:
        pemitter->c = c;
        break;
    }
    pemitter->fDirty = 1;
}
