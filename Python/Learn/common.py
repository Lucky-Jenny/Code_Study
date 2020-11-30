# This file contains Module, Date, Json in Python.

print("-------------------------------Module")
# Python------Module
import Module_X as mx		# Module_X is .py file in .
							# 'as' to change name
mx.funx("LX")
print(dir(mx))      # list all funcs, values in Module

import platform		# 'platform' --> Module of Python
print(platform.system())	# Linux

from Module_X import people
print(people["age"])		# not Module.people["age"] !!!


print("-------------------------------Date")
# Python------Date
import datetime
x = datetime.datetime.now()
print(x)					# 2019-12-03 13:59:09.642708
print(x.year)				# 2019
print(x.strftime("%A"))		# Tuesday

x = datetime.datetime(2020,1,2)		# set datetime
print(x)					# 2020
print(x.strftime("%B"))		# January

# strtime_format: https://www.w3school.com.cn/python/python_datetime.asp


print("-------------------------------Json")
# Python------Json
import json
x = '{ "name":"LX", "age":23, "city":"SH", "favor":"basketball" }'
y = json.loads(x)	# json.loads() --> convert Json to Python
print(y["name"])

x = {
	"name": "LX",
	"age" : 23,
	"city": "basketball",
	"married": True,
	"friends": ("Alex", "Jenny", "KD"),
	"cars": None,
	"pets": [
		{"name": "gugu", "kind": "hamster"},
		{"name": "lucky", "kind": "dog"}
	]
}
y = json.dumps(x)	# json.dumps() --> convert Python to Json
print(y)
print(json.dumps(x, indent=4))	# readeble with indent
print("--------")
print(json.dumps(x, indent=4, separators=(";", "=")))
# separators --> ';' as divided symbol, '=' as equivalence



