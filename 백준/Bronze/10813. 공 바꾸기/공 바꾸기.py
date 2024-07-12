N, M = map(int, input().split())
basket=[]
a=0
for k in range(N):
    a+=1
    basket.append(a)

for _ in range(M):
    i, j = map(int, input().split())
    basket[i-1],basket[j-1] = basket[j-1],basket[i-1] 

for n in range(N):
    print(basket[n], end = ' ')
