import numpy as np

def point_cam_to_img(K, R, t, P_cam):
    P_cam_homo = np.append(P_cam, 1)  # 转换为齐次坐标
    Rt = np.column_stack((R, t))  # 构建[R|t]矩阵
    P_img_homo = np.dot(K, np.dot(Rt, P_cam_homo))  # 计算图像坐标系下的点（齐次坐标）
    P_img = P_img_homo[:2] / P_img_homo[2]  # 转换为非齐次坐标
    return P_img

# 测试
K = np.array([[700, 0, 300],
              [0, 700, 200],
              [0, 0, 1]])

R = np.array([[0.866, -0.5, 0],
              [0.5, 0.866, 0],
              [0, 0, 1]])

t = np.array([0, 0, 5])

P_cam = np.array([1, 1, 10])

point_cam_to_img(K, R, t, P_cam)
