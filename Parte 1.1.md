i. ¿Qué es un Rvalor y un Lvalor?
El Rvalores son variables que se les asigna valores mientras que los Lvalores son variables las cuales tienen un Rvalor asignado, pero a un Rvalor no se le puede asignar un Lvalor

ii. ¿Porqué es necesario que una clase tenga constructores y operadores por
copia y por referencia?
Necesita tener constructores y operadores porque ocupa referenciar no solo la informacion original si no tambien la referencia.

iii. ¿Qué función desarrollan los :: en la implementación de la clase?
Los :: sirven para acceder a las variables o funciones de una clase.

iv. ¿Cómo se le denomina a cuando una clase posee un operador puede
tener múltiples implementaciones dependiendo de los argumentos que
este reciba?
Es una sobrecarga de funciones

v. ¿Cúal es la funcion del archivo .h ?
Un archivo .h es conocido como el header, el proposito del header es declarar variables, funciones, y constantes.

Complejidad Temporal
Calcular la complejidad temporal en Big(O) Notation del siguiente algoritmo:

```
#include <iostream>
int algoritmo1(int n) {
int resultado = 0;
for (int i = 0; i < n; i++) {
resultado += i; // Operación simple O(1)
}
for (int i = 0; i < n; i++) {
for (int j = 0; j < n; j++) {
resultado += i * j; // Operación simple O(1)
}
}
return resultado;
}
int main() {
int n;
std::cout << "Ingrese el valor de n: ";
std::cin >> n;

int resultado = algoritmo1(n);
std::cout << "Resultado: " << resultado << std::endl;
return 0;
}
```
O(n^2)