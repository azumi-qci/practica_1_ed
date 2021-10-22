
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <boost/algorithm/string.hpp>
// Librerias para generar numero aleatorio
#include <stdlib.h>
#include <time.h>

#define DELIMITADOR "|"
#define SEPARADOR "\n"
#define NOMBRE_ARCHIVO "Catalogo_Dia.txt"

/**
 * Práctica 1
 * Materia: Estructura de datos II
 * Profesor/a: Lara López Graciela
 * Sección: D12
 *
 * - Integrantes del equipo -
 * Hernández Suárez Cesar Alejandro
 * Lepiz Hernández Manuel Alejandro
 * Ocampo Orozco Alan Vidal
 */

using std::atoi;
using std::cin;
using std::cout;
using std::endl;
using std::exit;
using std::ifstream;
using std::ios;
using std::ofstream;
using std::string;
using std::stringstream;
using std::system;
using std::to_string;
using std::toupper;

// Declarar la estructura "Producto"

struct Producto {
  string code;
  string name;
  string description;
  string trademark;
  string price;
  string available;
  string province;
  string category;
  char active;
  int length;
};

// Declaración de funciones
void pauseConsole();
void clearConsole();
int opcionesMenu();
void capturarProducto();
void imprimirProducto(const Producto &p);
string generarCodigoProducto(const Producto &p);
void productoToUpper(Producto &p);
void escribirProductoEnArchivo(const Producto &p);
void imprimir();

/**
 * Función principal
 */
int main()
{
  Producto producto;
  
  while (true)
  {
    clearConsole();

    switch(opcionesMenu())
    {
      case 1: 
        capturarProducto();

        break;
      case 2:
        imprimir();

        break;
      case 3:
        break;
      case 4:
        break;

      case 5:
      {
        cout << "Saliendo del programa..." << endl;

        exit(0);
      }
      default:
      {
        cout << "Opción no válida" << endl;

        pauseConsole();
        break;
      }
    }
  }
}

/**
 * Función que pausa la ejecución del programa
 */
void pauseConsole()
{
  cout << endl;
  cout << "Presione ENTER para continuar...";
  cin.get();
}

/**
 * Función que limpia la consola
 */
void clearConsole()
{
  system("clear || cls");
}

/**
 * Función que muestra las opciones disponibles
 */
int opcionesMenu()
{
  // Char para comprobar cualquier tipo de caracter, no solo números
  char option[1];

  cout << "- Menú de opciones -" << endl;
  cout << "1. Insertar producto" << endl;
  cout << "2. Mostrar productos" << endl;
  cout << "3. Eliminar producto (forma lógica)" << endl;
  cout << "4. Generar lista de productos" << endl;
  cout << "5. Salir" << endl;
  cout << "Opción: ";

  cin >> option;
  cin.ignore();

  // Convierte un char a int, si no es un número válido, regresará 0
  return atoi(option);
}

/**
 * Función que captura los datos de un producto y lo guarda en el archivo
 */
void capturarProducto()
{
  clearConsole();

  Producto producto;

  cout << "- Capturar nuevo producto -" << endl << endl;
  cout << "Nombre: ";
  getline(cin, producto.name);
  cout << "Descripción: ";
  getline(cin, producto.description);
  cout << "Marca: ";
  getline(cin, producto.trademark);
  cout << "Precio: ";
  getline(cin, producto.price);
  cout << "Cantidad disponible: ";
  getline(cin, producto.available);
  cout << "Provincia: ";
  getline(cin, producto.province);
  cout << "Categoria: ";
  getline(cin, producto.category);

  // Generar código del producto
  producto.code = generarCodigoProducto(producto);
  // Convertir en mayúsculas todas las cadenas
  productoToUpper(producto);
  // Guardar producto en archivo
  escribirProductoEnArchivo(producto);

  cout << "Producto registrado correctamente" << endl;
  
  pauseConsole();
}

/**
 * Función que muestra todos los datos del producto
 * Nota: SOLO PARA DEBUGGING
 */
