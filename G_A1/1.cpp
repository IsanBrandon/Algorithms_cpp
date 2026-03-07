int fun1(int m, int A[], int n, int B[], int C[]) {
    int i = 0, j = 0, k = 0;
    while(i < m && j < n) {
        if (A[i] < B[j])
            C[k++] = A[i], i++; 
        else if (A[i] > B[j])
            C[k++] = B[j], j++;
        else // A[i] == B[j]인 경우
            C[k++] = A[i], i++, j++;
    }
    while (i < m)
        C[k++] = A[i], i++;
    while (j < n)
        C[k++] = B[j], j++;
    return k;
}

double fun2(int n) {
    double sum = 0;
    for (double i = 1.0; i < n; i *= 1.5)
        sum += i;
    return sum;
}

/* 배열 data에는 n개의 양의 정수가 저장되어 있다. */
int fun5(int n, int K, int data[]) {
    int begin=0, sum = 0, max_sum = 0;
    for (int end = 0; end < n; end++) {
        sum += data[end];
        while (sum > K)
            sum -= data[begin++];
        if (sum > max_sum)
            max_sum = sum;
    }
    return max_sum; 
}