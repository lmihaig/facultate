import numpy as np
import matplotlib.pyplot as plt


# modificati acest path local astfel incat sa puteti citi datele corect
data_path = "/Users/bogdan/Desktop/data/"

# CIFRE
# incarca datele pentru cifre
exemple_cifre = np.loadtxt(data_path + "train_images.txt").astype(np.uint8)
etichete_cifre = np.loadtxt(data_path + "train_labels.txt").astype(np.int8)

print(exemple_cifre.shape)
print(etichete_cifre.shape)

# ploteaza primele 100 de cifre
nr_imagini = 10

etichete_100 = etichete_cifre[: nr_imagini**2]
print("Etichetele exemplelor sunt:", np.reshape(etichete_100, (nr_imagini, nr_imagini)))

plt.figure(figsize=(5, 5))
for i in range(nr_imagini**2):
    plt.subplot(nr_imagini, nr_imagini, i + 1)
    plt.axis("off")
    plt.imshow(np.reshape(exemple_cifre[i, :], (28, 28)), cmap="gray")
plt.show()

...
