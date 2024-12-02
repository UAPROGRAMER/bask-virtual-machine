%include "lib.asm"

db OC_PUSH
dq 15

db OC_PUSH
dq 0

db OC_SETVAR

db OC_PUSH
dq 10

db OC_PRINT

db OC_PUSH
dq 0

db OC_GETVAR

db OC_PRINT

db OC_PUSH
dq 0

db OC_EXIT