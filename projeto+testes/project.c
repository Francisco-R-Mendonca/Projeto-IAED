/**
 * Programa que faz a gestão de parques de estacionamento e os seus veículos 
 * @file project.c
 * @author ist1109264
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "project.h"


/**
 * Cria um novo veículo com a matrícula e data de entrada fornecidas.
 * @param matricula a matrícula do novo veículo.
 * @param data_e a data de entrada do novo veículo.
 * @return Um ponteiro para o novo veículo criado.
*/
Veiculo* criaVeiculo(Matricula matricula, Data data_e) {
	Data data_s = {0, 0, 0, 0, 0};
    /** aloca a memoria do novo veiculo. */
	Veiculo* novoVeiculo = (Veiculo*) malloc(sizeof(Veiculo));
    /** define os valores do veiculo */
	novoVeiculo->matricula = matricula;
	novoVeiculo->data_e = data_e;
	novoVeiculo->data_s = data_s;
	novoVeiculo->next = NULL;
	return novoVeiculo;
}


/**
 * Cria um novo nó de veículo com o veículo fornecido.
 * @param veiculo o veículo associado ao nó.
 * @return Um ponteiro para o novo nó de veículo criado.
*/
VeiculoNode* criaVeiculoNode(Veiculo *veiculo) {
    /** aloca a memoria do novo nó de veiculo. */
    VeiculoNode* novoNode = (VeiculoNode*)malloc(sizeof(VeiculoNode));
    /** define os valores do nó do veiculo */
    novoNode->veiculo = veiculo;
    novoNode->next = NULL;
    return novoNode;
}


/**
 * Cria um novo parque com o nome, o precoX, o precoY, o precoZ e a capacidade.
 * @param nome o nome do novo parque.
 * @param pX o preco por 15 minutos até 1 hora associado ao novo parque.
 * @param pY o preco por 15 minutos após 1 hora associado ao novo parque.
 * @param pZ o preco maximo cobrado por dia associado ao novo parque.
 * @param capacidade a capacidade do novo parque.
 * @return Um ponteiro para o novo parque criado.
*/
Parque* criaParque(char nome[], float pX, float pY, float pZ, int capacidade) {
    /** aloca a memoria do novo parque. */
    Parque* novoParque = (Parque*)malloc(sizeof(Parque));
    /** define os valores do parque */
    strcpy(novoParque->nome, nome);
    novoParque->precoX = pX;
    novoParque->precoY = pY;
    novoParque->precoZ = pZ;
    novoParque->capacidade = capacidade;
    novoParque->veiculos_head = NULL;
    novoParque->next = NULL;
    return novoParque;
}


/**
 * Registra a entrada de um veiculo num parque adicionando o nó do veiculo ao 
   parque.
 * @param parque o ponteiro para o parque ao qual temos de dar entrada.
 * @param matricula a matrícula do veículo.
 * @param data_e a data de entrada do veículo.
*/
void EntradaVeiculo(Parque *parque, Matricula matricula, Data data_e) {
    Veiculo *novoVeiculo;
    VeiculoNode *novoNode, *atual;
    novoVeiculo = criaVeiculo(matricula, data_e);
    novoNode = criaVeiculoNode(novoVeiculo);
    /** 
     * se não há veiculos no parque, adiciona o novo veiculo como primeiro 
     * se há veiculos no parque, adiciona o novo veiculo à frente do anterior
    */
    if (parque->veiculos_head == NULL) {
        parque->veiculos_head = novoNode;
    } else {
        atual = parque->veiculos_head;
        while (atual->next != NULL) {
            atual = atual->next;
        }
        atual->next = novoNode;
    }
}


/**
 * Calcula o número de lugares disponíveis no parque.
 * @param parque o ponteiro do parque que se deseja calcular os lugares 
   disponíveis.
 * @return O número de lugares disponíveis no parque.
*/
int lugares_disponiveis(Parque *parque) {
    int capacidade_total = parque->capacidade;
    int ocupados = 0;
    VeiculoNode *veiculoAtual = parque->veiculos_head;
    /** Percorre todos os veiculos */
    while (veiculoAtual != NULL) {
        /** Se o veiculo não tem data de saida, está a ocupar um lugar */
        if (veiculoAtual->veiculo->data_s.dia == 0) {
            ocupados++;
        }
        veiculoAtual = veiculoAtual->next;
    }
    return capacidade_total - ocupados;
}


/**
 * Encontra um parque pelo nome, percorrendo a lista de parques.
 * @param primeiroParquePtr O ponteiro para o ponteiro do primeiro parque na 
   lista.
 * @param nomeParque O nome do parque a ser encontrado.
 * @return Um ponteiro para o parque do nome, ou NULL se o parque não existe.
*/
Parque* encontraPporNome(Parque **primeiroParquePtr, char *nomeParque) {
    Parque *parqueAtual = *primeiroParquePtr;
    /** Percorre todos os parques */
    while (parqueAtual != NULL) {
        /** Se o nome for igual retorna o ponteiro */
        if (strcmp(parqueAtual->nome, nomeParque) == 0) {
            return parqueAtual;
        }
        parqueAtual = parqueAtual->next;
    }
    return NULL;
}


/**
 * Encontra uma lista de nós de veículo com base na matrícula fornecida, 
   percorrendo a lista de veículos do parque atual.
 * @param parqueAtual O parque atual onde se deseja procurar.
 * @param m A matrícula do veículo a ser encontrada na lista.
 * @return Um ponteiro para a lista encadeada de nós de veículo que 
   correspondem à matrícula fornecida.
*/
VeiculoNode* encontraListaVMatricula(Parque *parqueAtual, Matricula m) {
    VeiculoNode *veiculoAtual = parqueAtual->veiculos_head;
    VeiculoNode *lista = NULL;
    VeiculoNode *ultimoVeiculoEncontrado = NULL;
    VeiculoNode *nVeiculo;
    /** Percorre todos os veiculos do parque */
    while (veiculoAtual != NULL) {
        /** Se a matricula for a mesma. */
        if (strcmp(veiculoAtual->veiculo->matricula.par1, m.par1) == 0 &&
            strcmp(veiculoAtual->veiculo->matricula.par2, m.par2) == 0 &&
            strcmp(veiculoAtual->veiculo->matricula.par3, m.par3) == 0) {
            /** aloca a memoria para o nó do veiculo. */
            nVeiculo = malloc(sizeof(VeiculoNode));
            /** define os valores do nó do veiculo */
            nVeiculo->veiculo = veiculoAtual->veiculo;
            nVeiculo->next = NULL; 
            /** 
             * Se a lista estiver vazia, o novo nó se torna o primeiro
             * Se não, adiciona o nó de veículo ao final da lista
            */
            if (lista == NULL) {
                lista = nVeiculo;
                ultimoVeiculoEncontrado = nVeiculo;
            } else {
                ultimoVeiculoEncontrado->next = nVeiculo;
                ultimoVeiculoEncontrado = nVeiculo;
            }
        }
        veiculoAtual = veiculoAtual->next;
    }
    return lista;
}


