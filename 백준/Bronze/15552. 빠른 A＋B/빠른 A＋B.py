import sys

n=int(input())
sum=0

for i in range(n):
    a,b=map(int,sys.stdin.readline().split())
    print(a+b)