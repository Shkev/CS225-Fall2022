/**
 * @file fib.cpp
 * Contains Fibonacci-number generating functions both utilizing and not
 * utilizing memoization.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "fib.h"

#include <unordered_map>
#include <vector>
#include <cstddef>
#include <iostream>

using namespace std;

using std::unordered_map;

/**
 * Calculates the nth Fibonacci number where the zeroth is defined to be
 * 0.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long fib(unsigned long n)
{
    /* Your code goes here! */
    if (n <= 1) {
        return n;
    }
    return fib(n-1) + fib(n-2);
}

/**
 * Calculates the nth Fibonacci number where the zeroth is defined to be
 * 0. This version utilizes memoization.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long memoized_fib(unsigned long n)
{
    cout << n << endl;
    /* Your code goes here! */
    static unordered_map<unsigned long, unsigned long> memo;
    memo[0] = 0;
    memo[1] = 1;
    auto lookup = memo.find(n);
    if (lookup != memo.end()) {
        return lookup->second;
    }
    unsigned long res = memoized_fib(n-1) + memoized_fib(n-2);
    memo[n] = res;
    return res;
}
