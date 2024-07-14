from itertools import combinations
N, M = map(int, input().split())
arr = list((map(int, input().split())))
max_sum = 0
for combo in combinations(arr, 3):
    result=sum(combo)
    if result <= M:
        max_sum=max(max_sum, result)
print(max_sum) 