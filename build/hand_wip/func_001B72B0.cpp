#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; int i[4]; } U;
typedef struct { U row[3]; } M3;
typedef struct { M3 basis; U position; } M4;
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
extern "C" M4 D_002A2D30;
extern "C" M3 *func_0022FD38(M3 *,NODE *,NODE *,const M3 *);
extern "C" M4 *func_0022FF40(M4 *,NODE *,NODE *,const M4 *);
extern "C" qword func_0022FC48(NODE *,NODE *,qword);
extern "C" M4 *func_0011C318(M4 *,const M4 *);
extern "C" M4 *func_0011C168(M4 *,const M4 *,const M4 *);
extern "C" qword func_0011BFF0(const M3 *);
extern "C" M3 *func_0011B628(M3 *,qword);
extern "C" qword *func_00256D18(qword *,qword);
extern "C" void func_001B72B0(P *p,NODE *stop,const M4 *input,qword *outRotation,qword *outPosition)
{
    qword position;
    if (!p->link->pose) {
        M3 basis, temporary;
        func_0022FD38(&temporary,stop,p->link->owner->right->parent,&input->basis);
        basis=temporary;
        *outRotation=func_0011BFF0(&basis);
        position=func_0022FC48(stop,p->link->owner->left->parent,input->position.q);
    } else {
        NODE *chain[16];
        U rotation,finalPosition;
        M4 inverse,from,to,replace,result,upper,product,intermediate,combined;
        OWNER *owner=p->link->owner;
        NODE *node;
        int count=0,left=-1,right=-1,j;
        func_0011C318(&inverse,input);
        for (node=p->link->pose->first;node!=stop;node=node->parent) {
            chain[count]=node;
            if (node==owner->left) left=count;
            if (node==owner->right) right=count;
            count++;
        }
        count--;
        func_0022FF40(&from,p->link->pose->first,owner->right,&D_002A2D30);
        func_0022FF40(&to,owner->right->parent,stop,&D_002A2D30);
        func_0011C168(&replace,&from,&p->link->pose->transform);
        from=replace;
        func_0011C168(&upper,&from,&inverse);
        func_0011C168(&result,&upper,&to);
        func_0011C318(&replace,&result);
        rotation.q=func_0011BFF0(&replace.basis);
        func_0011B628(&result.basis,rotation.q);
        func_00256D18(&replace.position.q,chain[right]->local.position.q);
        replace.basis=result.basis;
        replace.basis.row[2].i[3]=replace.basis.row[1].i[3]=replace.basis.row[0].i[3]=0;
        replace.position.f[3]=1.0f;
        upper=D_002A2D30;
        result=D_002A2D30;
        j=count;
        while (j>left) {
            if (j==right) func_0011C168(&product,&result,&replace);
            else func_0011C168(&product,&result,&chain[j]->local);
            j--;
            result=product;
        }
        for (j=left-1;j>=0;j--) {
            if (j==right) func_0011C168(&product,&upper,&replace);
            else func_0011C168(&product,&upper,&chain[j]->local);
            upper=product;
        }
        func_0011C168(&product,&upper,&p->link->pose->transform);
        upper=product;
        func_0011C168(&combined,&upper,&inverse);
        func_0011C168(&intermediate,&combined,&result);
        func_0011C318(&product,&intermediate);
        finalPosition=product.position;
        if (outRotation) *outRotation=rotation.q;
        position=finalPosition.q;
    }
    if (outPosition) *outPosition=position;
}
