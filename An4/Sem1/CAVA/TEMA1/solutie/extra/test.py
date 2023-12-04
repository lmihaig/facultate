import matplotlib.pyplot as plt
import numpy as np
import cv2

image = cv2.imread("./tabla_goala.jpg", cv2.IMREAD_GRAYSCALE)
rows, cols = image.shape


def generate_2d_anisotropic_gaussian_kernel(size_x, size_y, sigma_x, sigma_y):
    center_x, center_y = size_x // 2, size_y // 2
    x, y = np.meshgrid(np.arange(size_x), np.arange(size_y), indexing="ij")
    x_squared = ((x - center_x) ** 2) / (2 * sigma_x**2)
    y_squared = ((y - center_y) ** 2) / (2 * sigma_y**2)
    kernel = np.exp(-(x_squared + y_squared))
    return kernel


length = 1000
thick = 50

gaussian_kernel_y = generate_2d_anisotropic_gaussian_kernel(rows, cols, length, thick)
gaussian_kernel_x = generate_2d_anisotropic_gaussian_kernel(rows, cols, thick, length)
gaussian_kernel_cross = gaussian_kernel_x + gaussian_kernel_y

dft = cv2.dft(np.float32(image), flags=cv2.DFT_COMPLEX_OUTPUT)
dft_shifted = np.fft.fftshift(dft)

mask = np.zeros_like(dft_shifted)
mask[:, :, 0] = gaussian_kernel_cross
mask[:, :, 1] = gaussian_kernel_cross

fshift = dft_shifted * mask
f_ishift = np.fft.ifftshift(fshift)
img_back = cv2.idft(f_ishift)
img_back = cv2.magnitude(img_back[:, :, 0], img_back[:, :, 1])

cv2.normalize(img_back, img_back, 0, 255, cv2.NORM_MINMAX, dtype=cv2.CV_8U)

plt.figure(figsize=(18, 6))

plt.subplot(1, 3, 1)
plt.imshow(image, cmap="gray")
plt.title("Original Image")

plt.subplot(1, 3, 2)
plt.imshow(gaussian_kernel_cross, cmap="gray")
plt.title("Cross-Shaped Filter")

plt.subplot(1, 3, 3)
plt.imshow(img_back, cmap="gray")
plt.title("Filtered Image")

plt.tight_layout()
plt.show()
