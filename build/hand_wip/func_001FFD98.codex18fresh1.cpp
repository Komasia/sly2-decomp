// Read an offset field or invoke the corresponding reflected getter.
typedef int qword __attribute__((mode(TI)));
struct CRef;
struct OBJECT;
struct FUNCTION {int references,flags;OBJECT *owner;void *callback,*data;};
struct HOLDER;
struct POOL;
union U {qword q;int i[4];float f[4];};
struct M3 {U rows[3];};
struct TWO {int a,b;};
struct THREE {int a,b,c;};
extern POOL D_00452170;
extern "C" {
FUNCTION *func_00259C18(void);
void func_00259CF8(HOLDER *,FUNCTION *);
void func_00256120(FUNCTION *);
void func_0011CD98(POOL *,void *);
CRef *func_001291A8(CRef *,const CRef *);
CRef *func_00129658(CRef *,const CRef *);
void func_00129EC8(CRef *);
void func_0012A0B0(CRef *,int);
CRef *func_00129518(CRef *,int);
CRef *func_00129558(CRef *,float);
CRef *func_00129598(CRef *,int);
CRef *func_001296A8(CRef *,const qword *);
CRef *func_00129718(CRef *,qword);
CRef *func_00129808(CRef *,const qword *);
CRef *func_00129878(CRef *,const TWO *);
CRef *func_001298F0(CRef *,const THREE *);
CRef *func_00129A10(CRef *,OBJECT *);
CRef *func_00129A70(CRef *,FUNCTION *);
}
union TAG {int integer;float scalar;void *pointer;};
struct CRef {
    int type;TAG tag;
    CRef(){type=-1;}
    CRef(const CRef &r){func_001291A8(this,&r);}
    CRef &operator=(const CRef &r){func_00129658(this,&r);return *this;}
    ~CRef(){func_00129EC8(this);}
    void Reset(int type){func_00129EC8(this);func_0012A0B0(this,type);}
    CRef &Integer(int v){return *func_00129518(this,v);}
    CRef &Scalar(float v){return *func_00129558(this,v);}
    CRef &Boolean(int v){return *func_00129598(this,v);}
    void Vector(const qword *v){func_001296A8(this,v);}
    void Vector(qword v){func_00129718(this,v);}
    void Vector4(const qword *v){func_00129808(this,v);}
    void Pair(const TWO *v){func_00129878(this,v);}
    void Triple(const THREE *v){func_001298F0(this,v);}
    void Object(OBJECT *v){func_00129A10(this,v);}
    void Function(FUNCTION *v){func_00129A70(this,v);}
};
struct HOLDER {
    FUNCTION *function;
    HOLDER(FUNCTION *f){func_00259CF8(this,f);}
    ~HOLDER(){FUNCTION *f=function;if(f&&!--f->references){func_00256120(f);func_0011CD98(&D_00452170,f);}}
};
struct OBJECT {virtual ~OBJECT();};
union GETTER {
    int offset;
    int (OBJECT::*integer)();
    float (OBJECT::*scalar)();
    int (OBJECT::*boolean)();
    qword (OBJECT::*vector)();
    const M3 &(OBJECT::*matrix)();
    void (OBJECT::*vector4)(qword *);
    void (OBJECT::*pair)(TWO *);
    void (OBJECT::*triple)(THREE *);
    CRef (OBJECT::*reference)();
    OBJECT *(OBJECT::*object)();
};
union SETTER {void *function;void (OBJECT::*method)(int);};
struct PROPERTY {int type,flags;GETTER get;SETTER set;void *data;int unused1C;OBJECT *(OBJECT::*resolve)(int);};
static inline void CopyMatrix(M3 *to,const M3 *from){to->rows[0]=from->rows[0];to->rows[1]=from->rows[1];to->rows[2]=from->rows[2];to->rows[2].i[3]=0;to->rows[1].i[3]=0;to->rows[0].i[3]=0;}
extern "C" CRef func_001FFD98(OBJECT *object,PROPERTY *property)
{
    register int rawType __asm__("$2"),type __asm__("$7");
    CRef result;
    register int integerValue __asm__("$5");register float scalarValue __asm__("$f12");
    if(property->flags&1){
        HOLDER function(func_00259C18());
        function.function->owner=object;
        function.function->callback=property->set.function;
        function.function->data=property->data;
        result.Function(function.function);
    }else if(property->flags&2){
        if(property->flags&0x2000)object=(object->*property->resolve)(1);
        rawType=property->type;
        __asm__("daddu %0,%1,$0":"=r"(type):"r"(rawType));
        void *value=(char *)object+property->get.offset;
        if((unsigned int)rawType>=24)goto direct_default;
        {
        static void *const directHandlers[24]={
            &&direct_boolean, &&direct_scalar, &&direct_vector, &&direct_default,
            &&direct_matrix, &&direct_integer, &&direct_integer, &&direct_integer,
            &&direct_integer, &&direct_vector4, &&direct_pair, &&direct_triple,
            &&direct_default, &&return_reference, &&direct_integer, &&direct_integer,
            &&direct_integer, &&direct_integer, &&direct_default, &&direct_integer,
            &&direct_integer, &&direct_default, &&direct_default, &&direct_integer
        };
        goto *directHandlers[type];
        }
        direct_integer:
            integerValue=*(int *)value;goto store_integer;
        direct_scalar:scalarValue=*(float *)value;goto store_scalar;
        direct_boolean:result.Boolean(*(int *)value!=0);goto direct_done;
        direct_vector:result.Vector((qword *)value);goto direct_done;
        direct_matrix:result.Reset(0x1B);CopyMatrix((M3 *)result.tag.pointer,(M3 *)value);goto direct_done;
        direct_vector4:result.Vector4((qword *)value);goto direct_done;
        direct_pair:result.Pair((TWO *)value);goto direct_done;
        direct_triple:result.Triple((THREE *)value);goto direct_done;

        direct_default:
            if(type&0x1000){integerValue=*(int *)value;goto store_integer;}
            else if(rawType=type&0x2000)result.Object(*(OBJECT **)value);
            goto direct_done;

direct_done:;

    }else{
        if(property->flags&0x2000)object=(object->*property->resolve)(1);
        rawType=property->type;
        __asm__("daddu %0,%1,$0":"=r"(type):"r"(rawType));
        switch(type){
        case 5:case 6:case 7:case 8:case 13:case 14:case 15:case 16:case 17:case 19:case 20:case 23:
            integerValue=(object->*property->get.integer)();goto store_integer;
        case 1:scalarValue=(object->*property->get.scalar)();
store_scalar:
            result.Scalar(scalarValue);break;
        case 0:result.Boolean((object->*property->get.boolean)()!=0);break;
        case 2:result.Vector((object->*property->get.vector)());break;
        case 4:{result.Reset(0x1B);M3 *matrix=(M3 *)result.tag.pointer;const M3 &source=(object->*property->get.matrix)();CopyMatrix(matrix,&source);break;}
        case 9:result.Reset(0x1C);(object->*property->get.vector4)((qword *)result.tag.pointer);break;
        case 10:result.Reset(0x1C);(object->*property->get.pair)((TWO *)result.tag.pointer);break;
        case 11:result.Reset(0x1E);(object->*property->get.triple)((THREE *)result.tag.pointer);break;
        default:
            if(type&0x8000){const CRef&reference=(object->*property->get.reference)();result=reference;}
            else if(type&0x1000){integerValue=(object->*property->get.integer)();
store_integer:
                result.Integer(integerValue);}
            else if(rawType=type&0x2000)result.Object((object->*property->get.object)());
            break;
        }
    }
return_reference:
    return result;
}

