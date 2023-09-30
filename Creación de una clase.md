Floatcell.cpp

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

Floatcell.h

```
// ifndef significa que si no esta definido:  
#ifndef FLOATCELL_FLOATCELL_H
// se defina FLOATCELL_FLOATCELL_H
#define FLOATCELL_FLOATCELL_H


class Floatcell {
// Cosas publicas, osea que se pueden accesar fuera de la clase en si.
    public:
    // Se inicializa un valor al objeto.
        explicit Floatcell(float newValue = 0);
    // Este es un constructor que se utiliza cuando no obtiene un valor el objeto.
        Floatcell(const Floatcell &rhs);
    // Asigna la direccion de memoria del objeto derecho.
        Floatcell(Floatcell &&rhs) noexcept;
    // El destructor, se puede llamar manualmente o se llama automaticamente cuando se deja de usar un valor.
        ~Floatcell() = default;

// Operadores de copiar y mover.
        Floatcell &operator=(const Floatcell &rhs);
        Floatcell &operator=(Floatcell &&rhs) noexcept;

// Operador sobrecargado para poder aceptar floats.
        Floatcell &operator=(float rhs);

// Funcion para obtener los valores.
        float getValue() const;
// Funcion para asignar valores.
        void setValue(float newValue);
//Cosas privadas, no se pueden accesar fuera de la clase en si.
    private:
    // Variable en la cual se guarda el valor
        float storedValue;


};

// Final del if que actua si no se definio FLOATCELL_FLOATCELL_H

#endif //INTCELL H
```
