import imageio.v3 as iio
import matplotlib.pyplot as plt
import numpy as np
import typer
from scipy.fft import dctn, idctn
import scipy.datasets
from typing_extensions import Annotated

import imageio.v3 as iio
import matplotlib.pyplot as plt
import numpy as np
import typer
from scipy.fft import dctn, idctn
import scipy.datasets
from typing_extensions import Annotated
import skimage


Q_LUM = np.array(
    [
        [16, 11, 10, 16, 24, 40, 51, 61],
        [12, 12, 14, 19, 26, 28, 60, 55],
        [14, 13, 16, 24, 40, 57, 69, 56],
        [14, 17, 22, 29, 51, 87, 80, 62],
        [18, 22, 37, 56, 68, 109, 103, 77],
        [24, 35, 55, 64, 81, 104, 113, 92],
        [49, 64, 78, 87, 103, 121, 120, 101],
        [72, 92, 95, 98, 112, 100, 103, 99],
    ],
    dtype=np.float32,
)

Q_CHROM = np.array(
    [
        [17, 18, 24, 47, 99, 99, 99, 99],
        [18, 21, 26, 66, 99, 99, 99, 99],
        [24, 26, 56, 99, 99, 99, 99, 99],
        [47, 66, 99, 99, 99, 99, 99, 99],
        [99, 99, 99, 99, 99, 99, 99, 99],
        [99, 99, 99, 99, 99, 99, 99, 99],
        [99, 99, 99, 99, 99, 99, 99, 99],
        [99, 99, 99, 99, 99, 99, 99, 99],
    ],
    dtype=np.float32,
)


def pad(array, size):
    new_shape = (size, size)
    pad_width = [(0, max(0, new_shape[i] - array.shape[i])) for i in range(2)]
    padded_array = np.pad(array, pad_width=pad_width, mode="edge")
    result_array = np.concatenate(
        [padded_array] * (new_shape[0] // padded_array.shape[0]), axis=0
    )
    result_array = result_array[: new_shape[0], : new_shape[1]]
    return result_array


def entropy_coding(img, block_size=8, q_lum=Q_LUM, q_chrom=Q_CHROM):
    layer_num = img.shape[2] if len(img.shape) == 3 else 1
    im_h, im_w = img.shape[:2]
    bl_h, bl_w = block_size, block_size
    intermediary_img = np.zeros((im_h, im_w, layer_num))
    for layer in range(layer_num):
        for row in range(0, im_h, bl_h):
            for col in range(0, im_w, bl_w):
                # block splitting
                block = img[row : row + bl_h, col : col + bl_w, layer]
                block = pad(block, bl_h)
                # dct

                # block -= 128
                dct = dctn(block)

                # quantization
                if layer == 0:
                    Q = q_lum
                else:
                    Q = q_chrom

                block = np.round(dct / Q)
                block = np.multiply(block, Q)
                block = idctn(block)

                intermediary_img[row : row + bl_h, col : col + bl_w, layer] = block[
                    : im_h - row, : im_w - col
                ]

    return intermediary_img


def adjust_quantization_matrix(Q_matrix, target_mse, current_mse):
    return Q_matrix * np.sqrt(target_mse / current_mse)


def main(
    input_path: Annotated[str, typer.Argument()] = "None",
    mse: float = typer.Option(None),
):
    try:
        img = iio.imread(input_path)
    except:
        print("Invalid or no input path, here's a raccoon instead")
        img = scipy.datasets.face()

    it = 0
    base_img = img
    img = skimage.color.ycbcr2rgb(skimage.color.rgb2ycbcr(base_img))
    modified_img = skimage.color.rgb2ycbcr(base_img)
    modified_img = entropy_coding(modified_img)
    modified_img = skimage.color.ycbcr2rgb(modified_img)

    current_mse = skimage.metrics.mean_squared_error(img, modified_img)

    while mse is not None and mse >= current_mse:
        q_lum = adjust_quantization_matrix(Q_LUM, mse, current_mse)
        q_chrom = adjust_quantization_matrix(Q_CHROM, mse, current_mse)

        modified_img = skimage.color.rgb2ycbcr(modified_img)
        modified_img = entropy_coding(modified_img, q_lum=q_lum, q_chrom=q_chrom)
        modified_img = skimage.color.ycbcr2rgb(modified_img)

        current_mse = skimage.metrics.mean_squared_error(img, modified_img)
        it += 1
        print(f"{it}: {current_mse}")

    _, ax = plt.subplots(1, 2, figsize=(16, 8))
    plt.suptitle(f"Current MSE: {current_mse}")
    ax[0].imshow(img)
    ax[0].set_title("Original")
    ax[1].imshow(modified_img)
    ax[1].set_title("Compressed")
    plt.show()


if __name__ == "__main__":
    typer.run(main)


# python jpegify.py --mse 9e-6
#
# python jpegify.py pisica.png
#
# python jpegify.py pisica.png --mse 5e-5