/**
 * Encontra o ultimo veiculo da Lista fornecia, percorrendo a lista de veículos 
   do parque atual.
 * @param Lista A Lista de veículos.
 * @return Um ponteiro para o ultimo veículo da lista.
*/
Veiculo* ultimoVeiculoLista(VeiculoNode *Lista) {
    /** Percorre todos os veiculos da lista até o proximo ser nulo */
    while (Lista->next != NULL) {
        Lista = Lista->next;
    }
    return Lista->veiculo;
}


/**
 * Verifica a validade do par analizando os caracteres que o compõem.
 * @param par O par da matricula.
 * @param min O caracter minimo.
 * @param max O caracter maximo.
 * @return 1 se for valido e 0 se for invalido.
*/
int parValido(char *par, char *min, char *max) {
    if ((par[0] >= *min && par[0] <= *max) && 
        (par[1] >= *min && par[1] <= *max)) {
        return 1;
    } 
    return 0;
}


/**
 * Verifica se o par é composto por letras.
 * @param par O par da matricula.
 * @return 1 se for de letras e 0 se não for.
*/
int parLetras(char *par) {
    if (par[0] >= 'A' && par[0] <= 'Z') {
        return 1;
    } 
    return 0;
}


/**
 * Verifica a validade da matricula.
 * @param m A matricula.
 * @return 1 se for valida e 0 se não for.
*/
int matriculaValida(Matricula m) {
    int p1, p2, p3;
    if (parValido(m.par1, "0", "9") == 0 && parValido(m.par1, "A", "Z") == 0) {
        return 0;
    } 
    if (parValido(m.par2, "0", "9") == 0 && parValido(m.par2, "A", "Z") == 0) {
        return 0;
    } 
    if (parValido(m.par3, "0", "9") == 0 && parValido(m.par3, "A", "Z") == 0) {
        return 0;
    } 
    p1 = parLetras(m.par1);
    p2 = parLetras(m.par2);
    p3 = parLetras(m.par3);
    /** Para ser valido pode ter 1 par de letras ou 2 pares de letras */
    if (p1 + p2 + p3 == 1 || p1 + p2 + p3 == 2) {
        return 1;
    }
    return 0;
}


/**
 * Verifica se a matricula está dentro do parque sem data de saida.
 * @param parqueAtual O ponteiro para o parque atual.
 * @param m A matricula.
 * @return 1 se a matricula está dentro do parque sem data de saida e 0 se não.
*/
int matriculaDentroParque(Parque *parqueAtual, Matricula m) {
    VeiculoNode *veiculoAtual = parqueAtual->veiculos_head;
    /** Percorre todos os veículos */
    while (veiculoAtual != NULL) {
        /** Verifica se a matrícula é igual e se não há data de saída */
        if (strcmp(veiculoAtual->veiculo->matricula.par1, m.par1) == 0 &&
            strcmp(veiculoAtual->veiculo->matricula.par2, m.par2) == 0 &&
            strcmp(veiculoAtual->veiculo->matricula.par3, m.par3) == 0 &&
            veiculoAtual->veiculo->data_s.dia == 0) {
            return 1;
        }
        veiculoAtual = veiculoAtual->next;
    }
    return 0;
}


/**
 * Verifica se a matricula está dentro de qualquer parque sem data de saida.
 * @param primeiroParque O ponteiro para o primeiro parque.
 * @param m A matricula.
 * @return 1 se a matricula está dentro de qualquer parque sem data de saida e 
   0 se não.
*/
int matriculaDentroQualquerParque(Parque *primeiroParque, Matricula m) {
    Parque *parqueAtual = primeiroParque;
    /** Percorre todos os parques */
    while (parqueAtual != NULL) {
        if (matriculaDentroParque(parqueAtual, m) == 1) {
            return 1;
        }
        parqueAtual = parqueAtual->next;
    }
    return 0;
}


/**
 * Verifica se a matricula está dentro de qualquer parque.
 * @param primeiroParque O ponteiro para o primeiro parque.
 * @param m A matricula.
 * @return 1 se a matricula está dentro de qualquer parque e 0 se não.
*/
int matriculaNaoExistenteParque(Parque *primeiroParque, Matricula m) {
    Parque *parqueAtual = primeiroParque;
    VeiculoNode *veiculoAtual;
    /** Percorre todos os parques */
    while (parqueAtual != NULL) {
        veiculoAtual = parqueAtual->veiculos_head;
        /** Percorre todos os veiculos do parque */
        while (veiculoAtual != NULL) {
            /** Verifica se a matrícula é igual*/
            if (strcmp(veiculoAtual->veiculo->matricula.par1, m.par1) == 0 &&
                strcmp(veiculoAtual->veiculo->matricula.par2, m.par2) == 0 &&
                strcmp(veiculoAtual->veiculo->matricula.par3, m.par3) == 0) {
                return 1;
            }
            veiculoAtual = veiculoAtual->next;
        }
        parqueAtual = parqueAtual->next;
    }
    return 0;
}


