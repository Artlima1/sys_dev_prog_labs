#include <iostream>
#include <cuda_runtime.h>
#include <random>

#define N_BINS 10
#define BINS_LOWER_BOUNDS {0, 10, 20, 30, 40, 50, 60, 70, 80, 90}
#define BINS_UPPER_BOUNDS {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}

#define N_ELEMENTS 1048576
#define ELEMENTS_LOWER_BOUND 0
#define ELEMENTS_UPPER_BOUND 100

#define MAX_THREADS_PER_BLOCK 1024

#define N_BLOCKS ((N_ELEMENTS + MAX_THREADS_PER_BLOCK - 1) / MAX_THREADS_PER_BLOCK)

// CUDA kernel function
__global__ void op_kernel(float* elements, float* bins_lower_bounds, float* bins_upper_bounds, float* output) {
    int e_idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (e_idx < N_ELEMENTS) {
        float element = elements[e_idx];
        for(int b_idx = 0; b_idx < N_BINS; b_idx++){
            if(element >= bins_lower_bounds[b_idx] && element < bins_upper_bounds[b_idx]){
                atomicAdd(&output[b_idx], 1.0f);
                break;
            }
        }
    }
}

void initiate_array(float * arr){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(ELEMENTS_LOWER_BOUND, ELEMENTS_UPPER_BOUND);
    for(int i=0; i<N_ELEMENTS; i++){
        arr[i] = static_cast<float>(dis(gen));
    }
}

int main() {
    // Set up device (optional, but good practice)
    dim3 gridDim(N_BLOCKS, 1, 1);
    dim3 blockDim(MAX_THREADS_PER_BLOCK, 1, 1);

    float elements[N_ELEMENTS];
    initiate_array(elements);
    float lower_bounds[N_BINS] = BINS_LOWER_BOUNDS;
    float upper_bounds[N_BINS] = BINS_UPPER_BOUNDS;
    float output[N_BINS] = {0};

    float * elements_dev = nullptr;
    float * lower_bounds_dev = nullptr;
    float * upper_bounds_dev = nullptr;
    float * out_dev = nullptr;

    cudaMalloc(&elements_dev, N_ELEMENTS * sizeof(float));
    cudaMalloc(&lower_bounds_dev, N_BINS * sizeof(float));
    cudaMalloc(&upper_bounds_dev, N_BINS * sizeof(float));
    cudaMalloc(&out_dev, N_BINS * sizeof(float));

    // Copy input data to device
    cudaMemcpy(elements_dev, elements, N_ELEMENTS * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(lower_bounds_dev, lower_bounds, N_BINS * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(upper_bounds_dev, upper_bounds, N_BINS * sizeof(float), cudaMemcpyHostToDevice);

    // Launch the kernel
    op_kernel<<<gridDim, blockDim>>>(elements_dev, lower_bounds_dev, upper_bounds_dev, out_dev);

    cudaMemcpy(output, out_dev, N_BINS * sizeof(float), cudaMemcpyDeviceToHost);

    for (int i = 0; i < N_BINS; i++) {
        std::cout << output[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}