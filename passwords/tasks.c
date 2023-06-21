#include "tasks.h"

void executeTask1(struct users users, struct stringList *top250) {

    tryPasswords(top250, users.passwords, users.hashSetting); //checks for top 250 most common words
    tryPasswords(users.names[0], users.passwords, users.hashSetting);
    tryPasswords(users.names[1], users.passwords, users.hashSetting);
    tryPasswords(users.names[2], users.passwords, users.hashSetting);
    tryPasswords(users.names[3], users.passwords, users.hashSetting);

    struct stringList *uppercase250 = uppercaseList(top250); //same words but uppercase
    struct stringList *uppercaseName0 = uppercaseList(users.names[0]);
    struct stringList *uppercaseName1 = uppercaseList(users.names[1]);
    struct stringList *uppercaseName2 = uppercaseList(users.names[2]);
    struct stringList *uppercaseName3 = uppercaseList(users.names[3]);

    struct stringList *capital250 = capitalList(top250);   //same words but capitalized
    struct stringList *capitalName0 = capitalList(users.names[0]);
    struct stringList *capitalName1 = capitalList(users.names[1]);
    struct stringList *capitalName2 = capitalList(users.names[2]);
    struct stringList *capitalName3 = capitalList(users.names[3]);

    tryPasswords(uppercase250, users.passwords, users.hashSetting);
    tryPasswords(uppercaseName0, users.passwords, users.hashSetting);
    tryPasswords(uppercaseName1, users.passwords, users.hashSetting);
    tryPasswords(uppercaseName2, users.passwords, users.hashSetting);
    tryPasswords(uppercaseName3, users.passwords, users.hashSetting);

    tryPasswords(capital250, users.passwords, users.hashSetting);
    tryPasswords(capitalName0, users.passwords, users.hashSetting);
    tryPasswords(capitalName1, users.passwords, users.hashSetting);
    tryPasswords(capitalName2, users.passwords, users.hashSetting);
    tryPasswords(capitalName3, users.passwords, users.hashSetting);

    freeStringList(uppercase250); //cleanup
    freeStringList(uppercaseName0);
    freeStringList(uppercaseName1);
    freeStringList(uppercaseName2);
    freeStringList(uppercaseName3);
    freeStringList(capital250);
    freeStringList(capitalName0);
    freeStringList(capitalName1);
    freeStringList(capitalName2);
    freeStringList(capitalName3);

    
}
void executeTask2(struct users users, struct stringList *books) {
    //checks for words from the Books file
    tryPasswords(books, users.passwords, users.hashSetting);
    struct stringList *uppercasebooks = uppercaseList(books);
    struct stringList *capitalbooks = capitalList(books);
    tryPasswords(uppercasebooks, users.passwords, users.hashSetting);
    tryPasswords(capitalbooks, users.passwords, users.hashSetting);
    //cleanup
    freeStringList(uppercasebooks);
    freeStringList(capitalbooks);
    
}
void executeTask3(struct users users, struct stringList *top250){
    //checks for words with "xor" at the end in the top 250 words
    char *xor = "xor";
    char end = '\0';
    struct stringList *t250xor = manipulateList(top250, end, xor, 1);
    tryPasswords(t250xor, users.passwords, users.hashSetting);
    freeStringList(t250xor);
}

void executeTask4(struct users users, struct stringList *books){
    //same but in the books file
    char *xor = "xor";
    char end = '\0';
    struct stringList *booksxor = manipulateList(books, end, xor, 1);
    tryPasswords(booksxor, users.passwords, users.hashSetting);
    freeStringList(booksxor);
}

