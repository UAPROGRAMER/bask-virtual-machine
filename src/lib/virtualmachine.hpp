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
    stack<int64_t> opstack;
    uint64_t index;
    uint8_t byte;

    public:

    VirtualMachine(vector<uint8_t>& _bytecode):
        bytecode(_bytecode),
        index((uint64_t)-1),
        byte(0)
    {
        read();
    }

    void read()
    {
        byte = bytecode.at(++index);
    }

    int run()
    {
        while (true)
        {
            if (byte == OC_EXIT)
            {
                return exit();
            }

            instruction();
            read();
        }
    }

    void instruction()
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
        for (uint8_t i = 0; i < 64; i+=8)
        {
            read();
            value |= ((int64_t)byte<<i);
        }
        opstack.push(value);
    }

    void pop()
    {
        opstack.pop();
    }

    void add()
    {
        int64_t value = opstack.top(); opstack.pop();
        value += opstack.top(); opstack.pop();
        opstack.push(value);
    }

    void sub()
    {
        int64_t value = opstack.top(); opstack.pop();
        value = opstack.top() - value; opstack.pop();
        opstack.push(value);
    }

    void print()
    {
        std::cout << opstack.top();
    }

    int exit()
    {
        return opstack.top();
    }
};

#endif