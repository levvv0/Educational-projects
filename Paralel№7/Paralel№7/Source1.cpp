//#include <iostream>
//#include <omp.h>
//#include <cstdio>
//#include <cmath>
//
//const int N = 1000;
//
//double A[N][N], B[N][N], C[N][N];
//
//void init_matrices()
//{
//#pragma omp parallel for
//    for (int i = 0; i < N; ++i)
//    {
//        for (int j = 0; j < N; ++j)
//        {
//            A[i][j] = (i + j) % 10;
//            B[i][j] = (i * j) % 10;
//            C[i][j] = 0.0;
//        }
//    }
//}
//
//void multiply_jik_guided(int num_threads)
//{
//    omp_set_num_threads(num_threads);
//
//#pragma omp parallel for collapse(2) schedule(guided)
//    for (int j = 0; j < N; ++j)
//    {
//        for (int i = 0; i < N; ++i)
//        {
//            double sum = 0.0;
//            for (int t = 0; t < N; ++t)
//            {
//                sum += A[i][t] * B[t][j];
//            }
//            C[i][j] = sum;
//        }
//    }
//}
//
//void multiply_kij_guided(int num_threads)
//{
//    omp_set_num_threads(num_threads);
//
//#pragma omp parallel for collapse(2) schedule(guided)
//    for (int t = 0; t < N; ++t)
//    {
//        for (int i = 0; i < N; ++i)
//        {
//            double temp = A[i][t];
//            for (int j = 0; j < N; ++j)
//            {
//                C[i][j] += temp * B[t][j];
//            }
//        }
//    }
//}
//
//int main()
//{
//    printf("========================================\n");
//    printf("УМНОЖЕНИЕ МАТРИЦ (OpenMP)\n");
//    printf("Вариант 6: j-i-k  и  k-i-j\n");
//    printf("Распределение: schedule(guided)\n");
//    printf("Размер матриц: %d x %d\n", N, N);
//    printf("========================================\n\n");
//
//    init_matrices();
//
//    int threads[] = { 1, 2, 4, 8, 12, 16, 20, 24, 28, 32 };
//    int n_tests = sizeof(threads) / sizeof(threads[0]);
//
//    printf("========== ВАРИАНТ 1: j-i-k ==========\n\n");
//    printf("Потоков\tВремя1\tВремя2\tВремя3\tСреднее\n");
//
//    for (int t = 0; t < n_tests; ++t)
//    {
//        int num_threads = threads[t];
//
//        double times[3];
//        for (int run = 0; run < 3; ++run)
//        {
//
//#pragma omp parallel for
//            for (int i = 0; i < N; ++i)
//            {
//                for (int j = 0; j < N; ++j)
//                {
//                    C[i][j] = 0.0;
//                }
//            }
//
//            double start = omp_get_wtime();
//            multiply_jik_guided(num_threads);
//            double end = omp_get_wtime();
//            times[run] = end - start;
//        }
//
//        double avg_time = (times[0] + times[1] + times[2]) / 3.0;
//
//        printf("%d\t%.4f\t%.4f\t%.4f\t%.4f\n",
//            num_threads, times[0], times[1], times[2], avg_time);
//    }
//
//    printf("\n========== ВАРИАНТ 2: k-i-j ==========\n\n");
//    printf("Потоков\tВремя1\tВремя2\tВремя3\tСреднее\n");
//
//    for (int t = 0; t < n_tests; ++t)
//    {
//        int num_threads = threads[t];
//
//        double times[3];
//        for (int run = 0; run < 3; ++run)
//        {
//#pragma omp parallel for
//            for (int i = 0; i < N; ++i)
//            {
//                for (int j = 0; j < N; ++j)
//                {
//                    C[i][j] = 0.0;
//                }
//            }
//
//            double start = omp_get_wtime();
//            multiply_kij_guided(num_threads);
//            double end = omp_get_wtime();
//            times[run] = end - start;
//        }
//
//        double avg_time = (times[0] + times[1] + times[2]) / 3.0;
//
//        printf("%d\t%.4f\t%.4f\t%.4f\t%.4f\n",
//            num_threads, times[0], times[1], times[2], avg_time);
//    }
//
//    return 0;
//}