void executeTask5(struct users users){
    //same for usernames
    char *xor = "xor";
    char end = '\0';
    struct stringList *Name0xor = manipulateList(users.names[0], end, xor, 1);
    struct stringList *Name1xor = manipulateList(users.names[1], end, xor, 1);
    struct stringList *Name2xor = manipulateList(users.names[2], end, xor, 1);
    struct stringList *Name3xor = manipulateList(users.names[3], end, xor, 1);

    tryPasswords(Name0xor, users.passwords, users.hashSetting);
    tryPasswords(Name1xor, users.passwords, users.hashSetting);
    tryPasswords(Name2xor, users.passwords, users.hashSetting);
    tryPasswords(Name3xor, users.passwords, users.hashSetting);
    freeStringList(Name0xor);
    freeStringList(Name1xor);
    freeStringList(Name2xor);
    freeStringList(Name3xor);
}

void executeTask6(struct users users, struct stringList *top250){
    //checks for words ending in "zorz", same in tasks 7 and 8
    char *zorz = "zorz";
    char end = '\0';
    struct stringList *t250zorz = manipulateList(top250, end, zorz, 1);
    tryPasswords(t250zorz, users.passwords, users.hashSetting);
    freeStringList(t250zorz);
}

void executeTask7(struct users users, struct stringList *books){

    char *zorz = "zorz";
    char end = '\0';
    struct stringList *bookszorz = manipulateList(books, end, zorz, 1);
    tryPasswords(bookszorz, users.passwords, users.hashSetting);
    freeStringList(bookszorz);
}

void executeTask8(struct users users){

    char *zorz = "zorz";
    char end = '\0';
    struct stringList *Name0zorz = manipulateList(users.names[0], end, zorz, 1);
    struct stringList *Name1zorz = manipulateList(users.names[1], end, zorz, 1);
    struct stringList *Name2zorz = manipulateList(users.names[2], end, zorz, 1);
    struct stringList *Name3zorz = manipulateList(users.names[3], end, zorz, 1);

    tryPasswords(Name0zorz, users.passwords, users.hashSetting);
    tryPasswords(Name1zorz, users.passwords, users.hashSetting);
    tryPasswords(Name2zorz, users.passwords, users.hashSetting);
    tryPasswords(Name3zorz, users.passwords, users.hashSetting);
    freeStringList(Name0zorz);
    freeStringList(Name1zorz);
    freeStringList(Name2zorz);
    freeStringList(Name3zorz);
}
void executeTask9(struct users users, struct stringList *years){
    //checks for names ending in years, like tom1999 or tom99, same for tasks 10, 11, 12
    struct stringList *Name0year = combinationList(users.names[0], years);
    tryPasswords(Name0year, users.passwords, users.hashSetting);
    freeStringList(Name0year);
}
void executeTask10(struct users users, struct stringList *years){

    struct stringList *Name1year = combinationList(users.names[1], years);
    tryPasswords(Name1year, users.passwords, users.hashSetting);
    freeStringList(Name1year);
}

void executeTask11(struct users users, struct stringList *years){

    struct stringList *Name2year = combinationList(users.names[2], years);
    tryPasswords(Name2year, users.passwords, users.hashSetting);
    freeStringList(Name2year);
}

void executeTask12(struct users users, struct stringList *years){

    struct stringList *Name3year = combinationList(users.names[3], years);
    tryPasswords(Name3year, users.passwords, users.hashSetting);
    freeStringList(Name3year);
}

void executeTask13(struct users users, struct stringList *top250){
    //checks for words like [)og instead of dog, same for tasks 14 and 15
    char *replace = "[)";
    char d = 'd';
    struct stringList *t250D = manipulateList(top250, d, replace, 1);
    tryPasswords(t250D, users.passwords, users.hashSetting);
    freeStringList(t250D);
}

void executeTask14(struct users users, struct stringList *books){

    char *replace = "[)";
    char d = 'd';
    struct stringList *booksD = manipulateList(books, d, replace, 1);
    tryPasswords(booksD, users.passwords, users.hashSetting);
    freeStringList(booksD);
}

