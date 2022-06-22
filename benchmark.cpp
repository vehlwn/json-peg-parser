#include "Value.h"

#include <chrono>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::string genStr(const std::size_t n)
{
    std::ostringstream os;
    os << "[";
    std::string comma = "";
    for(std::size_t i = 0; i < n; i++)
    {
        os << comma << "{"
           << "\"key " << i << "\":" << i << "}";
        comma = ",";
    }
    os << "]";
    return os.str();
}

int benchVehlwn()
{
    std::ofstream of{"times.txt"};
    for(std::size_t i = 100; i <= 30'000; i += 500)
    {
        const std::string input = genStr(i);
        std::cout << "i = " << i << "; len = " << input.size() << " bytes"
                  << std::endl;
        const auto t1 = std::chrono::steady_clock::now();
        const auto value = vehlwn::json::parse(input);
        const auto t2 = std::chrono::steady_clock::now();
        const double secs = std::chrono::duration<double>(t2 - t1).count();
        of << input.size() << '\t' << secs << std::endl;
        if(!value.isArray())
            return 1;
    }
    return 0;
}

int main()
{
    return benchVehlwn();
}
