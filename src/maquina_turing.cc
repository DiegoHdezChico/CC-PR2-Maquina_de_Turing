/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 * 
 * @author Diego Hernández Chico
 * @date 19 Sep 2025
 * CORREO: alu0101572062@ull.edu.es
 * @brief Fichero con la definición de los métodos de la clase AutomataPilaFinal
*/

#include <iostream>
#include <algorithm>

#include "../includes/automata_pila_final.h"

/**
 * @brief Configura el autómata de pila 
 * 
 * @param id_estados
 * @param alfabeto_entrada
 * @param alfabeto_pila
 * @param id_estado_inicial
 * @param id_estados_finales
 * @param descripcion_transiciones
 */
void AutomataPilaFinal::Configurar(std::shared_ptr<std::vector<std::string>> id_estados, 
      std::shared_ptr<std::vector<char>> alfabeto_entrada, 
      std::shared_ptr<std::vector<char>> alfabeto_pila, std::string id_estado_inicial,
      char simbolo_inicial_pila, std::shared_ptr<std::vector<std::string>> id_estados_finales, 
      std::shared_ptr<std::vector<std::vector<std::string>>> descripcion_transiciones,
      bool mostrar_traza) {
  try {
    comprobador_automata_.Ejecutar(id_estados, alfabeto_entrada, alfabeto_pila,
      id_estado_inicial, simbolo_inicial_pila, id_estados_finales, descripcion_transiciones);
  } catch (double error) {
    throw error;
  }
  alfabeto_entrada_ = alfabeto_entrada;
  alfabeto_pila_ = alfabeto_pila;
  id_estado_inicial_ = id_estado_inicial;
  simbolo_inicial_pila_ = simbolo_inicial_pila;
  mostrar_traza_ = mostrar_traza;
  std::vector<std::pair<int, std::vector<std::string>>> descripcion_transiciones_numeradas;
  for (int i{0}; i < descripcion_transiciones->size(); ++i) {
    descripcion_transiciones_numeradas.push_back(std::make_pair(i + 1, descripcion_transiciones->at(i)));
  }
  std::shared_ptr<std::vector<std::pair<int, Transicion>>> transiciones_estado_actual;
  int numero_transicion{1};
  bool es_final{false};
  std::string estado_actual{""};
  for (int i{0}; i < id_estados->size(); ++i) {
    estado_actual = id_estados->at(i);
    transiciones_estado_actual = std::make_shared<std::vector<std::pair<int, Transicion>>>();
    for (int j{0}; j < descripcion_transiciones_numeradas.size(); ++j) {
      if (estado_actual == descripcion_transiciones_numeradas[j].second[0]) {
        transiciones_estado_actual->push_back(std::make_pair(descripcion_transiciones_numeradas[j].first, Transicion(descripcion_transiciones->at(j))));
        ++numero_transicion;
      }
    }
    for (int j{0}; j < id_estados_finales->size(); ++j) {
      if (estado_actual == id_estados_finales->at(j)) {
        es_final = true;
      }
    }
    estados_.push_back(Estado(estado_actual, es_final, transiciones_estado_actual));
    es_final = false;
  }
}

/**
 * @brief Imprime la configuración actual del autómata
 */
void AutomataPilaFinal::ImprimeConfiguracion() {
  std::cout << "El conjunto de estados es:" << std::endl;
  for (int i{0}; i < estados_.size(); ++i) {
    std::cout << estados_[i].id() << " ";
  }
  std::cout << std::endl;
  std::cout << "El alfabeto de entrada es:" << std::endl;
  for (int i{0}; i < alfabeto_entrada_->size(); ++i) {
    std::cout << alfabeto_entrada_->at(i) << " ";
  }
  std::cout << std::endl;
  std::cout << "El alfabeto de pila es:" << std::endl;
  for (int i{0}; i < alfabeto_pila_->size(); ++i) {
    std::cout << alfabeto_pila_->at(i) << " ";
  }
  std::cout << std::endl;
  std::cout << "El estado inicial es: " << id_estado_inicial_ << std::endl;
  std::cout << "El simbolo inicial de la pila es: " << simbolo_inicial_pila_ << std::endl;
  std::cout << "El conjunto de estados finales es:" << std::endl;
  for (int i{0}; i < estados_.size(); ++i) {
    if (estados_[i].es_final()) {
      std::cout << estados_[i].id() << " ";
    }
  }
  std::cout << std::endl;
  std::cout << "Las transiciones son:" << std::endl;
  for (int i{0}; i < estados_.size(); ++i) {
    estados_[i].ImprimeTransiciones();
  }
}

/**
 * @brief Computa una cadena dada como argumento para determinar si pertenece
 * al lenguaje que reconoce el autómata. Establece el inicio de la recursividad
 * 
 * @param cadena_a_computar
 * @return true/false en función de si pertenece al lenguaje o no
 */
