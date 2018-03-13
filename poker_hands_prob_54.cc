#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <boost/tokenizer.hpp>
#include <algorithm>

using std::vector;
using std::string;
using std::cout;

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
  vector<int> card_count(14, 0);
  for (int i = 0; i < 5; i++) {
    int val = 0;
    if (player_cards[i][0] >= '2' && player_cards[i][0] <= '9') {
      val = player_cards[i][0] - '0'; 
    } else {
#if 1
      switch (player_cards[i][0]) {
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
          std::cout << "Error: invalid card " << player_cards[i] << "\n";
          val = 0;
        }
      }
#endif
    }

    card_count[val]++;
  }

  int pair_count = 0;
  int three_count = 0;
  for (int i = 1; i < 14; i++) {
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

vector<int> GetValues(const vector<string> &player_cards) {
  vector<int> values;
  assert(player_cards.size() == 5);

  int val = 0;
  for (int i = 0; i < 5; ++i) {
    if (player_cards[i][0] >= '2' && player_cards[i][0] <= '9') {
      val = player_cards[i][0] - '0'; 
    } else {
#if 1
      switch (player_cards[i][0]) {
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
          std::cout << "Error: invalid card " << player_cards[i] << "\n";
          val = 0;
        }
      }
#endif
    }
    values.push_back(val);
  }
  return values;
}

vector<int> GetValuesHighAce(const vector<string> &player_cards) {
  vector<int> values;
  assert(player_cards.size() == 5);

  int val = 0;
  for (int i = 0; i < 5; ++i) {
    if (player_cards[i][0] >= '2' && player_cards[i][0] <= '9') {
      val = player_cards[i][0] - '0'; 
    } else {
#if 1
      switch (player_cards[i][0]) {
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
          val = 14;
          break;
        }
        default: {
          std::cout << "Error: invalid card " << player_cards[i] << "\n";
          val = 0;
        }
      }
#endif
    }
    values.push_back(val);
  }
  return values;
}
HandRank CheckStraight(const vector<string> &player_cards) {

  vector<int> values = GetValues(player_cards);
#if 0
  for (auto single_card : player_cards) {
  int val1 = 0;
#if 1
    if (single_card[0] >= '2' && single_card[0] <= '9') {
      // val = single_card[0] - '0'; 
      val1 = 0;
      std::cout << "numbers\n";
    } else {
      val1 = 0;
    }
#endif
    values.push_back(val1+1);
  }
#endif
  
  assert(values.size() == 5);
  std::sort(values.begin(), values.end());  
  
  bool is_consecutive = true;
  for (int i = 0; i < values.size() - 1; ++i) {
    int diff = values[i+1] - values[i];
    if (diff != 1) {
      is_consecutive = false;
      break;
    }
  }
  if (is_consecutive == true) {
    return STRAIGHT;
  }
  if (values[0] == 1) {
    // need to check for high straight for ace
    values[0] = 14;
    std::sort(values.begin(), values.end());  
    for (int i = 0; i < values.size() - 1; ++i) {
      int diff = values[i+1] - values[i];
      if (diff != 1) {
        return HIGH_CARD;
      }
    }
    return STRAIGHT;
  } 
  return HIGH_CARD;
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
  return HIGH_CARD;
}

HandRank Process(vector<string> player) {
  HandRank flush_out = CheckFlush(player);
  HandRank kind_out = CheckKind(player);
  HandRank straight_out = CheckStraight(player);

  if (flush_out == HIGH_CARD && kind_out == HIGH_CARD && straight_out == HIGH_CARD) {
    return HIGH_CARD;
  } else if (flush_out == FLUSH && straight_out == STRAIGHT) {
    std::vector<int> values = GetValues(player);
    std::sort(values.begin(), values.end());  
    if (values[0] == 1 && values[1] == 10 && values[2] == 11 &&
        values[3] == 12 && values[4] == 13) {
      return ROYAL_FLUSH;
    }
    return STRAIGHT_FLUSH;
  } else if (flush_out == FLUSH) {
    return FLUSH;
  } else if (straight_out == STRAIGHT) {
    return STRAIGHT;
  } else {
    return kind_out;
  }
}

