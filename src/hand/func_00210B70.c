/* func_00210B70 (called by DeactivateJob and 0x162E38): the current episode's main world record (SafeHouse
 * transition.h: 0x210AE0 the episode, 0x210B98 its main world record). */
typedef struct WREC WREC;
int func_00210AE0(void);
WREC *func_00210B98(int iepisode);

WREC *func_00210B70(void)
{
    return func_00210B98(func_00210AE0());
}
