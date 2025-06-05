#pragma once
#include <thread>
#include <mutex>
#include <queue>
#include <functional>
#include <condition_variable>

class ZapisManager {
public:
    ZapisManager();
    ~ZapisManager();

    void dodajZadanie(const std::function<void()>& zadanie);
    void zakoncz();

private:
    std::thread watek;
    std::mutex mutex;
    std::condition_variable cv;
    std::queue<std::function<void()>> kolejka;
    bool koniec;

    void petlaZapisujaca();
};
