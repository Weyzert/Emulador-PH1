<h1><bold> Emulador-PH1 </bold> </h1>
<h2> Trabalho de Arquitetura e Organização de Computadores I, ministrada pelo Prof. Me. Marcos Jose Brusso, na Universidade de Passo Fundo - UPF </h2>
<h5><bold>Nome:</bold> Pedro Marcelo Roso Manica</h5> <h5><bold>Matrícula:</bold> 173722</h5>
<ul>
  
<li><h3>Entrada</h3></li>
<p>A entrada é composta por um arquivo-texto(.txt) contendo uma série de linhas. Cada linha correspondente ao conteúdo inicial de um endereço da memória do PH1 e é representada por um endereço e um valor (ambos em hexadecimal) separados por um espaço em branco. Os valores iniciais de todos os endereços de memórias não informados, assim como de todos os registradores serão 00 (zero). O nome do arquivo de entrada não é fixo dentro do programa, mas informado pelo usuário em tempo de execução.</p>
<ul>
  <li><h4><bold>Exemplo de entrada (arquivo "entrada01.txt")</bold></h4></li>
             00 10<br>
             01 81<br>
             02 30<br>
             03 82<br>
             04 20<br>
             05 80<br>
             06 F0<br>
             80 00<br>
             81 05<br>
             82 02<br>
  <li><h4>Comandos validos para a entrada</h4></li>
             <ul>
               <li><h5> Instrução NOP (00) </h5>
                 ● OpCode: 0000<br>
                 ● Operando? Não<br>
                 ● Comentário: Não executa nenhuma operação<br>
                 ● Tipo: Operações Diversa<br>
               </li>
               <li><h5> Instrução LDR end (01) </h5>
                 ● OpCode: 0001<br>
                 ● Operando? Sim<br>
                 ● Operação (RTL): AC <-  MEM[ end ]<br>
                 ● Comentário: Carrega valor da memória para AC<br>
                 ● Tipo: Transferência de dados<br>
               </li>
               <li><h5> Instrução STR end (02) </h5>
                 ● OpCode: 0010<br>
                 ● Operando? Sim<br>
                 ● Operação (RTL): MEM[ end ] <-  AC<br>
                 ● Comentário: Armazena na memória o valor do AC<br> 
                 ● Tipo: Transferência de dados<br>                 
               </li>  
               <li><h5> Instrução ADD end (03) </h5>
                 ● OpCode: 0011<br> 
                 ● Operando? Sim<br> 
                 ● Operação (RTL): AC <- AC +  MEM[ end ]<br>   
                 ● Comentário: Soma<br>  
                 ● Tipo: Operação aritmética<br> 
               </li>
               <li><h5> Instrução SUB end (04) </h5>
                 ● OpCode: 0100<br>  
                 ● Operando? Sim<br>  
                 ● Operação (RTL): AC <- AC -  MEM[ end ]<br>   
                 ● Comentário: Subtração<br>  
                 ● Tipo: Operação aritmétic<br>
               </li>
               <li><h5> Instrução MUL end (05) </h5>
                 ● OpCode: 0101<br> 
                 ● Operando? Sim<br> 
                 ● Operação (RTL): AC <- AC *  MEM[ end ]<br>  
                 ● Comentário: Multiplicação<br> 
                 ● Tipo: Operação aritmética<br>
               </li> 
               <li><h5> Instrução DIV end (06) </h5>
                 ● OpCode: 0110<br>
                 ● Operando? Sim<br> 
                 ● Operação (RTL): AC <- AC /  MEM[ end ]<br>  
                 ● Comentário: Divisão<br> 
                 ● Tipo: Operação aritmética<br>
               </li>
               <li><h5> Instrução NOT (07) </h5>
                 ● OpCode: 0111<br>
                 ● Operando? Não<br> 
                 ● Operação (RTL): AC <- !AC<br> 
                 ● Comentário: “Não” lógico<br> 
                 ● Tipo: Operação lógica bit-a-bit<br>                 
               </li>
               <li><h5> Instrução AND end (08) </h5>
                 ● OpCode: 1000<br>
                 ● Operando? Sim<br> 
                 ● Operação (RTL): AC <- AC & MEM[ end ]<br> 
                 ● Comentário: “E” lógico<br> 
                 ● Tipo: Operação lógica bit-a-bit<br>
               </li>
               <li><h5> Instrução OR end (09) </h5>
                 ● OpCode: 1001<br> 
                 ● Operando? Sim<br> 
                 ● Operação (RTL): AC <- AC | MEM[ end ]<br> 
                 ● Comentário: “OU” lógico<br> 
                 ● Tipo: Operação lógica bit-a-bit<br>
               </li>
               <li><h5> Instrução XOR end (0A) </h5>
                 ● OpCode: 1010<br> 
                 ● Operando? Sim<br> 
                 ● Operação (RTL): AC <- AC ^ MEM[ end ]<br> 
                 ● Comentário: “OU exclusivo” lógico<br> 
                 ● Tipo: Operação lógica bit-a-bit<br>
               </li>
               <li><h5> Instrução JMP end (0B) </h5>
                 ● OpCode: 1011<br>  
                 ● Operando? Sim<br>  
                 ● Operação (RTL): PC <- end<br>  
                 ● Comentário: Desvio incondicional<br>  
                 ● Tipo: Desvio (transferência de controle)<br> 
               </li>
               <li><h5> Instrução JEQ end (0C) </h5>
                 ● OpCode: 1100<br> 
                 ● Operando? Sim<br> 
                 ● Operação (RTL): Se(AC==0) PC <- end<br> 
                 ● Comentário: Desvio condicional, caso AC seja igual a zero<br> 
                 ● Tipo: Desvio (transferência de controle)<br>
               </li>
               <li><h5> Instrução JG end (0D) </h5>
                 ● OpCode: 1101<br> 
                 ● Operando? Sim<br> 
                 ● Operação (RTL): Se(AC>0) PC <- end<br> 
                 ● Comentário: Desvio condicional, caso AC seja maior que zero<br> 
                 ● Tipo: Desvio (transferência de controle)<br>
               </li>
               <li><h5> Instrução JL end (0E) </h5>
                 ● OpCode: 1110<br> 
                 ● Operando? Sim<br> 
                 ● Operação (RTL): Se(AC<0) PC <- end<br> 
                 ● Comentário: Desvio condicional, caso AC seja menor que zero<br> 
                 ● Tipo: Desvio (transferência de controle)<br>
               </li>
               <li><h5> Instrução HLT (0F) </h5>
                 ● OpCode: 1111<br> 
                 ● Operando? Não<br> 
                 ● Comentário: Término da execução<br> 
                 ● Tipo: Operações Diversas<br>
               </li>
             </ul>  
