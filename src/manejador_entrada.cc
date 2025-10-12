/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 * 
 * @author Diego Hernández Chico
 * @date 6 Oct 2025
 * CORREO: alu0101572062@ull.edu.es
 * @brief Fichero con la definición de funciones de la clase ManejadorEntrada
*/

#include <iostream>

#include "../includes/manejador_entrada.h"

/**
 * @brief Constructor de la clase ManejadorEntrada 
 */
ManejadorEntrada::ManejadorEntrada() {
  id_estados_ = std::make_shared<std::vector<std::string>>();
  alfabeto_entrada_ = std::make_shared<std::vector<char>>();
  alfabeto_cinta_= std::make_shared<std::vector<char>>();
  id_estado_inicial_ = "";
  simbolo_blanco_ = ' ';
  id_estados_finales_ = std::make_shared<std::vector<std::string>>();
  descripcion_transiciones_ = std::make_shared<std::vector<std::vector<std::string>>>();
  cadenas_por_fichero_ = false;
  cadenas_entrada_ = std::make_shared<std::vector<std::string>>();
  numero_cintas_ = 0;
  mostrar_traza_ = false;
}

/**
 * @brief Realiza la lectura de los parámetros desde un fichero dado
 * 
 * @param nombre_fichero desde el cual se extraerá la información
 */
void ManejadorEntrada::LecturaEntrada(int argc, char* argv[]) {
  std::string nombre_fichero_automata{""};
  std::string nombre_fichero_cadenas{""};
  std::string argumento_actual{""};
  for (int i{0}; i < argc; ++i) {
    argumento_actual = argv[i];
    if (argumento_actual == "-a") {
      nombre_fichero_automata = argv[i + 1];
    }
    if (argumento_actual == "-f") {
      nombre_fichero_cadenas = argv[i + 1];
      cadenas_por_fichero_ = true;
    }
    if (argumento_actual == "-t") {
      mostrar_traza_ = true;
    }
  }
  try {
    LecturaFicheroAutomata(nombre_fichero_automata);
  } catch (double error) {
    throw error;
  }
  if (cadenas_por_fichero_ && nombre_fichero_cadenas == "") {
    throw 1.3;
  }
  if (cadenas_por_fichero_) {
    try {
      LecturaCadenasEntrada(nombre_fichero_cadenas);
    } catch (double error) {
      throw error;
    }
  }
}

/**
 * @brief Imprime el valor de los diferentes atributos de la clase
 */
