# Equations

Equations is a simple library to solve mathematical equations such as `5log(10, x^2) When x=15`

#### Features
Equation supports the following opperations and functions:
* ^
* \*
* /
* \+
* \-
* | (square root)
* !
* log(b, x)
* ln(x)
* abs(x)
* cos(x)
* sin(x)
* tan(x)
* acos(x)
* asin(x)
* atan(x)

Equations can:
* Solve equations
* Determine if two equations are equal
* Convert the equation to Reverse Polish Notation

#### Languages
Equation supports the folowing languages:
* Python
* Java

#### Usage

##### Python

```python
eq = Equation("2log(3, x)-log(3, 2x)")
print (eq.solve(5, "x"), eq.ReversePolish, eq.isEqual(Equation("log(3, x/2)")))
```

#### Java

```java
Equation eq = new Equation("2log(3, x)-log(3, 2x)");
System.out.printf("%s %s %s\n", eq.solve(5, "x"), eq.reversePolish(), eq.equals(new Equation("log(3, x/2)")));
```

Both of the following will output:
`0.8340437671464689 [2, 3, x, log, *, 3, 2, x, *, log, -] true`
