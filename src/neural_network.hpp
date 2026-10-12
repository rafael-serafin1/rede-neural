#pragma once

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "logic.hpp"

///<label>REDE NEURAL</label>
///<desc>Rede neural capaz de aprender portas lógicas, com exceção do NOT porquê ele usa apenas duas entradas kkkkkk</desc>
///<span>


#define NUMERO_ENTRADAS 2
#define NUMERO_NOS_ESCONDIDOS 2
#define NUMERO_SAIDAS 1
#define NUMERO_TENTATIVAS_TREINO 4

struct __attribute__((packed)) bit {
    unsigned int value : 1;         // ocupa LITERALMENTE 1 bit
};

class neural_network {
private:
    const double LearningRate = 0.1f;

    double hidden_layer[NUMERO_NOS_ESCONDIDOS];
    double output_layer[NUMERO_SAIDAS];

    double hidden_weights[NUMERO_ENTRADAS][NUMERO_NOS_ESCONDIDOS];
    double output_weight[NUMERO_NOS_ESCONDIDOS][NUMERO_SAIDAS];

    double hidden_layer_bias[NUMERO_NOS_ESCONDIDOS];
    double output_layer_bias[NUMERO_SAIDAS];

    double training_inputs[NUMERO_TENTATIVAS_TREINO][NUMERO_ENTRADAS];
    double training_outputs[NUMERO_TENTATIVAS_TREINO][NUMERO_SAIDAS];

    logic_gates type;

    void inicializar_pesos_escondidos(double matriz[][NUMERO_NOS_ESCONDIDOS]) {
        for (int i = 0; i < NUMERO_ENTRADAS; ++i)
            for (int j = 0; j < NUMERO_NOS_ESCONDIDOS; ++j)
                matriz[i][j] = pesos_randomicos();
    }

    void inicializar_pesos_saida(double matriz[][NUMERO_SAIDAS]) {
        for (int i = 0; i < NUMERO_NOS_ESCONDIDOS; ++i)
            for (int j = 0; j < NUMERO_SAIDAS; ++j)
                matriz[i][j] = pesos_randomicos();
    }

    void inicializar_bias(double* bias, int n) {
        for (int i = 0; i < n; ++i) 
            bias[i] = this->pesos_randomicos();
    }

protected:
    double pesos_randomicos() {
        return ((double) rand()) / ((double) RAND_MAX);
    }

    void forward_pass(int i) {
        // compute hidden layer activation
        for (int j = 0; j < NUMERO_NOS_ESCONDIDOS; ++j) {
            double activation = hidden_layer_bias[j];

            for (int k = 0; k < NUMERO_ENTRADAS; ++k)
                activation += training_inputs[i][k] * hidden_weights[k][j];

            hidden_layer[j] = sigmoide(activation);
        }

        // compute output layer activation
        for (int j = 0; j < NUMERO_SAIDAS; ++j) {
            double activation = output_layer_bias[j];

            for (int k = 0; k < NUMERO_NOS_ESCONDIDOS; ++k)
                activation += hidden_layer[k] * output_weight[k][j];

            output_layer[j] = sigmoide(activation);
        }

        /* 
            std::printf("Input: %g %g ; Output: %g ; Predicted Output: %g\n", training_inputs[i][0], training_inputs[i][1], 
                output_layer[0], training_outputs[i][0]);
        */
    }

