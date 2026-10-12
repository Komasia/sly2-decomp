void CroutSolve(int n, float *a, float *b, float *x)
{
    int i, j;
    float sum;

    for (i = 0; i < n; i++) {
        if (a[i * n + i] == 0.0f) {
            x[i] = 0.0f;
            continue;
        }
        sum = 0.0f;
        for (j = 0; j < i; j++)
            sum += a[j * n + i] * x[j];
        x[i] = (b[i] - sum) / a[i * n + i];
    }

    for (i = n - 2; i >= 0; i--) {
        if (a[i * n + i] == 0.0f)
            continue;
        sum = 0.0f;
        for (j = i + 1; j < n; j++)
            sum += a[j * n + i] * x[j];
        x[i] -= sum;
    }
}
