/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 * 
 * @author Diego Hernández Chico
 * @date 12 Oct 2025
 * CORREO: alu0101572062@ull.edu.es
 * @brief Fichero con la definición de los métodos de la clase ManejadorErrores
*/

#include <cmath>
#include <iostream>

#include "../includes/manejador_errores.h"

/**
 * @brief Maneja las excepciones generadas durante la ejecución del programa de forma general
 * 
 * @param codigo_error
 */
void ManejadorErrores::Alertar(double codigo_error) {
  codigo_general_ = floor(codigo_error);
  codigo_especifico_ = codigo_error * 10 - codigo_general_ * 10;
  switch (codigo_general_) {
    case 1:
      std::cout << "Error en la lectura del fichero. ";
      AlertaFicheroLectura();
    break;
    case 2:
      std::cout << "Error en la configuración de la máquina. ";
      AlertaMaquina();
      break;
    case 3: 
      std::cout << "Error en las transiciones. ";
      AlertaTransiciones();
      break;
    case 4:
      std::cout << " Alerta. Se ha superado el límite de recursividad establecido. Abortando..." << std::endl;
  }
}

/**
 * @brief Maneja las excepciones generadas durante la ejecución de la lectura de fichero de entrada
 */
void ManejadorErrores::AlertaFicheroLectura() {
  switch (codigo_especifico_) {
    case 1:
      std::cout << "No se ha podido abrir el fichero con la descripción de la máquina." << std::endl;
      break;
    case 2:
      std::cout << "Una de las transiciones tiene un número incorrecto de entradas." << std::endl;
      break;
    case 3:
      std::cout << "No se ha especificado un fichero de entrada de cadenas." << std::endl;
      break;
    case 4:
      std::cout << "No se ha encontrado el fichero con las cadenas de entrada." << std::endl;
      break;
    case 5:
      std::cout << "No se ha especificado un número de cintas valido." << std::endl;
  }
}

/**
 * @brief Maneja las excepciones generadas durante la configuración de la máquina
 */
void ManejadorErrores::AlertaMaquina() {
  switch (codigo_especifico_) {
    case 1:
      std::cout << "El conjunto de estados está vacío." << std::endl;
      break;
    case 2:
      std::cout << "El alfabeto de cinta está vacío." << std::endl;
      break;
    case 3:
      std::cout << "No se ha especificado un estado inicial." << std::endl;
      break;
    case 4:
      std::cout << "No se ha especificado un símbolo blanco." << std::endl;
      break;
    case 5:
      std::cout << "No se ha proporcionado ningún estado final." << std::endl;
      break;
    case 6:
      std::cout << "Se ha incluido estados en el conjunto de estados finales que no pertenecen al conjunto de estados." << std::endl;
      break;
    case 7:
      std::cout << "No se ha introducido un estado inicial válido." << std::endl;
      break;
    case 8:
      std::cout << "El símbolo blanco especificado no pertenece al alfabeto de cinta." << std::endl;
      break;
  }
}

/**
 * @brief Maneja las excepciones generadas en la descripción de las transiciones
 */
void ManejadorErrores::AlertaTransiciones() {
  switch (codigo_especifico_) {
    case 1:
      std::cout << "Una de las transiciones hace uso de más de un caracter de lectura." << std::endl;
      break; 
    case 2:
      std::cout << "Una de las transiciones hace uso de más de un caracter de escritura." << std::endl;
      break;
    case 3:
      std::cout << "Una de las transiciones hace uso de más de un caracter para indicar el movimiento de las cintas." << std::endl;
      break;
    case 4:
      std::cout << "Una de las transiciones tiene un estado de origen que no pertenece al conjunto de estados." << std::endl;
      break;
    case 5:
      std::cout << "Una de las transiciones tiene un estado de destino que no pertenece al conjunto de estados." << std::endl;
      break;
    case 6:
      std::cout << "Una de las transiciones trata de leer un símbolo que no pertenece al alfabeto de la cinta." << std::endl;
      break;
    case 7:
      std::cout << "Una de las transiciones trata de escribir un símbolo que no pertenece al alfabeto de la cinta." << std::endl;
      break;
    case 8:
      std::cout << "Una de las transiciones tiene un movimiento que no es valido (R, L, S)." << std::endl;
      break;
  }
}