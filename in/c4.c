float area_circulo(float raio) { // Função para calcular a área de um círculo
    float pi = 3.14159;
    return pi * raio * raio;
}

int main() {
    float raio = 5.0;
    float area = area_circulo(raio);
    return 0;
}