/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 * 
 * @author Diego Hernández Chico
 * @date 6 Oct 2025
 * CORREO: alu0101572062@ull.edu.es
 * @brief Fichero con la declaración de la clase ManejadorEntrada
*/

#include <fstream>
#include <memory>
#include <vector>
#include <sstream>

#ifndef MANEJADOR_ENTRADA_H
#define MANEJADOR_ENTRADA_H

class ManejadorEntrada {
  public:
  ManejadorEntrada();
  void LecturaEntrada(int argc, char* argv[]);
  void ImprimeAtributos();
  std::shared_ptr<std::vector<std::string>> id_estados() const { return id_estados_; }
  std::shared_ptr<std::vector<char>> alfabeto_entrada() const { return alfabeto_entrada_; }
  std::shared_ptr<std::vector<char>> alfabeto_cinta() const { return alfabeto_cinta_; }
  std::string id_estado_inicial() const { return id_estado_inicial_; }
  char simbolo_blanco() const { return simbolo_blanco_; }
  std::shared_ptr<std::vector<std::string>> id_estados_finales() const { return id_estados_finales_; }
  std::shared_ptr<std::vector<std::vector<std::string>>> descripcion_transiciones() const { return descripcion_transiciones_; }
  std::shared_ptr<std::vector<std::string>> cadenas_entrada() const { return cadenas_entrada_; }
  int numero_cintas() const { return numero_cintas_; }
  bool mostrar_traza() const { return mostrar_traza_; }

  private:
  std::shared_ptr<std::vector<std::string>> id_estados_;
  std::shared_ptr<std::vector<char>> alfabeto_entrada_;
  std::shared_ptr<std::vector<char>> alfabeto_cinta_;
  std::string id_estado_inicial_;
  char simbolo_blanco_;
  std::shared_ptr<std::vector<std::string>> id_estados_finales_;
  std::shared_ptr<std::vector<std::vector<std::string>>> descripcion_transiciones_;
  std::shared_ptr<std::vector<std::string>> cadenas_entrada_;
  int numero_cintas_;
  bool mostrar_traza_;
  void LecturaFicheroAutomata(std::string nombre_fichero);
  void LecturaMultipleAlfabeto(std::stringstream& informacion_entrada, int id_alfabeto_a_rellenar);
  void LecturaMultipleEstados(std::stringstream& informacion_entrada, int id_conjunto_a_rellenar);
  void LecturaTransicion(std::stringstream& informacion_entrada);
  void LecturaCadenasEntrada(std::string nombre_fichero_cadenas);
};

#endif