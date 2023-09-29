#ifndef DOUBLE_CELL_H
#define DOUBLE_CELL_H

class DoubleCell {
public:
    // Default constructor
    DoubleCell();
    // Constructor with value
    explicit DoubleCell(double value);

    // Copy constructor
    DoubleCell(const DoubleCell& other);

    //Reference constructor
    DoubleCell(DoubleCell&&other) noexcept;

    // Destructor
    ~DoubleCell();

    // Assignment operator by copy
    DoubleCell& operator=(const DoubleCell & other);
    // Assignment operator by reference
    DoubleCell& operator=(DoubleCell&& other);

    // Assignment operator for double
    DoubleCell& operator=(double value);

    // Arithmetic operators
    DoubleCell operator +(const DoubleCell& other) const;
    DoubleCell operator +(const double other) const;
    DoubleCell operator -(const DoubleCell& other) const;
    DoubleCell operator -(const double other) const;
    DoubleCell operator *(const DoubleCell& other) const;
    DoubleCell operator *(const double other) const;
    DoubleCell operator /(const DoubleCell& other) const;
    DoubleCell operator /(const double other) const;

    // Setters
    void setValue(double newValue);
    // Getters

    double GetValue() const;


private:
    double Storedvalue;
};

#endif  // DOUBLE_CELL_H