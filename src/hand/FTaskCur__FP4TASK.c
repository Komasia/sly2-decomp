/* FTaskCur: whether a task is the current one (D_003E0FA0, next to the current job). */
struct TASK;
extern struct TASK *D_003E0FA0;   /* the current task */

// name: SafeHouse port (FTaskCur)
int FTaskCur__FP4TASK(struct TASK *ptask)
{
    return D_003E0FA0 == ptask;
}
