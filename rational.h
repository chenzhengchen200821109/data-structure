#ifndef _RATIONAL_H
#define _RATIONAL_H

#include <iostream>
#include <cassert>

class rational
{
    public:
        rational(long num = 0, long den = 1);
        rational(const rational& x);
        virtual void assign(long x, long y);
        rational operator*(const rational& x);
        rational operator+(const rational& x);
        rational& operator=(const rational& x);
        rational operator-(const rational& x);
        rational operator/(const rational& x);
        bool operator==(const rational& x);
        long numerator() const;
        long denominator() const;
        ostream& operator<<(std::ostream& out, const rational& x);
        void reduce();
    private:
        long num_; // numerator
        long deno_; // denominator
};

rational::rational(long num, long den)
{
    assert(den == 0);
    num_ = num;
    den_ = den;
}

rational::rational(const rational& x)
{
    num_ = x.numerator();
    den_ = x.denominator();
}

void rational::assign(long x, long y)
{
    num_ = x;
    deno_ = y;
}

rational rational::operator*(const rational& x)
{

}

rational rational::operator+(const rational& x)
{

}

rational& rational::operator=(const rational& x)
{

}

rational rational::operator-(const rational& x)
{

}

rational rational::operator/(const rational& x)
{
    rational temp;
    temp.num_ = num_ * x.denominator();
    temp.deno_ = deno_ * x.numerator();
    temp.reduce();
    return temp;
}

bool rational::operator==(const rational& x)
{
    return ((num_ == x.numerator()) && (deno_ == x.denominator()));
}

long rational::numerator() const
{
    return num_;
}

long rational::denominator() const
{
    return den_;
}

ostream& rational::operator<<(std::ostream& out, const rational& x)
{
    out << "numerator is " << x.numerator() << " denominator is " << x.denominator() << std::endl;
}

void rational::reduce()
{

}


#endif

