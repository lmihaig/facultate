import tkinter as tk
from tkinter import Canvas
import numpy as np
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
from PIL import Image, ImageDraw


class DrawFFTApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Draw and FFT")

        self.draw_canvas = Canvas(root, width=256, height=256, bg="white")
        self.draw_canvas.pack(side="left")
        self.draw_canvas.bind("<B1-Motion>", self.paint)

        self.image = Image.new("L", (256, 256), "white")
        self.draw = ImageDraw.Draw(self.image)

        self.fig = Figure(figsize=(5, 4), dpi=100)
        self.ax = self.fig.add_subplot(111)
        self.ax.axis("off")
        self.fft_canvas = FigureCanvasTkAgg(self.fig, master=root)
        self.fft_canvas.get_tk_widget().pack(side="right")

        self.button = tk.Button(root, text="Show FFT", command=self.update_fft)
        self.button.pack(side="bottom")

    def paint(self, event):
        x1, y1 = (event.x - 1), (event.y - 1)
        x2, y2 = (event.x + 1), (event.y + 1)
        self.draw_canvas.create_oval(x1, y1, x2, y2, fill="black", width=5)
        self.draw.ellipse([x1, y1, x2, y2], fill="black")

    def update_fft(self):
        img_array = np.array(self.image)
        fft_result = np.fft.fftshift(np.fft.fft2(img_array))
        fft_magnitude = np.log(np.abs(fft_result) + 1)

        self.ax.clear()
        self.ax.imshow(fft_magnitude, cmap="gray")
        self.ax.axis("off")
        self.fft_canvas.draw()


root = tk.Tk()
app = DrawFFTApp(root)
root.mainloop()
