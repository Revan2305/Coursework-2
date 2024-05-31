#include <iostream>

using namespace std;
int const vsego = 10;

struct student {
    char famila[30];
    char ima[30];
    char otchestvo[30];
    bool pol;
    int group;
    int vspiske;
    int otsenki[8];
    bool gorod;
    int dohod;
};

void newStud(student stud[]) {
    int k = vsego;
    for (int i = 0; i < vsego; i++) {
        if ((stud[i].pol != 0) && (stud[i].pol != 1)) {
            k = i;
            cout << endl;
            break;
        }
    }
    if (k == vsego) {
        cout << "Достигнут лимит студентов(" << vsego << ")!" << endl;
    }
    else {
        cout << "Введите фамилию студента: ";
        cin >> stud[k].famila;
        cout << "Введите имя студента: ";
        cin >> stud[k].ima;
        cout << "Введите отчество студента: ";
        cin >> stud[k].otchestvo;
        cout << endl << "Ввдите пол студента (0 - жен; 1 - муж): ";
        cin >> stud[k].pol;
        cout << endl << "Введите номер группы студента: ";
        cin >> stud[k].group;
        stud[k].vspiske = 1;
        for (int i = 0; i < k; i++) {
            if ((stud[i].group == stud[k].group) && (stud[i].vspiske >= stud[k].vspiske)) {
                stud[k].vspiske = stud[i].vspiske + 1;
            }
        }
        for (int i = 0; i < 8; i++) {
            while (!((stud[k].otsenki[i] > 1) && (stud[k].otsenki[i] < 6))) {
                cout << endl << "Введите оценку за " << i + 1 << "-й экзамен: ";
                cin >> stud[k].otsenki[i];
            }
        }
        cout << endl << "Введите месячный заработок студента: ";
        cin >> stud[k].dohod;
        cout << endl << "Введите место жительство студента(0 - местн; 1 - иногород): ";
        cin >> stud[k].gorod;
    }
}

void showStud(student stud[], int i) {
    cout << "|" << i << "|. " << stud[i].famila << " " << stud[i].ima << " " << stud[i].otchestvo << endl
        << "     Пол: ";
    if (stud[i].pol == 0) { cout << "женщина"; }
    else { cout << "мужчина"; }
    cout << endl << "     Группа: " << stud[i].group << " (" << stud[i].vspiske << "-й)" << endl
        << "     Оценки: ";
    for (int j = 0; j < 8; j++) {
        cout << stud[i].otsenki[j];
        if (j == 7) { cout << ';'; }
        else { cout << ", "; }
    }
    cout << endl << "     Доход: " << stud[i].dohod;
    if (stud[i].gorod == 0) { cout << " (местный)"; }
    else { cout << " (иногородний)"; }
    cout << endl;
}

void showStuds(student stud[]) {
    for (int i = 0; i < vsego; i++) {
        if (!((stud[i].pol != 0) && (stud[i].pol != 1))) {
            showStud(stud, i);
            cout << endl;
        }
    }
}

