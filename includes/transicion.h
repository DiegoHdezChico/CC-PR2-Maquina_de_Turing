/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 * 
 * @author Diego Hernández Chico
 * @date 20 Sep 2025
 * CORREO: alu0101572062@ull.edu.es
 * @brief Fichero con la declaración de la clase Transicion
*/

#include <memory>
#include <vector>
#include <string>

#include "transicion_cinta.h"

#ifndef TRANSICION_H
#define TRANSICION_H

class Transicion {
  public:
  Transicion(const std::vector<std::string>& descripcion_transicion, int numero_cintas);
  std::string id_estado_origen() const { return id_estado_origen_; }
  std::string id_estado_destino() const { return id_estado_destino_; };
  void ImprimeTransicion() const;
  char simbolo_a_leer(int cinta_elegida) const { return transiciones_cinta_[cinta_elegida].simbolo_a_leer(); }
  char simbolo_a_escribir(int cinta_elegida) const { return transiciones_cinta_[cinta_elegida].simbolo_a_escribir(); }

  private:
  std::string id_estado_origen_;
  std::string id_estado_destino_;
  std::vector<TransicionCinta> transiciones_cinta_;
};

#endif