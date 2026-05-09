```
--------------------------------------------------
Reference manual for Pilha.
--------------------------------------------------

0 - Index.
--------------------------------------------------
  1 - Introduction.
  
  2 - Concepts.
    2.1 - Default type.
    2.2 - Data stack.
    2.3 - Call stack.
    2.4 - Variables.
    2.5 - Targets.
    2.6 - Error handling.
    
  3 - Syntax.
  
  4 - Default commands.
    4.1 - Stack management.
    4.2 - Arithmetic operations.
    4.3 - Boolean logic.
    4.4 - Control flow.
    
  5 - The C API.
  
1 - Introduction.
--------------------------------------------------
  Pilha is a lightweight and embeddable scripting
  language, focused on stack manipulation and
  supports procedural programming.
  Pilha is written as a C library, with a minimal
  set of functions for embedded and fast use.
  
2 - Concepts.
--------------------------------------------------
  2.1 - Default type.
    All values are, by default, 32-bit integers.
  
  2.2 - Data stack.
    The data stack is a list of values.
    You can push a value as the last element and
    pop the last element as a value.
  
  2.3 - Call stack.
    The call stack is a separate stack used by
    call and return for sub-routine support.
  
  2.4 - Variables.
    Variables are key-to-value pairs in a table.
    You can store values to keys and
    load values from keys.
  
  2.5 - Targets.
    Targets are variables identified by a colon
    and are used as a position for control flow.
  
  2.6 - Error handling.
    If you write an invalid command or try to
    read an unknown file, you'll get an error at
    compile time.
    If you try to pop an empty stack or try to
    return without a call, you'll get an error at
    run time.
    Trying to use an undefined variable or
    dividing by 0 returns 0 instead of getting
    an error message.
  
3 - Syntax.
--------------------------------------------------
  Syntax is how the interpreter reads text and
  writes code to a pilha struct.
  It is case-insensitive and ignores spaces or
  text written after semicolons.
  Line breaks are used to terminate commands,
  execution ends automatically at file end.
  
4 - Default commands.
--------------------------------------------------
  4.1 - Stack management.
    Push X      ( A B -- A B X )
    PushAt X    ( A B -- A B Variable[X] )
    Pop         ( A B -- A )
    PopAt X     ( A B -- A ; Variable[X] = B )
    Copy        ( A B -- A B B )
    Swap        ( A B -- B A )
  
  4.2 - Arithmetic operations.
    Add         ( A B -- A+B )
    Subtract    ( A B -- A-B )
    Multiply    ( A B -- A*B )
    Divide      ( A B -- A/B )
    Modulo      ( A B -- A%B )
    Increment   ( A -- A++ )
    Decrement   ( A -- A-- )
    Absolute    ( A -- |A| )
    Minimum     ( A B -- Min(A,B) )
    Maximum     ( A B -- Max(A,B) )
    Random      ( A -- Random(0,A) )
  
  4.3 - Boolean logic.
    Equal       ( A B -- A==B )
    EqualNot    ( A B -- A!=B )
    More        ( A B -- A>B )
    MoreEqual   ( A B -- A>=B )
    Less        ( A B -- A<B )
    LessEqual   ( A B -- A<=B )
    And         ( A B -- A&&B )
    Or          ( A B -- A||B )
    Not         ( A -- !A )
  
  4.4 - Control flow.
    Jump X      ( Jump to target )
    IfTrue      ( Execute next command if -
                - pop value is not zero )
    IfFalse     ( Execute next command if -
                - pop value is zero )
    Exit        ( End execution )
    Call X      ( Call sub-routine )
    Return      ( Return from sub-routine )
    
5 - The C API.
--------------------------------------------------
    pilha *pilha_new();
      // Returns a new pilha struct.
    void pilha_delete(pilha* p);
      // Deletes an existent pilha struct.
    void pilha_file(pilha* p, char* file);
      // Reads file and writes bytecode to pilha.
    void pilha_run(pilha* p);
      // Executes current bytecode from pilha.
    void pilha_push(pilha* p, i32 value);
      // Push value to pilha stack.
    i32 pilha_pop(pilha* p);
      // Pop value from pilha stack.
    i32 *pilha_variable(pilha* p, char* key);
      // Get pointer to pilha variable.
```
