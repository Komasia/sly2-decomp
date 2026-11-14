/* class: a reference-counted Splice pointer (the CRefPtr<T>::operator= copies; this one for a CFrame (RefEvalApply, CFrame::CloneTo, RunDeferredSpliceEvents)): the new object's
 * count (its first word) raised and the pointer set; the old one is not released here. */
typedef struct REFC { int cref; } REFC;

void func_00257058(REFC **pp, REFC *p)
{
    if (p != 0) {
        p->cref++;
    }
    *pp = p;
}
