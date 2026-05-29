#include <iostream>
#include <string>
#include "AnyType.hpp"

int main(void)
{
    AnyType empty_var;
    AnyType int_var = 42;
    AnyType double_var = 3.14;

    std::cout << "empty_var: " << empty_var.GetTypeAsStirng() << "\n";
    std::cout << "int_var: " << int_var.GetTypeAsStirng() << " -> " << int_var.ToInt() << "\n";
    std::cout << "double_var: " << double_var.GetTypeAsStirng() << " -> " << double_var.ToDouble() << "\n\n";

    int_var = true;
    std::cout << "int_var after reassignment: " << int_var.GetTypeAsStirng() << " -> " << int_var.ToBool() << "\n\n";

    AnyType a = 10;
    AnyType b = 5.5;

    std::cout << "Before Swap:\n";
    std::cout << "a: " << a.GetTypeAsStirng() << " -> " << a.ToInt() << "\n";
    std::cout << "b: " << b.GetTypeAsStirng() << " -> " << b.ToDouble() << "\n";

    a.Swap(b);

    std::cout << "After Swap:\n";
    std::cout << "a: " << a.GetTypeAsStirng() << " -> " << a.ToDouble() << "\n";
    std::cout << "b: " << b.GetTypeAsStirng() << " -> " << b.ToInt() << "\n\n";

    AnyType copied = a;
    AnyType moved = std::move(copied);

    std::cout << "Moved object: " << moved.GetTypeAsStirng() << " -> " << moved.ToDouble() << "\n";

    moved.Destroy();
    std::cout << "Moved object after Destroy: " << moved.GetTypeAsStirng() << "\n\n";

    AnyType test_val = 'Z';

    try {
        std::cout << "Testing type safety (trying to get int from char)...\n";
        int wrong_value = test_val.ToInt();
        std::cout << wrong_value << "\n";
    }
    catch (const std::exception& ex) {
        std::cout << "Exception caught: " << ex.what();
    }

    return 0;
}