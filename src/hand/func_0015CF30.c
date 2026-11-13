// (Claude agent) UpdateEpMenu__FP6EPMENU: UI menu state machine. FSpriteAnimPlaying__FP2LOi takes (p, r) with r = IdPartCur__FP6EPMENU(p); the n12C==0 flag uses a shared "setf: f = 1" block (reorg fills both beql/bnel slots from it).
struct CRef { int m_tagk; int m_n; };
struct CRefG { int m_tagk; float m_g; };
struct X {
    char pad[0x110]; int n110; int n114; int n118; int n11C; int n120; int pad124; int n128; int n12C; float g130;
};
struct G { char pad[0x3B58]; void *a3B58[9]; void *a3B7C[9]; };
extern struct G g_sw;
extern char D_003D4A60[];
extern char D_003D9ED0[], D_002E6550[], D_003DA4F0[];
extern char g_joy[];
extern char D_002F66B0[];
extern float D_002DDF0C;
extern int D_002BE248[];
extern int D_002BE26C;
extern int D_002BE270;
extern int D_002BE200[];
extern int D_002BE278[];
extern int D_002BE2A8[];
void func_00212C50(struct X *p);
int func_001D9880(void *p);
int IdPartCur__FP6EPMENU(struct X *p);
int func_001880D8(void *p);
int func_00187D80(void *p, int n);
int func_00187E88(void *p);
void SetEpMode__FP6EPMENUii(struct X *p, int a, int b);
void NProgress(void *pref, void *p, void *q);
void Decref(void *pref) asm("Decref__4CRef");
void SetHint__FP6EPMENUi(struct X *p, int n);
void QueueMovie__FPUcPv(void *p, int n);
void RequestTransition__FP2SWPUc3OIDT2iT2(struct G *pg, int a, int b, int c, int d, int e);
void *PsndNewPlain__Fi(int n);
void SetSource__4CSndPv(void *p, int n);
int CmovieOpen__FP6EPMENU(struct X *p);
int FSpriteAnimPlaying__FP2LOi(struct X *p, int n);
void *PloFindSwNearest__FP2LO3OIDii(struct G *pg, int kind, int oid, int n);
void SetExitState__FP2LOi(void *p, int n);
void TriggerExit__FP4EXIT(void *p);
int func_00210B98(int n);

static __inline__ void PlaySound(int n)
{
    SetSource__4CSndPv(PsndNewPlain__Fi(n), 0);
}

