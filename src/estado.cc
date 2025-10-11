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
 * @brief Devuelve un vector con las transiciones disponibles a partir de un simbolo de entrada
 * y de pila dados
 * 
 * @param simbolo_entrada que participa en la transicion
 * @param simbolo_pila que participa en la transicion
 * @return transiciones disponibles con esos símbolos de entrada y pila
 */
// std::shared_ptr<const std::vector<std::pair<int, Transicion>>> 
//     Estado::TransicionesPosibles(char simbolo_cadena, char simbolo_pila) {
//   // std::cout << "llegada a transiciones posibles con simbolo de cadena "  << simbolo_cadena << " y simbolo de pila " 
//   // << simbolo_pila << std::endl;
//   std::shared_ptr<std::vector<std::pair<int, Transicion>>> transiciones_posibles;
//   transiciones_posibles = std::make_shared<std::vector<std::pair<int, Transicion>>>();
//   for (int i{0}; i < transiciones_estado_->size(); ++i) {
//     if (simbolo_pila == transiciones_estado_->at(i).second.simbolo_pila_a_consumir()) {
//       if (simbolo_cadena == transiciones_estado_->at(i).second.simbolo_alfabeto_a_consumir()
//           || transiciones_estado_->at(i).second.simbolo_alfabeto_a_consumir() == '.') {
//         transiciones_posibles->push_back(transiciones_estado_->at(i));
//       }
//     }
//   }
//   return transiciones_posibles;
// }