void imprimirProducto(const Producto &p)
{
  cout << "Producto " << endl;
  cout << p.code << " ";
  cout << p.name << " ";
  cout << p.description << " ";
  cout << p.trademark << " ";
  cout << p.price << " ";
  cout << p.available << " ";
  cout << p.province << " ";
  cout << p.category;
}

/**
 * Función que busca y muestra el producto deseado
 */
void imprimir()
{
  clearConsole();

  Producto p;
  string bclave;
  ifstream archivo(NOMBRE_ARCHIVO, ios::in);

  bool encontrado = false;

  cout << "- Buscar producto - " << endl;
  cout << "Ingrese la clave del producto: ";

  cin >> bclave;
  cin.ignore();

  while (!archivo.eof())
  {
    archivo >> p.code;
    if (p.code.find(bclave) != string::npos)
    {
      encontrado = true;

      cout << "clave: " << p.code << endl;    
      archivo >> p.name;
      cout << "Nombre:" << p.name << endl;
      archivo >> p.description;
      cout << "Descripción: " << p.description << endl;
      archivo >> p.trademark;
      cout << "Marca: " << p.trademark << endl;
      archivo >> p.price;
      cout << "Price:" << p.price << endl;
      archivo >> p.available;
      cout << "Disponibles: " << p.available << endl;
      archivo >> p.province;
      cout << "Provincia: " << p.province << endl;
      archivo >> p.category;
      cout << "Category:" << p.category << endl;
    }
  }

  if (!encontrado)
  {
    cout << endl << "Producto no encontrado" << endl;
  }

  if (archivo.is_open())
  {
    archivo.close();
  }

  pauseConsole();
}

/**
 * Función que genera el código del producto
 */
string generarCodigoProducto(const Producto &p) {
  int numeroAleatorio;
  stringstream codigo;
  string numero, caracter;

  srand(time(NULL)); // Semilla para generar un numero
  numeroAleatorio = rand() % 999; // Entre 0 y 999

  // Si el numero es menor que 100 agregamos un "0" para que sean 3 digitos
  if (numeroAleatorio<100) codigo << "0";
  numero = to_string(numeroAleatorio); 
  // Seleccionar los primeros caracteres de las cadenas 
  codigo << numero;

  for (int i(0); i < 2; i++)
  {
    caracter = p.category[i];
    codigo << caracter;
  }

  for (int i(0); i < 3; i++)
  {
    caracter = p.trademark[i];
    codigo << caracter;
  }

  for (int i(0); i < 2; i++)
  {
    caracter = p.name[i];
    codigo << caracter;
  }  

  // Retornar un string del objeto stringstream
  return codigo.str();
}

/**
 * Funcion para convertir a mayus todas las cadenas del registro
 */
void productoToUpper(Producto &p) {
  boost::to_upper(p.code);
  boost::to_upper(p.name);
  boost::to_upper(p.description);
  boost::to_upper(p.trademark);
  boost::to_upper(p.province);
  boost::to_upper(p.category);
}

/**
 * Función que escribe un nuevo producto al archivo
 */
void escribirProductoEnArchivo(const Producto &p) {
  // Crear un objeto de salida de archivo, y agregar los elementos al final del archivo
  ofstream archivo(NOMBRE_ARCHIVO, ios::app);

  stringstream producto;

  producto << p.code << DELIMITADOR;
  producto << p.name << DELIMITADOR;
  producto << p.description << DELIMITADOR;
  producto << p.trademark << DELIMITADOR;
  producto << p.price << DELIMITADOR;
  producto << p.available << DELIMITADOR;
  producto << p.province << DELIMITADOR;
  producto << p.category << DELIMITADOR << SEPARADOR;

  if (archivo.is_open())
  {
    archivo << producto.str();
    archivo.close();
  }
}

//Eliminar producto forma logica
/*
void eliminarProductoFormaLogica(const Producto &p){

}*/
