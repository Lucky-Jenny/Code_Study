# This is mainly about file-system in Python.

print("-------------------------------File")
# Python------File

f = open("what.txt", "a")
f.write("\nThis is added by file.py")
f.close()		# always remember f.close() !!!

f = open("what.txt", "rt")	
print(f.read())			# read whole string
print(f.read(5))		# read first five values
print(f.readline())		# read the first line
f.close()

import os		# if delete file, must import module 'os'
if os.path.exists("wer.txt"):
	os.remove("wer.txt")
else:
	print("The file doesn't exist")

