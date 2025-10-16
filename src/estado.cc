/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 * 
 * @author Diego Hernández Chico
 * @date 22 Sep 2025
 * CORREO: alu0101572062@ull.edu.es
 * @brief Fichero con la definición de los métodos de la clase Estado
*/

#include <iostream>

#include "../includes/estado.h"

/**
 * @brief Constructor de la clase Estado
 * 
 * @param id del estado a crear
 * @param es_final para indicar si estamos ante un estado de este tipo
 * @param tranciciones_estado Aquellas que parten desde el propio estado
 */
Estado::Estado(std::string id, bool es_final, std::shared_ptr<std::vector<std::pair<int, Transicion>>> transiciones_estado) {
  id_ = id;
  es_final_ = es_final;
  transiciones_estado_ = transiciones_estado;
}

/**
 * @brief Imprime las transiciones del estado
 */
void Estado::ImprimeTransiciones() {
  for (int i{0}; i < transiciones_estado_->size(); ++i) {
    std::cout << transiciones_estado_->at(i).first << ": ";
    transiciones_estado_->at(i).second.ImprimeTransicion();
  }
}

/**
 * @brief Devuelve la transicion disponible para los simbolos sobre los cuales 
 * se encuentra la cabeza de lectura/escritura actualmente
 * 
 * @param simbolos_lectura
 * @return O bien la transición encontrada, o null en caso de no haber 
 * ninguna
 */
std::shared_ptr<const Transicion> Estado::TransicionPosible(std::shared_ptr<std::vector<char>> simbolos_lectura, int numero_cintas) const {
  bool transicion_posible{true};
  for (int i{0}; i < transiciones_estado_->size(); ++i) {
    for (int j{0}; j < numero_cintas; ++j) {
      if (transiciones_estado_->at(i).second.simbolo_a_leer(j) != simbolos_lectura->at(j)) {
        transicion_posible = false;
      }
    }
    if (transicion_posible == true) {
      return std::make_shared<const Transicion>(transiciones_estado_->at(i).second);
    }
    transicion_posible = true;
  }
  return nullptr;
}