    void back_propagation(int i) {
        // compute change in output weights
        double delta_output[NUMERO_SAIDAS];

        for (int j = 0; j < NUMERO_SAIDAS; ++j) {
            double error_margin = (training_outputs[i][j] - output_layer[j]);
            delta_output[j] = error_margin * derivar_sigmoide(output_layer[j]);
        }

        // compute change in hidden weights
        double delta_hidden[NUMERO_NOS_ESCONDIDOS];

        for (int j = 0; j < NUMERO_NOS_ESCONDIDOS; ++j) {
            double error_margin = 0.0f;
            for (int k = 0; k < NUMERO_SAIDAS; ++k)
                error_margin += delta_output[k] * output_weight[j][k];
            
            delta_hidden[j] = error_margin * derivar_sigmoide(hidden_layer[j]);
        }

        // apply change in output weights
        for (int j = 0; j < NUMERO_SAIDAS; ++j) {
            output_layer_bias[j] += delta_output[j] * LearningRate;
            for (int k = 0; k < NUMERO_NOS_ESCONDIDOS; ++k) 
                output_weight[k][j] += hidden_layer[k] * delta_output[j] * LearningRate;
        }

        // apply change in hidden weights
        for (int j = 0; j < NUMERO_NOS_ESCONDIDOS; ++j) {
            hidden_layer_bias[j] += delta_hidden[j] * LearningRate;
            for (int k = 0; k < NUMERO_ENTRADAS; ++k) 
                hidden_weights[k][j] += training_inputs[i][k] * delta_hidden[j] * LearningRate;
        }
    }

public:
    neural_network(double TrainingInputs[NUMERO_TENTATIVAS_TREINO][NUMERO_ENTRADAS], double TrainingOutputs[NUMERO_TENTATIVAS_TREINO][NUMERO_SAIDAS], 
        logic_gates LogicGateType): type(LogicGateType)
    {
        for (int i = 0; i < NUMERO_TENTATIVAS_TREINO; ++i) {
            for (int j = 0; j < NUMERO_ENTRADAS; ++j)
                training_inputs[i][j] = TrainingInputs[i][j];

            for (int j = 0; j < NUMERO_SAIDAS; ++j)
                training_outputs[i][j] = TrainingOutputs[i][j];
        }

        this->initialize_weights();
    }

    logic_gates get_type() {
        return this->type;
    }

    void initialize_weights() {
        this->inicializar_pesos_escondidos(this->hidden_weights);
        this->inicializar_pesos_saida(this->output_weight);

        this->inicializar_bias(this->hidden_layer_bias, NUMERO_NOS_ESCONDIDOS);
        this->inicializar_bias(this->output_layer_bias, NUMERO_SAIDAS);
    }

    double sigmoide(double x) {
        return 1 / (1 + exp(-x));
    }

    double derivar_sigmoide(double x) {
        return x * (1 - x);
    }

    void embaralhar(int array[], size_t n) {
        if (n > 1) {
            for (register size_t i = 0; i < n - 1; ++i) {
                size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
                int t = array[j];
                array[j] = array[i];
                array[i] = t;
            }
        }
    }

    void printall() {
        std::printf("\nRESULT FOR '%s'\n", type);

        fputs("Final Hidden Weights\n[", stdout);
        for (int j = 0; j < NUMERO_NOS_ESCONDIDOS; ++j) 
            printf("%f, ", hidden_weights[j]);

        fputs("]\nFinal Output Weights\n[", stdout);
        for (int j = 0; j < NUMERO_SAIDAS; ++j) 
            printf("%f, ", output_weight[j]);

        fputs("]\nFinal Hidden Blases\n[", stdout);
        for (int j = 0; j < NUMERO_NOS_ESCONDIDOS; ++j) {
            printf("%f, ", hidden_layer_bias[j]);
        }

        fputs("]\nFinal Output Blases\n[", stdout);
        for (int j = 0; j < NUMERO_SAIDAS; ++j) {
            printf("%f, ", output_layer_bias[j]);
        }

        printf("]\n\n");
    }


    void treinar(int* TrainingSetOrder, int NumberOfEpochs) {
        for (int epoch = 0; epoch < NumberOfEpochs; epoch++) {
            embaralhar(TrainingSetOrder, NUMERO_TENTATIVAS_TREINO);
            
            for (int x = 0; x < NUMERO_TENTATIVAS_TREINO; ++x) {
                int i = TrainingSetOrder[x];

                // forward pass
                this->forward_pass(i);

                /// backprop
                this->back_propagation(i);
            }
        }
    }

    double prever(double x, double y) {
        double inputs[NUMERO_ENTRADAS] = {x, y};

        for (register int i = 0; i < NUMERO_NOS_ESCONDIDOS; ++i) {
            double activation = hidden_layer_bias[i];

            for (register int j = 0; j < NUMERO_ENTRADAS; ++j) 
                activation += inputs[j] * hidden_weights[j][i];

            hidden_layer[i] = sigmoide(activation);
        }

        double activation = output_layer_bias[0];
        
        for (register int i = 0; i < NUMERO_NOS_ESCONDIDOS; ++i) 
            activation += hidden_layer[i] * output_weight[i][0];

        output_layer[0] = sigmoide(activation);

        return output_layer[0];
    }

    bit normalizar(double x) {
        return bit{ 
            (unsigned int)
            ((x >= 0.5f) ? 1 : 0)
        };
    }
};

///</span>