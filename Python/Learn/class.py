# Here we talk about class in Python.

print("-------------------------------Class")
# Python------Class
class Test:
	x = 5
c1 = Test()		# should have () --> means object
print(c1.x)

class Person:
	def __init__(self, name, age):	# every Class have __init__() to initialize values.
		self.name = name	# self --> this
		self.age = age

	def output(mm):		# Any name can replace "self".
		ostr = "My Name is {0}\tAge: {1}"
		print(ostr.format(mm.name, mm.age))
c1 = Person("LX", 23) 
c1.output()
del c1.age		# delete "age" of c1, not "age" in Person
del c1			# delete object "c1", not class Person
c2 = Person("gyj",23)
c2.output() 	# My Name is gyj	Age: 23
del c2


print("-------------------------------Inherit")
# Python------Inherit
class Person_son(Person):
	pass	# if inherit all methods of parent class use "pass" 	
class Student(Person):
	def __init__(self, name, age, sex):
		super().__init__(name, age)	# <==> Person,__init__(self, name, age)
		self.sex = sex
	def Info(self):
		print("Information:\nName:", self.name, "\nAge:", self.age, "\nSex:", self.sex)

c1 = Student("LX", 23, "male")
c1.Info()



print("-------------------------------iterator")
# Python------Iterator
tuplex = ("apple", "banana", "orange")
iterx = iter(tuplex)
print(next(iterx))		# apple
print(next(iterx))		# banana
print(next(iterx))		# orange

strx = "name"
iterx = iter(strx)
print(next(iterx))		# n
print(next(iterx))		# a
print(next(iterx))		# m
print(next(iterx))		# e

class Numbers:
	def __iter__(self):	# __iter__() is must for iterator
		self.a = 1
		return self
	def __next__(self):	# __next__() is for next(iter)
		if self.a <=4:
			x = self.a
			self.a += 1
			return x
		else:
			raise StopIteration		# Stop iterator by if
num = Numbers()
iterx = iter(num)
for i in iterx:		# loop is another way for iteration
	print(i)





