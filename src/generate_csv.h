#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <vector> 
#include <string> 

struct Datos { 
    std::string campo1; 
    std::string campo2; 
    std::string campo3; 
}; 

std::vector<Datos> loadDataFromCSV(const std::string& filename) { 
    std::vector<Datos> datos; 
    std::ifstream file(filename); 

    if (!file.is_open()) { 
        std::cerr << "Error al abrir el archivo: " << filename << std::endl; 
        return datos; 
    } 

    std::string line; 
    while (std::getline(file, line)) { 
        std::stringstream ss(line); 
        std::string campo; 
        Datos dato; 
        std::getline(ss, dato.campo1, ','); 
        std::getline(ss, dato.campo2, ','); 
        std::getline(ss, dato.campo3, ','); 

        datos.push_back(dato); 

    } 

    file.close(); 
    return datos; 

} 


int main() { 
    std::string nombreArchivo = "datos.csv"; 
    std::vector<Datos> datos = loadDataFromCSV(nombreArchivo); 

    for (const auto& dato : datos) { 
        std::cout << "Campo 1: " << dato.campo1 << std::endl; 
        std::cout << "Campo 2: " << dato.campo2 << std::endl; 
        std::cout << "Campo 3: " << dato.campo3 << std::endl; 
        std::cout << "------------------------" << std::endl; 

    } 
    return 0; 
} 