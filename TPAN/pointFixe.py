import math
def pointFixe(x,e):
   Nmax=1000000000
   n=0
   def fonctiong(x):
      #return (1/(x**2 + 3))
      return (math.log(x**2) * x)
   while n<Nmax-1 :
        xi=fonctiong(x)
        if abs(xi-x)<e :
           break
        n=n+1
        x=xi
        print("g(",xi,") =",fonctiong(xi),"\n")
   if n<Nmax :
      print("convegrnce atteinte en n+1 iteration",n+1,"\nla solution approche est : ",xi)
   else:
       print("la convergence non atteinte ")
   print("g(",xi,") =",fonctiong(xi))
pointFixe(12, 10**(-120))