/**
 * Consoante o mês retorna o numero de dias desse mês.
 * @param mes O ponteiro para o primeiro parque.
 * @return numero de dias do mês e 0 se não for um mês valido.
*/
int diasPorMes(int mes) {
    int dias = 0;
    switch(mes) {
        case 12: dias = 31; break; // Dezembro
        case 11: dias = 30; break; // Novembro
        case 10: dias = 31; break; // Outubro
        case 9: dias = 30; break;  // Setembro
        case 8: dias = 31; break;  // Agosto
        case 7: dias = 31; break;  // Julho
        case 6: dias = 30; break;  // Junho
        case 5: dias = 31; break;  // Maio
        case 4: dias = 30; break;  // Abril
        case 3: dias = 31; break;  // Março
        case 2: dias = 28; break;  // Fevereiro
        case 1: dias = 31; break;  // Janeiro
    }
    return dias;
}


/**
 * Verifica se a data é valida.
 * @param d A data.
 * @return 1 se a data é valida e 0 se não.
*/
int dataValida(Data d) {
    int dias = diasPorMes(d.mes);
    if (d.dia > 0 && d.dia <= dias && d.mes > 0 && d.mes <= 12 && d.ano >= 0 && 
        d.ano <= ANO_MAX && d.hora >= 0 && d.hora <= HORA_MAX && d.min >= 0 
        && d.min <= MIN_MAX) {
        return 1;
    }
    return 0;
}


/**
 * Converte a data para o numero de minutos que passaram até à data desde 
   01-01-0000 00:00, a data inicial.
 * @param d A data.
 * @return numero de minutos que passaram até à data.
*/
int converteData(Data d) {
    int minutos, dias = 0;
    switch(d.mes) {
        case 12: dias = 334; break; // Dezembro
        case 11: dias = 304; break; // Novembro
        case 10: dias = 273; break; // Outubro
        case 9: dias = 243; break;  // Setembro
        case 8: dias = 212; break;  // Agosto
        case 7: dias = 181; break;  // Julho
        case 6: dias = 151; break;  // Junho
        case 5: dias = 120; break;  // Maio
        case 4: dias = 90; break;   // Abril
        case 3: dias = 59; break;   // Março
        case 2: dias = 31; break;   // Fevereiro
        case 1: dias = 0; break;    // Janeiro
    }
    minutos = d.ano * MINUTOS_ANO + (dias + d.dia - 1) * MINUTOS_DIA + 
    d.hora * MINUTOS_HORA + d.min;
    return minutos;
}


/**
 * Recebe uma data e retorna a data do dia seguinte às 00:00.
 * @param d A data.
 * @return A data correspondente ao dia seguinte.
*/
Data diaSeguinte(Data d) {
    int dias = diasPorMes(d.mes);
    Data diaSeguinte = {0, 0, 0, 0, 0};
    /** 
     * Se o dia for menor que o maximo de dias desse mês, adiciona um dia
     * Se não, se o mês for menor que dezembro, passa de mes
     * Se não, passa de ano
    */
    if (d.dia < dias) {
        diaSeguinte.dia = d.dia + 1;
        diaSeguinte.mes = d.mes;
        diaSeguinte.ano = d.ano;
    } else if (d.mes != MES_MAX) {
        diaSeguinte.dia = 1;
        diaSeguinte.mes = d.mes + 1;
        diaSeguinte.ano = d.ano;
    } else {
        diaSeguinte.dia = 1;
        diaSeguinte.mes = 1;
        diaSeguinte.ano = d.ano + 1;
    }
    return diaSeguinte;
}


/**
 * Calcula o valor a pagar pelo tempo de estadia naquele parque.
 * @param tempo_min O tempo que passou em minutos.
 * @param precoX O preço a cobrar por 15 minutos até 1 hora.
 * @param precoY O preço a cobrar por 15 minutos após 1 hora.
 * @param precoZ O preço maximo a cobrar por dia.
 * @return O valor da fatura a pagar pelo tempo.
*/
float faturaVeiculo(int tempo_min, float precoX, float precoY, float precoZ) {
    float fatura_dias, fatura_ultimo_dia = 0;
    int dias, tempo_res, quarto_hora;
    dias = tempo_min / MINUTOS_DIA;
    tempo_res = tempo_min % MINUTOS_DIA;
    quarto_hora = tempo_res / MINUTOS_QUARTO;
    tempo_res = tempo_res % MINUTOS_QUARTO;
    fatura_dias = dias * precoZ;
    if (quarto_hora >= 4) {
        fatura_ultimo_dia += 4 * precoX + (quarto_hora - 4) * precoY;
        if (tempo_res > 0) {
            fatura_ultimo_dia += precoY;
        }
    } else {
        fatura_ultimo_dia += quarto_hora * precoX;
        if (tempo_res > 0) {
            fatura_ultimo_dia += precoX;
        }
    }
    /** Se a fatura do ultimo dia for superior ao valor maximo, cobra maximo*/
    if (fatura_ultimo_dia > precoZ) {
        fatura_ultimo_dia = precoZ;
    }
    return fatura_dias + fatura_ultimo_dia;
}


/**
 * Calcula o tamanho da lista de parques, percorrendo a lista de parques.
 * @param primeiroParque O ponteiro para o primeiro parque.
 * @return O tamanho da lista de parques.
*/
int tamanhoListaParques(Parque *primeiroParque) {
    int tamanho = 0;
    Parque *atual = primeiroParque;
    /** Percorre todos os parques */
    while (atual != NULL) {
        tamanho++;
        atual = atual->next;
    }
    return tamanho;
}


/**
 * Cria uma lista dos nomes dos parques.
 * @param primeiroParque O ponteiro do primeiro parque.
 * @return A lista dos nomes dos parques.
*/
char** listaNomesParques(Parque *primeiroParque) {
    int numParques;
    Parque *parqueAtual = primeiroParque;
    char **nomes;
    numParques = tamanhoListaParques(primeiroParque);
    /** aloca a memoria para a lista de nomes. */
    nomes = (char**)malloc(numParques * sizeof(char*));
    parqueAtual = primeiroParque;
    int i = 0;
    /** Percorre todos os parques */
    while (parqueAtual != NULL) {
        /** strdup aloca e copia a string */
        nomes[i] = strdup(parqueAtual->nome);
        i++;
        parqueAtual = parqueAtual->next;
    }
    return nomes;
}


