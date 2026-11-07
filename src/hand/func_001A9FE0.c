struct O { char pad[0xAC]; struct O *next; };
// name: SafeHouse port (PrependXpList)
void PrependXpList__FP2XPPP2XPPv(void *unused, struct O *b, struct O **pp)
{
    if (b) {
        struct O *last = b;
        while (last->next) last = last->next;
        last->next = *pp;
        *pp = b;
    }
}
