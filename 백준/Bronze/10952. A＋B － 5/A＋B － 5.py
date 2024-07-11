import sys
while True:
    a,b=map(int,sys.stdin.readline().split())
    if str(a)=='0' and str(b)=='0':
        break
    else:
        print(a+b)
