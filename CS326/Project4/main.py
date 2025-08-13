"""
    Name:Alec Zheng,NSHE_ID_2001982564,1002,ASSIGNMENT_4
    Description: Virtual Machine for Jython
    Input: Jythob code
    Output: stack values and operations
"""
import sys
# ===-------------------------------------------------------------------------
# default values used by the virtual machine.
DEFAULT_STACK_SIZE = 1000
DEFAULT_CALL_STACK_SIZE = 1000

# ===-------------------------------------------------------------------------
# bytecode instructions.
IADD = 1       # int addition
ISUB = 2       # int subtraction
IMUL = 3       # int multiplication
ILT = 4        # int less than
IEQ = 5        # int equal
BR = 6         # branch
BRT = 7        # branch if true
BRF = 8        # branch if false
ICONST = 9     # push constant int
LOAD = 10      # load from local context
GLOAD = 11     # load from global memory
STORE = 12     # store in local context
GSTORE = 13    # store in global memory
PRINT = 14     # prnt stack top
POP = 15       # throw away top of stack
CALL = 16      # function call
RET = 17       # return with/without value
HALT = 18      # stop execution


# ===-------------------------------------------------------------------------
# an instruction that consists of a name and a number of arguments.
class Instruction:
    def __init__(self, name, nargs=0):
        self.name = name
        self.nargs = nargs

    def __str__(self):
        return "[" + self.name + ", " + str(self.nargs) + "]"


# ===-------------------------------------------------------------------------
# the list of available instructions.
instructions = [
    Instruction("noop"),
    Instruction("iadd"),
    Instruction("isub"),
    Instruction("imul"),
    Instruction("ilt"),
    Instruction("ieq"),
    Instruction("br", 1),
    Instruction("brt", 1),
    Instruction("brf", 1),
    Instruction("iconst", 1),
    Instruction("load", 1),
    Instruction("gload", 1),
    Instruction("store", 1),
    Instruction("gstore", 1),
    Instruction("print"),
    Instruction("pop"),
    Instruction("call", 1),
    Instruction("ret"),
    Instruction("halt")
]


# ===-------------------------------------------------------------------------
# the information pushed onto the stack frame.
class ActivationRecord:
    def __init__(self, invokecontex, function_context, returnip):
        self.invokecontext = invokecontex  # caller (the activation that made the call)
        self.function_context = function_context  # information about the function being executing
        self.returnip = returnip  # return address of the caller
        self.locals = [0] * (function_context.nargs + function_context.nlocals)  # args + locals


# ===-------------------------------------------------------------------------
# information regarding a function, such as its name, number of arguments,
# number of local variables, and its location in memory.
class FunctionContext:
    def __init__(self, name, nargs, nlocals, address):
        self.name = name
        self.nargs = nargs
        self.nlocals = nlocals
        self.address = address


