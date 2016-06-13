#include <stddef.h>

#include "./func.hpp"

namespace {

size_t dummy = 0;

}

void func() {
    ++dummy;
}

void derived::virtual_func() {
    ++dummy;
}
