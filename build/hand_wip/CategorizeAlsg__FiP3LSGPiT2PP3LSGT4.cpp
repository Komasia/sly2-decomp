typedef int qword __attribute__((mode(TI)));
struct VECTOR {union{qword q;float f[4];};VECTOR(){}VECTOR(const VECTOR&v){qword t;__asm__("lq %0,%1":"=r"(t):"m"(v.q));q=t;}VECTOR&operator=(const VECTOR&v){qword t;__asm__("lq %0,%1":"=r"(t):"m"(v.q));q=t;return *this;}};
struct OWNER;
struct EDGEPREFIX{unsigned short vertices[2];};
struct LSG {
    VECTOR pos0, pos1, n0, n1;
    float g0, g1;
    int x48;
    OWNER *pv0,*pv1;
    EDGEPREFIX *edge;
    int ipos;
    LSG *plsgNext;
};
extern "C" void *func_002332B8(void *pvDst, void *pvSrc, unsigned int cb);
template <class T> inline void Swap(T &a, T &b) { T t = a; a = b; b = t; }
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0x10000)->m)-0x10000)
typedef char VECTOR_q_Offset[FIELD_OFFSET(VECTOR,q)==0?1:-1];
typedef char EDGEPREFIX_vertices_Offset[FIELD_OFFSET(EDGEPREFIX,vertices)==0?1:-1];
typedef char LSG_pos0_Offset[FIELD_OFFSET(LSG,pos0)==0?1:-1];
typedef char LSG_pos1_Offset[FIELD_OFFSET(LSG,pos1)==16?1:-1];
typedef char LSG_n0_Offset[FIELD_OFFSET(LSG,n0)==32?1:-1];
typedef char LSG_n1_Offset[FIELD_OFFSET(LSG,n1)==48?1:-1];
typedef char LSG_g0_Offset[FIELD_OFFSET(LSG,g0)==64?1:-1];
typedef char LSG_g1_Offset[FIELD_OFFSET(LSG,g1)==68?1:-1];
typedef char LSG_x48_Offset[FIELD_OFFSET(LSG,x48)==72?1:-1];
typedef char LSG_pv0_Offset[FIELD_OFFSET(LSG,pv0)==76?1:-1];
typedef char LSG_pv1_Offset[FIELD_OFFSET(LSG,pv1)==80?1:-1];
typedef char LSG_edge_Offset[FIELD_OFFSET(LSG,edge)==84?1:-1];
typedef char LSG_ipos_Offset[FIELD_OFFSET(LSG,ipos)==88?1:-1];
typedef char LSG_plsgNext_Offset[FIELD_OFFSET(LSG,plsgNext)==92?1:-1];
typedef char Size_0[sizeof(qword)==16?1:-1];
typedef char Size_1[sizeof(VECTOR)==16?1:-1];
typedef char Size_2[sizeof(EDGEPREFIX)==4?1:-1];
typedef char Size_3[sizeof(LSG)==96?1:-1];
typedef char Size_4[sizeof(unsigned short)==2?1:-1];
typedef char Size_5[sizeof(unsigned int)==4?1:-1];
typedef char Size_6[sizeof(void*)==4?1:-1];
void CategorizeAlsg(int clsg, LSG *alsg, int *pcpos, int *aipos, LSG **aplsg, LSG **pplsg)
{
    LSG *plsgFree = 0;
    int cpos = 0;
    int j;
    *pplsg = 0;
    for (int i = 0; i < clsg; i++) {
        LSG *plsg = &alsg[i];
        if(plsg->pv0){
            if(plsg->pv1){plsg->plsgNext=*pplsg;*pplsg=plsg;continue;}
            goto reverse;
        }
        if(!plsg->pv1){plsg->plsgNext=plsgFree;plsgFree=plsg;continue;}
        goto one;
    reverse:
        Swap(plsg->pos0,plsg->pos1);Swap(plsg->n0,plsg->n1);Swap(plsg->g0,plsg->g1);Swap(plsg->pv0,plsg->pv1);plsg->ipos=1;
    one:
        for (j = 0; j < cpos; j++) {
            if (plsg->edge->vertices[plsg->ipos] == aipos[j])
                break;
        }
        if (j < cpos) {
            plsg->plsgNext = aplsg[j];
        } else {
            aipos[j] = plsg->edge->vertices[plsg->ipos];
            cpos++;
        }
        aplsg[j] = plsg;
    }
    for (j = 0; j < cpos; j++) {
        LSG *p;
        if (aplsg[j]->plsgNext)
            continue;
        for (p = plsgFree; p; p = p->plsgNext) {
            if (p->edge->vertices[0] == aipos[j] || p->edge->vertices[1] == aipos[j])
                goto next;
        }
        aplsg[j]->plsgNext = *pplsg;
        *pplsg = aplsg[j];
        func_002332B8(&aplsg[j], &aplsg[j + 1], (cpos - j - 1) * 4);
        func_002332B8(&aipos[j], &aipos[j + 1], (cpos - j - 1) * 4);
        j--;
        cpos--;
    next:;
    }
    *pcpos = cpos;
}
