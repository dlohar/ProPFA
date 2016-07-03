ProPFA
=============
* Name of the Project: ProPFA.
* Modules:
   - Range Analyzer.
   - Invariant Generation.
   - Path Extraction, WP and Volume Computation, and returns the overall Failure Probability with a confidence measure.

Description of Modules
-------------------------------

+ **Range Analyzer (yet another range analyzer):**
This module is a minimalistic Range Analyzer for C-type programs. It analyzes a program statically and determines an interval of values for each of its variables at each program point. It can also compute the set of 
discrete values each program variable can take. This tool is used in conjunction with the invariant generation tool 
called "InvGen" for generating linear arithmetic invariants. The range analyzer module is divided into two major parts: 
  - Frontend
		+ Parser for the input program, which generates the parse tree and abstract syntax tree(AST).
		+ Data Flow Equation Generator which takes as input the abstract syntax tree generated by the parser module, traverses the AST and produces a control flow graph which is used to generate the set of data flow equations. The data flow module then generates a set of data-flow equations from the control flow graph it generated previously.
  - Backend that solves those data flow equations generated by the frontend.
		+ Analysis in the concrete domain
		+ Analysis in the abstract domain.
 The abstract domain analyzer also exploits the concept of widening technique to minimize the number of iterations while solving the equations. Both of these sub engines solve the data flow equations separately in their respective domains and output the ranges of program variables at each program point. 

+ **Invariant Generation:**
The input program is parsed and for each while loop without any failure assertion inside the loop block, ProPFA uses 
InvGen to generate invariants. Initial templates for InvGen are provided by the range analyzer module of ProPFA. InvGen 
implements constraint solving approach and finds an instantiation of the template parameters that yields a safe invariant 
satisfying the subsequent assertion. ProPFA uses the generated invariants to abstract out the loops in the input program 
to accelerate failure analysis.
If no invariant is generated in any of these cases, ProPFA allows loop unrolling by user provided unrolling factors.

+ **Path Extraction, WP and Volume Computation, and returns the overall Failure Probability with a confidence measure:**
After abstracting out the loops wherever possible, ProPFA extracts all possible program execution paths depth-wise. ProPFA 
generate weakest preconditions for each success path by employing WP plug-in of Framework for Modular Analysis of C program 
(Frama-C). We compute the volume of the convex polytope generated by the intersection of generated weakest preconditions of 
success paths with the initial input regions. The discrete domain model counting tool `LattE' is integrated with ProPFA for
this purpose.

Limitations on input C program 
===============================
1. ProPFA considers uniform distribution for input variables within a specified region. It also allows discrete uniform regions
of input variables associated with probability distribution functions.
2. ProPFA can work on real domain. It provides necessary handling before executing LattE which only works on integer domain.
3. Range analysis only works for integer programs. If float values are there inside the input program it exits from this module and all loops 
are unrolled.
4. This version of ProPFA does not handle nested while loops, complex data structures like pointers, structures and function calls.
5. This version of ProPFA can only handle arrays if they do not appear in the Weakest Precondition.
6. Only SINGLE LINE comments are allowed.
7. only INT and VOID data types are allowed.
8. only WHILE loop and simple IF ELSE conditions are allowed.
9. POINTERS, ARRAYS and STRUCTURES are NOT allowed.
10. FOR, SWITCH, DO-WHILE and ELSE-IF constructs are NOT allowed.
11. BREAK and CONTINUE statements are NOT allowed.
12. All variables used in a function are declared either globally or in the begining of the function.
13. **The first line of the input program must be**
```c
void assert(int dummy_var) {}
```
*If any error occurs during installation, try downloading the dependencies individually, keep them in one folder and try!*

**It may be noted that, ProPFA is strictly limited to the limitations of the external tools it integrates with.**
 
Dependencies
------------------

+ Platform: 32 bit Ubuntu Distribution
+ External Tools:
	- WP-plugin of Frama-C (Version: Neon-20140301)
	- Frontend
	- InvGen
	- LattE (Version: latte-integrale-1.7.3)
+ Other Requirements: 
	- Python (Version: 2.7 or higher)
	- sympy-1.0
	- mpmath-0.19
	- OCAML (Version: 3.12.1)

Build Instructions
=====================

`./configure` (It will take around 20-30mins! You may take a break!)

`make`

Run Instructions
====================
`cd src`

`./driver.py <INPUT_C_FILE> <FUNCTION_NAME>`

`./ProPFA <INPUT_C_FILE>`

Test
====================
For testing purpose we've provided 2 sample input files named `sample_input.c` and a `latte_input` in the directory `src`. You may modify the content of these 2 files and test with different inputs. The file `latte_input` **MUST NOT** be renamed, as it's being used internally with the same name. The file `sample_input.c` contains a single function called `test`. To run, follow the following steps :

`cd src`

`./driver.py sample_input.c test`

`./ProPFA sample_input.c`

`cd ..`

`make clean`

Input File Format
======================

ProPFA takes two input files.

1. input_C_file: Input C file.
	- Format: Normal C-syntax (with all the limitations mentioned above).
	- Assertions are placed using the keyword assert.
2. input_latte_file: Range information in an input file (**must** be named as `latte_input`).
	- Format: Identical to the LattE halfspace representation.

Here is an example of a sample `latte-input` file:

Let V be the input polytope in terms of linear inequalities `(Ax<=b)` along with the distribution probabilities with the keyword **`probabilities`** after the linear inequalities for the ranges of variables `v_1` to `v_k`. The first line contains all the variables in some order (e.g: `v_1 < v_3 < v_2`). The number of regions for all variables (`r_1` no. of regions for variable `v_1`, `r_2` no. of regions for variable `v_2`, ... , `r_k` no. of regions for variable `v_k`) are need to be provided in the second line as follows:

`d r_1 r_2 r_3 ... r_k` where, `d` being the number of input variables used.

Let `V= {(x,y): [0 <= x <= 100 with probability 0.5], [100 < x <= 200 with probability 0.5], [0 <= y <= 100 with probability 0.5], [100 < y <= 100 with probability 0.5]}`. Corresponding to this, the input file will be:
```
x < y
2 2 2
0 -1 0
100 1 0
-100 -1 0
200 1 0
probabilities 0.5 0.5
100 1 0
-100 -1 0
200 1 0
probabilities 0.5 0.5     
```

We've provided a sample `sample_input.c` and a `latte_input` file in the directory `src`. You may modify these or use your own.

Read Authors
-------------------------
Please email us bug reports!!
The project is under constant improvement!
* Debasmita Lohar [debasmita.lohar@cse.iitkgp.ernet.in]
* Anudeep Dunaboyina [danudeep@cse.iitkgp.ernet.in]
* Dibyendu Das [dibyendud@iitkgp.ac.in]
* Soumyajit Dey	[soumya@cse.iitkgp.ernet.in]
