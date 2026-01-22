#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Quest {
public:
    string npc;
    string cel;
    string miejsce;
    int diff;

    Quest(string n, string c, string m, int d)
        : npc(n), cel(c), miejsce(m), diff(d) {
    }

    int reward() const {
        return diff * 100;
    }
};

class QuestFactory {
public:
    static Quest createQuest(int diff) {
        string NPC[] = { "Wiesniak", "Rycerz", "Czarodziej" };
        string CEL[] = { "zgubil miecz", "potrzebuje ziol", "szuka mapy" };
        string MIEJSCE[] = { "w lesie", "w jaskini", "na bagnach" };

        return Quest(
            NPC[rand() % 3],
            CEL[rand() % 3],
            MIEJSCE[rand() % 3],
            diff
        );
    }
};

class StepGenerator {
public:
    static void generateIterative(int diff) {
        for (int i = 1; i <= diff; i++) {
            printStep(i);
        }
    }

    static void generateRecursive(int step, int max) {
        if (step > max) return;

        printStep(step);
        generateRecursive(step + 1, max);
    }

private:
    static void printStep(int step) {
        string actions[] = { "szukaj", "walcz", "zbierz" };

        if (step % 2 == 1) {
            cout << "  Krok " << step
                << ": Idz do losowego miejsca i rozejrzyj się." << endl;
        }
        else {
            cout << "  Krok " << step
                << ": Zrob akcje: "
                << actions[rand() % 3] << "." << endl;
        }
    }
};

int getDiff() {
    int d;
    do {
        cout << "Podaj trudnosc questa (1 - 5): ";
        cin >> d;
    } while (d < 1 || d > 5);

    return d;
}


int main() {
    srand(time(nullptr));

    char mode;
    do {
        cout << "Wybierz tryb generowania krokow:\n";
        cout << "I - Iteracyjnie\n";
        cout << "R - Rekurencyjnie\n";
        cin >> mode;
        mode = toupper(mode);
    } while (mode != 'I' && mode != 'R');

    int diff = getDiff();
    Quest quest = QuestFactory::createQuest(diff);

    cout << "\nQUEST: " << quest.npc << " "
        << quest.cel << " "
        << quest.miejsce << "." << endl;

    cout << "Kroki:" << endl;

    if (mode == 'I') {
        StepGenerator::generateIterative(diff);
    }
    else {
        StepGenerator::generateRecursive(1, diff);
    }

    cout << "\nNagroda: " << quest.reward() << " zlota" << endl;

    return 0;
}
