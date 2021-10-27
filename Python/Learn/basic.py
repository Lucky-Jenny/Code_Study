#This is the first and basic tests on Python

print("-------------------------------print")
# Python-----style of value
x,y,z = "A","e",4
print("x="+x)	# str1 + str2
print(type(z))	# <class 'int'>

print("Do u like me? ", end=' ')	# end auto-set:'\n', u can set to other. 
strx = "U should ask {0}"
print(strx.format("Alex"))	# format-print like %s/%d/%p in C
strx = "play"
print("I like", strx, "more than anything.")	# There are blanks around strx, so u don't need to add blank.


print("-------------------------------function")
# Python-----use function
def func():		# must use 'def' to define a function.
	global x	# if change values out of func(), u must use "global".	
	x = "B"
	print("func(): x="+x)
func()
print("x="+x)


print("-------------------------------file")
# Python-----file management
f = open("what.txt")
print(f.readline())
f.close()		# always remember to close f


print("-------------------------------Input")
# Python------Input
print("Enter your name:")
print("Hello",input())		# input() for usr to input string.


a = [0,1,2,3,4]
print(a[-1], a[:-1], a[1:-1], a[::-1])


