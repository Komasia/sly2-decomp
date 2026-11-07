struct H { int id; void *table; };
struct DIRECTION_STATE;
struct MARKER;
union PAYLOAD {
    int oid;
    struct H *curvature;
    struct DIRECTION_STATE *direction;
    void *resource;
};
struct E { int kind; union PAYLOAD value; int n8, nC; };
extern char g_sw[];
void func_0020BD88(struct H *, void *);
void ResolveK3__FP5KIND3P3ALO(struct DIRECTION_STATE *, void *);
void *PloFindSwNearest__FP2LO3OIDii(void *, int, int, void *);
int func_00132EA0(void *);
struct MARKER *PeventLaunch__FP5KINDEi(void *, int);
struct H *func_0020C010(int);
void func_0020BD78(struct H *);

// name: SafeHouse port (ResolveKinde)
void ResolveKinde__FP5KINDEP5GUARD(struct E *e, void *context)
{
    void *resource;
    if (e->kind != 2) {
        if (e->kind == 3) {
            ResolveK3__FP5KIND3P3ALO(e->value.direction, context);
            return;
        }
    } else {
        func_0020BD88(e->value.curvature, context);
        return;
    }
    resource = PloFindSwNearest__FP2LO3OIDii(g_sw, 4, e->value.oid, context);
    if (!resource) {
        e->kind = -1;
        return;
    }
    switch (func_00132EA0(resource)) {
    case 0x6D:
        if (PeventLaunch__FP5KINDEi(resource, 0x22)) {
            e->kind = 2;
            e->value.curvature = func_0020C010(0x40);
            func_0020BD78(e->value.curvature);
            e->value.curvature->table = resource;
            func_0020BD88(e->value.curvature, context);
            if (e->nC == -1)
                e->nC = 0;
        } else {
            e->value.resource = resource;
            e->kind = 0;
        }
        break;
    case 0x6F:
        e->kind = 1;
        e->value.resource = resource;
        if (e->nC == -1)
            e->nC = 0;
        break;
    default:
        e->kind = -1;
        break;
    }
}
