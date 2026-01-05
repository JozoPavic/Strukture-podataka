#include <stdio.h>
#include <conio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>
#include<time.h>
#define Letter 2
typedef struct card* Position;
typedef struct card {
    char name;
    int numDeck;
    int id;
    int value;
    int AceValue;
    Position Next;
}Card;
int main() {
    srand(time(NULL));
    int sum = 0, sum1 = 0, sum2 = 0;
    int money = 1000;
    Card deck = { 0,0,NULL };

    Card hand = { 0,0,NULL };
    Card Secondhand = { 0,0,NULL };

    Card dealer = { 0,0,NULL };

    loadDeck(&deck);

    int ran = rand() % 13 + 1;

    int active = 1;
    int index = 0;
    int indexY = 0;
    int currentBet = 0, currentBet2 = 0;
    int confirmedBet = 0;
    int selectingBet = 1;
    int num;
    int numberOfHands = 1;
    int firstDone = 0, secondDone = 0;
    int numberOfActions = 0;
    //printer(index, sum, sum2, &hand, &dealer, money, currentBet, indexY);

    //reset(&sum, &sum2, &deck, &hand, &dealer, &confirmedBet);
    indexY = 1;
    while (active == 1) {
        while (selectingBet) {
            firstDone = 0;
            secondDone = 0;
            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
            num = _getch();
            switch (num) {
            case 75:// <-
                if (indexY == 1 && confirmedBet == 0 && currentBet != 0) {
                    currentBet = currentBet - 50;
                }
                printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

                // 
                break;

            case 77://->
                if (indexY == 1 && confirmedBet == 0 && currentBet < money) {
                    currentBet = currentBet + 50;
                }
                printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                break;
            case 72:// ^
                indexY--;
                if (indexY < 1) {
                    indexY = 2;
                }
                printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

                // 
                break;
            case 80:// ˇ
                indexY++;
                if (indexY > 2) {
                    indexY = 1;
                }
                printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                // 
                break;
            case 13://ENTER
                if (indexY == 2) {

                    active = 0;
                    printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                    delete(&dealer);
                    delete(&Secondhand);
                    delete(&hand);
                    delete(&deck);
                    printf("\nCOWARD");
                    return 0;
                }
                if (currentBet > 0 && currentBet <= money) {
                    confirmedBet = 1;
                    indexY = 0;
                    selectingBet = 0;
                    index = 0;
                    //reset(&sum, &sum2, &deck, &hand, &dealer, &confirmedBet);
                    sum = sum + out2(deck.Next, sum, &hand);
                    printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                    wait();
                    sum2 = sum2 + out2(deck.Next, sum2, &dealer);
                    printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                    wait();
                    sum = sum + out2(deck.Next, sum, &hand);
                    //sum2 = sum2 + out2(deck.Next, sum2, &dealer);
                    printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                }
                if (sum == 21) {
                    printf("\nYOU WIN");
                    money = money + currentBet;
                    //active = 0;
                    printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                    wait();
                    indexY = 1;
                    reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands);
                    selectingBet = 1;
                }
                break;
            }
        }
        num = _getch();
        switch (num) {
        case 75:// <-
            if (indexY == 1 && confirmedBet == 0) {
                currentBet = currentBet - 50;
            }
            else {
                index--;
                if (index < 0) {
                    index = 3;
                }
            }
            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

            // 
            break;

        case 77://->
            if (indexY == 1 && confirmedBet == 0) {
                currentBet = currentBet + 50;
            }
            else {
                index++;
                if (index > 3) {
                    index = 0;
                }

            }
            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
            break;
        case 72:// ^
            indexY--;
            if (indexY < 0) {
                indexY = 2;
            }
            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

            // 
            break;
        case 80:// ˇ
            indexY++;
            if (indexY > 2) {
                indexY = 0;
            }
            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

            // 
            break;
        case 13://ENTER

            if (indexY == 2) {

                active = 0;
                printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                printf("\nCOWARD");
                delete(&dealer);
                delete(&Secondhand);
                delete(&hand);
                delete(&deck);
                return 0;
            }
            if (index == 0) {
                numberOfActions++;
                if (numberOfHands > 1) {
                    if (firstDone == 0) {
                        sum = sum + out2(deck.Next, sum, &hand);

                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                        if (sum >= 21) {

                            //active = 0;
                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            wait();
                            firstDone = 1;

                        }
                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                    }
                    else {
                        sum1 = sum1 + out2(deck.Next, sum1, &Secondhand);

                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                        if (sum1 >= 21) {

                            //active = 0;
                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            wait();

                            //Napravi STAY
                            while (sum2 < 17) {
                                sum2 = sum2 + out2(deck.Next, sum2, &dealer);
                                printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                                wait();
                            }
                            //printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

                            compareTwoHands(sum, sum1, sum2, &money, &currentBet, &currentBet2);

                            //printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands);
                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

                            indexY = 1;
                            selectingBet = 1;
                        }

                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                    }
                }
                else {
                    if (currentBet <= money && currentBet > 0) {
                        sum = sum + out2(deck.Next, sum, &hand);
                        confirmedBet = 1;
                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                        if (sum == 21) {
                            //printf("\nYOU WIN");
                            wait();
                            money = money + currentBet;

                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            indexY = 1;
                            reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands);
                            selectingBet = 1;

                        }
                        if (sum > 21) {
                            //printf("\nYOU LOSE");
                            wait();
                            money = money - currentBet;

                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            indexY = 1;
                            reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands);
                            selectingBet = 1;

                        }
                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                    }
                }

            }//STAY
            else if (index == 1) {
                numberOfActions++;
                if (numberOfHands > 1) {
                    if (firstDone == 1) {
                        while (sum2 < 17) {
                            sum2 = sum2 + out2(deck.Next, sum2, &dealer);
                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            wait();
                        }
                        //printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

                        compareTwoHands(sum, sum1, sum2, &money, &currentBet, &currentBet2);

                        //printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                        reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands);
                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

                        indexY = 1;
                        selectingBet = 1;
                    }
                    else {
                        firstDone = 1;
                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                    }
                }
                else {
                    while (sum2 <= sum && sum2 < 17) {
                        sum2 = sum2 + out2(deck.Next, sum2, &dealer);
                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                        wait();
                    }
                    // printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                    if (sum2 > 21 || sum2 < sum) {
                        //printf("\nYOU WIN");
                        money = money + currentBet;

                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

                        reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands);
                    }
                    else if (sum2 > sum) {
                        //printf("\nYOU LOSE");
                        money = money - currentBet;

                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

                        reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands);
                    }
                    else if (sum2 == sum) {

                        reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands);
                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

                    }
                    printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

                    indexY = 1;
                    selectingBet = 1;
                }

            }
            else if (index == 2) {

                if (currentBet * 2 <= money) {
                    numberOfActions++;
                    if (numberOfHands > 1) {
                        if (firstDone == 0) {
                            sum = sum + out2(deck.Next, sum, &hand);
                            currentBet = 2 * currentBet;
                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            firstDone = 1;
                            //Pomakni strelicu
                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            break;

                        }
                        else {
                            sum1 = sum1 + out2(deck.Next, sum1, &Secondhand);
                            currentBet2 = currentBet2 * 2;

                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

                            //STAY
                            while (sum2 < 17) {
                                sum2 = sum2 + out2(deck.Next, sum2, &dealer);
                                printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                                wait();
                            }
                            //printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);


                            compareTwoHands(sum, sum1, sum2, &money, &currentBet, &currentBet2);


                            //printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands);
                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

                            indexY = 1;
                            selectingBet = 1;
                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                        }
                    }
                    else {
                        currentBet = currentBet * 2;
                        //HIT
                        sum = sum + out2(deck.Next, sum, &hand);
                        confirmedBet = 1;
                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                        wait();
                        if (sum == 21) {
                            //printf("\nYOU WIN");
                            money = money + currentBet;
                            //active = 0;
                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            indexY = 1;
                            reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands);
                            selectingBet = 1;
                            break;
                        }
                        if (sum > 21) {
                            //printf("\nYOU LOSE");
                            money = money - currentBet;
                            //active = 0;
                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            indexY = 1;
                            reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands);
                            selectingBet = 1;
                            break;
                        }
                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                        //STAY
                        while (sum2 <= sum && sum2 < 17) {
                            sum2 = sum2 + out2(deck.Next, sum2, &dealer);
                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            wait();
                        }
                        //wait();
                        //printer(index, sum, sum2, &hand, &dealer, money, currentBet, indexY);
                        if (sum2 > 21 || sum2 < sum) {
                            printf("\nYOU WIN");
                            money = money + currentBet;
                            //active = 0;
                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            //wait();
                            indexY = 1;
                            reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands);
                            //printer(index, sum, sum2, &hand, &dealer, money, currentBet, indexY);
                            selectingBet = 1;
                            break;
                        }
                        else if (sum2 > sum) {
                            //printf("\nYOU LOSE");
                            money = money - currentBet;
                            //active = 0;
                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

                            //wait();
                            indexY = 1;
                            reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands);
                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            selectingBet = 1;
                            break;

                        }
                        else if (sum2 == sum) {
                            indexY = 1;
                            reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands);
                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            selectingBet = 1;
                            break;
                        }

                    }


                    reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands);
                    printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

                }



            }
            else if (index == 3) {
                if (currentBet * 2 <= money && numberOfActions == 0) {
                    if (hand.Next->Next->id == hand.Next->id) {
                        numberOfHands = 2;
                        currentBet2 = currentBet;
                        splitHand(&hand, &Secondhand, &sum, &sum1);
                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                        numberOfActions++;
                    }
                }
                else {
                    //printf("\n  %d", numberOfActions);
                }

            }
            break;

        }
        //POPRAVI RESET, NAPRAVI POKAZIVAC ZA KOJU RUKU, NAPRAVI DA JE MOGUCE SPLIT SAMO NA POCETKU
        if (money == 0) {
            active = 0;
            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
            printf("\nOUT OF MONEY\n");
            delete(&dealer);
            delete(&Secondhand);
            delete(&hand);
            delete(&deck);
        }



    }
    return 0;
}

