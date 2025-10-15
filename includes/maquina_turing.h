/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 * 
 * @author Diego Hernández Chico
 * @date 10 Oct 2025
 * CORREO: alu0101572062@ull.edu.es
 * @brief Fichero con la declaración de la clase MaquinaTuring
*/

#include "transicion.h"
#include "estado.h"
#include "comprobador_maquina.h"
#include "cinta_infinita.h"

#ifndef MAQUINA_TURING_H
#define MAQUINA_TURING_H

typedef std::shared_ptr<std::vector<CintaInfinita>> Multicinta;

class MaquinaTuring {
  public:
  MaquinaTuring() {  }
  void Configurar(std::shared_ptr<std::vector<std::string>> id_estados, 
      std::shared_ptr<std::vector<char>> alfabeto_entrada, 
      std::shared_ptr<std::vector<char>> alfabeto_cinta, std::string id_estado_inicial,
      char simbolo_blanco, std::shared_ptr<std::vector<std::string>> id_estados_finales, 
      std::shared_ptr<std::vector<std::vector<std::string>>> descripcion_transiciones, int numero_cintas);
  void ImprimeConfiguracion();
  bool ComputaCadena(std::string cadena_a_computar);
  void ImprimeCintas();

  private:
  std::shared_ptr<std::vector<char>> alfabeto_entrada_;
  std::shared_ptr<std::vector<char>> alfabeto_cinta_;
  std::string id_estado_inicial_;
  std::vector<Estado> estados_;
  char simbolo_blanco_;
  bool mostrar_traza_;
  ComprobadorMaquina comprobador_maquina;
  Multicinta cintas_;
  int numero_cintas_;
  void PreparaCintas(std::string cadena_entrada);
  std::shared_ptr<const Estado> BuscaEstado(std::string id_estado_a_buscar);
};

#endif