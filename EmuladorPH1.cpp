/*
Copyright 2020 Pedro Marcelo Roso Manica

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <iostream>
#include <iomanip>

///----------------------------------------------------------------------Variaveis
int Registrador_de_Dados_da_Memoria;      //RDM
int Registrador_de_Enderecos_da_Memoria;  //REM
int Memoria_1 [ 256 ];                    //perna1
int Memoria_2 [ 256 ];                    //perna2
int Registrador_de_Instrucao;             //RI
int Contador_de_Programa;                 //PC
int Acumulador;                           //AC
///----------------------------------------------------------------------Declara a funcao
void Unidade_Central_de_Processamento ( void );

int main ( int argc, char** argv ) {

    FILE * arquivo;
	int endereco, dado;
///----------------------------------------------------------------------Caso os argumentos forem invalidos
	if ( argc != 2 )
	{
	    std::cerr << "Argumentos invalidos"
	              << std::endl
                  << "Exemplo: a.exe (entrada01.txt)"
                  << std::endl
                  ;
	    return 0;
	}

	arquivo = fopen( argv [ 1 ], "r" );
///----------------------------------------------------------------------Caso nao for possivel abrir o arquivo
	if ( arquivo == NULL )
	{
		std::cerr << "Falha ao abrir o arquivo"
		          << std::endl
		          ;
		return 0;
	}
///----------------------------------------------------------------------Se o arquivo for aberto
	std::cout << "Input file:" << argv [ 1 ]
	          << std::endl
		      ;
///----------------------------------------------------------------------Le todo o arquivo
	while ( !feof ( arquivo ) )
	{
		fscanf(arquivo, "%x %x", &endereco, &dado);
		Memoria_1 [ endereco ] = dado;
		Memoria_2 [ endereco ] = dado;
	}
///----------------------------------------------------------------------Fecha o arquivo
	fclose ( arquivo );
///----------------------------------------------------------------------Inicia a funcao responsavel por manipular os dados
	Unidade_Central_de_Processamento ();
	return 0;

}

void Unidade_Central_de_Processamento ( void ) {

	int i;
	int Contador = 0;

	std::cout << std::endl;
///----------------------------------------------------------------------PC iniciado
	Contador_de_Programa = 0;
///----------------------------------------------------------------------Loop infinito ate que o HLT apareca
	while ( 1 )
	{
		Registrador_de_Enderecos_da_Memoria = Contador_de_Programa;
		Registrador_de_Dados_da_Memoria = Memoria_1 [ Registrador_de_Enderecos_da_Memoria ];
		Contador_de_Programa = Contador_de_Programa + 1;
		Registrador_de_Instrucao = Registrador_de_Dados_da_Memoria;
///----------------------------------------------------------------------Instrucoes que usam apenas 1 endereco
		if ( Registrador_de_Instrucao != 0x00 && Registrador_de_Instrucao != 0x70 && Registrador_de_Instrucao != 0xf0 )
        {
			Registrador_de_Enderecos_da_Memoria = Contador_de_Programa;
			Registrador_de_Dados_da_Memoria = Memoria_1 [ Registrador_de_Enderecos_da_Memoria ];
			Contador_de_Programa = Contador_de_Programa + 1;
		}
///----------------------------------------------------------------------Daki em diante compara os valores
///----------------------------------------------------------------------lidos com a base da funcao e escreve a saida de acordo
		if ( Registrador_de_Instrucao == 0x00 )
        {
			std::cout << "NOP" << ";"
			          << std::endl
			          ;
			Contador = Contador + 1;
			continue;
		}

		if ( Registrador_de_Instrucao == 0x10 )
        {
			std::cout << "LDR " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Registrador_de_Dados_da_Memoria << ";"
			          << "AC <- MEM[" << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Registrador_de_Dados_da_Memoria << "]"
			          << std::endl
			          ;
			Registrador_de_Enderecos_da_Memoria = Registrador_de_Dados_da_Memoria;
			Registrador_de_Dados_da_Memoria = Memoria_1 [ Registrador_de_Enderecos_da_Memoria ];
			Acumulador = Registrador_de_Dados_da_Memoria;
			Contador = Contador + 1;
			continue;
		}

		if ( Registrador_de_Instrucao == 0x20 )
        {
			std::cout << "STR " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Registrador_de_Dados_da_Memoria << ";"
                      << "MEM[" << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Registrador_de_Dados_da_Memoria << "] <- AC"
                      << std::endl
                      ;
			Registrador_de_Enderecos_da_Memoria = Registrador_de_Dados_da_Memoria;
			Registrador_de_Dados_da_Memoria = Acumulador;
			Memoria_1 [ Registrador_de_Enderecos_da_Memoria ] = Registrador_de_Dados_da_Memoria;
			Contador = Contador + 1;
			continue;
		}

		if ( Registrador_de_Instrucao == 0x30 )
        {
			std::cout << "ADD " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Registrador_de_Dados_da_Memoria << ";"
			          << "AC <- AC + MEM[" << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Registrador_de_Dados_da_Memoria << "]"
			          << std::endl
			          ;
			Registrador_de_Enderecos_da_Memoria = Registrador_de_Dados_da_Memoria;
			Registrador_de_Dados_da_Memoria = Memoria_1 [ Registrador_de_Enderecos_da_Memoria ];
			Acumulador = Acumulador + Registrador_de_Dados_da_Memoria;
			Contador = Contador + 1;
			continue;
		}

		if ( Registrador_de_Instrucao == 0x40 )
        {
			std::cout << "SUB " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Registrador_de_Dados_da_Memoria << ";"
			          << "AC <- AC - MEM[" << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Registrador_de_Dados_da_Memoria << "]"
                      << std::endl
                      ;
			Registrador_de_Enderecos_da_Memoria = Registrador_de_Dados_da_Memoria;
			Registrador_de_Dados_da_Memoria = Memoria_1 [ Registrador_de_Enderecos_da_Memoria ];
			Acumulador = Acumulador - Registrador_de_Dados_da_Memoria;
			Contador = Contador + 1;
			continue;
		}

		if ( Registrador_de_Instrucao == 0x50 )
        {
			std::cout << "MUL " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Registrador_de_Dados_da_Memoria << ";"
			          << "AC <- AC * MEM[" << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Registrador_de_Dados_da_Memoria << "]"
			          << std::endl
			          ;
			Registrador_de_Enderecos_da_Memoria = Registrador_de_Dados_da_Memoria;
			Registrador_de_Dados_da_Memoria = Memoria_1 [ Registrador_de_Enderecos_da_Memoria ];
			Acumulador = Acumulador * Registrador_de_Dados_da_Memoria;
			Contador = Contador + 1;
			continue;
		}

		if ( Registrador_de_Instrucao == 0x60 )
        {
			std::cout << "DIV " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Registrador_de_Dados_da_Memoria << ";"
			          << "AC <- AC / MEM[" << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Registrador_de_Dados_da_Memoria << "]"
			          << std::endl
			          ;
			Registrador_de_Enderecos_da_Memoria = Registrador_de_Dados_da_Memoria;
			Registrador_de_Dados_da_Memoria = Memoria_1 [ Registrador_de_Enderecos_da_Memoria ];
			Acumulador = Acumulador / Registrador_de_Dados_da_Memoria;
			Contador = Contador + 1;
			continue;
		}

		if ( Registrador_de_Instrucao == 0x70 )
        {
			std::cout << "NOT" << ";"
			          << "AC <- !AC"
			          << std::endl
                      ;
			Acumulador = ~ Acumulador;
			Contador = Contador + 1;
			continue;
		}

		if ( Registrador_de_Instrucao == 0x80 )
        {
			std::cout << "AND " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Registrador_de_Dados_da_Memoria << ";"
			          << "AC <- AC & MEM[" << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Registrador_de_Dados_da_Memoria << "]"
                      << std::endl
                      ;
			Registrador_de_Enderecos_da_Memoria = Registrador_de_Dados_da_Memoria;
			Registrador_de_Dados_da_Memoria = Memoria_1 [ Registrador_de_Enderecos_da_Memoria ];
			Acumulador = Acumulador & Memoria_1 [ Registrador_de_Dados_da_Memoria ];
			Contador = Contador + 1;
			continue;
		}

		if ( Registrador_de_Instrucao == 0x90 )
        {
			std::cout << "OR " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Registrador_de_Dados_da_Memoria << ";"
			          << "AC <- AC | MEM[" << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Registrador_de_Dados_da_Memoria << "]"
                      << std::endl
                      ;
			Registrador_de_Enderecos_da_Memoria = Registrador_de_Dados_da_Memoria;
			Registrador_de_Dados_da_Memoria = Memoria_1 [ Registrador_de_Enderecos_da_Memoria ];
			Acumulador = Acumulador | Memoria_1 [ Registrador_de_Enderecos_da_Memoria ];
			Contador = Contador + 1;
			continue;
		}

		if ( Registrador_de_Instrucao == 0xA0 )
        {
			std::cout << "XOR " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Registrador_de_Dados_da_Memoria << ";"
			          << "AC <- AC ^ MEM[" << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Registrador_de_Dados_da_Memoria << "]"
			          << std::endl
			          ;
			Registrador_de_Enderecos_da_Memoria = Registrador_de_Dados_da_Memoria;
			Registrador_de_Dados_da_Memoria = Memoria_1 [ Registrador_de_Enderecos_da_Memoria ];
			Acumulador = Acumulador ^ Memoria_1 [ Registrador_de_Dados_da_Memoria ];
			Contador = Contador + 1;
			continue;
		}

		if ( Registrador_de_Instrucao == 0xB0 )
        {
			std::cout << "JMP " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Registrador_de_Dados_da_Memoria << ";"
			          << "PC <- " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Registrador_de_Dados_da_Memoria
			          << std::endl
			          ;
			Contador_de_Programa = Registrador_de_Dados_da_Memoria;
			Contador = Contador + 1;
			continue;
		}

		if ( Registrador_de_Instrucao == 0xC0 )
        {

			std::cout << "JEQ " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Registrador_de_Dados_da_Memoria << ";"
			          << "if (AC==0) PC <- " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Registrador_de_Dados_da_Memoria
			          << std::endl
                      ;

			if( Acumulador == 0 )
			{
				Contador_de_Programa = Registrador_de_Dados_da_Memoria;
			}

			Contador = Contador + 1;
			continue;
		}

		if ( Registrador_de_Instrucao == 0xD0 )
        {
			std::cout << "JG " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Registrador_de_Dados_da_Memoria << ";"
			          << "if (AC>0) PC <- " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Registrador_de_Dados_da_Memoria
			          << std::endl
			          ;

			if( Acumulador > 0 )
			{
				Contador_de_Programa = Registrador_de_Dados_da_Memoria;
			}

			Contador = Contador + 1;
			continue;
		}

		if ( Registrador_de_Instrucao == 0xE0 )
        {
			std::cout << "JL " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Registrador_de_Dados_da_Memoria << ";"
			          << "if (AC<0) PC <- " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Registrador_de_Dados_da_Memoria
			          << std::endl
			          ;

			if( Acumulador < 0 )
            {
				Contador_de_Programa = Registrador_de_Dados_da_Memoria;
			}

			Contador = Contador + 1;
			continue;
		}
///----------------------------------------------------------------------Fim do loop, pois o HLT apareceu
		if ( Registrador_de_Instrucao == 0xF0 )
        {
			std::cout << "HLT" << ";"
			          << std::endl
			          ;
			Contador = Contador + 1;
			break;
		}

	}
///----------------------------------------------------------------------Anteriormente escrevia funcao por funcao
///----------------------------------------------------------------------agora escreve todo o restante da lei da saida(AC e PC)
	std::cout << std::endl
              << Contador << " instructions executed" << std::endl
	          << std::endl
	          << "Registers:"
	          << std::endl
	          << "AC: " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Acumulador
	          << std::endl
	          << "PC: " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Contador_de_Programa
	          << std::endl
	          << std::endl
	          << "Memory:"
	          << std::endl
              ;
///----------------------------------------------------------------------Compara as memorias buscando por enderecos modificados
///----------------------------------------------------------------------Imprimindo o indice e a memoria
	for ( i = 128; i < 255; i++)
    {
		if ( Memoria_2 [ i ] != Memoria_1 [ i ] )
		{
			std::cout << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << i  << " "
			          << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Memoria_1 [ i ]
                      << std::endl
                      ;
		}
	}

}

