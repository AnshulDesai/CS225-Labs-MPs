/**
 * @file fib.cpp
 * Contains Fibonacci-number generating functions both utilizing and not
 * utilizing memoization.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "fib.h"

#include <map>

using std::map;

/**
 * Calculates the nth Fibonacci number where the zeroth is defined to be
 * 0.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long fib(unsigned long n)
{
    /* Your code goes here! */
    if(n == 0 || n == 1) {
      return n;
    }
    return (fib(n - 1) + fib(n - 2));
}

/**
 * Calculates the nth Fibonacci number where the zeroth is defined to be
 * 0. This version utilizes memoization.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long memoized_fib(unsigned long n)
{
    /* Your code goes here! */
    static map<unsigned long, unsigned long> memoMap = { {0,0}, {1,1}};

    map<unsigned long, unsigned long>::iterator query = memoMap.find(n);
    if(query != memoMap.end()) {
      return query->second;
    }
    else {
      unsigned long ret = (memoized_fib(n - 1) + memoized_fib(n - 2));
      memoMap[n] = ret;
      return ret;
    }
    return 0;
}
