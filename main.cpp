#include "poly.h"
#include <iostream>
#include <vector>

int main()
{
    std::cout << "P" << std::endl;
    // Create first polynomial: 3x^4 + 2x^2 + 1
    std::vector<std::pair<power, coeff>> p1_terms = {
        {4, 3},
        {2, 2},
        {0, 1}
    };
    polynomial p1(p1_terms.begin(), p1_terms.end());

    std::cout << "P" << std::endl;
    // Create second polynomial: 5x^3 + 2x + 7
    std::vector<std::pair<power, coeff>> p2_terms = {
        {3, 5},
        {1, 2},
        {0, 7}
    };
    polynomial p2(p2_terms.begin(), p2_terms.end());

    // Print the two polynomials
    std::cout << "Polynomial 1: ";
    // p1.print(); // Uncomment if you re-enable print()

    std::cout << "Polynomial 2: ";
    // p2.print(); // Uncomment if you re-enable print()

    // Test Addition
    polynomial sum = p1 + p2;
    std::cout << "Sum (p1 + p2): ";
    // sum.print(); // Uncomment if you re-enable print()

    // Test Multiplication
    polynomial product = p1 * p2;
    std::cout << "Product (p1 * p2): ";
    // product.print(); // Uncomment if you re-enable print()

    // Test Modulo
    polynomial remainder = p1 % p2;
    std::cout << "Remainder (p1 % p2): ";
    // remainder.print(); // Uncomment if you re-enable print()

    // Test Degree
    std::cout << "Degree of p1: " << p1.find_degree_of() << std::endl;
    std::cout << "Degree of p2: " << p2.find_degree_of() << std::endl;

    // Test Canonical Form
    std::vector<std::pair<power, coeff>> canonical = p1.canonical_form();
    std::cout << "Canonical form of p1: ";
    for (auto const& term : canonical) {
        std::cout << "(" << term.first << "," << term.second << ") ";
    }
    std::cout << std::endl;

    return 0;
}