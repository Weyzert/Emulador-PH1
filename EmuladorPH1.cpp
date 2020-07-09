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

int RDM;
int REM;
int Memoria_1 [256];
int Memoria_2 [256];
int RI;
int PC;
int AC;

void CPU (void);

int main (int argc, char** argv) {
    FILE * arquivo;
	int endereco, dado;

	if (argc != 2)
	{
	    std::cerr << "Argumentos invalidos"
	              << std::endl
                  << "Exemplo: a.exe (entrada01.txt)"
                  << std::endl
                  ;
	    return 0;
	}

	arquivo = fopen(argv [1], "r");

	if (arquivo == NULL)
	{
		std::cerr << "Falha ao abrir o arquivo"
		          << std::endl
		          ;
		return 0;
	}

	std::cout << std::endl
	          << "Input file:" << argv [1]
	          << std::endl
		      ;

	while (!feof (arquivo))
	{
		fscanf(arquivo, "%x %x", &endereco, &dado);
		Memoria_1 [endereco] = dado;
		Memoria_2 [endereco] = dado;
	}
	fclose (arquivo);
	CPU ();
	return 0;
}

void CPU (void) {
	int i;
	int Contador = 0;
	std::cout << std::endl;
	PC = 0;

	while (true)
	{
		REM = PC;
		RDM = Memoria_1 [REM];
		PC = PC + 1;
		RI = RDM;

		if (RI != 0x00 && RI != 0x70 && RI != 0xf0){
			REM = PC;
			RDM = Memoria_1 [REM];
			PC = PC + 1;
		}

		if (RI == 0x00){
			std::cout << "NOP" << ";" << std::endl;
			Contador++;
			continue;
		}

		if (RI == 0x10){
			std::cout << "LDR " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << RDM << ";"
			          << "AC <- MEM[" << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << RDM << "]" << std::endl;
			REM = RDM;
			RDM = Memoria_1 [REM];
			AC = RDM;
			Contador++;
			continue;
		}

		if (RI == 0x20){
			std::cout << "STR " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << RDM << ";"
                      << "MEM[" << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << RDM << "] <- AC" << std::endl;
			REM = RDM;
			RDM = AC;
			Memoria_1 [REM] = RDM;
			Contador++;
			continue;
		}

		if (RI == 0x30){
			std::cout << "ADD " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << RDM << ";"
			          << "AC <- AC + MEM[" << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << RDM << "]" << std::endl;
			REM = RDM;
			RDM = Memoria_1 [REM];
			AC = AC + RDM;
			Contador++;
			continue;
		}

		if (RI == 0x40){
			std::cout << "SUB " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << RDM << ";"
			          << "AC <- AC - MEM[" << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << RDM << "]" << std::endl;
			REM = RDM;
			RDM = Memoria_1 [REM];
			AC = AC - RDM;
			Contador++;
			continue;
		}

		if (RI == 0x50){
			std::cout << "MUL " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << RDM << ";"
			          << "AC <- AC * MEM[" << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << RDM << "]" << std::endl;
			REM = RDM;
			RDM = Memoria_1 [REM];
			AC = AC * RDM;
			Contador++;
			continue;
		}

		if (RI == 0x60){
			std::cout << "DIV " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << RDM << ";"
			          << "AC <- AC / MEM[" << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << RDM << "]" << std::endl;
			REM = RDM;
			RDM = Memoria_1 [REM];
			AC = AC / RDM;
			Contador++;
			continue;
		}

		if (RI == 0x70){
			std::cout << "NOT" << ";" << "AC <- !AC" << std::endl;
			AC = ~ AC;
			Contador++;
			continue;
		}

		if (RI == 0x80){
			std::cout << "AND " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << RDM << ";"
			          << "AC <- AC & MEM[" << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << RDM << "]" << std::endl;
			REM = RDM;
			RDM = Memoria_1 [REM];
			AC = AC & Memoria_1 [ RDM ];
			Contador++;
			continue;
		}

		if (RI == 0x90){
			std::cout << "OR " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << RDM << ";"
			          << "AC <- AC | MEM[" << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << RDM << "]" << std::endl;
			REM = RDM;
			RDM = Memoria_1 [REM];
			AC = AC | Memoria_1 [REM];
			Contador++;
			continue;
		}

		if (RI == 0xA0){
			std::cout << "XOR " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << RDM << ";"
			          << "AC <- AC ^ MEM[" << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << RDM << "]" << std::endl;
			REM = RDM;
			RDM = Memoria_1 [REM];
			AC = AC ^ Memoria_1 [RDM];
			Contador++;
			continue;
		}

		if (RI == 0xB0){
			std::cout << "JMP " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << RDM << ";"
			          << "PC <- " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << RDM << std::endl;
			PC = RDM;
			Contador++;
			continue;
		}

		if (RI == 0xC0){

			std::cout << "JEQ " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << RDM << ";"
			          << "if (AC==0) PC <- " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << RDM << std::endl;
			if(AC == 0){
				PC = RDM;
			}
			Contador++;
			continue;
		}

		if (RI == 0xD0){
			std::cout << "JG " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << RDM << ";"
			          << "if (AC>0) PC <- " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << RDM << std::endl;
			if(AC > 0){
				PC = RDM;
			}
			Contador++;
			continue;
		}

		if (RI == 0xE0){
			std::cout << "JL " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << RDM << ";"
			          << "if (AC<0) PC <- " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << RDM << std::endl;
			if(AC < 0){
				PC = RDM;
			}
			Contador++;
			continue;
		}
		if (RI == 0xF0){
			std::cout << "HLT" << ";" << std::endl;
			Contador++;
			break;
		}
	}

	std::cout << std::endl
              << std::dec << Contador << " instructions executed" << std::endl
	          << std::endl
              << "Registers:"
	          << std::endl
              << "AC: " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << AC
	          << std::endl
              << "PC: " << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << PC
	          << std::endl
              << std::endl
	          << "Memory:"
	          << std::endl;

	for (i = 128; i < 255; i++){
		if (Memoria_2 [i] != Memoria_1 [i]){
			std::cout << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << i  << " "
			          << std::uppercase << std::setfill ('0') << std::setw (2) << std::hex << Memoria_1 [i]
                      << std::endl;
		}
	}
}
