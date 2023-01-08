#include <SFML/Graphics.hpp>

int main()
{
sf::Font font;
if (!font.loadFromFile("arial.ttf"))
{
}

sf::Text text;

// select the font
text.setFont(font); // font is a sf::Font

// set the string to display
text.setString("Snake");

// set the character size
text.setCharacterSize(50); // in pixels, not points!

// set the color
text.setFillColor(sf::Color::Red);

// set the text style
text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::White);
	window.draw(text);

        // draw everything here...
        // window.draw(...);

        // end the current frame
        window.display();
    }

    return 0;
}