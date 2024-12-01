#ifndef __VIRTUALMACHINE_HPP__
#define __VIRTUALMACHINE_HPP__

#include "includes.hpp"

typedef enum : uint8_t
{
    OC_PUSH,
    OC_POP,
    OC_ADD,
    OC_SUB,
    OC_EXIT,
    OC_PRINT
} OperationCode;

class VirtualMachine
{
    private:

    vector<uint8_t> bytecode;
    std::stack<int64_t> stack;
    uint64_t operationpoiter;
    uint8_t byte;

    public:

    VirtualMachine(vector<uint8_t>& _bytecode):
        bytecode(_bytecode),
        operationpoiter((uint64_t)-1),
        byte(0)
    {
        read();
    }

    void read()
    {
        byte = bytecode.at(++operationpoiter);
    }

    int run()
    {
        while (true)
        {
            if (byte == OC_EXIT)
            {
                return exit();
            }

            operation();
            read();
        }
    }

    void operation()
    {
        switch (byte)
        {
            case OC_PUSH:
                push();
                break;
            case OC_POP:
                pop();
                break;
            case OC_ADD:
                add();
                break;
            case OC_SUB:
                sub();
                break;
            case OC_PRINT:
                print();
                break;
        }
    }

    void push()
    {
        int64_t value = 0;
        read();
        value |= (((int64_t)byte));
        read();
        value |= (((int64_t)byte)<<8);
        read();
        value |= (((int64_t)byte)<<16);
        read();
        value |= (((int64_t)byte)<<24);
        read();
        value |= (((int64_t)byte)<<32);
        read(); 
        value |= (((int64_t)byte)<<40);
        read();
        value |= (((int64_t)byte)<<48);
        read();
        value |= (((int64_t)byte)<<56);
        stack.push(value);
    }

    void pop()
    {
        stack.pop();
    }

    void add()
    {
        int64_t value = stack.top(); stack.pop();
        value += stack.top(); stack.pop();
        stack.push(value);
    }

    void sub()
    {
        int64_t value = stack.top(); stack.pop();
        value = stack.top() - value; stack.pop();
        stack.push(value);
    }

    void print()
    {
        std::cout << stack.top();
    }

    int exit()
    {
        return stack.top();
    }
};

#endif