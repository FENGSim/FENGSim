import numpy as np
import matplotlib.pyplot as plt
from numpy.fft import fft2, ifft2, fftfreq

M, N = 4, 4
f = np.array([[-0,-0,-0,0],
              [-0,-78.957,-9.6694e-15,78.957],
              [-0,-9.6694e-15,-1.1842e-30,9.6694e-15],
              [0,78.957,9.6694e-15,-78.957]], dtype=float)
    
print(f"M = {M}, N = {N}")
print(f"f = \n{f}\n")
    
# 1. numpy计算
F_numpy = np.fft.fft2(f)
print("numpy.fft.fft2(f):")
print(F_numpy)
print("\n")
    
# 2. 手动实现公式
F_manual = np.zeros((M, N), dtype=complex)
    
for u in range(M):      # 对应k1
    for v in range(N):  # 对应k2
        total = 0 + 0j
        for x in range(M):      # 对应j1
            for y in range(N):  # 对应j2
                angle = -2 * np.pi * (u*x/M + v*y/N)
                total += f[x, y] * (np.cos(angle) + 1j*np.sin(angle))
        F_manual[u, v] = total
print(F_manual)
