#include "Value.h"

#include <chrono>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>

int main()
{
    std::ostringstream os;
    os << "[";
    std::string comma = "";
    for(std::size_t i = 0; i < 2'000; i++)
    {
        os << comma << "{"
           << "\"key " << i << "\":" << i << "}";
        comma = ",";
    }
    os << "]";
    std::string input = os.str();
    const double mb = input.size() / 1024. / 1024.;
    std::cout << "size = " << mb << " MB" << std::endl;
    using vehlwn::json::parse;
    const auto t1 = std::chrono::steady_clock::now();
    const auto value = parse(input);
    const auto t2 = std::chrono::steady_clock::now();
    std::cout << "isArray = " << value.isArray() << std::endl;
    const double secs = std::chrono::duration<double>(t2 - t1).count();
    std::cout << secs << " s" << std::endl;
    std::cout << mb / secs << " MB/s" << std::endl;
}
