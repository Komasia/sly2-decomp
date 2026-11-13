extern unsigned char D_002C40C8[];
double pow(double, double);
double GTrunc(double) asm("GTrunc__Fd");
double dpmul(double,double);
double dpsub(double,double);
double litodp(int);
int dptoli(double);
/* Digit of g at decimal position a (precision b): 0 outside [b, b+15). */
unsigned char ChDigitFromG__Fdii(double g, int a, int b)
{
int i; double x;
    if (a < b || a - 15 >= b) i = 0;
    else {
        x = GTrunc(dpmul(g, pow(10.0, litodp(-b))));
        i = dptoli(dpsub(x, dpmul(GTrunc(dpmul(x, 0.1)), 10.0)));
    }
    return D_002C40C8[i];
}