void editStud(student stud[]) {
    cout << "Выберите какого студента изменить: " << endl;
    showStuds(stud);
    cout << "Введите значение: ";
    int i, j = 0, c, a = 0, b = 0;
    bool er = 1;
    cin >> i;
    while (er)
        if ((stud[i].pol != 0) && (stud[i].pol != 1)) {
            cout << "Неправильные данные." << endl;
        }
        else {
            er = 0;
            cout << endl << "Что изменить: " << endl
                << "|1|. ФИО" << endl
                << "|2|. Группу" << endl
                << "|3|. Номер в группе" << endl
                << "|4|. Пол" << endl
                << "|5|. Оценки" << endl
                << endl << "Введите значение: ";
            while (!((j > 0) && (j < 6))) {
                cin >> j;
                switch (j) {
                case 1:
                    cout << "Введите фамилию студента: ";
                    cin >> stud[i].famila;
                    cout << "Введите имя студента: ";
                    cin >> stud[i].ima;
                    cout << "Введите отчество студента: ";
                    cin >> stud[i].otchestvo;
                    cout << endl;
                    break;
                case 2: // плохо считает!!!
                    cout << "Введите группу: ";
                    cin >> stud[i].group;
                    for (int k = 0; k < vsego; k++) {
                        if ((stud[k].group == stud[i].group) && (stud[k].vspiske >= stud[i].vspiske)) {
                            stud[i].vspiske = stud[k].vspiske + 1;
                        }
                    }
                    cout << endl;
                    break;
                case 3:
                    cout << "Введите номер в группе: ";
                    cin >> c;
                    for (int k = 0; k < vsego; k++) {
                        if ((stud[k].group == stud[i].group) && (stud[k].vspiske == c)) {
                            stud[k].vspiske = stud[i].vspiske;
                            stud[i].vspiske = c;
                        }
                    }
                    cout << endl;
                    break;
                case 4:
                    stud[i].pol = !(stud[i].pol);
                    cout << "Пол изменен" << endl;
                    cout << endl;
                    break;
                case 5:
                    while (!((a > 0) && (a < 9))) {
                        cout << endl << "Какую по счету оценку изменить: ";
                        cin >> a;
                        cout << endl;
                    }
                    while (!((b > 2) && (b < 6))) {
                        cout << "Введите число: ";
                        cin >> b;
                        cout << endl;
                    }
                    stud[i].otsenki[a - 1] = b;
                    break;
                default:
                    cout << " FATAL ERROR ";

                }
            }
        }
}

void showGroup(student stud[]) {
    int gr, st = 0;
    cout << "Введите группу: ";
    cin >> gr;
    for (int i = 0; i < vsego; i++) {
        if (stud[i].group == gr) {
            showStud(stud, i);
            cout << endl;
            st++;
        }
    }
    if (st == 0) { cout << "Студентов этой группы не существует" << endl << endl; }
}

void topStuds(student stud[]) {
    float scoreSort[vsego], score[vsego]{};
    int end = (vsego - 1), begin = 1;
    bool stop = true;
    for (int i = 0; i < vsego; i++) {
        for (int j = 0; j < 8; j++) {
            if (!((stud[i].pol != 0) && (stud[i].pol != 1))) {
                score[i] += stud[i].otsenki[j];
            }
            else { score[i] = 0; }
        }
        score[i] /= 8;
    }
    for (int i = 0; i < vsego; i++) {
        scoreSort[i] = score[i];
    }
    while (stop) {
        stop = false;
        for (int i = begin; i < end; i++) {
            if (scoreSort[i] > scoreSort[i - 1]) {
                float c = scoreSort[i];
                scoreSort[i] = scoreSort[i - 1];
                scoreSort[i - 1] = c;
                stop = true;
            }
        }
        end--;
        if (!stop) { break; }
        stop = false;
        for (int i = end - 1; i >= begin; i--) {
            if (scoreSort[i] > scoreSort[i - 1]) {
                float c = scoreSort[i];
                scoreSort[i] = scoreSort[i - 1];
                scoreSort[i - 1] = c;
                stop = true;
            }
        }
        begin++;
    }
    int k = vsego;
    for (int i = 0; i < vsego; i++) {
        if ((stud[i].pol != 0) && (stud[i].pol != 1)) {
            k = i;
            cout << endl;
            break;
        }
    }
    for (int i = 0; i <= (k - 1); i++) {
        for (int j = 0; j < vsego; j++) {
            if (scoreSort[i] == score[j]) {
                showStud(stud, j);
                cout << "     Среднея оценка: ";
                printf("%.2f", score[j]);
                cout << endl << endl;
            }
        }
    }
}

int showGend(student stud[], bool pol) {
    int k = 0;
    for (int i = 0; i < vsego; i++) {
        if (stud[i].pol == pol) {
            k++;
        }
    }
    return k;
}

