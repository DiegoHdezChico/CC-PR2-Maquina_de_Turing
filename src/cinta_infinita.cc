/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 * 
 * @author Diego Hernández Chico
 * @date 8 Oct 2025
 * CORREO: alu0101572062@ull.edu.es
 * @brief Fichero con la definición de los métodos de la clase CintaInfinita
*/

#include <iostream>

#include "../includes/cinta_infinita.h"

/**
 * @brief Constructor de la clase para una cinta vacía
 * 
 * @param simbolo_blanco en la cinta
 */
CintaInfinita::CintaInfinita(char simbolo_blanco) {
  cinta_ = std::make_shared<std::vector<char>>();
  simbolo_blanco_ = simbolo_blanco;
  cabeza_lectura_escritura_ = 1;
  for (int i{0}; i < 3; ++i) {
    cinta_->push_back(simbolo_blanco_);
  }
}

/**
 * @brief Contructor de la clase para cuando se quiere inicializar con una cadena
 * 
 * @param simbolo_blanco en al cinta
 * @param cadena_a_introducir en la cinta
 */
CintaInfinita::CintaInfinita(char simbolo_blanco, std::string cadena_a_introducir) {
  cinta_ = std::make_shared<std::vector<char>>();
  simbolo_blanco_ = simbolo_blanco;
  cabeza_lectura_escritura_ = 1;
  cinta_->push_back(simbolo_blanco);
  for (int i{0}; i < cadena_a_introducir.size(); ++i) {
    cinta_->push_back(cadena_a_introducir[i]);
  }
  cinta_->push_back(simbolo_blanco_);
}

/**
 * @brief Realiza el movimiento de la cabeza de lectura/escritura
 */
void CintaInfinita::MoverCabeza(char direccion) {
  if ((cabeza_lectura_escritura_ == 0 && direccion == 'L') || 
      (cabeza_lectura_escritura_ == cinta_->size() -1 && direccion == 'R')) {
    AmpliarRango();
  } else if (direccion == 'L') {
    --cabeza_lectura_escritura_;
  } else if (direccion == 'R') {
    ++cabeza_lectura_escritura_;
  }
}

/**
 * @brief Amplía el rango de la cinta en función de la zona que sea necesaria
 */
void CintaInfinita::AmpliarRango() {
  std::shared_ptr<std::vector<char>> nueva_cinta = std::make_shared<std::vector<char>>();
  if (cabeza_lectura_escritura_ == 0) {
    nueva_cinta->push_back(simbolo_blanco_);
  }
  for (int i{0}; i < cinta_->size(); ++i) {
    nueva_cinta->push_back(cinta_->at(i));
  }
  if (cabeza_lectura_escritura_ == cinta_->size() - 1) {
    nueva_cinta->push_back(simbolo_blanco_);
    ++cabeza_lectura_escritura_;
  }
  cinta_ = nueva_cinta;
}

/**
 * @brief Escribe el caracter pasado como parámetro en la posición que indica 
 * el cabezal de la cinta
 * 
 * @param simbolo_a_escribir en la cinta
 */
void CintaInfinita::Escribir(char simbolo_a_escribir) {
  cinta_->at(cabeza_lectura_escritura_) = simbolo_a_escribir;
}

/**
 * @brief Imprime la cinta en su estado actual
 */
void CintaInfinita::ImprimeCinta() {
  for (int i{0}; i < cinta_->size(); ++i) {
    if (cabeza_lectura_escritura_ == i) {
      std::cout << "[";
    }
    std::cout << cinta_->at(i);
    if (cabeza_lectura_escritura_ == i) {
      std::cout << "]";
    }
  }
  std::cout << std::endl;
}