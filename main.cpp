#include <SFML/Audio.hpp>
#include <iostream>
#include <windows.h>
#include <string>
#include <algorithm>
using namespace std;

namespace fs = filesystem;

string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return tolower(c); });
    return s;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    string folderPath = "musics";

    vector<string>musicFiles;

    if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
        std::cout << "Ошибка: Папка '" << folderPath << "' не найдена" << std::endl;
        std::cin.get();
        return 1;
    }

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            string ext = entry.path().extension().string();
            if (toLower(ext) == ".wav" || toLower(ext) == ".mp3") {
                musicFiles.push_back(entry.path().string());
            }
        }
    }

     if (musicFiles.empty()) {
        std::cout << "В папке '" << folderPath << "' не найдено аудиофайлов." << std::endl;
        std::cin.get();
        return 1;
    }

    cout << "========================" << endl;
    cout << "Найдены следующие треки: " << endl;

    for (size_t i = 0; i < musicFiles.size(); ++i) {
        cout << i + 1 << ". " << fs::path(musicFiles[i]).filename().string() << endl;
    }

    sf::Music music;
    int choice;
    cout << "=======================" << endl;
    cout << "Выбери трек: ";
    cin >> choice;
    cout << "\n";

    if (choice < 1 || choice > static_cast<int>(musicFiles.size())) {
        std::cout << "Неверный номер." << std::endl;
        std::cin.get();
        return 1;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Нажмите Enter чтобы переключить трек" << endl << endl;

    int curIdx = choice - 1;
    string isPause;
    while (true) {

        string currentFile = musicFiles[curIdx];
        cout << "Играет: " << fs::path(currentFile).filename().string();

        if (music.openFromFile(currentFile)) {
            music.play();
        } else {
            cout << "Ошибка при открытии файла: " << currentFile << endl;
        }

        cin.get();
        music.stop();

        curIdx++;
        
        if (curIdx >= musicFiles.size()) {
            curIdx = 0;
        }
    }
    return 0;
}
