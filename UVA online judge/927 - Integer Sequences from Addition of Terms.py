//https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=868
t=int(input())
while t:
    t-=1
    
    s=input()
    pol=s.split(" ")
    pol.pop(0)
    d=int(input())
    k=int(input())
    ini=0
    aux=0
    n=1
    while ini<k:
        aux=0
        grade=0
        for i in range(len(pol)):
            aux+=int(pol[i])*n**grade
            grade+=1
        ini+=n*d
        n+=1
    print(aux)
  
