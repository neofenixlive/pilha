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
    used for control flow support.
  
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
  writes code, it is case-insensitive and
  ignores spaces or anything after semicolons,
  line breaks are used to terminate commands.
  
  
  
4 - Default commands.
--------------------------------------------------
  4.1 - Stack management.
    PUSH NUM     ( A B -- A B NUM )
    POP          ( A B -- A )
    PUSH VAR     ( A B -- A B VAR )
    POP VAR      ( A B -- A -
                 - VAR is defined as B )
    COPY         ( A B -- A B B )
    SWAP         ( A B -- B A )
  
  4.2 - Arithmetic operations.
    ADD          ( A B -- A+B )
    SUBTRACT     ( A B -- A-B )
    MULTIPLY     ( A B -- A*B )
    DIVIDE       ( A B -- A/B )
    MODULO       ( A B -- A%B )
    INCREMENT    ( A -- A++ )
    DECREMENT    ( A -- A-- )
  
  4.3 - Boolean logic.
    EQUAL        ( A B -- A==B )
    MORE         ( A B -- A>B )
    LESS         ( A B -- A<B )
    AND          ( A B -- A&&B )
    OR           ( A B -- A||B )
    NOT          ( A -- !A )
  
  4.4 - Control flow.
    JUMP VAR     ( Execution index jumps to VAR )
    BRANCH VAR   ( Execution index jumps to VAR -
                 - if pop value is true )
    CALL VAR     ( Call sub-routine )
    RETURN       ( Return from sub-routine )
    HALT         ( End execution )
  
  
  
5 - The C API.
--------------------------------------------------
    pilha *pilha_new();
      // Returns a new pilha struct.
    void pilha_delete(pilha* p);
      // Deletes an existent pilha struct.
    void pilha_file(pilha* p, char* file);
      // Reads file as bytecode to pilha.
    void pilha_run(pilha* p);
      // Executes current bytecode from pilha.
    void pilha_push(pilha* p, i32 value);
      // Push value to pilha stack.
    i32 pilha_pop(pilha* p);
      // Pop value from pilha stack.
    i32 *pilha_variable(pilha* p, char* key);
      // Get pointer to pilha variable.
