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

#include <iostream>

#include "../includes/manejador_entrada.h"
#include "../includes/maquina_turing.h"

int main(int argc, char* argv[]) {
  ManejadorEntrada mi_manejador;
  mi_manejador.LecturaEntrada(argc, argv);
  MaquinaTuring mi_maquina;
  mi_maquina.Configurar(mi_manejador.id_estados(), 
      mi_manejador.alfabeto_entrada(), mi_manejador.alfabeto_cinta(), 
      mi_manejador.id_estado_inicial(), mi_manejador.simbolo_blanco(), 
      mi_manejador.id_estados_finales(), 
      mi_manejador.descripcion_transiciones(), mi_manejador.numero_cintas(),
      mi_manejador.mostrar_traza());
  mi_maquina.ImprimeConfiguracion();
}