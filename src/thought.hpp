#pragma once


/// @brief representa o 'output' ou 'saída'
class thought {
private:
    int output_nums   = 0;
    int training_nums = 0;

    double layer = 0.0f;
    double bias  = 0.0f;
    double delta = 0.0f;

    double* weights  = nullptr;
    double* training = nullptr;

    double randomizar() {
        return ((double) rand()) / ((double) RAND_MAX);
    }

public:
    thought(int OutputNum, int TrainingNum): output_nums(OutputNum), training_nums(TrainingNum) {
        weights  = new double[output_nums]{ 0.0f };
        training = new double[training_nums]{ 0.0f };
    }

    ~thought() {
        if (weights != nullptr)
            delete[] weights;
        if (training != nullptr)
            delete[] training;
    }

    void inicializar() {
        for (int i = 0; i < output_nums; ++i) 
            weights[i] = randomizar();

        bias = randomizar();
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


    double* get_weights() {
        return weights;
    }

    double get_weights(int index) {
        return weights[index];
    }

    void set_weights(double* value) {
        weights = value;
    }

    void set_weights(double value, int index) {
        weights[index] = value;
    }


    double* get_training() {
        return training;
    }

    double get_training(int index) {
        return training[index];
    }

    void set_training(double* training) {
        this->training = training;
    }

    void set_training(double value, int index) {
        training[index] = value;
    }
};