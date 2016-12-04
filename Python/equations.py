import math
import random
import search

def find(s, ch):
    return [i for i, ltr in enumerate(s) if ltr == ch]

def is_number(s):
    try:
        float(s)
        return True
    except ValueError:
        return False

class Equation:
	def __init__(self, equation):
		self.equation = equation
		self.ReversePolish = []
		self.operaters = {
			"^": [4, "R"],
			"*": [3, "L"],
			"/": [3, "L"],
			"+": [2, "L"],
			"-": [2, "L"],
			"~": [6, "R"],
			"|": [4, "R"],
			"!": [5, "R"]
		}

		self.functions = {
			"log": [2, lambda x, y: math.log(y, x)],
			"ln": [1, lambda x: math.log(x)],
			"abs": [1, lambda x: abs(x)],
			"acos": [1, lambda x: math.acos(x)],
			"asin": [1, lambda x: math.asin(x)],
			"atan": [1, lambda x: math.atan(x)],
			"cos": [1, lambda x: math.cos(x)],
			"sin": [1, lambda x: math.sin(x)],
			"tan": [1, lambda x: math.tan(x)]
		}
		self.shunt()

	def shunt(self):
		
		functions = self.functions
		operaters = self.operaters
		equation = self.fixVarMult(self.fixParenMult(self.convertNegetives(self.combineNums(self.findFuncTokens(list(self.equation.replace(" ", "")))))))
		operatorStack = []
		output = []

		for token in equation:
			if not(token in operaters) and not(token in functions) and token != "(" and token != ")" and token != ",":
				output.append(token)
			elif token in functions:
				operatorStack.append(token)
			elif token == ",":
				while len(operatorStack) and operatorStack[-1] != "(":
					output.append(operatorStack.pop())
			elif token in operaters:
				while(len(operatorStack) and operatorStack[-1] in operaters and ((operaters[token][1] == "L" and operaters[token][0] <= operaters[operatorStack[-1]][0]) or (operaters[token][1] == "R" and operaters[token][0] < operaters[operatorStack[-1]][0]))):
					output.append(operatorStack.pop())
				operatorStack.append(token)
			elif token == "(":
				operatorStack.append(token)
			elif token == ")":
				while len(operatorStack) and operatorStack[-1] != "(":
					output.append(operatorStack.pop())
				if len(operatorStack):
					operatorStack.pop()
				if operatorStack[-1] in functions:
					output.append(operatorStack.pop())

		while(len(operatorStack)):
			output.append(operatorStack.pop())

		self.ReversePolish = output

	def findFuncTokens(self, array):
		for func in self.functions:
			while search.search(array, list(func)) != None:
				i = search.search(array, list(func))
				array[i] = func
				for j in range(len(func)-1):
					del array[i+1]

		return array

	def fixVarMult(self, array):
		for i in range(len(array)):
			if not array[i] in self.operaters  and not is_number(array[i]) and array[i] != "(" and array[i] != ")" and array[i] != ",":
				if i-1 >= 0 and not array[i-1] in self.operaters and not array[i-1] in self.functions and array[i-1] != "(" and array[i-1] != ")"and array[i-1] != ",":
					array.insert(i, "*")
					i = i-1
		return array
	
	def fixParenMult(self, array):
		indices = [i for i, x in enumerate(array) if x == "("]
		for i in indices:
			if i-1 >= 0 and not array[i-1] in self.operaters and not array[i-1] in self.functions and array[i-1] != ",":
				array.insert(i, "*")

		indices = [i for i, x in enumerate(array) if x == ")"]
		for i in indices:
			if i+1 < len(array) and not array[i+1] in self.operaters and not array[i-1] in self.functions and array[i+1] != ")" and array[i+1] != ",":
				array.insert(i+1, "*")

		return array
				 

	def convertNegetives(self, array):
		indices = [i for i, x in enumerate(array) if x == "-"]
		for i in indices:
			if i-1 <0 or array[i-1] in self.operaters or array[i-1] == "(":
				array[i] = "~"
		return array

	def combineNums(self, array):
		output = []
		for token in array:
			if len(output):
				if (token.isdigit() or token == ".") and (is_number(output[-1])):
					output[-1] = output[-1] + token
				else:
					output.append(token)
			else:
				output.append(token)
		return output

	def solve(self, varVal, varName="x"):
		ReversePolish = list(self.ReversePolish)
		for n, i in enumerate(ReversePolish):
			if i == varName:
				ReversePolish[n] = varVal

		i = 0
		while i < len(ReversePolish):
			if ReversePolish[i] in self.operaters:
				if ReversePolish[i] == "^":
					del ReversePolish[i]
					ReversePolish[i-2] = math.pow(float(ReversePolish[i-2]), float(ReversePolish.pop(i-1)))
					i = i-2
				elif ReversePolish[i] == "*":
					del ReversePolish[i]
					ReversePolish[i-2] = float(ReversePolish[i-2]) * float(ReversePolish.pop(i-1))
					i = i-2
				elif ReversePolish[i] == "/":
					del ReversePolish[i]
					ReversePolish[i-2] = float(ReversePolish[i-2]) / float(ReversePolish.pop(i-1))
					i = i-2
				elif ReversePolish[i] == "+":
					del ReversePolish[i]
					ReversePolish[i-2] = float(ReversePolish[i-2]) + float(ReversePolish.pop(i-1))
					i = i-2
				elif ReversePolish[i] == "-":
					del ReversePolish[i]
					ReversePolish[i-2] = float(ReversePolish[i-2]) - float(ReversePolish.pop(i-1))
					i = i-2
				elif ReversePolish[i] == "~":
					del ReversePolish[i]
					ReversePolish[i-1] = -float(ReversePolish[i-1])
					i = i-1
				elif ReversePolish[i] == "|":
					del ReversePolish[i]
					ReversePolish[i-1] = math.sqrt(float(ReversePolish[i-1]))
					i = i-1
				elif ReversePolish[i] == "!":
					del ReversePolish[i]
					ReversePolish[i-1] = math.factorial(float(ReversePolish[i-1]))
					i = i-1
			elif ReversePolish[i] in self.functions:
				args = [];
				arity = self.functions[ReversePolish[i]][0]
				for j in range(0, arity):
					if(j):
						args.append(float(ReversePolish.pop(i-arity+j)))
					else:
						args.append(float(ReversePolish[i-arity]))
				ReversePolish[i-arity] = self.functions[ReversePolish[i-arity+1]][1](*args)
				del ReversePolish[i-arity+1]
				i = i-arity

			i = i+1

		return float(ReversePolish[0])

	def isEqual(self, equation):
		randomNumbers = []
		for i in range(0, 10):
			randomNumbers.append(random.randint(0, 1000000))

		equal = True
		for i in randomNumbers:
			if self.solve(i) != equation.solve(i):
				equal = False

		return equal
	def addFunc(self, name, arity, func):
		self.functions[name] = [arity, func]
		self.shunt()

		
eq = Equation("add(2, abs(-3))")
eq.addFunc("add", 2, lambda x, y: x+y)
print(eq.ReversePolish)
print(eq.equation, eq.ReversePolish, eq.solve(125), eq.isEqual(Equation("x-0.00000000001")))
