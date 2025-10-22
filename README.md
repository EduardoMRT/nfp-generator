```markdown
# nfp-generator

Projeto em C++ para cálculo e visualização de NFP (No-Fit Polygon) usando CGAL (soma de Minkowski) e SFML (visualização).

Este repositório contém:
- main.cpp — implementação (CGAL + SFML)
- exemplos em examples/
- scripts: build.sh, run.sh
- CMakeLists.txt (opcional)
- LICENSE (MIT)

Resumo rápido de uso:
1. Instale CGAL e SFML conforme as instruções a seguir (comandos fornecidos por você).
2. Compile: ./build.sh
3. Execute: ./run.sh
4. Forneça os vértices dos dois polígonos quando solicitado no terminal.
5. A janela SFML mostrará o NFP.

-------------------------
MANUAL DE INSTALAÇÃO (comandos fornecidos)
-------------------------
Tutorial de instalação do CGAL e da SFML no Ubuntu WSL

1. Primeiramente é bom verificar se o sistema está atualizado, e caso não estiver
atualizar, isso pode ser feito com o seguinte comando:
sudo apt update && sudo apt upgrade -y

2. Depois precisamos instalar as dependências do CGAL, no caso são pacotes
necessários para compilar:
sudo apt install -y build-essential cmake libgmp-dev libmpfr-dev
libboost-all-dev

3. Agora sim podemos realizar a instalação do CGAL propriamente dito:
sudo apt install -y libcgal-dev libcgal-qt5-dev

4. Após isso podemos criar um projeto de exemplo para verificar a instalação do
CGAL:
mkdir ~/cgal-exemplo && cd ~/cgal-exemplo

5. Opcional mas facilita muito, abra o VSCode e encontre a pasta acima, crie os
arquivos a seguir nessa pasta, você pode usar o seguinte comando para abrir o
VSCode:
code .

6. Exemplo de código para testar o CGAL:
#include <CGAL/Simple_cartesian.h>
#include <CGAL/convex_hull_2.h>
#include <vector>
#include <iostream>
typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point_2;
int main() {
std::vector<Point_2> pontos = { Point_2(0, 0), Point_2(10, 0), Point_2(5, 5) };
std::vector<Point_2> casca;
CGAL::convex_hull_2(pontos.begin(), pontos.end(),
std::back_inserter(casca));
std::cout << "Casca convexa:\n";

for (const auto& p : casca)
std::cout << p << "\n";
return 0;
}

7. Para compilar digite o seguinte comando:
g++ -Wall -Wextra -g3 main.cpp -o main

8. E depois digite para rodar o executável:
./main

Possíveis erros:

a) Falta do g++ intalado:
Caso você não possua o compilador g++ instalado, digite o seguinte código e repita
os passos 7 e 8:
sudo apt update
sudo apt install build-essential

b) Erro de compilação faltando dependências do CGAL, utilize o seguinte comando
para compilar com as dependências:
g++ -Wall -Wextra -g3 main.cpp -o main -lCGAL -lgmp -lmpfr
./main
c) Se você tentar o passo b) e mesmo assim obter erro, tente rodar o seguinte código
e depois voltar ao passo b):
sudo apt install libcgal-dev libcgal-qt5-dev libgmp-dev libmpfr-dev

Instalação da Biblioteca SFML

A SFML é uma biblioteca que possibilita a visualização gráfica, e que pode ser
utilizada para geração gráfica do NFP.
Para realizar sua instalação basta seguir os passos a seguir:

1. Atualizar o sistema, para fazer isso rode o seguinte código no terminal do seu
UbuntuWSL:
sudo apt update
sudo apt upgrade

2. Instalar a SFML, o que pode ser realizado pelo comando a seguir (veja os tópicos
4 e 5 da instalação do CGAL):
sudo apt install libsfml-dev

3. Criar um arquivo main.cpp com o seguinte conteúdo:
#include <SFML/Graphics.hpp>
int main()
{
sf::RenderWindow window(sf::VideoMode(800, 600), "Janela SFML");
while (window.isOpen())
{
sf::Event event;
while (window.pollEvent(event))
{
if (event.type == sf::Event::Closed)
window.close();
}
window.clear();
window.display();
}
return 0;
}

4. Compile o arquivo com (ele inclui as principais dependências da SFML para evitar
erros durante a compilação):
g++ main.cpp -o sfml_test -lsfml-graphics -lsfml-window -lsfml-system

5. Rode o programa com o código abaixo, caso tenha alterado o que vem a partir de
-o e antes de -lsfml... no comando acima, altere para o respectivo, caso contrário,
somente utilize.
./sfml_test

-------------------------
Exemplos
-------------------------
- Há um exemplo pronto em examples/polygons_example.txt com o formato esperado.
- Para usá-lo, rode o binário e copie/cole os valores do arquivo quando o programa pedir.

Licença
-------
Veja LICENSE (MIT) no repositório.

Autor
-----
EduardoMRT and Larissa Tebaldi
```