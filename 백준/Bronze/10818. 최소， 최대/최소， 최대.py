import sys

input = lambda: sys.stdin.readline().strip()

N = int(input())
a = list(map(int, input().split()))

print(min(a), max(a))