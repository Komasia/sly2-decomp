/* GrfActorStance: the actor's contact stance flags: 0 with +0x204 set; 4 in interaction states 3 / 4; 1 in a jump;
 * by the damage state: 7 when not hurt (-1, 0, 6), 1 in states 4, 7, 8, 12; else 0. */
// name: SafeHouse port (GrfActorStance)
int GrfActorStance__FP5ACTOR(char *pactor)
{
    if (*(int *)(pactor + 0x204)) return 0;
    switch (*(int *)(pactor + 0x4C8)) {
    case 3:
    case 4:
        return 4;
    }
    if (*(int *)(pactor + 0x2DC) != -1) return 1;
    switch (*(int *)(pactor + 0xDF4)) {
    case -1:
    case 0:
    case 6:
        return 7;
    case 4:
    case 7:
    case 8:
    case 12:
        return 1;
    }
    return 0;
}
