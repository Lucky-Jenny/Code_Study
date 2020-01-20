# This file will include all kinds of logical structures in Python.

print("-------------------------------If--Else")
# Python------If-Else
a = 600
b = 400
if a > b:
	print(("{0} is bigger than {1}").format(a, b))
elif a < b:
	print(("{0} is smaller than {1}").format(a, b))
elif a == b:
	print(("{0} equals {1}").format(a, b))
else:	pass	# if: XXX could be in-line
		#pass means continue in C


print("-------------------------------While")
# Python------While
i = 1
while i < 4:
	print(i) 
	i += 1
else:
	print("i =4")


print("-------------------------------For")
# Python------For
fire = ["a", "b", "c", "d"]
for i in fire:
	print(i)
	if i == "c":
		break

strx = "a"
for i in range(6):	# control the frequency of the following codes.
	print(strx)
	strx += "x"
strx = "b"
for i in range(2, 10, 3):	# for(i=2; i<10; i+=3) 3 --> step-length
	print(strx)
	strx += "x"

for i in [0, 1, 2]:
	pass			# codes in for should not be null!!


print("-------------------------------Function")
# Python------Function
def fun():			# must use 'def' to define functions.
	print("call fun().")
fun()


def funx(x, y, z):	# multi-values in function
	print("call funx(x): " + x + " " + y + " " + z)
funx("what", "is", "it")			# call with value "lx"


def funo(er = "lx"):
	print("My name is " + er)
funo("gyj")			# My name is gyj
funo()				# My name is lx


def funm(x3, x1, x2):	# order doesn't matter
	print("Here is : " + x1 + " " + x2 + " " + x3)
funm(x2 = "apple", x3 = "orange", x1 = "peach")


def funw(*x):		# *x means unknown number of values
	strx = "funw(*x): "
	for i in x:	
		strx += " " + i	# not x[i] !!!
	print(strx)
funw("try", "like", "lie", "mike")


def fbnc(n):		# recursion function: Febonacci Sequence
	if(n == 2 or n == 1):
		return 1
	elif(n <= 0):	pass
	else:
		return fbnc(n-1) + fbnc(n-2)

print("Febonacci Sequence:")
for i in range(1, 12):		# exclude end-number
	print(fbnc(i), end=' ')
print()


print("-------------------------------Lambda")
# Python------Lambda
x = lambda a, b : a* b	# Lambda is an anonymous function
print(x(5, 6))		# 30

def lamfun(n):	
	return lambda a : a * n
double = lamfun(2)	# double = lambda a : a * 2
triple = lamfun(3)	# triple = lambda a : a * 3
print(double(10))
print(triple(10))


