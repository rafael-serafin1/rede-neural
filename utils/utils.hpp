#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <iostream>

namespace nutils {
    template<typename T>
    const T& maior_repeticao(const T* array, std::size_t tamanho) {
        if (tamanho == 0)
            throw std::invalid_argument("Array vazio");

        size_t maior_count = 0;
        const T* maior = nullptr;

        for (size_t i = 0; i < tamanho; ++i) {
            size_t count = 0;

            for (size_t j = 0; j < tamanho; ++j) {
                if (array[i] == array[j])
                    ++count;
            }

            if (count > maior_count) {
                maior_count = count;
                maior = &array[i];
            }
        }

        return *maior;
    }
}

#endif