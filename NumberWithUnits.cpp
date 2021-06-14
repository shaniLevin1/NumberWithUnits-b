#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "NumberWithUnits.hpp"
using namespace std;
using namespace ariel;

namespace ariel {
    const double epsilon = 0.0001;
    map<string, map<string, double>> NumberWithUnits::number_units; 

    NumberWithUnits::NumberWithUnits(const double _num,const string& _units): num(_num) , units(_units){
        if(number_units.find(_units)==number_units.end()){
            throw "there is no unit like this";
        }
    }
    void NumberWithUnits::read_units(ifstream& units_file){
        double num1=0;
        double num2=0; 
        string unit1;
        string unit2;
        string space;
        string line;
            while(units_file>> num1 >> unit1 >> space >> num2 >> unit2){
                NumberWithUnits::number_units[unit1][unit2] = num2;
                NumberWithUnits::number_units[unit2][unit1] = 1/num2;
                
                for(auto &un1 : NumberWithUnits::number_units[unit2]) {
                    double w = NumberWithUnits::number_units[unit1][unit2] * un1.second;
                    NumberWithUnits::number_units[unit1][un1.first] = w;
                    NumberWithUnits::number_units[un1.first][unit1] = 1/w;
                }
                for(auto &un2 : NumberWithUnits::number_units[unit1]) {
                    double w = NumberWithUnits::number_units[unit2][unit1] * un2.second;
                    NumberWithUnits::number_units[unit2][un2.first] = w;
                    NumberWithUnits::number_units[un2.first][unit2] = 1/w;
                }

            }       
    }

    double NumberWithUnits::convert_unit(const string &unit1, const string &unit2,const double number) const{
        if(unit1==unit2) {
            return number;
        }
        if(NumberWithUnits::number_units.at(unit1).at(unit2)==0){
            throw "There is no way to convert between the units";
        }
        return NumberWithUnits::number_units[unit1][unit2]*number;
    }

    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& n) const{
        return NumberWithUnits(this->num + convert_unit(n.units, this->units,n.num),this->units);
    }
    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits& n) const{
        return NumberWithUnits(this->num - convert_unit(n.units, this->units,n.num),this->units);
    }
    NumberWithUnits NumberWithUnits::operator-() const{
        return NumberWithUnits(-this->num,this->units);
    }
    NumberWithUnits NumberWithUnits::operator+() const{
        return NumberWithUnits(+this->num,this->units);
        
    }
    NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits& n){
        this->num+=convert_unit(n.units, this->units,n.num);
        return *this;
    }
    NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& n){
        this->num-=convert_unit(n.units, this->units,n.num);
        return *this;
    }

    NumberWithUnits& NumberWithUnits::operator++(){
        this->num++;
        return *this;
    }
    NumberWithUnits& NumberWithUnits::operator--(){
        this->num--;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator++(int){
        NumberWithUnits same= *this;
        ++this->num;
        return same;
    }
    NumberWithUnits NumberWithUnits::operator--(int){
        NumberWithUnits same= *this;
        --this->num;
        return same;
    }
    NumberWithUnits operator*(const NumberWithUnits& n, double num){
        return NumberWithUnits(n.num*num,n.units);
    }
    NumberWithUnits operator*(double num,const NumberWithUnits& n){
        return NumberWithUnits(n.num*num,n.units);
    }

    bool NumberWithUnits::operator>(const NumberWithUnits& n1) const{
        double a=convert_unit(n1.units,this->units,n1.num);
        double b=this->num-a;
        return b>epsilon;
    }
    bool NumberWithUnits::operator>=(const NumberWithUnits& n1) const{
        return !(n1>*this);
    }
    bool NumberWithUnits::operator<(const NumberWithUnits& n1) const{
        return n1>*this;
    }
    bool NumberWithUnits::operator<=(const NumberWithUnits& n1) const{
        return !(*this>n1);
    }
    bool NumberWithUnits::operator==(const NumberWithUnits& n1) const{
        double a=convert_unit(n1.units,this->units,n1.num);
        double b=this->num-a;
        return abs(b)<epsilon;
    }
    bool NumberWithUnits::operator!=(const NumberWithUnits& n1) const{
        return !(*this == n1);
    }
    ostream& operator<<(ostream& out, const NumberWithUnits& n){
        out<<n.num<<"[" <<n.units<<"]";
        return out;
    }
    istream& operator>>(istream& in, NumberWithUnits& n){
        double num=0;
        string unit="";
        char c=']';
        char c1=' '; 
        char c2=' ';
        in >>num>>c1 >>unit;
        if(unit[unit.length()-1]==c) // c=']'
            unit=unit.erase(unit.length()-1); //remove ']'
        else
            in>>c2;
        n=NumberWithUnits(num,unit);
        return in;
    }
}