bool AutomataPilaFinal::ComputaCadena(std::string cadena_a_computar) {
  cadena_a_computar.erase(std::remove(cadena_a_computar.begin(), cadena_a_computar.end(), ' '), cadena_a_computar.end());
  std::string inicio_pila{simbolo_inicial_pila_};
  Pila pila_automata;
  pila_automata.Push(inicio_pila);
  int posicion_estado_arranque{0};
  for (int i{0}; i < estados_.size(); ++i) {
    if (id_estado_inicial_ == estados_[i].id()) {
      posicion_estado_arranque = i;
    }
  }
  int contador {0};
  return Computar(cadena_a_computar, 0, posicion_estado_arranque, pila_automata, "", contador);
}

/**
 * @brief Función recursiva para comprobar si una cadena pertenece 
 * al lenguaje que reconoce un autómata.
 * 
 * @param cadena_a_computar
 * @param posicion_caracter_actual desde el cual determinaremos el cambio de estado
 * @param posicion_estado_actual dentro del vector de estados que es miembro de la clase
 */
bool AutomataPilaFinal::Computar(std::string cadena_a_computar, 
      int posicion_caracter_actual, int posicion_estado_actual, 
      Pila pila_automata, std::string simbolos_pila_a_introducir,
      int& contador) {
  ++contador;
  if (contador > 10000) {
    throw 4.0;
  }
  char caracter_actual_entrada = cadena_a_computar[posicion_caracter_actual];
  if (posicion_caracter_actual == cadena_a_computar.size()) {
    caracter_actual_entrada = '.';
  }
  if (simbolos_pila_a_introducir != ".") {
    pila_automata.Push(simbolos_pila_a_introducir);
  }
  if (pila_automata.Empty()) {
    return false;
  }
  char tope_de_pila = pila_automata.Top();
  pila_automata.Pop();
  std::shared_ptr<const std::vector<std::pair<int, Transicion>>> transiciones_posibles = 
      estados_[posicion_estado_actual].TransicionesPosibles(caracter_actual_entrada, 
      tope_de_pila);
  if (caracter_actual_entrada == '.' && transiciones_posibles->empty()) {
    if (mostrar_traza_) {
      std::cout << std::endl;
      std::cout << "El estado actual es " << estados_[posicion_estado_actual].id() << std::endl;
      std::cout << "La cadena es " << std::endl;
      std::cout << "El estado de la pila es " << tope_de_pila;
      pila_automata.ImprimePila();
      std::cout << std::endl << "No hay transiciones disponibles." << std::endl;
      std::cout << std::endl << "------------------------------------------------------" << std::endl;
    }
    if (estados_[posicion_estado_actual].es_final()) {
      return true;
    } else {
      return false;
    }
  }
  bool cadena_pertenece{false};
  int posicion_estado_siguiente{0};
  int posicion_caracter_siguiente{0};
  for (int i{0}; i < transiciones_posibles->size(); ++i) {
    posicion_caracter_siguiente = posicion_caracter_actual;
    for (int j{0}; j < estados_.size(); ++j) {
      if (transiciones_posibles->at(i).second.id_estado_destino() == estados_[j].id()) {
        posicion_estado_siguiente = j;
      }
    }
    if (transiciones_posibles->at(i).second.simbolo_alfabeto_a_consumir() != '.') {
      ++posicion_caracter_siguiente;
    }
    if (mostrar_traza_) {
      std::cout << std::endl;
      std::cout << "El estado actual es " << estados_[posicion_estado_actual].id() << std::endl;
      std::cout << "La cadena es ";
      for (int j{posicion_caracter_actual}; j < cadena_a_computar.size(); ++j) {
        std::cout << cadena_a_computar[j];
      }
      std::cout << std::endl;
      std::cout << "El estado de la pila es " << tope_de_pila;
      pila_automata.ImprimePila();
      std::cout << std::endl << "Las transiciones disponibles son ";
      for (int j{0}; j < transiciones_posibles->size(); ++j) {
        std::cout << transiciones_posibles->at(j).first << " ";
      }
      std::cout << std::endl << "Ejecutamos la transicion " << transiciones_posibles->at(i).first << std::endl;
      std::cout << std::endl << "------------------------------------------------------" << std::endl;
    }
    cadena_pertenece = Computar(cadena_a_computar, posicion_caracter_siguiente, 
        posicion_estado_siguiente, pila_automata, 
        transiciones_posibles->at(i).second.simbolos_pila_a_introducir(), 
        contador);
    if (cadena_pertenece) {
      return true;
    }
  }
  if (mostrar_traza_) {
    std::cout << std::endl;
    std::cout << "El estado actual es " << estados_[posicion_estado_actual].id() << std::endl;
    std::cout << "La cadena es ";
    for (int j{posicion_caracter_actual}; j < cadena_a_computar.size(); ++j) {
      std::cout << cadena_a_computar[j];
    }
    std::cout << std::endl;
    std::cout << "El estado de la pila es " << tope_de_pila;
    pila_automata.ImprimePila();
    std::cout << std::endl << "No existen más transiciones que probar. Regresando..." << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;
  }
  return false; 
}