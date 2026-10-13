struct E;
struct O { char pad[0x40]; struct E *e; };
struct E { unsigned int grf; struct O *o; };
struct G { char pad[0x3F14]; int count; int dead; int *index; struct E *array; };
void func_00210140(struct G *g, struct O *o)
{
    struct E *e;
    if ((unsigned int)o->e & 0x40)
        return;
    if (g->count >= 0x1000 || (float)g->dead / (float)g->count > 0.1f) {
        struct E *end = g->array + g->count;
        struct E *tracked;
        struct E *write;
        struct E *read;
        if (g->index)
            tracked = g->array + *g->index;
        else
            tracked = 0;
        write = g->array;
        for (read = g->array; read < end; read++) {
            if (read == tracked)
                tracked = write;
            if (read->o) {
                read->o->e = write;
                *write++ = *read;
            }
        }
        g->dead = 0;
        g->count = write - g->array;
        if (g->index)
            *g->index = tracked - g->array;
    }
    e = &g->array[g->count++];
    e->o = o;
    e->grf = (unsigned int)o->e;
    o->e = e;
}
