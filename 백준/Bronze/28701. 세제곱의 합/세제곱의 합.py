def sum(n):
    if n>=1:
        return n+sum(n-1)
    else:
        return 0
x=int(input())
print(sum(x))
print(sum(x)**2)
print(sum(x)**2)