/* class: SHOP (a text callback of the shop's screen object, SafeHouse shop.cpp): the shop's info text - the message
 * when one is shown; on the buy page "<name><description><can / cannot afford>" (text 0xDA when the coins cover the
 * cost, else 0xD9; 0xDC with no item); on the sell page text 0xDB with the loot's value (0xE3 with none). */
typedef struct { int use,kind,cost,power,iepisode,idName,idDescription,x1C; } ITEM;   /* the item table */
typedef struct { int nValue; int ids,pad; } LOOT;   /* the loot table: its value */
typedef struct SHOP {                 /* field: SafeHouse port (shop.cpp SHOP) */
    /* 0x000 */ char pad[0x30];
    /* 0x030 */ int msg, pad34, idMsg, pad3C, page;
    /* 0x044 */ char pad44[0x254-0x44];
    /* 0x254 */ int itemBuy, itemSell;
} SHOP;
extern SHOP D_003DA150;
extern ITEM D_002BCD00[];
extern LOOT D_002C3288[];
extern struct G g_sw;
extern char g_game[],D_002A7A38[];    /* D_002A7A38: the buy text format */
char *func_0013E368(struct G *,int);
int func_00161798(void *pgame);       /* the coins (SafeHouse CCoins) */
int sprintf(char *,const char *,...);
char *s1_strcpy(char *,const char *) asm("strcpy");
static inline void CopyId(char *p,int id)
{
    s1_strcpy(p,func_0013E368(&g_sw,id));
}
void func_001DCAB0(char *pch)
{
    SHOP *pshop=&D_003DA150;
    if(pshop->msg!=-1) {
        CopyId(pch,pshop->idMsg);
        return;
    } else {
        switch(pshop->page) {
        case 0: {
            unsigned int item=pshop->itemBuy;
            if(item<0x2B) {
                if(D_002BCD00[item].idDescription!=pshop->msg) {
                    int *pc=&D_002BCD00[item].cost;
                    int ccoin=func_00161798(g_game);
                    int idsT=ccoin<*pc?0xD9:0xDA;
                    struct G *pg=&g_sw;
                    char *fmt=D_002A7A38;
                    char *pch1=func_0013E368(pg,D_002BCD00[item].idName);
                    char *pch2=func_0013E368(pg,D_002BCD00[item].idDescription);
                    sprintf(pch,fmt,pch1,pch2,func_0013E368(pg,idsT));
                    return;
                }
            }
            CopyId(pch,0xDC);
            return;
        }
        case 1: {
            unsigned int loot=pshop->itemSell;
            if(loot<0x40) {
                sprintf(pch,func_0013E368(&g_sw,0xDB),D_002C3288[loot].nValue);
                return;
            }
            CopyId(pch,0xE3);
            return;
        }
        default:
            *pch=0;
            return;
        }
    }
}