// name: SafeHouse port (UpdateEpMenu)
void UpdateEpMenu__FP6EPMENU(struct X *p)
{
    int r;
    func_00212C50(p);
    if (func_001D9880(D_003D9ED0))
        return;
    if (func_001D9880(D_002E6550))
        return;
    if (func_001D9880(D_003DA4F0))
        return;
    r = IdPartCur__FP6EPMENU(p);
    switch (p->n11C) {
    case -1:
        return;
    case 2: {
        float g = func_001880D8(g_joy);
        if (g < 0.0f && p->n110 <= 0) {
            PlaySound(0x36);
            return;
        }
        if (0.0f < g && p->n110 >= p->n118) {
            PlaySound(0x36);
            return;
        }
        if (g != 0.0f) {
            if (g < 0.0f)
                p->n114 = p->n110 - 1;
            else
                p->n114 = p->n110 + 1;
            SetEpMode__FP6EPMENUii(p, 0.0f < g ? 4 : 6, -1);
            return;
        }
        if (func_00187D80(g_joy, 0x40)) {
            SetEpMode__FP6EPMENUii(p, 7, -1);
            return;
        }
        if (p->n110 && func_00187D80(g_joy, 0x10)) {
            p->n114 = 0;
            SetEpMode__FP6EPMENUii(p, 6, -1);
            return;
        }
        switch (p->n12C) {
        case 0: {
            int c;
            int f = 0;
            int n = D_002BE248[p->n110];
            void *pv = g_sw.a3B7C[p->n110];
            if (pv) {
                struct CRef ref;
                NProgress(&ref, pv, D_003D4A60);
                c = ref.m_n;
                Decref(&ref);
                if (c >= 100)
                    goto setf;
            }
            if (D_002BE26C) {
            setf:
                f = 1;
            }
            if (n && f && 10.0f < D_002DDF0C - p->g130)
                SetHint__FP6EPMENUi(p, 1);
            return;
        }
        case 1:
            if (func_00187D80(g_joy, 0x80)) {
                QueueMovie__FPUcPv(D_002F66B0, D_002BE248[p->n110]);
                RequestTransition__FP2SWPUc3OIDT2iT2(&g_sw, 0, 0x189, -1, 0, -1);
                PlaySound(0x34);
                return;
            }
            if (2.0f < D_002DDF0C - p->g130)
                SetHint__FP6EPMENUi(p, 0);
            return;
        }
        return;
    }
    case 8:
        switch (p->n120) {
        case -1:
            if (func_00187D80(g_joy, 0x40))
                SetEpMode__FP6EPMENUii(p, 10, -1);
            else if (func_00187D80(g_joy, 0x10))
                SetEpMode__FP6EPMENUii(p, 9, -1);
            return;
        case 0: {
            float g;
            if (func_00187D80(g_joy, 0x40)) {
                D_002BE270 = p->n128;
                QueueMovie__FPUcPv(D_002F66B0, D_002BE200[p->n128]);
                RequestTransition__FP2SWPUc3OIDT2iT2(&g_sw, 0, 0x189, -1, 0, -1);
                PlaySound(0x34);
                return;
            }
            if (func_00187D80(g_joy, 0x10)) {
                SetEpMode__FP6EPMENUii(p, 9, -1);
                return;
            }
            g = func_00187E88(g_joy);
            if (g < 0.0f && p->n128 <= 0) {
                PlaySound(0x36);
                return;
            }
            if (0.0f < g && p->n128 >= CmovieOpen__FP6EPMENU(p)) {
                PlaySound(0x36);
                return;
            }
            if (g != 0.0f) {
                if (g < 0.0f)
                    p->n128 = p->n128 - 1;
                else
                    p->n128 = p->n128 + 1;
                SetEpMode__FP6EPMENUii(p, 8, 0.0f < g ? 2 : 1);
            }
            return;
        }
        case 1:
        case 2:
            if (!FSpriteAnimPlaying__FP2LOi(p, r))
                SetEpMode__FP6EPMENUii(p, 8, 0);
            return;
        }
        return;
    case 10:
        if (!FSpriteAnimPlaying__FP2LOi(p, r)) {
            int f = 0;
            void *pv = g_sw.a3B58[p->n110];
            if (pv) {
                struct CRefG ref;
                float g;
                f = 1;
                NProgress(&ref, pv, D_003D4A60);
                g = ref.m_g;
                Decref(&ref);
                if (g != 0.0f)
                    f = 0;
            }
            if (f) {
                void *po = PloFindSwNearest__FP2LO3OIDii(&g_sw, 5, D_002BE2A8[p->n110], 0);
                if (po) {
                    SetExitState__FP2LOi(po, 3);
                    TriggerExit__FP4EXIT(po);
                } else
                    f = 0;
            }
            if (!f) {
                int s = func_00210B98(p->n110);
                RequestTransition__FP2SWPUc3OIDT2iT2(&g_sw, s, 0x189, -1, 0, 0x30A);
            }
            SetEpMode__FP6EPMENUii(p, -1, -1);
        }
        return;
    default:
        if (!FSpriteAnimPlaying__FP2LOi(p, r)) {
            int k = D_002BE278[p->n11C];
            int n = -1;
            if (k == 8 && p->n110 == 0) {
                p->n128 = 0;
                n = 0;
            }
            SetEpMode__FP6EPMENUii(p, k, n);
        }
        return;
    }
}
