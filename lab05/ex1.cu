#include <iostream>
#include <cuda_runtime.h>

#define ARRAY_DIM 2048
#define MAX_THREADS_PER_BLOCK 1024

#define N_BLOCKS ((ARRAY_DIM + MAX_THREADS_PER_BLOCK - 1) / MAX_THREADS_PER_BLOCK)

// CUDA kernel function
__global__ void op_kernel(float* input, float* output) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < ARRAY_DIM) {
        output[idx] = input[idx] * 2.0f; // Example operation: doubling the input
    }
}

int main() {
    // Set up device (optional, but good practice)
    dim3 gridDim(N_BLOCKS, 1, 1);
    dim3 blockDim(MAX_THREADS_PER_BLOCK, 1, 1);

    float input[ARRAY_DIM];
    float output[ARRAY_DIM];

    // Initialize input array
    for (int i = 0; i < ARRAY_DIM; i++) {
        input[i] = i;
    }

    float * inp_dev = nullptr;
    float * out_dev = nullptr;

    cudaMalloc(&inp_dev, ARRAY_DIM * sizeof(float));
    cudaMalloc(&out_dev, ARRAY_DIM * sizeof(float));

    // Copy input data to device
    cudaMemcpy(inp_dev, input, ARRAY_DIM * sizeof(float), cudaMemcpyHostToDevice);

    // Launch the kernel
    op_kernel<<<gridDim, blockDim>>>(inp_dev, out_dev);

    cudaMemcpy(output, out_dev, ARRAY_DIM * sizeof(float), cudaMemcpyDeviceToHost);

    for (int i = 0; i < ARRAY_DIM; i++) {
        std::cout << output[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}