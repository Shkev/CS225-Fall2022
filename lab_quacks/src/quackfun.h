/**
 * @file quackfun.h
 * Contains the QuackFun namespace definition.
 */

#pragma once

#include <stack>
#include <queue>
#include <cassert>
#include <iostream>

/**
 * Namespace to contain the stack and queue functions for this lab.
 */
namespace QuackFun
{
    using std::stack;
    using std::queue;

    template <typename T>
    T sum(stack<T>& s);

    bool isBalanced(queue<char> input);

    template <typename T>
    void scramble(queue<T>& q);

    template <typename T>
    queue<T> ReverseQueueElements(queue<T>& q, unsigned num_elem);

    template <typename T>
    void AppendQueueElem(queue<T>& q_loc, queue<T>& q_cp, int num_elem);

};

#include "quackfun.hpp"
