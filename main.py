import numpy
m = numpy.array([[-5, 3, -3, -5, 0],
                  [0, 3, 5, 5, -3],
                  [3, 3, 0, -3, -2],
                  [-5, 1, 0, -4, -2],
                  [2, 1, -5, 0, -1]])
itog = m
print(m)
for i in range(1, 5):
    itog = numpy.matmul(itog, m)
print(itog)