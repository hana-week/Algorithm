n = int(input())
a = [100]*26
g = n

for _ in range(n):
    a=[100]*26
    s = input()
    for i in range(len(s)):
        if a[ord(s[i])-97]==100: a[ord(s[i])-97] = i
        else: 
            if i-a[ord(s[i])-97] > 1: 
                g -= 1
                break
            else:
                a[ord(s[i])-97] = i
    
print(g)