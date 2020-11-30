# This is meanly about different structs of values

print("-------------------------------List")
# Python------list
lista = ["a", "b", "c", "d", "e"]
print(lista)
print(lista[-1])	# e  --> the last one
print(lista[-3:-1])	# ['c', 'd'] exclude -1
print(len(lista))	# 5

lista.append("f");print(lista)	# ['a', 'b', 'c', 'd', 'e', 'f'] 
lista.insert(2,"x");print(lista)# ['a', 'b', 'x', 'c', 'd', 'e', 'f'] 
lista.remove("x");print(lista)	# ['a', 'b', 'c', 'd', 'e', 'f']	
lista.pop();print(lista)		# ['a', 'b', 'c', 'd', 'e'] 
del lista[0];print(lista)		# ['b', 'c', 'd', 'e']
lista.reverse();print(lista)	# ['e', 'd', 'c', 'b']
lista.clear();print(lista)		# []
del lista						# (null)

lista = ["a", "b", "c"]	# <class 'tuple'>  must have ','ista = ["a", "b", "c"]
listb = lista.copy()	# copy method1
listb = list(lista)		# copy method2
listb = ["d", "e", "f"]
listc = lista + listb	# link method1 +
lista.extend(listb)		# link method2 extend(list)
for x in listb:			# link method3 append(item)
	lista.append(x)	

name = list("xiao")		# ['x', 'i', 'a', 'o']
print(name)
name = list(("xiao",))	# ['xiao']  | must have ','
print(name)


print("-------------------------------Tuple")
# Python------tuple
tuplea = ("A", "B", "C", "D")	# Once created, tuple can't be modified(include add, change and delete on item).
print(tuplea[-3:-1])	# ('B', 'C')	# the method of print is the same as 'List'.
lista = list(tuplea)	# the only way to modify is turning to 'List'.
tupleb = ("E", "F", "G", "H")
tuplea += tupleb	# link two tuples by +=
print(tuplea)

tuplea = ("apple")
print(type(tuplea))	# <class 'str'> 
tupleb = ("apple",) 
print(type(tupleb)) # <class 'tuple'>  must have ','

tuplea = ("a", "f", "t", "a", "b", "t", "f", "b", "a")
print(tuplea)
print(tuplea.count("a"))	# 3 | return frequency of 'a'
print(tuplea.index("b"))	# 4 | return the first addr of 'b'


print("-------------------------------Set")
# Python------Set
seta = {"a", "b", "c", "d"}	# Once created, Set can't modify items but can add and delete items.
print(seta)		# Set is out -of-order, so 'seta[2]' is wrong.
seta.add("e")	# the position of 'add' is uncertain.
seta.update(["f", "g"])		# add multi items
seta.remove("f")			# remove the specified item
seta.clear()
del seta

seta = {"a", "b", "c"}
setb = {"d", "e", "f"}
print(("a = {0}\nb = {1}").format(seta, setb))
seta.update(setb)		# link --> update, union	
setc = seta.union(setb)	# update & union will remove duplicate items.
print(("a.update(b) = {0}\na.union(b)  = {1}").format(seta, setc))


print("-------------------------------Dictionary")
# Python------Dictionary
dicta = {
	"name": "LX",
	"age" : 23,
	"fav" : "ball"
}		# like Set, Dict is out-of-order. It doesn't have index.
print(dicta)
x = dicta["fav"]	# <==> dicta.get("fav")
print(x)
print("loop get:")

for x in dicta.values():	# loop get values
	print(x)

for x, y in dicta.items():	# loop get items
	print(x,y)

dicta["like"] = "play"		# add an item
print(dicta)

dicta.pop("like")			# delete item-"like"
dicta.popitem()				# delete an item in random
dicta.clear()				# clear
#dictb = dicta		wrong!!!
dictb = dicta.copy()		# assign values to dictb

girl = {
	"name": "gyj",
	"age" : 24
}
boy = {
	"name": "lx",
	"age" : 23
}
family = {				# nested structure
	"boy" : boy,
	"girl": girl
}
print(family)

