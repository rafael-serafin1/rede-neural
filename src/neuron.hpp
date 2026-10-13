#pragma once

#include <stdio.h>
#include <stdlib.h>

#ifndef NEURON_H
#define NEURON_H

class neuron {
private:
    int input_nums = 0;

    double layer = 0.0f;
    double bias  = 0.0f;
    double delta = 0.0f;
    double* weights = nullptr;

    double randomizar() {
        return ((double) rand()) / ((double) RAND_MAX);
    }

public:
    neuron(int InputNum): input_nums(InputNum) {
        weights = new double[input_nums]{ 0.0f };
    }

    ~neuron() {
        if (weights != nullptr)
            delete[] weights;
    }

    void inicializar() {
        for (int i = 0; i < input_nums; ++i) 
            this->weights[i] = randomizar();

        this->bias = randomizar();
    }


    ///
    /// getters e setters
    /// 
    double get_layer() {
        return layer;
    }

    void set_layer(double value) {
        layer = value;
    }


    double* get_weights() {
        return weights;
    }

    double get_weights(int index) {
        return weights[index];
    }

    void set_weights(double value, int index) {
        weights[index] = value;
    }


    double get_bias() {
        return bias;
    }
 
    void set_bias(double value) {
        bias = value;
    }


    double get_delta() {
        return delta;
    }

    void set_delta(double value) {
        delta = value;
    } 
};

#endif