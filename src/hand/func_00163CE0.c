/* class: TASK (SafeHouse task.cpp, orig 0x00163F48 / 0x00163CE0: the current task left). */
struct TASK;
int FTaskCur__FP4TASK(struct TASK *ptask);
void DeactivateTask__FP4TASK(struct TASK *ptask);

void func_00163CE0(struct TASK *ptask)
{
    if (FTaskCur__FP4TASK(ptask) != 0) {
        DeactivateTask__FP4TASK(ptask);
    }
}
