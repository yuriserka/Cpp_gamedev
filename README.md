# Joguinho C++

  - O objetivo deste projeto foi:
    - Estudar programas gráficos para o C++
    - Aprimorar meu conhecimento na linguagem
  - Foi inteiramente baseado no projeto do [carlbirch](https://github.com/carlbirch/BirchEngine) e em seus vídeos

# Pré-requisitos para o Windows
  - instale o [Cygwin](https://cygwin.com/install.html)
  - instale o [MinGW](https://sourceforge.net/projects/mingw/)
  - instale o [Git](https://git-scm.com/)
  - Há duas maneiras de rodar o programa, pelo [Visual Studio](https://visualstudio.microsoft.com/pt-br/thank-you-downloading-visual-studio/?sku=Community&rel=15) ou pelo terminal
  ## preparação
  1) Terminal (serve para o linux também)
        - abra um terminal
        - entre na pasta que deseje que fique os arquivos 
        - clone o repositório
          ```
           PS git clone https://github.com/yuriserka/Cpp_gamedev.git
          ```
        - execute os comandos:
          ```
            PS cd .\Cpp_gamedev\
            PS cd .\JoguinhoCplusplus\
            ```
        - dentro desta pasta haverá um Makefile, que contém quatro operações básicas.
        ## build
        - responsável por compilar a aplicação e gerar o executável do jogo
        ## tests
        - responsável por compilar os tests e gerar o executável dos testes
        ## install (apenas Linux)
        - responsável por instalar as dependências do programa
        ## clean
        - responsável por eliminar os objetos gerados e os executáveis
        
# Compilação de fato
  - no linux para compilar bastar executar
    ```
      $ make {alguma das opções acima}
    ```
  - no windows para compilar bastar executar
    ```
      $ mingw32-make.exe {alguma das opções acima}
    ```
  - vale ressaltar que em qualquer uma das plataformas passar o comando do make sem argumentos irá executar o build e o tests, portanto, gerando os dois executáveis
  
 2) Pelo Visual Studio
    # Todo

License
----

MIT