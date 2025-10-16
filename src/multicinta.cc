/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 * 
 * @author Diego Hernández Chico
 * @date 16 Oct 2025
 * CORREO: alu0101572062@ull.edu.es
 * @brief Fichero con la definición de los métodos de la clase Multicinta
*/

#include "../includes/multicinta.h"

/**
 * @brief Prepara las cintas para comenzar la ejecución
 * 
 * @param cadena_entrada con la que inicializar la primera cinta
 */
void Multicinta::PreparaCintas(std::string cadena_entrada, char simbolo_blanco, int numero_cintas) {
  cintas_ = std::make_shared<std::vector<CintaInfinita>>();
  cintas_->push_back(CintaInfinita(simbolo_blanco, cadena_entrada));
  for (int i{0}; i < numero_cintas - 1; ++i) {
    cintas_->push_back(CintaInfinita(simbolo_blanco));
  }
}

/**
 * @brief Imprime las cintas de la máquina en su estado actual
 */
void Multicinta::ImprimeCintas() {
  for (int i{0}; i < cintas_->size(); ++i) {
    cintas_->at(i).ImprimeCinta();
  }
}

/**
 * @brief Retorna los símbolos sobre los que se encuentran las cabezas de 
 * lectura/escritura de cada una de las cintas
 */
std::shared_ptr<std::vector<char>> Multicinta::SimbolosActuales() {
  std::shared_ptr<std::vector<char>> simbolos_a_leer = std::make_shared<std::vector<char>>();
  for (int i{0}; i < cintas_->size(); ++i) {
    simbolos_a_leer->push_back(cintas_->at(i).SimboloActual());
  }
  return simbolos_a_leer;
}

/**
 * @brief Escribe en cada cinta el simbolo correspondiente
 * 
 * @param simbolos_a_escribir. Conjunto de símbolos, indexados en función de la 
 * cinta en la que se debe insertar.
 */
void Multicinta::Escribir(std::shared_ptr<std::vector<char>> simbolos_a_escribir) {
  for (int i{0}; i < cintas_->size(); ++i) {
    cintas_->at(i).Escribir(simbolos_a_escribir->at(i));
  }
}

/**
 * @brief Realiza para cada cinta el moviminto correspondiente
 * 
 * @param movimientos_a_realizar. Conjunto de movimientos, indexados en función 
 * de la cinta en la que se debe insertar.
 */
void Multicinta::Mover(std::shared_ptr<std::vector<char>> movimientos_a_realizar) {
  for (int i{0}; i < cintas_->size(); ++i) {
    cintas_->at(i).MoverCabeza(movimientos_a_realizar->at(i));
  }
}