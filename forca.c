#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h" // Header fille

char palavrasecreta[TAMANHO_PALAVRA]; 
char chutes[26];
int chutesdados = 0;

void abertura(){
    printf(",---,---,---,---,---,---,---,---,---,---,---,---,---,-------, \n");
    printf("|1/2| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | + | ' | &lt;- | \n");
    printf("|---'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-----| \n");
    printf("| -&gt;| |   |   |   | J | O | G | O |   |   |   | ] | ^ |  | \n");
    printf("|-----',--',--',--',--',--',--',--',--',--',--',--',--'|    | \n");
    printf("| Caps |   |   |   |   | D | A |   |   |   | \\ | [ | * |    |\n");
    printf("|----,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'---'----| \n");
    printf("|    | &lt; |   | F | O | R | C | A |   | , | . | - |       | \n");
    printf("|----'-,-',--'--,'---'---'---'---'---'---'-,-'---',--,------| \n");
    printf("| ctrl |  | alt |                          |altgr |  | ctrl | \n");
    printf("'------'  '-----'--------------------------'------'  '------' \n");
}

int letraexiste(char letra){

    for(int j = 0; j < strlen(palavrasecreta); j++) {
        if(letra == palavrasecreta[j]) {
            return 1;
        }
    }

    return 0;
}

void chuta(){

    char chute;
    printf("Qual letra? ");
    scanf(" %c", &chute); 

    if(letraexiste(chute)) {
        printf("\nVoce acertou: a palavra TEM a letra %c\n\n", chute);
    } else {
        printf("\nVoce errou: a palavra NAO tem a letra %c\n\n", chute);
    }

    chutes[chutesdados] = chute;
    chutesdados++;
}

int jachutou(char letra){

    for (int j = 0; j < chutesdados; j++){
        if (chutes[j] == letra){
            return 1;
        }
    }
    return 0;
}

void desenhaforca(){

    int erros = chuteserrados();

    printf("  _______      \n");
    printf(" |/      |     \n");
    printf(" |      %c%c%c \n", (erros >= 1 ? '(' : ' '), (erros >= 1 ? '_' : ' '), (erros >= 1 ? ')' : ' ')); 
    printf(" |      %c%c%c \n", (erros >= 3 ? '\\' : ' '), (erros >= 2 ? '|' : ' '), (erros >= 3 ? '/' : ' '));
    printf(" |       %c    \n", (erros >= 2 ? '|' : ' '));
    printf(" |      %c %c  \n", (erros >= 4 ? '/' : ' '), (erros >= 4 ? '\\' : ' '));
    printf(" |             \n");
    printf("_|___          \n");
    printf("\n\n");

    for (int i = 0; i < strlen(palavrasecreta); i++){ // FOR que percorre todo o array MELANCIA de 0 a 7

        int achou = jachutou(palavrasecreta[i]);

        if (achou) {
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }

    }

    printf("\n");
}

int ganhou(){

    for(int i = 0; i < strlen(palavrasecreta); i++) {
        if(!jachutou(palavrasecreta[i])) {
            return 0;
        }
    }

    return 1;
}

int chuteserrados(){
    int erros = 0;

    for(int i = 0; i < chutesdados; i++) {
        
        if(!letraexiste(chutes[i])) {
            erros++;
        }
    }

    return erros;
}

int enforcou(){
    return chuteserrados() >= 5;
}

void escolhepalavra(){
    FILE* f;

    f = fopen("palavras.txt", "r"); 
    if(f == NULL) {
        printf("Desculpe, banco de dados nao disponivel.\n\n");
        exit(1);
    }

    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras);

    srand(time(0));
    int randomico = rand() % qtddepalavras;

    // lê do arquivo até chegar na linha desejada
    for(int i = 0; i <= randomico; i++) {
        fscanf(f, "%s", palavrasecreta);
    }

    fclose(f);
}

void adicionapalavra(){

    char quer;
    printf("Voce deseja adicionar uma nova palavra no jogo? (S/N)\n");
    scanf(" %c", &quer);

    if(quer == 'S') {

        char novapalavra[TAMANHO_PALAVRA];
        printf("Qual a nova palavra? \n");
        scanf("%s", &novapalavra);

        FILE* f;

        f = fopen("palavras.txt", "r+"); // "r+" - vai ler e escrever no arquivo

        if(f == NULL) {
            printf("Desculpe, banco de dados nao disponivel.\n\n");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;

        fseek(f, 0, SEEK_SET); // posiciona para inicio do arquivo
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END); // posiciona para o final do arquivo
        fprintf(f, "\n%s", novapalavra); 

        fclose(f);

    }

}

