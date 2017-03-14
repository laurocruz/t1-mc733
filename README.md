# Programa 18 - Cifra de bloco AES usado modo de operação CBC
## O programa cifra e decifra texto de bloco em bloco. Com o modo de operação CBC podemos realizar essa operação para grandes extensões de texto.

A cifra realiza a cifração de blocos de 128 bits com chaves de tamanho 128, 192 ou 256 bits (tamanho da chave ainda a ser definido). Para garantir que grandes quantidades de dados seja cifradas para realizar o benchmark usaremos o modo de operação CBC, que divide o plaintext em váriops blocos de 128 bits, realiza um ou-exclusivo desse plaintext com o ciphertext da cifração anterior e passa esse bloco pelo AES, gerando assim um novo ciphertext:

![alt tag](https://upload.wikimedia.org/wikipedia/commons/8/80/CBC_encryption.svg)

![alt_tag](https://upload.wikimedia.org/wikipedia/commons/2/2a/CBC_decryption.svg)

Podemos esperar que, para boas implementações da cifra, o tempo para realizar uma operação com plaintexts de mesmo tamanho seja a mesma. Se não, que pelo menos a operação para o mesmo plaintext seja a mesma sempre.

## Por que Ã© bom para medir desempenho?

Para grandes tamanhos de input (plaintext/ciphertext) podemos obter bons levantamentos do trabalho do processador, por o trabalho para cifrar cada bloco é relativamente extenso.

Usando grandes textos também podemos esperar uma utilização do disco que afetará o benchmark, visto que existe o trabalho de copiar bloco a bloco do texto para a memória, e então copiar esse bloco de volta para o disco (em forma de ciphertext/plaintext).

Podem existir implementações do AES que fazem uso de aceleradores ou de execução paralela. Nesse caso, se encontramos boas implementações que fazem uso dessas ferramentas, nosso benchmark também poderá fazer uma avaliação disso.

## O que baixar
É necessário baixar a implementação em C do AES e do modo de operação CBC. Ambos se encontram no repositório e foram adaptados da implementação que sem encontra em https://github.com/kokke/tiny-AES128-C

## Como compilar/instalar
Necessário apenas compilar os arquivos fontes. A compilação, realizada com o `gcc`, pode ser feita através do Makefile (`$ make`).

## Como executar
`$ ./aes arq_enc.pt arq_dec.ct`

`arq_enc.pt`: arquivo a ser cifrado.

`arq_dec.ct` (OPCIONAL): arquivo a ser decifrado.

Os arquivos utilizados para fazer o benchmark no projeto estão no repositório com os nomes `test500MB.pt` e `test500MB.ct`, ambos tendo, como sugerem seus nomes, 500 MB.

## Como medir o desempenho
Como que o desempenho Ã© medido atravÃ©s deste programa? Se for atravÃ©s de tempo, vocÃª deve
especificar claramente qual tempo deverÃ¡ ser utilizado e indicar o motivo aqui. Quantas vezes a
medida deverÃ¡ ser feita? O que fazer com ela (mÃ©dia, etc) ? NÃ£o especificar o tempo serÃ¡
considerado falha grave.
## Como apresentar o desempenho
Como o desempenho deverÃ¡ ser mostrado. Margem de erro, etc.
## MediÃ§Ãµes base (uma mÃ¡quina)
Inclua a especificaÃ§Ã£o dos componentes relevantes e os resultados de desempenho.
