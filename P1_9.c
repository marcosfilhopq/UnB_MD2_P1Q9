#include <stdio.h>

// Função para calcular o mdc usando o Algoritmo de Euclides
int mdc(int a, int b) {
    while (b != 0) {
        int resto = a % b;
        a = b;
        b = resto;
    }
    return a;
}

// Verifica se dois números são primos entre si (coprimos)
int sao_coprimos(int a, int b) {
    return mdc(a, b) == 1;
}

// Função para calcular o inverso modular usando o Algoritmo Estendido de Euclides
int inverso_modular(int a, int n) {
    int t = 0, novo_t = 1;
    int r = n, novo_r = a;
    while (novo_r != 0) {
        int quociente = r / novo_r;
        int temp = novo_t;
        novo_t = t - quociente * novo_t;
        t = temp;

        temp = novo_r;
        novo_r = r - quociente * novo_r;
        r = temp;
    }
    if (r > 1) return -1; // Não tem inverso
    if (t < 0) t += n;
    return t;
}

// Função para exponenciação modular eficiente (a^e mod n)
int exp_mod(int a, int e, int n) {
    int resultado = 1;
    a = a % n;
    while (e > 0) {
        if (e % 2 == 1)
            resultado = (resultado * a) % n;
        a = (a * a) % n;
        e = e / 2;
    }
    return resultado;
}

// Função para fatorar n1 e calcular φ(n1)
int phi(int n) {
    int resultado = n;
    for (int p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0)
                n /= p;
            resultado -= resultado / p;
        }
    }
    if (n > 1)
        resultado -= resultado / n;
    return resultado;
}

// Verifica se um número é primo (teste simples)
int eh_primo(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return 0;
    return 1;
}

int main() {
    int H, G, n, x, n1;

    // Solicita ao professor os dados de entrada
    printf("Digite os valores de H, G, n, x, n1: ");
    scanf("%d %d %d %d %d", &H, &G, &n, &x, &n1);

    printf("\nEtapa 1: Verificando se G e n sao primos entre si:\n");
    if (!sao_coprimos(G, n)) {
        printf("G e n não sao primos entre si. Divisão modular não é possível.\n");
        return 1;
    }

    printf("G e n sao primos entre si. Prosseguindo...\n");

    printf("\nEtapa 2: Calculando o inverso modular de G em Z%d:\n", n);
    int G_inverso = inverso_modular(G, n);
    if (G_inverso == -1) {
        printf("G nao possui inverso modular em Z%d. Divisao impossível.\n", n);
        return 1;
    }
    printf("Inverso de G e: %d\n", G_inverso);

    printf("\nEtapa 3: Dividindo H por G em Z%d (a = H ⊘ G):\n", n);
    int a = (H * G_inverso) % n;
    printf("Valor de a = %d\n", a);

    printf("\nEtapa 4: Verificando se a e n1 sao coprimos:\n");
    if (!sao_coprimos(a, n1)) {
        printf("a e n1 nao sao coprimos. Operaçao modular inválida.\n");
        return 1;
    }
    printf("a e n1 sao coprimos.\n");

    int x1;
    if (eh_primo(n1)) {
        printf("\nEtapa 5: n1 e primo. Usando Pequeno Teorema de Fermat:\n");
        x1 = n1 - 1;
    } else {
        printf("\nEtapa 5: n1 nao e primo. Usando Teorema de Euler:\n");
        x1 = phi(n1);
    }
    printf("Valor de x1 = %d\n", x1);

    printf("\nEtapa 6: Decompondo x = x1 * q + r:\n");
    int q = x / x1;
    int r = x % x1;
    printf("x = %d = %d * %d + %d\n", x, x1, q, r);

    printf("\nEtapa 7: Calculando os valores intermediarios:\n");
    int x2 = exp_mod(a, x1, n1);
    printf("a^x1 mod n1 = %d\n", x2);

    int parte1 = exp_mod(x2, q, n1);
    printf("(a^x1)^q mod n1 = %d\n", parte1);

    int parte2 = exp_mod(a, r, n1);
    printf("a^r mod n1 = %d\n", parte2);

    int resultado = (parte1 * parte2) % n1;
    printf("\nResultado final: a^x mod n1 = %d\n", resultado);

    return 0;
}
