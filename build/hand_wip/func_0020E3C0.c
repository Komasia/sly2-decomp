typedef struct KEY KEY;
typedef struct CRef { int tagk,tag; } CRef;

CRef *func_001291A8(CRef *, const CRef *);
void func_00129EC8(void *);
KEY *func_001D88D0(const char *, ...);
int func_00210A88();
int func_00210AE0();
int func_00210B28();
void func_001619A0(void *, int, void *);
typedef struct S {
    char pad[0x3B1C];
    KEY *dt,*coins,*world,*episode;
    KEY *settings[11];
    KEY *levelDt[9];
    KEY *levelPercent[9];
} S;
extern char D_003D4A60[],D_002DEB30[];
extern int D_002E1E54;
extern char D_002A8968[],D_002A8970[],D_002A8980[],D_002A8990[],D_002A8998[],D_002A89A0[],D_002A89A8[],D_002A89B0[],D_002A89C0[],D_002A89D0[],D_002A89E0[],D_002A89F0[],D_002A8A00[],D_002A8A10[],D_002A8A20[],D_002A8A38[],D_002A8A48[],D_002A8A58[],D_002A8A60[],D_002A8A78[];
extern char *D_002A39E8[9];
CRef *func_00258200(CRef *,KEY *,const CRef *,void *);
CRef *func_001D8B20(CRef *,const CRef *,const char *,...);
void func_0020E3C0(S *p) {
    CRef input,result;
    register CRef *out asm("s4")=&result;
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
    {
        KEY **key=p->levelPercent;
        char **names=D_002A39E8;
        int i;
        for(i=8;i>=0;--i) {
            key[-9]=func_001D88D0(D_002A8A58,*names,D_002A8968,0);
            *key=func_001D88D0(D_002A8A58,*names,D_002A8A60,0);
            ++key;
            ++names;
        }
    }
    {
        CRef copy;
        KEY *key;
        int value=D_002E1E54;
        input.tagk=0x15;
        input.tag=value;
        key=p->settings[0];
        func_001291A8(&copy,&input);
        func_00258200(out,key,&copy,D_003D4A60);
        func_00129EC8(out);
        func_00129EC8(&copy);
        func_00129EC8(&input);
    }
    {
        CRef copy;
        KEY *key;
        int value=func_00210A88();
        input.tagk=0x15;
        input.tag=value;
        key=p->world;
        func_001291A8(&copy,&input);
        func_00258200(out,key,&copy,D_003D4A60);
        func_00129EC8(out);
        func_00129EC8(&copy);
        func_00129EC8(&input);
    }
    {
        CRef copy;
        KEY *key;
        int value=func_00210AE0();
        input.tagk=0x15;
        input.tag=value;
        key=p->episode;
        func_001291A8(&copy,&input);
        func_00258200(out,key,&copy,D_003D4A60);
        func_00129EC8(out);
        func_00129EC8(&copy);
        func_00129EC8(&input);
    }
    {
        int episode=func_00210AE0();
        if(func_00210B28()<episode) {
            CRef copy;
            int e=func_00210AE0();
            copy.tagk=0x15;
            copy.tag=e;
            func_001D8B20(&input,&copy,D_002A8A78,0);
            func_00129EC8(&input);
            func_00129EC8(&copy);
        }
    }
    func_001619A0(D_002DEB30,3,0);
}
