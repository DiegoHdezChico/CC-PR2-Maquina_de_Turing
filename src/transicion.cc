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
 * @param id_estados identificador de los estados definidos de la máquina
 * @param alfabeto_entrada de la maquina
 * @param alfabeto_pila de la maquina
 */
Transicion::Transicion(const std::vector<std::string>& descripcion_transicion, int numero_cintas) {
  int indice_estado_origen{0};
  int indice_estado_destino{numero_cintas + 1};
  int indice_comienzo_escritura{indice_estado_destino + 1};
  id_estado_origen_ = descripcion_transicion[0];
  id_estado_destino_ = descripcion_transicion[indice_estado_destino];
  char simbolo_a_leer{' '};
  char simbolo_a_escribir{' '};
  char direccion_movimiento{' '};
  std::vector<std::vector<char>> descripciones_cinta;
  for (int i{0}; i < numero_cintas; ++i) {
    descripciones_cinta.push_back(std::vector<char>());
  }

  for (int i{0}; i < numero_cintas; ++i) {
    if (descripcion_transicion[i + 1].size() != 1) {
      throw 3.1;
    }
    simbolo_a_leer = descripcion_transicion[i + 1][0];
    descripciones_cinta[i].push_back(simbolo_a_leer);
    if (descripcion_transicion[indice_comienzo_escritura + 2 * i].size() != 1) {
      throw 3.2;
    }
    if (descripcion_transicion[indice_comienzo_escritura + 2 * i + 1].size() != 1) {
      throw 3.3;
    }
    simbolo_a_escribir = descripcion_transicion[indice_comienzo_escritura + 2 * i][0];
    direccion_movimiento = descripcion_transicion[indice_comienzo_escritura + 2 * i + 1][0];
    descripciones_cinta[i].push_back(simbolo_a_escribir);
    descripciones_cinta[i].push_back(direccion_movimiento);
  }
  for (int i{0}; i < descripciones_cinta.size(); ++i) {
    simbolo_a_leer = descripciones_cinta[i][0];
    simbolo_a_escribir = descripciones_cinta[i][1];
    direccion_movimiento = descripciones_cinta[i][2];
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