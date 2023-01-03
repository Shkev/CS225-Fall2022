/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 * stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 *
 * **Hint**: think recursively!
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the Standard Template Library (STL) stack in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param s A stack holding values to sum.
 * @return  The sum of all the elements in the stack, leaving the original
 *          stack in the same state (unchanged).
 */
template <typename T>
T sum(stack<T>& s)
{
    if (s.empty()) return 0;
    T top = s.top();
    s.pop();
    T total = top + sum(s);
    s.push(top);
    return total;
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of square bracket characters, [, ], and other
 * characters. This function will return true if and only if the square bracket
 * characters in the given string are balanced. For this to be true, all
 * brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is
 * balanced, "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is
 * balanced.
 *
 * For this function, you may only create a single local variable of type
 * `stack<char>`! No other stack or queue local objects may be declared. Note
 * that you may still declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return      Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{
    stack<char> open_brackets;
    while (!input.empty()) {
        char c = input.front();
        if (c == '[') {
            open_brackets.push(c);
        } else if (c == ']') {
            if (open_brackets.empty()) return false;
            open_brackets.pop();
        }
        input.pop();
    }
    if (open_brackets.empty()) return true;
    return false;
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 *
 * **Hint**: You'll want to make a local stack variable.
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the Standard Template Library (STL) queue in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param q A queue of items to be scrambled
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    queue<T> q2;
    // first element stays
    AppendQueueElem(q2, q, 1);
    std::cout << q2.back();
    queue<T> q_rev = ReverseQueueElements(q, 2);
    AppendQueueElem(q2, q_rev, 2);
    std::cout << q2.back();
    AppendQueueElem(q2, q, 3);
    std::cout << q2.back();
    q_rev = ReverseQueueElements(q, 4);
    AppendQueueElem(q2, q_rev, 4);
    std::cout << q2.back();
    AppendQueueElem(q2, q, 5);
    std::cout << q2.back();
    q_rev = ReverseQueueElements(q, 2);
    AppendQueueElem(q2, q_rev, 2);
    std::cout << q2.back();

    assert(q.empty());
    assert(!q2.empty());

    queue<T> q3 = q2;
    while (!q3.empty()) {
        std::cout << q3.front() << ' ';
        q3.pop();
    }
    std::cout << '\n';

    q = q2;
}

template <typename T>
queue<T> ReverseQueueElements(queue<T>& q, unsigned num_elem) {
    stack<T> s;
    queue<T> q2;
    if (q.empty()) return q2;
    for (unsigned i = 0; !q.empty() && i < num_elem; ++i) {
        s.push(q.front());
        q.pop();
    }
    while (!s.empty()) {
        q2.push(s.top());
        s.pop();
    }
    return q2;
}

template <typename T>
void AppendQueueElem(queue<T>& q_loc, queue<T>& q_cp, int num_elem) {
    while (!q_cp.empty() && num_elem > 0) {
        q_loc.push(q_cp.front());
        q_cp.pop();
        num_elem--;
    }
}

}
