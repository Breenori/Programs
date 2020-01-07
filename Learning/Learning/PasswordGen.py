import random
import math

symbol_pool = ['A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Z','1','2','3','4','5','6','7','8','9']
password = ""
characters = 26
total_length = len(symbol_pool)

length = int(input("Please enter password length:"))


for c in range(0, length):
		random.seed()
		rnum = random.random()*total_length

		if(rnum < characters):
			rlower = random.random()
			
			if(rlower < 0.5):
				password += str(symbol_pool[int(rnum)].lower())
			else:
				password += str(symbol_pool[int(rnum)])
		else:
			password += str(symbol_pool[int(rnum)])

print(password)