#include <chrono>
#include <iostream>
#include <memory>

#define BOOST_SIGNALS_NO_DEPRECATION_WARNING
#include <boost/signals.hpp>
#include <boost/signals2.hpp>

#include "./func.hpp"

void print_duration(std::ostream &out, const std::string& str, const std::chrono::high_resolution_clock::duration &d)
{
    out << str << ": ";

    if (d < std::chrono::microseconds(10))
        out << std::chrono::duration_cast<std::chrono::duration<float, std::nano>>(d).count() << " ns";
    else if (d < std::chrono::milliseconds(10))
        out << std::chrono::duration_cast<std::chrono::duration<float, std::micro>>(d).count() << " µs";
    else if (d < std::chrono::seconds(10))
        out << std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(d).count() << " ms";
    else if (d < std::chrono::minutes(10))
        out << std::chrono::duration_cast<std::chrono::duration<float>>(d).count() << " s";

    out << std::endl;
}

void direct_call()
{
    const size_t count = 1000000000;
    size_t i = 0;

    auto begin = std::chrono::high_resolution_clock::now();

    for (; i < count; ++i)
        func();

    std::chrono::high_resolution_clock::duration total = std::chrono::high_resolution_clock::now() - begin;
    print_duration(std::cout, "Direct call", total / i);
}

void function_ptr_call()
{
    const size_t count = 1000000000;
    size_t i = 0;
    void(*func_ptr)() = &func;

    auto begin = std::chrono::high_resolution_clock::now();

    for (; i < count; ++i)
        func_ptr();

    std::chrono::high_resolution_clock::duration total = std::chrono::high_resolution_clock::now() - begin;
    print_duration(std::cout, "Function pointer call", total / i);
}

void measure_virtual_call()
{
    const size_t count = 1000000000;
    size_t i = 0;

    derived obj;
    base *p = &obj;

    auto begin = std::chrono::high_resolution_clock::now();

    for (; i < count; ++i)
        p->virtual_func();

    std::chrono::high_resolution_clock::duration total = std::chrono::high_resolution_clock::now() - begin;
    print_duration(std::cout, "Virtual function call", total / i);
}

void measure_function_object_call()
{
    const size_t count = 1000000000;
    size_t i = 0;
    std::function<void()> function(&func);

    auto begin = std::chrono::high_resolution_clock::now();

    for (; i < count; ++i)
        function();

    std::chrono::high_resolution_clock::duration total = std::chrono::high_resolution_clock::now() - begin;
    print_duration(std::cout, "Function object call", total / i);
}

void measure_function_vector_call()
{
    const size_t count = 100000000;
    size_t i = 0;
    std::vector<std::function<void()>> functions;

    functions.push_back(&func);

    auto begin = std::chrono::high_resolution_clock::now();

    for (; i < count; ++i) {
        for (auto &func: functions)
            func();
    }

    std::chrono::high_resolution_clock::duration total = std::chrono::high_resolution_clock::now() - begin;
    print_duration(std::cout, "Function vector call", total / i);
}

void measure_boost_signals_call()
{
    const size_t count = 100000000;
    size_t i = 0;

    boost::signal<void()> signal;
    signal.connect(&func);

    auto begin = std::chrono::high_resolution_clock::now();
    for (; i < count; ++i)
        signal();

    std::chrono::high_resolution_clock::duration total = std::chrono::high_resolution_clock::now() - begin;
    print_duration(std::cout, "boost::signals call", total / i);
}

void measure_boost_signals2_no_mutex_call()
{
    const size_t count = 100000000;
    size_t i = 0;

    using boost::signals2::keywords::mutex_type;
    using boost::signals2::signal_type;
    using boost::signals2::dummy_mutex;

    signal_type<void(), mutex_type<dummy_mutex>>::type signal;
    signal.connect(&func);

    auto begin = std::chrono::high_resolution_clock::now();

    for (; i < count; ++i)
        signal();

    std::chrono::high_resolution_clock::duration total = std::chrono::high_resolution_clock::now() - begin;
    print_duration(std::cout, "boost::signals2 (dummy mutex) call", total / i);
}

void measure_boost_signals2_call()
{
    const size_t count = 100000000;
    size_t i = 0;

    boost::signals2::signal<void()> signal;
    signal.connect(&func);

    auto begin = std::chrono::high_resolution_clock::now();
    for (; i < count; ++i)
        signal();

    std::chrono::high_resolution_clock::duration total = std::chrono::high_resolution_clock::now() - begin;
    print_duration(std::cout, "boost::signals2 call", total / i);
}

int main()
{
    direct_call();
    function_ptr_call();
    measure_virtual_call();
    measure_function_object_call();
    measure_function_vector_call();
    measure_boost_signals_call();
    measure_boost_signals2_no_mutex_call();
    measure_boost_signals2_call();

    return 0;
}