/**
 * Troca os valores de duas strings.
 * @param a O endereço da primeira string.
 * @param b O endereço da segunda string.
*/
void troca_strings(char **a, char **b) {
    char *aux = *a;
    *a = *b;
    *b = aux;
}


/**
 * Ordena uma lista de strings usando o algoritmo bubble sort.
 * @param lista_strings O array de strings a ser ordenado.
 * @param tamanho_lista O tamanho da lista de strings.
*/
void bubble_sort(char **lista_strings, int tamanho_lista) {
    int i, j;
    for (i = 0; i < tamanho_lista - 1; i++) {
        for (j = 0; j < tamanho_lista - i - 1; j++) {
            if (strcmp(lista_strings[j], lista_strings[j + 1]) > 0) {
                troca_strings(&lista_strings[j], &lista_strings[j + 1]);
            }
        }
    }
}


/**
 * Cria uma lista de nós de veículo ordenada por data de saída.
 * @param parqueAtual O parque atual do qual se deseja criar a lista.
 * @return Um ponteiro para a lista de veículos ordenada pela data de saída.
*/
VeiculoNode* criaListaVporSaida(Parque* parqueAtual) {
    VeiculoNode *veiculoAtual = parqueAtual->veiculos_head, *lista = NULL, 
    *veiculoAnterior, *veiculoNaLista, *novoVeiculoNode;
    while (veiculoAtual != NULL) {
        if (veiculoAtual->veiculo->data_s.dia == 0) {
            veiculoAtual = veiculoAtual->next;
            continue;
        }
        veiculoAnterior = NULL;
        veiculoNaLista = lista;
        /** Procura o local correto para inserir o veículo na lista ordenada*/
        while (veiculoNaLista != NULL && converteData(veiculoAtual->veiculo->
        data_s) > converteData(veiculoNaLista->veiculo->data_s)) {
            veiculoAnterior = veiculoNaLista;
            veiculoNaLista = veiculoNaLista->next;
        }
        /** aloca a memoria para o nó do veiculo. */
        novoVeiculoNode = malloc(sizeof(VeiculoNode));
        /** define os valores do novo nó do veiculo. */
        novoVeiculoNode->veiculo = veiculoAtual->veiculo;
        novoVeiculoNode->next = NULL;
        if (veiculoAnterior == NULL) {
            novoVeiculoNode->next = lista;
            lista = novoVeiculoNode;
        } else {
            veiculoAnterior->next = novoVeiculoNode;
            novoVeiculoNode->next = veiculoNaLista;
        }
        veiculoAtual = veiculoAtual->next;
    }
    return lista;
}


/**
 * Remove todos os nós de uma lista encadeada de veículos e liberta a memória 
   alocada para cada nó da lista de veículos.
 * @param veiculos O ponteiro para o primeiro nó da lista de veículos.
*/
void removeNode(VeiculoNode *veiculos) {
    VeiculoNode *proximoNode;
    /** Percorre todos os nós dos veiculos e liberta o nó*/
    while (veiculos != NULL) {
        proximoNode = veiculos->next;
        free(veiculos);
        veiculos = proximoNode;
    }
}


/**
 * Remove todos os veículos e nós de uma lista encadeada de veículos e liberta 
   a memória alocada para cada veículo e nó da lista de veículos.
 * @param veiculos O ponteiro para o primeiro nó da lista de veículos.
 */
void removeVeiculos(VeiculoNode *veiculos) {
    VeiculoNode *proximoNode;
    /** Percorre todos os nós dos veiculos e liberta o veiculo e o nó*/
    while (veiculos != NULL) {
        proximoNode = veiculos->next;
        free(veiculos->veiculo);
        free(veiculos);
        veiculos = proximoNode;
    }
}


/**
 * Liberta a memória alocada para uma lista de strings e para a própria lista.
 * @param Lista O array de strings a ser libertada da memória.
 * @param tamanho O tamanho da lista de strings.
*/
void removeChar(char **Lista, int tamanho) {
    int i = 0;
    /** Percorre todos os nomes e liberta-os*/
    while (i < tamanho) {
        free(Lista[i]);
        i++;
    } 
    free(Lista);
}


/**
 * Remove um parque da lista de parques, libertando a memória alocada para o 
   parque e os seus veículos.
 * @param parqueRemover O ponteiro para o parque a ser removido.
 * @param primeiroParquePtr O endereço do ponteiro para o primeiro parque.
*/
void removeParque(Parque *parqueRemover, Parque **primeiroParquePtr) {
    VeiculoNode *ListaV;
    Parque *parqueAtual;
    ListaV = parqueRemover->veiculos_head;
    /** remove os veiculos da lista*/
    removeVeiculos(ListaV);
    /** atualiza os ponteiros removendo o ponteiro do parque a remover*/
    if (*primeiroParquePtr == parqueRemover) {
        *primeiroParquePtr = parqueRemover->next;
    } else {
        parqueAtual = *primeiroParquePtr;
        while (parqueAtual->next != NULL && parqueAtual->next != parqueRemover) {
            parqueAtual = parqueAtual->next;
        }
        parqueAtual->next = parqueRemover->next;
    }
    free(parqueRemover);
}


/**
 * Remove todos os parques da lista de parques, libertando a memória alocada 
   para cada parque e os seus veículos.
 * @param primeiroParquePtr O endereço do ponteiro para o primeiro parque.
*/
void removeTodosParques(Parque **primeiroParquePtr) {
    VeiculoNode *ListaV;
    Parque *parqueRemover = *primeiroParquePtr, *proximoParque;
    /** percorre todos os parques*/
    while (parqueRemover != NULL) {
        proximoParque = parqueRemover->next;
        ListaV = parqueRemover->veiculos_head;
        /** remove os veiculos da lista*/
        removeVeiculos(ListaV);
        /** remove o parque*/
        free(parqueRemover);
        parqueRemover = proximoParque;
    }
    /** redefine o primeiro ponteiro para nulo*/
    *primeiroParquePtr = NULL;
}


