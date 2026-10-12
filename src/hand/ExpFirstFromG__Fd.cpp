extern "C" double func_00245178(double);
int ExpFirstFromG(double g)
{
    int exp;
    if (g > 0.0) {
        double l = func_00245178(g);
        exp = (int)l;
        if (l < 0.0 && l != (double)exp)
            exp--;
    } else {
        exp = 0;
    }
    return exp;
}
