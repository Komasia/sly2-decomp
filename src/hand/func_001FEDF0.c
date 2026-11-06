void SetSoundMasterVolume__FP8SOUNDMGRf(void *, float);
void SetSoundChannelVolume__FP8SOUNDMGRiif(void *, int, int, float);
// name: SafeHouse port (ResetSoundVolumes)
void ResetSoundVolumes__FPv(void *p)
{
    int i, j;
    SetSoundMasterVolume__FP8SOUNDMGRf(p, 1.0f);
    for (i = 0; i < 8; i++) {
        if (i == 1) continue;
        for (j = 0; j < 4; j++) SetSoundChannelVolume__FP8SOUNDMGRiif(p, j, i, 1.0f);
    }
}
