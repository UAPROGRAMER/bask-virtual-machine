%include "lib.asm"

db OC_PUSH
dq 10

db OC_PUSH
dq 5

db OC_SUB

db OC_PUSH
dq 2

db OC_ADD

db OC_PRINT

db OC_POP

db OC_PUSH
dq 0

db OC_EXIT