</ul>
<li><h3>Saída</h3></li>
<p>A lei de saída do programa contem exatamente os seguintes parametros:</p>
   <ul>
     <li>Uma linha com "Input file: " seguido do nome do arquivo de entrada</li>
     <li>Uma linha em branco</li>
     <li>Para cada instrução  executada* uma nova linha contendo:</li>
        <ul>
          <li>O memônico da instrução em letras maiúsculas</li>
          <li>Um espaço em branco</li>
          <li>O operando (se houver) em hexadecimal, com dois dígitos</li>
          <li>" ; "</li>
          <li>A descrição da instrução em RTL</li>
        </ul>
      <li>Uma linha em branco</li>
      <li>N " instructions executed", onde N é o número total de instruções executadas</li>
      <li>Uma linha em branco</li>
      <li>Uma linha contendo "Registers:"</li>
      <li>"AC: " seguido do valor final do registrador AC, em hexadecimal, com dois dígitos</li>
      <li>"PC: " seguido do valor final do registrador PC, em hexadecimal, com dois dígitos</li>
      <li>Uma linha em branco</li>
      <li>Uma linha contendo "Memory:"</li>
      <li>Para cada endereço de memória que tenha sido modificado (escrito) durante a execução do programa, uma linha contendo:</li>
         <ul>
           <li>O endereço de memória, em hexadecimal, com dois dígitos</li>
           <li>Um espaço em branco</li>
           <li>O valor contido naquele endereço ao final da execução, em hexadecimal, com dois dígitos</li>
         </ul>
   </ul>

</ul>
