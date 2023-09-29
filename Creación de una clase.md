```

#include "Floatcell.h"
// Se escribe el constructor normal, al cual se le puede meter un valor.

// Default constructor
Floatcell::Floatcell(float newValue) : storedValue(newValue) {}

// Este constructor puede copiar valores de otro objeto sin depender del original.

// Copy constructor
Floatcell::Floatcell(const Floatcell &rhs) : storedValue(rhs.storedValue) {}

// Move constructor
Floatcell::Floatcell(Floatcell &&rhs) noexcept : storedValue(rhs.storedValue) {
    // rhs.storedValue = 0;
}

// Se introduce el operador= para copiar valores de otros floatcells

// Copy assignment operator
Floatcell &Floatcell::operator=(const Floatcell &rhs) {
    if (this != &rhs) {
        storedValue = rhs.storedValue;
    }
    return *this;
}

//En este operador el valor del lado derecho se mueve y el valor que estuvo alli se repone a 0.

// Remove Move assignment operator
Floatcell &Floatcell::operator=(Floatcell &&rhs) noexcept {
    if (this != &rhs) {
        storedValue = rhs.storedValue;
        rhs.storedValue = 0;
    }
    return *this;
}

//El operador se sobrecarga para que solo pueda aceptar integers enteros.

// Overloaded assignment operator to accept only integer data
Floatcell &Floatcell::operator=(float rhs) {
    storedValue = rhs;
    return *this;}
```