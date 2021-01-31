#include "lib.h"

using namespace std;


int main()
{
    print_ip(static_cast<char>(-1));
    print_ip(static_cast<short>(0));
    print_ip(static_cast<int>(2130706433));
    print_ip(static_cast<long long>(8875824491850138409));
    print_ip("3.7.8.1"s);
    print_ip(std::vector<int>{ 96, 127, 56, 5 });
    print_ip(std::list<int>{ 3, 1, 2, 7 });
    print_ip(std::tuple{ 5, 7, 3, 1});

    return 0;
}
