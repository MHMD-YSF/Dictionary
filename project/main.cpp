#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;
struct sWord {
    string data;
    sWord* next;
};
struct dWord {
    string data;
    bool notenterd = true;
    sWord* synonym;
    sWord* antonym;
    dWord* next;
    dWord* previous;
};
struct Dictionary {
    dWord* head;
    dWord* tail;
};
int  findFirstOccurrence(const string& str, char ch) {
    int  pos = str.find(ch);
    return (pos != string::npos) ? pos : str.length();
}
void addSynonym(dWord* word, string synonym) {
    sWord* newSynonym = new sWord;
    newSynonym->data = synonym;
    newSynonym->next = word->synonym;
    word->synonym = newSynonym;
}
void addAtHeadSynonym(dWord* word, string synonym) {
    sWord* newSynonym = new sWord;
    if (word->synonym == nullptr)
    {
        word->synonym = newSynonym;
        newSynonym->data = synonym;
    }
    else {
        newSynonym->data = synonym;
        newSynonym->next = word->synonym;
        word->synonym = newSynonym;
    }
}
void displayDictionary(Dictionary &dict) { // Display dictionary
    dWord* currWord = dict.head;
    while (currWord != nullptr) {
        cout << "Word: " << currWord->data << ::endl;

        cout << "Synonyms: ";
        sWord* synonym = currWord->synonym;
        while (synonym != nullptr) {
            cout << synonym->data << " ";
            synonym = synonym->next;
        }
        cout << endl;

        cout << "Antonyms: ";
        sWord* antonym = currWord->antonym;
        while (antonym != nullptr) {
            cout << antonym->data << " ";
            antonym = antonym->next;
        }
        cout << endl;

        cout << "------------------------" << endl;
        currWord = currWord->next;
    }
}
void addWord(Dictionary& dict, string word) {  // hone aam nzeedd new wrod aal dictionary 
    dWord* newWord = new dWord;
    newWord->data = word;
    newWord->synonym = nullptr;
    newWord->antonym = nullptr;
    newWord->next = nullptr;
    newWord->previous = nullptr;

    if (dict.head == nullptr) {
        dict.head = newWord;
        dict.tail = newWord;
    }
    else {
        dict.tail->next = newWord;
        newWord->previous = dict.tail;
        dict.tail = newWord;
    }
}
dWord* findWord(Dictionary& dict, string word) // hone b2ate3lo wrod to find position of word 
{
    dWord* currWord = dict.head;
    while (currWord != nullptr) {
        if (currWord->data == word) {
            return currWord;
        }
        currWord = currWord->next;
    }
    return nullptr;
}
void addAntonym(dWord* word, string antonym) { // hone aam fawetlo new antonymm 
    sWord* newAntonym = new sWord;
    newAntonym->data = antonym;
    newAntonym->next = word->antonym;
    word->antonym = newAntonym;
}
void addAtHeadAntonym(dWord* word, string antonym) // iza ma aande antonym bestaamel lyser 3nde 
{
    sWord* newAntonym = new sWord;
    if (word->antonym == nullptr)
    {
        word->antonym = newAntonym;
        newAntonym->data = antonym;
    }
    else {
        newAntonym->data = antonym;
        newAntonym->next = word->antonym;
        word->antonym = newAntonym;
    }
}
Dictionary InsertAtRear(Dictionary& dict, string word)  // add ekher pos bil dictionary 
{
    dWord* temp1 = new dWord;
    temp1->data = word;
    temp1->next = nullptr,
        temp1->previous = nullptr;
    temp1->previous = dict.tail;
    dict.tail->next = temp1;
    dict.tail = temp1;
    temp1->synonym = nullptr;
    temp1->antonym = nullptr;
    return dict;

}
Dictionary InsertAtHead(Dictionary& dict, string word)
{
    dWord* temp2 = new dWord;
    temp2->data = word;
    temp2->next = nullptr,
        temp2->previous = nullptr;
    temp2->next = dict.head;
    dict.head->previous = temp2;
    dict.head = temp2;
    temp2->synonym = nullptr;
    temp2->antonym = nullptr;
    return dict;
}
void Print(Dictionary& dict)    // print hon cout lal dictionary  word la hala
{
    dWord* curr1 = dict.head;
    while (curr1 != nullptr)
    {
        cout << curr1->data << " " << "/";
        curr1 = curr1->next;

    }
    cout << endl;
}
Dictionary Sort(Dictionary& dict) //Ex3
{
    dWord* curr = dict.head;
    while (curr != nullptr)
    {
        dWord* nextcurr = curr->next;
        dWord* curr1 = dict.head;
        while (curr1 != nullptr && curr1->next != nullptr)
        {
            dWord* nextcurr1 = curr1->next;
            dWord* prevcurr1 = curr1->previous;

            if (curr1->data > nextcurr1->data)
            {
                dWord* tmp = curr1;
                if (curr1 == dict.head)
                {
                    tmp->next = nullptr;
                    tmp->previous = nullptr;
                    nextcurr1->previous = prevcurr1;
                    tmp->next = nextcurr1->next;
                    nextcurr1->next->previous = tmp;
                    tmp->previous = nextcurr1;
                    nextcurr1->next = tmp;
                    dict.head = nextcurr1;

                }
                else if (nextcurr1 == dict.tail)
                {
                    tmp->next = nullptr;
                    tmp->previous = nullptr;
                    nextcurr1->previous = prevcurr1;
                    prevcurr1->next = nextcurr1;
                    tmp->next = nextcurr1->next;
                    tmp->previous = nextcurr1;
                    nextcurr1->next = tmp;
                    dict.tail = curr1;
                }
                else {
                    tmp->next = nullptr;
                    tmp->previous = nullptr;
                    nextcurr1->previous = prevcurr1;
                    prevcurr1->next = nextcurr1;
                    tmp->next = nextcurr1->next;
                    nextcurr1->next->previous = tmp;
                    tmp->previous = nextcurr1;
                    nextcurr1->next = tmp;
                }
            }

            curr1 = curr1->next;
        }
        curr = nextcurr;
    }

    return dict;
}
Dictionary AddNewWord(Dictionary& dict, string word) //Ex4  // 
{
    int count = 0;
    dWord* cur = dict.head;
    string headword;
    string tailword;
    dWord* head = dict.head;
    tailword = dict.tail->data;
    headword = dict.head->data;
    do {
        count = 0;
        cout << "Enter the word you want to add:" << endl;
        getline(cin, word);
        while (cur != nullptr)
        {
            dWord* nextcur = cur->next;
            if (cur->data == word)
            {
                count++;

            }
            sWord* cur1 = cur->synonym;
            while (cur1 != nullptr)
            {
                if (cur1->data == word)
                {
                    count++;

                }
                cur1 = cur1->next;

            }
            sWord* cur2 = cur->antonym;
            while (cur2 != nullptr)
            {
                if (cur2->data == word)
                {
                    count++;

                }
                cur2 = cur2->next;

            }
            cur = nextcur;
        }
        if (count > 0)
            cout << "The word entered already exists." << endl;
    } while (count > 0);
    string largeword1;
    dWord* lword = nullptr;
    string noword = "none";
    do {
        cout << "Which word would you think that the word entered would be best related to:(none if not found)" << endl;
        Print(dict);
        getline(cin, largeword1);
        lword = findWord(dict, largeword1);
    } while (lword == nullptr && largeword1 != noword);

    if (largeword1 == noword)
    {
        if (word < headword)
            return InsertAtHead(dict, word);
        else if (word > tailword)
            return InsertAtRear(dict, word);
        else
        {
            dWord* temp = new dWord;
            temp->data = word;
            temp->next = nullptr;
            temp->previous = nullptr;
            dWord* cur3 = head;
            while (cur3->next != nullptr)
            {
                dWord* nextcur3 = cur3->next;
                if (cur3->next->data > temp->data)
                {
                    temp->next = cur3->next;
                    temp->previous = cur3;
                    nextcur3->previous = temp;
                    cur3->next = temp;
                    temp->synonym = nullptr;
                    temp->antonym = nullptr;
                    break;
                }
                cur3 = nextcur3;
            }
            cout << "New word added successfully." << endl;
        }
    }
    else
    {
        if (lword != nullptr)
        {
            char b;
            do {
                cout << "Is your word a(s) synonym or an(a) antonym.(please stick to the format given" << endl;
                cin >> b;
                cin.ignore();
            } while (b != 's' && b != 'a');
            if (b == 's')
            {
                if (word < headword)
                    dict = InsertAtHead(dict, word);
                else if (word > tailword)
                    dict = InsertAtRear(dict, word);
                else
                {
                    dWord* temp = new dWord;
                    temp->data = word;
                    temp->next = nullptr;
                    temp->previous = nullptr;
                    dWord* cur3 = head;
                    while (cur3->next != nullptr)
                    {
                        dWord* nextcur3 = cur3->next;
                        if (cur3->next->data > temp->data)
                        {
                            temp->next = cur3->next;
                            temp->previous = cur3;
                            nextcur3->previous = temp;
                            cur3->next = temp;
                            temp->synonym = nullptr;
                            temp->antonym = nullptr;
                            break;
                        }
                        cur3 = nextcur3;
                    }
                    cout << "New word added successfully." << endl;
                }
                dWord* sword = findWord(dict, word);
                cout << sword->data << endl;
                addSynonym(lword, word);
                cout << "The word has been added to the synonyms of " << lword->data << endl;
                addSynonym(sword, lword->data);
                sWord* current1 = lword->synonym->next;
                while (current1 != NULL)
                {
                    dWord* lword1 = findWord(dict, current1->data);
                    addAtHeadSynonym(lword1, word);
                    addAtHeadSynonym(sword, lword1->data);
                    current1 = current1->next;
                }
                sWord* current2 = lword->antonym;
                dWord* lword2 = findWord(dict, current2->data);
                addAntonym(lword2, word);
                addAntonym(sword, lword2->data);
                current2 = lword->antonym->next;
                while (current2 != NULL)
                {
                    dWord* lword2 = findWord(dict, current2->data);
                    addAtHeadAntonym(lword2, word);
                    addAtHeadAntonym(sword, lword2->data);
                    current2 = current2->next;
                }
            }
            else {
                if (word < headword)
                    dict = InsertAtHead(dict, word);
                else if (word > tailword)
                    dict = InsertAtRear(dict, word);
                else
                {
                    dWord* temp = new dWord;
                    temp->data = word;
                    temp->next = nullptr;
                    temp->previous = nullptr;
                    dWord* cur3 = head;
                    while (cur3->next != nullptr)
                    {
                        dWord* nextcur3 = cur3->next;
                        if (cur3->next->data > temp->data)
                        {
                            temp->next = cur3->next;
                            temp->previous = cur3;
                            nextcur3->previous = temp;
                            cur3->next = temp;
                            temp->synonym = nullptr;
                            temp->antonym = nullptr;
                            break;
                        }
                        cur3 = nextcur3;
                    }
                    cout << "New word added successfully." << endl;
                }
                dWord* sword = findWord(dict, word);
                addAntonym(lword, word);
                cout << "The word has been added to the antonyms of " << lword->data << endl;
                addAntonym(sword, lword->data);
                sWord* current1 = lword->synonym;
                while (current1 != NULL)
                {
                    dWord* lword1 = findWord(dict, current1->data);
                    addAtHeadAntonym(lword1, word);
                    addAtHeadAntonym(sword, lword1->data);
                    current1 = current1->next;
                }
                sWord* current2 = lword->antonym->next;
                dWord* lword2 = findWord(dict, current2->data);
                addSynonym(lword2, word);
                addSynonym(sword, lword2->data);
                current2 = current2->next;
                while (current2 != NULL)
                {
                    lword2 = findWord(dict, current2->data);
                    addAtHeadSynonym(lword2, word);
                    addAtHeadSynonym(sword, lword2->data);
                    current2 = current2->next;
                }
            }
        }
    }
    return dict;
}
Dictionary AddNewSword(Dictionary& dict, string word, string word1) //Ex5
{

    dWord* lword = nullptr;
    do {
        cout << "Which word would you like to add the synonym/antonym of ?" << endl;
        Print(dict);
        getline(cin, word1);
        lword = findWord(dict, word1);
    } while (lword == nullptr);
    int count = 0;
    dWord* cur = dict.head;
    string headword;
    string tailword;
    dWord* head = dict.head;
    tailword = dict.tail->data;
    headword = dict.head->data;
    do {
        count = 0;
        cout << "Enter the word you want to add:" << endl;
        getline(cin, word);
        while (cur != nullptr)
        {
            dWord* nextcur = cur->next;
            if (cur->data == word)
            {
                count++;

            }
            sWord* cur1 = cur->synonym;
            while (cur1 != nullptr)
            {
                if (cur1->data == word)
                {
                    count++;

                }
                cur1 = cur1->next;

            }
            sWord* cur2 = cur->antonym;
            while (cur2 != nullptr)
            {
                if (cur2->data == word)
                {
                    count++;

                }
                cur2 = cur2->next;

            }
            cur = nextcur;
        }
        if (count > 0)
            cout << "The word entered already exists." << endl;
    } while (count > 0);
    if (lword != nullptr)
    {
        char b;
        do {
            cout << "Is your word a(s) synonym or an(a) antonym.(please stick to the format given" << endl;
            cin >> b;
            cin.ignore();
        } while (b != 's' && b != 'a');
        if (b == 's')
        {
            if (word < headword)
                dict = InsertAtHead(dict, word);
            else if (word > tailword)
                dict = InsertAtRear(dict, word);
            else
            {
                dWord* temp = new dWord;
                temp->data = word;
                temp->next = nullptr;
                temp->previous = nullptr;
                dWord* cur3 = head;
                while (cur3->next != nullptr)
                {
                    dWord* nextcur3 = cur3->next;
                    if (cur3->next->data > temp->data)
                    {
                        temp->next = cur3->next;
                        temp->previous = cur3;
                        nextcur3->previous = temp;
                        cur3->next = temp;
                        temp->synonym = nullptr;
                        temp->antonym = nullptr;
                        break;
                    }
                    cur3 = nextcur3;
                }
                cout << "New word added successfully." << endl;
            }
            dWord* sword = findWord(dict, word);
            addSynonym(lword, word);
            cout << "The word has been added to the synonyms of " << lword->data << endl;
            addSynonym(sword, lword->data);
            sWord* current1 = lword->synonym->next;
            while (current1 != NULL)
            {
                dWord* lword1 = findWord(dict, current1->data);
                addAtHeadSynonym(lword1, word);
                addAtHeadSynonym(sword, lword1->data);
                current1 = current1->next;
            }
            sWord* current2 = lword->antonym;
            dWord* lword2 = findWord(dict, current2->data);
            addAntonym(lword2, word);
            addAntonym(sword, lword2->data);
            current2 = lword->antonym->next;
            while (current2 != NULL)
            {
                dWord* lword2 = findWord(dict, current2->data);
                addAtHeadAntonym(lword2, word);
                addAtHeadAntonym(sword, lword2->data);
                current2 = current2->next;
            }
        }
        else {
            if (word < headword)
                dict = InsertAtHead(dict, word);
            else if (word > tailword)
                dict = InsertAtRear(dict, word);
            else
            {
                dWord* temp = new dWord;
                temp->data = word;
                temp->next = nullptr;
                temp->previous = nullptr;
                dWord* cur3 = head;
                while (cur3->next != nullptr)
                {
                    dWord* nextcur3 = cur3->next;
                    if (cur3->next->data > temp->data)
                    {
                        temp->next = cur3->next;
                        temp->previous = cur3;
                        nextcur3->previous = temp;
                        cur3->next = temp;
                        temp->synonym = nullptr;
                        temp->antonym = nullptr;
                        break;
                    }
                    cur3 = nextcur3;
                }
                cout << "New word added successfully." << endl;
            }
            dWord* sword = findWord(dict, word);
            addAntonym(lword, word);
            cout << "The word has been added to the antonyms of " << lword->data << endl;
            addAntonym(sword, lword->data);
            sWord* current1 = lword->synonym;
            while (current1 != NULL)
            {
                dWord* lword1 = findWord(dict, current1->data);
                addAtHeadAntonym(lword1, word);
                addAtHeadAntonym(sword, lword1->data);
                current1 = current1->next;
            }
            sWord* current2 = lword->antonym->next;
            dWord* lword2 = findWord(dict, current2->data);
            addSynonym(lword2, word);
            addSynonym(sword, lword2->data);
            current2 = current2->next;
            while (current2 != NULL)
            {
                lword2 = findWord(dict, current2->data);
                addAtHeadSynonym(lword2, word);
                addAtHeadSynonym(sword, lword2->data);
                current2 = current2->next;
            }
        }
    }
    return dict;

}
int WordOccurrence(Dictionary& dict, dWord* wor) { //search bi kel abel hyd l word bl diction if existe
    int occ = 0;
    dWord* cuur = wor;
    if (wor == dict.head)
        return 0;

    while (cuur != nullptr) {
        sWord* cuur1 = cuur->synonym;
        sWord* cuur2 = cuur->antonym;

        if (cuur->data == wor->data) {
            occ++;
        }

        while (cuur1 != nullptr) {
            if (cuur1->data == wor->data) {
                occ++;
            }
            cuur1 = cuur1->next;
        }

        while (cuur2 != nullptr) {
            if (cuur2->data == wor->data) {
                occ++;
            }
            cuur2 = cuur2->next;
        }

        cuur = cuur->previous;
    }

    return occ;
}
int SWordOccurrence(Dictionary& dict, dWord* wor, sWord* wor1) {
    int occ = 0;
    dWord* cuur = wor;

    while (cuur != NULL) {
        sWord* cuur1 = cuur->synonym;
        sWord* cuur2 = cuur->antonym;

        if (cuur->data == wor1->data) {
            occ++;
        }

        while (cuur1 != nullptr) {
            if (cuur1->data == wor1->data) {
                occ++;
            }
            cuur1 = cuur1->next;
        }

        while (cuur2 != nullptr) {
            if (cuur2->data == wor1->data) {
                occ++;
            }
            cuur2 = cuur2->next;
        }

        cuur = cuur->previous;
    }

    return occ;
}
Dictionary SearchSWord(Dictionary& dict, string word) //Ex8
{
    cout << "enter the word:" << endl;
    getline(cin, word);
    dWord* fword = findWord(dict, word);
    if (fword != nullptr) {
        cout << "Synonyms: ";
        sWord* currentSynonym = fword->synonym;
        while (currentSynonym != nullptr) {
            cout << currentSynonym->data << " ";
            currentSynonym = currentSynonym->next;
        }
        cout << endl;

        cout << "Antonyms: ";
        sWord* currentAntonym = fword->antonym;
        while (currentAntonym != nullptr) {
            cout << currentAntonym->data << " ";
            currentAntonym = currentAntonym->next;
        }
        cout << endl;
    }
    else
    {
        cout << "Word not found in the dictionary." << endl;
    }
    return dict;
}
bool StartsConsecutiveLetters(string charArray, string letters)
{
    int charArrayLength = charArray.length();
    int lettersLength = letters.length();
    if (charArrayLength < lettersLength) {
        return false;
    }

    for (int i = 0; i < lettersLength; ++i) {
        if (charArray.at(i) != letters.at(i)) {
            return false;
        }
    }

    return true;
}
Dictionary SearchFirstWord(Dictionary& dict, const string& letters) { //Ex7
    dWord* current4 = dict.head;
    bool found = false;

    while (current4 != NULL) {
        dWord* nextcurrent4 = current4->next;

        if (WordOccurrence(dict, current4) > 1) {
            current4 = nextcurrent4;
            continue;
        }

        if (StartsConsecutiveLetters(current4->data, letters)) {
            cout << current4->data << endl;
            found = true;
        }

        sWord* currentSynonym = current4->synonym;
        while (currentSynonym != NULL) {
            if (SWordOccurrence(dict, current4, currentSynonym) > 1) {
                currentSynonym = currentSynonym->next;
                continue;
            }

            if (StartsConsecutiveLetters(currentSynonym->data, letters)) {
                cout << currentSynonym->data << endl;
                found = true;
            }

            currentSynonym = currentSynonym->next;
        }

        sWord* currentAntonym = current4->antonym;
        while (currentAntonym != NULL) {
            if (SWordOccurrence(dict, current4, currentAntonym) > 1) {
                currentAntonym = currentAntonym->next;
                continue;
            }

            if (StartsConsecutiveLetters(currentAntonym->data, letters)) {
                cout << currentAntonym->data << endl;
                found = true;
            }

            currentAntonym = currentAntonym->next;
        }

        current4 = nextcurrent4;
    }

    if (!found) {
        cout << "Not found" << endl;
    }
    return dict;
}
void Read(Dictionary& dict, const char* filename) //imput
{
    ifstream inputFile;
    inputFile.open(filename);
    if (!inputFile.is_open()) {
        cerr << "Error opening the file!" << endl;
        return;
    }
    string line; //save the lines
    int counter = 0; // awal kelme bi kel line
    dWord* largeWord = nullptr;
    dWord* tempword = new dWord;
    while (getline(inputFile, line, '\n')) { // when I read from the file
        istringstream iss(line); // am hot l line bi alb l variable line
        string word;
        counter = 0;
        string wordsBeforeFirstHash;
        size_t pos = 0;
        int firstHashPos = findFirstOccurrence(line, '#'); // position of # in findOCC
        if (firstHashPos == line.length())
            wordsBeforeFirstHash = line;
        else
            wordsBeforeFirstHash = line.substr(0, firstHashPos); // substr betbalich position 0 w btekhod firstHashPos 

        counter = 0;
        string jung; // save every word
        dWord* djung = new dWord; //save as pointer
        while (pos != string::npos) {
            size_t spacePos = wordsBeforeFirstHash.find(':', pos); //bas le2e : bsayva bi spacePos
            if (spacePos == string::npos && counter == 0) // eza word ma ena synonyms bi zida whda w bi hot string::npos la ytl3 mn l while
            {
                jung = wordsBeforeFirstHash.substr(pos);
                addWord(dict, jung);
                largeWord = findWord(dict, jung);
                pos = string::npos;
            }
            else {
                if (spacePos == string::npos) {
                    jung = wordsBeforeFirstHash.substr(pos); //bthkhda men l position lal ekhir wordsBeforeFirstHash
                    addSynonym(largeWord, jung);
                    if (SWordOccurrence(dict, largeWord, largeWord->synonym) <= 1)
                    {
                        addWord(dict, jung);
                    }
                    djung = findWord(dict, jung);
                    addSynonym(djung, largeWord->data);
                    break;
                }
                else {
                    if (counter == 0) {
                        jung = wordsBeforeFirstHash.substr(pos, spacePos - pos);
                        addWord(dict, jung);
                        largeWord = findWord(dict, jung);
                        pos = spacePos + 1;
                    }
                    else {
                        jung = wordsBeforeFirstHash.substr(pos, spacePos - pos);
                        addSynonym(largeWord, jung);
                        if (SWordOccurrence(dict, largeWord, largeWord->synonym) <= 1)
                        {
                            addWord(dict, jung);
                        }
                        djung = findWord(dict, jung); //save the word as a dword
                        addSynonym(djung, largeWord->data); //add largeWord synonym to djung
                        pos = spacePos + 1;
                    }
                }
                counter++;
            }
        }
        if (firstHashPos != line.length()) // if no antonims ma tfout 3lya
        {
            string wordsAfterFirstHash = line.substr(firstHashPos + 1);
            pos = 0;
            if (largeWord != NULL)
            {
                while (pos != string::npos) {
                    size_t spacePos = wordsAfterFirstHash.find('#', pos);
                    if (spacePos == string::npos) { // eza ma l2it # eza ekhir klme
                        jung = wordsAfterFirstHash.substr(pos);
                        addAntonym(largeWord, jung);
                        if (SWordOccurrence(dict, largeWord, largeWord->antonym) <= 1)
                        {
                            addWord(dict, jung);
                        }
                        djung = findWord(dict, jung);
                        addAntonym(djung, largeWord->data);
                        break;
                    }
                    else {
                        jung = wordsAfterFirstHash.substr(pos, spacePos - pos);
                        addAntonym(largeWord, jung);
                        if (SWordOccurrence(dict, largeWord, largeWord->antonym) <= 1)
                        {
                            addWord(dict, jung);
                        }
                        djung = findWord(dict, jung);
                        addAntonym(djung, largeWord->data);
                        pos = spacePos + 1;
                    }

                }
            }
        }
        sWord* current1 = largeWord->synonym;
        while (current1 != NULL)
        {
            sWord* curr = largeWord->synonym;
            dWord* syn = findWord(dict, current1->data); //bde le2e dWord tb3 l synonyms li nhna 3lay 
            while (curr != NULL)
            {
                if (curr->data != syn->data)
                {
                    addSynonym(syn, curr->data); //eza ma knit zeta klme ben l line bade zida
                }

                curr = curr->next;
            }
            sWord* curr1 = largeWord->antonym;
            while (curr1 != NULL)
            {
                addAntonym(syn, curr1->data);
                curr1 = curr1->next;
            }
            current1 = current1->next;
        }
        sWord* current = largeWord->antonym; // am zid l synonms wel antonyms tb3 l antonyms
        while (current != NULL)
        {
            sWord* curr2 = largeWord->synonym;
            dWord* ant = findWord(dict, current->data);
            while (curr2 != NULL)
            {
                addAntonym(ant, curr2->data);
                curr2 = curr2->next;
            }
            sWord* curr3 = largeWord->antonym;
            while (curr3 != NULL)
            {
                if (curr3->data != ant->data)
                    addSynonym(ant, curr3->data);
                curr3 = curr3->next;
            }
            current = current->next;
        }
    }
    inputFile.close();
}
void Output(Dictionary& dict, const char* filename) { //EX2 
    ofstream outputFile(filename, ios::out);
    if (!outputFile.is_open()) {
        cout << "Unable to open file!" << endl;
        return;
    }

    dWord* currWord = dict.head;
    outputFile << currWord->data;

    sWord* synonym = currWord->synonym;
    while (synonym != nullptr) {
        outputFile << ":" << synonym->data;
        synonym = synonym->next;
    }

    sWord* antonym = currWord->antonym;
    while (antonym != nullptr) {
        outputFile << "#" << antonym->data;
        antonym = antonym->next;
    }
    outputFile << endl;
    currWord = currWord->next;
    while (currWord != nullptr)
    {
        if (WordOccurrence(dict, currWord) <= 1)
        {

            outputFile << currWord->data;

            sWord* synonym = currWord->synonym;
            while (synonym != nullptr) {
                if (synonym->next != nullptr)
                    outputFile << ":" << synonym->data;
                synonym = synonym->next;
            }

            sWord* antonym = currWord->antonym;
            while (antonym != nullptr) {
                outputFile << "#" << antonym->data;
                antonym = antonym->next;
            }

            outputFile << endl;
        }
        currWord = currWord->next;
    }
    outputFile.close();
}
sWord* Deletehead(sWord* S)
{
    sWord* tmp = S->next;
    delete S;
    S = tmp;
    return S;
}
sWord* DeleteEnd(sWord* S)
{
    sWord* curr = S;
    while (curr != NULL && curr->next->next != NULL)
    {
        curr = curr->next;
    }
    delete curr->next;
    curr->next = NULL;
    return S;
}
sWord* Deletesword(sWord* S, string value)
{
    sWord* curr = S;
    while (curr->next != NULL)
    {
        if (curr->next->data == value)
        {
            sWord* tmp = curr->next;
            curr->next = tmp->next;
            delete tmp;
        }
        curr = curr->next;
    }
    return S;
}
Dictionary DeleteAtHead(Dictionary& dict)
{
    dWord* curr = dict.head->next;
    curr->previous = NULL;
    delete dict.head;
    dict.head = curr;
    return dict;
}
Dictionary DeleteAtTail(Dictionary& dict)
{
    dWord* curr = dict.tail;
    dict.tail = curr->previous;
    dict.tail->next = NULL;
    delete curr;
    return dict;
}
Dictionary DeleteAtMid(Dictionary& dict, string value)
{
    dWord* curr = dict.head;
    if (curr->data == value)
        DeleteAtHead(dict);
    if (dict.tail->data == value)
        dict = DeleteAtTail(dict);
    while (curr != NULL && curr->next != NULL && curr->data != value)
        curr = curr->next;
    if (curr->next != NULL)
    {
        curr->previous->next = curr->next;
        curr->next->previous = curr->previous;
        delete curr;
    }
    return dict;
}
Dictionary Delete(Dictionary& dict, string lettersToDelete) { //Ex6
    cout << "Enter the letters:" << endl;
    getline(cin, lettersToDelete);

    dWord* cur = dict.head;
    while (cur != nullptr) {
        dWord* nextNode = cur->next; // Store next node to avoid issues after deletion

        if (cur->data.find(lettersToDelete) != string::npos) {
            // Deleting synonyms
            while (cur->synonym != nullptr) {
                cur->synonym = Deletehead(cur->synonym);
            }

            // Deleting antonyms
            while (cur->antonym != nullptr) {
                cur->antonym = Deletehead(cur->antonym);
            }

            // Handle deletion at head
            if (cur == dict.head) {
                dict = DeleteAtHead(dict);
            }
            // Handle deletion at tail
            else if (cur == dict.tail) {
                dict = DeleteAtTail(dict);
                break; // No need to continue further
            }
            // Handle deletion at mid
            else {
                dict = DeleteAtMid(dict, cur->data);
            }
        }
        else {
            sWord* curSynonym = cur->synonym;
            sWord* curAntonym = cur->antonym;
            while (curSynonym != nullptr) {
                if (curSynonym->data.find(lettersToDelete) != string::npos) {
                    if (cur->synonym->data.find(lettersToDelete) != string::npos)
                    {
                        curSynonym = curSynonym->next;
                        cur->synonym = Deletehead(cur->synonym);
                        if (cur->synonym == NULL)
                            break;

                    }
                    else if (curSynonym->next == nullptr) {
                        cur->synonym = DeleteEnd(cur->synonym);
                        break;
                    }
                    else {
                        sWord* tmp1 = curSynonym->next;
                        cur->synonym = Deletesword(cur->synonym, curSynonym->data);
                        curSynonym = tmp1;
                    }
                }
                else {
                    curSynonym = curSynonym->next;
                }
            }
            while (curAntonym != nullptr) {
                if (curAntonym->data.find(lettersToDelete) != string::npos) {
                    if (cur->antonym->data.find(lettersToDelete) != string::npos)
                    {
                        curAntonym = curAntonym->next;
                        cur->antonym = Deletehead(cur->antonym);
                        if (cur->antonym == NULL)
                            break;
                    }
                    else if (curAntonym->next == nullptr) {
                        cur->antonym = DeleteEnd(cur->antonym);
                        break;
                    }
                    else {
                        sWord* tmp2 = curAntonym->next;
                        cur->antonym = Deletesword(cur->antonym, curAntonym->data);
                        curAntonym = tmp2;
                    }
                }
                else {
                    curAntonym = curAntonym->next;
                }
            }
        }
        cur = nextNode; // Move to the next node
    }

    return dict;
}
Dictionary FDelete(Dictionary& dict, string lettersToDelete) { //Ex9
    cout << "Enter the letters:" << endl;
    getline(cin, lettersToDelete);

    dWord* cur = dict.head;
    while (cur != nullptr) {
        dWord* nextNode = cur->next; // Store next node to avoid issues after deletion

        if (StartsConsecutiveLetters(cur->data, lettersToDelete) == true) {
            // Deleting synonyms
            while (cur->synonym != nullptr) {
                cur->synonym = Deletehead(cur->synonym);
            }

            // Deleting antonyms
            while (cur->antonym != nullptr) {
                cur->antonym = Deletehead(cur->antonym);
            }

            // Handle deletion at head
            if (cur == dict.head) {
                dict = DeleteAtHead(dict);
            }
            // Handle deletion at tail
            else if (cur == dict.tail) {
                dict = DeleteAtTail(dict);
                break; // No need to continue further
            }
            // Handle deletion at mid
            else {
                dict = DeleteAtMid(dict, cur->data);
            }
        }
        else {
            sWord* curSynonym = cur->synonym;
            sWord* curAntonym = cur->antonym;
            while (curSynonym != nullptr) {
                if (StartsConsecutiveLetters(curSynonym->data, lettersToDelete) == true) {
                    if (StartsConsecutiveLetters(cur->synonym->data, lettersToDelete) == true)
                    {
                        curSynonym = curSynonym->next;
                        cur->synonym = Deletehead(cur->synonym);
                        if (cur->synonym == NULL)
                            break;

                    }
                    else if (curSynonym->next == nullptr) {
                        cur->synonym = DeleteEnd(cur->synonym);
                        break;
                    }
                    else {
                        sWord* tmp1 = curSynonym->next;
                        cur->synonym = Deletesword(cur->synonym, curSynonym->data);
                        curSynonym = tmp1;
                    }
                }
                else {
                    curSynonym = curSynonym->next;
                }
            }
            while (curAntonym != nullptr) {
                if (StartsConsecutiveLetters(curAntonym->data, lettersToDelete) == true) {
                    if (StartsConsecutiveLetters(cur->antonym->data, lettersToDelete) == true)
                    {
                        curAntonym = curAntonym->next;
                        cur->antonym = Deletehead(cur->antonym);
                        if (cur->antonym == NULL)
                            break;
                    }
                    else if (curAntonym->next == nullptr) {
                        cur->antonym = DeleteEnd(cur->antonym);
                        break;
                    }
                    else {
                        sWord* tmp2 = curAntonym->next;
                        cur->antonym = Deletesword(cur->antonym, curAntonym->data);
                        curAntonym = tmp2;
                    }
                }
                else {
                    curAntonym = curAntonym->next;
                }
            }
        }
        cur = nextNode; // Move to the next node
    }

    return dict;
}
int main()
{
    Dictionary dict;
    string word;
    dict.head = nullptr;
    dict.tail = nullptr;

    // processFile("data.txt", dict);
    string word1;
    string letters;
    int num;
    char a;
    char b;
    Read(dict, "words.txt");
    dict = Sort(dict);
    string l;
 //  displayDictionary(dict);
    cout << "Hello user." << endl;
    do {
        do {
            cout << "What do you want to do ?" << endl;
            cout << "Press 1 if you want to add a new word." << endl;
            cout << "Press 2 if you want to add a new synonym or antonym for an existing word." << endl;
            cout << "Press 3 if you want to search for the synonyms or antonyms of a word." << endl;
            cout << "Press 4 if you want to search for words that begin with certain letters ." << endl;
            cout << "Press 5 if you want delete words that contains certain letters." << endl;
            cout << "Press 6 if you want to delete words that start whith certain letters." << endl;
            cin >> num;
            cin.ignore();
        } while (num != 1 && num != 2 && num != 2 && num != 3 && num != 4 && num != 5 && num != 6);
        if (num == 1)
        {
            dict = AddNewWord(dict, word);
            displayDictionary(dict);
        }
        if (num == 2)
        {
            dict = AddNewSword(dict, word, word1);
            displayDictionary(dict);
        }
        if (num == 3)
        {
            dict = SearchSWord(dict, word);
        }
        if (num == 4)
        {
            cout << "enter the letters you want:" << endl;
            getline(cin, letters);
            dict = SearchFirstWord(dict, letters);
        }
        if (num == 5)
        {
            dict = Delete(dict, l);
            displayDictionary(dict);
        }
        if (num == 6)
        {
            dict = FDelete(dict, l);
            displayDictionary(dict);
        }
        do {
            cout << "do you want to continue?(y/n)" << endl;
            cin >> a;
        } while (a != 'y' && a != 'n');
    } while (a == 'y');
    do {
        cout << "do you want to save your work?(y/n)" << endl;
        cin >> b;
    } while (b != 'y' && b != 'n');
    if (b == 'y')
        Output(dict, "words.txt");
    return 0;
}