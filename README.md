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
               <li><h5> Instrução NOP </h5>
                 ● OpCode: 0000<br>
                 ● Operando? Não<br>
                 ● Comentário: Não executa nenhuma operação<br>
                 ● Tipo: Operações Diversa<br>
               </li>
               <li><h5> Instrução LDR end </h5>
                 ● OpCode: 0001<br>
                 ● Operando? Sim<br>
                 ● Operação (RTL): AC <-  MEM[ end ]<br>
                 ● Comentário: Carrega valor da memória para AC<br>
                 ● Tipo: Transferência de dados<br>
               </li>
               <li><h5> Instrução STR end </h5>
                 ● OpCode: 0010<br>
                 ● Operando? Sim<br>
                 ● Operação (RTL): MEM[ end ] <-  AC<br>
                 ● Comentário: Armazena na memória o valor do AC<br> 
                 ● Tipo: Transferência de dados<br>                 
               </li>  
             
             
</ul>  
  
</ul>
