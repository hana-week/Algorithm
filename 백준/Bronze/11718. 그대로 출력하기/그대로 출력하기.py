while True:
    try:
        S = input()
        print(S)
        if len(S) == '':
            break
    except EOFError:
        break