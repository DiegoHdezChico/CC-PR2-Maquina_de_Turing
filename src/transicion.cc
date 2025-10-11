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
Transicion::Transicion(const std::vector<std::string>& descripcion_transicion, int numero_cintas) {
  id_estado_origen_ = descripcion_transicion[0];
  id_estado_destino_ = descripcion_transicion[1];
  char simbolo_a_leer{' '};
  char simbolo_a_escribir{' '};
  char direccion_movimiento{' '};
  for (int i {0}; i < numero_cintas * 3; i += 3) {
    if (descripcion_transicion[i + 2].size() != 1) {
      throw 3.1;
    }
    if (descripcion_transicion[i + 3].size() != 1) {
      throw 3.2;
    }
    if (descripcion_transicion[i + 4].size() != 1) {
      throw 3.3;
    }
    simbolo_a_leer = descripcion_transicion[i + 2][0];
    simbolo_a_escribir = descripcion_transicion[i + 3][0];
    direccion_movimiento = descripcion_transicion[i + 4][0];
    transiciones_cinta_.push_back(TransicionCinta(simbolo_a_leer, simbolo_a_escribir, direccion_movimiento));
  }
}

/**
 * @brief Imprime de forma ordenada la transicion
 */
void Transicion::ImprimeTransicion() const {
  std::cout << id_estado_origen_ << ", " << id_estado_destino_ << "," << std::endl;
  for (int i{0}; i < transiciones_cinta_.size(); ++i) {
    std::cout << "\tCinta " << i + 1 << ": ";
    transiciones_cinta_[i].ImprimeTransicionCinta();
    std::cout << std::endl;
  }
}