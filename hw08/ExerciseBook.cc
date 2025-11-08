#include <iostream>
using namespace std;
class Book; // forward ref before Exercise

class Exercise {
private:
    Book& book;
    int chapter;
    int number;
    Exercise* next;
    Exercise* requirements[16];
    int reqCount;
    bool assigned;

public:
    Exercise(Book& b, int c, int n, Exercise* prev)
        : book(b), chapter(c), number(n), next(nullptr),
          reqCount(0), assigned(false)
    {
        for (int i = 0; i < 16; ++i) {
        requirements[i] = nullptr; // initialize to nullptr to prevent crash
    }
        // link to previous exercise
        if (prev){
         prev->next = this;
        }
    }

    int getChapter() { 
        return chapter; }
    int getNumber()  { 
        return number; }
    Exercise* getNext() { 
        return next; }


    void print() {
        if (assigned){
         cout << chapter << "." << number;
        }
        else cout << "*.*";
    }

    void addRequirement(Exercise* ex) {
        if (reqCount < 16)
            requirements[reqCount++] = ex;
    }

    void markAssigned();
    void markUnassigned();
};

class Book {
private:
    Exercise* first;
    Exercise* last;

public:
    Book() : first(nullptr), last(nullptr) {}

    ~Book() {
        // clean up exercises
        for (Exercise* p = first; p != nullptr; ) {
            Exercise* next = p->getNext();
            delete p;
            p = next;
        }
    }

    // prevent copying/moving
    Book(const Book&) = delete;
    Book& operator=(const Book&) = delete;
    Book(Book&&) = delete;
    Book& operator=(Book&&) = delete;

    Exercise& addExercise(int ch, int num) {
        if (!first) {
            first = last = new Exercise(*this, ch, num, nullptr);
        } else {
            last = new Exercise(*this, ch, num, last);
        }
        return *last;
    }

    Exercise* getExercise(int ch, int num) {
        for (Exercise* p = first; p != nullptr; p = p->getNext()) {
            if (p->getChapter() == ch && p->getNumber() == num){
                return p;
            }
        }
        return nullptr;
    }

    Exercise* getFirst() { return first; }

    void printAll() {
        int current = -1;
        for (Exercise* p = first; p != nullptr; p = p->getNext()) {
            if (current != -1 && p->getChapter() != current){
                cout << "\n";
            }
            current = p->getChapter();
            p->print();
            cout << " ";
            
        }
        if (current != -1) {
            cout << "\n";
        }
    }
};

void Exercise::markAssigned() {
    if (assigned){
         return;
    }
    assigned = true;

    // Mark all requirements as assigned too
    for (int i = 0; i < reqCount; ++i) {
        if (requirements[i]){
            requirements[i]->markAssigned();
        }
    }
}

void Exercise::markUnassigned() {
    if (!assigned){
        return;
    }
    assigned = false;

    // Unassign all exercises that depend on this one
    for (Exercise* ex = book.getFirst(); ex != nullptr; ex = ex->getNext()) {
        for (int i = 0; i < ex->reqCount; ++i) {
            if (ex->requirements[i] == this) {
                ex->markUnassigned();
                break;
            }
        }
    }
}

int main() {
    Book book;

    Exercise& e91 = book.addExercise(9, 1);
    Exercise& e92 = book.addExercise(9, 2);
    Exercise& e93 = book.addExercise(9, 3);
    Exercise& e101 = book.addExercise(10, 1);
    Exercise& e102 = book.addExercise(10, 2);

    // dependencies
    e93.addRequirement(&e91);
    e93.addRequirement(&e92);
    e101.addRequirement(&e93);
    e102.addRequirement(&e91);

    book.printAll();

    while (true) {
        int ch, num;
        if (!(cin >> ch >> num) || (ch == 0 && num == 0)){
            break;
        }
        int absNum = (num < 0) ? -num : num;
        Exercise* ex = book.getExercise(ch, absNum);
        if (ex) {
            if (num > 0) {
                ex->markAssigned();
            }
            else {
                ex->markUnassigned();
            }
        }

        book.printAll();
    }

    return 0;
}
