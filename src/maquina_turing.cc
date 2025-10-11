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

#include "../includes/maquina_turing.h"

/**
 * @brief Configura la máquina de Turing
 * 
 * @param id_estados
 * @param alfabeto_entrada
 * @param alfabeto_pila
 * @param id_estado_inicial
 * @param id_estados_finales
 * @param descripcion_transiciones
 */
void MaquinaTuring::Configurar(std::shared_ptr<std::vector<std::string>> id_estados, 
      std::shared_ptr<std::vector<char>> alfabeto_entrada, 
      std::shared_ptr<std::vector<char>> alfabeto_cinta, std::string id_estado_inicial,
      char simbolo_blanco, std::shared_ptr<std::vector<std::string>> id_estados_finales, 
      std::shared_ptr<std::vector<std::vector<std::string>>> descripcion_transiciones, int numero_cintas,bool mostrar_traza) {
  try {
    comprobador_maquina.Ejecutar(id_estados, alfabeto_entrada, alfabeto_cinta,
      id_estado_inicial, simbolo_blanco, id_estados_finales, descripcion_transiciones);
  } catch (double error) {
    throw error;
  }
  alfabeto_entrada_ = alfabeto_entrada;
  alfabeto_cinta_ = alfabeto_cinta;
  id_estado_inicial_ = id_estado_inicial;
  simbolo_blanco_ = simbolo_blanco;
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
        transiciones_estado_actual->push_back(std::make_pair(descripcion_transiciones_numeradas[j].first, Transicion(descripcion_transiciones->at(j), numero_cintas)));
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
void MaquinaTuring::ImprimeConfiguracion() {
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
  std::cout << "El alfabeto de cinta es:" << std::endl;
  for (int i{0}; i < alfabeto_cinta_->size(); ++i) {
    std::cout << alfabeto_cinta_->at(i) << " ";
  }
  std::cout << std::endl;
  std::cout << "El estado inicial es: " << id_estado_inicial_ << std::endl;
  std::cout << "El simbolo blanco es: " << simbolo_blanco_ << std::endl;
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
bool MaquinaTuring::ComputaCadena(std::string cadena_a_computar) {
  return 0;
}