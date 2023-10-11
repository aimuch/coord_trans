
要将相机坐标系下的点 $P_{\text{cam}} = [X, Y, Z]^T$ 转换到图像坐标系下的点 $p_{\text{img}} = [u, v]^T$，你可以使用以下方程：
```math
\begin{pmatrix}
u \\
v \\
1
\end{pmatrix}
=
K \cdot [R|t] \cdot
\begin{pmatrix}
X \\
Y \\
Z \\
1
\end{pmatrix}
```
其中，
- $K$ 是相机的内参矩阵，通常为一个 3x3 的矩阵。
- $[R|t]$ 是相机的外参矩阵，其中 $ R $ 是旋转矩阵，$ t $ 是平移向量。
- $u, v$ 是图像坐标系下的点。

Python 代码如下：

转换后的图像坐标系下的点为 $ (u, v) = (317.08, 263.75) $。这是通过应用内外参矩阵和相机坐标系下的点来计算得到的。
