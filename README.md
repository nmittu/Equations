# Equations

Equations is a simple library to solve mathematical equations using the shunting-yard algorithm

### Features
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
* Any custom functions

Equations can:
* Solve equations
* Determine if two equations are equal
* Convert the equation to Reverse Polish Notation

### Languages
Equation supports the folowing languages:
* Python
* Java
* C

### Usage

#### Solve Equations

##### Python

```python
eq = Equation("2log(3, x)-log(3, 2x)")
print (eq.solve(5, "x"), eq.ReversePolish, eq.isEqual(Equation("log(3, x/2)")))
```

##### Java

```java
Equation eq = new Equation("2log(3, x)-log(3, 2x)");
System.out.printf("%s %s %s\n", eq.solve(5, "x"), eq.reversePolish(), eq.equals(new Equation("log(3, x/2)")));
```

##### C

```c
struct Equation* eq = equation_create("2log(3, x)-log(3, 2x)");
printf("%Lf", equation_solve(eq, 5, "x"));
function_to_print_array(eq->rev_polish, eq->rev_pol_len);
printf("%d", equation_is_equal(eq, equation_create("log(3, x/2)")));
equation_destroy(eq);
```

All of the above will output:
`0.8340437671464689 [2, 3, x, log, *, 3, 2, x, *, log, -] true`

#### Custom Functions

##### Python

```python
eq = Equation("atan2(3x, log(2, x^2))")
eq.addFunc("atan2", 2, lambda x, y: math.atan2(x, y))
print(eq.solve(25))
```

##### Java

```java
Equation eq = new Equation("atan2(3x, log(2, x^2))");
eq.addFunc("atan2", 2, (double[] args) -> Math.atan2(args[0], args[1]));
System.out.println(eq.solve(25))
```

##### C
```c
long double atan2_func(long double args[]){
    return atan2(args[0], args[1]);
}

struct Equation* eq = equation_create("atan2(3x, log(2, x^2))");
equation_add_func(eq, "atan2", 2, atan2_func);
printf("%Lf", equation_solve(eq, 25, "x"));
```

All of the above will output:
`1.4475874257006534`