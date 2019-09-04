#include <future>
#include <iostream>
#include <vector>
#include <thread>

/*
Egy olyan függvény, aminek a számítása sok időt vesz igénybe
*/
void f1()
{
    long x = 252523567;
    int c = 0;
    for (int i = 1; i <= x; ++i)
    {
        if (x % i == 0)
        {
            ++c;
        }
    }
    std::cout << x << " has " << c << " divisors." << std::endl;
}

int f2()
{
    long x = 252523567;
    int c = 0;
    for (int i = 1; i <= x; ++i)
    {
        if (x % i == 0)
        {
            ++c;
        }
    }
    return c;
}

int g()
{
    return 42;
}

int bad_main1()
{
    std::thread t(f1);
    int v = g();
    std::cout << v << std::endl;
    return 0;
    /*
    a stack kiürülésével az std::thread() destruktora le fog futni,
    ami ha még nem végzett a számítással, std::terminate-t hív, ami 99% eséllyel
    egy implementáció-függő SIGABRT szignál kezelésére fut -> a program hibával leáll
    */
}

int bad_main2()
{
    std::thread t(f1);
    t.join();
    /*
    Ha egy szálat elindítás után egyből be is várunk, azzal "kinyírtuk" a párhuzamos
    futás nyújtotta előnyöket, mivel így szekvencializálásra került a programunk.
    */
    int v = g();
    std::cout << v << std::endl;
    return 0;
}

int bad_main3()
{
    std::thread t(f2);
    int v = g();
    std::cout << v << std::endl;
    t.join();
    /*
    Az f2 és a main is kiírna a konzolra, azonban közös erőforrás felhasználása különböző szálakról
    (írási módban) nem garantálja az összefésüléses szemantika elvét, így ez nem lesz jó:
    az std::thread(t) helyett ezért inkább eltároljuk a visszatérési értéket egy std::future<T> objektumban
    */
    return 0;
}

int h(const std::vector<int> &v)
{
    return v.size();
}

//A "jó" megoldás
int main()
{
    std::future<int> t = std::async(std::launch::async, f2);
    /*
    Az std::launch::deferred "lusta" módon indítaná a szálat, tehát csak akkor indul el a tényleges függvényhívás,
    amikor a .get() hívás megtörténne. Emiatt azonban megint szekvencializálásra kerülne a program.
    */
    int v = g();
    std::cout << v << std::endl;

    std::vector<int> v(10, 42);
    std::future<int> q = std::async(std::launch::async, h, std::ref(v));
    /*
    A referencia szerinti paraméterátadás során a template-deduction miatt sokszor szükséges lehet
    az std::ref(..) - vagy std::cref(..) - wrapper használata öszetett objektumoknál,
    ha önmagában nem ismeri fel a fordító a típusokat - rendszerint ez a template-osztályok esetén fordul elő.
    */

    //az std::future::wait() csak bevárja a szálat, a .get() emellett az eredményt is visszaadja nekünk.
    //Ha nincs szükség visszatérési értékre, akkor std::future<void> helyett std::thread-et használjunk.
    int c = t.get();
    std::cout << c << std::endl;
    return 0;
}
