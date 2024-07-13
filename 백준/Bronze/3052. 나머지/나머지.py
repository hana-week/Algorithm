A = []
B = [0] * 10
for _ in range(10):
    A.append(int(input()))
for i in range(len(A)):
    B[i] = A[i] % 42
C = len(set(B))
print(C)