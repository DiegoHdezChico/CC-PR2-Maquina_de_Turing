/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 * 
 * @author Diego Hernández Chico
 * @date 11 Oct 2025
 * CORREO: alu0101572062@ull.edu.es
 * @brief Fichero con la definición de los métodos de la clase TransicionCinta
*/

#include <iostream>

#include "../includes/transicion_cinta.h"

/**
 * @brief Imprime los valores de la trancision relativos a la cinta a la que 
 * está asignada
 */
void TransicionCinta::ImprimeTransicionCinta() const {
  std::cout << "(" << simbolo_a_leer_ << ", " << simbolo_a_escribir_ << ", " << direccion_movimiento_ << ")" << std::endl;
}