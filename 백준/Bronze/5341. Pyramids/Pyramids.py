def sum(n):
    if n>=1:
        return n+sum(n-1)
    else:
        return 0
while True:
    x=int(input())
    if x==0:
        break
    else:
        print(sum(x))