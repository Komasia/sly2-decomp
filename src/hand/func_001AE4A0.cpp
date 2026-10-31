/* STACKSCOPE::~STACKSCOPE (0x1AE4A0): pop the stack-heap frame (g++ adds the delete of a heap object). */
#include "stackscope.h"

STACKSCOPE::~STACKSCOPE()
{
    FreeStackImpl();
}
