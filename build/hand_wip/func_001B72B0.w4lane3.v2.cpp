#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; int i[4]; } U;
typedef struct { U row[3]; } M3;
typedef struct { M3 basis; U position; } M4;
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
typedef struct NODE { M4 local,world; char pad80[0x20]; struct NODE *parent; } NODE;
typedef struct { char pad[0x58]; NODE *left,*right; } OWNER;
typedef struct { char pad[0x50]; NODE *first; char pad54[0xC]; M4 transform; } POSE;
typedef struct { char pad[0x180]; OWNER *owner; int pad184; POSE *pose; } LINK;
typedef struct { char pad[0x13F0]; LINK *link; } P;
typedef char USize[sizeof(U)==16?1:-1];
typedef char M3Size[sizeof(M3)==48?1:-1];
typedef char M4Size[sizeof(M4)==64?1:-1];
typedef char M4_basis_Offset[FIELD_OFFSET(M4,basis)==0?1:-1];
typedef char M4_position_Offset[FIELD_OFFSET(M4,position)==48?1:-1];
typedef char NODE_local_Offset[FIELD_OFFSET(NODE,local)==0?1:-1];
typedef char NODE_world_Offset[FIELD_OFFSET(NODE,world)==64?1:-1];
typedef char NODE_parent_Offset[FIELD_OFFSET(NODE,parent)==160?1:-1];
typedef char OWNER_left_Offset[FIELD_OFFSET(OWNER,left)==88?1:-1];
typedef char OWNER_right_Offset[FIELD_OFFSET(OWNER,right)==92?1:-1];
typedef char POSE_first_Offset[FIELD_OFFSET(POSE,first)==80?1:-1];
typedef char POSE_transform_Offset[FIELD_OFFSET(POSE,transform)==96?1:-1];
typedef char LINK_owner_Offset[FIELD_OFFSET(LINK,owner)==384?1:-1];
typedef char LINK_pose_Offset[FIELD_OFFSET(LINK,pose)==392?1:-1];
typedef char P_link_Offset[FIELD_OFFSET(P,link)==5104?1:-1];
typedef char qword_Size[sizeof(qword)==16?1:-1];
typedef char int_Size[sizeof(int)==4?1:-1];
typedef char unsigned_Size[sizeof(unsigned)==4?1:-1];
typedef char short_Size[sizeof(short)==2?1:-1];
typedef char pointer_Size[sizeof(void*)==4?1:-1];
typedef char float_Size[sizeof(float)==4?1:-1];
typedef char U_Alignment[__alignof__(U)==16?1:-1];
typedef char M3_Alignment[__alignof__(M3)==16?1:-1];
typedef char M4_Alignment[__alignof__(M4)==16?1:-1];
typedef char M3_row0_Offset[FIELD_OFFSET(M3,row[0])==0?1:-1];
typedef char M3_row1_Offset[FIELD_OFFSET(M3,row[1])==16?1:-1];
typedef char M3_row2_Offset[FIELD_OFFSET(M3,row[2])==32?1:-1];
typedef char U_W_Offset[FIELD_OFFSET(U,f[3])==12?1:-1];
typedef char NODE_Prefix_Size[sizeof(NODE)==0xB0?1:-1];
typedef char OWNER_Prefix_Size[sizeof(OWNER)==0x60?1:-1];
typedef char POSE_Prefix_Size[sizeof(POSE)==0xA0?1:-1];
typedef char LINK_Prefix_Size[sizeof(LINK)==0x18C?1:-1];
typedef char P_Prefix_Size[sizeof(P)==0x13F4?1:-1];
extern "C" M4 D_002A2D30;
extern "C" M3 *func_0022FD38(M3 *,NODE *,NODE *,const M3 *);
extern "C" M4 *func_0022FF40(M4 *,NODE *,NODE *,const M4 *);
extern "C" qword func_0022FC48(NODE *,NODE *,VU_VECTOR);
extern "C" qword func_0011BFF0(const M3 *);
extern "C" M3 *func_0011B628(M3 *,VU_VECTOR);
extern "C" qword *func_00256D18(qword *,VU_VECTOR);
extern "C" M4 func_0011C318(const M4 &);
extern "C" M4*InverseInto(M4*,const M4*) __asm__("func_0011C318");
extern "C" M4 func_0011C168(const M4 &,const M4 &);
extern "C" void func_001B72B0(P *p,NODE *stop,const M4 *input,qword *outRotation,qword *outPosition)
{
    if (!p->link->pose) {
        M3 basis, temporary;
        func_0022FD38(&temporary,stop,p->link->owner->right->parent,&input->basis);
        basis=temporary;
        *outRotation=func_0011BFF0(&basis);
        *outPosition=func_0022FC48(stop,p->link->owner->left->parent,VU_VECTOR(input->position.q));
        return;
    } else {
        NODE *chain[16];
        U rotation,finalPosition;

        OWNER *owner=p->link->owner;
        NODE *node;
        int count=0,left=-1,right=-1,j;
        M4 inverse=func_0011C318(*input);M4 from,to;
        for (node=p->link->pose->first;node!=stop;node=node->parent) {
            chain[count]=node;
            if (node==owner->left) left=count;
            if (node==owner->right) right=count;
            count++;
        }
        func_0022FF40(&from,p->link->pose->first,owner->right,&D_002A2D30);
        func_0022FF40(&to,owner->right->parent,stop,&D_002A2D30);
        from=func_0011C168(from,p->link->pose->transform);
        M4 replace;
        M4 result=func_0011C168(func_0011C168(from,inverse),to);
        InverseInto(&replace,&result);
        rotation.q=func_0011BFF0(&replace.basis);
        func_0011B628(&result.basis,VU_VECTOR(rotation.q));
        func_00256D18(&replace.position.q,VU_VECTOR(chain[right]->local.position.q));
        M4 *pr = &replace;
        pr->basis = result.basis;
        replace.basis.row[0].i[3]=replace.basis.row[1].i[3]=replace.basis.row[2].i[3]=0;
        pr->position.f[3]=1.0f;
        result=D_002A2D30;
        M4 upper=D_002A2D30;
        for (int i=count-1;i>left;i--) {
            if (i==right) result=func_0011C168(result,replace);
            else result=func_0011C168(result,chain[i]->local);
        }
        for (j=left-1;j>=0;j--) {
            if (j==right) upper=func_0011C168(upper,replace);
            else upper=func_0011C168(upper,chain[j]->local);
        }
        upper=func_0011C168(upper,p->link->pose->transform);
        M4 product=func_0011C318(func_0011C168(func_0011C168(upper,inverse),result));
        finalPosition=product.position;
        if (outRotation) *outRotation=VU_VECTOR(rotation.q).q;
        if(outPosition)*outPosition=VU_VECTOR(finalPosition.q).q;
    }
}
