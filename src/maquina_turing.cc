/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 * 
 * @author Diego Hernández Chico
 * @date 10 Oct 2025
 * CORREO: alu0101572062@ull.edu.es
 * @brief Fichero con la definición de los métodos de la clase MaquinaTuring
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
      std::shared_ptr<std::vector<std::vector<std::string>>> descripcion_transiciones, int numero_cintas) {
  try {
    comprobador_maquina.Ejecutar(id_estados, alfabeto_entrada, alfabeto_cinta,
      id_estado_inicial, simbolo_blanco, id_estados_finales, descripcion_transiciones, numero_cintas);
  } catch (double error) {
    throw error;
  }
  alfabeto_entrada_ = alfabeto_entrada;
  alfabeto_cinta_ = alfabeto_cinta;
  id_estado_inicial_ = id_estado_inicial;
  simbolo_blanco_ = simbolo_blanco;
  numero_cintas_ = numero_cintas;
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
 * @brief Imprime la configuración actual de la máquina
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
  std::cout << "El número de cintas es: " << numero_cintas_ << std::endl;
  std::cout << "Las transiciones son:" << std::endl;
  for (int i{0}; i < estados_.size(); ++i) {
    estados_[i].ImprimeTransiciones();
  }
}

/**
 * @brief Computa una cadena dada como argumento para determinar si pertenece
 * al lenguaje que reconoce la máquina. Establece el inicio de la recursividad
 * 
 * @param cadena_a_computar
 * @return true/false en función de si pertenece al lenguaje o no
 */
bool MaquinaTuring::ComputaCadena(std::string cadena_a_computar) {
  cintas_.PreparaCintas(cadena_a_computar, simbolo_blanco_, numero_cintas_);
  std::shared_ptr<const Estado> estado_actual = BuscaEstado(id_estado_inicial_);
  std::shared_ptr<const Transicion> transicion_a_efectuar;
  std::shared_ptr<std::vector<char>> simbolos_a_leer;
  std::shared_ptr<std::vector<char>> simbolos_a_escribir;
  std::shared_ptr<std::vector<char>> movimientos_a_realizar;
  while (true) {
    simbolos_a_leer = cintas_.SimbolosActuales();
    transicion_a_efectuar = estado_actual->TransicionPosible(simbolos_a_leer, numero_cintas_);
    if (transicion_a_efectuar == nullptr) {
      if (estado_actual->es_final()) {
        return true;
      } else {
        return false;
      }
    }
    estado_actual = BuscaEstado(transicion_a_efectuar->id_estado_destino());
    simbolos_a_escribir = std::make_shared<std::vector<char>>();
    movimientos_a_realizar = std::make_shared<std::vector<char>>();
    for (int i{0}; i < numero_cintas_; ++i) {
      simbolos_a_escribir->push_back(transicion_a_efectuar->simbolo_a_escribir(i));
      movimientos_a_realizar->push_back(transicion_a_efectuar->direccion_movimiento(i));
    }
    cintas_.Escribir(simbolos_a_escribir);
    cintas_.Mover(movimientos_a_realizar);
  }
}

/**
 * @brief Retorna el estado dado su identificador
 * 
 * @param id_estado_a_buscar
 * @return estado al que pertenece el identificador pasado como parámetro
 */
std::shared_ptr<const Estado> MaquinaTuring::BuscaEstado(std::string id_estado_a_buscar) {
  for (int i{0}; i < estados_.size(); ++i) {
    if (estados_[i].id() == id_estado_a_buscar) {
      return std::make_shared<const Estado>(estados_[i]);
    }
  }
  return nullptr;
}

/**
 * @brief Imprime las cintas de la máquina en su estado actual
 */
void MaquinaTuring::ImprimeCintas() {
  cintas_.ImprimeCintas();
}