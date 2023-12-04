import tkinter as tk
from tkinter import Canvas, Label
import cv2
import numpy as np
from PIL import Image, ImageTk


class KernelDesigner(tk.Tk):
    def __init__(self):
        super().__init__()
        self.kernel_size = 7
        self.kernel_values = np.zeros(
            (self.kernel_size, self.kernel_size), dtype=np.float32
        )
        # self.image_path = "../extra/cat.jpg"
        self.image_path = "../extra/tabla_goala.jpg"
        self.image = cv2.resize(
            cv2.imread(self.image_path, cv2.IMREAD_GRAYSCALE),
            (0, 0),
            fx=0.2,
            fy=0.2,
        )
        self.processed_image = None
        self.create_widgets()
        self.display_images()

    def create_widgets(self):
        # Kernel design area
        self.kernel_frame = Canvas(self, width=350, height=350, bg="white")
        self.kernel_frame.grid(row=0, column=0)

        # Image display area
        self.original_image_label = Label(self)
        self.original_image_label.grid(row=0, column=1)

        self.processed_image_label = Label(self)
        self.processed_image_label.grid(row=0, column=2)

        self.kernel_rects = {}
        rect_size = 50
        for i in range(self.kernel_size):
            for j in range(self.kernel_size):
                x0, y0 = j * rect_size, i * rect_size
                x1, y1 = x0 + rect_size, y0 + rect_size
                rect = self.kernel_frame.create_rectangle(
                    x0, y0, x1, y1, fill="black", outline="blue"
                )
                self.kernel_rects[(i, j)] = rect

        self.kernel_frame.bind("<Button-1>", self.toggle_rect)

        apply_button = tk.Button(self, text="Apply Kernel", command=self.apply_kernel)
        apply_button.grid(row=1, column=1)

    def toggle_rect(self, event):
        row, col = event.y // 50, event.x // 50
        if row < self.kernel_size and col < self.kernel_size:
            current_value = self.kernel_values[row, col]
            match current_value:
                case 0:
                    new_value = 0.5
                case 0.5:
                    new_value = 1
                case 1:
                    new_value = 0
                case _:
                    raise ValueError(f"Invalid value: {current_value}")
            self.kernel_values[row, col] = new_value
            color = (
                "black" if new_value == 0 else "gray" if new_value == 0.5 else "white"
            )
            self.kernel_frame.itemconfig(self.kernel_rects[(row, col)], fill=color)

    def apply_kernel(self):
        if self.image is not None and np.sum(self.kernel_values) != 0:
            norm_kernel = np.array(self.kernel_values, dtype=np.uint8)
            print(norm_kernel)
            self.processed_image = cv2.filter2D(self.image, -1, norm_kernel)
            print(self.processed_image)
            self.display_images()

    def display_images(self):
        if self.image is not None:
            original_image = Image.fromarray(self.image)
            original_image = ImageTk.PhotoImage(original_image)
            self.original_image_label.configure(image=original_image)
            self.original_image_label.image = original_image

            if self.processed_image is not None:
                processed_image = Image.fromarray(self.processed_image)
                processed_image = ImageTk.PhotoImage(processed_image)
                self.processed_image_label.configure(image=processed_image)
                self.processed_image_label.image = processed_image


if __name__ == "__main__":
    app = KernelDesigner()
    app.mainloop()
