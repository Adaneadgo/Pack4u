#1
tempC = int(input("Input the temperature in Celsius: "))
tempF = (9.0/5.0) * tempC + 32.0
print (tempC, "C = ",tempF, "F  " )

#2a
f,n=1,0
while n<20:
    print('{0} != {1}'.format(n, f))
    n+=1
    f*=n

#2b
f=1
for n in range(20):
    if n!=0:
        f*=n
    print('{0} != {1}'.format(n, f))

#3
for i in range(10): #or for x in range(1, 11):
        print (i, end=" ")
        print (i**2, end=" ",)
        print (i**3)
print()
for x in range(1, 11):
    print('{0:2d} {1:5d} {2:4d}'.format(x, x*x, x*x*x))

#4 gcd
print()
x_old=int(input("enter the first number: "))
y_old=int(input("enter the second number: "))
x,y=x_old,y_old
while x!=y:
    if x>y:
        x-=y
    else:
        y-=x
print('gcd of {0} and {1} is {2}'.format(x_old,y_old,x))

#euclid
print()
a_old=int(input("enter the first number: "))
b_old=int(input("enter the second number: "))
a,b=a_old,b_old
while b!=0:
    c=a    
    a=b
    b=c%b
   
print('gcd of {0} and {1} is {2}'.format(a_old,b_old,a)) 


 
