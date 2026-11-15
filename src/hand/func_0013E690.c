/* RefReadOption: an option value read as a CRef by its OTYP kind: 0 bool (U8), 5 / 6 S32, 1 F32, 7, 14-17, 19-21, 23
 * S16 ids, 9 a CLQ (3 F32), 10 an LM (2 F32), 2 a vector (3 F32); a U32 for the kinds 0x1000..0x1FFF (bit 0x8000
 * aside); anything else void. TAGK 0x15 is S32. SafeHouse port (lo.h OPTVAL). */
typedef struct CRef { int m_tagk; union { int n; float g; } u; } CRef;
int U8Read(void *pbs) asm("U8Read__18CBinaryInputStream");
int S32Read(void *pbs) asm("S32Read__18CBinaryInputStream");
float F32Read(void *pbs) asm("F32Read__18CBinaryInputStream");
int S16Read(void *pbs) asm("S16Read__18CBinaryInputStream");
int U32Read(void *pbs) asm("U32Read__18CBinaryInputStream");
void func_00129330(CRef *ret, float *ag);   /* a CLQ CRef */
void func_00129398(CRef *ret, float *ag);   /* an LM CRef */
void func_001291E0(CRef *ret, float *ag);   /* a vector CRef */
void InitTag(CRef *ret, int tagk) asm("InitTag__4CRef");
// name: SafeHouse port (RefReadOption)
CRef *RefReadOption__FiP18CBinaryInputStream(CRef *ret, int otyp, void *pbs)
{
    float ag[3];
    switch (otyp) {
    case 0:
        {
            int f = U8Read(pbs) != 0;
            ret->m_tagk = 0x17;   /* TAGK_Bool */
            ret->u.n = f;
        }
        break;
    case 5: case 6:
        ret->u.n = S32Read(pbs);
        ret->m_tagk = 0x15;
        break;
    case 1:
        ret->u.g = F32Read(pbs);
        ret->m_tagk = 0x16;   /* TAGK_F32 */
        break;
    case 7: case 14: case 15: case 16: case 17: case 19: case 20: case 21: case 23:
        ret->u.n = S16Read(pbs);
        ret->m_tagk = 0x15;
        break;
    case 9:
        {
            float *pg = ag;
            int j;
            for (j = 0; j < 3; j++)
                *pg++ = F32Read(pbs);
        }
        func_00129330(ret, ag);
        break;
    case 10:
        ag[0] = F32Read(pbs);
        ag[1] = F32Read(pbs);
        func_00129398(ret, ag);
        break;
    case 2:
        {
            float *pg = ag;
            int j;
            for (j = 0; j < 3; j++)
                *pg++ = F32Read(pbs);
        }
        func_001291E0(ret, ag);
        break;
    default:
        if (((otyp & ~0x8000) >> 12) == 1) {
            ret->u.n = U32Read(pbs);
            ret->m_tagk = 0x15;
        } else {
            InitTag(ret, 0x24);   /* TAGK_Void */
        }
        break;
    }
    return ret;
}
