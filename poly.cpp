#include "poly.h"
// #include <iostream>

// Default Constructor
polynomial::polynomial()
{
    // push back because we want decreasing order of powers (EX: 4, 3, 2, 1, 0), so 0 would be at bottom
    terms.push_back({0, 0}); // super easy, zero polynomial has canonical form as [(0,0)]
}

// Copy Constructor
polynomial::polynomial(const polynomial &other)
{
    terms = other.terms; // simple copy
}

// = operator
polynomial& polynomial::operator=(const polynomial &other)
{
    if (this != &other)
    {
        terms = other.terms;
    }

    return(*this);
}

// + operator (polynomial + polynomial)
polynomial operator+(const polynomial &one, const polynomial &two)
{
    polynomial final;

    // toss in all the terms for polynomial one
    for (size_t i = 0; i < one.terms.size(); i++)
    {
        final.terms.push_back(one.terms[i]);
    }

    // toss in all the terms for polynomial two
    for (size_t i = 0; i < two.terms.size(); i++)
    {
        final.terms.push_back(two.terms[i]);
    }

    // mix
    final.sort();
    final.combine();
    final.clean();

    return(final);
}

// + operator (polynomial + int)
polynomial operator+(const polynomial &poly, int val)
{
    polynomial final;
    
    final = poly; // = operator used

    // We assume that everything is sorted
    if (final.terms.back().first == 0) // Add val to constant
    {
        final.terms.back().second += val;
    }
    else // Toss val in at the end
    {
        final.terms.push_back({0, val});
    }

    final.sort();
    final.combine();
    final.clean();

    return(final);
}

// + operator (int + polynomial)
polynomial operator+(int val, const polynomial &poly)
{
    // very simple, we flip it and use the previous (polynomial + int) function
    polynomial final;

    final = poly + val;

    return(final);
}

// * operator (polynomial * polynomial)
polynomial operator*(const polynomial &one, const polynomial &two)
{
    polynomial final;

    // multiply each term in the first polynomial by each term in the second
    for (size_t i = 0; i < one.terms.size(); i++)
    {
        for (size_t j = 0; j < two.terms.size(); j++)
        {
            // when using this pair, first will be power and second will be coeff (as stated in poly.h)
            power power = one.terms[i].first + two.terms[j].first; // add powers together
            coeff coeff = one.terms[i].second * two.terms[j].second; // multiply coefficients
            final.terms.push_back({power, coeff});
        }
    }
    
    final.sort();
    final.combine();
    final.clean();

    return(final);
}

// * operator (polynomial * int)
polynomial operator*(const polynomial &poly, int val)
{
    polynomial final;

    // multiply each terms coeff by the val
    for (size_t i = 0; i < poly.terms.size(); i++)
    {
        // only change the coeffecient
        final.terms.push_back({poly.terms[i].first, poly.terms[i].second * val});
    }

    final.sort();
    final.combine();
    final.clean();

    return(final);
}

// * operator (int * polynomial)
polynomial operator*(int val, const polynomial &poly)
{
    // very simple, we flip it and use the previous (polynomial * int) function
    polynomial final;

    final = poly * val;

    return(final);
}

// % operator (polynomial % polynomial)
polynomial operator%(const polynomial &p, const polynomial &d) // This one needs to be done differently
{
    polynomial r;

    r = p; // = operator

    r.sort();
    r.combine();
    r.clean();

    while ((r.terms[0].second != 0) && (r.terms[0].first >= d.terms[0].first)) // wikipedia (pseudocode)
    {
        power diff_power = r.terms[0].first - d.terms[0].first; // subtract powers
        coeff diff_coeff = r.terms[0].second / d.terms[0].second; // divide coeffs

        // temp polynomial to combine diff_power and diff_coeff into polynomial
        polynomial temp;
        temp.terms.push_back({diff_power, diff_coeff});

        // update remainder and sort it for next (or last) iteration of loop
        r = r + ((-1) * (temp) * d); // wikipedia (pseudocode)
        r.sort();
        r.combine();
        r.clean();
    }

    return(r);
}

// Polynomial degree
size_t polynomial::find_degree_of()
{
    // Assuming everything is sorted
    return(terms[0].first);
}

// Polynomial in canonical form
std::vector<std::pair<power, coeff>> polynomial::canonical_form() const
{
    // Assuming everything is sorted
    return(terms);
}

// Helper function: sort
void polynomial::sort()
{
    if (terms.empty() == true)
    {
        return;
    }

    // DIY sorting (bubble sort)
    for (size_t i = 0; i < terms.size(); i++)
    {
        for (size_t j = 0; j < terms.size() - i - 1; j++)
        {
            if (terms[j].first < terms[j + 1].first) // decreasing order: <
            {
                auto temp = terms[j];
                terms[j] = terms[j + 1];
                terms[j + 1] = temp;
            }
        }
    }

    return;
}

// Helper function: combine
void polynomial::combine()
{
    if (terms.empty() == true)
    {
        return;
    }

    std::vector<std::pair<power, coeff>> other;

    // we call this after sorting, sorting helps greatly here
    // if this wasn't sorted, we'd have to loop over terms twice
    // since terms are sorted, we can just combine as we go along
    for (size_t i = 0; i < terms.size(); i++)
    {
        if (terms[i].first == other.back().first) // if power of term matches power of other vector
        {
            other.back().second += terms[i].second; // combine coefficients
        }
        else
        {
            other.push_back(terms[i]); // push in new term into other vector
        }
    }

    terms = move(other); // transfer information

    return;
}

// Helper function: clean
void polynomial::clean()
{
    if (terms.empty() == true)
    {
        // we want there to always be a zero term in an "empty" polynomial
        terms.push_back({0, 0}); // we only do this once (in the last helper function)
        return;
    }

    std::vector<std::pair<power, coeff>> other;

    for (size_t i = 0; i < terms.size(); i++)
    {
        if (terms[i].second != 0) // if a term is not empty (coefficient is not 0)
        {
            other.push_back(terms[i]); // we push it back in other vector
        }
    }

    terms = move(other); // transfer information

    return;
}

// // Print polynomial
// void polynomial::print() const
// {
//     if (terms.empty() == true)
//     {
//         std::cout << "0" << std::endl; // empty means its 0
//         return;
//     }

//     bool first = true; // spacing after first term

//     for (size_t i = 0; i < terms.size(); i++)
//     {
//         coeff coeff = terms[i].second;
//         power power = terms[i].first;

//         // For the sake of neatness and readability
//         if (first == true)
//         {
//             if (coeff < 0)
//             {
//                 std::cout << "-";
//             }
//         }
//         else
//         {
//             if (coeff > 0)
//             {
//                 std::cout << " + ";
//             }
//             else
//             {
//                 std::cout << " - ";
//             }
//         }

//         // We dont want to print a 1 for coeff
//         if (std::abs(coeff) != 1 && power != 0)
//         {
//             std::cout << std::abs(coeff);
//         }

//         // we dont want to print x for power of 0 (constant)
//         if (power > 0)
//         {
//             std::cout << "x";
//             if (power > 1) // we also dont want to print a 1 for power
//             {
//                 std::cout << "^" << power;
//             }
//         }
//         else // power == 0 (last term so just print the coeff)
//         {
//             std::cout << std::abs(coeff);
//         }

//         first = false; // spacing after first term
//     }

//     std::cout << std::endl; // just a newline

//     return;
// }