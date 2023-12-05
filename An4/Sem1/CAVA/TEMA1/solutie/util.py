import cv2 as cv
from matplotlib import pyplot as plt
import json
import numpy as np
import os
from typing import List, Tuple, Dict
import numpy as np

import time


def show_image(image):
    image = cv.resize(image, (0, 0), fx=0.3, fy=0.3)
    cv.imshow("image", image)
    cv.waitKey(0)
    cv.destroyAllWindows()


def print_image(image, gray=True, fft=True, title=None, output_dir=None):
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

    if output_dir:
        plt.savefig(output_dir)
    else:
        plt.show()


def color_filter(image, color_rgb, sensitivity):
    hsv = cv.cvtColor(image, cv.COLOR_BGR2HSV)
    color_hsv = cv.cvtColor(color_rgb, cv.COLOR_RGB2HSV)
    h, s, v = color_hsv[0][0]
    lower_bound = np.array(
        [h - sensitivity, max(s - sensitivity, 0), max(v - sensitivity, 0)]
    )
    upper_bound = np.array(
        [h + sensitivity, min(s + sensitivity, 255), min(v + sensitivity, 255)]
    )

    mask = cv.inRange(hsv, lower_bound, upper_bound)
    filtered_image = cv.bitwise_and(image, image, mask=mask)
    return filtered_image


def find_largest_contour(mask):
    mask = cv.cvtColor(mask, cv.COLOR_BGR2GRAY)
    _, binary = cv.threshold(mask, 1, 255, cv.THRESH_BINARY)
    binary = cv.morphologyEx(
        binary, cv.MORPH_CLOSE, np.ones((5, 5), np.uint8), iterations=20
    )
    contours, _ = cv.findContours(binary, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_SIMPLE)
    if contours:
        return max(contours, key=cv.contourArea)
    return None


def crop_board(image):
    mask = color_filter(image, color_rgb=np.uint8([[[11, 143, 171]]]), sensitivity=60)
    largest_contour = find_largest_contour(mask)
    if largest_contour is None:
        return None

    x, y, w, h = cv.boundingRect(largest_contour)
    tightness = 20

    x, y, w, h = x - tightness, y - tightness, w + 2 * tightness, h + 2 * tightness
    top_left = (x, y)
    bottom_right = (x + w, y + h)
    top_right = (x + w, y)
    bottom_left = (x, y + h)
    orig = np.array(
        [[top_left], [top_right], [bottom_right], [bottom_left]], dtype="float32"
    )
    dest = np.array([[0, 0], [w, 0], [w, h], [0, h]], dtype="float32")
    m = cv.getPerspectiveTransform(orig, dest)
    return cv.warpPerspective(image, m, (w, h))


def index_to_board_notation(pos):
    row, col = pos
    if row < 0 or row >= 15 or col < 0 or col >= 15:
        return "Invalid index"

    col_letter = chr(65 + col)
    row_number = str(row + 1)
    return row_number + col_letter


def board_notation_to_index(notation):
    if (
        not notation
        or len(notation) < 2
        or not notation[0].isdigit()
        or not notation[1:].isalpha()
    ):
        return "Invalid notation"

    row = int(notation[:-1]) - 1

    col = ord(notation[-1].upper()) - ord("A")

    if row < 0 or row >= 15 or col < 0 or col >= 15:
        return "Invalid index"

    return (row, col)


def grid_mask(image):
    lines = cv.HoughLines(image, 1, np.pi / 180, 350)
    mask = np.zeros_like(image)
    width, height = mask.shape

    def cluster_lines(lines, rho_tolerance=10):
        if not lines:
            return []

        lines = sorted(lines, key=lambda x: x[0])

        clusters = []
        current_cluster = [lines[0]]
        for i in range(1, len(lines)):
            if abs(lines[i][0] - current_cluster[-1][0]) <= rho_tolerance:
                current_cluster.append(lines[i])
            else:
                clusters.append(current_cluster)
                current_cluster = [lines[i]]
        if current_cluster:
            clusters.append(current_cluster)
        averaged_lines = [
            (np.mean([line[0] for line in cluster]), cluster[0][1])
            for cluster in clusters
        ]

        return averaged_lines

    def insert_missing_lines(lines):
        lines = sorted(lines, key=lambda x: x[0])

        spacings = np.diff([line[0] for line in lines])
        mean_spacing = np.mean(spacings)

        new_lines = []
        for index, spacing in enumerate(spacings):
            if spacing > mean_spacing * 1.5:
                new_rho = (lines[index][0] + lines[index + 1][0]) / 2
                new_lines.append((new_rho, lines[index][1]))

        for new_line in new_lines:
            lines.append(new_line)
        lines = sorted(lines, key=lambda x: x[0])
        return lines

    def filter_lines(lines, tolerance=np.pi / 180, rho_tolerance=50):
        filtered_lines = {"vertical": [], "horizontal": []}

        for line in lines:
            for rho, theta in line:
                if abs(theta) < tolerance or abs(theta - np.pi) < tolerance:
                    filtered_lines["vertical"].append((rho, theta))
                elif abs(theta - np.pi / 2) < tolerance:
                    filtered_lines["horizontal"].append((rho, theta))

        filtered_lines["vertical"] = cluster_lines(
            filtered_lines["vertical"], rho_tolerance
        )
        filtered_lines["horizontal"] = cluster_lines(
            filtered_lines["horizontal"], rho_tolerance
        )
        filtered_lines["vertical"] = insert_missing_lines(filtered_lines["vertical"])
        filtered_lines["horizontal"] = insert_missing_lines(
            filtered_lines["horizontal"]
        )
        return filtered_lines

    def draw_lines(image, lines):
        for rho, theta in lines:
            a = np.cos(theta)
            b = np.sin(theta)
            x0 = a * rho
            y0 = b * rho
            x1 = int(x0 + width * (-b))
            y1 = int(y0 + height * (a))
            x2 = int(x0 - width * (-b))
            y2 = int(y0 - height * (a))
            cv.line(image, (x1, y1), (x2, y2), (255, 255, 255), 8)

    filtered_lines = filter_lines(lines)
    draw_lines(mask, filtered_lines["vertical"])
    draw_lines(mask, filtered_lines["horizontal"])
    return mask, filtered_lines


