def pf(number):
	factors=[]
	d=2
	while(number>1):
		while(number%d==0):
			factors.append(d)
			number=number/d
			print(factors)
		d+=1
	return factors

factors = pf (122)
print(factors)