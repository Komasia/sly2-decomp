struct S { char pad[0x3B8]; int fl; };
// name: SafeHouse port (CSndVoice::Kind)
int Kind__9CSndVoice(struct S *p) { return (p->fl & 4) ? 2 : 1; }
