# Programa 18 - Cifra de bloco AES usado modo de operação CBC
## O programa cifra e decifra texto de bloco em bloco. Com o modo de operação CBC podemos realizar essa operação para grandes extensões de texto.

A cifra realiza a cifração de blocos de 128 bits com chaves de tamanho 128, 192 ou 256 bits (tamanho da chave ainda a ser definido). Para garantir que grandes quantidades de dados seja cifradas para realizar o benchmark usaremos o modo de operação CBC, que divide o plaintext em váriops blocos de 128 bits, realiza um ou-exclusivo desse plaintext com o ciphertext da cifração anterior e passa esse bloco pelo AES, gerando assim um novo ciphertext:

![alt tag](https://upload.wikimedia.org/wikipedia/commons/8/80/CBC_encryption.svg)

![alt_tag](https://upload.wikimedia.org/wikipedia/commons/2/2a/CBC_decryption.svg)

Podemos esperar que, para boas implementações da cifra, o tempo para realizar uma operação com plaintexts de mesmo tamanho seja a mesma. Se não, que pelo menos a operação para o mesmo plaintext seja a mesma sempre.

## Por que é bom para medir desempenho?

Para grandes tamanhos de input (plaintext/ciphertext) podemos obter bons levantamentos do trabalho do processador, por o trabalho para cifrar cada bloco é relativamente extenso.

Usando grandes textos também podemos esperar uma utilização do disco que afetará o benchmark, visto que existe o trabalho de copiar bloco a bloco do texto para a memória, e então copiar esse bloco de volta para o disco (em forma de ciphertext/plaintext).

Podem existir implementações do AES que fazem uso de aceleradores ou de execução paralela. Nesse caso, se encontramos boas implementações que fazem uso dessas ferramentas, nosso benchmark também poderá fazer uma avaliação disso.

## O que baixar
É necessário baixar a implementação em C do AES e do modo de operação CBC. Ambos se encontram no repositório e foram adaptados da implementação que sem encontra em https://github.com/kokke/tiny-AES128-C

## Como compilar/instalar
Necessário apenas compilar os arquivos fontes. A compilação, realizada com o `gcc`, pode ser feita através do Makefile (`$ make`).

## Como executar
`$ ./aes arq_enc.pt [arq_dec.ct]`

`arq_enc.pt`: arquivo a ser cifrado.

`arq_dec.ct` (OPCIONAL): arquivo a ser decifrado.

Os arquivos utilizados para fazer o benchmark no projeto estão no repositório com os nomes `test500MB.pt` e `test500MB.ct`, ambos tendo, como sugerem seus nomes, 500 MB.

Para gerar os arquivos aleatórios:

```
dd if=/dev/urandom of=test500MB.pt bs=1048576 count=500
```

## Como medir o desempenho
O desempenho é medido principalmente através do tempo de execução das funções de encrypt e decrypt da cifra, e é medido o tempo real e o tempo da CPU. É interessante utilizar estes dois tempos pois podemos avaliar o tempo que o sistema realmente utiliza para realizar a tarefa e o tempo perdido com outras tarefas (cache misses, page faults, branch misses, mudanças de contexto etc).

Sobre o tempo perdido realizando essas outras tarefas, obtemos um levantamento da eficiência da máquina com a utilização da ferramenta `perf`, que utilizando a linha de comando

```
$ perf stat -B ./aes arq_enc.pt [arq_dec.ct]
```

nos mostra a quantidade de ciclos do processador para efetuar todo o programa, o tempo gasto em mudanças de contexto e de cpu (em caso de paralelismo), o tempo gasto com page faults e a quantidade de instruções por clock realizadas na execução.

Para os tempos de execução da CPU a medição pode ser realizada cinco vezes e ser feita a média aritmética. Essa quantidade é apenas para garantir valores mais exatos e um melhor cálculo da margem de erro, pois o tempo obtido com a função `clock_gettime` da biblioteca oficial do C `time.h` retorna valores bastante precisos, e pouca variação nas medições é percebida. Isso, claro, considerando que as medições são feitas com a máquina nos mesmos estados.

Para os tempos reais a mesma média pode ser realizada e obter o tempo gasto sem executação a operação com MEDIA(REAL) - MEDIA(CPU).

Não foi feita uma análise estatística para chegar a esse valor, mas avaliando os valores obtidos no nosso sistema, a margem de erro está em torno de 5%, tanto para tempo real quanto para o tempo da CPU.

## Como apresentar o desempenho

Considerando que as margens de erro para as funções de encrypt e decrypt não diferem muito, podemos avaliar o desempenho utilizando apenas o tempo para cifrar.

O desempenho é apresentado como:

MÉDIA DE EXECUÇÂO PELA CPU (M) +- ERRO (0.05*M) s

TEMPO GASTO SEM EXECUTAR A TAREFA

FREQUÊNCIA DO PROCESSADOR E INSTRUÇÔES POR CICLO (obtidos pelo perf)


## Medições base (uma máquina)

Especificações mais relevantes do sistema utilizado: (utilizando `lshw`)

```
OS: 4.8.13-1-ARCH x86_64 GNU/Linux
```

```
description: Portable Computer
product: Vostro 3560
```
```
-cpu
          version: Intel(R) Core(TM) i7-3632QM CPU @ 2.20GHz
          size: 1375MHz
          capacity: 4GHz
          width: 64 bits
          clock: 100MHz
```
```
*-memory
          size: 8GiB
        *-bank:0
             description: SODIMM DDR3 Synchronous 1600 MHz (0.6 ns)
             size: 4GiB
             width: 64 bits
             clock: 1600MHz (0.6ns)
        *-bank:1
             description: SODIMM DDR3 Synchronous 1600 MHz (0.6 ns)
             size: 4GiB
             width: 64 bits
             clock: 1600MHz (0.6ns)
```

Valores obtidos (todos obtidos para uma entrada a ser cifrada de 500 MB):

Média: 22.9681 +- 1.1484 s
Tempo desperdiçado: 0.0009 s
Frequência: 3.060 GHz
IPC: 2.40
