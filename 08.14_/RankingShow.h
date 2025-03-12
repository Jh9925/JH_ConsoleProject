#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <windows.h> // For MessageBox and Sleep


using namespace std;

struct RNKINFO {
    char* name;
    int score;
    RNKINFO* next;
};

struct LINKEDLIST {
    RNKINFO* cur;
    RNKINFO* head;
    RNKINFO* tail;
};

void printScore(LINKEDLIST* lnk);
void insertData(LINKEDLIST* lnk, const char* name, int score);
void deleteLastNode(LINKEDLIST* lnk);
void RankingShow();

void TextColor(int font, int backGround);


void TextColor2(int font, int backGround)
{
    int Color = font + backGround * 16;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);

}
void RankingShow() {
    // system("mode con: cols=50 lines=50");
    system("title Ranking View");

    ifstream file("Save/ranking.rnk");
    if (!file.is_open()) {
        MessageBox(NULL, TEXT("Failed to open the file."), NULL, NULL);
        return;
    }

    LINKEDLIST* lnk = new LINKEDLIST();
    lnk->cur = nullptr;
    lnk->head = nullptr;
    lnk->tail = nullptr;

    while (!file.eof()) {
        char tempName[50] = { 0 };
        int tempScore = 0;
        file >> tempName >> tempScore;  // Read from file
        insertData(lnk, tempName, tempScore);  // Add to list
    }
    file.close();

    printScore(lnk);  // Sort and print list
    system("pause");

    while (lnk->head != nullptr && lnk->head->next != nullptr) {
        deleteLastNode(lnk);
    }

    delete lnk;  // Free the list structure
    Sleep(1000);
}

void printScore(LINKEDLIST* lnk) {
    RNKINFO* cur = lnk->head;
    int cnt = 0;

    while (cur != nullptr) {
        cnt++;
        cur = cur->next;
    }

    RNKINFO** ptr = new RNKINFO * [cnt];
    cur = lnk->head;
    for (int i = 0; i < cnt; i++) {
        ptr[i] = cur;
        cur = cur->next;
    }

    for (int i = 0; i < cnt - 1; i++) {
        for (int j = i + 1; j < cnt; j++) {
            if (ptr[i]->score < ptr[j]->score) {
                RNKINFO* temp = ptr[i];
                ptr[i] = ptr[j];
                ptr[j] = temp;
            }
        }
    }
    // 이게 출력임
    TextColor2(14, 0);
    cout << " ________________________________________________" << endl;
    cout << " %=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x" << endl;
    cout << "                      점수 순위 " << endl;
    for (int i = 0; i < cnt-1; i++) {
        cout << "  " << i + 1 << " -> " << ptr[i]->name << " " << ptr[i]->score << endl << endl;
    }
    cout << " 메인으로 돌아가기 : 스페이스바 꾹 " << endl<<endl;
    cout << " %=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x%=x" << endl;
    cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    TextColor2(15, 0);
    delete[] ptr;  // Free allocated memory
}

void insertData(LINKEDLIST* lnk, const char* name, int score) {
    RNKINFO* newRNK = new RNKINFO();
    // 새 이름을 저장할 버퍼의 크기를 정확히 지정
    size_t nameLen = strlen(name);
    newRNK->name = new char[nameLen + 1]; // +1 for null terminator

    // newRNK->name = new char[strlen(name) + 1];
    strcpy_s(newRNK->name, nameLen + 1, name);
    newRNK->score = score;
    newRNK->next = nullptr;

    if (lnk->head == nullptr && lnk->tail == nullptr) {
        lnk->head = lnk->tail = newRNK;
    }
    else {
        lnk->tail->next = newRNK;
        lnk->tail = newRNK;
    }
}

void deleteLastNode(LINKEDLIST* lnk) {
    if (lnk->head == nullptr || lnk->head->next == nullptr) {
        delete lnk->head;
        lnk->head = lnk->tail = nullptr;
        return;
    }

    RNKINFO* cur = lnk->head;
    while (cur->next->next != nullptr) {
        cur = cur->next;
    }

    delete cur->next;
    cur->next = nullptr;
    lnk->tail = cur;
}