int main(){

    abertura();
    escolhepalavra();

    do {
        // imprime a palavra secreta
        desenhaforca();
        // captura um novo chute
        chuta(); 

    } while(!ganhou() && !enforcou());

    if(ganhou()) {
        printf("***********  PARABENS :), voce ganhou!  ************\n\n");                                                                                                             
        printf("                          ####                    \n");
        printf("                        ######                    \n");
        printf("                      ########                    \n");
        printf("                    ##########                    \n");
        printf("                    ##########                    \n");
        printf("                  ############                    \n");
        printf("                ##############                    \n");
        printf("                ############################      \n");
        printf("    ########    ############################      \n");
        printf("    ########    ############################      \n");
        printf("    ########    ############################      \n");
        printf("    ########    ############################      \n");
        printf("    ########    ############################      \n");
        printf("    ########    ##########################        \n");
        printf("    ########    ########################          \n");
        printf("    ########    ########################          \n");
        printf("    ########    ######################            \n");
        printf("    ########    ######################            \n");
        printf("\n\n");
    } else {
        printf("**************  PUXA :(, voce foi enforcado!  **************\n");
        printf("A palavra secreta era **%s** \n\n", palavrasecreta);
        
        printf("                     @@@@@@@@@@@@@@@@@@@                     \n");
        printf("                 @@@@@@             @@@@@@@                  \n");
        printf("              @@@@                       @@@@                \n");
        printf("             @@@                             @@              \n");
        printf("            @@                                @@             \n");
        printf("           @@                     `           @@             \n");
        printf("          @@                                   @@            \n");
        printf("          @@ @@                             @@ @@            \n");
        printf("          @@ @@                             @@  @            \n");
        printf("          @@ @@                             @@  @            \n");
        printf("          @@  @@                            @@ @@            \n");
        printf("          @@  @@                           @@  @@            \n");
        printf("           @@ @@   @@@@@@@@     @@@@@@@@   @@ @@             \n");
        printf("            @@@@ @@@@@@@@@@     @@@@@@@@@@ @@@@@             \n");
        printf("             @@@ @@@@@@@@@@     @@@@@@@@@@ @@@               \n");
        printf("    @@@       @@  @@@@@@@@       @@@@@@@@@  @@      @@@@     \n");
        printf("   @@@@@     @@   @@@@@@@   @@@   @@@@@@@   @@     @@@@@@    \n");
        printf("  @@   @@    @@     @@@    @@@@@    @@@     @@    @@   @@    \n");
        printf(" @@@    @@@@  @@          @@@@@@@          @@  @@@@    @@@   \n");
        printf("@@         @@@@@@@@       @@@@@@@       @@@@@@@@@        @@  \n");
        printf("@@@@@@@@@     @@@@@@@@    @@@@@@@    @@@@@@@@      @@@@@@@@  \n");
        printf("  @@@@ @@@@@      @@@@@              @@@ @@     @@@@@@ @@@   \n");
        printf("          @@@@@@  @@@  @@           @@  @@@  @@@@@@          \n");
        printf("              @@@@@@ @@ @@@@@@@@@@@ @@ @@@@@@                \n");
        printf("                  @@ @@ @ @ @ @ @ @ @ @ @@                   \n");
        printf("                @@@@  @ @ @ @ @ @ @ @   @@@@@                \n");
        printf("            @@@@@ @@   @@@@@@@@@@@@@   @@ @@@@@              \n");
        printf("    @@@@@@@@@@     @@                 @@      @@@@@@@@@      \n");
        printf("   @@           @@@@@@@             @@@@@@@@          @@     \n");
        printf("    @@@     @@@@@     @@@@@@@@@@@@@@@     @@@@@     @@@      \n");
        printf("      @@   @@@           @@@@@@@@@           @@@   @@        \n");
        printf("      @@  @@                                   @@  @@        \n");
        printf("       @@@@                                     @@@@         \n");
        printf("\n\n");

    }

    adicionapalavra();
    
}

// ANOTAÇÕES

//sprintf(palavrasecreta, "MELANCIA"); funçao sprintf(), análoga a printf é a que nos ajuda a escrever palavras dentro de arrays de char.
// Variaveis globais definidas fora de todos os escopos, liberando acesso por todas as funções sem necessidade de passar como parâmetro
// Variaveis globais - importantes e por consequência, manipuladas por todas as nossas funções.
// toda vez que for ler um char, dar um espaço antes da máscara para ele ignorar o enter
// OPERADOR TERNÁRIO - para desenhar o boneco da forca de acordo com a quantidade de erros
// fopen() - abre o arquivo de palavras
// scanf() - similar ao scanf normal a diferença dela é que o primeiro parâmetro é o ponteiro para um arquivo.
// fseek() - pra posicionar de onde o arquivo vai ler ou escrever
// fprintf() - similar ao printf normal a diferença dela é que o primeiro parâmetro é o ponteiro para um arquivo.