int DecideWinner(vector<string> card_vec) {
  // First five is player 1
  //
  //
  vector<string> player_1, player_2;
  SplitPlayers(card_vec, &player_1, &player_2);
  assert(player_1.size() == 5);
  assert(player_2.size() == 5);
  HandRank score_1 = Process(player_1);
  HandRank score_2 = Process(player_2);
  if (score_1 > score_2) {
    return 1;
  } else if (score_1 < score_2) {
    return 2;
  } else {
    vector<int> values_1 = GetValuesHighAce(player_1);
    vector<int> values_2 = GetValuesHighAce(player_2);
    std::sort(values_1.begin(), values_1.end());  
    std::sort(values_2.begin(), values_2.end());  
    // rank with the highest card wins
    switch (score_1) {
      case STRAIGHT_FLUSH: {
        if (values_1[0] > values_2[0]) {
          return 1;
        } else if (values_1[0] < values_2[0]) {
          return 2;
        } else {
          cout << "confused -- straight_flush\n";
        }
        break;
      }
      case FLUSH: {
        for (int i = 4; i >= 0; --i) {
          if (values_1[i] > values_2[i]) {
            return 1;
          } else if (values_1[i] < values_2[i]) {
            return 2;
          }
        }
        break;
      }
      case STRAIGHT: {
        if (values_1[0] > values_2[0]) {
          return 1;
        } else if (values_1[0] < values_2[0]) {
          return 2;
        } else {
          cout << "confused -- straight\n";
        }
        break;
      }
      case FULL_HOUSE: {
        if (values_1[2] > values_2[2]) {
          return 1;
        } else if (values_1[2] < values_2[2]) {
          return 2;
        } else {
          cout << "confused -- full_house\n";
        }
        break;
      }
      case FOUR_KIND: {
        // when sorted the index 2 has to be definitely in the 4 of a kind
        if (values_1[2] > values_2[2]) {
          return 1;
        } else if (values_1[2] < values_2[2]) {
          return 2;
        } else {
          cout << "confused -- four_kind\n";
        }
        break;
      }
      case THREE_KIND: {
        // when sorted the index 2 has to be definitely in the 4 of a kind
        if (values_1[2] > values_2[2]) {
          return 1;
        } else if (values_1[2] < values_2[2]) {
          return 2;
        } else {
          cout << "confused -- three kind\n";
        }
        break;
      }
      case HIGH_CARD: {
        for (int i = 4; i >= 0; --i) {
          if (values_1[i] > values_2[i]) {
            return 1;
          } else if (values_1[i] < values_2[i]) {
            return 2;
          }
        }
        cout << "confused -- high card\n";
        break;
      }
      case ONE_PAIR: {
 #if 1
        // find pair 1
        int val_1 = 0;
        int val_2 = 0;
        for (int i = 0; i < 4; ++i) {
          if (values_1[i+1] == values_1[i]) {
            val_1 = values_1[i+1];
          }
          if (values_2[i+1] == values_2[i]) {
            val_2 = values_2[i+1];
          }
        }
        if (val_1 > val_2) {
          return 1;
        } else if (val_1 < val_2) {
          return 2;
        } else {
          int i = 4, j = 4;
          while(i>=0 && j >= 0) {
            if (values_1[i] == val_1) {
              i -= 2;
            }
            if (values_2[j] == val_2) {
              j-=2;
            }
            if (j < 0 || i < 0) {
              cout << "confused -- one pair\n";
              break;
            }
            if (values_1[i] > values_2[j]) {
              return 1;
            } else if (values_1[i] < values_2[j]) {
              return 2;
            }
          }
        }
#endif
        break;
      }
      case TWO_PAIRS: {
        cout << "confused -- two pairs\n";
        break;
      }
      case ROYAL_FLUSH: {
        cout << "confused -- royal flush\n";
        break;
      }
      default:
        cout << "confused\n";
        return 2;
    }  // end of switch
  }
  std::cout << "\n------------------\n";
  return 2;
}

int main() {
  std::ifstream is("p054_poker.txt");
  // std::ifstream is("poker.txt");
  if (!is) {
    std::cout << "error opening file \n";
  }
  std::string game_line;
  int player1_win_counter = 0;
    
  while (std::getline(std::cin, game_line)) {
    // std::cout << game_line << std::endl;
    vector<string> card_vec = Tokenize(game_line);
    int player_num = DecideWinner(card_vec);
    if (player_num == 1) {
      player1_win_counter++;
    }
  }

  std::cout << "Number of wins by player1 is " << player1_win_counter << "\n";

  return 0;
}