/**
 * Imprime os nomes, capacidade e disponibilidade de todos os parques.
 * @param primeiroParquePtr O endereço do ponteiro para o primeiro parque.
*/
void printParques(Parque **primeiroParquePtr) {
    Parque *parqueAtual = *primeiroParquePtr;
    /** percorre todos os parques */
    while (parqueAtual != NULL) {
        printf("%s %d %d\n", parqueAtual->nome, parqueAtual->capacidade, 
        lugares_disponiveis(parqueAtual));
        parqueAtual = parqueAtual->next;
    }
}


/**
 * Adiciona um novo parque à lista de parques.
 * @param primeiroParquePtr O endereço do ponteiro para o primeiro parque.
 * @param novoParque O ponteiro para o novo parque a ser adicionado à lista.
*/
void adicionaParque(Parque **primeiroParquePtr, Parque *novoParque) {
    Parque *parqueAtual = *primeiroParquePtr;
    /** 
     * se não há parques, adiciona o novo parque como primeiro 
     * se há parques, adiciona o novo parque à frente do anterior
    */
    if (*primeiroParquePtr == NULL) {
        *primeiroParquePtr = novoParque;
    } else {
        parqueAtual = *primeiroParquePtr;
        while (parqueAtual->next != NULL) {
            parqueAtual = parqueAtual->next;
        }
        parqueAtual->next = novoParque;
    }
}


/**
 * Verifica se os dados fornecidos para um novo parque são válidos e se não há 
   conflitos com parques existentes.
 * @param primeiroParquePtr O endereço do ponteiro para o primeiro parque.
 * @param nome O nome do novo parque a ser verificado.
 * @param capacidade A capacidade do novo parque a ser verificada.
 * @param precoX O preço X do novo parque a ser verificado.
 * @param precoY O preço Y do novo parque a ser verificado.
 * @param precoZ O preço Z do novo parque a ser verificado.
 * @return 1 se os dados do novo parque são válidos e 0 caso contrário.
*/
int errosP(Parque **primeiroParquePtr, char *nome, int capacidade, 
float precoX, float precoY, float precoZ) {
    int contador = 0;
    Parque *parqueAtual = *primeiroParquePtr;
    /** percorre todos os parques, confirma se nome existe e conta os parques*/
    while (parqueAtual != NULL) {
        if (strcmp(parqueAtual->nome, nome) == 0) {
            printf("%s: parking already exists.\n", nome);
            return 0;
        }
        contador++;
        parqueAtual = parqueAtual->next;
    }
    if (capacidade <= 0) {
        printf("%d: invalid capacity.\n", capacidade);
        return 0;
    }
    if (!(0 < precoX && precoX < precoY && precoY < precoZ)) {
        printf("invalid cost.\n");
        return 0;
    }
    if (contador >= N_PARQUE_MAX) {
        printf("too many parks.\n");
        return 0;
    }
    return 1;
}


/**
 * Executa o comando 'p', que pode ser usado para imprimir todos os parques ou 
   adicionar um novo parque.
 * @param comando A string com o comando a ser realizado.
 * @param primeiroParquePtr O endereço do ponteiro para o primeiro parque.
*/
void comando_p(char *comando, Parque **primeiroParquePtr) {
    char letraComando, nomeParque[BUFSIZ];
    int capacidade = 0, erro;
    float precoX, precoY, precoZ;
    Parque *novoParque;
    /** Se o comando for composto apenas pela letra do comando só imprime */
    if (strlen(comando) == 2) {
        printParques(primeiroParquePtr);
        return;
    }
    /** 
     * se o nome tiver aspas usa o primeiro caso para ler o comando
     * caso contrario o segundo
    */
    if (comando[2] == '"') {
        sscanf(comando, "%c \"%[^\"]\" %d %f %f %f", &letraComando,
               nomeParque, &capacidade, &precoX, &precoY, &precoZ);
    } else {
        sscanf(comando, "%c %s %d %f %f %f", &letraComando,
               nomeParque, &capacidade, &precoX, &precoY, &precoZ);
    }
    erro = errosP(primeiroParquePtr, nomeParque, capacidade, precoX, 
    precoY, precoZ);
    if (erro == 0) {
        return;
    }
    /** cria e adiciona o parque */
    novoParque = criaParque(nomeParque, precoX, precoY, precoZ, capacidade);
    adicionaParque(primeiroParquePtr, novoParque);
}


/**
 * Verifica se os dados fornecidos para a entrada de um veículo são válidos.
 * @param primeiroParquePtr O endereço do ponteiro para o primeiro parque.
 * @param parqueAlterar O parque onde se deseja efetuar a entrada do veículo.
 * @param nome O nome do parque onde se deseja efetuar a entrada do veículo.
 * @param m A matrícula do veículo a ser verificada.
 * @param data A data de entrada do veículo a ser verificada.
 * @param ultima_data O ponteiro para a última data de alteração registrada.
 * @return 1 se os dados para a entrada do veículo são válidos e 0 caso 
   contrário.
*/
int errosE(Parque **primeiroParquePtr, Parque *parqueAlterar, char *nome, 
Matricula m, Data data, int *ultima_data) {
    if (parqueAlterar == NULL) {
        printf("%s: no such parking.\n", nome);
        return 0;
    }
    if (lugares_disponiveis(parqueAlterar) <= 0) {
        printf("%s: parking is full.\n", nome);
        return 0;
    }
    if (matriculaValida(m) == 0) {
        printf("%s-%s-%s: invalid licence plate.\n", m.par1, m.par2, m.par3);
        return 0;
    }
    if (matriculaDentroQualquerParque(*primeiroParquePtr, m) == 1) {
        printf("%s-%s-%s: invalid vehicle entry.\n", m.par1, m.par2, m.par3);
        return 0;
    }
    if (converteData(data) < *ultima_data || dataValida(data) == 0) {
        printf("invalid date.\n");
        return 0;
    }
    return 1;
}


