/* class: a reference-counted Splice pointer (the CRefPtr<T>::operator= copies; this one for a CProc's frame (RefEvalLambda, CProc::CloneTo)): the new object's
 * count (its first word) raised and the pointer set; the old one is not released here. */
typedef struct REFC { int cref; } REFC;

void func_00257038(REFC **pp, REFC *p)
{
    if (p != 0) {
        p->cref++;
    }
    *pp = p;
}
