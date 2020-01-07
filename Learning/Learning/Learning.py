import math

a = int(input("Please enter a:"))
b = int(input("Please enter b:"))
c = int(input("Please enter c:"))

if(a != 0):
	p = b / a
	q = c / a
	D = pow(p/2,2) - q

	if(D < 0):
		print("x1 = " + str(-p/2) + "+i" + str(math.sqrt(-D)))
		print("x2 = " + str(-p/2) + "-i" + str(math.sqrt(-D)))
	elif(D >= 0):
		x1 = -(p/2) + math.sqrt(D)
		x2 = -(p/2) - math.sqrt(D)
		print("x1 = " + str(x1))
		print("x2 = " + str(x2))
else:
	if(b != 0):
		x = -b / c
		print("x = " + str(x))
	else:
		if(c != 0):
			print("There are no values")
		else:
			print("There are infinite values")
