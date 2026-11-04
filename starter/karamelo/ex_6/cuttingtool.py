import os
import numpy as np

# ================= 配置参数 =================
# 1. 仿真时间参数
dt = 0.000001          # 【请修改】你的时间步长 (Time step)
nsteps = 5000       # 【请修改】总时间步数
output_dir = "tool_vtk_files"  # VTK 输出文件夹
write_interval = 20 # 每隔多少个时间步输出一个 VTK (方便快速预览)

# 2. 网格参数
cellsize = 1/100     # 【请修改】你的网格尺寸 (cellsize)

# 3. 指令中的常数
K_penalty = 100.0  # 罚系数，仅供 VTK 记录，不影响几何
base_xt_x = 1 - cellsize/2
base_xt_y = 0.2

base_xA_x = 10 + 1 - cellsize/2
base_xA_y = 0.2 + 0.1

base_xB_x = 1 - cellsize/2 + 2
base_xB_y = 10 + 0.2

# ================= 刀具运动学函数 =================
def get_tool_vertices(t):
    """
    根据时间 t 计算刀具的 3 个顶点坐标。
    根据你的指令: x = base - 50*time
    """
    # 顶点 xt
    xt = np.array([base_xt_x - 50*t, base_xt_y, 0.0])
    # 点 xA (位于第一条边)
    xA = np.array([base_xA_x - 50*t, base_xA_y, 0.0])
    # 点 xB (位于第二条边)
    xB = np.array([base_xB_x - 50*t, base_xB_y, 0.0])
    
    return [xt, xA, xB]

# ================= VTK 写入函数 =================
def write_polygon_vtk(filename, points, time):
    """写入三角形 (PolyData) 为 VTK 文件"""
    with open(filename, 'w') as f:
        f.write("# vtk DataFile Version 3.0\n")
        f.write(f"Cutting Tool at time {time:.6f}\n")
        f.write("ASCII\n")
        f.write("DATASET POLYDATA\n")
        
        # 写入 3 个点
        f.write(f"POINTS 3 float\n")
        for p in points:
            f.write(f"{p[0]:.6f} {p[1]:.6f} {p[2]:.6f}\n")
            
        # 写入三角形面 (3 个点组成 1 个多边形)
        f.write(f"POLYGONS 1 4\n")
        f.write(f"3 0 1 2\n")
        
        # 写入点数据，防止 Paraview 报错
        f.write(f"POINT_DATA 3\n")
        f.write(f"SCALARS ToolID float 1\n")
        f.write(f"LOOKUP_TABLE default\n")
        f.write(f"1.0 1.0 1.0\n")

# ================= 主循环 =================
def main():
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)
        print(f"Created output directory: {output_dir}")

    print(f"Starting VTK generation: dt={dt}, nsteps={nsteps}, cellsize={cellsize}")
    
    for step in range(0, nsteps + 1, write_interval):
        t = step * dt
        
        # 获取当前时刻刀具顶点
        points = get_tool_vertices(t)
        
        # 构造文件名 (例如 tool_000010.vtk)
        filename = os.path.join(output_dir, f"tool_{step:06d}.vtk")
        
        # 写入文件
        write_polygon_vtk(filename, points, t)
        
        if step % 100 == 0:
            print(f"Step {step}/{nsteps} (t={t:.4e}): Tool tip at X={points[0][0]:.3f}")

    print("VTK generation completed! Open the folder in ParaView.")

if __name__ == "__main__":
    main()
