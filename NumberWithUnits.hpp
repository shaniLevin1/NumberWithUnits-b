#include <iostream>
#include <map>
#include <string>
using namespace std;

namespace ariel {
    class NumberWithUnits{

    private:
        double num;
        string units;

    public:
        NumberWithUnits(const double num,const string& units);
        static map<string, map<string, double> > number_units;
        static void read_units(ifstream& file);
        double convert_unit(const string &unit1, const string &unit2,const double number)const;
        NumberWithUnits operator+(const NumberWithUnits& num) const;
        NumberWithUnits operator-(const NumberWithUnits& num) const;
        NumberWithUnits operator-() const;
        NumberWithUnits operator+() const;
        NumberWithUnits& operator+=(const NumberWithUnits& num); //changing num 
        NumberWithUnits& operator-=(const NumberWithUnits& num);
        NumberWithUnits& operator++();
        NumberWithUnits& operator--();
        NumberWithUnits operator++(int);
        NumberWithUnits operator--(int);
        friend NumberWithUnits operator*(const NumberWithUnits& num, double n);
        friend NumberWithUnits operator*(double d, const NumberWithUnits& num);
        bool operator>(const NumberWithUnits& num) const;
        bool operator>=(const NumberWithUnits& num) const;
        bool operator<(const NumberWithUnits& num) const;
        bool operator<=(const NumberWithUnits& num) const;
        bool operator==(const NumberWithUnits& num) const;
        bool operator!=(const NumberWithUnits& num) const;
        friend ostream& operator<<(ostream& os, const NumberWithUnits& num);
        friend istream& operator>>(istream& is, NumberWithUnits& num);
    };      

}