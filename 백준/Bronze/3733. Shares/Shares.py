while True:
    try:
        a,b=map(int,input().split())
        print(b//(a+1))
    except EOFError:
        break