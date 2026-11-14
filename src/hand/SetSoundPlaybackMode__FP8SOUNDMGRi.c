/* SetSoundPlaybackMode: change the sound manager's playback mode (+0x104) and tell the IOP side (snd_SetPlaybackMode). */
struct SOUNDMGR {
    /* 0x000 */ char pad0[0x104];
    /* 0x104 */ int playbackMode;   /* field: SafeHouse port */
};
void snd_SetPlaybackMode(int playbackMode);

// name: SafeHouse port (SetSoundPlaybackMode)
void SetSoundPlaybackMode__FP8SOUNDMGRi(struct SOUNDMGR *psoundmgr, int playbackMode)
{
    if (psoundmgr->playbackMode != playbackMode) {
        psoundmgr->playbackMode = playbackMode;
        snd_SetPlaybackMode(playbackMode);
    }
}
