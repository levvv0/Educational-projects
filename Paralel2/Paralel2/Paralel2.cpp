#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

using namespace std;

const long long N = 10000000;
const double A = 0.4;
const double B = 0.6;

#define MAX_THREADS 64

double f(double x) {
    return (x * x + sin(0.48 * (x + 2.0))) / (exp(x * x) + 0.38);
}

double simpson_static(int num_threads) {
    omp_set_dynamic(0);
    omp_set_num_threads(num_threads);

    double h = (B - A) / N;
    double sum_odd = 0.0;
    double sum_even = 0.0;

#pragma omp parallel for reduction(+:sum_odd, sum_even) schedule(static)
    for (long long i = 1; i < N; ++i) {
        double x = A + i * h;

        if (i % 2 == 0) {
            sum_even += f(x);
        }
        else {
            sum_odd += f(x);
        }
    }

    double result = (h / 3.0) * (f(A) + f(B) + 4.0 * sum_odd + 2.0 * sum_even);

    return result;
}

void distribution_simpson_static(int num_threads) {
    long long count[MAX_THREADS] = { 0 };
    int actual_threads = 0;

    omp_set_dynamic(0);
    omp_set_num_threads(num_threads);

    double h = (B - A) / N;

#pragma omp parallel
    {
        int tid = omp_get_thread_num();

#pragma omp single
        {
            actual_threads = omp_get_num_threads();
            cout << "\nRequested threads = " << num_threads << endl;
            cout << "OpenMP actually created " << actual_threads << " threads" << endl;
        }

#pragma omp for schedule(static)
        for (long long i = 1; i < N; ++i) {
            count[tid]++;

            double x = A + i * h;
            volatile double y = f(x);
        }
    }

    cout << "\nIteration distribution = " << actual_threads << ":" << endl;

    for (int i = 0; i < actual_threads; ++i) {
        cout << "Thread " << setw(2) << i << ": " << count[i] << " iterations" << endl;
    }
}

int main() {
    omp_set_dynamic(0);

    int threads[] = { 1, 2, 4, 8, 12, 16, 20, 24, 32 };
    int n_tests = sizeof(threads) / sizeof(threads[0]);

    double best_time = 1e9;
    int best_threads = 1;
    double best_result = 0.0;

    cout << "Threads\tRun1\tRun2\tRun3\tAverage Time\tIntegral" << endl;

    for (int t = 0; t < n_tests; ++t) {
        int num_threads = threads[t];

        double times[3];
        double results[3];

        for (int run = 0; run < 3; ++run) {
            double start = omp_get_wtime();
            results[run] = simpson_static(num_threads);
            double end = omp_get_wtime();

            times[run] = end - start;
        }

        double avg_time = (times[0] + times[1] + times[2]) / 3.0;
        double avg_result = (results[0] + results[1] + results[2]) / 3.0;

        cout << fixed << setprecision(4);
        cout << num_threads << "\t" 
            << times[0] << "\t"
            << times[1] << "\t"
            << times[2] << "\t"
            << avg_time << "\t\t";

        cout << fixed << setprecision(14) << avg_result << endl;

        if (avg_time < best_time) {
            best_time = avg_time;
            best_threads = num_threads;
            best_result = avg_result;
        }
    }

    cout << "\nBest Result" << endl;

    cout << "Best threads = " << best_threads << endl;

    cout << fixed << setprecision(4);
    cout << "Best average time = " << best_time << " seconds" << endl;

    cout << fixed << setprecision(14);
    cout << "Integral value = " << best_result << endl;

    distribution_simpson_static(best_threads);

    return 0;
}