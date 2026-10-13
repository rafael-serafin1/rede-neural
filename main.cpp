#include "./src/logic_brain.hpp"
#include <exception>
#include <sstream>
#include <string>
#include <vector>

int* converter(const std::string& texto) {
    std::vector<int> resultado;
    std::stringstream ss(texto);

    char c;
    int numero;

    while (ss >> c) {
        if (c >= '0' && c <= '9' || c == '-') {
            ss.putback(c);
            if (ss >> numero)
                resultado.push_back(numero);
        }
    }

    int* resultado_array = new int[resultado.size()];

    for (register int i = 0; i < resultado.size(); ++i)
        resultado_array[i] = resultado[i];

    return resultado_array;
}

int main(int argc, char** argv) {
    if (argc <= 2) {
        std::printf("faltam argumentos!");
        return 1;
    }

    int* ordem_treinamento = 
        (std::string(argv[1]) != "none") 
            ? converter(argv[1])
            : new int[4]{0, 1, 2, 3};
            
    int epochs = std::stoi(argv[2]);
    
    logic_brain nn = logic_brain(ordem_treinamento, epochs);

    try {
        nn.inicializar();
        nn.treinar();
        //bit resultado = nn.prever(logic_gates::AND, 1, 1);
        bit resultado = nn.arena(logic_gates::AND, 1, 1);

        std::printf("Resultado: %d\n", resultado.value);
    } catch (const std::invalid_argument& ex) {
        std::printf("%s\n", ex.what());
    } catch (const std::exception& ex) {
        std::printf("%s\n", ex.what());
    }

    delete ordem_treinamento;

    printf("!Programa finalizado com sucesso!");
    return 0;
}