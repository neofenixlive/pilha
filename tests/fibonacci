pop counter

push 0
pop fib1

push 1
pop fib2

loop:
  push fib1
  push fib1
  push fib2
  add
  pop fib3
  
  push fib2
  pop fib1
  
  push fib3
  pop fib2
  
  push counter
  decrement
  pop counter
  
  push counter
  push 0
  more
branch loop
