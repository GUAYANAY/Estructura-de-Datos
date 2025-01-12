#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "qrcodegen.hpp"        // Librería QR Code Generator
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"   // Librería para crear imágenes

using namespace qrcodegen;

// Función para guardar el código QR como una imagen PNG
void saveQRCodeAsPng(const QrCode &qr, const std::string &filename, int scale = 10) {
    const int size = qr.getSize();
    const int imageSize = size * scale;

    // Crear el buffer para la imagen en blanco (negro = 0, blanco = 255)
    std::vector<unsigned char> image(imageSize * imageSize, 255);

    // Dibujar el QR en el buffer
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            if (qr.getModule(x, y)) {
                for (int dy = 0; dy < scale; ++dy) {
                    for (int dx = 0; dx < scale; ++dx) {
                        int px = (y * scale + dy) * imageSize + (x * scale + dx);
                        image[px] = 0; // Negro para los módulos del QR
                    }
                }
            }
        }
    }

    // Guardar la imagen como PNG
    if (stbi_write_png(filename.c_str(), imageSize, imageSize, 1, image.data(), imageSize) == 0) {
        std::cerr << "Error al guardar la imagen " << filename << std::endl;
    } else {
        std::cout << "Código QR guardado como: " << filename << std::endl;
    }
}

int main() {
    std::string inputText;
    std::cout << "Introduce el texto para generar el código QR: ";
    std::getline(std::cin, inputText);

    // Generar el código QR
    QrCode qr = QrCode::encodeText(inputText.c_str(), QrCode::Ecc::MEDIUM);

    // Guardar el código QR como imagen
    saveQRCodeAsPng(qr, "codigo_qr.png", 10); // Escala 10 (ajustable)

    return 0;
}
