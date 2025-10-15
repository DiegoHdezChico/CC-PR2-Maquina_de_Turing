/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 * 
 * @author Diego Hernández Chico
 * @date 9 Oct 2025
 * CORREO: alu0101572062@ull.edu.es
 * @brief Fichero con la declaración de la clase ComprobadorMaquina
*/

#include <memory>
#include <vector>
#include <string>

#ifndef COMPROBADOR_MAQUINA_H
#define COMPROBADOR_MAQUINA_H

class ComprobadorMaquina {
  public:
  ComprobadorMaquina() {  }
  void Ejecutar(std::shared_ptr<std::vector<std::string>> id_estados, 
      std::shared_ptr<std::vector<char>> alfabeto_entrada, 
      std::shared_ptr<std::vector<char>> alfabeto_pila, std::string id_estado_inicial,
      char simbolo_blanco, std::shared_ptr<std::vector<std::string>> id_estados_finales, 
      std::shared_ptr<std::vector<std::vector<std::string>>> descripcion_transiciones, int numero_cintas);

  private:
  void CompruebaTransiciones(std::shared_ptr<std::vector<std::string>> id_estados, 
    std::shared_ptr<std::vector<char>> alfabeto_entrada, 
    std::shared_ptr<std::vector<char>> alfabeto_cinta,
    std::shared_ptr<std::vector<std::vector<std::string>>> descripcion_transiciones, int numero_cintas);
  bool CompruebaMovimiento(char movimiento_a_comprobar);
};

#endif