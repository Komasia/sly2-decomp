static inline int DefaultNegative(int value){int result=11;if(value>=-9)result=31;return result;}
int FUN_0018b988(int kind,int value){
    register int result __asm__("$2");
    switch(kind){
    case 1:
        if(value==-2)goto retTen;
        if(value<-1){if(value==-5)goto retEleven;goto neg;}
        if(value!=-1)goto zeroOrDefault;
        result=9;
returnSelected:return result;
retTen:return 10;
retEleven:return 11;
neg:return DefaultNegative(value);
    case 2:
        switch(value){case -3:retOne:return 1;case -4:return 13;case -5:return 6;case -7:return 25;case -2:goto twelve;}
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
        if(value==-3)goto retOne;
        if(value<-2){if(value==-4)goto retTwentyFour;goto neg;}
        if(value==-2)goto twelve;
        goto zeroOrDefault;
retTwentyFour:return 24;
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
        if(value==-2)goto twelve;
        if(value>=-1)goto zeroOrDefault;
scalar22:
        if(value!=-4)return DefaultNegative(value);
        return 22;
    case 15:
        switch(value){case -4:return 14;case -5:return 19;case -6:return 23;case -2:goto twelve;case 0:goto zero;}
        return DefaultNegative(value);
    case 16:
        result=0;
        if(value==0)goto returnSelected;
        {int negative=4;if(value>=0)negative=31;return negative;}
    case 17:
        result=0;
        if(value==0)goto returnSelected;
        {int negative=5;if(value>=0)negative=31;return negative;}
    case 18:
checkOrdinary:
        if(value==-2)goto twelve;
ordinary:
        if(value>=0)goto zero;return DefaultNegative(value);
    case 19:
        if(value==-2)goto twelve;
        if(value<-1)goto scalar22;
        goto zeroOrDefault;
    case 20:
        switch(value){case 0:goto zero;case -403:return 35;}
        return 31;
    case 21:
        if(value>=0)goto zero;
        if((unsigned)(value+100)<100)return 31;
        {int result=30;if(value>=-99)result=31;return result;}
    }
    result=31;return result;
}