def edge_detect(image):
    image_edges = cv.Canny(
        image=image,
        threshold1=100,
        threshold2=255,
        apertureSize=5,
        L2gradient=True,
    )
    return image_edges


def sharpen(image):
    kernel_h = np.array(
        [
            [0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0],
            [1, 1, 1, 1, 1],
            [0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0],
        ],
        dtype=np.uint8,
    )

    kernel_v = np.array(
        [
            [0, 0, 1, 0, 0],
            [0, 0, 1, 0, 0],
            [0, 0, 1, 0, 0],
            [0, 0, 1, 0, 0],
            [0, 0, 1, 0, 0],
        ],
        dtype=np.uint8,
    )

    image_h = cv.filter2D(image, -1, kernel_h)
    image_v = cv.filter2D(image, -1, kernel_v)

    # print_image(image_h, title="vertical")
    # print_image(image_v, title="horizontal")

    image_sharpened = image_h + image_v
    return image_sharpened


def denoise(image):
    image_gray = cv.cvtColor(image, cv.COLOR_BGR2GRAY)
    image_blurred = image_gray
    # image_blurred = cv.GaussianBlur(
    #     image_gray, ksize=(5, 5), sigmaX=1, borderType=cv.BORDER_REPLICATE
    # )
    # print_image(image_blurred, title="Gaussian")

    image_blurred = cv.bilateralFilter(
        image_blurred,
        d=9,
        sigmaColor=15,
        sigmaSpace=150,
        borderType=cv.BORDER_REPLICATE,
    )
    return image_blurred


