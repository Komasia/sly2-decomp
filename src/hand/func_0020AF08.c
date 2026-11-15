/* func_0020AF08 (0x20AF08, option 356): the guard action's reach angle, given in degrees. */
struct GUARDACTION { char pad[0x68]; float radReach; };
void func_0020AF08(struct GUARDACTION *paction, float deg) { paction->radReach = deg * 0.01745329424738884f; }
