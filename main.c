#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

void menu();
void remCliente();
void listCliente();
void melCliente();
void comCliente();
void atuCliente();
void limCliente();
void cadCliente();

typedef struct {
	char nome[30];
	int anoNasc, existencia;
	float valorMes;
}CLIENTE;
CLIENTE *cliente;

int maxCliente = 11;
int *pMaxCliente = &maxCliente;

int main() {
	setlocale(LC_ALL, "Portuguese");
	
	if (maxCliente == 10) {
		cliente = (CLIENTE *) malloc ((maxCliente) * sizeof(CLIENTE));
		if (cliente == NULL) {
			printf("Erro de malloc");
		} else {
			int i;
			for (i = 0; i < maxCliente; i++) {
				cliente[i].existencia = 0;
			}
		}
	} else if (maxCliente > 10) {
		cliente = realloc (cliente, (maxCliente) * sizeof(CLIENTE));
		if (cliente != NULL) {
			printf("Sucesso no realloc");
			int i;
			for (i = (maxCliente-10); i < maxCliente; i++){
				cliente[i].existencia = 0;
			}
		} else {
			printf("Erro do realloc");
		}
	}
	
	menu(&cliente);
	
	cliente = NULL;
	return 0;
}
void menu(CLIENTE *cliente) {
	int selecao;
	do {
		system("cls");
		printf("Digite o número da opção escolhida\n");
		printf("1 - Cadastro de cliente\n");
		printf("2 - Remover cliente\n");
		printf("3 - Listar todos os clientes\n");
		printf("4 - Listar o cliente melhor comprador\n");
		printf("5 - Mostrar compras de um cliente específico\n");
		printf("6 - Atualizar as compras de um cliente específico\n");
		printf("7 - Zerar todas as compras do mês de todos os clientes\n");
		printf("8 - Sair\n");
		printf("Opção: ");
		fflush(stdin);
		scanf("%d", &selecao);
		
		switch (selecao) {
			case 1 :
				cadCliente(&cliente);
				break;
			case 2 :
				remCliente(&cliente);
				break;
			case 3 :
				listCliente(&cliente);
				break;
			case 4 :
				melCliente(&cliente);
				break;
			case 5 :
				comCliente(&cliente);
				break;
			case 6 :
				atuCliente(&cliente);
				break;
			case 7 :
				limCliente(&cliente);
				break;
			case 8 :
				cliente = NULL;
				exit(0);
				break;
			default :
			break;	
		}
	} while (selecao != 8);
}
void cadCliente(CLIENTE **cliente) {
	char nomm[30];
	int anoNass, o, selecaoc, selecao, ex, i;
	float valorMee;
	
	do {
		system("cls");
		printf("Preencha os campos abaixo\n");
		fflush(stdin);
		printf("Nome: ");
		fgets(nomm, sizeof(nomm), stdin);
		printf("Ano de Nascimento: ");
		scanf("%d", &anoNass);
		printf("Valor gasto no mês(R$): ");
		scanf("%f", &valorMee);
		
		for(o = 0; o < maxCliente; o++){
			if ((*(*cliente+o)).existencia == 0) {
				strcpy((*(*cliente+o)).nome, nomm);
				(*(*cliente+o)).anoNasc = anoNass;
				(*(*cliente+o)).valorMes = valorMee;
				(*(*cliente+o)).existencia = 1;
				system("cls");
				printf("Cadastrado com sucesso\n");
				break;
			}
			if ((*(*cliente+maxCliente-1)).existencia == 1) {
				do {
					system("cls");
					printf("Número máximo de clientes cadastrado atingido, deseja aumentar o número de cadastrados de %d para %d?\n", maxCliente-1, maxCliente + 9);
					printf("1 - Sim\n");
					printf("2 - Não\n");
					printf("Opção: ");
					scanf("%d", &selecaoc);
					if (selecaoc == 1) {
						*pMaxCliente = *pMaxCliente + 10;
						selecaoc = 2;
						main();
						break;
					}
				} while (selecaoc != 2);
				break;
			}
		}
		printf("====================\n");
		printf("1 - Cadastrar outro cliente\n");
		printf("2 - Sair\n");
		printf("Opção: ");
		fflush(stdin);
		scanf("%d", &selecao);
	} while (selecao != 2);
}
void remCliente(CLIENTE **cliente) {
	int i, selecao, selecaox, selecaor;
	
	do {
		system("cls");
		for (i = 0; i < maxCliente; i++){
			if((*(*cliente+i)).existencia == 1){
				printf("Cliente - %d\n", i);
				printf("Nome: %s", (*(*cliente+i)).nome);
				printf("Ano de nascimento: %d\n", (*(*cliente+i)).anoNasc);
				printf("Valor gasto no mês: %.2f\n", (*(*cliente+i)).valorMes);
				printf("====================\n");
			}
		}
		printf("Selecione o número do cliente para exclui-lo, ou digite 0 para sair\n");
		printf("Opção: ");
		fflush(stdin);
		scanf("%d", &selecaox);
		if ((*(*cliente+selecaox)).existencia == 1){
			do {
				system("cls");
				printf("Tem certeza que deseja excluir o cliente %d permanentemente?\n", selecaox);
				printf("Nome: %s", (*(*cliente+selecaox)).nome);
				printf("Ano de nascimento: %d\n", (*(*cliente+selecaox)).anoNasc);
				printf("Valor gasto no mês: %.2f\n", (*(*cliente+selecaox)).valorMes);
				printf("====================\n");
				printf("1 - Sim\n");
				printf("2 - Não\n");
				printf("Opção: ");
				fflush(stdin);
				scanf("%d", &selecaor);
				if (selecaor == 1){
					(*(*cliente+selecaox)).existencia = 0;
					(*(*cliente+selecaox)).valorMes = 0;
					system("cls");
					printf("Cliente %d excluído com sucesso\n", selecaox);
					break;
				} else {
					system("cls");
					printf("Exclusão do veículo %d cancelada\n", selecaox);
					break;
				}
			} while (selecaor != 2);
		} else if (selecaox == 0) {
			system("cls");
			printf("Digite 2 para sair\n");
		} else {
			system("cls");
			printf("Este cliente não existe\n");
		}
		printf("====================\n");
		printf("1 - Remover outro cliente\n");
		printf("2 - Sair\n");
		printf("Opção: ");
		fflush(stdin);
		scanf("%d", &selecao);
	}while (selecao != 2);
}
void listCliente(CLIENTE **cliente) {
	int i, selecao;
	
	do {
		system("cls");
		for (i = 0; i < maxCliente; i++){
			if((*(*cliente+i)).existencia == 1){
				printf("Cliente - %d\n", i);
				printf("Nome: %s", (*(*cliente+i)).nome);
				printf("Ano de nascimento: %d\n", (*(*cliente+i)).anoNasc);
				printf("Valor gasto no mês: %.2f\n", (*(*cliente+i)).valorMes);
				printf("====================\n");
			}
		}
		printf("1 - Sair\n");
		printf("Opção: ");
		fflush(stdin);
		scanf("%d", &selecao);
	}while (selecao != 1);
}
void melCliente(CLIENTE **cliente) {
	float  a;
	int u, i, selecao;
	a = (*(*cliente)).valorMes;
	i = 0;
	
	for (u = 0; u < maxCliente; u++) {
		if(a < (*(*cliente+u)).valorMes) {
			a = (*(*cliente+u)).valorMes;
			i = u;
		}
	}
	if ((*(*cliente+i)).valorMes == 0){
		system("cls");
		printf("Nao foi encontrado nenhum cliente cadastrado\n");
		printf("Cadastre um cliente selecionando a opção 1 no menu\n");
		printf("1 - Voltar ao menu\n");
		printf("Opção: ");
		fflush(stdin);
		scanf("%d", &selecao);
	} else {
		do {
			system("cls");
			printf("Cliente com maior valor de compra\n");
			printf("Cliente - %d\n", i);
			printf("Nome: %s", (*(*cliente+i)).nome);
			printf("Ano de nascimento: %d\n", (*(*cliente+i)).anoNasc);
			printf("Valor gasto no mês: %.2f\n", (*(*cliente+i)).valorMes);
			printf("====================\n");
			printf("1 - Sair\n");
			printf("Opção: ");
			fflush(stdin);
			scanf("%d", &selecao);
		} while (selecao != 1);
	}
}
void comCliente(CLIENTE **cliente) {
	int i, selecao, selecaoc;
	
	do {
		system("cls");
		printf("Selecine um cliente mostrar o valor da compra do mês, ou digite 0 para sair\n");
		printf("Número do cliente: ");
		fflush(stdin);
		scanf("%d", &selecao);
		
		if ((*(*cliente+selecao)).existencia == 1){
			system("cls");
			printf("Cliente - %d\n", selecao);
			printf("Nome: %s", (*(*cliente+selecao)).nome);
			printf("Ano de nascimento: %d\n", (*(*cliente+selecao)).anoNasc);
			printf("Valor gasto no mês: %.2f\n", (*(*cliente+selecao)).valorMes);
		} else if (selecao == 0) {
			system("cls");
			printf("Digite 2 para sair\n");
		} else {
			system("cls");
			printf("Esse cliente não existe\n");
		}
		printf("====================\n");
		printf("1 - Fazer outra pesquisa\n");
		printf("2 - Sair\n");
		fflush(stdin);
		printf("Opção: ");
		scanf("%d", &selecaoc);
	} while (selecaoc != 2);
}
void atuCliente(CLIENTE **cliente) { 
	int i, selecao, selecaom;
	float valor, valori;
	
	do {
		do {
			system("cls");
			printf("Selecine um cliente para atualizar as compras do mês, ou digite 0 para sair\n");
			printf("====================\n");
			for (i = 0; i < maxCliente; i++){
				if((*(*cliente+i)).existencia == 1){
					printf("Cliente - %d\n", i);
					printf("Nome: %s", (*(*cliente+i)).nome);
					printf("Ano de nascimento: %d\n", (*(*cliente+i)).anoNasc);
					printf("Valor gasto no mês: %.2f\n", (*(*cliente+i)).valorMes);
					printf("====================\n");
				}
			}
			printf("Opção: ");
			fflush(stdin);
			scanf("%d", &selecao);
			if ((*(*cliente+selecao)).existencia == 1) {
				do {
					system("cls");
					printf("Cliente - %d\n", selecao);
					printf("Nome: %s", (*(*cliente+selecao)).nome);
					printf("Ano de nascimento: %d\n", (*(*cliente+selecao)).anoNasc);
					printf("Valor gasto no mês: %.2f\n", (*(*cliente+selecao)).valorMes);
					printf("====================\n");
					printf("Selecione uma opção\n");
					printf("1 - Mudar o valor\n");
					printf("2 - Incrementar o valor\n");
					printf("3 - Sair\n");
					printf("Opção: ");
					fflush(stdin);
					scanf("%d", &selecaom);
					if (selecaom == 1) {
						system("cls");
						valor = 0;
						printf("====================\n");
						printf("Valor gasto do mês do cliente %d: %.2f\n",selecao, (*(*cliente+selecao)).valorMes);
						printf("Valor a ser mudado: ");
						scanf("%f", &valor);
						(*(*cliente+selecao)).valorMes = valor;
						printf("Valor atualizado com sucesso\n");
					} else if (selecaom == 2) {
						system("cls");
						valor = 0;
						printf("====================\n");
						printf("Valor gasto do mês do cliente %d: %.2f\n",selecao, (*(*cliente+selecao)).valorMes);
						printf("Valor a ser incrementado: ");
						scanf("%f", &valori);
						(*(*cliente+selecao)).valorMes = (*(*cliente+selecao)).valorMes + valori;
						printf("Valor atualizado com sucesso\n");
					} else if (selecaom == 3) {
						system("cls");
						printf("Digite 2 para sair para a tela inicial\n");
					} else {
						system("cls");
						printf("Opção inválida\n");
					}
				} while (selecaom != 3);
			} else if (selecao == 0) {
				system("cls");
				printf("Digite 2 para sair para a tela principal");
			} else {
				system("cls");
				printf("Esse cliente não existe\n");
			}
		} while (selecao = 0);
		
		printf("====================\n");
		printf("1 - Atualizar outro cliente\n");
		printf("2 - Sair\n");
		printf("Opção: ");
		fflush(stdin);
		scanf("%d", &selecao);
	}while (selecao != 2);
}
void limCliente(CLIENTE **cliente) {
	int i, selecao;
	
	do {
		system("cls");
		for (i = 0; i < maxCliente; i++){
			if((*(*cliente+i)).existencia == 1){
				printf("Cliente - %d\n", i);
				printf("Nome: %s", (*(*cliente+i)).nome);
				printf("Ano de nascimento: %d\n", (*(*cliente+i)).anoNasc);
				printf("Valor gasto no mês: %.2f\n", (*(*cliente+i)).valorMes);
				printf("====================\n");
			}
		}
		printf("Tem certeza que deseja zerar o valor do gasto do mês de todos os cliente?\n");
		printf("1 - Sim\n");
		printf("2 - Não, voltar para a tela inicial\n");
		printf("Opção: ");
		fflush(stdin);
		scanf("%d", &selecao);
		if (selecao == 1){
			for (i = 0; i < maxCliente; i++) {
				if((*(*cliente+i)).existencia == 1) {
					(*(*cliente+i)).valorMes = 0;
					system("cls");
					printf("Valor zerado com sucesso");
				}
			}
		}
	} while (selecao != 2);
}
