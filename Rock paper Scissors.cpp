#include <iostream>
#include <cstdlib>
#include <ctime>

// ÇáÏÇáÉ ÇáÊí ÊÓÊŞÈá ÇÎÊíÇÑ ÇááÇÚÈ
char getPlayerChoice() {
    char choice;
    std::cout << "Enter your choice (r for Rock, p for Paper, s for Scissors): ";
    std::cin >> choice;
    return choice;
}

// ÇáÏÇáÉ ÇáÊí ÊæáÏ ÇÎÊíÇÑÇğ ÚÔæÇÆíÇğ ááÍÇÓæÈ
char getComputerChoice() {
    srand(time(0));
    int random = rand() % 3;
    switch (random) {
    case 0: return 'r';
    case 1: return 'p';
    case 2: return 's';
    }
    return 'r'; // İí ÍÇáÉ ÍÏæË ÎØÃ ÛíÑ ãÊæŞÚ
}

// ÇáÏÇáÉ ÇáÊí ÊÍÏÏ ÇáİÇÆÒ
std::string determineWinner(char player, char computer) {
    if (player == computer) {
        return "It's a tie!";
    }
    if ((player == 'r' && computer == 's') ||
        (player == 'p' && computer == 'r') ||
        (player == 's' && computer == 'p')) {
        return "You win!";
    }
    else {
        return "Computer wins!";
    }
}

// ÇáÏÇáÉ ÇáÑÆíÓíÉ ÇáÊí ÊäÙã ÇááÚÈÉ
void playGame() {
    char playerChoice = getPlayerChoice();
    char computerChoice = getComputerChoice();

    std::cout << "You chose: " << playerChoice << std::endl;
    std::cout << "Computer chose: " << computerChoice << std::endl;

    std::string result = determineWinner(playerChoice, computerChoice);
    std::cout << result << std::endl;
}

int main() {
    playGame();
    return 0;
}
