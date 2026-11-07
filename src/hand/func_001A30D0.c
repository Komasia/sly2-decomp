struct VTE { short d; short pad; void (*pfn)(void *); };
struct O { char pad[0xC]; struct VTE *vt; };
struct S { struct O *po; };
// name: SafeHouse port (HideSubtitleBox)
void HideSubtitleBox__FP9DIALOGSUB(struct S *p) { struct O *o = p->po; if (o) { struct VTE *e = &o->vt[50]; e->pfn((char *)o + e->d); } }
