pop degree
pop radicand

push 0
pop root

next_root:
  push root
  increment
  pop root
  
  push degree
  pop i
  
  setup_one:
    push root
  
    push i
    decrement
    pop i
  
    push i
    push 0
    more
  branch setup_one

  push degree
  decrement
  pop i
  
  setup_two:
    multiply
  
    push i
    decrement
    pop i
  
    push i
    push 0
    more
  branch setup_two
  
  pop near_radicand
  
  push near_radicand
  push radicand
  equal
  branch end
  
  push near_radicand
  push radicand
  less
branch next_root

push root
decrement
halt

end:
push root
halt
