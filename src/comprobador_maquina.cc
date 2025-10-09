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

#include "../includes/comprobador_maquina.h"

/**
 * @brief Comprueba que la configuración del autómata sea correcta
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
      std::shared_ptr<std::vector<std::vector<std::string>>> descripcion_transiciones) {
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
    throw 2.8;
  }
  CompruebaTransiciones(id_estados, alfabeto_entrada, alfabeto_cinta, 
        id_estado_inicial, simbolo_blanco, id_estados_finales, 
        descripcion_transiciones);
}

/**
 * @brief Comprueba que las transiciones del autómata sean correctas
 * 
 * @param id_estados
 * @param alfabeto_entrada
 * @param alfabeto_cinta
 * @param id_estado_inicial
 * @param simbolo_inicial_pila
 * @param id_estados_finales
 * @param descripcion_transiciones que queremos comprobar
 */
void ComprobadorMaquina::CompruebaTransiciones(std::shared_ptr<std::vector<std::string>> id_estados, 
      std::shared_ptr<std::vector<char>> alfabeto_entrada, 
      std::shared_ptr<std::vector<char>> alfabeto_pila, std::string id_estado_inicial,
      char simbolo_inicial_pila, std::shared_ptr<std::vector<std::string>> id_estados_finales, 
      std::shared_ptr<std::vector<std::vector<std::string>>> descripcion_transiciones) {
  std::string id_estado_origen{""};
  char simbolo_alfabeto_a_consumir{' '};
  char simbolo_pila_a_consumir{' '};
  std::string id_estado_destino{""};
  std::string simbolos_pila_a_introducir{""};
  bool transicion_valida{false};
  for (int i{0}; i < descripcion_transiciones->size(); ++i) {
    id_estado_origen = descripcion_transiciones->at(i)[0];
    simbolo_alfabeto_a_consumir = descripcion_transiciones->at(i)[1][0];
    simbolo_pila_a_consumir = descripcion_transiciones->at(i)[2][0];
    id_estado_destino = descripcion_transiciones->at(i)[3];
    simbolos_pila_a_introducir = descripcion_transiciones->at(i)[4];
    // Comprobamos el estado de origen
    for (int i{0}; i < id_estados->size(); ++i) {
      if (id_estado_origen == id_estados->at(i)) {
        transicion_valida = true;
      }
    }
    if (!transicion_valida) {
      throw 3.3;
    }
    transicion_valida = false;
    // Comprobamos el estado destino
    for (int i{0}; i < id_estados->size(); ++i) {
      if (id_estado_destino == id_estados->at(i)) {
        transicion_valida = true;
      }
    }
    if (!transicion_valida) {
      throw 3.4;
    }
    transicion_valida = false;
    // Comprobamos el simbolo de entrada a consumir
    for (int i{0}; i < alfabeto_entrada->size(); ++i) {
      if (simbolo_alfabeto_a_consumir == alfabeto_entrada->at(i) || simbolo_alfabeto_a_consumir == '.') {
        transicion_valida = true;
      }
    }
    if (!transicion_valida) {
      throw 3.5;
    }
    transicion_valida = false;
    // Comprobamos el simbolo de pila a consumir
    for (int i{0}; i < alfabeto_pila->size(); ++i) {
      if (simbolo_pila_a_consumir == alfabeto_pila->at(i)) {
        transicion_valida = true;
      }
      if (simbolo_pila_a_consumir == '.') {
        transicion_valida = false;
      }
    }
    if (!transicion_valida) {
      throw 3.6;
    }
    transicion_valida = false;
    // Comprobamos los simbolos de pila a introducir
    for (int i{0}; i < simbolos_pila_a_introducir.size(); ++i) {
      for (int j{0}; j < alfabeto_pila->size(); ++j) {
        if (simbolos_pila_a_introducir[i] == alfabeto_pila->at(j) || simbolos_pila_a_introducir[i] == '.') {
          transicion_valida = true;
        }      
      }
      if (!transicion_valida) {
        throw 3.7;
      }
      transicion_valida = false;
    }
  }
}