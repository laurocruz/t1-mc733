# t1-mc733
Trabalho 1 da disciplina MC733 - Professor Lucas Wanner

# Trabalho 1

# Programa 18 - Cifra de bloco AES usado modo de operação CBC
## O programa cifra e decifra texto de bloco em bloco. Com o modo de operação CBC podemos realizar essa operação para grandes extensões de texto.

A cifra realiza a cifração de blocos de 128 bits com chaves de tamanho 128, 192 ou 256 bits (tamanho
da chave ainda a ser definido). Para garantir que grandes quantidades de dados seja cifradas para
realizar o benchmark usaremos o modo de operação CBC, que divide o plaintext em váriops blocos de
128 bits, realiza um ou-exclusivo desse plaintext com o ciphertext da cifração anterior e passa esse
bloco pelo AES, gerando assim um novo ciphertext:

![alt tag](https://upload.wikimedia.org/wikipedia/commons/8/80/CBC_encryption.svg)

![alt_tag](https://upload.wikimedia.org/wikipedia/commons/2/2a/CBC_decryption.svg)

Podemos esperar que, para boas implementações da cifra, o tempo para realizar uma operação com
plaintexts de mesmo tamanho seja a mesma. Se não, que pelo menos a operação para o mesmo plaintext
seja a mesma sempre.

## Por que Ã© bom para medir desempenho?

Para grandes tamanhos de input (plaintext/ciphertext) podemos obter bons levantamentos do trabalho
do processador, por o trabalho para cifrar cada bloco é relativamente extenso.

Usando grandes textos também podemos esperar uma utilização do disco que afetará o benchmark, visto
que existe o trabalho de copiar bloco a bloco do texto para a memória, e então copiar esse bloco de
volta para o disco (em forma de ciphertext/plaintext).

Podem existir implementações do AES que fazem uso de aceleradores ou de execução paralela. Nesse
caso, se encontramos boas implementações que fazem uso dessas ferramentas, nosso benchmark também
poderá fazer uma avaliação disso.

## O que baixar
Onde pode ser baixado o cÃ³digo fonte dele. NÃ£o Ã© permitido utilizar nenhum versÃ£o jÃ¡ instalada
nos computadores.
## Como compilar/instalar
O programa deverÃ¡ ser instalado no computador, compilado localmente. NÃ£o deixar o binÃ¡rio
disponÃ­vel. NÃ£o deve ser necessÃ¡rio instalar como administrador do computador (root)
## Como executar
InstruÃ§Ãµes para execuÃ§Ã£o. Se seu programa precisa de entradas, vocÃª deve fornece-las para que
todos executem corretamente.
## Como medir o desempenho
Como que o desempenho Ã© medido atravÃ©s deste programa? Se for atravÃ©s de tempo, vocÃª deve
especificar claramente qual tempo deverÃ¡ ser utilizado e indicar o motivo aqui. Quantas vezes a
medida deverÃ¡ ser feita? O que fazer com ela (mÃ©dia, etc) ? NÃ£o especificar o tempo serÃ¡
considerado falha grave.
## Como apresentar o desempenho
Como o desempenho deverÃ¡ ser mostrado. Margem de erro, etc. 
## MediÃ§Ãµes base (uma mÃ¡quina)
Inclua a especificaÃ§Ã£o dos componentes relevantes e os resultados de desempenho.
