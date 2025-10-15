/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 * 
 * @author Diego Hernández Chico
 * @date 9 Oct 2025
 * CORREO: alu0101572062@ull.edu.es
 * @brief Fichero con la definición de metodos de la clase ComprobadorMaquina
*/

#include <iostream>

#include "../includes/comprobador_maquina.h"

/**
 * @brief Comprueba que la configuración de la máquina sea correcta
 * 
 * @param id_estados
 * @param alfabeto_entrada
 * @param alfabeto_pila
 * @param id_estado_inicial
 * @param id_estados_finales
 * @param descripcion_transiciones
 */
void ComprobadorMaquina::Ejecutar(std::shared_ptr<std::vector<std::string>> id_estados, 
      std::shared_ptr<std::vector<char>> alfabeto_entrada, 
      std::shared_ptr<std::vector<char>> alfabeto_cinta, std::string id_estado_inicial,
      char simbolo_blanco, std::shared_ptr<std::vector<std::string>> id_estados_finales, 
      std::shared_ptr<std::vector<std::vector<std::string>>> descripcion_transiciones, int numero_cintas) {
  if (id_estados->empty()) {
    throw 2.1;
  }
  if (alfabeto_cinta->empty()) {
    throw 2.2;
  }
  if (id_estado_inicial == "") {
    throw 2.3;
  }
  if (simbolo_blanco == ' ') {
    throw 2.4;
  }
  if (id_estados_finales->empty()) {
    throw 2.5;
  }
  std::vector<std::string> interseccion;
  bool estado_inicial_valido{false};
  for (int i{0}; i < id_estados->size(); ++i) {
    for (int j{0}; j < id_estados_finales->size(); ++j) {
      if (id_estados->at(i) == id_estados_finales->at(j)) {
        interseccion.push_back(id_estados->at(i));
      }
    }
    if (id_estado_inicial == id_estados->at(i)) {
      estado_inicial_valido = true;
    }
  }
  if (interseccion.size() != id_estados_finales->size()) {
    throw 2.6;
  }
  if (!estado_inicial_valido) {
    throw 2.7;
  }
  bool simbolo_blanco_valido{false};
  for (int i{0}; i < alfabeto_cinta->size(); ++i) {
    if (alfabeto_cinta->at(i) == simbolo_blanco) {
      simbolo_blanco_valido = true;
    }
  }
  if (!simbolo_blanco_valido) {
    std::cout << "el símbolo blanco no es válido" << std::endl;
    throw 2.8;
  }
  CompruebaTransiciones(id_estados, alfabeto_entrada, alfabeto_cinta, descripcion_transiciones, numero_cintas);
}

/**
 * @brief Comprueba que las transiciones de la máquina sean correctas
 * 
 * @param id_estados
 * @param alfabeto_entrada
 * @param alfabeto_cinta
 * @param descripcion_transiciones que queremos comprobar
 */
void ComprobadorMaquina::CompruebaTransiciones(std::shared_ptr<std::vector<std::string>> id_estados, 
      std::shared_ptr<std::vector<char>> alfabeto_entrada, 
      std::shared_ptr<std::vector<char>> alfabeto_cinta,
      std::shared_ptr<std::vector<std::vector<std::string>>> descripcion_transiciones, int numero_cintas) {
  std::string id_estado_origen{""};
  std::string id_estado_destino{""};
  char simbolo_a_leer{' '};
  char simbolo_a_escribir{' '};
  char movimiento_a_realizar{' '};
  bool transicion_valida{false};
  bool simbolo_a_leer_valido{false};
  bool simbolo_a_escribir_valido{false};
  bool movimiento_valido{false};
  int indice_estado_origen{0};
  int indice_estado_destino{numero_cintas + 1};
  int indice_comienzo_escritura{indice_estado_destino + 1};
  for (int i{0}; i < descripcion_transiciones->size(); ++i) {
    id_estado_origen = descripcion_transiciones->at(i)[indice_estado_origen];
    id_estado_destino = descripcion_transiciones->at(i)[indice_estado_destino];
    // Comprobamos el estado de origen
    for (int j{0}; j < id_estados->size(); ++j) {
      if (id_estado_origen == id_estados->at(j)) {
        transicion_valida = true;
      }
    }
    if (!transicion_valida) {
      throw 3.4;
    }
    transicion_valida = false;
    // Comprobamos el estado destino
    for (int j{0}; j < id_estados->size(); ++j) {
      if (id_estado_destino == id_estados->at(j)) {
        transicion_valida = true;
      }
    }
    if (!transicion_valida) {
      throw 3.5;
    }
    transicion_valida = false;
    for (int j{0}; j < numero_cintas; ++j) {
      simbolo_a_leer = descripcion_transiciones->at(i)[1 + j][0];
      simbolo_a_escribir = descripcion_transiciones->at(i)[indice_comienzo_escritura + 2 * j][0];
      movimiento_a_realizar = descripcion_transiciones->at(i)[indice_comienzo_escritura + 1 + 2 * j][0];
      // Comprobamos el simbolo a leer
      for (int k{0}; k < alfabeto_cinta->size(); ++k) {
        if (simbolo_a_leer == alfabeto_cinta->at(k)) {
          simbolo_a_leer_valido = true;
        }
        if (simbolo_a_escribir == alfabeto_cinta->at(k)) {
          simbolo_a_escribir_valido = true;
        }
      }
      if (!simbolo_a_leer_valido) {
        throw 3.6;
      }
      simbolo_a_leer_valido = false;
      if (!simbolo_a_escribir_valido) {
        throw 3.7;
      }
      simbolo_a_escribir_valido = false;
      if (!CompruebaMovimiento(movimiento_a_realizar)) {
        throw 3.8;
      }
    }
    transicion_valida = false;
  }
}

/**
 * @brief Comrpueba si un movimiento es válido
 * 
 * @param movimiento_a_comprobar
 * @return true/false en función del resultado
 */
bool ComprobadorMaquina::CompruebaMovimiento(char movimiento_a_comprobar) {
  if (movimiento_a_comprobar == 'L') {
    return true;
  }
  if (movimiento_a_comprobar == 'R') {
    return true;
  }
  if (movimiento_a_comprobar == 'S') {
    return true;
  }
  return false;
}