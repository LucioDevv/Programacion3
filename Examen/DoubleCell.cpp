#include "DoubleCell.h"
#include <stdexcept>

// Default constructor
DoubleCell::DoubleCell()
        :Storedvalue(0.0){}

// Constructor with value
DoubleCell::DoubleCell(double value)
        : Storedvalue(value){}

// Copy constructor
DoubleCell::DoubleCell(const DoubleCell& other)
        : Storedvalue(other.Storedvalue){}

//Reference  constructor
DoubleCell::DoubleCell(DoubleCell&&  other) noexcept
        : Storedvalue(other.Storedvalue){
    other.Storedvalue=0;}

// Destructor
DoubleCell::~DoubleCell() {

}

// Assignment operator by copy
DoubleCell& DoubleCell::operator=(const DoubleCell& other){
    if (this != &other){
        Storedvalue = other.Storedvalue;
    }
    return *this;
}

// Assignment operator by reference
DoubleCell& DoubleCell::operator=(DoubleCell&& other){
    if (this != &other){
        Storedvalue = other.Storedvalue;
        other.Storedvalue=0;
    }
    return *this;
}

// Assignment operator for double
DoubleCell& DoubleCell::operator=(double value){
    Storedvalue = value;
    return *this;
}

// Arithmetic operators
//DoubleCell adding
DoubleCell DoubleCell::operator +(const DoubleCell& other) const{
    return DoubleCell(Storedvalue + other.Storedvalue);
}
//primitive double adding
DoubleCell DoubleCell::operator +(double other) const{

    return DoubleCell(Storedvalue + other);
}
//primitive double subtraction
DoubleCell DoubleCell::operator -(double other) const {

    return DoubleCell(Storedvalue - other);
}

//DoubleCell subtraction
DoubleCell DoubleCell::operator -(const DoubleCell& other) const{
    return DoubleCell(Storedvalue - other.Storedvalue);
}

//DoubleCell multiplication
DoubleCell DoubleCell::operator *(const DoubleCell& other) const{
    return DoubleCell(Storedvalue * other.Storedvalue);
}
//primitive double multiplication
DoubleCell DoubleCell::operator *(double other) const{

    return DoubleCell(Storedvalue * other);}
//DoubleCell division
DoubleCell DoubleCell::operator /(const DoubleCell& other) const{
    if(other.Storedvalue == 0){
        throw std::invalid_argument("Division by zero");
    }
    return DoubleCell(Storedvalue / other.Storedvalue);
}

//Primitive double division
DoubleCell DoubleCell::operator /(double value) const{
    if(value == 0){
        throw std::invalid_argument("Division by zero");
    }
    return DoubleCell(Storedvalue / value);
}

// Setters
void DoubleCell::setValue(double newValue) {
    Storedvalue = newValue;}

// Getter
double  DoubleCell::GetValue() const {return Storedvalue;}
