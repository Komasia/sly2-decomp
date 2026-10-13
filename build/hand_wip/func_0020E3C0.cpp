struct KEY;
extern "C" {
void func_001291A8(void *, const void *);
void func_00129EC8(void *);
KEY *func_001D88D0(void *, ...);
int func_00210A88();
int func_00210AE0();
int func_00210B28();
void func_001619A0(void *, int, void *);
}
struct CRef {
    int tagk, tag;
    CRef(int n) { tagk=0x15; tag=n; }
    CRef(const CRef &r) { func_001291A8(this,&r); }
    ~CRef() { func_00129EC8(this); }
};
struct S {
    char pad[0x3B1C];
    KEY *dt,*coins,*world,*episode;
    KEY *settings[11];
    KEY *levelDt[9];
    KEY *levelPercent[9];
};
extern char D_003D4A60[],D_002DEB30[];
extern int D_002E1E54;
extern char D_002A8968[],D_002A8970[],D_002A8980[],D_002A8990[],D_002A8998[],D_002A89A0[],D_002A89A8[],D_002A89B0[],D_002A89C0[],D_002A89D0[],D_002A89E0[],D_002A89F0[],D_002A8A00[],D_002A8A10[],D_002A8A20[],D_002A8A38[],D_002A8A48[],D_002A8A58[],D_002A8A60[],D_002A8A78[];
extern char *D_002A39E8[9];
extern "C" CRef func_00258200(KEY *,const CRef &,void *);
extern "C" CRef func_001D8B20(const CRef &,const char *,...);
static inline void Set(KEY *key,CRef value,void *context) {
    func_00258200(key,value,context);
}
extern "C" void func_0020E3C0(S *p) {
    p->dt=func_001D88D0(D_002A8968,0);
    p->world=func_001D88D0(D_002A8970,0);
    p->episode=func_001D88D0(D_002A8980,0);
    p->coins=func_001D88D0(D_002A8990,D_002A8998,0);
    p->settings[0]=func_001D88D0(D_002A89A0,D_002A89A8,0);
    p->settings[1]=func_001D88D0(D_002A89A0,D_002A89B0,0);
    p->settings[2]=func_001D88D0(D_002A89A0,D_002A89C0,0);
    p->settings[3]=func_001D88D0(D_002A89A0,D_002A89D0,0);
    p->settings[4]=func_001D88D0(D_002A89A0,D_002A89E0,0);
    p->settings[5]=func_001D88D0(D_002A89A0,D_002A89F0,0);
    p->settings[6]=func_001D88D0(D_002A89A0,D_002A8A00,0);
    p->settings[7]=func_001D88D0(D_002A89A0,D_002A8A10,0);
    p->settings[8]=func_001D88D0(D_002A89A0,D_002A8A20,0);
    p->settings[9]=func_001D88D0(D_002A89A0,D_002A8A38,0);
    p->settings[10]=func_001D88D0(D_002A89A0,D_002A8A48,0);
    KEY **key=p->levelPercent;
    char **names=D_002A39E8;
    for(int i=8;i>=0;--i) {
        key[-9]=func_001D88D0(D_002A8A58,*names,D_002A8968,0);
        *key=func_001D88D0(D_002A8A58,*names,D_002A8A60,0);
        ++key;
        ++names;
    }
    { CRef r(D_002E1E54); Set(p->settings[0],r,D_003D4A60); }
    { CRef r(func_00210A88()); Set(p->world,r,D_003D4A60); }
    { CRef r(func_00210AE0()); Set(p->episode,r,D_003D4A60); }
    int episode=func_00210AE0();
    if(func_00210B28()<episode)
        func_001D8B20(CRef(func_00210AE0()),D_002A8A78,0);
    func_001619A0(D_002DEB30,3,0);
}
