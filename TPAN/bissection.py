import math
def Bissection(a,b):
  def fonctiont(x):
    return (math.exp(x) - (4*x))
    

  n=0
  while abs(b-a)>=(10 **(-80)) : 
     c=(a+b)/2
     if fonctiont(c)==0:
        print("la Racine est c=",c)
        break
     if fonctiont(c)*fonctiont(b)<0:
        a=c
     else: 
        b=c
     n=n+1
     print(n)
  print("la racine est c =", c)
  print("nombre d'iterations =", n)
  print(math.exp(c) - 4*c)
Bissection(0, 2*math.log(2))
