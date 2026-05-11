#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <optional>
#include <vector>

// Harita ayarlarý
const unsigned int satir_sayisi = 9;
const unsigned int sutun_sayisi = 13;
const float kare_boyutu = 64.f;

enum HucreTipi {
    BOS = 0,
    KIRILAMAZ_DUVAR = 1,
    KIRILABILIR_KUTU = 2
};

int main() {
    // pencere
    sf::RenderWindow pencere(sf::VideoMode(sf::Vector2u(sutun_sayisi * kare_boyutu, satir_sayisi * kare_boyutu)), "Bomberman");
    pencere.setFramerateLimit(60);

    // harita
    int harita[satir_sayisi][sutun_sayisi] = {
        {0, 0, 0, 2, 2, 0, 2, 0, 2, 2, 0, 0, 0},
        {0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0},
        {2, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 2},
        {0, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0},
        {2, 0, 2, 0, 2, 2, 0, 2, 2, 0, 2, 0, 2},
        {0, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0},
        {2, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 2},
        {0, 1, 2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 0},
        {0, 0, 0, 2, 2, 0, 2, 0, 2, 2, 0, 0, 0}
    };

    // zemin ve duvar
    sf::RectangleShape kare(sf::Vector2f(kare_boyutu, kare_boyutu));
    kare.setOutlineThickness(-1.f);
    kare.setOutlineColor(sf::Color(50, 50, 50));

    // oyuncu karakteri
    sf::CircleShape oyuncu(kare_boyutu / 2.5f);
    oyuncu.setFillColor(sf::Color::Blue);
    oyuncu.setOrigin(sf::Vector2f(oyuncu.getRadius(), oyuncu.getRadius()));

    // oyuncu baþlangýç yeri
    sf::Vector2f oyuncuKonum(kare_boyutu / 2.f, kare_boyutu / 2.f);
    float hiz = 4.0f;

    // döngü
    while (pencere.isOpen()) {
        
        while (const std::optional<sf::Event> olay = pencere.pollEvent()) {
            if (olay->is<sf::Event::Closed>())
                pencere.close();
        }

        // hareket þekli
        // yeni konum
        sf::Vector2f yeniKonum = oyuncuKonum;

        // hareket
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            yeniKonum.y -= hiz;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            yeniKonum.y += hiz;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            yeniKonum.x -= hiz;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            yeniKonum.x += hiz;

        // oyuncunun bulunduðu kareyi hesapla
        int sutun = yeniKonum.x / kare_boyutu;
        int satir = yeniKonum.y / kare_boyutu;

        // harita sýnýrý kontrolü
        if (satir >= 0 && satir < satir_sayisi &&
            sutun >= 0 && sutun < sutun_sayisi)
        {
            // sadece boþ karede hareket etsin
            if (harita[satir][sutun] == BOS)
            {
                oyuncuKonum = yeniKonum;
            }
        }

        oyuncu.setPosition(oyuncuKonum);

        pencere.clear();

        // harita
        for (unsigned int i = 0; i < satir_sayisi; ++i) {
            for (unsigned int j = 0; j < sutun_sayisi; ++j) {
                kare.setPosition(sf::Vector2f(j * kare_boyutu, i * kare_boyutu));

                if (harita[i][j] == KIRILAMAZ_DUVAR)
                    kare.setFillColor(sf::Color(100, 100, 100)); // gri
                else if (harita[i][j] == KIRILABILIR_KUTU)
                    kare.setFillColor(sf::Color(200, 100, 50));  // kahverengi
                else
                    kare.setFillColor(sf::Color(34, 139, 34));   // yeþil

                pencere.draw(kare);
            }
        }

        // oyuncuyu çiz
        pencere.draw(oyuncu);

        pencere.display();
    }

    return 0;
}