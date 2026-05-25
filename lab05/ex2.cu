#include <iostream>
#include <cuda_runtime.h>

#define ARRAY_DIM 2048
#define MAX_THREADS_PER_BLOCK 1024

#define N_BLOCKS ((ARRAY_DIM + MAX_THREADS_PER_BLOCK - 1) / MAX_THREADS_PER_BLOCK)

// CUDA kernel function
__global__ void op_kernel(float* input, float* output) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    float avg;
    if (idx < ARRAY_DIM) {
        if(idx > 0 && idx < ARRAY_DIM - 1) {
            avg = (input[idx - 1] + input[idx] + input[idx + 1]) / 3.0f; // Example operation: averaging with neighbors
        } 
        else if(idx == 0) {
            avg = (input[idx] + input[idx] + input[idx + 1]) / 3.0f; // Average for the first element
        }
        else {
            avg = (input[idx - 1] + input[idx] + input[idx]) / 3.0f; // Average for the last element
        }
        output[idx] = avg; // Example operation: using the averaged value
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
        input[i] = (float) i;
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