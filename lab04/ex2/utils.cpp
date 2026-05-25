
#include <cstdlib>
#include <future>
#include <thread>
#include <vector>

// #define VERSION_SEQ
//#define VERSION_A
#define VERSION_C

double * build_rand_array(const int size) {
    auto array = new double[size];

    for (int i = 0; i < size; i++) {
        array[i] = (rand() % 2) - 0.5;
    }

    return array;
}

double ** build_rand_matrix(const int size) {
    auto m = new double*[size];

    for (int i = 0; i < size; i++) {
        m[i] = new double[size];
        for (int j = 0; j < size; j++) {
            m[i][j] = rand();
        }
    }

    return m;
}

void delete_matrix(double ** m, const int size) {
    for (int i = 0; i < size; i++) {
        delete[] m[i];
    }
    delete[] m;
}

void vec(const double  * v1, const double * v2, int size, double * res) {
    double tmp = 0;
    for (int i = 0; i < size; i++) {
        tmp += v1[i] * v2[i];
    }
    *res = tmp;
}

double op_seq(const double * v1, const double * v2, double ** mat, const int n) {
    double tmp = 0;
    const auto v = new double[n];

    for (int i = 0; i < n; i++) {
        vec(v1, mat[i], n, &v[i]);
    }


    tmp = 0;
    for (int i = 0; i < n; i++) {
        tmp += v2[i] * v[i];
    }

    delete[] v;
    return tmp;
}

double op_vA(const double * v1, const double * v2, double ** mat, const int n) {
    double tmp = 0;
    const auto v = new double[n];

    std::vector<std::thread> pool;
    for (int i = 0; i < n; i++) {
        pool.emplace_back([&, i] {vec(v1, mat[i], n, &v[i]);});
    }

    for (int i = 0; i < n; i++) {
        pool[i].join();
    }

    tmp = 0;
    for (int i = 0; i < n; i++) {
        tmp += v2[i] * v[i];
    }

    delete[] v;
    return tmp;
}

double op_vC(const double * v1, const double * v2, double ** mat, const int n) {
    double tmp = 0;
    const auto v = new std::future<double>[n];

    for (int i = 0; i < n; i++) {
        v[i] = std::async (
            std::launch::async,
            [&, i]() {
                double tmp_l = 0;
                for (int j = 0; j < n; j++) {
                    tmp_l += v1[j] * mat[i][j];
                }
                return tmp_l;
            }
        );
    }

    tmp = 0;
    for (int i = 0; i < n; i++) {
        tmp += v2[i] * v[i].get();
    }

    delete[] v;
    return tmp;
}

double op(const double * v1, const double * v2, double ** mat, const int n) {
#ifdef VERSION_SEQ
    return op_seq(v1, v2, mat, n);
#elif defined VERSION_A
    return op_vA(v1, v2, mat, n);
#elif defined VERSION_C
    return op_vC(v1, v2, mat, n);
#else
    return 0;
#endif
}

