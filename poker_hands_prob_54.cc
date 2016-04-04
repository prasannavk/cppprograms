#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <boost/tokenizer.hpp>
#include <algorithm>

using std::vector;
using std::string;

boost::char_separator<char> sep(" ");

vector<string> Tokenize(string game_line) {
  boost::tokenizer<boost::char_separator<char> > tokens(game_line, sep);
  vector<string> string_tokens;
  for (auto single_word : tokens) {
    // std::cout << single_word << ",";
    string_tokens.push_back(single_word);
  }
  // std::cout << "\n";
  return string_tokens;
}

void SplitPlayers(const vector<string> &card_vec, vector<string> *player_1,
    vector<string> *player_2) {
  assert(card_vec.size() == 10);
  for (size_t i = 0; i < 5; ++i) {
    player_1->push_back(card_vec[i]);
  }
  
  for (size_t i = 5; i < 10; ++i) {
    player_2->push_back(card_vec[i]);
  }
}

enum Suits {
  CLUBS    = 0,
  DIAMONDS,
  HEARTS,
  SPADES
};

enum HandRank {
  HIGH_CARD = 0,
  ONE_PAIR = 1,
  TWO_PAIRS = 2,
  THREE_KIND = 3,
  STRAIGHT = 4,
  FLUSH = 5,
  FULL_HOUSE = 6,
  FOUR_KIND = 7,
  STRAIGHT_FLUSH = 8,
  ROYAL_FLUSH = 9
};

Suits ConvertLetterToSuit(char suit_letter) {
  switch (suit_letter) {
    case 'C':
      return CLUBS;
    case 'D':
      return DIAMONDS;
    case 'H':
      return HEARTS;
    case 'S':
      return SPADES;
    default:
      std::cout << "error: unknown letter indicating suit\n";
  }
}

HandRank CheckKind(const vector<string> &player_cards) {
  // 2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace
  vector<int> card_count(13, 0);
  for (auto single_card : player_cards) {
    int val = single_card[0] - '0';
    card_count[val]++;
  }

  int pair_count = 0;
  int three_count = 0;
  for (int i = 0; i < 13; i++) {
    if (card_count[i] == 2) {
      pair_count++; 
    } else if (card_count[i] == 3) {
      // 3 of a kind
      three_count++;
      // the three would have also counted as a pair
      pair_count--;
    } else if (card_count[i] == 4) {
      // 4 of a kind
      return FOUR_KIND;
    }
  }
  if (pair_count == 1) {
    if (three_count == 1) {
      return FULL_HOUSE;
    } else {
      return ONE_PAIR;
    }
  } else if (pair_count == 2) {
     return TWO_PAIRS;
  } else if (three_count == 1) {
    return THREE_KIND;
  }
  return HIGH_CARD;
}

HandRank CheckStraight(const vector<string> &player_cards) {
  vector<int> values;
  int val = 0;
  assert(player_cards.size() == 5);
  for (auto single_card : player_cards) {
    if (single_card[0] >= '2' && single_card[0] <= '9') {
      val = single_card[0] - '0'; 
    } else {
#if 0
      switch (single_card[0]) {
        case 'T': {
          val = 10;
          break;
        }
        case 'J': {
          val = 11;
          break;
        }
        case 'Q': {
          val = 12;
          break;
        }
        case 'K': {
          val = 13;
          break;
        }
        case 'A': {
          val = 1;
          break;
        }
        default: {
          std::cout << "Error: invalid card " << single_card << "\n";
          val = 0;
        }
      }
#endif
      val = 0;
    }
    values.push_back(val);
  }
  
  return HIGH_CARD;
#if 0
  assert(values.size() == 5);
  std::sort(values.begin(), values.end());  
  std::cout << "values in straight \n";
  for (auto value : values) {
    std::cout << value << " ";
  }
  std::cout << "\n";
  assert(values.size() == 5);

  for (int i = 0; i < values.size() - 1; ++i) {
    int diff = values[i+1] - values[i];
    if (diff != 1) {
      std::cout << "returning high card\n";
      return HIGH_CARD;
    }
  }
  std::cout << "returning straight\n";
  return STRAIGHT;
#endif
}

HandRank CheckFlush(const vector<string> &player_cards) {
  int suit_count[4] = {0, 0, 0, 0};
  for (auto single_card : player_cards) {
    int suit_enum = ConvertLetterToSuit(single_card[1]);
    suit_count[suit_enum]++;
  }

  for (int i = 0; i < 4; ++i) {
    if (suit_count[i] == 5) {
      return FLUSH;
    }
  }
}

int DecideWinner(vector<string> card_vec) {
  // First five is player 1
  //
  //
  // Royal Flush
  vector<string> player_1, player_2;
  SplitPlayers(card_vec, &player_1, &player_2);
  assert(player_1.size() == 5);
  assert(player_2.size() == 5);
  std::cout << CheckKind(player_1) << " vs " << CheckKind(player_2) << "\n";
  std::cout << CheckStraight(player_1) << " vs " << CheckStraight(player_2) << "\n";
  std::cout << CheckFlush(player_1) << " vs " << CheckFlush(player_2) << "\n";
  std::cout << "\n------------------\n";
  return 1;
}

int main() {
  std::ifstream is("p054_poker.txt");
  if (!is) {
    std::cout << "error opening file \n";
  }
  std::string game_line;
  int counter = 1;
    
  while (std::getline(is, game_line)) {
    // std::cout << "line " << counter << "\n";
    std::cout << game_line << std::endl;
    vector<string> card_vec = Tokenize(game_line);
    int player_num = DecideWinner(card_vec);
    counter++;
  }

  return 0;
}
