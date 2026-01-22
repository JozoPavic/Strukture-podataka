#include <stdio.h>
#include <conio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>
#include<time.h>
int setUp = 0;
typedef struct card* Position;
typedef struct card {
    char name;
    int numDeck;//koliko je ima u spilu
    int id;//id karte
    int value;//vrijednost karte
    int AceValue;//Samo za aseve
    Position Next;
}Card;
int main() {
    srand(time(NULL));
    //SUME svih mogucih ruku prve 2 za igraca, sum2 za dealer-a
    int sum = 0, sum1 = 0, sum2 = 0;
    int money = 1000;
    //Liste
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

    indexY = 1;
    while (active == 1) {
        //Odabir koliko ulazemo
        while (selectingBet) {
            //Resetiramo stanja ruku
            firstDone = 0;
            secondDone = 0;
            //Nacrtaj ekran/stol
            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
            //Uzima char sa tipkovnice bez potrebe za ENTER-om
            num = _getch();
            switch (num) {
                //indexY =1 onda stojimo na opciji za ulog novca
            case 75:// <- min ulog je 50, max je ALLIN (sav novac koji imas)
                if (indexY == 1 && confirmedBet == 0 && currentBet != 0) {
                    currentBet = currentBet - 50;
                }//Kako upires strelicu tako se poziva funkcija koja crta da vidis svoj ulog
                printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

                // 
                break;

            case 77://->
                if (indexY == 1 && confirmedBet == 0 && currentBet < money) {
                    currentBet = currentBet + 50;
                }//Kako upires strelicu tako se poziva funkcija koja crta da vidis svoj ulog
                printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                break;
            case 72:// ^
                //Strelica prema gore smanjuje indexY, dok ulazes novac ce se vracati između opcije za ulog i EXIT-a
                indexY--;
                if (indexY < 1) {
                    indexY = 2;
                }
                printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

                // 
                break;
            case 80:// ˇ
                //Strelica prema dolje povecava indexY, dok ulazes novac ce se vracati između opcije za ulog i EXIT-a
                indexY++;
                if (indexY > 2) {
                    indexY = 1;
                }
                printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                // 
                break;
            case 13://ENTER
                //Ako je indexY=2 onda smo na opciji EXIT
                if (indexY == 2) {
                    //Izlazi iz igre, brise sve liste
                    active = 0;
                    printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                    delete(&dealer);
                    delete(&Secondhand);
                    delete(&hand);
                    delete(&deck);
                    printf("\nCOWARD");
                    return 0;
                }
                //Ako je ulog vazeci
                if (currentBet > 0 && currentBet <= money) {

                    confirmedBet = 1;
                    indexY = 0;
                    //Vise nemozemo promjeniti ulog 
                    selectingBet = 0;
                    index = 0;

                    //Izvalcimo kartu(za igraca) sa out2, pa sa printer-om nacrtamo pa sa wait sacekamo 2 sek
                    sum = sum + out2(deck.Next, sum, &hand);
                    printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                    wait();
                    //Izvalcimo kartu(za dealer-a) sa out2, pa sa printer-om nacrtamo pa sa wait sacekamo 2 sek
                    sum2 = sum2 + out2(deck.Next, sum2, &dealer);
                    printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                    wait();
                    //Ponovno izvucemo kartu za igraca, pa nacrtamo
                    sum = sum + out2(deck.Next, sum, &hand);

                    printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                }//Ako vec u prve 2 karte izvucemo 21 automatska pobjeda
                if (sum == 21) {
                    //printf("\nYOU WIN");
                    //Povecaj novac za trenutni ulog
                    money = money + currentBet;
                    //Nacrtaj pa sacekaj, 
                    printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                    wait();
                    //Resetiraj, postavi strelicu na opciju odabira uloga
                    indexY = 1;
                    reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands, &currentBet);
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
            else if (indexY == 0) {
                //Pomak po 4 opcije ako dođe na kraj vrati ga na pocetak
                index--;
                if (index < 0) {
                    index = 3;
                }
            }
            //Nacrtaj pomicanje strelice
            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

            // 
            break;

        case 77://->
            if (indexY == 1 && confirmedBet == 0) {
                currentBet = currentBet + 50;
            }
            else if (indexY == 0) {
                //Pomak po 4 opcije ako dođe na kraj vrati ga na pocetak
                index++;
                if (index > 3) {
                    index = 0;
                }

            }//Nacrtaj pomicanje strelice
            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
            break;
        case 72:// ^
            indexY--;
            if (indexY < 0) {
                indexY = 2;
            }//Nacrtaj pomicanje strelice
            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

            // 
            break;
        case 80:// ˇ
            indexY++;
            if (indexY > 2) {
                indexY = 0;
            }//Nacrtaj pomicanje strelice
            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

            // 
            break;
        case 13://ENTER
            //Ako je na opciji EXIT
            if (indexY == 2) {
                //Izlazi iz igre, brise sve liste
                active = 0;
                printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                printf("\nCOWARD");
                delete(&dealer);
                delete(&Secondhand);
                delete(&hand);
                delete(&deck);
                return 0;
            }//HIT - vuci kartu
            if (index == 0) {
                //povecaj broj akcija tkd se moze SPLIT samo na pocetku
                numberOfActions++;
                //U slucaju da je odabrana opcija SPLIT
                if (numberOfHands > 1) {
                    //Za prvu ruku 
                    if (firstDone == 0) {
                        //vuci kartu i nacrtaj
                        sum = sum + out2(deck.Next, sum, &hand);

                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                        //Ako je ima 21 ili vise odmah prebaci na drugu ruku
                        if (sum >= 21) {

                            //Nacrtaj ruku i pricekaj pa prebaci se na drugu ruku(igras sa drugom rukom)
                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            wait();
                            firstDone = 1;

                        }
                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                    }
                    else {//Za drugu ruku 
                        sum1 = sum1 + out2(deck.Next, sum1, &Secondhand);

                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                        //Ako je ima 21 ili vise odmah Dealer krece izvlaciti karte tj. tvoj potez je zavrsen
                        if (sum1 >= 21) {

                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            wait();

                            //Napravi STAY
                            while (sum2 < 17) {
                                //Vuce, nacrta kartu pa saceka 2s
                                sum2 = sum2 + out2(deck.Next, sum2, &dealer);
                                printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                                wait();
                            }

                            //Uspoređuje ruke
                            compareTwoHands(sum, sum1, sum2, &money, &currentBet, &currentBet2);
                            //resetira i ponovno nacrta prazan stol
                            reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands, &currentBet);
                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            //Ponovno mozemo odabirati ulog
                            indexY = 1;
                            selectingBet = 1;
                        }

                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                    }
                }
                else {//NIJE SPLIT - igramo sa 1 rukom
                    if (currentBet <= money && currentBet > 0) {
                        //Vuci kartu
                        sum = sum + out2(deck.Next, sum, &hand);
                        confirmedBet = 1;
                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                        //Ako ima 21 - pobjeda
                        if (sum == 21) {
                            //printf("\nYOU WIN");
                            //Povecaj novac
                            wait();
                            money = money + currentBet;
                            //nacrtaj novac
                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            indexY = 1;
                            //Resetiraj sve da opet mozemo igrat
                            reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands, &currentBet);
                            selectingBet = 1;

                        }//Izgubio
                        if (sum > 21) {
                            //printf("\nYOU LOSE");
                            wait();//Smanji novac
                            money = money - currentBet;
                            //Resetiraj sve da opet mozemo igrat
                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            indexY = 1;
                            reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands, &currentBet);
                            selectingBet = 1;

                        }
                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                    }
                }

            }//STAY
            else if (index == 1) {
                //Povecaj broj akcija 
                numberOfActions++;
                //Ako je split-ano
                if (numberOfHands > 1) {
                    //DRUGA RUKA
                    if (firstDone == 1) {
                        //Dealer krece izvlaciti karte
                        while (sum2 < 17) {
                            sum2 = sum2 + out2(deck.Next, sum2, &dealer);
                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            wait();
                        }
                        //Usporedi sve 3 ruke

                        compareTwoHands(sum, sum1, sum2, &money, &currentBet, &currentBet2);

                        //resetiraj da se opet moze igrat
                        reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands, &currentBet);
                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

                        indexY = 1;
                        selectingBet = 1;
                    }//PRVA RUKA
                    else {
                        //PREBACI SE NA DRUGU RUKU
                        firstDone = 1;
                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                    }
                }
                else {//SAMO jedna ruka
                    //Dealer izvlaci
                    while (sum2 <= sum && sum2 < 17) {
                        sum2 = sum2 + out2(deck.Next, sum2, &dealer);
                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                        wait();
                    }
                    //Ako je dealer prekoracia 21 ili ima manje od igraca
                    if (sum2 > 21 || sum2 < sum) {
                        //printf("\nYOU WIN");

                        //Povecaj novac pa resetiraj
                        money = money + currentBet;
                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                        reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands, &currentBet);
                    }
                    else if (sum2 > sum) {
                        //printf("\nYOU LOSE");

                        //Smanji novac pa resetiraj
                        money = money - currentBet;
                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                        reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands, &currentBet);
                    }
                    //Ako je izjednaceno
                    else if (sum2 == sum) {

                        reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands, &currentBet);
                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

                    }
                    //Vrati na opciju za ulog
                    printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

                    indexY = 1;
                    selectingBet = 1;
                }

            }//DOUBLE DOWN - 1 HIT pa STAY
            else if (index == 2) {

                if (currentBet * 2 <= money) {
                    numberOfActions++;
                    //Ako imamo 2 ruke
                    if (numberOfHands > 1) {

                        //PRVA RUKA 
                        if (firstDone == 0) {
                            if ((currentBet * 2 + currentBet2) <= money) {
                                //vuci kartu
                                sum = sum + out2(deck.Next, sum, &hand);
                                //udvostruci ulog za tu ruku
                                currentBet = 2 * currentBet;

                                printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                                //Promjeni ruku
                                firstDone = 1;
                                //Pomakni strelicu
                                printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                                break;
                            }
                            else {}
                        }
                        else {//DRUGA RUKA
                            if ((currentBet2 * 2 + currentBet) <= money) {
                                //vuci kartu
                                sum1 = sum1 + out2(deck.Next, sum1, &Secondhand);
                                //Udvostruci ulog za tu ruku
                                currentBet2 = currentBet2 * 2;

                                printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

                                //STAY
                                while (sum2 < 17) {
                                    //DEALER KRECE IZVLACITI KARTE
                                    sum2 = sum2 + out2(deck.Next, sum2, &dealer);
                                    printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                                    wait();
                                }
                                //Usporedi rukue

                                compareTwoHands(sum, sum1, sum2, &money, &currentBet, &currentBet2);

                                //Resetiraj
                                reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands, &currentBet);
                                printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

                                indexY = 1;
                                selectingBet = 1;
                                printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            }
                            else {}
                        }
                    }
                    else {//Samo 1 ruka - nema SPLIT-a
                        //Udvostruci ulog
                        currentBet = currentBet * 2;
                        //HIT
                        sum = sum + out2(deck.Next, sum, &hand);
                        confirmedBet = 1;
                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                        wait();
                        //Ako je 21 - automatska pobjeda
                        if (sum == 21) {
                            //printf("\nYOU WIN");ž
                            //Povecaj novac - nacrtaj pa resetiraj
                            money = money + currentBet;
                            //active = 0;
                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            indexY = 1;
                            reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands, &currentBet);
                            selectingBet = 1;
                            break;
                        }//Igrac je prekoracio
                        if (sum > 21) {
                            //printf("\nYOU LOSE");
                            //Smanji novac - nacrtaj pa resetiraj
                            money = money - currentBet;
                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            indexY = 1;
                            reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands, &currentBet);
                            selectingBet = 1;
                            break;
                        }
                        //Ako igrac nije prekoracio Dealer izvalci karte
                        printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                        //STAY
                        while (sum2 <= sum && sum2 < 17) {
                            sum2 = sum2 + out2(deck.Next, sum2, &dealer);
                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            wait();
                        }
                        //Igrac pobjedio
                        if (sum2 > 21 || sum2 < sum) {
                            //printf("\nYOU WIN");
                            money = money + currentBet;

                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            //Resetiraj
                            indexY = 1;
                            reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands, &currentBet);
                            selectingBet = 1;
                            break;
                        }//Igrac izgubio
                        else if (sum2 > sum) {
                            //printf("\nYOU LOSE");
                            money = money - currentBet;
                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

                            //Resetiraj
                            indexY = 1;
                            reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands, &currentBet);
                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            selectingBet = 1;
                            break;

                        }//nerjeseno
                        else if (sum2 == sum) {
                            //Resetiraj
                            indexY = 1;
                            reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands, &currentBet);
                            printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);
                            selectingBet = 1;
                            break;
                        }

                    }


                    //reset(&sum, &sum1, &sum2, &deck, &hand, &Secondhand, &dealer, &confirmedBet, &numberOfActions, &numberOfHands);
                    //printer(index, sum, sum1, sum2, &hand, &Secondhand, &dealer, money, currentBet, indexY, firstDone);

                }



            }//SPLIT opcija
            else if (index == 3) {
                //Ako igrac ima dovoljno novca tj. treba duplo ulozit i mora SPLIT biti odmah na pocetku
                if (currentBet * 2 <= money && numberOfActions == 0) {
                    //Ako ima dvije iste karte
                    if (hand.Next->Next->id == hand.Next->id) {
                        //Povecaj broj ruku i ulog za drugu ruku
                        numberOfHands = 2;
                        currentBet2 = currentBet;
                        //Stvori drugu ruku od karata prve
                        splitHand(&hand, &Secondhand, &sum, &sum1);
                        //Nacrtaj
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
        //Izgubis sav novac = EXIT
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
    //Koliko cekamo
    int second = 2;
    while (second > 0) {
        clock_t stop = clock() + CLOCKS_PER_SEC;
        while (stop > clock()) {

        }
        second--;
    }
    return 0;
}
int reset(int* sum, int* sum1, int* sum2, Position deck, Position hand, Position Secondhand, Position dealer, int* confirmedBet, int* numberOfActions, int* numberOfHands, int* currentBet) {
    //Obrisi ruke igraca i dealera
    delete(hand);
    delete(Secondhand);
    delete(dealer);
    //Resetiraj spil ne brisat tkd ne brisemo i ponovno unosimo 52 el u listu svaki put kada opet idemo igrati
    resetDeck(deck);
    //Resetiraj sume
    *sum = 0;
    *sum1 = 0;
    *sum2 = 0;
    //Resetiraj 
    *confirmedBet = 0;
    *numberOfActions = 0;
    *numberOfHands = 1;
    *currentBet = 0;
    setUp = 0;
    return 0;
}
int splitHand(Position FirstHand, Position SecondHand, int* sum, int* sum1) {
    //Prebaci se na 1 el liste prve ruke
    FirstHand = FirstHand->Next;
    //Prvi el (koji nije head) druge liste postaje ona karta koju je igrac zadnju izvukao
    SecondHand->Next = FirstHand->Next;
    //Mici tu kartu iz igraceve prve ruke
    FirstHand->Next = NULL;
    //Podjeli sume tih dviju ruku npr. Prva ruka su dvije 8 - sume su obje 8
    *sum1 = *sum / 2;
    *sum = *sum / 2;
    return 0;
}
int compareTwoHands(int sum, int sum1, int sum2, int* money, int* currentBet, int* currentBet2) {
    //Usporedba sume prve ruke sa dealer-ovom rukom
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
    //Usporedba sume druge ruke sa dealer-ovom rukom
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
    //Izbrisi listu
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
    //Idemo cijelim spilom i postavljamo svaku kartu na numDeck=1
    Position First = Start->Next;
    while (First != NULL) {
        First->numDeck = 1;
        First = First->Next;
    }
    return 0;
}
int printHand(Position First) {
    //Ako nema karata u ruci
    if (First == NULL) {
        return 0;
    }

    while (First != NULL) {
        //U slucaju da je 10, ima ime T jer char moze podnjeti 1 znak
        if (First->name == 'T') {
            printf("|10| ");
        }//Bilo koja druga karta nacrtaj njeno ime
        else {
            printf("|%c| ", First->name);
        }
        First = First->Next;
    }

    return 0;
}
int printer(int index, int sum, int sum1, int sum2, Position hand, Position hand2, Position dealer, int money, int currentBet, int indexY, int firstDone) {

    char space = NULL;
    //Ocisti ekran
    system("cls");
    //Napisi vrijednosti - u slucaju da je samo 1 ruka ili 2 
    if (sum1 == 0) {
        printf("YOU %d    DEALER %d%28cMoney:%d$\n", sum, sum2, space, money);
    }
    else {
        printf("YOU %d %d DEALER %d%28cMoney:%d$\n", sum, sum1, sum2, space, money);
    }

    for (int i = 0; i < 57; i++) {
        printf("_");
    }
    printf("\nDEALER%18c", space);

    if (dealer != NULL) {
        if (printHand(dealer->Next) == 0) {
            printf("\n");
        }
        else {
            printHand(dealer->Next);
        }
    }
    printf("\n\nYOU%19c", space);

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

    printf("%22c", space);

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

    for (int i = 0; i < 57; i++) {
        printf("-");
    }
    printf("\n");
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
    //Ponovi 4 puta
    for (int j = 0; j < 4; j++) {

        int i = 13;
        while (i > 0) {
            //Alociraj novi el tj. kartu
            Position Q = malloc(sizeof(Card));
            //Greska
            if (Q == NULL) {
                return -1;
            }
            //Ace
            if (i == 1) {
                Q->value = 11;
            }//Jack, Queen, King
            if (i > 10) {
                Q->value = 10;
            }//Svi ostali imaju vrijednost od svog index-a tj. brojevi 
            else {
                Q->value = i;
            }
            Q->name = malloc(sizeof(char) * 2);
            //Postavi njihov index King - 13, 8 ima index=8
            Q->id = i;
            //Postavi imena za Ace,10,King,Queen,Jack
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
            }//Sve ostale karte imena su samo brojevi
            else {
                Q->name = Q->id;
            }
            //Postavi br. te karte u spliu na 1
            Q->numDeck = 1;
            //Ubaci u listu
            Q->Next = Start->Next;
            Start->Next = Q;
            i--;
        }
    }

    return 0;
}
int checkAce(Position First) {
    //Prodi cijelom listom
    Position Start = First;
    while (Start != NULL) {
        //ako je AceValue neke karte 11 tj. ima neiskoristenog asa
        if (Start->AceValue == 11) {
            //postavi mu vrijednost na 1, vrati istinu
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
    int ran, i = 0;
    do {
        again = 0;
        ran = rand() % 52 + 1;
        /*if (setUp == 0 || setUp == 2) {
            ran = 5 + 13 * setUp;

        }
        else {
            ran = rand() % 52 + 1;
        }
        setUp++;*/
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
    //Ubaci ispred
    newCard->Next = P->Next;
    P->Next = newCard;
    //Postavi Id karte
    newCard->id = Start->id;
    //Postavi sve na 0, pa ako je zapravo A stavit ce 1 ili 11
    newCard->AceValue = 0;
    if (ran == 1) {
        newCard->AceValue = 11;
    }
    //te karte vise nema u spilu
    Start->numDeck--;


    if (ran > 39) {
        ran = ran - 13;
    }
    if (ran > 26) {
        ran = ran - 13;
    }
    if (ran > 13) {
        ran = ran - 13;
    }
    //ACE - ako povucemo asa
    if (ran == 1) {
        //ako koristimo asa moramo koristiti kao 1
        if (sum + 11 > 21) {
            newCard->AceValue = 1;
            return 1;
        }
        else {//ako koristimo asa kao 11, tj suma + 11 <=21
            newCard->AceValue = 11;
            return 11;
        }
    }
    //QUEEN JACK OR KING - povucemo Q,J,K,T(10) njihova vrijednost je 10
    if (ran > 10) {
        //Ako je suma veca od 21, provjeri je li u ruci igrac ima asa
        if (sum + 10 > 21) {
            if (checkAce(Hand) == 1) {
                //ACE moze biti 11 ili 1, pa ako ga ima 10 postaje 0
                return 0;
            }
        }

        return 10;
    }
    //NUM CARD
    else {
        if (sum + ran > 21) {
            //Ako je suma veca od 21, provjeri je li u ruci igrac ima asa
            if (checkAce(Hand) == 1) {
                //smanji za 10
                return ran - 10;
            }
        }
        //nemoj smanjiti sumu
        return ran;
    }
    return 0;
}
