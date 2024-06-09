#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

enum class Screen
{
    Main,
    ListaDesafios,
    Introducao,
    IntroducaoQuestao1,
    IntroducaoPt2,
    IntroducaoQuestao2,
    IntroducaoFim,
    SobreCpp,
    Variaveis,
    VariaveisFim,
    ReordenarCodigo,
    Condicionais,
    CondicionaisQ1,
    ConicionaisQ2,
    CondicionaisFim
};

void centerText(sf::Text& text, sf::RenderWindow& window, float y)
{
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
    text.setPosition(window.getSize().x / 2.0f, y);
}

void wrapText(sf::Text& text, float width)
{
    std::string str = text.getString();
    std::string wrapped;
    std::string line;
    for (char& ch : str)
    {
        line += ch;
        text.setString(line);
        if (text.getLocalBounds().width > width)
        {
            wrapped += '\n';
            line.clear();
        }
        wrapped += ch;
    }
    text.setString(wrapped);
}

int main()
{
    // Cria a janela principal
    sf::RenderWindow window(sf::VideoMode(1024, 600), "Quiz C++", sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    // Define a cor do fundo
    sf::Color backgroundColor(245, 245, 245); // Branco gelo

    // Carrega a fonte
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        // Error handling
        return -1;
    }

    // Texto do menu principal
    sf::Text menuText[3];
    std::string menuItems[3] = { "Iniciar desafios", "Sobre o C++", "Sair" };
    for (int i = 0; i < 3; ++i)
    {
        menuText[i].setFont(font);
        menuText[i].setString(menuItems[i]);
        menuText[i].setCharacterSize(30);
        menuText[i].setFillColor(sf::Color::Black);
        centerText(menuText[i], window, 200 + i * 50);
    }

    // Lista de desafios
    sf::Text listaDesafios[5];
    std::string challengeItems[5] = { "1- Introdução", "2- Variáveis", "3- Condicionais" };
    for (int i = 0; i < 5; ++i)
    {
        listaDesafios[i].setFont(font);
        listaDesafios[i].setString(challengeItems[i]);
        listaDesafios[i].setCharacterSize(24);
        listaDesafios[i].setFillColor(sf::Color::Black);
        centerText(listaDesafios[i], window, 100 + i * 50);
    }

    // Sobre o c++
    sf::Text sobreCppText;
    sobreCppText.setFont(font);
    sobreCppText.setString(
        "É uma linguagem de programação compilada multi-paradigma e de uso geral.\n\n"
        "Foi criada em 1980 por Bjarne Stroustrupe é uma das linguagens comerciais mais populares,\n\n"
        "sendo bastante usada também na academia por seu grande desempenho e base de utilizadores.\n");
    sobreCppText.setCharacterSize(16);
    sobreCppText.setFillColor(sf::Color::Black);
    wrapText(sobreCppText, window.getSize().x - 40);
    sobreCppText.setPosition(20, 20);


    // Texto da introdução
    sf::Text introducaoText;
    introducaoText.setFont(font);
    introducaoText.setString(
        "Codigo do Hello World\n\n"
        "#include <iostream> // Inclue a Biblioteca iostream\n\n"
        "int main() { // inicializacao do programa\n"
        "    std::cout << \"Hello World!\"; // Imprime Hello Wolrd\n"
        "    return 0; // Retorna 0 indicando que o programa executou com sucesso\n"
        "} // Fecha o bloco do código\n\n"
        "A biblioteca utilizada no codigo anterior teve como função o uso do cout"
        "- lido como see out - que por sua vez imprime na tela o que estava\n" 
        "entre as aspas.");
    introducaoText.setCharacterSize(16);
    introducaoText.setFillColor(sf::Color::Black);
    wrapText(introducaoText, window.getSize().x - 40);
    introducaoText.setPosition(20, 20);

    // Botao "Avancar"
    sf::Text advanceButton;
    advanceButton.setFont(font);
    advanceButton.setString("Avançar");
    advanceButton.setCharacterSize(20);
    advanceButton.setFillColor(sf::Color::Black);
    advanceButton.setPosition(window.getSize().x - 100, window.getSize().y - 50);

    // Texto da pergunta 1
    sf::Text introducaoQuestao;
    introducaoQuestao.setFont(font);
    introducaoQuestao.setString("Qual biblioteca foi utilizada?");
    introducaoQuestao.setCharacterSize(24);
    introducaoQuestao.setFillColor(sf::Color::Black);
    centerText(introducaoQuestao, window, 100);

    // Opções da pergunta 1
    sf::Text introducaoQuestaoOpcoes[3];
    std::string optionItems1[3] = { "a) iostream", "b) sstream", "c) sfml" };
    for (int i = 0; i < 3; ++i)
    {
        introducaoQuestaoOpcoes[i].setFont(font);
        introducaoQuestaoOpcoes[i].setString(optionItems1[i]);
        introducaoQuestaoOpcoes[i].setCharacterSize(24);
        introducaoQuestaoOpcoes[i].setFillColor(sf::Color::Black);
        centerText(introducaoQuestaoOpcoes[i], window, 200 + i * 50);
    }

    // Texto de feedback
    sf::Text feedbackText;
    feedbackText.setFont(font);
    feedbackText.setCharacterSize(24);
    feedbackText.setFillColor(sf::Color::Black);
    centerText(feedbackText, window, 400);

    // Texto da lição sobre comentários
    sf::Text introducaoPt2Text;
    introducaoPt2Text.setFont(font);
    introducaoPt2Text.setString(
        "Relembrando o inicio do código do hello world, vemos que logo apos a inclusão da biblioteca temos um \"//\", "
        "eles sao utilizados pra fazer um comentario no codigo, e existem dois tipos de comentarios:\n\n"
        "Os de uma linha \"//Exemplo de comentario\" , e os de multi-linhas /**/\n"
        "\"/* Exemplo\n"
        "de comentario\n"
        "de multi-linhas */\n\n"
        "Alem de que todos os caracteres dentro dos comentarios sao ignorados pelo compilador C++.");
    introducaoPt2Text.setCharacterSize(16);
    introducaoPt2Text.setFillColor(sf::Color::Black);
    wrapText(introducaoPt2Text, window.getSize().x - 40);
    introducaoPt2Text.setPosition(20, 20);

    // Texto da pergunta 2
    sf::Text introducaoQuestao2Text;
    introducaoQuestao2Text.setFont(font);
    introducaoQuestao2Text.setString("Quais simbolos são utilizados para fazerem comentarios de uma linha e multi-linhas?");
    introducaoQuestao2Text.setCharacterSize(24);
    introducaoQuestao2Text.setFillColor(sf::Color::Black);
    centerText(introducaoQuestao2Text, window, 100);

    // Opções da pergunta 2
    sf::Text option2[4];
    std::string optionItems2[4] = { "a) // e <-- -->", "b) /**/ e #", "c) <!-- --> e #", "d) // e /**/" };
    for (int i = 0; i < 4; ++i)
    {
        option2[i].setFont(font);
        option2[i].setString(optionItems2[i]);
        option2[i].setCharacterSize(20);
        option2[i].setFillColor(sf::Color::Black);
        centerText(option2[i], window, 200 + i * 50);
    }

    // Texto de conclusão da introdução
    sf::Text introducaoFimText;
    introducaoFimText.setFont(font);
    introducaoFimText.setString("Parabêns por completar a introdução pressione em retornar para \nvoltar para a tela de desafios");
    introducaoFimText.setCharacterSize(20);
    introducaoFimText.setFillColor(sf::Color::Black);
    wrapText(introducaoFimText, window.getSize().x - 40);
    introducaoFimText.setPosition(20, 200);

    // Botao "Retornar"
    sf::Text returnButton;
    returnButton.setFont(font);
    returnButton.setString("Retornar");
    returnButton.setCharacterSize(20);
    returnButton.setFillColor(sf::Color::Black);
    returnButton.setPosition(window.getSize().x / 2 - 40, window.getSize().y - 50);

    //Texto das variavies
    sf::Text variaveisITexto;
    variaveisITexto.setFont(font);
    variaveisITexto.setString(
        "Em programação, variaveis tem a função de guardar informações que seram \nmanipuladas pelo programa.\n"
        "Quando uma variavel é definida em c++, deve - se informar tanto seu nome quanto o tipo de informação contida nela, que podem ser:\n\n"
        "-Integer(int) - Para guardar numeros;\n\n"
        "-Floating point(float) - Para guardar numeros fracionados, decimais;\n\n"
        "-Double(double) - Para guardar numeros fracionados, decimais gigantes;\n\n"
        "-Character(char) - Para guardar letras;\n\n"
        "-String(string) - Para guardar palavras / sequencia de letras;\n\n"
        "-Boolean(bool) - Para guardar valores de True ou False; \n\n");
    variaveisITexto.setCharacterSize(16);
    variaveisITexto.setFillColor(sf::Color::Black);
    wrapText(variaveisITexto, window.getSize().x - 40);
    variaveisITexto.setPosition(20, 20);

    //Texto das variaviespt2
    sf::Text variaveisITextoPt2;
    variaveisITextoPt2.setFont(font);
    variaveisITextoPt2.setString(
        "Exemplo de definição de utilização de variável:\n\n"
        "Primeiro vamos definir o tipo de variável, que sera uma string.\n\n"
        "Agora damos o nome de primeiroNome \n\n"
        "-Por fim adicionamos um valor para ela primeiroNome = 'João'\n\n"
        "E é assim que ela ficara no final:\n\n"
        "string primeiroNome = 'João'\n\n");
    variaveisITextoPt2.setCharacterSize(16);
    variaveisITextoPt2.setFillColor(sf::Color::Black);
    wrapText(variaveisITextoPt2, window.getSize().x - 40);
    variaveisITextoPt2.setPosition(20, 20);

    // Texto do desafio de reorganizar código
    sf::Text variaveisQuestao;
    variaveisQuestao.setFont(font);
    variaveisQuestao.setString("Reorganize o texto");
    variaveisQuestao.setCharacterSize(24);
    variaveisQuestao.setFillColor(sf::Color::Black);
    centerText(variaveisQuestao, window, 100);

    // Opções do desafio
    std::vector<sf::Text> codeLines(3);
    std::string codeItems[3] = { "quantia = 10;", "cout << quantia;", "int quantia;" };
    for (int i = 0; i < 3; ++i)
    {
        codeLines[i].setFont(font);
        codeLines[i].setString(codeItems[i]);
        codeLines[i].setCharacterSize(24);
        codeLines[i].setFillColor(sf::Color::Black);
        codeLines[i].setPosition(100, 150 + i * 50);
    }

    //Fim Variaveis
    sf::Text variaveisFimText;
    variaveisFimText.setFont(font);
    variaveisFimText.setString("Parabens por completar a seção das variáveis pressione em retornar para \nvoltar para a tela de desafios");
    variaveisFimText.setCharacterSize(16);
    variaveisFimText.setFillColor(sf::Color::Black);
    wrapText(variaveisFimText, window.getSize().x - 40);
    variaveisFimText.setPosition(20, 20);


    //Texto das Condicionais
    sf::Text condicionaisInicio;
    condicionaisInicio.setFont(font);
    condicionaisInicio.setString(
        "Em C++ temos os seguintes tipos de declaração de condicionais:\n\n"
        "-if para especificar um bloco de código a ser executado, se uma condição especificada for verdadeira;\n\n"
        "-else para especificar um bloco de código a ser executado, se a mesma condição for falsa;\n\n"
        "-else if para especificar uma nova condição a ser testada, se a primeira condição for falsa;\n\n"
        "-switch para especificar muitos blocos alternativos de código a serem executados;\n\n"
        "E a forma correta de escrever os condicionais seria por exemplo:\n\n"
        "if (a > b) sempre tendo os parenteses.\n\n");
    condicionaisInicio.setCharacterSize(16);
    condicionaisInicio.setFillColor(sf::Color::Black);
    wrapText(condicionaisInicio, window.getSize().x - 40);
    condicionaisInicio.setPosition(20, 20);

    // Questão 1 Condicionais
    sf::Text questao1Condicionais;
    questao1Condicionais.setFont(font);
    questao1Condicionais.setString(
        "Dado o seguinte código, o que deve ser posto nos espaços em branco para que o condicional esteja correto?\n\n"
        "int x = 20;\n\n"
        "int y = 18;\n\n"
        "__ (x _ y) {\n\n"
        "  cout << 'x is greater than y';\n\n"
        "}");
    questao1Condicionais.setCharacterSize(15);
    questao1Condicionais.setFillColor(sf::Color::Black);
    centerText(questao1Condicionais, window, 100);

    // Opções da Questão 1 Condicionais
    std::vector<sf::Text> questao1CondicionaisOpcoes(4);
    std::string questao1CondicionaisStrings[4] = { "a) if e >", "b) else if +", "c) else -", "d) switch <" };
    for (int i = 0; i < 4; ++i)
    {
        questao1CondicionaisOpcoes[i].setFont(font);
        questao1CondicionaisOpcoes[i].setString(questao1CondicionaisStrings[i]);
        questao1CondicionaisOpcoes[i].setCharacterSize(15);
        questao1CondicionaisOpcoes[i].setFillColor(sf::Color::Black);
        questao1CondicionaisOpcoes[i].setPosition(150, 250 + i * 50);
    }  

    //Fim Concicionais
    sf::Text condicionaisFim;
    condicionaisFim.setFont(font);
    condicionaisFim.setString("Parabens por completar a seção das condicionais pressione em retornar para \nvoltar para a tela de desafios");
    condicionaisFim.setCharacterSize(16);
    condicionaisFim.setFillColor(sf::Color::Black);
    wrapText(condicionaisFim, window.getSize().x - 40);
    condicionaisFim.setPosition(20, 20);

    // Estado da tela atual
    Screen currentScreen = Screen::Main;
    int correctAnswers = 0;
    bool isDragging = false;
    int draggedIndex = -1;
    sf::Vector2f prevMousePos;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (currentScreen == Screen::ReordenarCodigo)
                {
                    for (int i = 0; i < 3; ++i)
                    {
                        if (codeLines[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
                        {
                            isDragging = true;
                            draggedIndex = i;
                            prevMousePos = window.mapPixelToCoords(mousePos);
                            break;
                        }
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                if (currentScreen == Screen::ReordenarCodigo)
                {
                    isDragging = false;
                    draggedIndex = -1;
                }
            }

            if (event.type == sf::Event::MouseMoved)
            {
                if (isDragging && draggedIndex != -1)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f currentPos = window.mapPixelToCoords(mousePos);
                    sf::Vector2f deltaPos = currentPos - prevMousePos;

                    codeLines[draggedIndex].move(0, deltaPos.y);
                    prevMousePos = currentPos;

                    // Ensure the code lines don't overlap
                    for (int i = 0; i < 3; ++i)
                    {
                        if (i != draggedIndex && codeLines[draggedIndex].getGlobalBounds().intersects(codeLines[i].getGlobalBounds()))
                        {
                            if (deltaPos.y > 0)
                            {
                                codeLines[draggedIndex].setPosition(codeLines[draggedIndex].getPosition().x, codeLines[i].getPosition().y + codeLines[i].getGlobalBounds().height);
                            }
                            else 
                            {
                                codeLines[draggedIndex].setPosition(codeLines[draggedIndex].getPosition().x, codeLines[i].getPosition().y - codeLines[draggedIndex].getGlobalBounds().height);
                            }
                        }
                    }

                    // Linhas não sairam da janela
                    for (int i = 0; i < 3; ++i)
                    {
                        sf::Vector2f pos = codeLines[i].getPosition();
                        if (pos.y < 0)
                        {
                            codeLines[i].setPosition(pos.x, 0);
                        }
                        else if (pos.y + codeLines[i].getGlobalBounds().height > window.getSize().y)
                        {
                            codeLines[i].setPosition(pos.x, window.getSize().y - codeLines[i].getGlobalBounds().height);
                        }
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (currentScreen == Screen::Main)
                {
                    // Verifica se "Iniciar desafios" foi clicado
                    if (menuText[0].getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        currentScreen = Screen::ListaDesafios;
                    }
                    // Verifica se "História" foi clicado
                    else if (menuText[1].getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        currentScreen = Screen::SobreCpp;
                    }
                    // Verifica se "Sair" foi clicado
                    else if (menuText[2].getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        window.close();
                    }
                }
                else if (currentScreen == Screen::ListaDesafios)
                {
                    // Verifica se "Introdução" foi clicado
                    if (listaDesafios[0].getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        currentScreen = Screen::Introducao;
                    }
                    else if (listaDesafios[1].getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        currentScreen = Screen::Variaveis;
                    }
                    else if (listaDesafios[2].getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        currentScreen = Screen::Condicionais;
                    }
                }
                else if (currentScreen == Screen::SobreCpp)
                {
                    // Verifica se "Retornar" foi clicado
                    if (returnButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        currentScreen = Screen::Main;
                    }
                }
                else if (currentScreen == Screen::Introducao)
                {
                    // Verifica se "Avancar" foi clicado
                    if (advanceButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        currentScreen = Screen::IntroducaoQuestao1;
                    }
                }
                else if (currentScreen == Screen::IntroducaoQuestao1)
                {
                    // Verifica qual opção foi clicada
                    for (int i = 0; i < 3; ++i)
                    {
                        if (introducaoQuestaoOpcoes[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
                        {
                            if (i == 0)
                            {
                                currentScreen = Screen::IntroducaoPt2;
                            }
                            else
                            {
                                feedbackText.setString("Resposta incorreta, tente novamente.");
                            }
                            centerText(feedbackText, window, 400);
                        }
                    }
                }
                else if (currentScreen == Screen::IntroducaoPt2)
                {
                    if (advanceButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        currentScreen = Screen::IntroducaoQuestao2;
                    }
                }
                else if (currentScreen == Screen::IntroducaoQuestao2)
                {
                    // Verifica qual opção foi clicada
                    for (int i = 0; i < 4; ++i)
                    {
                        if (option2[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
                        {
                            if (i == 3)
                            {
                                currentScreen = Screen::IntroducaoFim;
                            }
                            else
                            {
                                feedbackText.setString("Resposta incorreta, tente novamente.");
                            }
                            centerText(feedbackText, window, 400);
                        }
                    }
                }
                else if (currentScreen == Screen::IntroducaoFim)
                {
                    if (returnButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        currentScreen = Screen::Main;
                    }
                }             
                else if (currentScreen == Screen::Variaveis)
                {
                    if (advanceButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        currentScreen = Screen::ReordenarCodigo;
                    }
                }
                else if (currentScreen == Screen::ReordenarCodigo)
                {
                    std::vector<float> positions;
                    for (int i = 0; i < 3; ++i)
                    {
                        positions.push_back(codeLines[i].getPosition().y);
                    }

                    std::vector<int> order = { 0, 1, 2 };
                    std::sort(order.begin(), order.end(), [&positions](int a, int b) {
                        return positions[a] < positions[b];
                        });

                    if (order[0] == 2 && order[1] == 0 && order[2] == 1)
                    {
                        currentScreen = Screen::VariaveisFim;
                    }
                }
                else if (currentScreen == Screen::VariaveisFim)
                {

                    if (returnButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        currentScreen = Screen::Main;
                    }
                }
                else if (currentScreen == Screen::Condicionais)
                {
                    if (advanceButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        currentScreen = Screen::CondicionaisQ1;
                    }
                }
                else if (currentScreen == Screen::CondicionaisQ1)
                {
                    for (int i = 0; i < 4; ++i)
                    {
                        if (questao1CondicionaisOpcoes[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
                        {                            
                            if (i == 0)
                            {
                                currentScreen = Screen::CondicionaisFim;
                            }
                            else
                            {
                               // feedbackText.setString("Resposta incorreta, tente novamente.");
                            }
                            centerText(feedbackText, window, 400);
                        }
                    }
                } 
                else if (currentScreen == Screen::CondicionaisFim)
                {
                    // Verifica se "Retornar" foi clicado
                    if (returnButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        currentScreen = Screen::Main;
                    }
                }
            }
        }

        window.clear(backgroundColor);

        if (currentScreen == Screen::Main)
        {
            for (int i = 0; i < 3; ++i)
            {
                window.draw(menuText[i]);
            }
        }
        else if (currentScreen == Screen::ListaDesafios)
        {
            for (int i = 0; i < 5; ++i)
            {
                window.draw(listaDesafios[i]);
            }
        }
        else if (currentScreen == Screen::SobreCpp)
        {
            window.draw(sobreCppText);
            window.draw(returnButton);
        }
        else if (currentScreen == Screen::Introducao)
        {
            window.draw(introducaoText);
            window.draw(advanceButton);
        }
        else if (currentScreen == Screen::IntroducaoQuestao1)
        {
            window.draw(introducaoQuestao);
            for (int i = 0; i < 3; ++i)
            {
                window.draw(introducaoQuestaoOpcoes[i]);
            }
            window.draw(feedbackText);
        }
        else if (currentScreen == Screen::IntroducaoPt2)
        {
            window.draw(introducaoPt2Text);
            window.draw(advanceButton);
        }
        else if (currentScreen == Screen::IntroducaoQuestao2)
        {
            window.draw(introducaoQuestao2Text);
            for (int i = 0; i < 4; ++i)
            {
                window.draw(option2[i]);
            }
            window.draw(feedbackText);
        }
        else if (currentScreen == Screen::IntroducaoFim)
        {
            window.draw(introducaoFimText);
            window.draw(returnButton);
        }
        else if (currentScreen == Screen::Variaveis)
        {
            window.draw(variaveisITexto);
            window.draw(advanceButton);
        }
        else if (currentScreen == Screen::ReordenarCodigo)
        {
            window.draw(variaveisQuestao);
            for (int i = 0; i < 3; ++i)
            {
                window.draw(codeLines[i]);
            }
        }
        else if (currentScreen == Screen::VariaveisFim)
        {
            window.draw(variaveisFimText);
            window.draw(returnButton);
        }
        else if (currentScreen == Screen::Condicionais)
        {
            window.draw(condicionaisInicio);
            window.draw(advanceButton);
        }
        else if (currentScreen == Screen::CondicionaisQ1)
        {
            window.draw(questao1Condicionais);
            for (int i = 0; i < 4; ++i)
            {
                window.draw(questao1CondicionaisOpcoes[i]);
            }
            window.draw(feedbackText);
        }
        else if (currentScreen == Screen::CondicionaisFim)
        {
            window.draw(condicionaisFim);
            window.draw(returnButton);
        }

        window.display();
    }

    return 0;
}