import numpy as np
import matplotlib.pyplot as plt

dataPath = "data\\"

# incarca exemplele
Cifra_0_exemple = np.loadtxt(dataPath + "0.txt", "uint8")
Cifra_1_exemple = np.loadtxt(dataPath + "1.txt", "uint8")
Cifra_2_exemple = np.loadtxt(dataPath + "2.txt", "uint8")
Cifra_3_exemple = np.loadtxt(dataPath + "3.txt", "uint8")
Cifra_4_exemple = np.loadtxt(dataPath + "4.txt", "uint8")
Cifra_5_exemple = np.loadtxt(dataPath + "5.txt", "uint8")
Cifra_6_exemple = np.loadtxt(dataPath + "6.txt", "uint8")
Cifra_7_exemple = np.loadtxt(dataPath + "7.txt", "uint8")
Cifra_8_exemple = np.loadtxt(dataPath + "8.txt", "uint8")
Cifra_9_exemple = np.loadtxt(dataPath + "9.txt", "uint8")

data_to_show = np.zeros((100, 28 * 28))
data_to_show[0:25] = Cifra_0_exemple[:25]
data_to_show[25:50] = Cifra_1_exemple[:25]
data_to_show[50:75] = Cifra_2_exemple[:25]
data_to_show[75:100] = Cifra_3_exemple[:25]

# ploteaza primele 25 de exemple pentru cifrele 0, 1, 2, 3
nbImages = 10
plt.figure(figsize=(5, 5))
for i in range(nbImages**2):
    plt.subplot(nbImages, nbImages, i + 1)
    plt.axis("off")
    plt.imshow(np.reshape(data_to_show[i, :], (28, 28)), cmap="gray")
plt.show()


# Completati codul in continuare