void ManejadorEntrada::ImprimeAtributos() {
  std::cout << "El conjunto de estados es:" << std::endl;
  for (int i{0}; i < id_estados_->size(); ++i) {
    std::cout << id_estados_->at(i) << " ";
  }
  std::cout << std::endl;
  std::cout << "El alfabeto de entrada es:" << std::endl;
  for (int i{0}; i < alfabeto_entrada_->size(); ++i) {
    std::cout << alfabeto_entrada_->at(i) << " ";
  }
  std::cout << std::endl;
  std::cout << "El alfabeto de cinta es:" << std::endl;
  for (int i{0}; i < alfabeto_cinta_->size(); ++i) {
    std::cout << alfabeto_cinta_->at(i) << " ";
  }
  std::cout << std::endl;
  std::cout << "El estado inicial es: " << id_estado_inicial_ << std::endl;
  std::cout << "El simbolo blanco es: " << simbolo_blanco_ << std::endl;
  std::cout << "El conjunto de estados finales es:" << std::endl;
  for (int i{0}; i < id_estados_finales_->size(); ++i) {
    std::cout << id_estados_finales_->at(i) << " ";
  }
  std::cout << "El número de cintas es " << numero_cintas_ << std::endl;
  std::cout << std::endl;
  std::cout << "La función de transición es:" << std::endl;
  for (int i{0}; i < descripcion_transiciones_->size(); ++i) {
    for (int j{0}; j < descripcion_transiciones_->at(i).size(); ++j) {
      std::cout << descripcion_transiciones_->at(i)[j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

/**
 * @brief Lee el fichero de entrada para precargar la configuración del autómata.
 *
 * @param nombre_fichero
 */
void ManejadorEntrada::LecturaFicheroAutomata(std::string nombre_fichero) {
  std::ifstream fichero_entrada{nombre_fichero};
  if (!fichero_entrada.is_open()) {
    throw 1.1;
  }
  std::string linea_de_texto{""};
  std::string palabra_actual{""};
  std::getline(fichero_entrada, linea_de_texto);
  int controlador_entrada{0};
  while (std::getline(fichero_entrada, linea_de_texto)) {
    if (linea_de_texto[0] != '#') {
      std::stringstream informacion_a_extraer(linea_de_texto);
      switch (controlador_entrada) {
          case 0:
            LecturaMultipleEstados(informacion_a_extraer, 1);
            break;
          case 1:
            LecturaMultipleAlfabeto(informacion_a_extraer, 1);
            break;
          case 2:
            LecturaMultipleAlfabeto(informacion_a_extraer, 2);
            break;
          case 3:
            informacion_a_extraer >> id_estado_inicial_;
            break;
          case 4: 
            informacion_a_extraer >> simbolo_blanco_;
            break;
          case 5:
            LecturaMultipleEstados(informacion_a_extraer, 2);
            break;
          case 6:
            informacion_a_extraer >> numero_cintas_;
            if (numero_cintas_ == 0) {
              throw 1.5;
            }
            break;
          default:
            LecturaTransicion(informacion_a_extraer);
      }
      ++controlador_entrada;
    }
  }
}

/**
 * @brief Rellena el vector especificado mediante el parámetro con la información de la línea de entrada. Los códigos de identificación son.
 * 1: Alfabeto de entrada 
 * 2: Alfabeto de pila
 *
 * @param informacion_a_extraer
 * @param id_conjunto_a_rellenar
 */
void ManejadorEntrada::LecturaMultipleAlfabeto(std::stringstream& informacion_entrada, int id_alfabeto_a_rellenar) {
  std::shared_ptr<std::vector<char>> alfabeto_a_rellenar; 
  if (id_alfabeto_a_rellenar == 1) {
    alfabeto_a_rellenar = alfabeto_entrada_;
  } else {
    alfabeto_a_rellenar = alfabeto_cinta_;
  }
  char simbolo_a_anadir{' '};
  while (informacion_entrada >> simbolo_a_anadir) {
    alfabeto_a_rellenar->push_back(simbolo_a_anadir);
  }
}

/**
 * @brief Rellena el vector especificado mediante el parámetro con la información de la línea de entrada. Los códigos de identificación son.
 * 1: Conjunto estados 
 * 2: Conjunto estados finales
 *
 * @param informacion_a_extraer
 * @param id_conjunto_a_rellenar
 */
void ManejadorEntrada::LecturaMultipleEstados(std::stringstream& informacion_entrada, int id_conjunto_a_rellenar) {
  std::shared_ptr<std::vector<std::string>> conjunto_a_rellenar; 
  if (id_conjunto_a_rellenar == 1) {
    conjunto_a_rellenar = id_estados_;
  } else {
    conjunto_a_rellenar = id_estados_finales_;
  }
  std::string simbolo_a_anadir{""};
  while (informacion_entrada >> simbolo_a_anadir) {
    conjunto_a_rellenar->push_back(simbolo_a_anadir);
  }
}

/**
 * @brief Rellena el vector de transiciones con la entrada correspondiente
 * 
 * @param informacion_entrada desde la cual se extraerá la transición
 */
void ManejadorEntrada::LecturaTransicion(std::stringstream& informacion_entrada) {
  std::string informacion_cinta{""};
  std::string id_estado_origen{""};
  std::string id_estado_destino{""};
  std::vector<std::string> nueva_transicion;
  nueva_transicion.clear();
  informacion_entrada >> id_estado_origen;
  nueva_transicion.push_back(id_estado_origen);
  informacion_entrada >> id_estado_destino;
  nueva_transicion.push_back(id_estado_destino);
  int elementos_cinta_leidos{0};
  while (informacion_entrada >> informacion_cinta) {
    nueva_transicion.push_back(informacion_cinta);
  }
  if (nueva_transicion.size() != 2 + 3 * numero_cintas_) {
    throw 1.2;
  }
  descripcion_transiciones_->push_back(nueva_transicion);
}

/**
 * @brief Lee las cadenas de entrada desde el fichero especificado
 * 
 * @param nombre_fichero_cadenas desde el cual las extraeremos
 */
void ManejadorEntrada::LecturaCadenasEntrada(std::string nombre_fichero_cadenas) {
  std::ifstream fichero_cadenas{nombre_fichero_cadenas};
  if (!fichero_cadenas.is_open()) {
    throw 1.4;
  }
  std::string cadena_a_introducir;
  while (std::getline(fichero_cadenas, cadena_a_introducir)) {
    cadenas_entrada_->push_back(cadena_a_introducir);
  }
}