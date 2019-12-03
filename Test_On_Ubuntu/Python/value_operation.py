# This file contains different styles of values.

print("-------------------------------Math")
# Python------style of Math
x = int(6.3)
y = float(1)
z = complex(6)	#can't convert complex to any other types.

import random	#pyhton didn't have rand(), but it has "random" module.
ran = random.randrange(1,20)
st = "The rand(1,20) shows: {}"	# {} is %d/%s... in C.
print(st.format(ran))	#the format-print in python

print("-------------------------------string")
# Python------style of string
x = str(3.5) 	#string in python is actually str-char[].
ptr = """Line A
Line B
Line C"""	
print(ptr)		# with """, u can enter multi-line string.
print("ptr[3:10]:\n"+ptr[3:10])	#exclude 10 show: 3-9
print(len(ptr))

y = " My Name is LX. "
y1 = y.strip()	#remove blank space in the head and tail.
y2 = y.lower() 	#all to lower-case
y3 = y.upper() 	#all to upper-case
y4 = y.replace("LX", "Xiaoxiao") #replace A to B
y5 = y.split(" ") #split the string to sub-string according to " " blank space
ytr = "{2}\n{0}\n{1}\n{3}\n{4}"
print(ytr.format(y1,y2,y3,y4,y5))


print("-------------------------------bool")
# Python------style of bool
x = bool("abc")	# TRUE --> True  123  ["a","b","c"]  200>30
y = bool(False)	#FALSE --> None  0  ""  {}  ()  []
				#attention: True/False not true/false
z = bool(isinstance(30,int))
print(("bool(""abc)={0}\nbool(False)={1}\nbool(isinstance(30,int)={2})").format(x,y,z))


print("-------------------------------operation")
# Python------operation
x = 2**5	# 2*2*2*2*2
x = 5/2		# 2.5	
y = 25%3
z = 25//3	# 8		5//2(V3.x) <==> 5/2(V2.x)	

x += 3		# *=  /=  %=  //=  **=  &=  |=  ^=  <<=  >>=
bool(3!=4)	# ==  >   <   >=   <=

x = ["apple", "banana"]
y = ["apple", "banana"]	# x and y are different in addr, object
z = x	#	the same addr, object, content.
ptr = "x is y:{0}\nx is z:{1}"
print(ptr.format((x is y),(x is z)))
				# False		True  
bool("banana" in x)		# True
bool("pineapple" in x)	# False
