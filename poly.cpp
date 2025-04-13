#include "poly.h"
#include <algorithm>
#include <iostream>

// Default Constructor
polynomial::polynomial()
{
    // push back because we want decreasing order of powers (EX: 4, 3, 2, 1, 0), so 0 would be at bottom
    terms.push_back({0, 0}); // super easy, zero polynomial has canonical form as [(0,0)]
}

// Constructor
template <typename Iter>
polynomial::polynomial(Iter start, Iter end)
{
    terms.assign(start, end);

    // sort all terms
    sort();

    // combine like terms
    combine();

    // clean '0' terms
    clean();
}

// Copy Constructor
polynomial::polynomial(const polynomial &other)
{
    terms = other.terms; // simple copy
}

polynomial& polynomial::operator=(const polynomial &other)
{
    if (this != &other)
    {
        terms = other.terms;
    }

    return(*this);
}

// other operators ~~~~~~~~~~~~~~~~~~~~

void polynomial::sort()
{
    // algorithm library (https://www.digitalocean.com/community/tutorials/sorting-a-vector-in-c-plus-plus)
    // lambda function used
    std::sort(terms.begin(), terms.end(), [](auto &a, auto &b){ return a.first > b.first; });

    return;
}

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

void polynomial::clean()
{
    std::vector<std::pair<power, coeff>> other;

    for (size_t i = 0; i < terms.size(); i++)
    {
        if (terms[i].second != 0) // if a term is not empty (coefficient is not 0)
        {
            other.push_back(terms[i]); // we push it back in other vector
        }
    }

    // special case: if empty, push in zero polynomial
    if (other.empty() == true)
    {
        other.push_back({0, 0});
    }

    terms = move(other); // transfer information

    return;
}

void polynomial::print() const
{
    if (terms.empty()) {
        std::cout << "0\n";
        return;
    }

    bool first_term = true;

    for (const auto& term : terms)
    {
        coeff c = term.second;
        power p = term.first;

        if (c == 0) continue; // shouldn't happen if clean() worked, but extra safe

        // Handle sign
        if (!first_term)
        {
            if (c > 0)
                std::cout << " + ";
            else
                std::cout << " - ";
        }
        else
        {
            if (c < 0)
                std::cout << "-";
        }

        // Handle absolute value of coefficient
        if (std::abs(c) != 1 || p == 0)  // Don't print 1 or -1 for non-constant terms
            std::cout << std::abs(c);

        // Handle variable and exponent
        if (p > 0)
        {
            std::cout << "x";
            if (p > 1)
                std::cout << "^" << p;
        }

        first_term = false;
    }

    std::cout << std::endl;

    return;
}