#include <iostream>

#include <boost/version.hpp>
#include <boost/config.hpp>


int main(int argc, char **argv)
{

    std::cout << "Boost 版本:" << BOOST_VERSION << std::endl;
    std::cout << "Boost lib 版本:" << BOOST_LIB_VERSION << std::endl;
    std::cout << "操作系统:" << BOOST_PLATFORM << std::endl;
    std::cout << "编译器:" << BOOST_COMPILER << std::endl;
    std::cout << "标准库:" << BOOST_STDLIB << std::endl;
    system("pause");
    return 0;
}
 