```
#ifndef AVL_TREE_H  
#define AVL_TREE_H  
  
#include<iostream>  
#include<iomanip> 
#include<algorithm>  
#include<memory> 
  
template <typename T> // Se crea una plantilla que pueda trabajar con cualquier valor
class Node {  
public:  
    T data;
    int height; // int que indique la altura
    std::shared_ptr<Node<T>> left; //Puntero compartido que apunta a la izquierda 
    std::shared_ptr<Node<T>> right; //Puntero compartido que apunta a la derecha  
  
    Node(T data) : data(data), height(1), left(nullptr), right(nullptr) {} // Definición de Node  
};  
  
template <typename T> // Crea una plantilla para AVLTree 
class AVLTree {  
public:  
    std::shared_ptr<Node<T>> root; // Puntero para la raíz con valores de Node<T>  
  
    AVLTree(): root(nullptr) {} // AVLTree hereda de la raíz  
  
    void add(T data) {  
        root = insert(root, data); // Agrega a la raíz los datos actuales  
    }  
  
    void remove(T data)  {  
        root = deleteNode(root, data); // Elimina datos de la raíz  
    }  
  
    void print() {  
        if (root != nullptr) {  
            print(root, 0); // Si la raíz no está vacía, imprime  
        } else {  
            std::cout << "The tree is empty." << std::endl; // Si la raíz está vacía, indique que está vacía  
        }  
    }  
  
private:  
    void print(std::shared_ptr<Node<T>> node, int indent) {  
        if(node) {  
            if(node->right) { // Verifica si el nodo actual tiene un nodo derecho y se mueve a él  
                print(node->right, indent + 8); // Imprime el hijo derecho del nodo actual con una sangría de 8, para  
            }  
            if (indent) { // Si el indent tiene un valor, entonces establece dicho valor como ancho, setw = setwidth
                std::cout << std::setw(indent) << ' ';  
            }  
            if (node->right) { // Verifica si el nodo actual tiene un nodo derecho y se mueve a él  
                std::cout << " / (Derecho de " << node->data << ")\n" << std::setw(indent) << ' '; // Imprime el lado derecho de los datos actuales  
            }  
            std::cout << node->data << "\n" ; // Imprime los datos  
            if (node->left) { // Verifica si el nodo actual tiene un nodo izquierdo y se mueve a él  
                std::cout << std::setw(indent) << ' ' << " \\ (Izquierdo de " << node->data << ")\n"; // Imprime el lado izquierdo de los datos actuales  
                print(node->left, indent + 8);  
            }  
        }  
    }  
  
//Crea un nuevo nodo  
    std::shared_ptr<Node<T>> newNode(T data) {  
        return std::make_shared<Node<T>>(data);  
    }  
  
/*ROTACIONES PARA REBALANCEO*/  
// Rota en el sentido de las agujas del reloj el nodo deseado  
    std::shared_ptr<Node<T>> rightRotate(std::shared_ptr<Node<T>> y) {  
        std::shared_ptr<Node<T>> x = y->left; // Asigna x como el valor de y->left (hijo izquierdo de y)  
        std::shared_ptr<Node<T>> T2 = x->right; // Asigna T2 como el valor de x->right (hijo derecho de x)  
  
        x->right = y; // Asigna y al hijo derecho de x  
        y->left = T2; // Asigna T2 al hijo izquierdo de y  
  
        y->height = max(height(y->left), height(y->right))+1; // Recalcula la altura de y  
        x->height = max(height(x->left), height(x->right))+1; // Recalcula la altura de x  
  
        return x;  
    }  
  
// Rota en sentido contrario a las agujas del reloj el nodo deseado  
    std::shared_ptr<Node<T>> leftRotate(std::shared_ptr<Node<T>> x) {  
        std::shared_ptr<Node<T>> y = x->right; // Asigna y a el valor de x->right  
        std::shared_ptr<Node<T>> T2 = y->left; // Asigna T2 a el valor de y->left  
  
        y->left = x; // Asigna x al hijo izquierdo de y  
        x->right = T2; // Asigna T2 al hijo derecho de x  
  
        x->height = max(height(x->left),height(x->right))+1; // Recalcula la altura de x  
        y->height = max(height(y->left),height(y->right))+1; // Recalcula la altura de y  
  
        return y;  
    }  
  
    int getBalance(std::shared_ptr<Node<T>> N) {  
        if (N == nullptr) // Si el nodo es nulo, devuelve 0.  
            return 0;  
        return height(N->left) - height(N->right); // Si el nodo no es nulo, resta la altura del lado izquierdo menos la altura del lado derecho  
    }  
  
    std::shared_ptr<Node<T>> insert(std::shared_ptr<Node<T>> node, T data) {  
        if (node == nullptr) // Si el nodo es nulo, crea un nuevo nodo con los datos asignados  
            return (newNode(data));  
  
        if (data < node->data) // Comprueba si los datos son menores que los datos en el nodo  
            node->left = insert(node->left, data); // Si es así, se asigna un nuevo nodo con dichos datos al hijo izquierdo del nodo  
        else if (data > node->data) // Si no se cumple la condición anterior, comprueba si los datos son mayores que los datos en el nodo  
            node->right = insert(node->right, data); // Si es así, se asigna un nuevo nodo con dichos datos al hijo derecho del nodo  
        else  
            return node; // Devuelve el nodo si no se cumple ninguna condición anterior  
  
        node->height = 1 + max(height(node->left), height(node->right)); // Recalcula la altura después de la inserción  
  
        int balance = getBalance(node); // Crea una variable int para verificar el balance usando la resta previamente definida  
  
        if (balance > 1 && data < node->left->data) // Si el balance es mayor que 1 Y los datos son menores que los datos en el hijo izquierdo del nodo  
            return rightRotate(node); // Rota en el sentido de las agujas del reloj en dicho nodo  
  
        if (balance < -1 && data > node->right->data) // Si el balance es menor que -1 Y los datos son mayores que los datos en el hijo derecho del nodo  
            return leftRotate(node); // Rota en el sentido contrario a las agujas del reloj en dicho nodo  
  
        if (balance > 1 && data > node->left->data) { // Si el balance es mayor que 1 Y los datos son mayores que los datos en el hijo izquierdo del nodo  
            node->left = leftRotate(node->left); // Rota en el sentido contrario a las agujas del reloj en el hijo izquierdo del nodo y asigna el nuevo valor de rotación al nodo  
            return rightRotate(node); // Rota en el sentido de las agujas del reloj en dicho nodo (con rotación izquierda)  
        }  
  
        if (balance < -1 && data < node->right->data) { // Si el balance es menor que -1 Y los datos son menores que los datos en el hijo derecho del nodo  
            node->right = rightRotate(node->right); // Rota en el sentido de las agujas del reloj en el hijo derecho del nodo y asigna el nuevo valor de rotación al nodo  
            return leftRotate(node); // Rota en el sentido contrario a las agujas del reloj en dicho nodo (con rotación derecha)  
        }  
  
        return node; // Devuelve el nodo con la rotación  
    }  
  
    std::shared_ptr<Node<T>> minValueNode(std::shared_ptr<Node<T>> node) {  
        std::shared_ptr<Node<T>> current = node; // Declara un nuevo nodo llamado current con el valor del nodo actual  
  
        while (current->left != nullptr) // Mientras el hijo izquierdo del nodo actual no sea nulo  
            current = current->left; // Declara el nodo actual como su hijo izquierdo  
  
        return current; // Devuelve el nodo actual  
    }  
  
    std::shared_ptr<Node<T>> deleteNode(std::shared_ptr<Node<T>> root, T data) {  
        if (!root) // Comprueba si la raíz está vacía  
            return root; // Si es así, devuelve la raíz (nullptr) ya que no hay nada  
  
        if (data < root->data) { // Si los datos son menores que los datos en la raíz  
            root->left = deleteNode(root->left, data); // En el hijo izquierdo del nodo, elimina el nodo izquierdo  
        }  
        else if(data > root->data) { // Si los datos son mayores que los datos en la raíz  
            root->right = deleteNode(root->right, data); // En el hijo derecho del nodo, elimina el nodo derecho  
        }  
        else {  
            if(!root->left || !root->right) { // Comprueba si el hijo izquierdo o derecho de la raíz está vacío  
                root = (root->left) ? root->left : root->right; // Si el hijo izquierdo de la raíz existe, se asigna a la raíz el hijo izquierdo de la raíz. Si no, se asigna el hijo derecho de la raíz  
            }  
            else {  
                std::shared_ptr<Node<T>> temp = minValueNode(root->right); // Asigna a temp Node el valor mínimo del lado derecho de la raíz  
                root->data = temp->data; // Asigna a los datos de la raíz los datos de temp  
                root->right = deleteNode(root->right, temp->data); // Elimina en el lado derecho del nodo los datos de temp  
                temp.reset(); // Reinicia temp  
            }  
        }  
  
        if(!root) // Comprueba si la raíz existe  
            return root; // Devuelve la raíz (nullptr)  
  
        root->height = 1 + max(height(root->left), height(root->right)); // Recalcula la altura después de la eliminación  
  
        int balance = getBalance(root); // Crea int para el balance desde la raíz  
  
        if (balance > 1 && getBalance(root->left) >= 0) // Si el balance es mayor que 1 Y el balance del hijo izquierdo de la raíz es mayor o igual a 0  
            return rightRotate(root); // Rota en el sentido de las agujas del reloj en la raíz  
  
        if (balance < -1 && getBalance(root->right) <= 0) // Si el balance es menor que -1 Y el balance del hijo derecho de la raíz es menor o igual a 0  
            return leftRotate(root); // Rota en el sentido contrario a las agujas del reloj en la raíz  
  
        if (balance > 1 && getBalance(root->left) < 0) { // Si el balance es mayor que 1 Y el balance del hijo izquierdo de la raíz es menor que 0  
            root->left = leftRotate(root->left); // Rota en el sentido contrario a las agujas del reloj en el hijo izquierdo de la raíz  
            return rightRotate(root); // Rota en el sentido de las agujas del reloj en la raíz  
        }  
  
        if (balance < -1 && getBalance(root->right) > 0) { // Si el balance es menor que -1 Y el balance del hijo derecho de la raíz es mayor que 0  
            root->right = rightRotate(root->right); // Rota en el sentido de las agujas del reloj en el hijo derecho de la raíz  
            return leftRotate(root); // Rota en el sentido contrario a las agujas del reloj en la raíz  
        }  
  
        return root; // Devuelve la raíz después de la rotación  
    }  
  
    int height(std::shared_ptr<Node<T>> N) {  
        if (N == nullptr) // Comprueba si N es nulo, si es así devuelve 0  
            return 0;  
        return N->height; // Si no, devuelve la altura de N  
    }  
  
    int max(int a, int b) {  
        return (a > b)? a : b; // Comprueba si a es mayor que b. Si es así, devuelve a. Si no, devuelve b  
    }  
};  
  
#endif /* AVL_TREE_H */
```

Arbol AVL:

	Que es un arbol AVL?

Es un arbol binario el cual siempre esta equilibrado de forma que para todos los nodos, la altura no difiera de un lado a otro. [1]

	Que es un arbol binario?

Un arbol binario es una estructura de datos donde cada nodo puede tener un hijo izquierdo y un hijo derecho. No pueden tener más de dos hijos, de ahí es donde viene el nombre de "binario" [2]

	Como se representa un arbol AVL?
[[220px-AVL_Tree_Example.gif]]
![[AVLtreef.svg 2.png]]

[1] Wikipedia. (2021, 9 mayo)  Árbol AVL. (En linea) https://es.wikipedia.org/wiki/%C3%81rbol_AVL
[2] Wikipedia. (2022, 25 febrero)  Árbol Binario. (En linea) https://es.wikipedia.org/wiki/%C3%81rbol_binario