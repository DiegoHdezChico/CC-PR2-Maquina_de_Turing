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

#ifndef TRANSICION_H
#define TRANSICION_H

class Transicion {
  public:
  Transicion(const std::vector<std::string>& descripcion_transicion);
  std::string id_estado_origen() const { return id_estado_origen_; }
  char simbolo_alfabeto_a_consumir() const { return simbolo_alfabeto_a_consumir_; }
  char simbolo_pila_a_consumir() const { return simbolo_pila_a_consumir_; };
  std::string id_estado_destino() const { return id_estado_destino_; };
  std::string simbolos_pila_a_introducir() const { return simbolos_pila_a_introducir_; }
  void ImprimeTransicion() const;
  
  private:
  std::string id_estado_origen_;
  char simbolo_alfabeto_a_consumir_;
  char simbolo_pila_a_consumir_;
  std::string id_estado_destino_;
  std::string simbolos_pila_a_introducir_;
};

#endif