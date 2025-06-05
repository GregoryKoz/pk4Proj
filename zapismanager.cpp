#include "ZapisManager.h"

ZapisManager::ZapisManager() : koniec(false) {
    watek = std::thread(&ZapisManager::petlaZapisujaca, this);
}

ZapisManager::~ZapisManager() {
    zakoncz();
    if (watek.joinable()) watek.join();
}

void ZapisManager::dodajZadanie(const std::function<void()>& zadanie) {
    {
        std::lock_guard<std::mutex> lock(mutex);
        kolejka.push(zadanie);
    }
    cv.notify_one();
}

void ZapisManager::zakoncz() {
    {
        std::lock_guard<std::mutex> lock(mutex);
        koniec = true;
    }
    cv.notify_one();
}

void ZapisManager::petlaZapisujaca() {
    while (true) {
        std::function<void()> zadanie;
        {
            std::unique_lock<std::mutex> lock(mutex);
            cv.wait(lock, [&]() { return koniec || !kolejka.empty(); });

            if (koniec && kolejka.empty()) break;

            zadanie = std::move(kolejka.front());
            kolejka.pop();
        }
        zadanie();
    }
}
