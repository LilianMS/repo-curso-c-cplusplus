#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CINZA "\033[2;30m"
#define RESET "\033[0m"

int	main()
{
	int a, b, c;
	char op;
	char input[100];

	a = b = c = 0;
	while (1)
	{
		printf("Digite a expressão: \n");
		printf(CINZA "ex: 2 + 3\nou \"x\" para sair\n" RESET);
		fgets(input, sizeof(input), stdin);

		if (input[0] == 'x' || input[0] == 'X')
		{
			printf("Encerrando o programa...\n");
			break;
		}

		if (sscanf(input, "%d %c %d", &a, &op, &b) != 3)
		{
			printf("Entrada inválida. Tente novamente.\n");
			continue;
		}

		switch (op)
		{
		case '+':
			c = a + b;
			break;
		case '-':
			c = a - b;
			break;
		case '*':
			c = a * b;
			break;
		case '/':
			if (b == 0)
			{
				printf("Erro: divisão por zero.\n");
				continue;
			}
			c = a / b;
			break;
		default:
			printf("Operador inválido\n");
			continue;
		}

		printf("Resultado: %d\n", c);
	}
	return 0;
}
/**
 *  Aqui fgets é usado para ler a entrada do usuário como uma linha de texto. Em seguida, sscanf é usado para analisar essa linha e extrair os valores de a, op e b. Se a entrada for 'x' ou 'X', o programa encerra. Se sscanf não conseguir ler três valores, uma mensagem de erro é exibida e o loop continua, solicitando ao usuário que tente novamente.
 *  
 */
