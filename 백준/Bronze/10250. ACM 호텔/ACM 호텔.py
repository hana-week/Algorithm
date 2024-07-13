t = int(input())

for _ in range(t):
    h,w,n = map(int,input().split())
    y = n%h
    x = n//h + 1
    if n % h == 0:
        y = y+h
        x = x-1

    print(100*y+x)