#define OFF(t,m) ((unsigned)&((t*)0)->m)
typedef char property_layout_pointer[(sizeof(void*)==4)?1:-1];
typedef char property_layout_int[(sizeof(int)==4)?1:-1];
typedef char property_layout_float[(sizeof(float)==4)?1:-1];
typedef char property_layout_short[(sizeof(short)==2)?1:-1];
typedef char property_layout_long[(sizeof(long)==8)?1:-1];
typedef char property_layout_qword[(sizeof(qword)==16)?1:-1];
typedef char property_layout_U[(sizeof(U)==16)?1:-1];
typedef char property_layout_U_alignment[(__alignof__(U)==16)?1:-1];
typedef char property_layout_M3[(sizeof(M3)==0x30)?1:-1];
typedef char property_layout_M3_rows[(OFF(M3,rows)==0)?1:-1];
typedef char property_layout_M3_alignment[(__alignof__(M3)==16)?1:-1];
typedef char property_layout_TWO[(sizeof(TWO)==8)?1:-1];
typedef char property_layout_TWO_b[(OFF(TWO,b)==4)?1:-1];
typedef char property_layout_THREE[(sizeof(THREE)==12)?1:-1];
typedef char property_layout_THREE_c[(OFF(THREE,c)==8)?1:-1];
typedef char property_layout_FUNCTION[(sizeof(FUNCTION)==0x14)?1:-1];
typedef char property_layout_FUNCTION_refs[(OFF(FUNCTION,references)==0)?1:-1];
typedef char property_layout_FUNCTION_flags[(OFF(FUNCTION,flags)==4)?1:-1];
typedef char property_layout_FUNCTION_owner[(OFF(FUNCTION,owner)==8)?1:-1];
typedef char property_layout_FUNCTION_callback[(OFF(FUNCTION,callback)==0xC)?1:-1];
typedef char property_layout_FUNCTION_data[(OFF(FUNCTION,data)==0x10)?1:-1];
typedef char property_layout_HOLDER[(sizeof(HOLDER)==4)?1:-1];
typedef char property_layout_HOLDER_function[(OFF(HOLDER,function)==0)?1:-1];
typedef char property_layout_OBJECT[(sizeof(OBJECT)==4)?1:-1];
typedef char property_layout_TAG[(sizeof(TAG)==4)?1:-1];
typedef char property_layout_CRef[(sizeof(CRef)==8)?1:-1];
typedef char property_layout_CRef_type[(OFF(CRef,type)==0)?1:-1];
typedef char property_layout_CRef_tag[(OFF(CRef,tag)==4)?1:-1];
typedef char property_layout_GETTER[(sizeof(GETTER)==8)?1:-1];
typedef char property_layout_SETTER[(sizeof(SETTER)==8)?1:-1];
typedef char property_layout_PROPERTY[(sizeof(PROPERTY)==0x28)?1:-1];
typedef char property_layout_PROPERTY_type[(OFF(PROPERTY,type)==0)?1:-1];
typedef char property_layout_PROPERTY_flags[(OFF(PROPERTY,flags)==4)?1:-1];
typedef char property_layout_PROPERTY_get[(OFF(PROPERTY,get)==8)?1:-1];
typedef char property_layout_PROPERTY_set[(OFF(PROPERTY,set)==0x10)?1:-1];
typedef char property_layout_PROPERTY_data[(OFF(PROPERTY,data)==0x18)?1:-1];
typedef char property_layout_PROPERTY_unused[(OFF(PROPERTY,unused1C)==0x1C)?1:-1];
typedef char property_layout_PROPERTY_resolve[(OFF(PROPERTY,resolve)==0x20)?1:-1];
typedef char property_layout_PMF_integer[(sizeof(int (OBJECT::*)())==8)?1:-1];
typedef char property_layout_PMF_scalar[(sizeof(float (OBJECT::*)())==8)?1:-1];
typedef char property_layout_PMF_qword[(sizeof(qword (OBJECT::*)())==8)?1:-1];
typedef char property_layout_PMF_reference[(sizeof(CRef (OBJECT::*)())==8)?1:-1];
typedef char property_layout_PMF_resolve[(sizeof(OBJECT *(OBJECT::*)(int))==8)?1:-1];
