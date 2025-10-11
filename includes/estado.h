/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 * 
 * @author Diego Hernández Chico
 * @date 20 Sep 2025
 * CORREO: alu0101572062@ull.edu.es
 * @brief Fichero con la declaración de la clase Estado
*/

#include <string>
#include <memory>
#include <vector>
#include <optional>

#include "transicion.h"

#ifndef ESTADO_H
#define ESTADO_H

class Estado {
  public:
  Estado(std::string id, bool es_final, std::shared_ptr<std::vector<std::pair<int, Transicion>>> transiciones_estado);
  std::string id() const { return id_; }
  bool es_final() const { return es_final_; }
  void ImprimeTransiciones();
  std::shared_ptr<const Transicion> TransicionPosible(const std::vector<char>& simbolos_lectura, int numero_cintas) const;

  private:
  std::string id_;
  bool es_final_;
  std::shared_ptr<std::vector<std::pair<int, Transicion>>> transiciones_estado_;
};

#endif