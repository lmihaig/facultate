N = 200

with open("x.dat") as infile:
    x = [float(a.strip()) for a in infile.readlines()]

with open("y.dat") as infile:
    y = [float(a.strip()) for a in infile.readlines()]


with open("mat.dat") as infile:
    A = [[0 for j in range(N)] for i in range(N)]
    for i, line in enumerate(infile.readlines()):
        A[i] = [float(j.strip()) for j in line.split()]

numerator = 0.0
for i in range(N):
    for j in range(N):
        numerator += x[i] * A[i][j] * y[j]

# calculate denominator
denominator = 0.0
for i in range(N):
    denominator += x[i] * y[i]

# calculate result
result = numerator / denominator

print(result)
