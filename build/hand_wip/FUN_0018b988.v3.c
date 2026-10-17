// (Claude agent, 2026-10-17) v3: aligned 23 (v2 24). kind 20 case 0 first; kinds 16/17 goto zero; kind 3/10 tail `if(v!=0)goto neg; zero: return 0;` with neg = case 1 default -> AD24 block now exact. Left: kinds 1/11 {0} leaf not cross-jumped to AD24.
static inline int DefaultNegative(int value){int result=11;if(value>=-9)result=31;return result;}
int FUN_0018b988(int kind,int value){
    switch(kind){
    case 1:
        switch(value){case -1:return 9;case -2:return 10;case -5:return 11;case 0:goto zero;}
        neg: return DefaultNegative(value);
    case 2:
        switch(value){case -3:return 1;case -4:return 13;case -5:return 6;case -7:return 25;case -2:goto twelve;}
        goto ordinary;
scalar16:
        if(value!=-4)return DefaultNegative(value);
ret16:
        return 16;
    case 4:
        if(value==-4)goto ret16;
        goto checkOrdinary;
    case 5:
        switch(value){case -4:return 16;case -5:return 17;case -2:goto twelve;}
        goto ordinary;
    case 6:
        switch(value){case -3:return 1;case -4:return 16;case -5:return 18;case -8:return 26;case -2:goto twelve;}
        goto ordinary;
    case 3:
    case 10:
        if(value==-2)goto twelve;
        if(value<-1)goto scalar16;
zeroOrDefault:
        if(value!=0)goto neg;
zero:
        return 0;
    case 11:
        switch(value){case -3:return 1;case -4:return 24;case -2:goto twelve;case 0:goto zero;}
        return DefaultNegative(value);
    case 12:
        if(value==-2)goto twelve;
        if(value>=-1)goto zeroOrDefault;
        if(value!=-4)return DefaultNegative(value);
ret21:
        return 21;
    case 13:
        if(value==-4)goto ret21;
        goto checkOrdinary;
twelve:
        return 12;
    case 14:
        switch(value){case -4:return 22;case -2:goto twelve;case 0:goto zero;}
        return DefaultNegative(value);
    case 15:
        switch(value){case -4:return 14;case -5:return 19;case -6:return 23;case -2:goto twelve;case 0:goto zero;}
        return DefaultNegative(value);
    case 16:
        if(value==0)goto zero;
        {int result=4;if(value>=0)result=31;return result;}
    case 17:
        if(value==0)goto zero;
        {int result=5;if(value>=0)result=31;return result;}
    case 18:
checkOrdinary:
        if(value==-2)goto twelve;
ordinary:
        if(value>=0)goto zero;return DefaultNegative(value);
    case 19:
        switch(value){case -4:return 22;case -2:goto twelve;case 0:goto zero;}
        return DefaultNegative(value);
    case 20:
        switch(value){case 0:goto zero;case -403:return 35;}
        break;
    case 21:
        if(value>=0)goto zero;
        if((unsigned)(value+100)<100)return 31;
        {int result=30;if(value>=-99)result=31;return result;}
    }
    return 31;
}
