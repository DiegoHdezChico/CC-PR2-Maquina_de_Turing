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
  PreparaCintas(cadena_a_computar);
  std::shared_ptr<const Estado> estado_actual = BuscaEstado(id_estado_inicial_);
  std::shared_ptr<const Transicion> transicion_a_efectuar;
  std::vector<char> simbolos_a_leer;
  while (true) {
    for (int i{0}; i < numero_cintas_; ++i) {
      simbolos_a_leer.push_back(cintas_->at(i).SimboloActual());
    }
    transicion_a_efectuar = estado_actual->TransicionPosible(simbolos_a_leer, numero_cintas_);
    if (transicion_a_efectuar == nullptr) {
      if (estado_actual->es_final()) {
        return true;
      } else {
        return false;
      }
    }
    estado_actual = BuscaEstado(transicion_a_efectuar->id_estado_destino());
    for (int i{0}; i < numero_cintas_; ++i) {
      cintas_->at(i).Escribir(transicion_a_efectuar->simbolo_a_escribir(i));
      cintas_->at(i).MoverCabeza(transicion_a_efectuar->direccion_movimiento(i));
    }
    simbolos_a_leer.clear();
  }
}

/**
 * @brief Prepara las cintas para comenzar la ejecución
 * 
 * @param cadena_entrada con la que inicializar la primera cinta
 */
void MaquinaTuring::PreparaCintas(std::string cadena_entrada) {
  cintas_ = std::make_shared<std::vector<CintaInfinita>>();
  cintas_->push_back(CintaInfinita(simbolo_blanco_, cadena_entrada));
  for (int i{0}; i < numero_cintas_ - 1; ++i) {
    cintas_->push_back(CintaInfinita(simbolo_blanco_));
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
  for (int i{0}; i < cintas_->size(); ++i) {
    cintas_->at(i).ImprimeCinta();
  }
}