# ===-------------------------------------------------------------------------
# represents a stack-based interpreter that simulates a hardware
# processor with no general-purpose registers (i.e., data is never
# moved to registers from memory).
class VirtualMachine:
    def __init__(self, nglobals, code, constant_pool):
        self.code = code  # word-addressable code memory
        self.globals = [0] * nglobals  # global variable space
        self.stack = [0] * DEFAULT_STACK_SIZE  # operand stack, grows upwards
        self.constant_pool = constant_pool  # funtion table (an array of functions)
        self.ip = 0  # instruction pointer (register)
        self.sp = -1  # stack pointer register (register)
        self.activation = None  # the active context (current activation record)
        self.trace = False  # flag used for debugging

    def tostring_stack(self):
        s = "stack=["
        for i in range(self.sp + 1):
            s = s + ' ' + str(self.stack[i])
        s += ' ]'
        return s

    def tostring_call_stack(self):
        stack = []
        activation = self.activation
        while activation is not None:
            if activation.function_context is not None:
                stack.insert(0, activation.function_context.name)
            activation = activation.invokecontext
        return 'calls=[' + ' '.join(str(x) for x in stack) + ']'

    def tostring_disinstr(self):
        opcode = self.code[self.ip]
        opname = instructions[opcode].name
        s = [f'{self.ip:04d}\t{opname:11}']
        nargs = instructions[opcode].nargs
        if opcode == CALL:
            s.append(self.constant_pool[self.code[self.ip + 1]].name)
        elif nargs > 0:
            operands = []
            i = self.ip + 1
            while i <= self.ip + nargs:
                operands.append(str(self.code[i]))
                i += 1
            for x in range(len(operands)):
                s.append(', ') if x > 0 else None
                s.append(operands[x])
        return ' '.join(x for x in s)

    def dump_memory(self):
        print('Data memory')
        addr = 0
        for x in self.globals:
            print('{:4d}: {:d}\n'.format(addr, x))
            addr += 1
        print()

    def exec(self, startip):
        self.ip = startip
        self.activation = ActivationRecord(None, self.constant_pool[0], 0)
        self.cpu()

    def cpu(self):
        opcode = self.code[self.ip]
        while opcode != HALT and self.ip < len(self.code):
            if self.trace:
                print('{:35}'.format(self.tostring_disinstr()))
            self.ip += 1  # jump to the next instruction or to operand
            if opcode == IADD:
                op2 = self.stack[self.sp]  # 2nd operand at top of stack
                self.sp -= 1
                op1 = self.stack[self.sp]  # 1st operand below top
                self.sp -= 1
                self.stack[self.sp + 1] = op1 + op2
                self.sp += 1
            # TODO: WRITE YOUR CODE HERE!!!

            # All student writen code is below 74 characters
            # Provided code not changed per instructions
            elif opcode == ISUB:
                op2 = self.stack[self.sp]  # 2nd operand at top of stack
                self.sp -= 1
                op1 = self.stack[self.sp]  # 1st operand below top
                self.sp -= 1
                self.stack[self.sp + 1] = op1 - op2
                self.sp += 1
            elif opcode == IMUL:
                op2 = self.stack[self.sp]  # 2nd operand at top of stack
                self.sp -= 1
                op1 = self.stack[self.sp]  # 1st operand below top
                self.sp -= 1
                self.stack[self.sp + 1] = op1 * op2
                self.sp += 1
            elif opcode == ILT:
                op2 = self.stack[self.sp]  # 2nd operand at top of stack
                self.sp -= 1
                op1 = self.stack[self.sp]  # 1st operand below top
                self.sp -= 1
                if(op1 < op2):
                    self.stack[self.sp + 1] = True
                else:
                    self.stack[self.sp + 1] = False
                self.sp += 1
            elif opcode == IEQ:
                op2 = self.stack[self.sp]  # 2nd operand at top of stack
                self.sp -= 1
                op1 = self.stack[self.sp]  # 1st operand below top
                self.sp -= 1
                if(op1 == op2):
                    self.stack[self.sp + 1] = True
                else:
                    self.stack[self.sp + 1] = False
                self.sp += 1
            elif opcode == BRT:             
                op = self.stack[self.sp]  # operand at top of stack
                self.sp -= 1
                if(op == True):            # check bool on top of stack
                    self.ip = self.code[self.ip]
                else:
                    self.ip += 1
            elif opcode == BRF:             
                op = self.stack[self.sp]  # operand at top of stack
                self.sp -= 1
                if(op == False):           # check bool on top of stack
                    self.ip = self.code[self.ip]
                else:
                    self.ip += 1
            elif opcode == ICONST:
                op = self.code[self.ip]
                self.stack[self.sp + 1] = op    #operand to the stack
                self.sp += 1 
                self.ip += 1
            elif opcode == LOAD:            
                op = self.code[self.ip]
                #pull value from local to stack
                self.stack[self.sp + 1] = self.activation.locals[op]
                self.sp += 1
                self.ip += 1
            elif opcode == STORE:           
                op = self.code[self.ip]
                # pull value from stack to local
                self.activation.locals[op] = self.stack[self.sp]
                self.sp -= 1
                self.ip += 1
            elif opcode == GLOAD:
                # same as load but global
                op = self.code[self.ip]
                self.stack[self.sp + 1] = self.globals[op]
                self.sp += 1
                self.ip += 1
            elif opcode == GSTORE:
                # same as store but global
                op = self.code[self.ip]
                self.globals[op] = self.stack[self.sp]
                self.sp -= 1
                self.ip += 1

            elif opcode == CALL:        
                funcobj = self.code[self.ip]
                self.ip += 1
                arguments = self.constant_pool[funcobj].nargs
                # new activation record
                self.activation = ActivationRecord(self.activation, 
                self.constant_pool[funcobj], self.ip)
                self.sp = (self.sp - arguments) + 1
                for x in range(arguments): # move arguments to locals
                    self.activation.locals[x] = self.stack[self.sp]
                    self.sp += 1
                # make sure stack pointer removes arguments
                self.sp -= arguments + 1   
                self.ip = self.constant_pool[funcobj].address
                
            # end of code
            elif opcode == BR:
                self.ip = self.code[self.ip]
            elif opcode == PRINT:
                print(self.stack[self.sp])
                self.sp -= 1
            elif opcode == POP:
                self.sp -= 1
            elif opcode == RET:
                self.ip = self.activation.returnip
                self.activation = self.activation.invokecontext
            else:
                print('invalid opcode: {0} at ip= {1}'.format(opcode, self.ip - 1))
                exit(1)
            if self.trace:
                print('{:22} {}\n'.format(self.tostring_stack(), self.tostring_call_stack()))
            opcode = self.code[self.ip]
        if self.trace:
            print('{:35}'.format(self.tostring_disinstr()))
        if self.trace:
            print(self.tostring_stack())
        if self.trace:
            print(self.dump_memory())