void allMarks(student stud[]) {
    int mar = 0;
    while (!((mar > 0) && (mar < 4))) {
        cout << "Каких студентов показать: " << endl
            << "|1|. Троишники 3/4/5" << endl
            << "|2|. Хорошисты  4/5" << endl
            << "|3|. Отличники    5" << endl;
        cin >> mar;
    }
    for (int i = 0; i < vsego; i++) {
        bool four = 0, three = 0;
        for (int j = 0; j < 8; j++) {
            if (stud[i].otsenki[j] == 3) { three = 1; }
            if (stud[i].otsenki[j] == 4) { four = 1; }
        }
        switch (mar) {
        case 1:
            if (three) {
                showStud(stud, i);
                cout << endl;
            }
            break;
        case 2:
            if (!three && four) {
                showStud(stud, i);
                cout << endl;
            }
            break;
        case 3:
            if (!(three || four)) {
                showStud(stud, i);
                cout << endl;
            }
            break;
        }
    }
}

void showId(student stud[]) {
    int id;
    cout << "Введите номер студентов в списке: ";
    cin >> id;
    for (int i = 0; i < vsego; i++) {
        if (id == stud[i].vspiske) {
            showStud(stud, i);
            cout << endl;
        }
    }
}

void dohodN(student stud[]) {
    int k = vsego;
    for (int i = 0; i < vsego; i++) {
        if ((stud[i].pol != 0) && (stud[i].pol != 1)) {
            k = i;
            break;
        }
    }
    int d;
    cout << "Показать студентов чей доход ниже: ";
    cin >> d;
    for (int i = 0; i <= (k - 1); i++) {
        if (stud[i].dohod < d) {
            showStud(stud, i);
            cout << endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    struct student student[vsego];
    student[0] = { "Поляков", "Иван", "Михайлович", 1, 3372, 23, {4, 4, 4, 5, 5, 5, 5, 4}, 0, 65000 };
    student[1] = { "Павелко", "Владислав", "Сергеевич", 1, 3372, 19, {3, 3, 5, 4, 3, 4, 4, 5}, 1, 55000 };
    student[2] = { "Матвиенко", "Арсений", "Витальевич", 1, 3372, 15, {3, 4, 3, 5, 4, 5, 3, 5}, 0, 82000 };
    student[3] = { "Балева", "Юлия", "Эдуардовна", 0, 3372, 1, {4, 3, 3, 4, 4, 5, 4, 4}, 1, 35000 };
    student[4] = { "Бугров", "Савелий", "Олегович", 1, 3373, 2, {5, 4, 5, 4, 5, 5, 4, 5}, 0, 25000 };

    int num = 0;
    while (num != 10) {
        cout << "Выбор задач: " << endl
            << "|1|. Показать всех студентов" << endl
            << "|2|. Записать студента" << endl
            << "|3|. Редактировать студента" << endl
            << "|4|. Показать всех студентов определенной группы" << endl
            << "|5|. Топ успеваемости студентов по возрастанию" << endl
            << "|6|. Кол-во студентов(м/ж)" << endl
            << "|7|. Показать студентов с успеваемостью(/3 /4,5 /5)" << endl
            << "|8|. Показать студентов с номером в списке" << endl
            << "|9|. Показать студентов чей доход ниже чем указанный" << endl
            << "|10|. Закрыть программу" << endl
            << endl << "Введите значение: ";
        cin >> num;
        cout << endl;
        switch (num) {
        case 1:
            showStuds(student);
            break;
        case 2:
            newStud(student);
            break;
        case 3:
            editStud(student);
            break;
        case 4:
            showGroup(student);
            break;
        case 5:
            topStuds(student);
            break;
        case 6:
            bool sex;
            cout << "Выберите пол студентов(0 - жен; 1 - муж): ";
            cin >> sex;
            if (sex == 0) {
                cout << "Кол-во женщин: " << showGend(student, sex) << endl << endl;
                break;
            }
            cout << "Кол-во мужщин: " << showGend(student, sex) << endl << endl;
            break;
        case 7:
            allMarks(student);
            break;
        case 8:
            showId(student);
            break;
        case 9:
            dohodN(student);
            break;
        case 10:
            break;
        default:
            cout << "Try again";
        }
        system("Pause");
        system("cls");
    }
    return 0;
}