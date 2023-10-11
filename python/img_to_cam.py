def point_img_to_cam(K, R, t, P_img, Z):
    K_inv = np.linalg.inv(K)
    Rt_inv = np.linalg.inv(R)
    
    # 计算图像坐标的齐次坐标
    P_img_homo = np.array([P_img[0] * Z, P_img[1] * Z, Z])
    
    # 计算相机坐标系下的坐标
    P_cam = np.dot(Rt_inv, np.dot(K_inv, P_img_homo) - t)
    
    return P_cam

# 测试
K = np.array([[700, 0, 300],
              [0, 700, 200],
              [0, 0, 1]])

R = np.array([[0.866, -0.5, 0],
              [0.5, 0.866, 0],
              [0, 0, 1]])

t = np.array([0, 0, 5])

P_img = np.array([317.08, 263.75])
Z = 10.0

point_img_to_cam(K, R, t, P_img, Z)