# ===-------------------------------------------------------------------------
# entry point of your program.
if __name__ == '__main__':
    args = sys.argv
    # change this to test each program individually
    # ADD=1, SUB=2, MUL=3, LOOP=4, FOO=6, FACTORIAL=6
    PROGRAM_NUM = int(args[1])

    # program #1 ==---------------------------------------------
    add_program = [
        # .def main: ARGS=0, LOCALS=0              ADDRESS
        ICONST, 1,                                   # 0
        ICONST, 2,                                   # 2
        IADD,                                        # 4
        # print 1+3
        PRINT,                                       # 5
        HALT                                         # 6
    ]

    # program #2 ==---------------------------------------------
    sub_program = [
        # .def main: ARGS=0, LOCALS=0              ADDRESS
        ICONST, 4,                                   # 0
        ICONST, 2,                                   # 2
        ISUB,                                        # 4
        # print 4+2
        PRINT,                                       # 5
        HALT                                         # 6
    ]

    # program #3 ==---------------------------------------------
    mul_program = [
        # GLOBALS=2, OP1, OP2
        # .def main: ARGS=0, LOCALS=0
        # OP1=5                                    ADDRESS
        ICONST, 5,                                   # 0
        GSTORE, 0,                                   # 2
        # OP2=25
        ICONST, 25,                                  # 4
        GSTORE, 1,                                   # 6
        # OP1=OP1*OP2
        GLOAD, 1,                                    # 8
        GLOAD, 0,                                    # 10
        IMUL,                                        # 12
        GSTORE, 0,                                   # 13
        # print OP1
        GLOAD, 0,                                    # 15
        PRINT,                                       # 17
        HALT                                         # 18
    ]

    # program #4 ==---------------------------------------------
    loop_program = [
        # GLOBALS=2; N, I
        # N=10                                     ADDRESS
        ICONST, 10,                                  # 0
        GSTORE, 0,                                   # 2
        # I=0
        ICONST, 0,                                   # 4
        GSTORE, 1,                                   # 6
        # while I<N:
        # GOTO (8)
        GLOAD, 1,                                    # 8
        GLOAD, 0,                                    # 10
        ILT,                                         # 12
        BRF, 24,                                     # 13
        # I=I+1
        GLOAD, 1,                                    # 15
        ICONST, 1,                                   # 17
        IADD,                                        # 19
        GSTORE, 1,                                   # 20
        BR, 8,                                       # 22
        # DONE (26)
        # print
        GLOAD, 1,                                    # 24
        PRINT,                                       # 26
        HALT                                         # 27
    ]

    # note that programs 1, 2, 3, and 4 use the same active context;
    # again, the active content contains information about a function's
    # activation record
    loop_metadata = [
        # .def main: ARGS=0, LOCALS=0, ADDRESS=0
        FunctionContext('main', 0, 0, 0)
    ]

    # program #5 ==---------------------------------------------
    foo_program = [
        # .def main: ARGS=0, LOCALS=0
        # call foo                                   ADDRESS
        ICONST, 4,                                     # 0
        CALL, 1,  # 1 represents function index        # 2
        HALT,                                          # 4
        # .def foo: ARGS=1, LOCALS=0
        LOAD, 0,                                       # 5
        PRINT,                                         # 7
        RET                                            # 8
    ]

    foo_metadata = [
        # .def main: ARGS=0, LOCALS=0, ADDRESS=0
        FunctionContext('main', 0, 0, 0),
        # .def foo: ARGS=1, LOCALS=0, ADDRESS=1
        FunctionContext('foo', 1, 0, 5)
    ]

    # program #6 ==---------------------------------------------
    factorial_program = [
        # .def factorial: ARGS=1, LOCALS=0
        # if N < 2 return 1                          ADDRESS
        LOAD, 0,                                       # 0
        ICONST, 2,                                     # 2
        ILT,                                           # 4
        BRF, 10,                                       # 5
        ICONST, 1,                                     # 7
        RET,                                           # 9
        # return N * factorial(N-1)
        LOAD, 0,                                       # 10
        LOAD, 0,                                       # 12
        ICONST, 1,                                     # 14
        ISUB,                                          # 16
        CALL, 1,  # 1 represents function index        # 17
        IMUL,                                          # 19
        RET,                                           # 20
        # .def main: ARGS=0, LOCALS=0
        # print factorial(1)
        ICONST, 5,                                     # 21
        CALL, 1,  # 1 represents function index        # 23
        PRINT,                                         # 25
        HALT                                           # 26
    ]

    factorial_metadata = [
        # .def main: ARGS=0, LOCALS=0, ADDRESS=21
        FunctionContext('main', 0, 0, 21),
        # .def factorial: ARGS=1, LOCALS=0, ADDRESS=0
        FunctionContext('factorial', 1, 0, 0)
    ]

    # testing programs, individually
    if PROGRAM_NUM == 1:
        vm = VirtualMachine(0, add_program, loop_metadata)
        vm.trace = True
        vm.exec(loop_metadata[0].address)
    elif PROGRAM_NUM == 2:
        vm = VirtualMachine(2, sub_program, loop_metadata)
        vm.trace = True
        vm.exec(loop_metadata[0].address)
    elif PROGRAM_NUM == 3:
        vm = VirtualMachine(2, mul_program, loop_metadata)
        vm.trace = True
        vm.exec(loop_metadata[0].address)
    elif PROGRAM_NUM == 4:
        vm = VirtualMachine(2, loop_program, loop_metadata)
        vm.trace = True
        vm.exec(loop_metadata[0].address)
    elif PROGRAM_NUM == 5:
        vm = VirtualMachine(0, foo_program, foo_metadata)
        vm.trace = True
        vm.exec(foo_metadata[0].address)
    elif PROGRAM_NUM == 6:
        vm = VirtualMachine(0, factorial_program, factorial_metadata)
        vm.trace = True
        vm.exec(factorial_metadata[0].address)