/**
 * Executa o comando 'e', que é usado para efetuar a entrada de um veículo num 
   parque.
 * @param comando A string contendo o comando e seus argumentos.
 * @param primeiroParquePtr O endereço do ponteiro para o primeiro parque.
 * @param ultima_data O ponteiro para a última data de alteração.
*/
void comando_e(char *comando, Parque **primeiroParquePtr, int *ultima_data) {
    char letraComando, nomeParque[BUFSIZ];
    int erro;
    Matricula matricula;
    Data data_e;
    Parque *parqueAlterar;
    /** 
     * se o nome tiver aspas usa o primeiro caso para ler o comando
     * caso contrario o segundo
    */
    if (comando[2] == '"') {
        sscanf(comando, "%c \"%[^\"]\" %2s-%2s-%2s %2d-%2d-%4d %2d:%2d", 
               &letraComando, nomeParque, matricula.par1, matricula.par2, 
               matricula.par3, &data_e.dia, &data_e.mes, &data_e.ano, 
               &data_e.hora, &data_e.min);
    } else {
        sscanf(comando, "%c %s %2s-%2s-%2s %2d-%2d-%4d %2d:%2d", 
               &letraComando, nomeParque, matricula.par1, matricula.par2, 
               matricula.par3, &data_e.dia, &data_e.mes, &data_e.ano, 
               &data_e.hora, &data_e.min);
    }
    parqueAlterar = encontraPporNome(primeiroParquePtr, nomeParque);
    erro = errosE(primeiroParquePtr, parqueAlterar, nomeParque, 
    matricula, data_e, ultima_data);
    if (erro == 0) {
        return;
    }
    /** Dá entrada do veiculo no parque */
    EntradaVeiculo(parqueAlterar, matricula, data_e);
    /** Dá print dos dados atualizados do parque */
    printf("%s %d\n", nomeParque, lugares_disponiveis(parqueAlterar));
    /** atualiza a ultima data do sistema */
    *ultima_data = converteData(data_e);
}


/**
 * Verifica se existem erros nos dados fornecidos para a saída de um veículo de
   um parque.
 * @param parqueAlterar O parque do qual se deseja efetuar a saída do veículo.
 * @param nome O nome do parque do qual se deseja efetuar a saída do veículo.
 * @param m A matrícula do veículo que se deseja retirar do parque.
 * @param data A data de saída do veículo do parque.
 * @param ultima_data O ponteiro para a última data de alteração.
 * @return 1 se não houver erros nos dados fornecidos, 0 caso contrário.
*/
int errosS (Parque *parqueAlterar, char *nome, Matricula m, Data data, 
int *ultima_data) {
    if (parqueAlterar == NULL) {
        printf("%s: no such parking.\n", nome);
        return 0;
    }
    if (matriculaValida(m) == 0) {
        printf("%s-%s-%s: invalid licence plate.\n", m.par1, m.par2, m.par3);
        return 0;
    }
    if (matriculaDentroParque(parqueAlterar, m) == 0) {
        printf("%s-%s-%s: invalid vehicle exit.\n", m.par1, m.par2, m.par3);
        return 0;
    }
    if (converteData(data) < *ultima_data || dataValida(data) == 0) {
        printf("invalid date.\n");
        return 0;
    }
    return 1;
}


/**
 * Calcula a fatura do veículo e atualiza a data de saída no parque.
 * @param parqueAtual O parque onde o veículo está estacionado.
 * @param m A matrícula do veículo.
 * @param data_s A data de saída do veículo do parque.
*/
void FaturaEAtualizaVeiculo (Parque *parqueAtual, Matricula m, Data data_s) {
    float fatura, precoX, precoY, precoZ;
    int tempo_min;
    Data data_e;
    VeiculoNode* ListaV;
    Veiculo* ultimoV;
    ListaV = encontraListaVMatricula(parqueAtual, m);
    /** encontra o ultimo veiculo da lista de veiculos com a matricula*/
    ultimoV = ultimoVeiculoLista(ListaV);
    /** atualiza a data de saida*/
    ultimoV->data_s = data_s;
    /** descobre a data de entrada do mesmo veiculo*/
    data_e = ultimoV->data_e;
    tempo_min = converteData(data_s) - converteData(data_e);
    precoX = parqueAtual->precoX;
    precoY = parqueAtual->precoY;
    precoZ = parqueAtual->precoZ;
    fatura = faturaVeiculo(tempo_min, precoX, precoY, precoZ);
    /** Imprime os dados do veiculo que saiu */
    printf("%s-%s-%s %02d-%02d-%04d %02d:%02d %02d-%02d-%04d %02d:%02d %.2f\n", 
           m.par1, m.par2, m.par3, data_e.dia, data_e.mes, data_e.ano, 
           data_e.hora, data_e.min, data_s.dia, data_s.mes, data_s.ano, 
           data_s.hora, data_s.min, fatura);
    /** Dá free da memoria alocada para a criação da lista de veiculos */
    removeNode(ListaV);
}


/**
 * Processa o comando 's' para registrar a saída de um veículo do parque e 
   calcular a sua fatura.
 * @param comando A string contendo o comando de saída.
 * @param primeiroParquePtr O ponteiro para o primeiro parque.
 * @param ultima_data O ponteiro para a última data de alteração.
*/
void comando_s(char *comando, Parque **primeiroParquePtr, int *ultima_data) {
    char letraComando, nomeParque[BUFSIZ];
    Matricula matricula;
    Data data_s;
    int erro;
    Parque *parqueAlterar;
    /** 
     * se o nome tiver aspas usa o primeiro caso para ler o comando
     * caso contrario o segundo
    */
    if (comando[2] == '"') {
        sscanf(comando, "%c \"%[^\"]\" %2s-%2s-%2s %2d-%2d-%4d %2d:%2d", 
               &letraComando, nomeParque, matricula.par1, matricula.par2, 
               matricula.par3, &data_s.dia, &data_s.mes, &data_s.ano, 
               &data_s.hora, &data_s.min);
    } else {
        sscanf(comando, "%c %s %2s-%2s-%2s %2d-%2d-%4d %2d:%2d", &letraComando, 
               nomeParque, matricula.par1, matricula.par2, matricula.par3, 
               &data_s.dia, &data_s.mes, &data_s.ano, &data_s.hora, &data_s.min);
    }
    parqueAlterar = encontraPporNome(primeiroParquePtr, nomeParque);
    erro = errosS(parqueAlterar, nomeParque, matricula, data_s, ultima_data);
    if (erro == 0) {
        return;
    }
    FaturaEAtualizaVeiculo (parqueAlterar, matricula, data_s);
    /** atualiza a ultima data do sistema */
    *ultima_data = converteData(data_s);
}


