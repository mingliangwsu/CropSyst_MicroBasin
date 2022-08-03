#ifndef COUT_MP_H
#define COUT_MP_H
#include "stdlib.h"
#include "stdio.h"
#include <iostream>

#ifdef _MSC_VER

#include <sstream>

class Cout_MP
{
private:
    // Buffer
    std::ostringstream oss;
    // private constructor
    Cout_MP(): oss(std::ostringstream::out) {
    }
public:
    // to get a printer
    static Cout_MP Print() {
        return Cout_MP();
    }

    // for all types (except Action)
    template <class T>
    Cout_MP& operator<<(const T& input) {
        oss << input;
        return *this;
    }

    // actions
    enum Action{
        ENDL,
        PRINT,
    };
    // for action type
    Cout_MP& operator<<(const Action& input) {
        switch(input) {
            // endl => append n
            case ENDL:{
                oss << "\n";
            }
            // endl or print => print
            case PRINT:{
                std::cout << oss.str();
                std::cout.flush();
                oss.clear();
            }break;
        }
        return *this;
    }
};

#endif

#endif // COUT_MP_H
