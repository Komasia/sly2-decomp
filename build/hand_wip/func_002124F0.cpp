typedef struct {int a[4];} FRAME;
typedef struct {int cb,kind;} MSG;
typedef struct {char pad[0x70];} BIS;
typedef struct {int a,b,kind;char pad[0x104];} KEY;
typedef union {MSG msg;char magic[4];} TMP;
typedef struct S S;
typedef struct N {int a,b;char pad8[0x2C];int c;int pad38;int d;S *owner;int priority,last;struct N *next;} N;
struct S {char pad[0x50];int count;void *data;int state;char pad5c[4];int tick;char pad64[0x5C];N *file;};
typedef struct {char pad[0xC];int priority;} POOL;
extern "C" FRAME *func_001AE478(FRAME *);
extern "C" void func_001AE4A0(FRAME *,int);
extern "C" BIS *func_001848A8(BIS *,int,void *,int);
extern "C" void func_00184950(BIS *,int);
extern "C" void func_00258248(KEY *);
extern "C" void *func_001AE318(MSG *);
extern "C" int func_00184D60(BIS *,KEY *);
extern "C" void func_001179D8(BIS *,int,void *);
extern "C" unsigned char func_00117BD0(BIS *);
extern "C" int func_00117C20(BIS *);
extern "C" int func_00233470(const void *,const void *,int);
extern "C" void func_00212A70(S *,int);
extern "C" void func_00214398(S *,BIS *,S *,int *,void **);
extern "C" void func_00214460(S *,BIS *,S *);
extern N *D_003E106C;
extern POOL D_003E1C70;
extern int D_002BE538;
extern char D_002A8AE8[];
static inline int Max(int a,int b) {return a<b?b:a;}
static inline int SetKey(KEY *k,N *n) {
    if(!n)return 0;
    {int a=n->c,b=n->a,c=n->d,d=n->b;
    k->kind=2;
    k->a=(b^a)+0xCA0;
    k->b=d^c;}
    return k->b!=0;
}
extern "C" void func_002124F0(S *p) {
    FRAME frame;
    TMP tmp;
    BIS stream;
    KEY key;
    int priority=0;
    N *n;
    S *owner;
    int version;
    for(n=D_003E106C;n;n=n->next) {
        owner=n->owner;
        if(owner->state==0)continue;
        if(owner->state==1 && D_002BE538-owner->tick>=2)continue;
        priority=Max(priority,n->last);
    }
    for(n=D_003E106C;n;n=n->next) {
        owner=n->owner;
        if(n->priority>=priority && owner->state!=0)func_00212A70(owner,0);
    }
    D_003E1C70.priority=priority;
    func_001AE478(&frame);
    BIS *bs=&stream;
    KEY *pk=&key;
    MSG *msg=&tmp.msg;

    msg->cb=0x10000;msg->kind=0x40;
    func_001848A8(bs,0x10000,func_001AE318(msg),0);
    pk->kind=2;
    func_00258248(pk);
    if(!SetKey(&key,p->file)||!func_00184D60(bs,pk))goto fail;
    func_001179D8(bs,0x4000,(void *)0x70000000);
    tmp.magic[0]=func_00117BD0(bs);
    tmp.magic[1]=func_00117BD0(bs);
    tmp.magic[2]=func_00117BD0(bs);
    tmp.magic[3]=func_00117BD0(bs);
    version=func_00117C20(bs);
    if(!func_00233470(tmp.magic,D_002A8AE8,4)&&version==6)goto load;
fail:
    func_00184950(bs,2);
    func_001AE4A0(&frame,2);
    return;
load:
    p->file->priority=D_003E1C70.priority;
    func_00214398(p,bs,p,&p->count,&p->data);
    func_00214460(p,bs,p);
    p->file->last=D_003E1C70.priority;
    func_00184950(bs,2);
    func_001AE4A0(&frame,2);
}
