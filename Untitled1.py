from turtle import *
def r(x,y):
  rt(x)
  fd(y)

tracer(10)
fd(84)
bgcolor('black')
color('sky blue')
width(3)
for i in range(2003):
  fd(i)
  r(90,i)
  r(90,i)
  r(270,i)
  r(90,i)
  circle(100,100)
done()