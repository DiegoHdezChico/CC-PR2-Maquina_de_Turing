# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Complejidad Computacional
# 
# @author Diego Hernández Chico
# @date 6 Oct 2025
# CORREO: alu0101572062@ull.edu.es
# @brief Makefile del programa simulador_maquina_turing
#

CXX = g++
CXXFLAGS = -g -std=c++17 -fsanitize=address

.PHONY: all clean 

all: simulador_maquina_turing

simulador_maquina_turing: src/*.cc
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f simulador_maquina_turing