import numpy as np

base = np.array(
    [
        [0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0],
    ]
)

corner = np.array(
    [
        [5, 0, 0, 4, 0, 0, 0],
        [0, 0, 3, 0, 0, 4, 0],
        [0, 3, 0, 0, 2, 0, 0],
        [4, 0, 0, 3, 0, 2, 0],
        [0, 0, 2, 0, 1, 0, 1],
        [0, 4, 0, 2, 0, 1, 0],
        [0, 0, 0, 0, 1, 0, 0],
    ]
)

corner_height, corner_width = corner.shape
base[0:corner_height, 0:corner_width] = corner
rotated_corner = np.rot90(corner, -1)
base[0:corner_width, -corner_height:] = rotated_corner

rotated_corner_180 = np.rot90(corner, -2)

base[-corner_height:, -corner_width:] = rotated_corner_180

rotated_corner_270 = np.rot90(corner, -3)

base[-corner_height:, 0:corner_width] = rotated_corner_270

base


print(base)
