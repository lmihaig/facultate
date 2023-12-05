import cv2 as cv
from matplotlib import pyplot as plt
import json
import numpy as np


def generate_2d_anisotropic_gaussian_kernel(size_x, size_y, sigma_x, sigma_y):
    center_x, center_y = size_x // 2, size_y // 2
    x, y = np.meshgrid(np.arange(size_x), np.arange(size_y), indexing="ij")
    x_squared = ((x - center_x) ** 2) / (2 * sigma_x**2)
    y_squared = ((y - center_y) ** 2) / (2 * sigma_y**2)
    kernel = np.exp(-(x_squared + y_squared))
    return kernel


class ImageProcessor:
    def __init__(self, image_path):
        self.image_path = image_path
        self.image_cropped = cv.imread(image_path)
        self.image = cv.imread(image_path)
        self.mask = None
        self.config = json.load(open("../config.json"))
        self.antrenare_folder = "../../antrenare/"
        self.evaluare_folder = "../../evaluare/"
        self.auxiliare_folder = "../../imagini_auxiliare/"

    def show_image(self, image=None):
        if image is None:
            image = self.image
        image = cv.resize(image, (0, 0), fx=0.3, fy=0.3)
        cv.imshow("image", image)
        cv.waitKey(0)
        cv.destroyAllWindows()

    def print_image(self, image=None, gray=True, fft=True, title=None):
        if image is None:
            image = self.image
        fig, axes = plt.subplots(1, 2, figsize=(12, 6))
        if not gray:
            image_rgb = cv.cvtColor(image, cv.COLOR_BGR2RGB)
            axes[0].imshow(image_rgb)
            image_gray = cv.cvtColor(image, cv.COLOR_BGR2GRAY)
        else:
            axes[0].imshow(image, cmap="gray")
            image_gray = image
        axes[0].set_title("Image")
        axes[0].axis("off")

        if fft:
            f = np.fft.fft2(image_gray)
            fshift = np.fft.fftshift(f)
            magnitude_spectrum = 20 * np.log(np.abs(fshift) + 1e-60)
            axes[1].imshow(magnitude_spectrum, cmap="gray")
            axes[1].set_title("Spectrum")
            axes[1].axis("off")
        else:
            axes[1].remove()

        if title:
            plt.suptitle(title)
        plt.tight_layout()
        plt.show()

    def colorFilter(self):
        hsv = cv.cvtColor(self.image, cv.COLOR_BGR2HSV)
        lower_blue = np.array([90, 50, 50])
        upper_blue = np.array([130, 255, 255])
        mask = cv.inRange(hsv, lower_blue, upper_blue)
        self.mask = mask
        filtered_image = cv.bitwise_and(self.image, self.image, mask=mask)
        self.print_image(filtered_image, gray=False, title="Filtered")

    def crop_ROI(self):
        contours, _ = cv.findContours(
            self.mask, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_SIMPLE
        )
        if contours:
            largest_contour = max(contours, key=cv.contourArea)
            x, y, w, h = cv.boundingRect(largest_contour)
            roi = self.image_cropped[y : y + h, x : x + w]

        self.image_cropped = cv.cvtColor(roi.copy(), cv.COLOR_BGR2RGB)
        self.image = roi
        self.print_image(gray=False, title="ROI")

    def denoise(self):
        self.image = cv.cvtColor(self.image, cv.COLOR_BGR2GRAY)

        self.image = cv.GaussianBlur(
            self.image, ksize=(5, 5), sigmaX=1, borderType=cv.BORDER_REPLICATE
        )
        self.print_image(title="Gaussian")

        self.image = cv.bilateralFilter(
            self.image,
            d=9,
            sigmaColor=15,
            sigmaSpace=150,
            borderType=cv.BORDER_REPLICATE,
        )
        self.print_image(title="Bilateral")

    def sharpen(self):
        kernel = np.array([[0, 1, 0], [1, 1, 1], [0, 1, 0]], dtype=np.uint8)
        self.image = cv.filter2D(self.image, -1, kernel)
        self.image = cv.normalize(
            self.image, dst=None, alpha=0, beta=255, norm_type=cv.NORM_MINMAX
        )
        self.print_image(title="Sharpened")

    def fft_mask(self):
        length = self.image.shape[0] // 20
        thick = self.image.shape[1] // 200

        rows, cols = self.image.shape
        gaussian_kernel_y = generate_2d_anisotropic_gaussian_kernel(
            rows, cols, length, thick
        )
        gaussian_kernel_x = generate_2d_anisotropic_gaussian_kernel(
            rows, cols, thick, length
        )
        gaussian_kernel_cross = gaussian_kernel_x + gaussian_kernel_y

        dft = cv.dft(np.float32(self.image), flags=cv.DFT_COMPLEX_OUTPUT)
        dft_shifted = np.fft.fftshift(dft)

        mask = np.zeros_like(dft_shifted)
        mask[:, :, 0] = gaussian_kernel_cross
        mask[:, :, 1] = gaussian_kernel_cross

        fshift = dft_shifted * mask
        f_ishift = np.fft.ifftshift(fshift)
        img_back = cv.idft(f_ishift)
        img_back = cv.magnitude(img_back[:, :, 0], img_back[:, :, 1])

        self.image = cv.normalize(
            img_back, dst=None, alpha=0, beta=255, norm_type=cv.NORM_MINMAX
        )
        self.image = np.uint8(self.image)
        self.print_image(title="Masked")

    def threshold(self):
        ret, self.image = cv.threshold(self.image, 200, 255, cv.THRESH_BINARY)
        kernel = np.ones((3, 3), np.uint8)
        self.image = cv.erode(self.image, kernel)
        self.print_image(title="Thresholded")

    def canny(self):
        self.image = cv.Canny(
            image=self.image,
            threshold1=100,
            threshold2=255,
            apertureSize=5,
            L2gradient=True,
        )
        self.print_image(title="Canny")

    def closing(self):
        h_kernel = np.ones((1, 20), np.uint8)
        v_kernel = np.ones((20, 1), np.uint8)

        def connect_lines(image, kernel):
            d_im = cv.dilate(image, kernel, iterations=2)
            e_im = cv.erode(d_im, kernel, iterations=2)
            return e_im

        self.image = connect_lines(self.image, h_kernel)
        self.image = connect_lines(self.image, v_kernel)
        self.print_image(title="Closing")

    def houghlines(self):
        lines = cv.HoughLines(
            self.image,
            rho=15,
            theta=np.pi / 180,
            threshold=250,
            min_theta=0,
            max_theta=9 * np.pi / 16,
        )
        angle_margin = np.deg2rad(5)
        if lines is not None:
            for rho, theta in lines[:, 0]:
                a = np.cos(theta)
                b = np.sin(theta)
                x0 = a * rho
                y0 = b * rho
                x1 = int(x0 + 1000 * (-b))
                y1 = int(y0 + 1000 * (a))
                x2 = int(x0 - 1000 * (-b))
                y2 = int(y0 - 1000 * (a))
                if abs(theta) < angle_margin or abs(theta - np.pi) < angle_margin:
                    cv.line(self.image, (x1, y1), (x2, y2), (255, 255, 255), 2)
                elif abs(theta - np.pi / 2) < angle_margin:
                    cv.line(self.image, (x1, y1), (x2, y2), (255, 255, 255), 2)
        self.print_image(title="Houghlines")

    def corners_and_perspective(self):
        contours, _ = cv.findContours(
            self.image, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_SIMPLE
        )
        max_area = 0
        for i in range(len(contours)):
            if len(contours[i]) > 3:
                possible_top_left = None
                possible_bottom_right = None
                for point in contours[i].squeeze():
                    if (
                        possible_top_left is None
                        or point[0] + point[1]
                        < possible_top_left[0] + possible_top_left[1]
                    ):
                        possible_top_left = point

                    if (
                        possible_bottom_right is None
                        or point[0] + point[1]
                        > possible_bottom_right[0] + possible_bottom_right[1]
                    ):
                        possible_bottom_right = point

                diff = np.diff(contours[i].squeeze(), axis=1)
                possible_top_right = contours[i].squeeze()[np.argmin(diff)]
                possible_bottom_left = contours[i].squeeze()[np.argmax(diff)]
                if (
                    cv.contourArea(
                        np.array(
                            [
                                [possible_top_left],
                                [possible_top_right],
                                [possible_bottom_right],
                                [possible_bottom_left],
                            ]
                        )
                    )
                    > max_area
                ):
                    max_area = cv.contourArea(
                        np.array(
                            [
                                [possible_top_left],
                                [possible_top_right],
                                [possible_bottom_right],
                                [possible_bottom_left],
                            ]
                        )
                    )
                    top_left = possible_top_left
                    bottom_right = possible_bottom_right
                    top_right = possible_top_right
                    bottom_left = possible_bottom_left

        width = 810
        height = 810

        cv.circle(self.image_cropped, tuple(top_left), 20, (0, 0, 255), -1)
        cv.circle(self.image_cropped, tuple(top_right), 20, (0, 0, 255), -1)
        cv.circle(self.image_cropped, tuple(bottom_left), 20, (0, 0, 255), -1)
        cv.circle(self.image_cropped, tuple(bottom_right), 20, (0, 0, 255), -1)
        self.print_image(image=self.image_cropped, fft=False)

        puzzle = np.array(
            [[top_left], [top_right], [bottom_right], [bottom_left]], dtype="float32"
        )
        destionation_puzzle = np.array(
            [[0, 0], [width, 0], [width, height], [0, height]], dtype="float32"
        )
        m = cv.getPerspectiveTransform(puzzle, destionation_puzzle)
        result = cv.warpPerspective(self.image_cropped, m, (width, height))
        result = cv.cvtColor(result, cv.COLOR_BGR2RGB)
        self.print_image(image=self.image_cropped, fft=False)

    def pipeline(self):
        self.print_image(gray=False, title="Original image")
        self.colorFilter()
        self.crop_ROI()
        self.denoise()
        self.sharpen()
        self.fft_mask()
        self.threshold()
        self.canny()
        self.closing()
        self.houghlines()
        self.corners_and_perspective()


img = ImageProcessor("./tabla_negoala.jpg")
img.pipeline()
