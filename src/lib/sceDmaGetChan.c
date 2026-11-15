// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* sceDmaGetChan (libdma): register block of DMA channel `id` (0..9), or 0. */
extern void *_sceDmaChans[10];
void *sceDmaGetChan(int id)
{
    return (unsigned)id < 10 ? _sceDmaChans[id] : 0;
}
