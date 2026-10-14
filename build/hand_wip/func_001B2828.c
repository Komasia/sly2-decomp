struct CLOCK { float t; float dt; char pad[0x34]; float t3c; };
extern struct CLOCK D_002DDED0;
struct G { char pad[0x104]; struct H *x104; char pad1[4]; float f10C; unsigned packetOffset; char pad2[0x23C - 0x114]; int x23C; volatile int stage; };
struct LM{float low,high;};
struct H{char pad[8];struct LM window;};
struct DMA;struct QW{int q __attribute__((mode(TI)));};
extern struct G D_002F66B0;
extern struct DMA*D_002DE598;
int func_00234A60(int n);
void func_0016F8B8(struct DMA*,struct QW*);
void func_0016F6B8(void);
int func_0011D910(const struct LM*,float);
void func_0016F590(void);
struct DRAWVIEW{char pad[0x110];unsigned packetOffset;};
static __inline__ void Draw(struct QW*x,struct DRAWVIEW*draw)
{
    func_0016F8B8(D_002DE598, (struct QW*)(draw->packetOffset+0x41BC00));
    if (x) func_0016F8B8(D_002DE598, x);
    func_0016F590();
}
static inline unsigned AddressPage(void){unsigned page;__asm__("lui %0,%%hi(%1)":"=r"(page):"i"(&D_002F66B0));return page;}
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef char CLOCK_Size[sizeof(struct CLOCK)==64?1:-1];
typedef char G_Size[sizeof(struct G)==580?1:-1];
typedef char LM_Size[sizeof(struct LM)==8?1:-1];
typedef char H_Size[sizeof(struct H)==16?1:-1];
typedef char DRAWVIEW_Size[sizeof(struct DRAWVIEW)==276?1:-1];
typedef char QW_Size[sizeof(struct QW)==16?1:-1];
typedef char CLOCK_Align[__alignof__(struct CLOCK)==4?1:-1];
typedef char G_Align[__alignof__(struct G)==4?1:-1];
typedef char LM_Align[__alignof__(struct LM)==4?1:-1];
typedef char H_Align[__alignof__(struct H)==4?1:-1];
typedef char DRAWVIEW_Align[__alignof__(struct DRAWVIEW)==4?1:-1];
typedef char QW_Align[__alignof__(struct QW)==16?1:-1];
typedef char CLOCK_t_Offset[FIELD_OFFSET(struct CLOCK,t)==0?1:-1];
typedef char CLOCK_dt_Offset[FIELD_OFFSET(struct CLOCK,dt)==4?1:-1];
typedef char CLOCK_t3c_Offset[FIELD_OFFSET(struct CLOCK,t3c)==60?1:-1];
typedef char G_x104_Offset[FIELD_OFFSET(struct G,x104)==260?1:-1];
typedef char G_f10C_Offset[FIELD_OFFSET(struct G,f10C)==268?1:-1];
typedef char G_packetOffset_Offset[FIELD_OFFSET(struct G,packetOffset)==272?1:-1];
typedef char G_x23C_Offset[FIELD_OFFSET(struct G,x23C)==572?1:-1];
typedef char G_stage_Offset[FIELD_OFFSET(struct G,stage)==576?1:-1];
typedef char LM_low_Offset[FIELD_OFFSET(struct LM,low)==0?1:-1];
typedef char LM_high_Offset[FIELD_OFFSET(struct LM,high)==4?1:-1];
typedef char H_window_Offset[FIELD_OFFSET(struct H,window)==8?1:-1];
typedef char DRAWVIEW_packetOffset_Offset[FIELD_OFFSET(struct DRAWVIEW,packetOffset)==272?1:-1];
typedef char QW_q_Offset[FIELD_OFFSET(struct QW,q)==0?1:-1];
void func_001B2828(void)
{
    unsigned page=AddressPage();
    register struct G*g __asm__("$17");
    struct QW*x;
    __asm__("addiu %0,%1,%%lo(%2)":"=r"(g):"r"(page),"i"(&D_002F66B0));
    for (;;) {
        struct DRAWVIEW*draw=(struct DRAWVIEW*)(page+0x66B0U);
        int semaphore=g->x23C;unsigned offset;struct DMA*channel;
        g->stage=0;
        (void)func_00234A60(semaphore);
        offset=g->packetOffset;channel=D_002DE598;
        g->stage=1;
        func_0016F8B8(channel,(struct QW*)(offset+0x3F8E80));
        g->stage = 2;
        func_0016F6B8();
        if(g->x104){if(func_0011D910(&g->x104->window,D_002DDED0.t3c-g->f10C))x=(struct QW*)(g->packetOffset+0x41DC00);else x=0;}else x=0;
        Draw(x,draw);
        Draw(x,draw);
    }
}
