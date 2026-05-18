
#include <cstdlib>

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

double op(const double * v1, const double * v2, double ** mat, const int n) {
    double tmp = 0;
    const auto v = new double[n];

    for (int j = 0; j < n; j++) {
        tmp = 0;
        for (int i = 0; i < n; i++) {
            tmp += v1[i] * mat[i][j];
        }
        v[j] = tmp;
    }

    tmp = 0;
    for (int i = 0; i < n; i++) {
        tmp += v2[i] * v[i];
    }

    delete[] v;
    return tmp;
}
