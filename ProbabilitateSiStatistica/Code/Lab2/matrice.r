vector = 1:12
mat = matrix(vector, nrow = 3, byrow=TRUE)
mat
m1 = rbind(mat, 4:7)
m1
m2 = cbind(m1, 4:7)
m2

l2 = list(a = 1, b = c(1, 7), c = matrix(1:10, nrow = 2))
l2
l2[[1]]
class(l2[[1]])