void executeTask15(struct users users){

    char *replace = "[)";
    char d =  'd';
    struct stringList *Name0D = manipulateList(users.names[0], d, replace, 1);
    struct stringList *Name2D = manipulateList(users.names[2], d, replace, 1);
    struct stringList *Name3D = manipulateList(users.names[3], d, replace, 1);
    struct stringList *Name1D = manipulateList(users.names[1], d, replace, 1);
    tryPasswords(Name1D, users.passwords, users.hashSetting);
    tryPasswords(Name2D, users.passwords, users.hashSetting);
    tryPasswords(Name3D, users.passwords, users.hashSetting);
    tryPasswords(Name0D, users.passwords, users.hashSetting);
    freeStringList(Name0D);
    freeStringList(Name1D);
    freeStringList(Name2D);
    freeStringList(Name3D);
}

void executeTask16(struct users users, struct stringList *top250){
    //checks for words like (at instead of cat, same for tasks 17 and 18
    char *replace = "(";
    char c = 'c';
    struct stringList *t250C = manipulateList(top250, c, replace, 1);
    tryPasswords(t250C, users.passwords, users.hashSetting);
    freeStringList(t250C);
}

void executeTask17(struct users users, struct stringList *books){

    char *replace = "(";
    char c = 'c';
    struct stringList *booksC = manipulateList(books, c, replace, 1);
    tryPasswords(booksC, users.passwords, users.hashSetting);
    freeStringList(booksC);
}

void executeTask18(struct users users){

    char *replace = "(";
    char c =  'c';
    struct stringList *Name0C = manipulateList(users.names[0], c, replace, 1);
    struct stringList *Name2C = manipulateList(users.names[2], c, replace, 1);
    struct stringList *Name3C = manipulateList(users.names[3], c, replace, 1);
    struct stringList *Name1C = manipulateList(users.names[1], c, replace, 1);
    tryPasswords(Name1C, users.passwords, users.hashSetting);
    tryPasswords(Name2C, users.passwords, users.hashSetting);
    tryPasswords(Name3C, users.passwords, users.hashSetting);
    tryPasswords(Name0C, users.passwords, users.hashSetting);
    freeStringList(Name0C);
    freeStringList(Name1C);
    freeStringList(Name2C);
    freeStringList(Name3C);
}

void executeTask19(struct users users, struct stringList *top250){
    //checks for words like pleaze instead of please, same for 20 and 21
    char *replace = "z";
    char s = 's';
    struct stringList *t250S = manipulateList(top250, s, replace, 1);
    tryPasswords(t250S, users.passwords, users.hashSetting);
    freeStringList(t250S);
}

void executeTask20(struct users users, struct stringList *books){

    char *replace = "z";
    char s = 's';
    struct stringList *booksS = manipulateList(books, s, replace, 1);
    tryPasswords(booksS, users.passwords, users.hashSetting);
    freeStringList(booksS);
}

void executeTask21(struct users users){

    char *replace = "z";
    char s =  's';
    struct stringList *Name0S = manipulateList(users.names[0], s, replace, 1);
    struct stringList *Name2S = manipulateList(users.names[2], s, replace, 1);
    struct stringList *Name3S = manipulateList(users.names[3], s, replace, 1);
    struct stringList *Name1S = manipulateList(users.names[1], s, replace, 1);
    tryPasswords(Name1S, users.passwords, users.hashSetting);
    tryPasswords(Name2S, users.passwords, users.hashSetting);
    tryPasswords(Name3S, users.passwords, users.hashSetting);
    tryPasswords(Name0S, users.passwords, users.hashSetting);
    freeStringList(Name0S);
    freeStringList(Name1S);
    freeStringList(Name2S);
    freeStringList(Name3S);
}

void executeTask22(struct users users, struct stringList *top250){
    //checks for words like phancy instead of fancy, same for 23 and 24
    char *replace = "ph";
    char f = 'f';
    struct stringList *t250f = manipulateList(top250, f, replace, 1);
    tryPasswords(t250f, users.passwords, users.hashSetting);
    freeStringList(t250f);
}

void executeTask23(struct users users, struct stringList *books){

    char *replace = "ph";
    char f = 'f';
    struct stringList *booksf = manipulateList(books, f, replace, 1);
    tryPasswords(booksf, users.passwords, users.hashSetting);
    freeStringList(booksf);
}

