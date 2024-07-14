N = int(input())
constructor = []
for i in range(N,-1,-1):
  if i + sum(list(map(int,list(str(i))))) == N:
    constructor.append(i)

print(sorted(constructor)[0]) if len(constructor)>=1 else print(0)

#진짜 잘 짰다..