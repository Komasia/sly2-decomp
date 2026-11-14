/* class: CSndVoice: a slot for a new one from its slot heap D_003DD074 (PsndNewVoice calls it; the size argument is unused). */
#include "slotheap.h"

extern SLOTHEAP D_003DD074;
void *func_0011CCC0(SLOTHEAP *pslotheap);

void *func_001FCCF0(int cb)
{
    return func_0011CCC0(&D_003DD074);
}