void executeTask24(struct users users){

    char *replace = "ph";
    char f =  'f';
    struct stringList *Name0F = manipulateList(users.names[0], f, replace, 1);
    struct stringList *Name2F = manipulateList(users.names[2], f, replace, 1);
    struct stringList *Name3F = manipulateList(users.names[3], f, replace, 1);
    struct stringList *Name1F = manipulateList(users.names[1], f, replace, 1);
    tryPasswords(Name1F, users.passwords, users.hashSetting);
    tryPasswords(Name2F, users.passwords, users.hashSetting);
    tryPasswords(Name3F, users.passwords, users.hashSetting);
    tryPasswords(Name0F, users.passwords, users.hashSetting);
    freeStringList(Name0F);
    freeStringList(Name1F);
    freeStringList(Name2F);
    freeStringList(Name3F);
}

void executeTask25(struct users users, struct stringList *top250){
    //checks for words like l1ke instead of like, same for 26 and 27
    char *replace = "1";
    char i = 'i';
    struct stringList *t250i = manipulateList(top250, i, replace, 1);
    tryPasswords(t250i, users.passwords, users.hashSetting);
    freeStringList(t250i);
}

void executeTask26(struct users users, struct stringList *books){

    char *replace = "1";
    char i = 'i';
    struct stringList *booksi = manipulateList(books, i, replace, 1);
    tryPasswords(booksi, users.passwords, users.hashSetting);
    freeStringList(booksi);
}

void executeTask27(struct users users){

    char *replace = "1";
    char i =  'i';
    struct stringList *Name0I = manipulateList(users.names[0], i, replace, 1);
    struct stringList *Name2I = manipulateList(users.names[2], i, replace, 1);
    struct stringList *Name3I = manipulateList(users.names[3], i, replace, 1);
    struct stringList *Name1I = manipulateList(users.names[1], i, replace, 1);
    tryPasswords(Name1I, users.passwords, users.hashSetting);
    tryPasswords(Name2I, users.passwords, users.hashSetting);
    tryPasswords(Name3I, users.passwords, users.hashSetting);
    tryPasswords(Name0I, users.passwords, users.hashSetting);
    freeStringList(Name0I);
    freeStringList(Name1I);
    freeStringList(Name2I);
    freeStringList(Name3I);
}

void executeTask28(struct users users, struct stringList *top250){
    //checks for words like m&n instead of men, same for 29 and 31
    char *replace = "&";
    char e = 'e';
    struct stringList *t250e = manipulateList(top250, e, replace, 1);
    tryPasswords(t250e, users.passwords, users.hashSetting);
    freeStringList(t250e);
}

void executeTask29(struct users users, struct stringList *books){

    char *replace = "&";
    char e = 'e';
    struct stringList *bookse = manipulateList(books, e, replace, 1);
    tryPasswords(bookse, users.passwords, users.hashSetting);
    freeStringList(bookse);
}

void executeTask30(struct users users){

    char *replace = "&";
    char e =  'e';
    struct stringList *Name0e = manipulateList(users.names[0], e, replace, 1);
    struct stringList *Name2e = manipulateList(users.names[2], e, replace, 1);
    struct stringList *Name3e = manipulateList(users.names[3], e, replace, 1);
    struct stringList *Name1e = manipulateList(users.names[1], e, replace, 1);
    tryPasswords(Name1e, users.passwords, users.hashSetting);
    tryPasswords(Name2e, users.passwords, users.hashSetting);
    tryPasswords(Name3e, users.passwords, users.hashSetting);
    tryPasswords(Name0e, users.passwords, users.hashSetting);
    freeStringList(Name0e);
    freeStringList(Name1e);
    freeStringList(Name2e);
    freeStringList(Name3e);
}

