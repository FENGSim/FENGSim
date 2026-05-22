#include <stdio.h>
#include <cuda_runtime.h>

#define N 1024  // matrix N x N

// multiplication: C = A * B
__global__ void matrixMul(const float *A, const float *B, float *C, int n)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < n && col < n) {
        float sum = 0.0f;
        for (int k = 0; k < n; k++) {
            sum += A[row * n + k] * B[k * n + col];
        }
        C[row * n + col] = sum;
    }
}

// initial values
void initMatrix(float *mat, int n, float value) {
    for (int i = 0; i < n * n; i++) {
        mat[i] = value;
    }
}

// error estimate
bool verifyResult(float *C, int n, float expected) {
    for (int i = 0; i < n * n; i++) {
        if (abs(C[i] - expected) > 1e-3) {
            return false;
        }
    }
    return true;
}

int main()
{
    size_t bytes = N * N * sizeof(float);
    
    // allocate host memory
    float *h_A = (float*)malloc(bytes);
    float *h_B = (float*)malloc(bytes);
    float *h_C = (float*)malloc(bytes);
    
    // initial values
    initMatrix(h_A, N, 1.0f);
    initMatrix(h_B, N, 2.0f);
    
    // allocate gpu memory
    float *d_A, *d_B, *d_C;
    cudaMalloc(&d_A, bytes);
    cudaMalloc(&d_B, bytes);
    cudaMalloc(&d_C, bytes);
    
    // copy GPU
    cudaMemcpy(d_A, h_A, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, bytes, cudaMemcpyHostToDevice);
    
    // set threads
    dim3 threadsPerBlock(16, 16);
    dim3 blocksPerGrid((N + 15) / 16, (N + 15) / 16);
    
    // time counting
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    
    cudaEventRecord(start);
    matrixMul<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);
    cudaEventRecord(stop);
    
    cudaEventSynchronize(stop);
    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);
    
    // copy to host memory
    cudaMemcpy(h_C, d_C, bytes, cudaMemcpyDeviceToHost);
    
    // error estimate
    float expected = N * 2.0f; 
    if (verifyResult(h_C, N, expected)) {
        printf("Matrix multiplication correct!\n");
        printf("Time: %.3f ms\n", milliseconds);
        printf("Performance: %.2f GFLOPS\n", 
               2.0 * N * N * N / (milliseconds / 1000.0) / 1e9);
    } else {
        printf("Result incorrect!\n");
    }
    
    // clean
    free(h_A); free(h_B); free(h_C);
    cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    
    return 0;
}