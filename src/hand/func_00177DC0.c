struct AIMSG { int kind; int pad4[3]; int n; int pad14[2]; int n1C; };
/* FSameMsg: whether two reaction messages are the same: the kind, and by kind the hit (+0x1C) or the argument
 * (+0x10). */
// name: SafeHouse port (FSameMsg)
int FSameMsg__FP5AIMSGT0(struct AIMSG *paimsg1, struct AIMSG *paimsg2) {
    if (paimsg1->kind != paimsg2->kind) return 0;
    switch (paimsg1->kind) {
    case 9: case 10: case 11: return paimsg1->n1C == paimsg2->n1C;
    case 4: return paimsg1->n == paimsg2->n;
    case 5: return paimsg1->n == paimsg2->n;
    case 3: return paimsg1->n == paimsg2->n;
    case 13: return paimsg1->n == paimsg2->n;
    case 2: return paimsg1->n == paimsg2->n;
    case 14: return paimsg1->n == paimsg2->n;
    case 18: return paimsg1->n == paimsg2->n;
    case 6: return paimsg1->n == paimsg2->n;
    }
    return 1;
}