void executeTask31(struct users users, struct stringList *top250){
    //checks for words like me[\] instead of men, same for 32 and 33
    char *replace = "[\\]";
    char n = 'n';
    struct stringList *t250n = manipulateList(top250, n, replace, 1);
    tryPasswords(t250n, users.passwords, users.hashSetting);
    freeStringList(t250n);
}

void executeTask32(struct users users, struct stringList *books){

    char *replace = "[\\]";
    char n = 'n';
    struct stringList *booksn = manipulateList(books, n, replace, 1);
    tryPasswords(booksn, users.passwords, users.hashSetting);
    freeStringList(booksn);
}

void executeTask33(struct users users){

    char *replace = "[\\]";
    char n =  'n';
    struct stringList *Name0n = manipulateList(users.names[0], n, replace, 1);
    struct stringList *Name2n = manipulateList(users.names[2], n, replace, 1);
    struct stringList *Name3n = manipulateList(users.names[3], n, replace, 1);
    struct stringList *Name1n = manipulateList(users.names[1], n, replace, 1);
    tryPasswords(Name1n, users.passwords, users.hashSetting);
    tryPasswords(Name2n, users.passwords, users.hashSetting);
    tryPasswords(Name3n, users.passwords, users.hashSetting);
    tryPasswords(Name0n, users.passwords, users.hashSetting);
    freeStringList(Name0n);
    freeStringList(Name1n);
    freeStringList(Name2n);
    freeStringList(Name3n);
}

void executeTask34(struct users users, struct stringList *top250){
    //checks for words like c[]ke instead of coke, same for 35 and 36
    char *replace = "[]";
    char o = 'o';
    struct stringList *t250o = manipulateList(top250, o, replace, 1);
    tryPasswords(t250o, users.passwords, users.hashSetting);
    freeStringList(t250o);
}

void executeTask35(struct users users, struct stringList *books){

    char *replace = "[]";
    char o = 'o';
    struct stringList *bookso = manipulateList(books, o, replace, 1);
    tryPasswords(bookso, users.passwords, users.hashSetting);
    freeStringList(bookso);
}

void executeTask36(struct users users){

    char *replace = "[]";
    char o =  'o';
    struct stringList *Name0o = manipulateList(users.names[0], o, replace, 1);
    struct stringList *Name2o = manipulateList(users.names[2], o, replace, 1);
    struct stringList *Name3o = manipulateList(users.names[3], o, replace, 1);
    struct stringList *Name1o = manipulateList(users.names[1], o, replace, 1);
    tryPasswords(Name1o, users.passwords, users.hashSetting);
    tryPasswords(Name2o, users.passwords, users.hashSetting);
    tryPasswords(Name3o, users.passwords, users.hashSetting);
    tryPasswords(Name0o, users.passwords, users.hashSetting);
    freeStringList(Name0o);
    freeStringList(Name1o);
    freeStringList(Name2o);
    freeStringList(Name3o);
}

void executeTask37(struct users users, struct stringList *top250){
    //checks for words like !_ove or |_ove instead of love, same for 38 and 39
    char *replace1 = "!_", *replace2 = "|_";
    char l = 'l';
    struct stringList *t250l1 = manipulateList(top250, l, replace1, 1);
    struct stringList *t250l2 = manipulateList(top250, l, replace2, 1);
    tryPasswords(t250l1, users.passwords, users.hashSetting);
    tryPasswords(t250l2, users.passwords, users.hashSetting);
    freeStringList(t250l1);
    freeStringList(t250l2);
}

void executeTask38(struct users users, struct stringList *books){

    char *replace1 = "!_", *replace2 = "|_";
    char l = 'l';
    struct stringList *booksl1 = manipulateList(books, l, replace1, 1);
    struct stringList *booksl2 = manipulateList(books, l, replace2, 1);
    tryPasswords(booksl1, users.passwords, users.hashSetting);
    tryPasswords(booksl2, users.passwords, users.hashSetting);
    freeStringList(booksl1);
    freeStringList(booksl2);
}

