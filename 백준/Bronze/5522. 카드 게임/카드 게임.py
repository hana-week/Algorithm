sum=0
while True:
    try:
        sum+=int(input())
    except EOFError:
        break
print(sum)