#ifndef _FUNC_HPP_
#define _FUNC_HPP_

void func();

struct base {
    virtual void virtual_func() = 0;
};

struct derived : public base {
    void virtual_func() override;
};

#endif // _FUNC_HPP_