def get_piece(prev_image, cur_image, grid, mask=None):
    def pipeline(image):
        image = color_filter(image, np.uint8([[[200, 240, 250]]]), 60)
        image = cv.cvtColor(image, cv.COLOR_HSV2BGR)
        return image

    prev_image = pipeline(prev_image)
    cur_image = pipeline(cur_image)
    size = (
        max(prev_image.shape[1], cur_image.shape[1]),
        max(prev_image.shape[0], cur_image.shape[0]),
    )
    prev_image_diff = cv.resize(prev_image, size, interpolation=cv.INTER_AREA)
    cur_image_diff = cv.resize(cur_image, size, interpolation=cv.INTER_AREA)

    current_image = cur_image_diff.copy()

    image = 255 - cv.absdiff(prev_image_diff, cur_image_diff)

    gray = cv.cvtColor(image, cv.COLOR_BGR2GRAY)
    _, thresh = cv.threshold(gray, 160, 255, cv.THRESH_BINARY_INV)
    thresh = cv.morphologyEx(
        thresh, cv.MORPH_OPEN, np.ones((3, 3), np.uint8), iterations=1
    )
    thresh = cv.morphologyEx(
        thresh, cv.MORPH_CLOSE, np.ones((3, 3), np.uint8), iterations=3
    )
    thresh = cv.erode(thresh, np.ones((3, 3), np.uint8), iterations=2)

    cnts, _ = cv.findContours(thresh.copy(), cv.RETR_EXTERNAL, cv.CHAIN_APPROX_SIMPLE)

    good_contours = []
    for contour in cnts:
        area = cv.contourArea(contour)
        if area > 15:
            x, y, w, h = cv.boundingRect(contour)
            aspect_ratio = max(w / h, h / w)
            if 1.9 < aspect_ratio < 2.1:
                # print(f"Area: {area}, Aspect Ratio: {aspect_ratio}")
                good_contours.append(contour)

    contour = max(cnts, key=cv.contourArea)

    contour_poly = cv.approxPolyDP(contour, 3, True)
    bounding_rect = cv.boundingRect(contour_poly)

    # output = cv.drawContours(image, [contour_poly], -1, (255, 0, 0), 6)
    # image = cv.rectangle(image, bounding_rect, (0, 255, 0), 6)

    # draw_grid(image.copy(), mask, title="Grid Mask")
    # print_image(image, title="Contour", fft=False)

    x, y, w, h = bounding_rect
    locations = localize_piece(bounding_rect, grid)
    # print(locations)

    domino = current_image.copy()[y : y + h, x : x + w]
    domino = cv.cvtColor(domino, cv.COLOR_BGR2GRAY)
    # domino = cv.GaussianBlur(domino, (5, 5), 0)

    orientation = "horizontal"
    if h > w:
        orientation = "vertical"
        domino = cv.rotate(domino, cv.ROTATE_90_COUNTERCLOCKWISE)
        w, h = h, w

    left_rect_start = (0, 0)
    left_rect_end = (w // 2, h)

    right_rect_start = (w // 2, 0)
    right_rect_end = (w, h)

    left_square = domino[
        left_rect_start[1] : left_rect_end[1], left_rect_start[0] : left_rect_end[0]
    ]
    right_square = domino[
        right_rect_start[1] : right_rect_end[1], right_rect_start[0] : right_rect_end[0]
    ]

    def circles(image):
        circles = cv.HoughCircles(
            image,
            cv.HOUGH_GRADIENT_ALT,
            dp=1,
            minDist=25,
            param1=400,
            param2=0.2,
            minRadius=12,
            maxRadius=16,
        )

        if circles is not None:
            # print("circles:", circles)
            # print("circles len:", len(circles))
            # print("circles[0] len:", len(circles[0]))
            circles = np.uint16(np.around(circles))
            return circles
        return np.array([[]])

    left_circles = circles(left_square)
    right_circles = circles(right_square)

    domino = cv.cvtColor(domino, cv.COLOR_GRAY2RGB)

    # for circle in left_circles[0, :]:
    #     x, y, r = circle
    #     cv.circle(domino, (x, y), r, (0, 0, 255), 1)

    # for circle in right_circles[0, :]:
    #     x, y, r = circle
    #     cv.circle(domino, (x + w // 2, y), r, (0, 255, 0), 1)

    # print(left_circles, right_circles)

    # cv.rectangle(domino, left_rect_start, left_rect_end, (0, 0, 255), 1)
    # cv.rectangle(domino, right_rect_start, right_rect_end, (0, 255, 0), 1)
    # print_image(domino, title="Domino", fft=False, gray=False)
    # print_image(
    #     domino,
    #     title="Domino",
    #     fft=False,
    #     gray=False,
    #     output_dir=f"./test/{int(time.time())}.jpg",
    # )
    # time.sleep(1)

    left_circles = len(left_circles[0, :])
    right_circles = len(right_circles[0, :])
    return (orientation, locations[0], left_circles, locations[1], right_circles)


def localize_piece(
    rect: Tuple[float, float, float, float], lines: Dict[str, List[Tuple[float, float]]]
) -> List[Tuple[int, int]]:
    x, y, w, h = rect

    vertical_lines = sorted([line[0] * np.cos(line[1]) for line in lines["vertical"]])
    horizontal_lines = sorted(
        [line[0] * np.sin(line[1]) for line in lines["horizontal"]]
    )

    def find_overlapping_squares():
        overlapping_squares = []
        for i in range(len(horizontal_lines) - 1):
            for j in range(len(vertical_lines) - 1):
                if (
                    horizontal_lines[i] < y + h
                    and horizontal_lines[i + 1] > y
                    and vertical_lines[j] < x + w
                    and vertical_lines[j + 1] > x
                ):
                    overlapping_squares.append((i, j))
        return overlapping_squares

    overlapping_squares = find_overlapping_squares()

    intersection_areas = {}
    for i, j in overlapping_squares:
        top = max(y, horizontal_lines[i])
        bottom = min(y + h, horizontal_lines[i + 1])
        left = max(x, vertical_lines[j])
        right = min(x + w, vertical_lines[j + 1])

        area = max(0, right - left) * max(0, bottom - top)
        if area > 0:
            intersection_areas[(i, j)] = area

    top_two_squares = sorted(
        intersection_areas, key=intersection_areas.get, reverse=True
    )[:2]

    top_two_squares = sorted(top_two_squares, key=lambda x: (x[1], x[0]))
    return top_two_squares


def draw_grid(image, mask, title=None, output_dir=None):
    pink = [180, 105, 255]
    min_height = min(image.shape[0], mask.shape[0])
    min_width = min(image.shape[1], mask.shape[1])
    image = image[:min_height, :min_width]
    mask = mask[:min_height, :min_width]
    if len(image.shape) == 3:
        channels = image.shape[2]
        mask = np.repeat(mask[:, :, np.newaxis], channels, axis=2)
    pink_overlay = np.full_like(image, pink)
    overlayed_image = np.where(mask == 255, pink_overlay, image)
    print_image(
        overlayed_image, gray=False, title=title, output_dir=output_dir, fft=False
    )
