**4/28/2025**
*  **feedback.md is for instructor use only. DO NOT change the feedback.md**; make a copy if needed
* class definition style & standards:  first, member vars  none per line and do not forget to initialize them;  second functions: separate group of functions  by a blank line; either matching setter/getter pairs or list all setters back to back and list all getters back to back; start with a default c’tor, followed by  copy c’tor (if any), then other c’tors in the order of increased number of arguments, d’tor- right after c’tor(s), overloaded functions- list them back to back in the order of increased number of arguments;  all accessor/getter functions should be const; all functions with more than one statement should be normal (defined externally, outside of the class and below main()), no inline functions with more than one statement; initialize all member variables to appropriate default values at the time of definition; all member variables must be private; classes must provide a strong exception guarantee; must have default c’tor; implement Rule of Three when necessary
* no test runs -10
* battle  does not comply with the assignment -10
* classes do not provide strong exception guarantee -10
* if a user enters a value of a wrong data type, the program goes into an infinite loop; should create a highly reusable function that takes an error message string as a parameter, clears the failed input and outputs the error message to be called in the default case of the menu switch -5
* missing default c’tor(s) -5
* does not print army stats  before and after the battle -5
* inline functions do not adhere to the best practices -5 
* getter/accessor function(s) allow object state modification -5
* class design: can only battle when creating a new Game obj? army class should be responsible for validation of army name and size, etc -2
* readability, comments; do not state the obvious, do not reiterate/duplicate the code, remove outdated code; comments supposed to help and not create unnecessary clutter; "Code never lies, comments sometimes do." - Ron Jeffries”; what is the purpose of the comments as this(ese) one(s); -2
```text
//FUNCTION DECLERATIONS---------------------------------------------------------------------------------
string checkName(string name);
* multiple return statements in a non-recursive function; may result in unreachable return; use if/else, use a variable to store the results and return the variable; e.g. a function to check the length of a string, function to validate account number,  short validations can be done in the return statement; e.g.  return a<MIN_LENGTH;   -2 -5
* what if numbers change? if it is not 1 or 0 make it const; in case of ASCII values, use chars, e.g., temp>’a’  -2
* 172 and like, poor  and redundant logic;  setCreature()  with 4 args should be the only functions used for validation; exceptions should be caught and dealt with in setCreature()  with 4 args; this way validation and set statements are not all over the class code; no need to rethrow exceptions; if set creature called by a c’tor and throws an exception, a creature object will not be created, you might have an id for an object for not the objects;  see assignment; discussed in class -2 -5 -10

