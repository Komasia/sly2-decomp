struct Q { char pad[0x4C]; int st; };
struct S { char pad[0x17C]; struct Q *pq; };
void func_001E8378(struct Q *q);
void func_001E9090(struct Q *q);
void func_001A5E80(struct S *p);
void func_001E6340(struct S *p)
{
    if (p->pq) {
        switch (p->pq->st) {
        case 0:
        case 3:
            func_001E8378(p->pq);
            break;
        case 1:
        case 2:
            func_001E9090(p->pq);
            break;
        }
    } else {
        func_001A5E80(p);
    }
}
