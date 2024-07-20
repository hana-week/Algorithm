#15 16 17            2 2 75
#19 32 90

# a 🍰 b = (a.z + b.x, a.y × b.y, a.x + b.z)

a,b,c=map(int,input().split())
d,e,f=map(int,input().split())

print(d-c,e//b,f-a)