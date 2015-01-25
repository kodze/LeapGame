#include "../../../include/rank.hpp"

static size_t WriteCallBack(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool replace(std::string& str, const std::string& from, const std::string& to) {
    if (str.length() == 0) {
        return true;
    }

    size_t idx = 0;

    for (;;) {
        idx = str.find(from, idx);
        if (idx == string::npos)  break;

        str.replace( idx, from.length(), to);
        idx += to.length();
    }

}

int Split(vector<string>& vecteur, string chaine, char separateur)
{
    vecteur.clear();

    string::size_type stTemp = chaine.find(separateur);

    while(stTemp != string::npos)
    {
        vecteur.push_back(chaine.substr(0, stTemp));
        chaine = chaine.substr(stTemp + 1);
        stTemp = chaine.find(separateur);
    }

    vecteur.push_back(chaine);

    return vecteur.size();
}

RankController::RankController(RenderWindow *window, SFMLKernel *kernel, const string &name, int score) : IController(window, kernel, name), _score(0)
{
    if (!_backgroundImg.loadFromFile("res/img_end/worldrank.jpg"))
    {
        cerr << "-> " << _name << ": Loading Background Fail" << endl;
    }
    _curl = curl_easy_init();
    getScore();
    _pseudo = "";
}

void RankController::getScore()
{
    if (_curl)
    {

        CURLcode	res;
        string	readBuffer;
        string	formatedAddr;

        _result.clear();
        // Get response from Get API
        formatedAddr = "http://77.194.204.33:11080/LeapGameServer/rank.php?request=GET";
        curl_easy_setopt(_curl, CURLOPT_URL, formatedAddr.c_str());
        curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
        curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(_curl);
        replace(readBuffer, "<br />", "\n");

        if (readBuffer.substr(readBuffer.size() - 6, readBuffer.size()) == "<br />")
        {
            readBuffer = readBuffer.substr(0, readBuffer.size() - 6);
        }

        Split(_result, readBuffer, '\n');
    }
}

RankController::~RankController()
{
    curl_easy_cleanup(_curl);
}

int RankController::eventManager(Event event)
{
    if (event.type == sf::Event::TextEntered && _pseudo.size() < 3)
    {
        // Handle ASCII characters only
        if (event.text.unicode < 128 && _pseudo.size() < 3)
        {
            if (static_cast<char>(event.text.unicode) >= 'a' && static_cast<char>(event.text.unicode) <= 'z')
                _pseudo += static_cast<char>(event.text.unicode) - 32;
            else
                _pseudo += static_cast<char>(event.text.unicode);
        }
        else
        {
            CURLcode	res;
            string	readBuffer;

            string request = "http://77.194.204.33:11080/LeapGameServer/rank.php?request=SET:" + _pseudo + ":" + to_string(_score);
            curl_easy_setopt(_curl, CURLOPT_URL, request.c_str());
            curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
            curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(_curl);
            getScore();
        }
    }
}

int RankController::display() {
    // Background

    Sprite text;
    text.setTexture(_backgroundImg);
    _window->draw(text);

    sf::Font font;
    font.loadFromFile("res/8-Bit-Madness.ttf");

    int size = _result.size();
    for (int i = 0; i < size - 1; i++) {
        string tmp = _result.at(i);
        // Display Score
        sf::Text txt(to_string(i + 1) + ") " + tmp, font);
        txt.setPosition(Vector2f(WIDTH / 2 - 100, 300 + (i * 120)));
        txt.setCharacterSize(50);
        txt.setStyle(sf::Text::Bold);
        txt.setColor(Color(50, 54, 101));
        _window->draw(txt);
    }
}