void executeTask39(struct users users){

    char *replace1 = "!_", *replace2 = "|_";
    char l = 'l';
    struct stringList *Name0l1 = manipulateList(users.names[0], l, replace1, 1);
    struct stringList *Name2l1 = manipulateList(users.names[2], l, replace1, 1);
    struct stringList *Name3l1 = manipulateList(users.names[3], l, replace1, 1);
    struct stringList *Name1l1 = manipulateList(users.names[1], l, replace1, 1);
    tryPasswords(Name1l1, users.passwords, users.hashSetting);
    tryPasswords(Name2l1, users.passwords, users.hashSetting);
    tryPasswords(Name3l1, users.passwords, users.hashSetting);
    tryPasswords(Name0l1, users.passwords, users.hashSetting);
    freeStringList(Name0l1);
    freeStringList(Name1l1);
    freeStringList(Name2l1);
    freeStringList(Name3l1);

    struct stringList *Name0l2 = manipulateList(users.names[0], l, replace2, 1);
    struct stringList *Name2l2 = manipulateList(users.names[2], l, replace2, 1);
    struct stringList *Name3l2 = manipulateList(users.names[3], l, replace2, 1);
    struct stringList *Name1l2 = manipulateList(users.names[1], l, replace2, 1);
    tryPasswords(Name1l2, users.passwords, users.hashSetting);
    tryPasswords(Name2l2, users.passwords, users.hashSetting);
    tryPasswords(Name3l2, users.passwords, users.hashSetting);
    tryPasswords(Name0l2, users.passwords, users.hashSetting);
    freeStringList(Name0l2);
    freeStringList(Name1l2);
    freeStringList(Name2l2);
    freeStringList(Name3l2);
}

void doWork(int task, struct users users, struct stringList *top250, struct stringList *books, struct stringList *years) {
    switch (task) { //all threads will work on these tasks in parallel
        case 1:
            executeTask1(users, top250);
            break;
        case 2:
            executeTask2(users, books);
            break;
        case 3:
            executeTask3(users, top250);
            break;
        case 4:
            executeTask4(users, books);
            break;
        case 5:
            executeTask5(users);
            break;
        case 6:
            executeTask6(users, top250);
            break;
        case 7:
            executeTask7(users, books);
            break;
        case 8:
            executeTask8(users);
            break;
        case 9:
            executeTask9(users, years);
            break;
        case 10:
            executeTask10(users, years);
            break;
        case 11:
            executeTask11(users, years);
            break;
        case 12:
            executeTask12(users, years);
            break;
        case 13:
            executeTask13(users, top250);
            break;
        case 14:
            executeTask14(users, books);
            break;
        case 15:
            executeTask15(users);
            break;
        case 16:
            executeTask16(users, top250);
            break;
        case 17:
            executeTask17(users, books);
            break;
        case 18:
            executeTask18(users);
            break;
        case 19:
            executeTask19(users, top250);
            break;
        case 20:
            executeTask20(users, books);
            break;
        case 21:
            executeTask21(users);
            break;
        case 22:
            executeTask22(users, top250);
            break;
        case 23:
            executeTask23(users, books);
            break;
        case 24:
            executeTask24(users);
            break;
        case 25:
            executeTask25(users, top250);
            break;
        case 26:
            executeTask26(users, books);
            break;
        case 27:
            executeTask27(users);
            break;
        case 28:
            executeTask28(users, top250);
            break;
        case 29:
            executeTask29(users, books);
            break;
        case 30:
            executeTask30(users);
            break;
        case 31:
            executeTask31(users, top250);
            break;
        case 32:
            executeTask32(users, books);
            break;
        case 33:
            executeTask33(users);
            break;
        case 34:
            executeTask34(users, top250);
            break;
        case 35:
            executeTask35(users, books);
            break;
        case 36:
            executeTask36(users);
            break;
        case 37:
            executeTask37(users, top250);
            break;
        case 38:
            executeTask38(users, books);
            break;
        case 39:
            executeTask39(users);
            break;
        default:
            break;
    }
}