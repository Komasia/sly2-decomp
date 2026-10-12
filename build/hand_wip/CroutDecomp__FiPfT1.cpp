static inline float GAbs(float g) { return __builtin_fabsf(g); }

void CroutDecomp(int n, float *a, float *lu)
{
    int i, j, k;
    float sum;
    float g;

    if (n == 0)
        return;

    for (i = 0; i < n; i++)
        lu[i] = a[i];

    if (GAbs(lu[0]) < 1e-8f) {
        for (i = 0; i < n; i++)
            lu[i * n] = 0.0f;
    } else {
        for (i = 1; i < n; i++)
            lu[i * n] = a[i * n] / lu[0];
    }

    for (i = 1; i < n - 1; i++) {
        for (j = i; j < n; j++) {
            sum = 0.0f;
            for (k = 0; k < i; k++)
                sum += lu[k * n + j] * lu[i * n + k];
            lu[i * n + j] = a[i * n + j] - sum;
        }
        if (GAbs(lu[i * n + i]) < 1e-8f) {
            for (j = i; j < n; j++)
                lu[j * n + i] = 0.0f;
        } else {
            for (j = i + 1; j < n; j++) {
                sum = 0.0f;
                for (k = 0; k < i; k++)
                    sum += lu[k * n + i] * lu[j * n + k];
                lu[j * n + i] = (a[j * n + i] - sum) / lu[i * n + i];
            }
        }
    }

    sum = 0.0f;
    for (k = 0; k < n - 1; k++)
        sum += lu[k * n + n - 1] * lu[(n - 1) * n + k];
    g = a[(n - 1) * n + n - 1] - sum;
    lu[(n - 1) * n + n - 1] = g;
    if (GAbs(g) < 1e-8f)
        lu[(n - 1) * n + n - 1] = 0.0f;
}
