/* OSTRM::~OSTRM (Sly 1 stream.c): the buffered rest written out. */
#include "stream.h"

OSTRM::~OSTRM() { Flush(); }
