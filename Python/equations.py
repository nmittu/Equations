import math
import random

def find(s, ch):
    return [i for i, ltr in enumerate(s) if ltr == ch]



class Equation:
	def __init__(self, equation):
		self.equation = equation
		self.ReversePolish = []
		self.shunt()

	def shunt(self):
		operaters = {
			"^": [4, "R"],
			"*": [3, "L"],
			"/": [3, "L"],
			"+": [2, "L"],
			"-": [2, "L"],
			"~": [6, "R"],
			"|": [4, "R"],
			"!": [5, "R"]
		}
		self.operaters = operaters
		equation = self.fixParenMult(self.convertNegetives(self.combineNums(list(self.equation))))
		operatorStack = []
		output = []

		for token in equation:
			if not(token in operaters) and token != "(" and token != ")":
				output.append(token)
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

		while(len(operatorStack)):
			output.append(operatorStack.pop())

		self.ReversePolish = output

	def fixParenMult(self, array):
		indices = [i for i, x in enumerate(array) if x == "("]
		for i in indices:
			if i-1 >= 0 and not array[i-1] in self.operaters:
				array.insert(i, "*")

		indices = [i for i, x in enumerate(array) if x == ")"]
		for i in indices:
			if i+1 < len(array) and not array[i+1] in self.operaters:
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
				if (token.isdigit() or token == ".") and output[-1].isdigit():
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

		
eq = Equation("(x+2)(x+3)")
print(eq.equation, eq.ReversePolish, eq.solve(125), eq.isEqual(Equation("2*(-x)")))