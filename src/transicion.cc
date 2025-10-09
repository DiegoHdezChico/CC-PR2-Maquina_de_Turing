/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 * 
 * @author Diego Hernández Chico
 * @date 20 Sep 2025
 * CORREO: alu0101572062@ull.edu.es
 * @brief Fichero con la definición de los métodos de la clase Transicion
*/

#include <iostream>

#include "../includes/transicion.h"

/**
 * @brief Constructor de la clase Transicion
 * 
 * @param descripcion_transicion desde la cual formaremos la transicion
 * @param id_estados identificador de los estados definidos del autómata
 * @param alfabeto_entrada del automata
 * @param alfabeto_pila del automata
 */
Transicion::Transicion(const std::vector<std::string>& descripcion_transicion) {
  id_estado_origen_ = descripcion_transicion[0];
  if (descripcion_transicion[1].size() != 1) {
    throw 3.1;
  }
  simbolo_alfabeto_a_consumir_ = descripcion_transicion[1][0];
  if (descripcion_transicion[2].size() != 1) {
    throw 3.2;
  }
  simbolo_pila_a_consumir_ = descripcion_transicion[2][0];
  id_estado_destino_ = descripcion_transicion[3];
  simbolos_pila_a_introducir_ = descripcion_transicion[4];
}

/**
 * @brief Imprime de forma ordenada la transicion
 */
void Transicion::ImprimeTransicion() const {
  std::cout << "(" << id_estado_origen_ << ", " << simbolo_alfabeto_a_consumir_ << ", " << simbolo_pila_a_consumir_ << ")";
  std::cout << " -> " << "(" << id_estado_destino_ << ", " << simbolos_pila_a_introducir_ << ")" << std::endl;
}