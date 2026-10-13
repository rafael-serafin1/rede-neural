#pragma once

#include "neural_network.hpp"
#include <vector>
#include <memory>
#include <stdexcept>

class logic_brain {
private:
    std::vector<std::unique_ptr<neural_network>> brain;
    int* training_set_order;
    int epochs;

protected:
    double inputs[NUMERO_TENTATIVAS_TREINO][NUMERO_ENTRADAS] = {
        {0.0f, 0.0f}, {0.0f, 1.0f}, 
        {1.0f, 0.0f}, {1.0f, 1.0f}
    };

    // and
    double outputs_and[NUMERO_TENTATIVAS_TREINO][NUMERO_SAIDAS] = {
        {0.0f}, {0.0f}, {0.0f}, {1.0f}
    };

    // or
    double outputs_or[NUMERO_TENTATIVAS_TREINO][NUMERO_SAIDAS] = {
        {0.0f}, {1.0f}, {1.0f}, {1.0f}
    };

    // xor
    double outputs_xor[NUMERO_TENTATIVAS_TREINO][NUMERO_SAIDAS] = {
        {0.0f}, {1.0f}, {1.0f}, {0.0f}
    };

    // nand
    double outputs_nand[NUMERO_TENTATIVAS_TREINO][NUMERO_SAIDAS] = {
        {1.0f}, {1.0f}, {1.0f}, {0.0f}
    };

    // nor
    double outputs_nor[NUMERO_TENTATIVAS_TREINO][NUMERO_SAIDAS] = {
        {1.0f}, {0.0f}, {0.0f}, {0.0f}
    };

    // nxor
    double outputs_nxor[NUMERO_TENTATIVAS_TREINO][NUMERO_SAIDAS] = {
        {1.0f}, {0.0f}, {0.0f}, {1.0f}
    };

public:
    logic_brain(int* TrainingSetOrder, int Epochs): 
        training_set_order(TrainingSetOrder), epochs(Epochs) { }

    void inicializar() {
        brain.push_back(std::make_unique<neural_network>(inputs, outputs_and,   logic_gates::AND));
        brain.push_back(std::make_unique<neural_network>(inputs, outputs_or,    logic_gates::OR));
        brain.push_back(std::make_unique<neural_network>(inputs, outputs_xor,   logic_gates::XOR));
        brain.push_back(std::make_unique<neural_network>(inputs, outputs_nand,  logic_gates::NAND));
        brain.push_back(std::make_unique<neural_network>(inputs, outputs_nor,   logic_gates::NOR));
        brain.push_back(std::make_unique<neural_network>(inputs, outputs_nxor,  logic_gates::NXOR));
    }

    void treinar() {
        for (auto& i: brain)
            i->treinar(training_set_order, epochs);
    }

    void treinar(bool print) {
        for (auto& i: brain) {
            i->treinar(training_set_order, epochs);
            i->printall();
        }
    }

    bit prever(logic_gates type, double x, double y) {
        bit resultado;

        for (auto& i: brain) {
            if (i->get_type() == type) {
                double retornado = i->prever(x, y);
                
                resultado = i->normalizar(retornado);
                return resultado;
            }
        }

        throw std::invalid_argument("[~ X ~] porta logica desconhecida");
    }

    bit arena(logic_gates type, double x, double y) {
        bit resultado;

        for (auto& i: brain) {
            if (i->get_type() == type) {
                double* previsoes = i->previsao(x, y);
                double retornado  = i->batalhar(previsoes);

                resultado = i->normalizar(retornado);
                
                delete previsoes;
                return resultado;
            }
        }

        throw std::invalid_argument("[~ X ~] porta logica desconhecida");
    }
};
