#include <iostream>

#define EXAMPLE

extern double * build_rand_array(int size);
extern double ** build_rand_matrix(int size);
extern void delete_matrix(double ** m, int size);
extern double op(const double * v1, const double * v2, double ** mat, const int n);

int main(int argc, char * argv[]) {
    int n;

#ifdef EXAMPLE
    n = 5;
    auto v1 = new double[5]{ -0.0613, -0.1184,  0.2655,  0.2952, -0.3131 };
    auto v2 = new double[5]{ -0.3235,  0.1948, -0.1829,  0.4502, -0.4656 };
    auto mat = new double*[5];
    // stored transposed: mat[i] = i-th column of M, enabling cache-friendly row access
    mat[0] = new double[5]{ -0.3424,  0.4706,  0.4572, -0.0146,  0.3003 };
    mat[1] = new double[5]{ -0.3581, -0.0782,  0.4157,  0.2922,  0.4595 };
    mat[2] = new double[5]{  0.1557, -0.4643,  0.3491,  0.4340,  0.1787 };
    mat[3] = new double[5]{  0.2577,  0.2431,  0.1078, -0.1555, -0.3288 };
    mat[4] = new double[5]{  0.2060, -0.4682, -0.2231, -0.4029, -0.4656 };
#else
    n = std::stoi(argv[1]);
    auto v1 = build_rand_array(n);
    auto v2 = build_rand_array(n);
    auto mat = build_rand_matrix(n);
#endif

    double res = op(v1, v2, mat, n);

    std::cout << res << std::endl;

    delete [] v1;
    delete [] v2;
    delete_matrix(mat, n);

}
