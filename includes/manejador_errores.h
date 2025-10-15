/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 * 
 * @author Diego Hernández Chico
 * @date 12 Oct 2025
 * CORREO: alu0101572062@ull.edu.es
 * @brief Fichero con la declaración de la clase ManejadorErrores
*/

#ifndef MANEJADOR_ERRORES_H
#define MANEJADOR_ERRORES_H

class ManejadorErrores {
  public:
  ManejadorErrores(): codigo_general_(0), codigo_especifico_(0) {  }
  void Alertar(double codigo_error);

  private:
  int codigo_general_;
  int codigo_especifico_;
  void AlertaFicheroLectura();
  void AlertaMaquina();
  void AlertaTransiciones();
};

#endif