/**
 * Imprime os veículos estacionados num determinado parque com uma dada 
   matrícula.
 * @param primeiroParquePtr O ponteiro para o primeiro parque.
 * @param nomes Um array de strings contendo os nomes dos parques.
 * @param m A matrícula dos veículos a serem impressos.
 * @param i O índice do parque dentro do array de nomes.
*/
void printVeiculos(Parque **primeiroParquePtr, char **nomes, Matricula m, 
int i) {
    Data data_e, data_s;
    Parque* parqueAtual = encontraPporNome(primeiroParquePtr, nomes[i]);
    VeiculoNode* veiculos = encontraListaVMatricula(parqueAtual, m);
    VeiculoNode* veiculosParaRemover = veiculos;
    /** Percorre todos os veiculos da lista */
    while (veiculos != NULL) {
        data_e = veiculos->veiculo->data_e;
        data_s = veiculos->veiculo->data_s;
        /** 
         * se o veiculo tiver data de saida associada imprime com a mesma
         * caso contrario não a imprime
        */
        if (data_s.dia != 0) {
            printf("%s %02d-%02d-%04d %02d:%02d %02d-%02d-%04d %02d:%02d\n", 
                   nomes[i], data_e.dia, data_e.mes, data_e.ano, 
                   data_e.hora, data_e.min, data_s.dia, data_s.mes, 
                   data_s.ano, data_s.hora, data_s.min);
        } else {
            printf("%s %02d-%02d-%04d %02d:%02d\n", nomes[i], 
                   data_e.dia, data_e.mes, data_e.ano, data_e.hora, 
                   data_e.min);
        }
        veiculos = veiculos->next;
    }
    /** Dá free da memoria alocada para a criação da lista de veiculos */
    removeNode(veiculosParaRemover);
}


/**
 * Executa o comando 'v', que imprime os veículos de uma determinada matrícula
   estacionados em todos os parques.
 * @param comando A string que contem o comando completo.
 * @param primeiroParquePtr O ponteiro para o primeiro parque.
*/
void comando_v(char *comando, Parque **primeiroParquePtr) {
    char letraComando;
    int i = 0, tamanho;
    Matricula matricula;
    char **nomes;
    sscanf(comando, "%c %2s-%2s-%2s", &letraComando, matricula.par1, 
           matricula.par2, matricula.par3);
    if (matriculaValida(matricula) == 0) {
        printf("%s-%s-%s: invalid licence plate.\n", matricula.par1, 
        matricula.par2, matricula.par3);
        return;
    }
    if (matriculaNaoExistenteParque(*primeiroParquePtr, matricula) == 0) {
        printf("%s-%s-%s: no entries found in any parking.\n", matricula.par1, 
        matricula.par2, matricula.par3);
        return;
    }
    /** cria uma lista de nomes e ordena pelo mesmo */
    nomes = listaNomesParques(*primeiroParquePtr);
    tamanho = tamanhoListaParques(*primeiroParquePtr);
    bubble_sort(nomes, tamanho);
    /** percorre todos os nomes da lista */
    while (i < tamanho) {
        printVeiculos(primeiroParquePtr, nomes, matricula, i);
        i++;
    }
    /** Dá free da memoria alocada para a criação da lista de nomes */
    removeChar(nomes, tamanho);
}


/**
 * Calcula e imprime o valor faturado num parque por dia até à ultima saida.
 * @param veiculoAtual O ponteiro para o nó de veículo atual.
 * @param pX O preço por 15 minutos até 1 hora.
 * @param pY O preço por 15 minutos após 1 hora.
 * @param pZ O preço máximo cobrado por dia.
 * @param ultima_data O ponteiro para a última data de alteração.
*/
void faturaSemDia(VeiculoNode *veiculoAtual, float pX, float pY, float pZ, 
int *ultima_data) {
    float fatura;
    int tempo_min, data_e_min, data_s_min, dataAtual_min, dataAtualFinal_min;
    Data dataAtualFinal, dataAtual = veiculoAtual->veiculo->data_s;
    /** define as datas do intervalo */
    dataAtualFinal = diaSeguinte(dataAtual);
    dataAtual_min = converteData(dataAtual);
    dataAtualFinal_min = converteData(dataAtualFinal);
    /** enquanto a data inicial do intervalo for menor que a da ultima 
    alteração */
    while (dataAtual_min < *ultima_data) {
        /** faz reset do valor da fatura */
        fatura = 0;
        /** percorre os veiculos */
        while (veiculoAtual != NULL) {
            data_e_min = converteData(veiculoAtual->veiculo->data_e);
            data_s_min = converteData(veiculoAtual->veiculo->data_s);
            /** Se a data de saida estiver no intervalo incrementa a fatura */
            if (data_s_min < dataAtualFinal_min && 
            data_s_min >= dataAtual_min) {
                tempo_min = data_s_min - data_e_min;
                fatura += faturaVeiculo(tempo_min, pX, pY, pZ);
                veiculoAtual = veiculoAtual->next;
            } else {break;}
        }
        /** se a fatura for diferente de 0 imprime a mesma com a data inicial 
        do intervalo*/
        if (fatura != 0) {
            printf("%02d-%02d-%04d %.2f\n", dataAtual.dia, dataAtual.mes, 
            dataAtual.ano, fatura);
        }
        /** atualiza as datas de intervalo */
        dataAtual_min = dataAtualFinal_min;
        dataAtualFinal_min += MINUTOS_DIA;
        dataAtual = diaSeguinte(dataAtual);
    }
}


