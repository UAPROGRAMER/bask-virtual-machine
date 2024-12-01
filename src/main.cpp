#include "lib/main.hpp"

std::vector<uint8_t> readFileToByteVector(char* filePath) {
    std::vector<uint8_t> byteVector;
    
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        return byteVector;
    }
    
    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    byteVector.resize(fileSize);
    
    if (!file.read(reinterpret_cast<char*>(byteVector.data()), fileSize)) {
        std::cerr << "Error: Could not read file " << filePath << std::endl;
        byteVector.clear();
    }

    file.close();
    return byteVector;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Not enought arguments.\n";
        return 1;
    }

    vector<uint8_t> bytecode = readFileToByteVector(argv[1]);

    VirtualMachine vm (bytecode);

    int value;

    try
    {
        value = vm.run();
    }
    catch (...)
    {
        return 1;
    }

    return value;
}