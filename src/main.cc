/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 * 
 * @author Diego Hernández Chico
 * @date 6 Oct 2025
 * CORREO: alu0101572062@ull.edu.es
 * @brief Programa para simular una Máquina de Turing
*/

#include "../includes/manejador_entrada.h"

int main(int argc, char* argv[]) {
  ManejadorEntrada mi_manejador;
  mi_manejador.LecturaEntrada(argc, argv);
  mi_manejador.ImprimeAtributos();
}