/* AddRefAsega: one more reference to an animation segment player (released by ReleaseAsega). */
#include "asega.h"

// name: SafeHouse port (AddRefAsega)
void AddRefAsega__FP5ASEGA(ASEGA *pasega)
{
    pasega->cref++;
}
