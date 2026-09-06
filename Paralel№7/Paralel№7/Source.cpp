#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

const int N = 1000;
#define MAX_THREADS 64

double A[N][N], B[N][N], C[N][N];

void init_matrices() {
#pragma omp parallel for collapse(2)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = (i + j) % 10;
            B[i][j] = (i * j) % 10;
            C[i][j] = 0.0;
        }
    }
}

void clear_C() {
#pragma omp parallel for collapse(2)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0.0;
        }
    }
}

void multiply_jik_dynamic(int num_threads) {
    omp_set_num_threads(num_threads);

#pragma omp parallel for collapse(2) schedule(dynamic)
    for (int j = 0; j < N; ++j) {
        for (int i = 0; i < N; ++i) {
            double sum = 0.0;

            for (int k = 0; k < N; ++k) {
                sum += A[i][k] * B[k][j];
            }

            C[i][j] = sum;
        }
    }
}

void multiply_kij_dynamic(int num_threads) {
    omp_set_num_threads(num_threads);

#pragma omp parallel
    {
        for (int k = 0; k < N; ++k) {
#pragma omp for schedule(dynamic)
            for (int i = 0; i < N; ++i) {
                double temp = A[i][k];

                for (int j = 0; j < N; ++j) {
                    C[i][j] += temp * B[k][j];
                }
            }
        }
    }
}

void distribution_jik_dynamic(int num_threads) {
    long long count[MAX_THREADS] = { 0 };

    omp_set_num_threads(num_threads);
    clear_C();

#pragma omp parallel for collapse(2) schedule(dynamic)
    for (int j = 0; j < N; ++j) {
        for (int i = 0; i < N; ++i) {
            int tid = omp_get_thread_num();
            count[tid]++;

            double sum = 0.0;

            for (int k = 0; k < N; ++k) {
                sum += A[i][k] * B[k][j];
            }

            C[i][j] = sum;
        }
    }

    printf("\nIteration distribution for j-i-k, threads = %d:\n", num_threads);

    for (int i = 0; i < num_threads; ++i) {
        printf("Thread %2d: %lld iterations\n", i, count[i]);
    }
}

void distribution_kij_dynamic(int num_threads) {
    long long count[MAX_THREADS] = { 0 };

    omp_set_num_threads(num_threads);
    clear_C();

#pragma omp parallel
    {
        for (int k = 0; k < N; ++k) {
#pragma omp for schedule(dynamic)
            for (int i = 0; i < N; ++i) {
                int tid = omp_get_thread_num();
                count[tid]++;

                double temp = A[i][k];

                for (int j = 0; j < N; ++j) {
                    C[i][j] += temp * B[k][j];
                }
            }
        }
    }

    printf("\nIteration distribution for k-i-j, threads = %d:\n", num_threads);

    for (int i = 0; i < num_threads; ++i) {
        printf("Thread %2d: %lld iterations\n", i, count[i]);
    }
}

int main() {

    init_matrices();

    int threads[] = { 1, 2, 4, 8, 12, 16, 20, 24, 32 };
    int n_tests = sizeof(threads) / sizeof(threads[0]);

    double best_time_jik = 1e9;
    int best_threads_jik = 1;

    double best_time_kij = 1e9;
    int best_threads_kij = 1;

    printf("Matrix Multiplication 1: j-i-kn\n");
    printf("Threads\tRun1\tRun2\tRun3\tAverage Time\n");

    for (int t = 0; t < n_tests; ++t) {
        int num_threads = threads[t];
        double times[3];

        for (int run = 0; run < 3; ++run) {
            clear_C();

            double start = omp_get_wtime();
            multiply_jik_dynamic(num_threads);
            double end = omp_get_wtime();

            times[run] = end - start;
        }

        double avg_time = (times[0] + times[1] + times[2]) / 3.0;

        printf("%d\t%.4f\t%.4f\t%.4f\t%.4f\n",
            num_threads, times[0], times[1], times[2], avg_time);

        if (avg_time < best_time_jik) {
            best_time_jik = avg_time;
            best_threads_jik = num_threads;
        }
    }

    printf("\nMatrix Multiplication 2: k-i-j-\n\n");
    printf("Threads\tRun1\tRun2\tRun3\tAverage Time\n");

    for (int t = 0; t < n_tests; ++t) {
        int num_threads = threads[t];
        double times[3];

        for (int run = 0; run < 3; ++run) {
            clear_C();

            double start = omp_get_wtime();
            multiply_kij_dynamic(num_threads);
            double end = omp_get_wtime();

            times[run] = end - start;
        }

        double avg_time = (times[0] + times[1] + times[2]) / 3.0;

        printf("%d\t%.4f\t%.4f\t%.4f\t%.4f\n",
            num_threads, times[0], times[1], times[2], avg_time);

        if (avg_time < best_time_kij) {
            best_time_kij = avg_time;
            best_threads_kij = num_threads;
        }
    }

    printf("\nBest Results\n");
    printf("Best j-i-k: threads = %d, average time = %.4f\n",
        best_threads_jik, best_time_jik);
    printf("Best k-i-j: threads = %d, average time = %.4f\n",
        best_threads_kij, best_time_kij);

    distribution_jik_dynamic(best_threads_jik);
    distribution_kij_dynamic(best_threads_kij);

    return 0;
}