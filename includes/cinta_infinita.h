/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 * 
 * @author Diego Hernández Chico
 * @date 8 Oct 2025
 * CORREO: alu0101572062@ull.edu.es
 * @brief Fichero con la declaración de la clase CintaInfinita
*/

#include <vector>
#include <string>
#include <memory>

#ifndef CINTA_INFINITA_H
#define CINTA_INFINITA_H

class CintaInfinita {
  public:
  CintaInfinita(char simbolo_blanco): simbolo_blanco_(simbolo_blanco), cabeza_lectura_escritura_(0) { cinta_->clear(); }
  CintaInfinita(char simbolo_blanco, std::string cadena_a_introducir);
  char SimboloActual() const { return cinta_->at(cabeza_lectura_escritura_); }
  void MoverCabeza(char direccion);
  void Escribir(char simbolo_a_escribir);

  private:
  std::shared_ptr<std::vector<char>> cinta_;
  int cabeza_lectura_escritura_;
  char simbolo_blanco_;
  void AmpliarRango();
};

#endif