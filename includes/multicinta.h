/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 * 
 * @author Diego Hernández Chico
 * @date 16 Oct 2025
 * CORREO: alu0101572062@ull.edu.es
 * @brief Fichero con la declaración de la clase Multicinta
*/

#include "cinta_infinita.h"

#ifndef MULTICINTA_H
#define MULTICINTA_H

class Multicinta {
  public:
  Multicinta() {  }
  void PreparaCintas(std::string cadena_entrada, char simbolo_blanco, int numero_cintas);
  void ImprimeCintas();
  std::shared_ptr<std::vector<char>> SimbolosActuales();
  void Escribir(std::shared_ptr<std::vector<char>> simbolos_a_escribir);
  void Mover(std::shared_ptr<std::vector<char>> movimientos_a_realizar);

  private:
  std::shared_ptr<std::vector<CintaInfinita>> cintas_;
};

#endif