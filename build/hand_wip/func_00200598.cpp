typedef int qword __attribute__((mode(TI)));
struct CRef;
extern "C" {
void func_0012A0B0(CRef *,int);
void func_001291A8(CRef *,const CRef *);
CRef *func_00129658(CRef *,const CRef *);
void func_00129EC8(CRef *);
CRef func_00129D58(const CRef *);
CRef func_00129DA8(const CRef *);
CRef func_00201110(int,const CRef *,const int *,void **);
}
union TAG {int n;float f;void *pointer;};
struct CRef {
    int type;TAG tag;
    CRef(){type=-1;}
    CRef(const CRef &r){func_001291A8(this,&r);}
    CRef &operator=(const CRef &r){func_00129658(this,&r);return *this;}
    ~CRef(){func_00129EC8(this);}
    void Reset(int k){func_00129EC8(this);func_0012A0B0(this,k);}
};
struct M3 {qword rows[3];};
struct V2 {float x,y;};
struct V3 {float x,y,z;};
struct OBJECT {virtual ~OBJECT();};
union SETTER {
    int offset;
    void (OBJECT::*integer)(int);
    void (OBJECT::*scalar)(float);
    void (OBJECT::*vector)(qword);
    void (OBJECT::*matrix)(const M3 &);
    void (OBJECT::*vector4)(const qword &);
    void (OBJECT::*vector2)(const V2 &);
    void (OBJECT::*vector3)(const V3 &);
    void (OBJECT::*pointer)(void *);
};
struct PROPERTY {int type,flags;int unused8,unusedC;SETTER set;int unused18,unused1C;OBJECT *(OBJECT::*resolve)(int);};
static inline int AsInt(const CRef &r){if(r.type==0x15)return r.tag.n;CRef value;value=func_00129D58(&r);return value.tag.n;}
static inline float AsFloat(const CRef &r){if(r.type==0x16)return r.tag.f;CRef value;value=func_00129DA8(&r);return value.tag.f;}
extern "C" CRef func_00200598(OBJECT *object,PROPERTY *property,const CRef &input)
{
    CRef result;
    result.Reset(0x24);
    if(property->flags&0x10){
        if(property->flags&0x2000)object=(object->*property->resolve)(1);
        void *target=(char *)object+property->set.offset;
        result=func_00201110(1,&input,&property->type,&target);
    }else{
        if(property->flags&0x2000)object=(object->*property->resolve)(1);
        switch(property->type){
        case 5:case 6:case 7:case 8:case 13:case 14:case 15:case 16:case 17:case 19:case 20:case 23:
            (object->*property->set.integer)(AsInt(input));break;
        case 1:
            (object->*property->set.scalar)(AsFloat(input));break;
        case 0:
            (object->*property->set.pointer)(input.tag.pointer);break;
        case 2:
            (object->*property->set.vector)(*(qword *)input.tag.pointer);break;
        case 4:
            (object->*property->set.matrix)(*(M3 *)input.tag.pointer);break;
        case 9:
            (object->*property->set.vector4)(*(qword *)input.tag.pointer);break;
        case 10:
            (object->*property->set.vector2)(*(V2 *)input.tag.pointer);break;
        case 11:
            (object->*property->set.vector3)(*(V3 *)input.tag.pointer);break;
        default:
            if(property->type&0x1000)(object->*property->set.pointer)(input.tag.pointer);
            else if(property->type&0x2000)(object->*property->set.pointer)(input.tag.pointer);
            break;
        }
    }
    return result;
}
