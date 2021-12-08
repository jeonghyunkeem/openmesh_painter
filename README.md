# openmesh_painter
> Author: Jeonghyun Kim 
> Date: 08-Dec-2021

Mesh painter using OpenMesh for CS492D

## Requirements
```
OpenMesh
Eigen
```

## Description
1. Takes function matrix `_vectors` and column `_c` (e.g. index of LBO, timestep for HKS) to draw. 
2. Normalize function values are normalized to color domain (0~255).
3. Colorize face of mesh with averaged function value of its vertices. 
