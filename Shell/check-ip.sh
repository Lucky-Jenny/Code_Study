#!/bin/bash

read -p "Input IP Addr:" ip

Check()
{
	echo "IP: $1"
	arry=($(echo $1 | tr '.' ' '))
	isValid=1
	i=0

	for x in ${arry[@]}
	do
		i=$(($i+1))
		# Judge x is number
		grep '^[[:digit:]]*$' <<< $x > /dev/null
		if [ "x$?" = "x0" ]; then
			# Judge range: 0 < x < 256, i = 4
			if [ $x -gt 255 ]; then
				isValid=0
			fi
		else
			isValid=0	
		fi
	done

	if [ "x$isValid" = "x1" -a "k$i" = "k4" ]; then
		echo -e "\033[40;32mValid\033[0m"
	else
		echo -e "\033[40;31mInvalid\033[0m"
	fi
}

Check $ip

#Check 25.255.255.23.34.345
#Check 25.255.255.23
#Check 2gr.gg34..

exit 0

