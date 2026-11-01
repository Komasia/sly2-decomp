/* func_00225B60: Update (virtual slot 15) of class 69, derived from class 50 (PO): the SO Update, then the class's
 * own part. */
#include "so.h"

void UpdateSo__FP2SOf(SO *p, float dt);
void func_00225BA0(void *);
void func_00225E98(void *);
void func_00226250(void *);

void func_00225B60(SO *p, float dt)
{
    UpdateSo__FP2SOf(p, dt);
    func_00225BA0(p);
    func_00225E98(p);
    func_00226250(p);
}