int wait() {
    int second = 2;
    while (second > 0) {
        clock_t stop = clock() + CLOCKS_PER_SEC;
        while (stop > clock()) {

        }
        second--;
    }
    return 0;
}
int reset(int* sum, int* sum1, int* sum2, Position deck, Position hand, Position Secondhand, Position dealer, int* confirmedBet, int* numberOfActions, int* numberOfHands) {
    delete(hand);
    delete(Secondhand);
    delete(dealer);
    resetDeck(deck);
    *sum = 0;
    *sum1 = 0;
    *sum2 = 0;

    *confirmedBet = 0;
    *numberOfActions = 0;
    *numberOfHands = 1;
    return 0;
}
int splitHand(Position FirstHand, Position SecondHand, int* sum, int* sum1) {
    FirstHand = FirstHand->Next;

    SecondHand->Next = FirstHand->Next;
    FirstHand->Next = NULL;
    *sum1 = *sum / 2;
    *sum = *sum / 2;
    return 0;
}
int compareTwoHands(int sum, int sum1, int sum2, int* money, int* currentBet, int* currentBet2) {

    if (sum > 21) {
        *money = *money - *currentBet;
    }
    else if (sum == 21 && sum > sum2) { *money = *money + *currentBet; }
    else {
        if (sum2 < 22) {
            if (sum2 > sum) {
                *money = *money - *currentBet;
            }
            else if (sum2 == sum) { *money = *money - 0; }
            else {
                *money = *money + *currentBet;
            }

        }
        else {
            *money = *money + *currentBet;
        }
    }

    if (sum1 > 21) {
        *money = *money - *currentBet2;
    }
    else if (sum1 == 21 && sum1 > sum2) { *money = *money + *currentBet2; }
    else {
        if (sum2 < 22) {
            if (sum2 > sum1) {
                *money = *money - *currentBet2;
            }
            else if (sum2 == sum1) { *money = *money - 0; }
            else {
                *money = *money + *currentBet2;
            }

        }
        else {
            *money = *money + *currentBet2;
        }
    }

    *currentBet2 = 0;
    return 0;
}
int delete(Position Start) {
    Position temp, First = Start->Next;
    while (Start->Next != NULL) {

        temp = Start->Next;
        Start->Next = temp->Next;
        //Postavlja next na NULL
        temp->Next = NULL;
        //Izbriši
        free(temp);
    }
    return 0;
}
int resetDeck(Position Start) {
    Position First = Start->Next;
    while (First != NULL) {
        First->numDeck = 1;
        First = First->Next;
    }
    return 0;
}
int printHand(Position First) {
    if (First == NULL) {
        return 0;
    }

    while (First != NULL) {
        if (First->name == 'T') {
            printf("|10| ");
        }
        else {
            printf("|%c| ", First->name);
        }
        First = First->Next;
    }
    //printf("\n");
    return 0;
}
int printer(int index, int sum, int sum1, int sum2, Position hand, Position hand2, Position dealer, int money, int currentBet, int indexY, int firstDone) {

    char space = NULL;
    system("cls");
    printf("YOU %d %d DEALER %d%30cMoney:%d$\n", sum, sum1, sum2, space, money);
    if (firstDone == 0) {
        printf("> ");
    }
    else { printf("  "); }
    if (hand != NULL) {
        if (printHand(hand->Next) == 0) {
            printf("\n");
        }
        else {
            printHand(hand->Next);
        }
    }
    if (firstDone == 1) {
        printf("> ");
    }
    else { printf("  "); }
    if (hand2 != NULL) {
        if (printHand(hand2->Next) == 0) {
            printf("\n");
        }
        else {
            printHand(hand2->Next);
        }

    }
    printf("  ");
    if (dealer != NULL) {
        if (printHand(dealer->Next) == 0) {
            printf("\n");
        }
        else {
            printHand(dealer->Next);
        }
    }

    if (indexY == 0) {
        if (index == 0) {

            printf("> ");
            printf("HIT         ");
            printf("  STAY        ");
            printf("  DOUBLEDOWN        ");
            printf("  SPLIT        \n");

            printf("    BET:<-   %d   ->\n", currentBet);
            printf("  EXIT        \n");
        }
        else if (index == 1) {


            printf("  HIT         ");
            printf("> ");
            printf("STAY        ");
            printf("  DOUBLEDOWN        ");
            printf("  SPLIT        \n");
            printf("    BET:<-   %d   ->\n", currentBet);
            printf("  EXIT        \n");
        }
        else if (index == 2) {


            printf("  HIT         ");
            printf("  STAY        ");
            printf("> ");
            printf("DOUBLEDOWN        ");
            printf("  SPLIT        \n");
            printf("    BET:<-   %d   ->\n", currentBet);
            printf("  EXIT        \n");
        }
        else if (index == 3) {

            printf("  HIT         ");
            printf("  STAY        ");
            printf("  DOUBLEDOWN        ");
            printf("> ");
            printf("SPLIT        \n");
            printf("    BET:<-   %d   ->\n", currentBet);
            printf("  EXIT        \n");
        }

    }
    else if (indexY == 1) {
        printf("  HIT         ");
        printf("  STAY        ");
        printf("  DOUBLEDOWN        ");
        printf("  SPLIT        \n");
        printf("  > ");
        printf("BET:<-   %d   ->\n", currentBet);
        printf("  EXIT        \n");
    }
    else if (indexY == 2) {
        printf("  HIT         ");
        printf("  STAY        ");
        printf("  DOUBLEDOWN        ");
        printf("  SPLIT        \n");
        printf("    BET:<-   %d   ->\n", currentBet);
        printf("> ");
        printf("EXIT        \n");
    }
    printf("\n");
    return 0;
}
int loadDeck(Position Start) {
    for (int j = 0; j < 4; j++) {

        int i = 13;
        while (i > 0) {
            Position Q = malloc(sizeof(Card));
            if (Q == NULL) {
                return -1;
            }
            if (i == 1) {
                Q->value = 11;
            }
            if (i > 10) {
                Q->value = 10;
            }
            else {
                Q->value = i;
            }
            Q->name = malloc(sizeof(char) * 2);

            Q->id = i;
            if (Q->id == 13) {
                Q->name = 'K';
            }
            else if (Q->id == 12) {
                Q->name = 'Q';
            }
            else if (Q->id == 11) {
                Q->name = 'J';
            }
            else if (Q->id == 10) {
                Q->name = 'T';
            }
            else if (Q->id == 1) {
                Q->name = 'A';
            }
            else {
                Q->name = Q->id;
            }
            Q->numDeck = 1;

            Q->Next = Start->Next;
            Start->Next = Q;
            i--;
        }
    }

    return 0;
}
int checkAce(Position First) {
    Position Start = First;
    while (Start != NULL) {
        if (Start->AceValue == 11) {
            Start->AceValue = 1;
            return 1;
        }
        Start = Start->Next;
    }
    return 0;
}
int out2(Position First, int sum, Position Hand) {
    int again = 0;
    Position Start = First;
    Position P = Hand;
    int ran;
    do {
        again = 0;
        ran = rand() % 52 + 1;

        for (int i = 0; i < ran - 1; i++) {
            Start = Start->Next;
        }
        if (Start->numDeck <= 0) {
            Start = First;
            again = 1;
        }

    } while (again == 1 || Start->numDeck <= 0);

    Position newCard = malloc(sizeof(Card));
    if (newCard == NULL) {
        return -1;
    }
    if (Start->name == 'K' || Start->name == 'Q' || Start->name == 'J' || Start->name == 'A' || Start->name == 'T') {
        newCard->name = Start->name;
    }
    else {
        newCard->name = Start->name + '0';
    }

    newCard->Next = P->Next;
    P->Next = newCard;
    newCard->id = Start->id;
    //Postavi sve na 0, pa ako je zapravo A stavit ce 1 ili 11
    newCard->AceValue = 0;
    if (ran == 1) {
        newCard->AceValue = 11;
    }

    Start->numDeck--;
    //printf("%d\n", Start->id);
    //printf("%d\n", Start->numDeck);
    //ACE
    if (ran > 39) {
        ran = ran - 13;
    }
    if (ran > 26) {
        ran = ran - 13;
    }
    if (ran > 13) {
        ran = ran - 13;
    }
    if (ran == 1) {
        if (sum + 11 > 21) {
            newCard->AceValue = 1;
            return 1;
        }
        else {
            newCard->AceValue = 11;
            return 11;
        }
    }
    //QUEEN JACK OR KING
    if (ran > 10) {
        if (sum + 10 > 21) {
            if (checkAce(Hand) == 1) {
                return 0;
            }
        }

        return 10;
    }
    //NUM CARD
    else {
        if (sum + ran > 21) {
            if (checkAce(Hand) == 1) {
                return ran - 10;
            }
        }

        return ran;
    }
    return 0;
}