/**
 * Calcula e imprime a fatura para veículos que sairam num determinado dia.
 * @param veiculoAtual O ponteiro para o nó de veículo atual.
 * @param pX O preço por 15 minutos até 1 hora.
 * @param pY O preço por 15 minutos após 1 hora.
 * @param pZ O preço máximo cobrado por dia.
 * @param data A data para a qual se deseja calcular a fatura.
 * @param ultima_data O ponteiro para a última data de alteração.
*/
void faturaComDia(VeiculoNode *veiculoAtual, float pX, float pY, float pZ, 
Data data, int *ultima_data) {
    float fatura;
    int tempo_min, data_e_min, data_s_min, dataAtualFinal_min, data_min;
    Data dataAtualFinal;
    /** define as datas do intervalo */
    data_min = converteData(data);
    dataAtualFinal = diaSeguinte(data);
    dataAtualFinal_min = converteData(dataAtualFinal);
    if (data_min > *ultima_data || dataValida(data) == 0) {
        printf("invalid date.\n");
        return;
    }
    /** percorre os veiculos */
    while (veiculoAtual != NULL) {
        data_s_min = converteData(veiculoAtual->veiculo->data_s);
        /** Se a data de saida estiver no intervalo imprime a fatura do veiculo
        e a data de saida */
        if (data_s_min >= data_min && data_s_min < dataAtualFinal_min) {
            data_e_min = converteData(veiculoAtual->veiculo->data_e);
            tempo_min = data_s_min - data_e_min;
            fatura = faturaVeiculo(tempo_min, pX, pY, pZ);
            printf("%s-%s-%s %02d:%02d %.2f\n", 
                   veiculoAtual->veiculo->matricula.par1,
                   veiculoAtual->veiculo->matricula.par2,
                   veiculoAtual->veiculo->matricula.par3,
                   veiculoAtual->veiculo->data_s.hora,
                   veiculoAtual->veiculo->data_s.min, fatura);
        }
        veiculoAtual = veiculoAtual->next;
    }
}


/**
 * Processa o comando 'f', que processa as faturas de estacionamento de um 
   parque.
 * @param comando A string que contem o comando.
 * @param primeiroParquePtr O ponteiro para o ponteiro do primeiro parque.
 * @param ultima_data O ponteiro para a última data de alteração.
*/
void comando_f(char *comando, Parque **primeiroParquePtr, int *ultima_data) {
    char letraComando, nomeParque[BUFSIZ];
    Data data = {0, 0, 0, 0, 0};
    Parque *parqueAtual;
    VeiculoNode *veiculoAtual;
    /** 
     * se o nome tiver aspas usa o primeiro caso para ler o comando
     * caso contrario o segundo
    */
    if (comando[2] == '"') {
        sscanf(comando, "%c \"%[^\"]\" %2d-%2d-%4d", &letraComando, nomeParque, 
               &data.dia, &data.mes, &data.ano);
    } else {
        sscanf(comando, "%c %s %2d-%2d-%4d", &letraComando, nomeParque, 
               &data.dia, &data.mes, &data.ano);
    }
    parqueAtual = encontraPporNome(primeiroParquePtr, nomeParque);
    if (parqueAtual == NULL) {
        printf("%s: no such parking.\n", nomeParque);
        return;
    }
    veiculoAtual = criaListaVporSaida(parqueAtual);
    /** 
     * se não for indicada uma data no comando usa o primeiro caso para fazer a 
       fatura
     * caso contrario o segundo
    */
    if (data.dia == 0) {
        faturaSemDia(veiculoAtual, parqueAtual->precoX, parqueAtual->precoY, 
        parqueAtual->precoZ, ultima_data);
    } else {
        faturaComDia(veiculoAtual, parqueAtual->precoX, parqueAtual->precoY, 
        parqueAtual->precoZ, data, ultima_data);
    }
    /** Dá free da memoria alocada para a criação da lista de veiculos */
    removeNode(veiculoAtual);
}


/**
 * Processa o comando 'r', que remove um parque especificado e imprime a lista 
   de parques restantes.
 * @param comando A string que contem o comando.
 * @param primeiroParquePtr O ponteiro para o ponteiro do primeiro parque.
*/
void comando_r(char *comando, Parque **primeiroParquePtr) {
    char letraComando, nomeParque[BUFSIZ];
    int i = 0, tamanho;
    char **nomes;
    Parque *parqueAtual;
    /** 
     * se o nome tiver aspas usa o primeiro caso para ler o comando
     * caso contrario o segundo
    */
    if (comando[2] == '"') {
        sscanf(comando, "%c \"%[^\"]\"", &letraComando, nomeParque);
    } else {
        sscanf(comando, "%c %s", &letraComando, nomeParque);
    }
    parqueAtual = encontraPporNome(primeiroParquePtr, nomeParque);
    if (parqueAtual == NULL || primeiroParquePtr == NULL) {
        printf("%s: no such parking.\n", nomeParque);
        return;
    }
    /** Dá free da memoria alocada do parque e dos seus veiculos */
    removeParque(parqueAtual, primeiroParquePtr);
    /** Cria uma lista ordenada do nomes dos parques */
    nomes = listaNomesParques(*primeiroParquePtr);
    tamanho = tamanhoListaParques(*primeiroParquePtr);
    bubble_sort(nomes, tamanho);
    /** imprime o nome dos parques */
    while (i < tamanho) {
        printf("%s\n", nomes[i]);
        i++;
    }
    /** Dá free da memoria alocada para a criação da lista de nomes */
    removeChar(nomes, tamanho);
}


/**
 * Função principal que lê o comando e usando as funções estabelacidas faz as 
   alterações necessarias.
   @return dá sempre 0 no fim do programa.
*/
int main() {
    char comando[BUFSIZ];
    int running = 1, ultima_data = 0;
    Parque *primeiroParque = NULL;
    while (running) {
        /** lê a linha de texto  e armazená-la na string comando */
        fgets(comando, sizeof(comando), stdin);
        /** consoante a primeira letra do comando aplica o comando 
        correspondente ou no caso do q termina o ciclo */
        switch (comando[0]) {
            case 'q':
                running = 0; break;
            case 'p':
                comando_p(comando, &primeiroParque); break;
            case 'e':
                comando_e(comando, &primeiroParque, &ultima_data); break;
            case 's':
                comando_s(comando, &primeiroParque, &ultima_data); break;
            case 'v':
                comando_v(comando, &primeiroParque); break;
            case 'f':
                comando_f(comando, &primeiroParque, &ultima_data); break;
            case 'r':
                comando_r(comando, &primeiroParque); break;
        }
    }
    /** Dá free da memoria alocada de todos parque e dos seus veiculos */
    removeTodosParques(&primeiroParque);
    return 0;
}