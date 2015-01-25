#include "../../../include/Results.hpp"


ResultsController::ResultsController(RenderWindow *window, SFMLKernel *kernel, const string &name, int score) : IController(window, kernel, name), _score(score)
{
    if (!_backgroundImg.loadFromFile("res/img_end/gameover.jpg"))
    {
        cerr << "-> " << _name << ": Loading Background Fail" << endl;
    }
    _pseudo = "";
    _curl = curl_easy_init();
}

ResultsController::~ResultsController()
{
}

int ResultsController::eventManager(Event event)
{
    if (event.type == sf::Event::TextEntered && _pseudo.size() <= 3) {
        // Handle ASCII characters only
        if (event.type == sf::Event::TextEntered && _pseudo.size() < 3) {
            // Handle ASCII characters only
            if (event.text.unicode < 128 && _pseudo.size() < 3) {
                if (static_cast<char>(event.text.unicode) >= 'a' && static_cast<char>(event.text.unicode) <= 'z')
                    _pseudo += static_cast<char>(event.text.unicode) - 32;
                else
                    _pseudo += static_cast<char>(event.text.unicode);

            }
        }
    }
    else if (_pseudo.size() == 3)
    {
      CURLcode        res;
      string  readBuffer;
      string  formatedAddr;

      _result.clear();
      // Get response from Get API
      formatedAddr = "http://77.194.204.33:11080/LeapGameServer/rank.php?request=SET:" + _pseudo + ":" + to_string(_score);
      curl_easy_setopt(_curl, CURLOPT_URL, formatedAddr.c_str());
      //curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
      //curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &readBuffer);
      res = curl_easy_perform(_curl);
      
      _kernel->loadModule(Module::Rank);
    }
}

int ResultsController::display() {

    Sprite text;
    text.setTexture(_backgroundImg);
    _window->draw(text);

    sf::Font font;
    font.loadFromFile("res/8-Bit-Madness.ttf");
    sf::Text pseudoTxt("Pseudo: " + _pseudo, font);
    pseudoTxt.setPosition(Vector2f(WIDTH / 2 - 50, HEIGHT / 2 + 50));
    _window->draw(pseudoTxt);
}
