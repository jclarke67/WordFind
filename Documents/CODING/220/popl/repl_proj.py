OPERATORS = "*+/-"

def is_operator(operator):
  global OPERATORS
  if operator in OPERATORS:
    return True
  else:
  	return False

def is_integer(value):
	if value.isdigit():
		return True
	if value[0] == "-": 
	# Checks if value is preceded by negative symbol

		if value[1:].isdigit():
			return True
		return False
	return False

def solve(value1, operator, value2):
  if operator == '+':
    solved = value1 + value2
  if operator == '-':
    solved = value1 - value2
  if operator == '*':
    solved = value1 * value2
  if operator == '/':
  	if value2 != 0: 
  	# value2 is the divisor, this prevents zero division

  		solved = value1//value2
  	else: 
  	# if value2 is zero, throw error message and return

  		print("ERROR")
  		return
  return solved

def operate(expr, index):
	print("")
	print("INDEX------ " + str(index))
	print("MATH: " + expr[index-1] + " " + expr[index] + " " + expr[index+1] + " OPERATOR: " + str(expr[index]))
	total = solve(int(expr[index-1]), str(expr[index]), int(expr[index+1]))
	print("TOTAL: " + str(total))
	expr[index-1] = str(total)
	if index+1 < len(expr):
		del expr[index+1]
	del expr[index]
	print("MODIFIED LIST " + str(expr))

	return total

def evaluate(expr):
	index = 0
	result = 0
	if len(expr) == 1:
		result = expr[0]
		print(expr[0])
		return

	if len(expr) == 3:
		result = operate(expr, 1)

	if '*' in expr:
		index = expr.index('*')
		result = operate(expr, index)
		index = 0

	if '/' in expr:
		index = expr.index('/')
		result = operate(expr, index)
		index = 0

	a = 0
	while a < (len(expr)):
		if len(expr) == 3:
			result = operate(expr, 1)
			print(result)
			return
		if is_operator(str(expr[a])):
			index = a
			result = operate(expr, index)
		a+=1
	if expr[0] == 'None':
		return
	print(result)
	return 
		
def parse(userInput):
	prev = "start"
	if is_operator(userInput[-1]):
		print("ERROR")
		return
	for a in userInput:
		if prev == "start":
			if is_integer(a):
				prev = "num"
				continue
			else:
				print("ERROR")
				return False

		if prev == "num":
			if is_operator(a):
				prev = "operator"
				continue
			else:
				print("ERROR")
				return False

		if prev == "operator":
			if is_integer(a):
				prev = "num"
				continue
			else:
				print("ERROR")
				return False
	return True	

def read_expr():
  userinput = ""
  userinput = input("> ")
  if userinput == "":
    print("Goodbye!")
    return
  else:
  	userinput = userinput.split()
  	# print("STRINGS: " + str(userinput))
  	def start(userinput):
  		if parse(userinput) == True:
  			evaluate(userinput)
  	start(userinput) 
  	return read_expr()

def main():
	read_expr()

main()
