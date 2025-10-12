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
#include "../includes/manejador_errores.h"

int main(int argc, char* argv[]) {
  ManejadorEntrada mi_manejador_entrada;
  ManejadorErrores mi_manejador_errores;
  try {
    mi_manejador_entrada.LecturaEntrada(argc, argv);
  } catch (double error) {
    mi_manejador_errores.Alertar(error);
    return 1;
  }
  MaquinaTuring mi_maquina;
  try {
    mi_maquina.Configurar(mi_manejador_entrada.id_estados(), 
        mi_manejador_entrada.alfabeto_entrada(), 
        mi_manejador_entrada.alfabeto_cinta(), 
        mi_manejador_entrada.id_estado_inicial(), 
        mi_manejador_entrada.simbolo_blanco(), 
        mi_manejador_entrada.id_estados_finales(), 
        mi_manejador_entrada.descripcion_transiciones(), 
        mi_manejador_entrada.numero_cintas(),
        mi_manejador_entrada.mostrar_traza());
  } catch (double error) {
    mi_manejador_errores.Alertar(error);
    return 1;
  }
  mi_maquina.ImprimeConfiguracion();
}