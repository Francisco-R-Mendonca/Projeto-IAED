/**
 * Lista as constantes e estruturas de dados usados ao longo do programa.
 * @file project.h
 * @author ist1109264
*/
#ifndef PROJECT_H
#define PROJECT_H

/** Numero maximo de parques. */
#define N_PARQUE_MAX 20

/** Numero de minutos num ano. */
#define MINUTOS_ANO 525600

/** Numero de minutos num dia. */
#define MINUTOS_DIA 1440

/** Numero de minutos numa hora. */
#define MINUTOS_HORA 60

/** Numero de minutos num quarto de hora. */
#define MINUTOS_QUARTO 15

/** Numero do ano maximo. */
#define ANO_MAX 9999

/** Numero do mes maximo, após o 12 o ano muda. */
#define MES_MAX 12

/** Numero da hora maxima, após as 23 o dia muda. */
#define HORA_MAX 23

/** Numero do minuto maximo, após as 59 a hora muda. */
#define MIN_MAX 59

/** Estrutura correspondente às datas. */
typedef struct Data {
    int dia;
    int mes;
    int ano;
    int hora;
    int min;
} Data;

/** Estrutura correspondente às matriculas dos veiculos. */
typedef struct Matricula {
    char par1[3];
    char par2[3];
    char par3[3];
} Matricula;

/** Estrutura correspondente ao veiculo. */
typedef struct Veiculo {
    Matricula matricula;
    Data data_e;
    Data data_s;
    struct Veiculo *next;
} Veiculo;

/** Estrutura correspondente à lista de nós dos veiculos. */
typedef struct VeiculoNode {
    Veiculo *veiculo;
    struct VeiculoNode *next;
} VeiculoNode;

/** Estrutura correspondente ao parque. */
typedef struct Parque {
    char nome[BUFSIZ];
    float precoX;
    float precoY;
    float precoZ;
    int capacidade;
    VeiculoNode *veiculos_head;
    struct Parque *next;
} Parque;

#endif