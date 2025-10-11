/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 * 
 * @author Diego Hernández Chico
 * @date 11 Oct 2025
 * CORREO: alu0101572062@ull.edu.es
 * @brief Fichero con la declaración de la clase TransicionCinta
*/

#ifndef TRANSICION_CINTA_H
#define TRANSICION_CINTA_H

class TransicionCinta {
  public:
  TransicionCinta(char simbolo_a_leer, char simbolo_a_escribir, char direccion_movimiento): simbolo_a_leer_(simbolo_a_leer), simbolo_a_escribir_(simbolo_a_escribir), direccion_movimiento_(direccion_movimiento) {  }
  char simbolo_a_leer() const { return simbolo_a_leer_; }
  char simbolo_a_escribir() const { return simbolo_a_escribir_; }
  char direccion_movimiento() const { return direccion_movimiento_; }
  void ImprimeTransicionCinta() const;
  private:
  char simbolo_a_leer_;
  char simbolo_a_escribir_;
  char direccion_movimiento_;
};

#endif