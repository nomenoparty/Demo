#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>
#include <thread>
#include<sstream>
//#include <unistd.h>
using namespace std;

// Lớp đại diện cho một trang
//class Page
//{
//public:
//	void draw(sf::RenderWindow& window)
//	{
//
//	}
//};
//
bool isMouseOver(sf::RectangleShape& button, sf::Event event)
{
	return button.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y);
}
 
 bool isMouseOver(sf::RectangleShape& rect, sf::RenderWindow& window)
{
    sf::FloatRect bounds = rect.getGlobalBounds();
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    return bounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
}

bool isMouseOver(sf::Text& option, sf::RenderWindow& window)
{
    sf::FloatRect bounds = option.getGlobalBounds();
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    return bounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
}

struct film {
	string title;
	string desc;
	string image;
};

std::vector<film> films;
std::vector<pair<sf::RectangleShape, pair<sf::Text, string>>> productBoxes;
//std::vector<pair<sf::RectangleShape, pair<sf::Text, sf::Sprite>>> productBoxes;
//std::pair<sf::RectangleShape, bool> box[3][12][6];

int createFilmsWindow(sf::RenderWindow& window, sf::RenderWindow& window1, sf::Font& font, float filmListPosition1)
{
	window.setVisible(false);
	window.setActive(false);
	window1.setVisible(true);
	window1.setActive(true);
	sf::Texture texture;
	if (!texture.loadFromFile("fotor-ai-20231112163130.jpg"))
		return EXIT_FAILURE;

	// tạo sprite sử dụng texture đã tải
	sf::Sprite sprite(texture);
	sf::Vector2u windowsize = window1.getSize();
	float scalex = 1050.0 / texture.getSize().x;
	float scaley = 1000.0 / texture.getSize().y;
	sprite.setScale(scalex, scaley);

	sf::RectangleShape buttonTitle(sf::Vector2f(600, 45));
	buttonTitle.setFillColor(sf::Color(86, 0, 172, 70));
	buttonTitle.setPosition(200, 70);

	sf::RectangleShape lineTitle(sf::Vector2f(5, 45));
	lineTitle.setFillColor(sf::Color(18, 104, 10));
	lineTitle.setPosition(200, 70);

	sf::Text inputTextTitle;
	inputTextTitle.setFont(font);
	inputTextTitle.setCharacterSize(27);
	inputTextTitle.setFillColor(sf::Color(255, 255, 255));
	inputTextTitle.setPosition(210, 73);

	sf::RectangleShape buttonDesc(sf::Vector2f(600, 500));
	buttonDesc.setFillColor(sf::Color(86, 0, 172, 70));
	buttonDesc.setPosition(200, 200);

	sf::RectangleShape lineDesc(sf::Vector2f(5, 500));
	lineDesc.setFillColor(sf::Color(18, 104, 10));
	lineDesc.setPosition(200, 200);

	sf::Text inputTextDesc;
	inputTextDesc.setFont(font);
	inputTextDesc.setCharacterSize(27);
	inputTextDesc.setFillColor(sf::Color(255, 255, 255));
	inputTextDesc.setPosition(210, 196);

	sf::RectangleShape buttonImage(sf::Vector2f(600, 45));
	buttonImage.setFillColor(sf::Color(86, 0, 172, 70));
	buttonImage.setPosition(200, 785);

	sf::RectangleShape lineImage(sf::Vector2f(5, 45));
	lineImage.setFillColor(sf::Color(18, 104, 10));
	lineImage.setPosition(200, 785);

	sf::Text inputTextImage;
	inputTextImage.setFont(font);
	inputTextImage.setCharacterSize(27);
	inputTextImage.setFillColor(sf::Color(255, 255, 255));
	inputTextImage.setPosition(210, 788);

	sf::Texture createTexture;
	if (!createTexture.loadFromFile("2023-11-13_171327.png"))
		return EXIT_FAILURE;

	sf::Sprite createSprite(createTexture);
	float scalex1 = 300.0 / createTexture.getSize().x;
	float scaley1 = 75.0 / createTexture.getSize().y;
	createSprite.setScale(scalex1, scaley1);
	createSprite.setPosition(350, 870);

	sf::Font fontCreate;
	if (!fontCreate.loadFromFile("SourceSansPro-Bold.ttf"))
	{
		std::cout << "Failed to load font!" << std::endl;
		return -1;
	}

	sf::Text textCreate;
	textCreate.setFont(fontCreate);
	textCreate.setCharacterSize(37);
	textCreate.setFillColor(sf::Color(255, 255, 255));
	textCreate.setPosition(432, 883);
	textCreate.setString("CREATE");

	string textDesc = "";

	bool isInputTitleActive = false;
	bool isInputDescActive = false;
	bool isInputImageActive = false;

	bool checkwindow1 = false;

	while (window1.isOpen())
	{
		sf::Event event;
		while (window1.pollEvent(event))
		{
			//if (event.type == sf::Event::Closed)
			//{
			//	window1.close();
			//}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				if (isMouseOver(buttonTitle, event))
				{
					lineTitle.setFillColor(sf::Color(128, 241, 118));
					lineDesc.setFillColor(sf::Color(18, 104, 10));
					lineImage.setFillColor(sf::Color(18, 104, 10));
					isInputTitleActive = true;
					isInputDescActive = false;
					isInputImageActive = false;
				}
				else if (isMouseOver(buttonDesc, event))
				{
					lineDesc.setFillColor(sf::Color(128, 241, 118));
					lineTitle.setFillColor(sf::Color(18, 104, 10));
					lineImage.setFillColor(sf::Color(18, 104, 10));
					isInputDescActive = true;
					isInputTitleActive = false;
					isInputImageActive = false;
				}
				else if (isMouseOver(buttonImage, event)) {
					lineImage.setFillColor(sf::Color(128, 241, 118));
					lineDesc.setFillColor(sf::Color(18, 104, 10));
					lineTitle.setFillColor(sf::Color(18, 104, 10));
					isInputDescActive = false;
					isInputTitleActive = false;
					isInputImageActive = true;
				}
				else {
					lineDesc.setFillColor(sf::Color(18, 104, 10));
					lineTitle.setFillColor(sf::Color(18, 104, 10));
					lineImage.setFillColor(sf::Color(18, 104, 10));
					isInputDescActive = false;
					isInputTitleActive = false;
					isInputImageActive = false;
				}

				if (createSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
					string currentTextTitle = inputTextTitle.getString();
					string currentTextDesc = textDesc;
					string currentTextImage = inputTextImage.getString();
					sf::Texture texTureTest;
					if (currentTextTitle == "") {
						lineTitle.setFillColor(sf::Color(126, 0, 33));
					}
					if (currentTextDesc == "") {
						lineDesc.setFillColor(sf::Color(126, 0, 33));
					}
					if (currentTextImage == "" || !texTureTest.loadFromFile(currentTextImage)) {
						lineImage.setFillColor(sf::Color(126, 0, 33));
					}
					if (currentTextTitle != "" && currentTextDesc != "" && currentTextImage != "" && texTureTest.loadFromFile(currentTextImage)) {
						//for (int i = 0; i < films.size(); i++)
						//{
						//	productBoxes[i].first.setPosition(20 + i * 350, 125);

						//	productBoxes[i].second.first.setString(films[i].title);
						//	float textX = productBoxes[i].first.getPosition().x + productBoxes[i].first.getSize().x / 2 - productBoxes[i].second.first.getLocalBounds().width / 2;
						//	productBoxes[i].second.first.setPosition(textX, 600);
						//	productBoxes[i].second.second = films[i].image;
						//}
						films.push_back({ currentTextTitle, currentTextDesc, currentTextImage });
						//cout << "phim size = " << films.size() << ' ';
						//cout << "productBoxes size = " << productBoxes.size() << ' ';
						sf::RectangleShape productBox(sf::Vector2f(327.5f, 470.f));
						productBox.setPosition(20.f + 377.5 * (int)((films.size() - 1) % 4), filmListPosition1 + (int)((films.size() - 1) / 4) * 500);
						productBox.setFillColor(sf::Color::White);
						productBox.setOutlineThickness(2);
						productBox.setOutlineColor(sf::Color::Black);
						//productBox.setPosition(20 + (films.size() - 1) * 350, 125);

						sf::Text productText(currentTextTitle, font, 24);
						productText.setFillColor(sf::Color::Black);

						float text_X = 20.f + 377.5 * (int)((films.size() - 1) % 4) + productBox.getSize().x / 2 - productText.getLocalBounds().width / 2;
						float text_Y = filmListPosition1 + (int)((films.size() - 1) / 4) * 500 + productBox.getSize().y - 25;
						productText.setPosition(text_X, text_Y);

						//float textX = productBox.getPosition().x + productBox.getSize().x / 2 - productText.getLocalBounds().width / 2;
						//cout << "productBox.getPosition().x" << productBox.getPosition().x << endl;
						//cout << "productBox.getSize().x" << productBox.getSize().x << endl;
						//cout << "productText.getLocalBounds().width" << productText.getLocalBounds().width << endl;
						//productText.setPosition(textX, 600);

						productBoxes.push_back({ productBox , {productText, currentTextImage} });

						//sf::RectangleShape productBox(sf::Vector2f(327.5f, 470.f));
						//productBox.setFillColor(sf::Color::White);
						//productBox.setOutlineThickness(2);
						//productBox.setOutlineColor(sf::Color::Black);

						//sf::Text productText(films[i].title, font, 24);
						//productText.setFillColor(sf::Color::Black);

						//productBoxes.push_back({ productBox , {productText, films[i].image} });

						//cout << "productBoxes size = " << productBoxes.size() << endl;
						window1.setVisible(false);
						window1.setActive(false);
						window.setVisible(true);
						window.setActive(true);
						return 0;
						//checkwindow1 = true; break;
						//sf::Vector2f offset(0, 0);
						//sf::Vector2f newPos = productBoxes[productBoxes.size() - 1].first.getPosition() + offset;
						//float textX = productBoxes[productBoxes.size() - 1].first.getPosition().x + productBoxes[productBoxes.size() - 1].first.getSize().x / 2 - productBoxes[productBoxes.size() - 1].second.first.getLocalBounds().width / 2;

						//for (int i = productBoxes.size() - 1; i >= 1; i--)
						//{
						//	productBoxes[i].first.setPosition(productBoxes[i - 1].first.getPosition());
						//	float textX = productBoxes[i].first.getPosition().x + productBoxes[i].first.getSize().x / 2 - productBoxes[i].second.first.getLocalBounds().width / 2;
						//	productBoxes[i].second.first.setPosition(textX, 600);
						//}

						//productBoxes[0].first.setPosition(newPos);
						//productBoxes[0].second.first.setPosition(textX, 600);
					}
				}
			}
			else if (event.type == sf::Event::TextEntered)
			{
				if (isInputTitleActive)
				{
					if (event.text.unicode < 128)
					{
						if (event.text.unicode == '\b')
						{
							if (!inputTextTitle.getString().isEmpty()) {
								std::string currentText = inputTextTitle.getString();
								currentText.pop_back();
								inputTextTitle.setString(currentText);
							}
						}
						else if (event.text.unicode == '\r' || event.text.unicode == '\n')
						{
							inputTextTitle.setString(inputTextTitle.getString() + "\n");
						}
						else
						{
							inputTextTitle.setString(inputTextTitle.getString() + static_cast<char>(event.text.unicode));
						}
					}
				}
				else if (isInputDescActive)
				{
					if (event.text.unicode < 128)
					{
						if (event.text.unicode == '\b')
						{
							if (!inputTextDesc.getString().isEmpty()) {
								std::string currentText = inputTextDesc.getString();
								currentText.pop_back();
								textDesc.pop_back();
								inputTextDesc.setString(currentText);
							}
						}
						else if (event.text.unicode == '\r' || event.text.unicode == '\n')
						{
							inputTextDesc.setString(inputTextDesc.getString() + "\n");
							textDesc += "\n";
						}
						else
						{
							string lastString;
							stringstream ss(inputTextDesc.getString());
							while (getline(ss, lastString, '\n')) {
							}

							sf::Text tempText;
							tempText.setFont(font);
							tempText.setCharacterSize(27);
							tempText.setString(lastString);
							float lineDescWidth = tempText.getLocalBounds().width;
							float buttonDescWidth = buttonDesc.getLocalBounds().width;
							if (lineDescWidth > buttonDescWidth - 20)
							{
								// Thêm ký tự xuống dòng
								inputTextDesc.setString(inputTextDesc.getString() + "\n");
							}
							inputTextDesc.setString(inputTextDesc.getString() + static_cast<char>(event.text.unicode));
							textDesc += static_cast<char>(event.text.unicode);
						}

					}
				}
				else if (isInputImageActive)
				{
					if (event.text.unicode < 128)
					{
						if (event.text.unicode == '\b')
						{
							if (!inputTextImage.getString().isEmpty()) {
								std::string currentText = inputTextImage.getString();
								currentText.pop_back();
								inputTextImage.setString(currentText);
							}
						}
						else if (event.text.unicode == '\r' || event.text.unicode == '\n')
						{
							inputTextImage.setString(inputTextImage.getString() + "\n");
						}
						else
						{
							inputTextImage.setString(inputTextImage.getString() + static_cast<char>(event.text.unicode));
						}
					}
				}
			}
			if (event.type == sf::Event::MouseMoved)
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window1);
				if (createSprite.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
				{
					if (!createTexture.loadFromFile("2023-11-13_173035.png"))
						return EXIT_FAILURE;
					float scalex1 = 300.0 / createTexture.getSize().x;
					float scaley1 = 75.0 / createTexture.getSize().y;
					createSprite.setScale(scalex1, scaley1);
				}
				else
				{
					if (!createTexture.loadFromFile("2023-11-13_171327.png"))
						return EXIT_FAILURE;
					float scalex1 = 300.0 / createTexture.getSize().x;
					float scaley1 = 75.0 / createTexture.getSize().y;
					createSprite.setScale(scalex1, scaley1);
				}
			}
		}

		//if (checkwindow1) break;

		window1.clear();
		window1.draw(sprite);

		window1.draw(buttonTitle);
		window1.draw(inputTextTitle);
		window1.draw(lineTitle);

		window1.draw(buttonDesc);
		window1.draw(inputTextDesc);
		window1.draw(lineDesc);

		window1.draw(buttonImage);
		window1.draw(inputTextImage);
		window1.draw(lineImage);

		window1.draw(createSprite);
		window1.draw(textCreate);

		window1.display();
	}
}

int updateFilmsWindow(sf::RenderWindow& window, sf::RenderWindow& window1, sf::Font& font, int index, float filmListPosition1)
{
	window.setVisible(false);
	window.setActive(false);
	window1.setVisible(true);
	window1.setActive(true);
	sf::Texture texture;
	if (!texture.loadFromFile("fotor-ai-20231112163130.jpg"))
		return EXIT_FAILURE;

	// tạo sprite sử dụng texture đã tải
	sf::Sprite sprite(texture);
	sf::Vector2u windowsize = window1.getSize();
	float scalex = 1050.0 / texture.getSize().x;
	float scaley = 1000.0 / texture.getSize().y;
	sprite.setScale(scalex, scaley);

	sf::RectangleShape buttonTitle(sf::Vector2f(600, 45));
	buttonTitle.setFillColor(sf::Color(86, 0, 172, 70));
	buttonTitle.setPosition(200, 70);

	sf::RectangleShape lineTitle(sf::Vector2f(5, 45));
	lineTitle.setFillColor(sf::Color(18, 104, 10));
	lineTitle.setPosition(200, 70);

	sf::Text inputTextTitle(films[index].title, font, 24);
	inputTextTitle.setCharacterSize(27);
	inputTextTitle.setFillColor(sf::Color(255, 255, 255));
	inputTextTitle.setPosition(210, 73);

	sf::RectangleShape buttonDesc(sf::Vector2f(600, 500));
	buttonDesc.setFillColor(sf::Color(86, 0, 172, 70));
	buttonDesc.setPosition(200, 200);

	sf::RectangleShape lineDesc(sf::Vector2f(5, 500));
	lineDesc.setFillColor(sf::Color(18, 104, 10));
	lineDesc.setPosition(200, 200);

	sf::Text inputTextDesc(films[index].desc, font, 24);
	inputTextDesc.setCharacterSize(27);
	inputTextDesc.setFillColor(sf::Color(255, 255, 255));
	inputTextDesc.setPosition(210, 196);

	sf::RectangleShape buttonImage(sf::Vector2f(600, 45));
	buttonImage.setFillColor(sf::Color(86, 0, 172, 70));
	buttonImage.setPosition(200, 785);

	sf::RectangleShape lineImage(sf::Vector2f(5, 45));
	lineImage.setFillColor(sf::Color(18, 104, 10));
	lineImage.setPosition(200, 785);

	sf::Text inputTextImage(films[index].image, font, 24);
	inputTextImage.setCharacterSize(27);
	inputTextImage.setFillColor(sf::Color(255, 255, 255));
	inputTextImage.setPosition(210, 788);

	sf::Texture updateTexture;
	if (!updateTexture.loadFromFile("2023-11-13_171327.png"))
		return EXIT_FAILURE;

	sf::Sprite updateSprite(updateTexture);
	float scalex1 = 300.0 / updateTexture.getSize().x;
	float scaley1 = 75.0 / updateTexture.getSize().y;
	updateSprite.setScale(scalex1, scaley1);
	updateSprite.setPosition(200, 870);

	sf::Texture deleteTexture;
	if (!deleteTexture.loadFromFile("2023-11-13_171327.png"))
		return EXIT_FAILURE;

	sf::Sprite deleteSprite(deleteTexture);
	scalex1 = 300.0 / deleteTexture.getSize().x;
	scaley1 = 75.0 / deleteTexture.getSize().y;
	deleteSprite.setScale(scalex1, scaley1);
	deleteSprite.setPosition(501, 870);

	sf::Font fontUpdate;
	if (!fontUpdate.loadFromFile("SourceSansPro-Bold.ttf"))
	{
		std::cout << "Failed to load font!" << std::endl;
		return -1;
	}

	sf::Text textUpdate;
	textUpdate.setFont(fontUpdate);
	textUpdate.setCharacterSize(37);
	textUpdate.setFillColor(sf::Color(255, 255, 255));
	textUpdate.setPosition(282, 883);
	textUpdate.setString("UPDATE");

	sf::Text textDelete;
	textDelete.setFont(fontUpdate);
	textDelete.setCharacterSize(37);
	textDelete.setFillColor(sf::Color(255, 255, 255));
	textDelete.setPosition(583, 883);
	textDelete.setString("DELETE");

	string textDesc = films[index].desc;

	bool isInputTitleActive = false;
	bool isInputDescActive = false;
	bool isInputImageActive = false;

	bool checkwindow1 = false;

	//for (int i = 0; i < films.size(); i++) cout << i << ' ' << films[i].title << endl;

	while (window1.isOpen())
	{
		sf::Event event;
		while (window1.pollEvent(event))
		{
			//if (event.type == sf::Event::Closed)
			//{
			//	window1.close();
			//}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				if (isMouseOver(buttonTitle, event))
				{
					lineTitle.setFillColor(sf::Color(128, 241, 118));
					lineDesc.setFillColor(sf::Color(18, 104, 10));
					lineImage.setFillColor(sf::Color(18, 104, 10));
					isInputTitleActive = true;
					isInputDescActive = false;
					isInputImageActive = false;
				}
				else if (isMouseOver(buttonDesc, event))
				{
					lineDesc.setFillColor(sf::Color(128, 241, 118));
					lineTitle.setFillColor(sf::Color(18, 104, 10));
					lineImage.setFillColor(sf::Color(18, 104, 10));
					isInputDescActive = true;
					isInputTitleActive = false;
					isInputImageActive = false;
				}
				else if (isMouseOver(buttonImage, event)) {
					lineImage.setFillColor(sf::Color(128, 241, 118));
					lineDesc.setFillColor(sf::Color(18, 104, 10));
					lineTitle.setFillColor(sf::Color(18, 104, 10));
					isInputDescActive = false;
					isInputTitleActive = false;
					isInputImageActive = true;
				}
				else {
					lineDesc.setFillColor(sf::Color(18, 104, 10));
					lineTitle.setFillColor(sf::Color(18, 104, 10));
					lineImage.setFillColor(sf::Color(18, 104, 10));
					isInputDescActive = false;
					isInputTitleActive = false;
					isInputImageActive = false;
				}

				if (updateSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
					string currentTextTitle = inputTextTitle.getString();
					string currentTextDesc = textDesc;
					string currentTextImage = inputTextImage.getString();
					sf::Texture texTureTest;
					if (currentTextTitle == "") {
						lineTitle.setFillColor(sf::Color(126, 0, 33));
					}
					if (currentTextDesc == "") {
						lineDesc.setFillColor(sf::Color(126, 0, 33));
					}
					if (currentTextImage == "" || !texTureTest.loadFromFile(currentTextImage)) {
						lineImage.setFillColor(sf::Color(126, 0, 33));
					}
					if (currentTextTitle != "" && currentTextDesc != "" && currentTextImage != "" && texTureTest.loadFromFile(currentTextImage)) {

						films[index].title = currentTextTitle;
						films[index].desc = currentTextDesc;
						films[index].image = currentTextImage;

						productBoxes[index].second.first.setString(currentTextTitle);
						productBoxes[index].second.second = currentTextImage;

						float text_X = 20.f + 377.5 * (int)(index % 4) + productBoxes[index].first.getSize().x / 2 - productBoxes[index].second.first.getLocalBounds().width / 2;
						float text_Y = filmListPosition1 + (int)(index / 4) * 500 + productBoxes[index].first.getSize().y - 25;
						productBoxes[index].second.first.setPosition(text_X, text_Y);

						window1.setVisible(false);
						window1.setActive(false);
						window.setVisible(true);
						window.setActive(true);
						return 0;
					}
				}

				if (deleteSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
					auto it1 = films.begin() + index;
					std::vector<pair<sf::RectangleShape, pair<sf::Text, string>>>::iterator it2 = productBoxes.begin() + index;
					//if (it2 >= productBoxes.begin() && it2 < productBoxes.end()) {
					//	cout << "oke con dê" << endl;
					//}
					//else {
					//	cout << "cook" << endl;
					//}
					//if (it1 >= films.begin() && it1 < films.end()) {
					//	cout << "oke con dê films" << endl;
					//}
					//else {
					//	cout << "cook films" << endl;
					//}
					films.erase(it1); productBoxes.erase(it2);

					for (int i = 0; i < films.size(); i++)
					{
						productBoxes[i].first.setPosition(20.f + 377.5 * (int)(i % 4), filmListPosition1 + (int)(i / 4) * 500);
						productBoxes[i].first.setFillColor(sf::Color::White);
						productBoxes[i].first.setOutlineThickness(2);
						productBoxes[i].first.setOutlineColor(sf::Color::Black);

						float text_X = 20.f + 377.5 * (int)(i % 4) + productBoxes[i].first.getSize().x / 2 - productBoxes[i].second.first.getLocalBounds().width / 2;
						float text_Y = filmListPosition1 + (int)(i / 4) * 500 + productBoxes[i].first.getSize().y - 25;
						productBoxes[i].second.first.setPosition(text_X, text_Y);
					}

					window1.setVisible(false);
					window.setVisible(true);
					return 0;
				}
			}
			else if (event.type == sf::Event::TextEntered)
			{
				if (isInputTitleActive)
				{
					if (event.text.unicode < 128)
					{
						if (event.text.unicode == '\b')
						{
							if (!inputTextTitle.getString().isEmpty()) {
								std::string currentText = inputTextTitle.getString();
								currentText.pop_back();
								inputTextTitle.setString(currentText);
							}
						}
						else if (event.text.unicode == '\r' || event.text.unicode == '\n')
						{
							inputTextTitle.setString(inputTextTitle.getString() + "\n");
						}
						else
						{
							inputTextTitle.setString(inputTextTitle.getString() + static_cast<char>(event.text.unicode));
						}
					}
				}
				else if (isInputDescActive)
				{
					if (event.text.unicode < 128)
					{
						if (event.text.unicode == '\b')
						{
							if (!inputTextDesc.getString().isEmpty()) {
								std::string currentText = inputTextDesc.getString();
								currentText.pop_back();
								textDesc.pop_back();
								inputTextDesc.setString(currentText);
							}
						}
						else if (event.text.unicode == '\r' || event.text.unicode == '\n')
						{
							inputTextDesc.setString(inputTextDesc.getString() + "\n");
							textDesc += "\n";
						}
						else
						{
							string lastString;
							stringstream ss(inputTextDesc.getString());
							while (getline(ss, lastString, '\n')) {
							}

							sf::Text tempText;
							tempText.setFont(font);
							tempText.setCharacterSize(27);
							tempText.setString(lastString);
							float lineDescWidth = tempText.getLocalBounds().width;
							float buttonDescWidth = buttonDesc.getLocalBounds().width;
							if (lineDescWidth > buttonDescWidth - 20)
							{
								// Thêm ký tự xuống dòng
								inputTextDesc.setString(inputTextDesc.getString() + "\n");
							}
							inputTextDesc.setString(inputTextDesc.getString() + static_cast<char>(event.text.unicode));
							textDesc += static_cast<char>(event.text.unicode);
						}

					}
				}
				else if (isInputImageActive)
				{
					if (event.text.unicode < 128)
					{
						if (event.text.unicode == '\b')
						{
							if (!inputTextImage.getString().isEmpty()) {
								std::string currentText = inputTextImage.getString();
								currentText.pop_back();
								inputTextImage.setString(currentText);
							}
						}
						else if (event.text.unicode == '\r' || event.text.unicode == '\n')
						{
							inputTextImage.setString(inputTextImage.getString() + "\n");
						}
						else
						{
							inputTextImage.setString(inputTextImage.getString() + static_cast<char>(event.text.unicode));
						}
					}
				}
			}
			if (event.type == sf::Event::MouseMoved)
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window1);
				if (updateSprite.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
				{
					if (!updateTexture.loadFromFile("2023-11-13_173035.png"))
						return EXIT_FAILURE;
					float scalex1 = 300.0 / updateTexture.getSize().x;
					float scaley1 = 75.0 / updateTexture.getSize().y;
					updateSprite.setScale(scalex1, scaley1);
				}
				else
				{
					if (!updateTexture.loadFromFile("2023-11-13_171327.png"))
						return EXIT_FAILURE;
					float scalex1 = 300.0 / updateTexture.getSize().x;
					float scaley1 = 75.0 / updateTexture.getSize().y;
					updateSprite.setScale(scalex1, scaley1);
				}
				if (deleteSprite.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
				{
					if (!deleteTexture.loadFromFile("2023-11-13_173035.png"))
						return EXIT_FAILURE;
					float scalex1 = 300.0 / deleteTexture.getSize().x;
					float scaley1 = 75.0 / deleteTexture.getSize().y;
					deleteSprite.setScale(scalex1, scaley1);
				}
				else
				{
					if (!deleteTexture.loadFromFile("2023-11-13_171327.png"))
						return EXIT_FAILURE;
					float scalex1 = 300.0 / deleteTexture.getSize().x;
					float scaley1 = 75.0 / deleteTexture.getSize().y;
					deleteSprite.setScale(scalex1, scaley1);
				}
			}
		}

		window1.clear();
		window1.draw(sprite);

		window1.draw(buttonTitle);
		window1.draw(inputTextTitle);
		window1.draw(lineTitle);

		window1.draw(buttonDesc);
		window1.draw(inputTextDesc);
		window1.draw(lineDesc);

		window1.draw(buttonImage);
		window1.draw(inputTextImage);
		window1.draw(lineImage);

		window1.draw(updateSprite);
		window1.draw(textUpdate);

		window1.draw(deleteSprite);
		window1.draw(textDelete);

		window1.display();
	}
}

#include <mutex>
#include <condition_variable>
#include <atomic>

std::atomic<bool> isPaused(false);

void updateFilmPosition(float& position, int& first, int& last)
{
	float speed = 100.0f; // Tốc độ di chuyển của bộ phim

	while (true)
	{
		//if (isPaused) {
		//	std::this_thread::yield(); // Tạm dừng thread
		//	continue;
		//}
		// Cập nhật vị trí của bộ phim
		position += speed * 0.016f; // 0.016f là thời gian giữa các khung hình (khoảng 60 khung hình/giây)

		// Kiểm tra nếu vị trí vượt qua một giới hạn, đặt lại vị trí về 0
		if (position >= 50) {
			position = -300;
			first = last;
			if (first == 0) last = films.size() - 1;
			else last--;
		}

		// Tạm dừng luồng trong 16ms (tương đương với 60 khung hình/giây)
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
}

int adminWindow()
{
	sf::RenderWindow window(sf::VideoMode(1500, 900), "Admin");

	sf::RenderWindow window1(sf::VideoMode(1050, 1000), "Create Window", sf::Style::None);
	window1.setVisible(false);
	window1.setActive(false);

	sf::RenderWindow window2(sf::VideoMode(1050, 1000), "Update Window", sf::Style::None);
	window2.setVisible(false);
	window2.setActive(false);

	sf::Texture texture;
	if (!texture.loadFromFile("image-admin.jpg"))
		return EXIT_FAILURE;

	// tạo sprite sử dụng texture đã tải
	sf::Sprite sprite(texture);
	sf::Vector2u windowsize = window.getSize();
	float scalex = 1500.0 / texture.getSize().x;
	float scaley = 900.0 / texture.getSize().y;
	sprite.setScale(scalex, scaley);

	//////////////////////Font///////////////////////////
	sf::Font font;
	if (!font.loadFromFile("Roboto-Bold.ttf"))
	{
		std::cout << "Failed to load font!" << std::endl;
		return -1;
	}
	//////////////////////Font///////////////////////////

	sf::RectangleShape headerBox(sf::Vector2f(1500, 100));
	headerBox.setFillColor(sf::Color(3, 19, 39)); //205, 156, 124, 150
	headerBox.setPosition(0, 0);

	//////////////////////Movie//////////////////

	//std::vector<pair<string, string>> films;

	string title = "My nhan dao chich";
	string desc = "";
	string linkImage = "mynhandaochich.jpg";
	films.push_back({ title, desc, linkImage });

	title = "Am hon do thi";
	desc = "";
	linkImage = "amhondothi.jpg";
	films.push_back({ title, desc, linkImage });

	title = "Nguoi vo cuoi cung";
	desc = "";
	linkImage = "nguoivocuoicung.jpg";
	films.push_back({ title, desc, linkImage });

	title = "Nam dem kinh hoang";
	desc = "";
	linkImage = "5demkinhhoang.jpg";
	films.push_back({ title, desc, linkImage });

	title = "Quy mon quan";
	desc = "";
	linkImage = "quymonquan.jpg";
	films.push_back({ title, desc, linkImage });

	title = "Wolfoo";
	desc = "";
	linkImage = "wolfoo.jpg";
	films.push_back({ title, desc, linkImage });

	title = "Dat rung phuong nam";
	desc = "";
	linkImage = "marvel.jpg";
	films.push_back({ title, desc, linkImage });

	title = "Biet doi Marvel";
	desc = "";
	linkImage = "marvel.jpg";
	films.push_back({ title, desc, linkImage });

	title = "Hai ke doi tra";
	desc = "";
	linkImage = "haikedoitra.png";
	films.push_back({ title, desc, linkImage });

	//std::vector<pair<sf::RectangleShape, pair<sf::Text, string>>> productBoxes;

	//for (int i = 0; i < films.size(); i++)
	//{
	//	sf::RectangleShape productBox(sf::Vector2f(300, 500));
	//	productBox.setFillColor(sf::Color::White);
	//	productBox.setOutlineThickness(2);
	//	productBox.setOutlineColor(sf::Color::Black);

	//	sf::Text productText(films[i].title, font, 24);
	//	productText.setFillColor(sf::Color::Black);

	//	productBoxes.push_back({ productBox , {productText, films[i].image} });
	//}

	float filmListPosition1 = 120.f;

	for (int i = 0; i < films.size(); i++)
	{
		sf::RectangleShape productBox(sf::Vector2f(327.5f, 470.f));
		productBox.setPosition(20.f + 377.5 * (int)(i % 4), filmListPosition1 + (int)(i / 4) * 500);
		productBox.setFillColor(sf::Color::White);
		productBox.setOutlineThickness(2);
		productBox.setOutlineColor(sf::Color::Black);

		sf::Text productText(films[i].title, font, 24);
		productText.setFillColor(sf::Color::Black);

		float text_X = 20.f + 377.5 * (int)(i % 4) + productBox.getSize().x / 2 - productText.getLocalBounds().width / 2;
		float text_Y = filmListPosition1 + (int)(i / 4) * 500 + productBox.getSize().y - 25;
		productText.setPosition(text_X, text_Y);

		productBoxes.push_back({ productBox , {productText, films[i].image} });
	}

	//for (int i = 0;i < films.size(); i++) {
	//	sf::Texture updateTexture;
	//	if (!updateTexture.loadFromFile("button_update.png"))
	//		return EXIT_FAILURE;

	//	sf::Sprite uSprite(updateTexture);

	//	sf::Texture deleteTexture;
	//	if (!deleteTexture.loadFromFile("button_delete.png"))
	//		return EXIT_FAILURE;

	//	sf::Sprite dSprite(deleteTexture);

	//	float scale_x = 163.50 / updateTexture.getSize().x;
	//	float scale_y = 30.0 / updateTexture.getSize().y;
	//	uSprite.setScale(scale_x, scale_y);
	//	uSprite.setPosition(20.f + 377.5 * (int)(i % 4), filmListPosition1 + (int)(i / 4) * 500 + productBoxes[i].first.getSize().y + 5);
	//	films[i].updateSprite = uSprite;

	//	dSprite.setScale(scale_x, scale_y);
	//	dSprite.setPosition(20.f + 377.5 * (int)(i % 4) + productBoxes[i].first.getSize().x / 2 + 0.5, filmListPosition1 + (int)(i / 4) * 500 + productBoxes[i].first.getSize().y + 5);
	//	films[i].deleteSprite = dSprite;

	//	sf::Font fontUpdate;
	//	if (!fontUpdate.loadFromFile("SourceSansPro-Bold.ttf"))
	//	{
	//		std::cout << "Failed to load font!" << std::endl;
	//		return -1;
	//	}

	//	sf::Text textUpdate;
	//	textUpdate.setFont(fontUpdate);
	//	textUpdate.setCharacterSize(25);
	//	textUpdate.setFillColor(sf::Color(255, 255, 255));
	//	textUpdate.setString("UPDATE");
	//	float width = productBoxes[i].first.getSize().x / 2 - textUpdate.getLocalBounds().width / 2;
	//	textUpdate.setPosition(20.f + 377.5 * (int)(i % 4) + width, filmListPosition1 + (int)(i / 4) * 500 + productBoxes[i].first.getSize().y + 7);

	//	films[i].updateText = textUpdate;

	//	sf::Text textDelete;
	//	textDelete.setFont(fontUpdate);
	//	textDelete.setCharacterSize(25);
	//	textDelete.setFillColor(sf::Color(255, 255, 255));
	//	textDelete.setString("DELETE");
	//	width = productBoxes[i].first.getSize().x / 2 - textDelete.getLocalBounds().width / 2;
	//	textDelete.setPosition(20.f + 377.5 * (int)(i % 4) + productBoxes[i].first.getSize().x / 2 + width, filmListPosition1 + (int)(i / 4) * 500 + productBoxes[i].first.getSize().y + 7);

	//	films[i].deleteText = textDelete;
	//}

	//////////////////////Movie//////////////////



	//////////////////////Order//////////////////
	sf::Texture textureOrder;
	if (!textureOrder.loadFromFile("order(1500-800).png"))
		return EXIT_FAILURE;

	// tạo sprite sử dụng texture đã tải
	sf::Sprite spriteOrder(textureOrder);
	float scale_x = 1500.0 / textureOrder.getSize().x;
	float scale_y = 800.0 / textureOrder.getSize().y;
	spriteOrder.setScale(scale_x, scale_y);
	spriteOrder.setPosition(0, 100);

	std::pair<sf::RectangleShape, bool> box[3][12][6];
	//vector< std::pair<sf::RectangleShape, bool>> box[12][6];

	double x_0 = 196, y_0 = 345;
	double delta_x = 93.5, delta_y = 88.5;

	for (int k = 0; k < 3; k++) {
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 6; j++) {
				double x = x_0 + i * delta_x, y = y_0 + j * delta_y;
				box[k][i][j].second = false;
				box[k][i][j].first.setSize(sf::Vector2f(76, 74.5));
				box[k][i][j].first.setFillColor(sf::Color(238, 100, 87)); //100, 238, 87
				box[k][i][j].first.setOutlineThickness(2);
				box[k][i][j].first.setOutlineColor(sf::Color::Black);
				box[k][i][j].first.setPosition(x, y);
			}
		}
	}


	//////////////////////Order//////////////////

	///////////////////////////////////

	//bool selectButton[3]; memset(selectButton, false, 3);
	bool homePageButton = true;
	bool selectDropDownButton = false;
	bool selectAndUpdateButton = false; int indexButton = 0;
	bool createButtonActive = false;

	sf::RectangleShape movieButton(sf::Vector2f(200, 100));
	movieButton.setFillColor(sf::Color(3, 22, 46));
	//createButton.setOutlineThickness(2);
	//createButton.setOutlineColor(sf::Color(205, 156, 124, 255));
	movieButton.setPosition(600, 0);

	sf::Text movieButtonText("MOVIE", font, 30);
	movieButtonText.setFillColor(sf::Color::White);
	movieButtonText.setPosition(655, 35);

	//////////////////dropdown/////////////////////////

	sf::RectangleShape dropdownBox(sf::Vector2f(200, 100));
	dropdownBox.setFillColor(sf::Color(3, 22, 46)); //3, 19, 39, 230
	dropdownBox.setPosition(800, 0);

	sf::Text dropdownText("ROOM", font, 30);
	dropdownText.setFillColor(sf::Color::White);
	dropdownText.setPosition(850, 35);

	std::vector< std::pair<sf::Text, sf::RectangleShape> > options;
	sf::RectangleShape option1Box(sf::Vector2f(200, 50));
	option1Box.setFillColor(sf::Color(3, 22, 46));
	//option1Box.setOutlineThickness(0.5);
	//option1Box.setOutlineColor(sf::Color::White);
	option1Box.setPosition(800, 100);

	sf::Text option1("ROOM 1", font, 30);
	option1.setPosition(848, 105);
	option1.setFillColor(sf::Color::White);
	options.push_back({ {option1} , option1Box });

	sf::RectangleShape option2Box(sf::Vector2f(200, 50));
	option2Box.setFillColor(sf::Color(3, 22, 46));
	//option2Box.setOutlineThickness(0.5);
	//option2Box.setOutlineColor(sf::Color::White);
	option2Box.setPosition(800, 150);

	sf::Text option2("ROOM 2", font, 30);
	option2.setPosition(848, 155);
	option2.setFillColor(sf::Color::White);
	options.push_back({ {option2} , option2Box });

	sf::RectangleShape option3Box(sf::Vector2f(200, 50));
	option3Box.setFillColor(sf::Color(3, 22, 46));
	//option3Box.setOutlineThickness(0.5);
	//option3Box.setOutlineColor(sf::Color::White);
	option3Box.setPosition(800, 200);

	sf::Text option3("ROOM 3", font, 30);
	option3.setPosition(848, 205);
	option3.setFillColor(sf::Color::White);
	options.push_back({ {option3} , option3Box });

	bool isDropdownActive = false;

	//////////////////dropdown/////////////////////////

	/////////////////create & exit////////////////////////////

	sf::RectangleShape createButton(sf::Vector2f(200, 100));
	createButton.setFillColor(sf::Color(3, 22, 46));
	//createButton.setOutlineThickness(2);
	//createButton.setOutlineColor(sf::Color(205, 156, 124, 255));
	createButton.setPosition(1000, 0);

	sf::Text createButtonText("CREATE", font, 30);
	createButtonText.setFillColor(sf::Color::White);
	createButtonText.setPosition(1045, 35);

	sf::RectangleShape exitButton(sf::Vector2f(200, 100));
	exitButton.setFillColor(sf::Color(3, 22, 46));
	//createButton.setOutlineThickness(2);
	//createButton.setOutlineColor(sf::Color(205, 156, 124, 255));
	exitButton.setPosition(1200, 0);

	sf::Text exitButtonText("EXIT", font, 30);
	exitButtonText.setFillColor(sf::Color::White);
	exitButtonText.setPosition(1263, 35);

	/////////////////create & exit////////////////////////////

	//float position = 50.0f;
	//int first = 0, last = films.size() - 1;
	//std::thread thread(updateFilmPosition, std::ref(position), std::ref(first), std::ref(last));

	//int cnt = 0;

	// Thiết lập vị trí ban đầu của danh sách bộ phim

	float delta = 25.f;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			//thread.detach();
			if (homePageButton) {
				// Xử lý sự kiện cuộn danh sách bộ phim
	//			if (event.type == sf::Event::MouseWheelScrolled)
	//			{
	//				// lăn xuống(-) lăn lên(+)
	//				//filmListPosition1 -= event.mouseWheelScroll.delta * 10.f;

	//				//if (event.mouseWheelScroll.delta > 0) {
	//				//	if (filmListPosition1 < 120.f) {
	//				//		filmListPosition1 += event.mouseWheelScroll.delta * 10.f;
	//				//	}
	//				//}
	//				//else if (event.mouseWheelScroll.delta < 0) {
	//				//	if (filmList7.getPosition().y >= 380) {
	//				//		filmListPosition1 += event.mouseWheelScroll.delta * 10.f;
	//				//	}
	//				//}
	//				if (films.size() > 0) {
	//					if (event.mouseWheelScroll.delta > 0) {
	//						if (filmListPosition1 < 120.f) {
	//							filmListPosition1 += event.mouseWheelScroll.delta * 20.f;
	//						}
	//					}
	//					else if (event.mouseWheelScroll.delta < 0) {
	//						if (productBoxes[films.size() - 1].first.getPosition().y >= 380) {
	//							filmListPosition1 += event.mouseWheelScroll.delta * 20.f;
	//						}
	//					}
	//				}

	//				for (int i = 0; i < films.size(); i++)
	//				{
	//					productBoxes[i].first.setPosition(20.f + 377.5 * (int)(i % 4), filmListPosition1 + (int)(i / 4) * 500);
	//					float text_X = 20.f + 377.5 * (int)(i % 4) + productBoxes[i].first.getSize().x / 2 - productBoxes[i].second.first.getLocalBounds().width / 2;
	//					float text_Y = filmListPosition1 + (int)(i / 4) * 500 + productBoxes[i].first.getSize().y - 25;
	//					productBoxes[i].second.first.setPosition(text_X, text_Y);
	//				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					if (productBoxes[films.size() - 1].first.getPosition().y >= 380) {
						filmListPosition1 += -delta;
						for (int i = 0; i < films.size(); i++)
						{
							productBoxes[i].first.move(0, -delta);
							productBoxes[i].second.first.move(0, -delta);
						}
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					if (filmListPosition1 < 120.f) {
						filmListPosition1 += delta;
						for (int i = 0; i < films.size(); i++)
						{
							productBoxes[i].first.move(0, delta);
							productBoxes[i].second.first.move(0, delta);
						}
					}
				}
				if (event.type == sf::Event::MouseMoved)
				{
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
					if (movieButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
					{
						movieButtonText.setFillColor(sf::Color(255, 84, 0));
					}
					else {
						movieButtonText.setFillColor(sf::Color::White);
					}
					//if (dropdownBox.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
					//	dropdownText.setFillColor(sf::Color(255, 84, 0));
					//}
					//else {
					//	dropdownText.setFillColor(sf::Color::White);
					//}
					if (dropdownBox.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
					{
						dropdownText.setFillColor(sf::Color(255, 84, 0));
						//isDropdownActive = !isDropdownActive;
						isDropdownActive = true;
					}
					else if (isDropdownActive)
					{
						bool check = true;
						for (int i = 0; i < 3; i++) {
							{
								//option.first.second = false;
								if (options[i].second.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
								{
									options[i].first.setFillColor(sf::Color(255, 84, 0));
									//homePageButton = false;  selectDropDownButton = true; selectAndUpdateButton = true;
									//break;
									check = false;
								}
								else {
									options[i].first.setFillColor(sf::Color::White);
									//isDropdownActive = false;
								}
							}
						}
						if (check) {
							isDropdownActive = false;
							dropdownText.setFillColor(sf::Color::White);
						}
					}
					//else if (isDropdownActive)
					//{
					//	for (int i = 0; i < 3; i++) {
					//		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
					//		{
					//			if (isMouseOver(options[i].second, window))
					//			{
					//				dropdownText.setString(options[i].first.getString());
					//				indexButton = i + 1;
					//				dropdownText.setFillColor(sf::Color::White);
					//				isDropdownActive = false;
					//				//isArrowDownUp = true;
					//				homePageButton = false;  selectDropDownButton = true; selectAndUpdateButton = true;
					//				break;
					//			}
					//		}
					//	}
					//}
					if (createButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
					{
						createButtonText.setFillColor(sf::Color(255, 84, 0));
					}
					else {
						createButtonText.setFillColor(sf::Color::White);
					}
					if (exitButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
					{
						exitButtonText.setFillColor(sf::Color(255, 84, 0));
					}
					else {
						exitButtonText.setFillColor(sf::Color::White);
					}
				}
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
				{
					if (exitButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
						cout << "Y";
						//mainWindow.setVisible(true);
						//mainWindow.setActive(true);
						window.close();
						return 0;
					}
					//if (isMouseOver(dropdownBox, window))
					//{
					//	dropdownBox.setFillColor(sf::Color(111, 110, 111));
					//	isDropdownActive = !isDropdownActive;
					//}
					//else if (isDropdownActive)
					//{
					//	for (int i = 0; i < 3; i++) {
					//		{
					//			//option.first.second = false;
					//			if (isMouseOver(options[i].second, window))
					//			{
					//				dropdownText.setString(options[i].first.getString());
					//				indexButton = i + 1;
					//				dropdownBox.setFillColor(sf::Color::White);
					//				isDropdownActive = false;
					//				//isArrowDownUp = true;
					//				homePageButton = false;  selectDropDownButton = true; selectAndUpdateButton = true;
					//				break;
					//			}
					//		}
					//	}

					//}
					if (isDropdownActive)
					{
						for (int i = 0; i < 3; i++) {
							{
								//option.first.second = false;
								if (isMouseOver(options[i].second, window))
								{
									dropdownText.setString(options[i].first.getString());
									indexButton = i + 1;
									dropdownText.setFillColor(sf::Color::White);
									isDropdownActive = false;
									//isArrowDownUp = true;
									homePageButton = false;  selectDropDownButton = true; selectAndUpdateButton = true;
									break;
								}
							}
						}

					}
					else if (createButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						createFilmsWindow(window, window1, font, filmListPosition1);
					}
					else {
						for (int i = 0; i < productBoxes.size(); i++)
						{
							if (productBoxes[i].first.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
								//cout << films[i].title << " " << films[i].desc << " " << films[i].image << endl;
								updateFilmsWindow(window, window2, font, i, filmListPosition1);
							}
						}
					}
				}
			}
			else if (selectAndUpdateButton) {
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
				{
					if (movieButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						homePageButton = true;
						selectDropDownButton = false;
						dropdownText.setString("ROOM");
						selectAndUpdateButton = false;
						indexButton = 0;
					}
					//if (isMouseOver(dropdownBox, window))
					//{
					//	dropdownText.setFillColor(sf::Color(255, 84, 0));
					//	//isDropdownActive = !isDropdownActive;
					//	isDropdownActive = true;
					//}
					//else if (isDropdownActive)
					//{
					//	for (int i = 0; i < 3; i++) {
					//		//option.first.second = false;
					//		if (isMouseOver(options[i].second, window))
					//		{
					//			dropdownText.setString(options[i].first.getString());
					//			indexButton = i + 1;
					//			dropdownBox.setFillColor(sf::Color::White);
					//			isDropdownActive = false;
					//			//isArrowDownUp = true;
					//			homePageButton = false;  selectDropDownButton = true; selectAndUpdateButton = true;
					//			break;
					//		}
					//	}
					//}
					if (isDropdownActive)
					{
						for (int i = 0; i < 3; i++) {
							//option.first.second = false;
							if (isMouseOver(options[i].second, window))
							{
								dropdownText.setString(options[i].first.getString());
								indexButton = i + 1;
								dropdownText.setFillColor(sf::Color::White);
								isDropdownActive = false;
								//isArrowDownUp = true;
								homePageButton = false;  selectDropDownButton = true; selectAndUpdateButton = true;
								break;
							}
						}

					}

					if (selectAndUpdateButton) {
						if (indexButton) {
							for (int i = 0; i < 12; i++) {
								for (int j = 0; j < 6; j++) {
									if (box[indexButton - 1][i][j].first.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
										if (box[indexButton - 1][i][j].second) {
											box[indexButton - 1][i][j].second = false;
											box[indexButton - 1][i][j].first.setFillColor(sf::Color(238, 100, 87)); //100, 238, 87

										}
										else {
											box[indexButton - 1][i][j].second = true;
											box[indexButton - 1][i][j].first.setFillColor(sf::Color(100, 238, 87)); //100, 238, 87
										}
									}
								}
							}
						}
					}
					if (createButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						createFilmsWindow(window, window1, font, filmListPosition1);
					}
				}
				if (event.type == sf::Event::MouseMoved)
				{
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
					if (movieButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
					{
						movieButtonText.setFillColor(sf::Color(255, 84, 0));
					}
					else {
						movieButtonText.setFillColor(sf::Color::White);
					}
					//if (dropdownBox.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
					//	dropdownText.setFillColor(sf::Color(255, 84, 0));
					//}
					//else {
					//	dropdownText.setFillColor(sf::Color::White);
					//}
					if (dropdownBox.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
					{
						dropdownText.setFillColor(sf::Color(255, 84, 0));
						//isDropdownActive = !isDropdownActive;
						isDropdownActive = true;
					}
					else if (isDropdownActive)
					{
						bool check = true;
						for (int i = 0; i < 3; i++) {
							{
								//option.first.second = false;
								if (options[i].second.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
								{
									options[i].first.setFillColor(sf::Color(255, 84, 0));
									//homePageButton = false;  selectDropDownButton = true; selectAndUpdateButton = true;
									//break;
									check = false;
								}
								else {
									options[i].first.setFillColor(sf::Color::White);
								}
							}
						}
						if (check) {
							isDropdownActive = false;
							dropdownText.setFillColor(sf::Color::White);
						}
					}
					//else if (isDropdownActive)
					//{
					//	for (int i = 0; i < 3; i++) {
					//		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
					//		{
					//			if (isMouseOver(options[i].second, window))
					//			{
					//				dropdownText.setString(options[i].first.getString());
					//				indexButton = i + 1;
					//				dropdownText.setFillColor(sf::Color::White);
					//				isDropdownActive = false;
					//				//isArrowDownUp = true;
					//				homePageButton = false;  selectDropDownButton = true; selectAndUpdateButton = true;
					//				break;
					//			}
					//		}
					//	}
					//}
					if (createButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
					{
						createButtonText.setFillColor(sf::Color(255, 84, 0));
					}
					else {
						createButtonText.setFillColor(sf::Color::White);
					}
					if (exitButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
					{
						exitButtonText.setFillColor(sf::Color(255, 84, 0));
					}
					else {
						exitButtonText.setFillColor(sf::Color::White);
					}
				}

			}
		}

		window.clear(sf::Color::White);

		window.draw(sprite);

		if (homePageButton) {
			for (int i = 0; i < films.size(); i++)
			{
				sf::Texture texture;
				if (!texture.loadFromFile(productBoxes[i].second.second)) {
					texture.loadFromFile("404.jfif");
				}
				sf::Sprite sprite(texture);
				float scalex = 317.5 / texture.getSize().x;
				float scaley = 445.0 / texture.getSize().y;
				sprite.setScale(scalex, scaley);
				float x = 20.f + 377.5 * (int)(i % 4) + 5;
				float y = filmListPosition1 + (int)(i / 4) * 500 + 5;
				sprite.setPosition(x, y);
				window.draw(productBoxes[i].first);
				window.draw(sprite);
				window.draw(productBoxes[i].second.first);
				//window.draw(films[i].updateSprite);
				//window.draw(films[i].deleteSprite);
				//window.draw(films[i].updateText);
				//window.draw(films[i].deleteText);
				//productBox.setPosition(20.f + 377.5 * (int)(i % 4), filmListPosition1 + (int)(i / 4) * 500);
			}
			//productBoxes[first].first.setPosition(position, 125);
			//float text_X = position + productBoxes[first].first.getSize().x / 2 - productBoxes[first].second.first.getLocalBounds().width / 2;
			//productBoxes[first].second.first.setPosition(text_X, 600);
			//sf::Texture texture;
			//if (!texture.loadFromFile(productBoxes[first].second.second)) {
			//	texture.loadFromFile("404.jfif");
			//}
			//sf::Sprite sprite(texture);
			//float scalex = 290.0 / texture.getSize().x;
			//float scaley = 475.0 / texture.getSize().y;
			//sprite.setScale(scalex, scaley);
			//float x = position + 5;
			//float y = productBoxes[first].first.getPosition().y + 5;
			//sprite.setPosition(x, y);
			//window.draw(productBoxes[first].first);
			//window.draw(sprite);
			//window.draw(productBoxes[first].second.first);

			//int cnt = 0; // co the error
			//for (int i = first + 1; i < films.size(); i++) {
			//	float pos = position + ++cnt * 350;
			//	productBoxes[i].first.setPosition(pos, 125);
			//	float text_X = pos + productBoxes[i].first.getSize().x / 2 - productBoxes[i].second.first.getLocalBounds().width / 2;
			//	productBoxes[i].second.first.setPosition(text_X, 600);
			//	sf::Texture texture;
			//	if (!texture.loadFromFile(productBoxes[i].second.second)) {
			//		texture.loadFromFile("404.jfif");
			//	}
			//	sf::Sprite sprite(texture);
			//	float scalex = 290.0 / texture.getSize().x;
			//	float scaley = 475.0 / texture.getSize().y;
			//	sprite.setScale(scalex, scaley);
			//	float x = pos + 5;
			//	float y = productBoxes[i].first.getPosition().y + 5;
			//	sprite.setPosition(x, y);
			//	window.draw(productBoxes[i].first);
			//	window.draw(sprite);
			//	window.draw(productBoxes[i].second.first);
			//}

			//for (int i = 0; i < first; i++) {
			//	float pos = position + ++cnt * 350;
			//	productBoxes[i].first.setPosition(pos, 125);
			//	float text_X = pos + productBoxes[i].first.getSize().x / 2 - productBoxes[i].second.first.getLocalBounds().width / 2;
			//	productBoxes[i].second.first.setPosition(text_X, 600);
			//	sf::Texture texture;
			//	if (!texture.loadFromFile(productBoxes[i].second.second)) {
			//		texture.loadFromFile("404.jfif");
			//	}
			//	sf::Sprite sprite(texture);
			//	float scalex = 290.0 / texture.getSize().x;
			//	float scaley = 475.0 / texture.getSize().y;
			//	sprite.setScale(scalex, scaley);
			//	float x = pos + 5;
			//	float y = productBoxes[i].first.getPosition().y + 5;
			//	sprite.setPosition(x, y);
			//	window.draw(productBoxes[i].first);
			//	window.draw(sprite);
			//	window.draw(productBoxes[i].second.first);
			//}
		}

		window.draw(headerBox);
		window.draw(movieButton);
		window.draw(movieButtonText);
		window.draw(createButton);
		window.draw(createButtonText);
		window.draw(exitButton);
		window.draw(exitButtonText);

		//if (homePageAdmin) {

		//}

		if (selectDropDownButton) {
			window.draw(spriteOrder);
		}

		if (selectAndUpdateButton) {
			if (indexButton) {
				for (int i = 0; i < 12; i++) {
					for (int j = 0; j < 6; j++) {
						window.draw(box[indexButton - 1][i][j].first);
					}
				}
			}
		}

		window.draw(dropdownBox);
		window.draw(dropdownText);
		//if (isArrowDownUp) {
		//	arrow.setPoint(0, sf::Vector2f(0, 0));
		//	arrow.setPoint(1, sf::Vector2f(15, 0));
		//	arrow.setPoint(2, sf::Vector2f(7.5, 7.5));
		//	arrow.setFillColor(sf::Color::Black);
		//	window.draw(arrow);
		//}

		if (isDropdownActive)
		{
			//isArrowDownUp = false;
			//arrow.setPoint(0, sf::Vector2f(7.5, 0));
			//arrow.setPoint(1, sf::Vector2f(0, 7.5));
			//arrow.setPoint(2, sf::Vector2f(15, 7.5));
			//arrow.setFillColor(sf::Color::Black);
			//window.draw(arrow);

			for (const std::pair<sf::Text, sf::RectangleShape> option : options)
			{
				window.draw(option.second);
				window.draw(option.first);
			}
		}


		// Vẽ danh sách bộ phim
		//for (int i = 0; i < films.size(); i++)
		//{
		//    sf::Text filmText(films[i].title + " (" + films[i].director + ", " + to_string(films[i].year) + ")", font, 20);
		//    filmText.setPosition(filmList.getPosition().x + 10.f, filmList.getPosition().y + filmListPosition + i * 30.f);
		//    window.draw(filmText);
		//}

		window.display();
	}

	return 0;
}

int loginAdminWindow(sf::RenderWindow& mainWindow, sf::RenderWindow& window) {
	window.setVisible(true);
	window.setActive(true);

	sf::Texture texture;
	if (!texture.loadFromFile("admin-login.jpg"))
		return EXIT_FAILURE;

	// tạo sprite sử dụng texture đã tải
	sf::Sprite sprite(texture);
	float scalex = 900.0 / texture.getSize().x;
	float scaley = 900.0 / texture.getSize().y;
	sprite.setScale(scalex, scaley);

	sf::Font font;
	if (!font.loadFromFile("SVN-Times New Roman Bold.ttf"))
	{
		std::cout << "Failed to load font!" << std::endl;
		return -1;
	}

	sf::RectangleShape buttonUserName(sf::Vector2f(600, 55));
	buttonUserName.setFillColor(sf::Color(3, 36, 86, 180));
	buttonUserName.setPosition(160, 250);

	sf::RectangleShape lineUserName(sf::Vector2f(10, 55));
	lineUserName.setFillColor(sf::Color(18, 104, 10));
	lineUserName.setPosition(160, 250);

	sf::Text inputTextUserName;
	inputTextUserName.setFont(font);
	inputTextUserName.setCharacterSize(29);
	inputTextUserName.setFillColor(sf::Color(255, 255, 255));
	inputTextUserName.setPosition(173, 256);

	sf::RectangleShape buttonPassword(sf::Vector2f(600, 55));
	buttonPassword.setFillColor(sf::Color(3, 36, 86, 180));
	buttonPassword.setPosition(160, 450);

	sf::RectangleShape linePassword(sf::Vector2f(10, 55));
	linePassword.setFillColor(sf::Color(18, 104, 10));
	linePassword.setPosition(160, 450);

	sf::Text inputTextPassword;
	inputTextPassword.setFont(font);
	inputTextPassword.setCharacterSize(29);
	inputTextPassword.setFillColor(sf::Color(255, 255, 255));
	inputTextPassword.setPosition(173, 456);

	sf::Texture continueTexture;
	if (!continueTexture.loadFromFile("button-continue.png"))
		return EXIT_FAILURE;

	sf::Sprite continueSprite(continueTexture);
	float scalex1 = 300.0 / continueTexture.getSize().x;
	float scaley1 = 75.0 / continueTexture.getSize().y;
	continueSprite.setScale(scalex1, scaley1);
	continueSprite.setPosition(163, 650);

	sf::Texture backTexture;
	if (!backTexture.loadFromFile("button-back.png"))
		return EXIT_FAILURE;

	sf::Sprite backSprite(backTexture);
	scalex1 = 300.0 / backTexture.getSize().x;
	scaley1 = 79.0 / backTexture.getSize().y;
	backSprite.setScale(scalex1, scaley1);
	backSprite.setPosition(456, 650);

	bool isInputTitleActive = false;
	bool isInputImageActive = false;

	bool checkwindow1 = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				if (isMouseOver(buttonUserName, event))
				{
					lineUserName.setFillColor(sf::Color(128, 241, 118));
					linePassword.setFillColor(sf::Color(18, 104, 10));
					isInputTitleActive = true;
					isInputImageActive = false;
				}
				else if (isMouseOver(buttonPassword, event)) {
					linePassword.setFillColor(sf::Color(128, 241, 118));
					lineUserName.setFillColor(sf::Color(18, 104, 10));
					isInputTitleActive = false;
					isInputImageActive = true;
				}
				else {
					lineUserName.setFillColor(sf::Color(18, 104, 10));
					linePassword.setFillColor(sf::Color(18, 104, 10));
					isInputTitleActive = false;
					isInputImageActive = false;
				}

				if (continueSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
					string currentTextUserName = inputTextUserName.getString();
					string currentTextPassword = inputTextPassword.getString();
					if (currentTextUserName == "" || currentTextPassword == "") {
						if (currentTextUserName == "")
							lineUserName.setFillColor(sf::Color(255, 0, 0));
						if (currentTextPassword == "")
							linePassword.setFillColor(sf::Color(255, 0, 0));
					}
					else if (currentTextUserName != "admin" || currentTextPassword != "password") {
						if (currentTextUserName != "admin") {
							lineUserName.setFillColor(sf::Color(255, 0, 0));
						}
						if (currentTextPassword != "password") {
							linePassword.setFillColor(sf::Color(255, 0, 0));
						}
					}
					else if (currentTextUserName == "admin" && currentTextPassword == "password") {
						window.setVisible(false);
						window.setActive(false);
						adminWindow();
						return 0;
					}
				}

				if (backSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
					window.setVisible(false);
					window.setActive(false);
					return 0;
				}
			}
			else if (event.type == sf::Event::TextEntered)
			{
				if (isInputTitleActive)
				{
					if (event.text.unicode < 128)
					{
						if (event.text.unicode == '\b')
						{
							if (!inputTextUserName.getString().isEmpty()) {
								std::string currentText = inputTextUserName.getString();
								currentText.pop_back();
								inputTextUserName.setString(currentText);
							}
						}
						else
						{
							float textWidth = inputTextUserName.getLocalBounds().width;
							float buttonWidth = buttonUserName.getLocalBounds().width;
							if (buttonWidth > textWidth + 20)
								inputTextUserName.setString(inputTextUserName.getString() + static_cast<char>(event.text.unicode));
						}
					}
				}
				else if (isInputImageActive)
				{
					if (event.text.unicode < 128)
					{
						if (event.text.unicode == '\b')
						{
							if (!inputTextPassword.getString().isEmpty()) {
								std::string currentText = inputTextPassword.getString();
								currentText.pop_back();
								inputTextPassword.setString(currentText);
							}
						}
						else
						{
							float textWidth = inputTextPassword.getLocalBounds().width;
							float buttonWidth = buttonPassword.getLocalBounds().width;
							if (buttonWidth > textWidth + 20)
								inputTextPassword.setString(inputTextPassword.getString() + static_cast<char>(event.text.unicode));
						}
					}
				}
			}
		}

		window.clear();
		window.draw(sprite);

		window.draw(buttonUserName);
		window.draw(inputTextUserName);
		window.draw(lineUserName);

		window.draw(buttonPassword);
		window.draw(inputTextPassword);
		window.draw(linePassword);

		window.draw(continueSprite);
		window.draw(backSprite);

		window.display();
	}
}

int main()
{
	// Tạo cửa sổ kích thước 800x600 pixels
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Cinema");

	sf::RenderWindow windowLoginAdmin(sf::VideoMode(900, 900), "Login Admin", sf::Style::None);
	windowLoginAdmin.setActive(false);
	windowLoginAdmin.setVisible(false);

	//sf::RenderWindow windowAdmin(sf::VideoMode(1500, 900), "Admin");
	//windowAdmin.setActive(false);
	//windowAdmin.setVisible(false);

	//TEXT CLOCK
	sf::Font fontClock;
	if (!fontClock.loadFromFile("Wallpoet-Regular.ttf"))
		return EXIT_FAILURE;

	// Tạo văn bản sử dụng font đã tải
	sf::Text textClock("", fontClock, 24);
	textClock.setPosition(0, 10);
	//TEXT CLOCK

	// tải ảnh từ file trên hệ thống
	sf::Texture texture;
	if (!texture.loadFromFile("movie.jpg"))
		return EXIT_FAILURE;

	// tạo sprite sử dụng texture đã tải
	sf::Sprite sprite(texture);

	// lấy kích thước của cửa sổ
	sf::Vector2u windowsize = window.getSize();

	// tính toán tỷ lệ giữa kích thước ảnh và kích thước cửa sổ
	float scalex = static_cast<float>(windowsize.x) / texture.getSize().x;
	float scaley = static_cast<float>(windowsize.y) / texture.getSize().y;

	// đặt tỷ lệ kích thước cho sprite
	sprite.setScale(scalex, scaley);

	// đặt vị trí của sprite
	sprite.setPosition(0, 0);


	// Tạo nút để chuyển sang trang khác
		//sf::RectangleShape button(sf::Vector2f(200, 50));
		////sf::CircleShape button(50, 100);
		//button.setFillColor(sf::Color(139, 216, 189));
		//button.setPosition(300, 250);

	sf::CircleShape button1(25);
	button1.setFillColor(sf::Color(139, 216, 189)); // Màu xám
	button1.setOutlineThickness(5);
	button1.setOutlineColor(sf::Color(150, 150, 150)); // Màu xám nhạt
	button1.setPosition(1100, 10);

	sf::CircleShape button2(25);
	button2.setFillColor(sf::Color(139, 216, 189)); // Màu xám
	button2.setOutlineThickness(5);
	button2.setOutlineColor(sf::Color(150, 150, 150)); // Màu xám nhạt
	button2.setPosition(1000, 10);

	sf::Texture texture1;
	if (!texture1.loadFromFile("admin-icon-png-4.jpg"))
	{
		std::cout << "Failed to load icon." << std::endl;
		return -1;
	}
	sf::Sprite iconSprite1(texture1);
	iconSprite1.setScale(0.2f, 0.2f);
	iconSprite1.setPosition(1105, 12);

	sf::Texture texture2;
	if (!texture2.loadFromFile("icon-home-removebg-preview.png"))
	{
		std::cout << "Failed to load icon." << std::endl;
		return -1;
	}
	sf::Sprite iconSprite2(texture2);
	iconSprite2.setScale(0.1f, 0.1f);
	iconSprite2.setPosition(994, 12);

	/*sf::Font font;
	if (!font.loadFromFile("ShortBaby-Mg2w.ttf"))
		return EXIT_FAILURE;

	sf::Text text("Click táo!", font, 24);
	text.setFillColor(sf::Color::Red);
	text.setPosition(button.getPosition().x + button.getSize().x / 2 - text.getGlobalBounds().width / 2,
		button.getPosition().y + button.getSize().y / 2 - text.getGlobalBounds().height / 2);*/

		// Vòng lặp chính
	while (window.isOpen())
	{
		// Xử lý các sự kiện
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				// Kiểm tra xem người dùng đã ấn vào nút hay chưa
				if (button1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					window.setActive(false);
					window.setVisible(false);
					loginAdminWindow(window, windowLoginAdmin);
					window.setActive(true);
					window.setVisible(true);
				}
				if (button2.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
				}
			}
		}

		auto now = std::chrono::system_clock::now();
		std::time_t now_time = std::chrono::system_clock::to_time_t(now);

		// Chuyển đổi std::time_t sang đối tượng std::tm
		std::tm time_info;
		localtime_s(&time_info, &now_time);

		// Chuyển đổi std::tm sang chuỗi có thể đọc được
		char buf[100];
		std::strftime(buf, sizeof(buf), "%Y-%m-%d | %H:%M:%S", &time_info);

		// Cập nhật văn bản hiển thị trên đồng hồ
		textClock.setString(buf);

		// Xóa cửa sổ
		window.clear();

		// Vẽ các đối tượng lên cửa sổ
		window.draw(sprite);
		window.draw(textClock);
		window.draw(button1);
		window.draw(button2);
		window.draw(iconSprite1);
		window.draw(iconSprite2);
		//window.draw(text);

		// Hiển thị cửa sổ
		window.display();
	}

	return 0;
}

//int main()
//{
//	// tạo cửa sổ kích thước 800x600 pixels
//	sf::RenderWindow window(sf::VideoMode(1195, 672), "drawing line");
//
//	sf::RectangleShape thickline(sf::Vector2f(1195, 3));
//	thickline.setFillColor(sf::Color::Red);
//	thickline.setPosition(0, 100);
//
//
//	//////////////////////order//////////////////
//	sf::Texture texture;
//	if (!texture.loadFromFile("order.jpg"))
//		return EXIT_FAILURE;
//
//	// tạo sprite sử dụng texture đã tải
//	sf::Sprite sprite(texture);
//	sf::Vector2u windowsize = window.getSize();
//	float scalex = 1195.0 / texture.getSize().x;
//	float scaley = 572.0 / texture.getSize().y;
//	sprite.setScale(scalex, scaley);
//	sprite.setPosition(0, 100);
//
//	std::pair<sf::RectangleShape, bool> box[3][12][6];
//	//vector< std::pair<sf::rectangleshape, bool>> box[12][6];
//
//	double x_0 = 157, y_0 = 277;
//	double delta_x = 74.5, delta_y = 64;
//
//	for (int k = 0; k < 3; k++) {
//		for (int i = 0; i < 12; i++) {
//			for (int j = 0; j < 6; j++) {
//				double x = x_0 + i * delta_x, y = y_0 + j * delta_y;
//				box[k][i][j].second = false;
//				box[k][i][j].first.setSize(sf::Vector2f(59, 52));
//				box[k][i][j].first.setFillColor(sf::Color(238, 100, 87)); //100, 238, 87
//				box[k][i][j].first.setOutlineThickness(2);
//				box[k][i][j].first.setOutlineColor(sf::Color::Black);
//				box[k][i][j].first.setPosition(x, y);
//			}
//		}
//	}
//
//
//	//////////////////////order//////////////////
//
//	///////////////////////////////////
//
//	sf::Font font;
//	if (!font.loadFromFile("shortbaby-mg2w.ttf"))
//	{
//		std::cout << "failed to load font!" << std::endl;
//		return -1;
//	}
//
//	//bool selectbutton[3]; memset(selectbutton, false, 3);
//	bool homepagebutton = true;
//	bool selectdropdownbutton = false;
//	bool selectandupdatebutton = false; int indexbutton = 0;
//	bool createbuttonactive = false;
//
//	sf::Text homepagetext("homepage", font, 24);
//	homepagetext.setFillColor(sf::Color::Black);
//	homepagetext.setPosition(500, 500);
//
//	sf::CircleShape button1(25);
//	button1.setFillColor(sf::Color(139, 216, 189)); // màu xám
//	button1.setOutlineThickness(5);
//	button1.setOutlineColor(sf::Color(150, 150, 150)); // màu xám nhạt
//	button1.setPosition(100, 25);
//
//	sf::Texture texture1;
//	if (!texture1.loadFromFile("icon-home-removebg-preview.png"))
//	{
//		std::cout << "failed to load icon." << std::endl;
//		return -1;
//	}
//	sf::Sprite iconsprite1(texture1);
//	iconsprite1.setScale(0.1f, 0.1f);
//	iconsprite1.setPosition(94, 28);
//	///////////////////////////////////
//
//	//////////////////dropdown/////////////////////////
//
//	sf::RectangleShape dropdownbox(sf::Vector2f(125, 50));
//	dropdownbox.setFillColor(sf::Color::white);
//	dropdownbox.setoutlinethickness(2);
//	dropdownbox.setoutlinecolor(sf::Color::black);
//	dropdownbox.setPosition(300, 25);
//
//	sf::text dropdowntext("room", font, 24);
//	dropdowntext.setfillcolor(sf::Color::black);
//	dropdowntext.setposition(319, 35);
//
//	std::vector< std::pair<sf::text, sf::rectangleshape> > options;
//	sf::RectangleShape option1box(sf::Vector2f(125, 50));
//	option1box.setFillColor(sf::Color::white);
//	option1box.setoutlinethickness(2);
//	option1box.setoutlinecolor(sf::Color::black);
//	option1box.setPosition(300, 75);
//
//	sf::text option1("room 1", font, 24);
//	option1.setposition(325, 85);
//	option1.setfillcolor(sf::Color::black);
//	options.push_back({ {option1} , option1box });
//
//	sf::RectangleShape option2box(sf::Vector2f(125, 50));
//	option2box.setFillColor(sf::color::white);
//	option2box.setoutlinethickness(2);
//	option2box.setoutlinecolor(sf::Color::black);
//	option2box.setPosition(300, 125);
//
//	sf::text option2("room 2", font, 24);
//	option2.setposition(325, 135);
//	option2.setfillcolor(sf::Color::black);
//	options.push_back({ {option2} , option2box });
//
//	sf::RectangleShape option3box(sf::Vector2f(125, 50));
//	option3box.setFillColor(sf::Color::white);
//	option3box.setoutlinethickness(2);
//	option3box.setoutlinecolor(sf::Color::black);
//	option3box.setPosition(300, 175);
//
//	sf::Text option3("room 3", font, 24);
//	option3.setPosition(325, 185);
//	option3.setfillcolor(sf::Color::Black);
//	options.push_back({ {option3} , option3box });
//
//	bool isdropdownactive = false;
//
//	sf::ConvexShape arrow(3);
//	arrow.setpoint(0, sf::Vector2f(0, 0));
//	arrow.setpoint(1, sf::Vector2f(15, 0));
//	arrow.setpoint(2, sf::Vector2f(7.5, 7.5));
//	arrow.setfillcolor(sf::Color::black);
//	arrow.setposition(402, 47);
//	bool isarrowdownup = true;
//
//	//////////////////dropdown/////////////////////////
//
//	/////////////////create////////////////////////////
//
//	sf::rectangleshape createbutton(sf::vector2f(125, 50));
//	createbutton.setfillcolor(sf::color::white);
//	createbutton.setoutlinethickness(2);
//	createbutton.setoutlinecolor(sf::color::black);
//	createbutton.setposition(600, 25);
//
//	sf::text createbuttontext("create", font, 24);
//	createbuttontext.setfillcolor(sf::color::black);
//	createbuttontext.setposition(614, 35);
//
//	/////////////////create////////////////////////////
//
//
//	while (window.isopen())
//	{
//		sf::event event;
//		while (window.pollevent(event))
//		{
//			if (event.type == sf::event::closed)
//			{
//				window.close();
//			}
//			if (event.type == sf::event::mousebuttonpressed && event.mousebutton.button == sf::mouse::left)
//			{
//				// kiểm tra xem người dùng đã ấn vào nút hay chưa
//				if (button1.getglobalbounds().contains(event.mousebutton.x, event.mousebutton.y))
//				{
//					homepagebutton = true;
//					selectdropdownbutton = false;
//					selectandupdatebutton = false;
//					indexbutton = 0;
//				}
//				if (ismouseover(dropdownbox, window))
//				{
//					dropdownbox.setfillcolor(sf::color(111, 110, 111));
//					isdropdownactive = !isdropdownactive;
//				}
//				else if (isdropdownactive)
//				{
//					for (int i = 0; i < 3; i++) {
//						{
//							//option.first.second = false;
//							if (ismouseover(options[i].second, window))
//							{
//								dropdowntext.setstring(options[i].first.getstring());
//								indexbutton = i + 1;
//								cout << i << indexbutton << endl;
//								dropdownbox.setfillcolor(sf::color::white);
//								isdropdownactive = false;
//								isarrowdownup = true;
//								homepagebutton = false;  selectdropdownbutton = true; selectandupdatebutton = true;
//								break;
//							}
//						}
//					}
//
//				}
//				if (selectandupdatebutton) {
//					if (indexbutton) {
//						for (int i = 0; i < 12; i++) {
//							for (int j = 0; j < 6; j++) {
//								if (box[indexbutton - 1][i][j].first.getglobalbounds().contains(event.mousebutton.x, event.mousebutton.y)) {
//									if (box[indexbutton - 1][i][j].second) {
//										box[indexbutton - 1][i][j].second = false;
//										box[indexbutton - 1][i][j].first.setfillcolor(sf::color(238, 100, 87)); //100, 238, 87
//
//									}
//									else {
//										box[indexbutton - 1][i][j].second = true;
//										box[indexbutton - 1][i][j].first.setfillcolor(sf::color(100, 238, 87)); //100, 238, 87
//									}
//								}
//							}
//						}
//					}
//				}
//			}
//
//		}
//		window.clear(sf::color::white);
//
//		//if (homepageadmin) {
//		window.draw(button1);
//		window.draw(iconsprite1);
//		//}
//
//		if (homepagebutton) {
//			window.draw(homepagetext);
//		}
//
//		if (selectdropdownbutton) {
//			window.draw(sprite);
//		}
//
//		if (selectandupdatebutton) {
//			if (indexbutton) {
//				for (int i = 0; i < 12; i++) {
//					for (int j = 0; j < 6; j++) {
//						window.draw(box[indexbutton - 1][i][j].first);
//					}
//				}
//			}
//		}
//
//		window.draw(thickline);
//
//		window.draw(dropdownbox);
//		window.draw(dropdowntext);
//		if (isarrowdownup) {
//			arrow.setpoint(0, sf::vector2f(0, 0));
//			arrow.setpoint(1, sf::vector2f(15, 0));
//			arrow.setpoint(2, sf::vector2f(7.5, 7.5));
//			arrow.setfillcolor(sf::color::black);
//			window.draw(arrow);
//		}
//
//		if (isdropdownactive)
//		{
//			isarrowdownup = false;
//			arrow.setpoint(0, sf::vector2f(7.5, 0));
//			arrow.setpoint(1, sf::vector2f(0, 7.5));
//			arrow.setpoint(2, sf::vector2f(15, 7.5));
//			arrow.setfillcolor(sf::color::black);
//			window.draw(arrow);
//
//			for (const std::pair<sf::text, sf::rectangleshape> option : options)
//			{
//				window.draw(option.second);
//				window.draw(option.first);
//			}
//		}
//
//		window.draw(createbutton);
//		window.draw(createbuttontext);
//
//		window.display();
//	}
//}

//int main()
//{
//	// Tạo cửa sổ kích thước 800x600 pixels
//	sf::RenderWindow window(sf::VideoMode(1195, 672), "Drawing Line");
//
//	sf::RectangleShape thickLine(sf::Vector2f(1195, 3));
//	thickLine.setFillColor(sf::Color::Red);
//	thickLine.setPosition(0, 100);
//
//
//	//////////////////////Order//////////////////
//	sf::Texture texture;
//	if (!texture.loadFromFile("order.jpg"))
//		return EXIT_FAILURE;
//
//	// tạo sprite sử dụng texture đã tải
//	sf::Sprite sprite(texture);
//	sf::Vector2u windowsize = window.getSize();
//	float scalex = 1195.0 / texture.getSize().x;
//	float scaley = 572.0 / texture.getSize().y;
//	sprite.setScale(scalex, scaley);
//	sprite.setPosition(0, 100);
//
//	//std::pair<sf::RectangleShape, bool> box[3][12][6];
//	//vector< std::pair<sf::RectangleShape, bool>> box[12][6];
//
//	double x_0 = 157, y_0 = 277;
//	double delta_x = 74.5, delta_y = 64;
//
//	//for (int k = 0; k < 3; k++) {
//	//	for (int i = 0; i < 12; i++) {
//	//		for (int j = 0; j < 6; j++) {
//	//			double x = x_0 + i * delta_x, y = y_0 + j * delta_y;
//	//			box[k][i][j].second = false;
//	//			box[k][i][j].first.setSize(sf::Vector2f(59, 52));
//	//			box[k][i][j].first.setFillColor(sf::Color(238, 100, 87)); //100, 238, 87
//	//			box[k][i][j].first.setOutlineThickness(2);
//	//			box[k][i][j].first.setOutlineColor(sf::Color::Black);
//	//			box[k][i][j].first.setPosition(x, y);
//	//		}
//	//	}
//	//}
//
//	std::pair<sf::RectangleShape, bool> box[12][6];
//	for (int i = 0; i < 12; i++) {
//		for (int j = 0; j < 6; j++) {
//			double x = x_0 + i * delta_x, y = y_0 + j * delta_y;
//			box[i][j].second = false;
//			box[i][j].first.setSize(sf::Vector2f(59, 52));
//			box[i][j].first.setFillColor(sf::Color(238, 100, 87)); //100, 238, 87
//			box[i][j].first.setOutlineThickness(2);
//			box[i][j].first.setOutlineColor(sf::Color::Black);
//			box[i][j].first.setPosition(x, y);
//		}
//	}
//
//
//	//////////////////////Order//////////////////
//
//	///////////////////////////////////
//
//	sf::Font font;
//	if (!font.loadFromFile("ShortBaby-Mg2w.ttf"))
//	{
//		std::cout << "Failed to load font!" << std::endl;
//		return -1;
//	}
//
//	//bool selectButton[3]; memset(selectButton, false, 3);
//	bool homePageButton = true;
//	bool selectDropDownButton = false;
//	bool selectAndUpdateButton = false;
//	bool createButtonActive = false;
//
//	sf::Text homePageText("HomePage", font, 24);
//	homePageText.setFillColor(sf::Color::Black);
//	homePageText.setPosition(500, 500);
//
//	sf::CircleShape button1(25);
//	button1.setFillColor(sf::Color(139, 216, 189)); // Màu xám
//	button1.setOutlineThickness(5);
//	button1.setOutlineColor(sf::Color(150, 150, 150)); // Màu xám nhạt
//	button1.setPosition(100, 25);
//
//	sf::Texture texture1;
//	if (!texture1.loadFromFile("icon-home-removebg-preview.png"))
//	{
//		std::cout << "Failed to load icon." << std::endl;
//		return -1;
//	}
//	sf::Sprite iconSprite1(texture1);
//	iconSprite1.setScale(0.1f, 0.1f);
//	iconSprite1.setPosition(94, 28);
//	///////////////////////////////////
//
//	//////////////////dropdown/////////////////////////
//
//	sf::RectangleShape dropdownBox(sf::Vector2f(125, 50));
//	dropdownBox.setFillColor(sf::Color::White);
//	dropdownBox.setOutlineThickness(2);
//	dropdownBox.setOutlineColor(sf::Color::Black);
//	dropdownBox.setPosition(300, 25);
//
//	sf::Text dropdownText("Rap", font, 24);
//	dropdownText.setFillColor(sf::Color::Black);
//	dropdownText.setPosition(331, 35);
//
//	std::vector< std::pair<sf::Text, sf::RectangleShape> > options;
//	sf::RectangleShape option1Box(sf::Vector2f(125, 50));
//	option1Box.setFillColor(sf::Color::White);
//	option1Box.setOutlineThickness(2);
//	option1Box.setOutlineColor(sf::Color::Black);
//	option1Box.setPosition(300, 75);
//
//	sf::Text option1("Rap 1", font, 24);
//	option1.setPosition(330, 85);
//	option1.setFillColor(sf::Color::Black);
//	options.push_back({ option1 , option1Box });
//
//	sf::RectangleShape option2Box(sf::Vector2f(125, 50));
//	option2Box.setFillColor(sf::Color::White);
//	option2Box.setOutlineThickness(2);
//	option2Box.setOutlineColor(sf::Color::Black);
//	option2Box.setPosition(300, 125);
//
//	sf::Text option2("Rap 2", font, 24);
//	option2.setPosition(330, 135);
//	option2.setFillColor(sf::Color::Black);
//	options.push_back({ option2 , option2Box });
//
//	sf::RectangleShape option3Box(sf::Vector2f(125, 50));
//	option3Box.setFillColor(sf::Color::White);
//	option3Box.setOutlineThickness(2);
//	option3Box.setOutlineColor(sf::Color::Black);
//	option3Box.setPosition(300, 175);
//
//	sf::Text option3("Rap 3", font, 24);
//	option3.setPosition(330, 185);
//	option3.setFillColor(sf::Color::Black);
//	options.push_back({ option3 , option3Box });
//
//	bool isDropdownActive = false;
//
//	sf::ConvexShape arrow(3);
//	arrow.setPoint(0, sf::Vector2f(0, 0));
//	arrow.setPoint(1, sf::Vector2f(15, 0));
//	arrow.setPoint(2, sf::Vector2f(7.5, 7.5));
//	arrow.setFillColor(sf::Color::Black);
//	arrow.setPosition(400, 47);
//	bool isArrowDownUp = true;
//
//	//////////////////dropdown/////////////////////////
//
//	/////////////////create////////////////////////////
//
//	sf::RectangleShape createButton(sf::Vector2f(125, 50));
//	createButton.setFillColor(sf::Color::White);
//	createButton.setOutlineThickness(2);
//	createButton.setOutlineColor(sf::Color::Black);
//	createButton.setPosition(600, 25);
//
//	sf::Text createButtonText("them moi", font, 24);
//	createButtonText.setFillColor(sf::Color::Black);
//	createButtonText.setPosition(614, 35);
//
//	/////////////////create////////////////////////////
//
//
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//			{
//				window.close();
//			}
//			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
//			{
//				// Kiểm tra xem người dùng đã ấn vào nút hay chưa
//				if (button1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
//				{
//					homePageButton = true;
//					selectDropDownButton = false;
//					selectAndUpdateButton = false;
//				}
//				if (isMouseOver(dropdownBox, window))
//				{
//					dropdownBox.setFillColor(sf::Color(111, 110, 111));
//					isDropdownActive = !isDropdownActive;
//				}
//				else if (isDropdownActive)
//				{
//					for (int i = 0; i < 3; i++) {
//						{
//							if (isMouseOver(options[i].second, window))
//							{
//								dropdownText.setString(options[i].first.getString());
//								dropdownBox.setFillColor(sf::Color::White);
//								isDropdownActive = false;
//								isArrowDownUp = true;
//								homePageButton = false;  selectDropDownButton = true; selectAndUpdateButton = true;
//								break;
//							}
//						}
//					}
//
//				}
//				if (selectAndUpdateButton) {
//					for (int i = 0; i < 12; i++) {
//						for (int j = 0; j < 6; j++) {
//							if (box[i][j].first.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
//								if (box[i][j].second) {
//									box[i][j].second = false;
//									box[i][j].first.setFillColor(sf::Color(238, 100, 87)); //100, 238, 87
//
//								}
//								else {
//									box[i][j].second = true;
//									box[i][j].first.setFillColor(sf::Color(100, 238, 87)); //100, 238, 87
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//		window.clear(sf::Color::White);
//
//		//if (homePageAdmin) {
//		window.draw(button1);
//		window.draw(iconSprite1);
//		//}
//
//		if (homePageButton) {
//			window.draw(homePageText);
//		}
//
//		if (selectDropDownButton) {
//			window.draw(sprite);
//		}
//
//		if (selectAndUpdateButton) {
//			for (int i = 0; i < 12; i++) {
//				for (int j = 0; j < 6; j++) {
//					window.draw(box[i][j].first);
//				}
//			}
//		}
//
//		window.draw(thickLine);
//
//		window.draw(dropdownBox);
//		window.draw(dropdownText);
//		if (isArrowDownUp) {
//			arrow.setPoint(0, sf::Vector2f(0, 0));
//			arrow.setPoint(1, sf::Vector2f(15, 0));
//			arrow.setPoint(2, sf::Vector2f(7.5, 7.5));
//			arrow.setFillColor(sf::Color::Black);
//			window.draw(arrow);
//		}
//
//		if (isDropdownActive)
//		{
//			isArrowDownUp = false;
//			arrow.setPoint(0, sf::Vector2f(7.5, 0));
//			arrow.setPoint(1, sf::Vector2f(0, 7.5));
//			arrow.setPoint(2, sf::Vector2f(15, 7.5));
//			arrow.setFillColor(sf::Color::Black);
//			window.draw(arrow);
//
//			for (const std::pair<sf::Text, sf::RectangleShape> option : options)
//			{
//				window.draw(option.second);
//				window.draw(option.first);
//			}
//		}
//
//		window.draw(createButton);
//		window.draw(createButtonText);
//
//		window.display();
//	}
//}



//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <string>
//#include <vector>
//
//
//int main()
//{
//	// Tạo cửa sổ kích thước 800x600 pixels
//	sf::RenderWindow window(sf::VideoMode(1195, 672), "Product List");
//
//	// Tạo danh sách sản phẩm
//
//	sf::RectangleShape thickLine(sf::Vector2f(1195, 3));
//	thickLine.setFillColor(sf::Color::Red);
//	thickLine.setPosition(0, 100);
//
//	// Tạo các sản phẩm
//	sf::Font font;
//	if (!font.loadFromFile("SVN-Times New Roman Bold.ttf"))
//	{
//		std::cout << "Failed to load font!" << std::endl;
//		return -1;
//	}
//
//	std::vector<pair<string, string>> films;
//
//	string title = "My nhan dao chich";
//	string linkImage = "mynhandaochich.jpg";
//	films.push_back({ title, linkImage });
//
//	title = "Am hon do thi";
//	linkImage = "amhondothi.jpg";
//	films.push_back({ title, linkImage });
//
//	title = "Nguoi vo cuoi cung";
//	linkImage = "nguoivocuoicung.jpg";
//	films.push_back({ title, linkImage });
//
//	title = "Nam dem kinh hoang";
//	linkImage = "5demkinhhoang.jpg";
//	films.push_back({ title, linkImage });
//
//	title = "Quy mon quan";
//	linkImage = "quymonquan.jpg";
//	films.push_back({ title, linkImage });
//
//	title = "Wolfoo";
//	linkImage = "wolfoo.jpg";
//	films.push_back({ title, linkImage });
//
//	title = "Dat rung phuong nam";
//	linkImage = "datrungphuongnam.jpg";
//	films.push_back({ title, linkImage });
//
//	title = "Biet doi Marvel";
//	linkImage = "marvel.jpg";
//	films.push_back({ title, linkImage });
//
//	title = "Hai ke doi tra";
//	linkImage = "haikedoitra.png";
//	films.push_back({ title, linkImage });
//
//	std::vector<pair<sf::RectangleShape, pair<sf::Text, string>>> productBoxes;
//
//	for (int i = 0; i < films.size(); i++)
//	{
//		sf::RectangleShape productBox(sf::Vector2f(300, 500));
//		productBox.setFillColor(sf::Color::White);
//		productBox.setOutlineThickness(2);
//		productBox.setOutlineColor(sf::Color::Black);
//		productBox.setPosition(20 + i * 350, 125);
//
//		sf::Text productText(films[i].first, font, 24);
//		productText.setFillColor(sf::Color::Black);
//		float textX = productBox.getPosition().x + productBox.getSize().x / 2 - productText.getLocalBounds().width / 2;
//		//productText.setPosition(30 + i * 350, 135);
//		productText.setPosition(textX, 600);
//
//		productBoxes.push_back({ productBox , {productText, films[i].second} });
//	}
//
//	// Vòng lặp chính
//	while (window.isOpen())
//	{
//		// Xử lý các sự kiện
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//			{
//				window.close();
//			}
//			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
//			{
//				for (int i = 0; i < productBoxes.size(); i++)
//				{
//					if (productBoxes[i].first.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
//						cout << productBoxes[i].second.first.getString().toAnsiString() << endl;
//					}
//				}
//			}
//		}
//
//		// Cập nhật vị trí của các sản phẩm
//		sf::Vector2f offset(0, 0);
//		sf::Vector2f newPos = productBoxes[productBoxes.size() - 1].first.getPosition() + offset;
//		float textX = productBoxes[productBoxes.size() - 1].first.getPosition().x + productBoxes[productBoxes.size() - 1].first.getSize().x / 2 - productBoxes[productBoxes.size() - 1].second.first.getLocalBounds().width / 2;
//
//		for (int i = productBoxes.size() - 1; i >= 1; i--)
//		{
//			productBoxes[i].first.setPosition(productBoxes[i - 1].first.getPosition());
//			float textX = productBoxes[i].first.getPosition().x + productBoxes[i].first.getSize().x / 2 - productBoxes[i].second.first.getLocalBounds().width / 2;
//			productBoxes[i].second.first.setPosition(textX, 600);
//		}
//
//		productBoxes[0].first.setPosition(newPos);
//		productBoxes[0].second.first.setPosition(textX, 600);
//
//		// Xóa màn hình
//		window.clear(sf::Color::White);
//
//		//window.draw(sprite);
//		window.draw(thickLine);
//
//
//
//		// Vẽ các sản phẩm
//		for (int i = 0; i < films.size(); i++)
//		{
//			sf::Texture texture;
//			if (!texture.loadFromFile(productBoxes[i].second.second)) {
//				return EXIT_FAILURE;
//			}
//			sf::Sprite sprite(texture);
//			sf::Vector2u windowsize = window.getSize();
//			float scalex = 290.0 / texture.getSize().x;
//			float scaley = 475.0 / texture.getSize().y;
//			sprite.setScale(scalex, scaley);
//			float x = productBoxes[i].first.getPosition().x + 5;
//			float y = productBoxes[i].first.getPosition().y + 5;
//			sprite.setPosition(x, y);
//
//			window.draw(productBoxes[i].first);
//			window.draw(sprite);
//			window.draw(productBoxes[i].second.first);
//		}
//
//
//		// Hiển thị màn hình
//		window.display();
//
//		// Chờ một giây
//		sf::sleep(sf::seconds(1));
//	}
//
//	return 0;
//}

//int main()
//{
//	sf::RenderWindow window(sf::VideoMode(1195, 672), "Drawing Line");
//
//	sf::RenderWindow window1(sf::VideoMode(1050, 1000), "Create Window", sf::Style::None);
//	window1.setVisible(false);
//
//	sf::RenderWindow window2(sf::VideoMode(1050, 1000), "Update Window", sf::Style::None);
//	window2.setVisible(false);
//
//	//////////////////////Font///////////////////////////
//	sf::Font font;
//	if (!font.loadFromFile("SVN-Times New Roman Bold.ttf"))
//	{
//		std::cout << "Failed to load font!" << std::endl;
//		return -1;
//	}
//	//////////////////////Font///////////////////////////
//
//
//	sf::RectangleShape thickLine(sf::Vector2f(1195, 3));
//	thickLine.setFillColor(sf::Color::Red);
//	thickLine.setPosition(0, 100);
//
//	//////////////////////HomePage//////////////////
//
//	//std::vector<pair<string, string>> films;
//
//	string title = "My nhan dao chich";
//	string desc = "";
//	string linkImage = "mynhandaochich.jpg";
//	films.push_back({ title, desc, linkImage });
//
//	title = "Am hon do thi";
//	desc = "";
//	linkImage = "amhondothi.jpg";
//	films.push_back({ title, desc, linkImage });
//
//	title = "Nguoi vo cuoi cung";
//	desc = "";
//	linkImage = "nguoivocuoicung.jpg";
//	films.push_back({ title, desc, linkImage });
//
//	title = "Nam dem kinh hoang";
//	desc = "";
//	linkImage = "5demkinhhoang.jpg";
//	films.push_back({ title, desc, linkImage });
//
//	title = "Quy mon quan";
//	desc = "";
//	linkImage = "quymonquan.jpg";
//	films.push_back({ title, desc, linkImage });
//
//	title = "Wolfoo";
//	desc = "";
//	linkImage = "wolfoo.jpg";
//	films.push_back({ title, desc, linkImage });
//
//	title = "Dat rung phuong nam";
//	desc = "";
//	linkImage = "marvel.jpg";
//	films.push_back({ title, desc, linkImage });
//
//	title = "Biet doi Marvel";
//	desc = "";
//	linkImage = "marvel.jpg";
//	films.push_back({ title, desc, linkImage });
//
//	title = "Hai ke doi tra";
//	desc = "";
//	linkImage = "haikedoitra.png";
//	films.push_back({ title, desc, linkImage });
//
//	//std::vector<pair<sf::RectangleShape, pair<sf::Text, string>>> productBoxes;
//
//	for (int i = 0; i < films.size(); i++)
//	{
//		sf::RectangleShape productBox(sf::Vector2f(300, 500));
//		productBox.setFillColor(sf::Color::White);
//		productBox.setOutlineThickness(2);
//		productBox.setOutlineColor(sf::Color::Black);
//
//		sf::Text productText(films[i].title, font, 24);
//		productText.setFillColor(sf::Color::Black);
//
//		productBoxes.push_back({ productBox , {productText, films[i].image} });
//	}
//
//	sf::Texture updateTexture;
//	if (!updateTexture.loadFromFile("button_update.png"))
//		return EXIT_FAILURE;
//
//	sf::Sprite updateSprite(updateTexture);
//
//	sf::Texture deleteTexture;
//	if (!deleteTexture.loadFromFile("button_delete.png"))
//		return EXIT_FAILURE;
//
//	sf::Sprite deleteSprite(deleteTexture);
//
//	//////////////////////HomePage//////////////////
//
//
//	//////////////////////Order//////////////////
//	sf::Texture texture;
//	if (!texture.loadFromFile("order.jpg"))
//		return EXIT_FAILURE;
//
//	// tạo sprite sử dụng texture đã tải
//	sf::Sprite sprite(texture);
//	sf::Vector2u windowsize = window.getSize();
//	float scalex = 1195.0 / texture.getSize().x;
//	float scaley = 572.0 / texture.getSize().y;
//	sprite.setScale(scalex, scaley);
//	sprite.setPosition(0, 100);
//
//	std::pair<sf::RectangleShape, bool> box[3][12][6];
//	//vector< std::pair<sf::RectangleShape, bool>> box[12][6];
//
//	double x_0 = 157, y_0 = 277;
//	double delta_x = 74.5, delta_y = 64;
//
//	for (int k = 0; k < 3; k++) {
//		for (int i = 0; i < 12; i++) {
//			for (int j = 0; j < 6; j++) {
//				double x = x_0 + i * delta_x, y = y_0 + j * delta_y;
//				box[k][i][j].second = false;
//				box[k][i][j].first.setSize(sf::Vector2f(59, 52));
//				box[k][i][j].first.setFillColor(sf::Color(238, 100, 87)); //100, 238, 87
//				box[k][i][j].first.setOutlineThickness(2);
//				box[k][i][j].first.setOutlineColor(sf::Color::Black);
//				box[k][i][j].first.setPosition(x, y);
//			}
//		}
//	}
//
//
//	//////////////////////Order//////////////////
//
//	///////////////////////////////////
//
//	//bool selectButton[3]; memset(selectButton, false, 3);
//	bool homePageButton = true;
//	bool selectDropDownButton = false;
//	bool selectAndUpdateButton = false; int indexButton = 0;
//	bool createButtonActive = false;
//
//	sf::Text homePageText("HomePage", font, 24);
//	homePageText.setFillColor(sf::Color::Black);
//	homePageText.setPosition(500, 500);
//
//	sf::CircleShape button1(25);
//	button1.setFillColor(sf::Color(139, 216, 189)); // Màu xám
//	button1.setOutlineThickness(5);
//	button1.setOutlineColor(sf::Color(150, 150, 150)); // Màu xám nhạt
//	button1.setPosition(100, 25);
//
//	sf::Texture texture1;
//	if (!texture1.loadFromFile("icon-home-removebg-preview.png"))
//	{
//		std::cout << "Failed to load icon." << std::endl;
//		return -1;
//	}
//	sf::Sprite iconSprite1(texture1);
//	iconSprite1.setScale(0.1f, 0.1f);
//	iconSprite1.setPosition(94, 28);
//	///////////////////////////////////
//
//	//////////////////dropdown/////////////////////////
//
//	sf::RectangleShape dropdownBox(sf::Vector2f(125, 50));
//	dropdownBox.setFillColor(sf::Color::White);
//	dropdownBox.setOutlineThickness(2);
//	dropdownBox.setOutlineColor(sf::Color::Black);
//	dropdownBox.setPosition(300, 25);
//
//	sf::Text dropdownText("Room", font, 24);
//	dropdownText.setFillColor(sf::Color::Black);
//	dropdownText.setPosition(320, 35);
//
//	std::vector< std::pair<sf::Text, sf::RectangleShape> > options;
//	sf::RectangleShape option1Box(sf::Vector2f(125, 50));
//	option1Box.setFillColor(sf::Color::White);
//	option1Box.setOutlineThickness(2);
//	option1Box.setOutlineColor(sf::Color::Black);
//	option1Box.setPosition(300, 75);
//
//	sf::Text option1("Room 1", font, 24);
//	option1.setPosition(323, 85);
//	option1.setFillColor(sf::Color::Black);
//	options.push_back({ {option1} , option1Box });
//
//	sf::RectangleShape option2Box(sf::Vector2f(125, 50));
//	option2Box.setFillColor(sf::Color::White);
//	option2Box.setOutlineThickness(2);
//	option2Box.setOutlineColor(sf::Color::Black);
//	option2Box.setPosition(300, 125);
//
//	sf::Text option2("Room 2", font, 24);
//	option2.setPosition(323, 135);
//	option2.setFillColor(sf::Color::Black);
//	options.push_back({ {option2} , option2Box });
//
//	sf::RectangleShape option3Box(sf::Vector2f(125, 50));
//	option3Box.setFillColor(sf::Color::White);
//	option3Box.setOutlineThickness(2);
//	option3Box.setOutlineColor(sf::Color::Black);
//	option3Box.setPosition(300, 175);
//
//	sf::Text option3("Room 3", font, 24);
//	option3.setPosition(323, 185);
//	option3.setFillColor(sf::Color::Black);
//	options.push_back({ {option3} , option3Box });
//
//	bool isDropdownActive = false;
//
//	sf::ConvexShape arrow(3);
//	arrow.setPoint(0, sf::Vector2f(0, 0));
//	arrow.setPoint(1, sf::Vector2f(15, 0));
//	arrow.setPoint(2, sf::Vector2f(7.5, 7.5));
//	arrow.setFillColor(sf::Color::Black);
//	arrow.setPosition(405, 47);
//	bool isArrowDownUp = true;
//
//	//////////////////dropdown/////////////////////////
//
//	/////////////////create////////////////////////////
//
//	sf::RectangleShape createButton(sf::Vector2f(125, 50));
//	createButton.setFillColor(sf::Color::White);
//	createButton.setOutlineThickness(2);
//	createButton.setOutlineColor(sf::Color::Black);
//	createButton.setPosition(600, 25);
//
//	sf::Text createButtonText("Create", font, 24);
//	createButtonText.setFillColor(sf::Color::Black);
//	createButtonText.setPosition(630, 35);
//
//	/////////////////create////////////////////////////
//
//	float position = 50.0f;
//	int first = 0, last = films.size() - 1;
//	std::thread thread(updateFilmPosition, std::ref(position), std::ref(first), std::ref(last));
//
//	int cnt = 0;
//
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//			{
//				window.close();
//				thread.detach();
//			}
//			if (homePageButton) {
//				//position = 50.0f;
//				//first = 0, last = films.size() - 1;
//				//std::thread tempThread(updateFilmPosition, std::ref(position), std::ref(first), std::ref(last));
//				//thread.swap(tempThread);
//
//				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
//				{
//					int chosenIndex = -1;
//					for (int i = 0; i < productBoxes.size(); i++)
//					{
//						if (productBoxes[i].first.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
//							//cout << films[i].title << " " << films[i].desc << " " << films[i].image << endl;
//							cout << i << endl;
//
//							//std::mutex mtx;
//							//std::condition_variable cv;
//							//std::unique_lock<std::mutex> lck(mtx);
//							//cv.wait(lck);
//							//isPaused = true;
//
//							//updateFilmsWindow(window, window2, font, i);
//							//isPaused = false;
//							//break;
//							films[i].isClicked = true;
//							chosenIndex = i;
//						}
//						else if (updateSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
//							cout << "update" << chosenIndex << endl;
//						}
//						else if (deleteSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
//							cout << "delete" << chosenIndex << endl;
//						}
//						else{
//							films[i].isClicked = false;
//							cout << "false\n";
//						}
//
//					}
//					//if (chosenIndex != -1) {
//					//	cout << "oke";
//					//	if (updateSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
//					//		cout << "update\n";
//					//	else if (deleteSprite.getGlobalBounds().contai
//					//	}ns(event.mouseButton.x, event.mouseButton.y)) {
//					//		cout << "delete\n";
//					//	}
//					//}
//					if (isMouseOver(dropdownBox, window))
//					{
//						dropdownBox.setFillColor(sf::Color(111, 110, 111));
//						isDropdownActive = !isDropdownActive;
//					}
//					else if (isDropdownActive)
//					{
//						for (int i = 0; i < 3; i++) {
//							{
//								//option.first.second = false;
//								if (isMouseOver(options[i].second, window))
//								{
//									dropdownText.setString(options[i].first.getString());
//									indexButton = i + 1;
//									dropdownBox.setFillColor(sf::Color::White);
//									isDropdownActive = false;
//									isArrowDownUp = true;
//									homePageButton = false;  selectDropDownButton = true; selectAndUpdateButton = true;
//									break;
//								}
//							}
//						}
//
//					}
//					if (createButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
//					{
//						createFilmsWindow(window, window1, font);
//					}
//				}
//			}
//			else if (selectAndUpdateButton) {
//				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
//				{
//					if (button1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
//					{
//						homePageButton = true;
//						selectDropDownButton = false;
//						dropdownText.setString("Room");
//						selectAndUpdateButton = false;
//						indexButton = 0;
//					}
//					if (isMouseOver(dropdownBox, window))
//					{
//						dropdownBox.setFillColor(sf::Color(111, 110, 111));
//						isDropdownActive = !isDropdownActive;
//					}
//					else if (isDropdownActive)
//					{
//						for (int i = 0; i < 3; i++) {
//							//option.first.second = false;
//							if (isMouseOver(options[i].second, window))
//							{
//								dropdownText.setString(options[i].first.getString());
//								indexButton = i + 1;
//								dropdownBox.setFillColor(sf::Color::White);
//								isDropdownActive = false;
//								isArrowDownUp = true;
//								homePageButton = false;  selectDropDownButton = true; selectAndUpdateButton = true;
//								break;
//							}
//						}
//					}
//					if (selectAndUpdateButton) {
//						if (indexButton) {
//							for (int i = 0; i < 12; i++) {
//								for (int j = 0; j < 6; j++) {
//									if (box[indexButton - 1][i][j].first.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
//										if (box[indexButton - 1][i][j].second) {
//											box[indexButton - 1][i][j].second = false;
//											box[indexButton - 1][i][j].first.setFillColor(sf::Color(238, 100, 87)); //100, 238, 87
//
//										}
//										else {
//											box[indexButton - 1][i][j].second = true;
//											box[indexButton - 1][i][j].first.setFillColor(sf::Color(100, 238, 87)); //100, 238, 87
//										}
//									}
//								}
//							}
//						}
//					}
//					if (createButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
//					{
//						createFilmsWindow(window, window1, font);
//					}
//				}
//			}
//		}
//		window.clear(sf::Color::White);
//
//		//if (homePageAdmin) {
//		window.draw(button1);
//		window.draw(iconSprite1);
//		//}
//
//		if (homePageButton) {
//			productBoxes[first].first.setPosition(position, 125);
//			float text_X = position + productBoxes[first].first.getSize().x / 2 - productBoxes[first].second.first.getLocalBounds().width / 2;
//			productBoxes[first].second.first.setPosition(text_X, 600);
//			sf::Texture texture;
//			if (!texture.loadFromFile(productBoxes[first].second.second)) {
//				texture.loadFromFile("404.jfif");
//			}
//			sf::Sprite sprite(texture);
//			float scalex = 290.0 / texture.getSize().x;
//			float scaley = 475.0 / texture.getSize().y;
//			sprite.setScale(scalex, scaley);
//			float x = position + 5;
//			float y = productBoxes[first].first.getPosition().y + 5;
//			sprite.setPosition(x, y);
//			window.draw(productBoxes[first].first);
//			window.draw(sprite);
//			window.draw(productBoxes[first].second.first);
//
//			int cnt = 0; // co the error
//			for (int i = first + 1; i < films.size(); i++) {
//				float pos = position + ++cnt * 350;
//				productBoxes[i].first.setPosition(pos, 125);
//				float text_X = pos + productBoxes[i].first.getSize().x / 2 - productBoxes[i].second.first.getLocalBounds().width / 2;
//				productBoxes[i].second.first.setPosition(text_X, 600);
//				sf::Texture texture;
//				if (!texture.loadFromFile(productBoxes[i].second.second)) {
//					texture.loadFromFile("404.jfif");
//				}
//				sf::Sprite sprite(texture);
//				float scalex = 290.0 / texture.getSize().x;
//				float scaley = 475.0 / texture.getSize().y;
//				sprite.setScale(scalex, scaley);
//				float x = pos + 5;
//				float y = productBoxes[i].first.getPosition().y + 5;
//				sprite.setPosition(x, y);
//				window.draw(productBoxes[i].first);
//				window.draw(sprite);
//				window.draw(productBoxes[i].second.first);
//			}
//
//			for (int i = 0; i < first; i++) {
//				float pos = position + ++cnt * 350;
//				productBoxes[i].first.setPosition(pos, 125);
//				float text_X = pos + productBoxes[i].first.getSize().x / 2 - productBoxes[i].second.first.getLocalBounds().width / 2;
//				productBoxes[i].second.first.setPosition(text_X, 600);
//				sf::Texture texture;
//				if (!texture.loadFromFile(productBoxes[i].second.second)) {
//					texture.loadFromFile("404.jfif");
//				}
//				sf::Sprite sprite(texture);
//				float scalex = 290.0 / texture.getSize().x;
//				float scaley = 475.0 / texture.getSize().y;
//				sprite.setScale(scalex, scaley);
//				float x = pos + 5;
//				float y = productBoxes[i].first.getPosition().y + 5;
//				sprite.setPosition(x, y);
//				window.draw(productBoxes[i].first);
//				window.draw(sprite);
//				window.draw(productBoxes[i].second.first);
//			}
//
//			for (int i = 0; i < films.size(); i++) {
//				if (films[i].isClicked) {
//
//					float scale_x = 149.0 / updateTexture.getSize().x;
//					float scale_y = 30.0 / updateTexture.getSize().y;
//					updateSprite.setScale(scale_x, scale_y);
//					float posi = productBoxes[i].first.getPosition().x;
//					float boxSize = productBoxes[i].first.getSize().x / 2;
//					updateSprite.setPosition(posi, 628);
//
//					scale_x = 149.0 / deleteTexture.getSize().x;
//					scale_y = 30.0 / deleteTexture.getSize().y;
//					deleteSprite.setScale(scale_x, scale_y);
//					deleteSprite.setPosition(posi + boxSize + 1, 628);
//
//					sf::Font fontUpdate;
//					if (!fontUpdate.loadFromFile("SourceSansPro-Bold.ttf"))
//					{
//						std::cout << "Failed to load font!" << std::endl;
//						return -1;
//					}
//
//					sf::Text textUpdate;
//					textUpdate.setFont(fontUpdate);
//					textUpdate.setCharacterSize(25);
//					textUpdate.setFillColor(sf::Color(255, 255, 255));
//					textUpdate.setString("UPDATE");
//					float widthText1 = textUpdate.getLocalBounds().width / 2;
//					textUpdate.setPosition(posi + boxSize / 2 + 1 - widthText1, 626);
//
//
//					sf::Text textDelete;
//					textDelete.setFont(fontUpdate);
//					textDelete.setCharacterSize(25);
//					textDelete.setFillColor(sf::Color(255, 255, 255));
//					textDelete.setString("DELETE");
//					float widthText2 = textDelete.getLocalBounds().width / 2;
//					textDelete.setPosition(posi + boxSize * 3 / 2 + 1 - widthText2, 626);
//
//
//					window.draw(updateSprite);
//					window.draw(deleteSprite);
//					window.draw(textUpdate);
//					window.draw(textDelete);
//				}
//			}
//		}
//
//		if (selectDropDownButton) {
//			window.draw(sprite);
//		}
//
//		if (selectAndUpdateButton) {
//			if (indexButton) {
//				for (int i = 0; i < 12; i++) {
//					for (int j = 0; j < 6; j++) {
//						window.draw(box[indexButton - 1][i][j].first);
//					}
//				}
//			}
//		}
//
//		window.draw(thickLine);
//
//		window.draw(dropdownBox);
//		window.draw(dropdownText);
//		if (isArrowDownUp) {
//			arrow.setPoint(0, sf::Vector2f(0, 0));
//			arrow.setPoint(1, sf::Vector2f(15, 0));
//			arrow.setPoint(2, sf::Vector2f(7.5, 7.5));
//			arrow.setFillColor(sf::Color::Black);
//			window.draw(arrow);
//		}
//
//		if (isDropdownActive)
//		{
//			isArrowDownUp = false;
//			arrow.setPoint(0, sf::Vector2f(7.5, 0));
//			arrow.setPoint(1, sf::Vector2f(0, 7.5));
//			arrow.setPoint(2, sf::Vector2f(15, 7.5));
//			arrow.setFillColor(sf::Color::Black);
//			window.draw(arrow);
//
//			for (const std::pair<sf::Text, sf::RectangleShape> option : options)
//			{
//				window.draw(option.second);
//				window.draw(option.first);
//			}
//		}
//
//		window.draw(createButton);
//		window.draw(createButtonText);
//
//		window.display();
//	}
//}

//int main()
//{
//	sf::RenderWindow window(sf::VideoMode(1500, 900), "Drawing Line");
//
//	sf::RenderWindow window1(sf::VideoMode(1050, 1000), "Create Window", sf::Style::None);
//	window1.setVisible(false);
//
//	sf::RenderWindow window2(sf::VideoMode(1050, 1000), "Update Window", sf::Style::None);
//	window2.setVisible(false);
//
//	sf::Texture texture;
//	if (!texture.loadFromFile("image-admin.jpg"))
//		return EXIT_FAILURE;
//
//	// tạo sprite sử dụng texture đã tải
//	sf::Sprite sprite(texture);
//	sf::Vector2u windowsize = window.getSize();
//	float scalex = 1500.0 / texture.getSize().x;
//	float scaley = 900.0 / texture.getSize().y;
//	sprite.setScale(scalex, scaley);
//
//	//////////////////////Font///////////////////////////
//	sf::Font font;
//	if (!font.loadFromFile("Roboto-Bold.ttf"))
//	{
//		std::cout << "Failed to load font!" << std::endl;
//		return -1;
//	}
//	//////////////////////Font///////////////////////////
//
//	sf::RectangleShape headerBox(sf::Vector2f(1500, 100));
//	headerBox.setFillColor(sf::Color(3, 19, 39)); //205, 156, 124, 150
//	headerBox.setPosition(0, 0);
//
//	//////////////////////Movie//////////////////
//
//	//std::vector<pair<string, string>> films;
//
//	string title = "My nhan dao chich";
//	string desc = "";
//	string linkImage = "mynhandaochich.jpg";
//	films.push_back({ title, desc, linkImage });
//
//	title = "Am hon do thi";
//	desc = "";
//	linkImage = "amhondothi.jpg";
//	films.push_back({ title, desc, linkImage });
//
//	title = "Nguoi vo cuoi cung";
//	desc = "";
//	linkImage = "nguoivocuoicung.jpg";
//	films.push_back({ title, desc, linkImage });
//
//	title = "Nam dem kinh hoang";
//	desc = "";
//	linkImage = "5demkinhhoang.jpg";
//	films.push_back({ title, desc, linkImage });
//
//	title = "Quy mon quan";
//	desc = "";
//	linkImage = "quymonquan.jpg";
//	films.push_back({ title, desc, linkImage });
//
//	title = "Wolfoo";
//	desc = "";
//	linkImage = "wolfoo.jpg";
//	films.push_back({ title, desc, linkImage });
//
//	title = "Dat rung phuong nam";
//	desc = "";
//	linkImage = "marvel.jpg";
//	films.push_back({ title, desc, linkImage });
//
//	title = "Biet doi Marvel";
//	desc = "";
//	linkImage = "marvel.jpg";
//	films.push_back({ title, desc, linkImage });
//
//	title = "Hai ke doi tra";
//	desc = "";
//	linkImage = "haikedoitra.png";
//	films.push_back({ title, desc, linkImage });
//
//	//std::vector<pair<sf::RectangleShape, pair<sf::Text, string>>> productBoxes;
//
//	//for (int i = 0; i < films.size(); i++)
//	//{
//	//	sf::RectangleShape productBox(sf::Vector2f(300, 500));
//	//	productBox.setFillColor(sf::Color::White);
//	//	productBox.setOutlineThickness(2);
//	//	productBox.setOutlineColor(sf::Color::Black);
//
//	//	sf::Text productText(films[i].title, font, 24);
//	//	productText.setFillColor(sf::Color::Black);
//
//	//	productBoxes.push_back({ productBox , {productText, films[i].image} });
//	//}
//
//	float filmListPosition1 = 120.f;
//
//	for (int i = 0; i < films.size(); i++)
//	{
//		sf::RectangleShape productBox(sf::Vector2f(327.5f, 470.f));
//		productBox.setPosition(20.f + 377.5 * (int)(i % 4), filmListPosition1 + (int)(i / 4) * 500);
//		productBox.setFillColor(sf::Color::White);
//		productBox.setOutlineThickness(2);
//		productBox.setOutlineColor(sf::Color::Black);
//
//		sf::Text productText(films[i].title, font, 24);
//		productText.setFillColor(sf::Color::Black);
//
//		float text_X = 20.f + 377.5 * (int)(i % 4) + productBox.getSize().x / 2 - productText.getLocalBounds().width / 2;
//		float text_Y = filmListPosition1 + (int)(i / 4) * 500 + productBox.getSize().y - 25;
//		productText.setPosition(text_X, text_Y);
//
//		productBoxes.push_back({ productBox , {productText, films[i].image} });
//	}
//
//	//for (int i = 0;i < films.size(); i++) {
//	//	sf::Texture updateTexture;
//	//	if (!updateTexture.loadFromFile("button_update.png"))
//	//		return EXIT_FAILURE;
//
//	//	sf::Sprite uSprite(updateTexture);
//
//	//	sf::Texture deleteTexture;
//	//	if (!deleteTexture.loadFromFile("button_delete.png"))
//	//		return EXIT_FAILURE;
//
//	//	sf::Sprite dSprite(deleteTexture);
//
//	//	float scale_x = 163.50 / updateTexture.getSize().x;
//	//	float scale_y = 30.0 / updateTexture.getSize().y;
//	//	uSprite.setScale(scale_x, scale_y);
//	//	uSprite.setPosition(20.f + 377.5 * (int)(i % 4), filmListPosition1 + (int)(i / 4) * 500 + productBoxes[i].first.getSize().y + 5);
//	//	films[i].updateSprite = uSprite;
//
//	//	dSprite.setScale(scale_x, scale_y);
//	//	dSprite.setPosition(20.f + 377.5 * (int)(i % 4) + productBoxes[i].first.getSize().x / 2 + 0.5, filmListPosition1 + (int)(i / 4) * 500 + productBoxes[i].first.getSize().y + 5);
//	//	films[i].deleteSprite = dSprite;
//
//	//	sf::Font fontUpdate;
//	//	if (!fontUpdate.loadFromFile("SourceSansPro-Bold.ttf"))
//	//	{
//	//		std::cout << "Failed to load font!" << std::endl;
//	//		return -1;
//	//	}
//
//	//	sf::Text textUpdate;
//	//	textUpdate.setFont(fontUpdate);
//	//	textUpdate.setCharacterSize(25);
//	//	textUpdate.setFillColor(sf::Color(255, 255, 255));
//	//	textUpdate.setString("UPDATE");
//	//	float width = productBoxes[i].first.getSize().x / 2 - textUpdate.getLocalBounds().width / 2;
//	//	textUpdate.setPosition(20.f + 377.5 * (int)(i % 4) + width, filmListPosition1 + (int)(i / 4) * 500 + productBoxes[i].first.getSize().y + 7);
//
//	//	films[i].updateText = textUpdate;
//
//	//	sf::Text textDelete;
//	//	textDelete.setFont(fontUpdate);
//	//	textDelete.setCharacterSize(25);
//	//	textDelete.setFillColor(sf::Color(255, 255, 255));
//	//	textDelete.setString("DELETE");
//	//	width = productBoxes[i].first.getSize().x / 2 - textDelete.getLocalBounds().width / 2;
//	//	textDelete.setPosition(20.f + 377.5 * (int)(i % 4) + productBoxes[i].first.getSize().x / 2 + width, filmListPosition1 + (int)(i / 4) * 500 + productBoxes[i].first.getSize().y + 7);
//
//	//	films[i].deleteText = textDelete;
//	//}
//
//	//////////////////////Movie//////////////////
//
//
//
//	//////////////////////Order//////////////////
//	sf::Texture textureOrder;
//	if (!textureOrder.loadFromFile("order(1500-800).png"))
//		return EXIT_FAILURE;
//
//	// tạo sprite sử dụng texture đã tải
//	sf::Sprite spriteOrder(textureOrder);
//	float scale_x = 1500.0 / textureOrder.getSize().x;
//	float scale_y = 800.0 / textureOrder.getSize().y;
//	spriteOrder.setScale(scale_x, scale_y);
//	spriteOrder.setPosition(0, 100);
//
//	std::pair<sf::RectangleShape, bool> box[3][12][6];
//	//vector< std::pair<sf::RectangleShape, bool>> box[12][6];
//
//	double x_0 = 196, y_0 = 345;
//	double delta_x = 93.5, delta_y = 88.5;
//
//	for (int k = 0; k < 3; k++) {
//		for (int i = 0; i < 12; i++) {
//			for (int j = 0; j < 6; j++) {
//				double x = x_0 + i * delta_x, y = y_0 + j * delta_y;
//				box[k][i][j].second = false;
//				box[k][i][j].first.setSize(sf::Vector2f(76, 74.5));
//				box[k][i][j].first.setFillColor(sf::Color(238, 100, 87)); //100, 238, 87
//				box[k][i][j].first.setOutlineThickness(2);
//				box[k][i][j].first.setOutlineColor(sf::Color::Black);
//				box[k][i][j].first.setPosition(x, y);
//			}
//		}
//	}
//
//
//	//////////////////////Order//////////////////
//
//	///////////////////////////////////
//
//	//bool selectButton[3]; memset(selectButton, false, 3);
//	bool homePageButton = true;
//	bool selectDropDownButton = false;
//	bool selectAndUpdateButton = false; int indexButton = 0;
//	bool createButtonActive = false;
//
//	sf::RectangleShape movieButton(sf::Vector2f(200, 100));
//	movieButton.setFillColor(sf::Color(3, 22, 46));
//	//createButton.setOutlineThickness(2);
//	//createButton.setOutlineColor(sf::Color(205, 156, 124, 255));
//	movieButton.setPosition(600, 0);
//
//	sf::Text movieButtonText("MOVIE", font, 30);
//	movieButtonText.setFillColor(sf::Color::White);
//	movieButtonText.setPosition(655, 35);
//
//	//////////////////dropdown/////////////////////////
//
//	sf::RectangleShape dropdownBox(sf::Vector2f(200, 100));
//	dropdownBox.setFillColor(sf::Color(3, 22, 46)); //3, 19, 39, 230
//	dropdownBox.setPosition(800, 0);
//
//	sf::Text dropdownText("ROOM", font, 30);
//	dropdownText.setFillColor(sf::Color::White);
//	dropdownText.setPosition(850, 35);
//
//	std::vector< std::pair<sf::Text, sf::RectangleShape> > options;
//	sf::RectangleShape option1Box(sf::Vector2f(200, 50));
//	option1Box.setFillColor(sf::Color(3, 22, 46));
//	//option1Box.setOutlineThickness(0.5);
//	//option1Box.setOutlineColor(sf::Color::White);
//	option1Box.setPosition(800, 100);
//
//	sf::Text option1("ROOM 1", font, 30);
//	option1.setPosition(848, 105);
//	option1.setFillColor(sf::Color::White);
//	options.push_back({ {option1} , option1Box });
//
//	sf::RectangleShape option2Box(sf::Vector2f(200, 50));
//	option2Box.setFillColor(sf::Color(3, 22, 46));
//	//option2Box.setOutlineThickness(0.5);
//	//option2Box.setOutlineColor(sf::Color::White);
//	option2Box.setPosition(800, 150);
//
//	sf::Text option2("ROOM 2", font, 30);
//	option2.setPosition(848, 155);
//	option2.setFillColor(sf::Color::White);
//	options.push_back({ {option2} , option2Box });
//
//	sf::RectangleShape option3Box(sf::Vector2f(200, 50));
//	option3Box.setFillColor(sf::Color(3, 22, 46));
//	//option3Box.setOutlineThickness(0.5);
//	//option3Box.setOutlineColor(sf::Color::White);
//	option3Box.setPosition(800, 200);
//
//	sf::Text option3("ROOM 3", font, 30);
//	option3.setPosition(848, 205);
//	option3.setFillColor(sf::Color::White);
//	options.push_back({ {option3} , option3Box });
//
//	bool isDropdownActive = false;
//
//	//////////////////dropdown/////////////////////////
//
//	/////////////////create & exit////////////////////////////
//
//	sf::RectangleShape createButton(sf::Vector2f(200, 100));
//	createButton.setFillColor(sf::Color(3, 22, 46));
//	//createButton.setOutlineThickness(2);
//	//createButton.setOutlineColor(sf::Color(205, 156, 124, 255));
//	createButton.setPosition(1000, 0);
//
//	sf::Text createButtonText("CREATE", font, 30);
//	createButtonText.setFillColor(sf::Color::White);
//	createButtonText.setPosition(1045, 35);
//
//	sf::RectangleShape exitButton(sf::Vector2f(200, 100));
//	exitButton.setFillColor(sf::Color(3, 22, 46));
//	//createButton.setOutlineThickness(2);
//	//createButton.setOutlineColor(sf::Color(205, 156, 124, 255));
//	exitButton.setPosition(1200, 0);
//
//	sf::Text exitButtonText("EXIT", font, 30);
//	exitButtonText.setFillColor(sf::Color::White);
//	exitButtonText.setPosition(1263, 35);
//
//	/////////////////create & exit////////////////////////////
//
//	//float position = 50.0f;
//	//int first = 0, last = films.size() - 1;
//	//std::thread thread(updateFilmPosition, std::ref(position), std::ref(first), std::ref(last));
//
//	//int cnt = 0;
//
//	// Thiết lập vị trí ban đầu của danh sách bộ phim
//
//	float delta = 25.f;
//
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//			//thread.detach();
//			if (homePageButton) {
//				// Xử lý sự kiện cuộn danh sách bộ phim
//	//			if (event.type == sf::Event::MouseWheelScrolled)
//	//			{
//	//				// lăn xuống(-) lăn lên(+)
//	//				//filmListPosition1 -= event.mouseWheelScroll.delta * 10.f;
//
//	//				//if (event.mouseWheelScroll.delta > 0) {
//	//				//	if (filmListPosition1 < 120.f) {
//	//				//		filmListPosition1 += event.mouseWheelScroll.delta * 10.f;
//	//				//	}
//	//				//}
//	//				//else if (event.mouseWheelScroll.delta < 0) {
//	//				//	if (filmList7.getPosition().y >= 380) {
//	//				//		filmListPosition1 += event.mouseWheelScroll.delta * 10.f;
//	//				//	}
//	//				//}
//	//				if (films.size() > 0) {
//	//					if (event.mouseWheelScroll.delta > 0) {
//	//						if (filmListPosition1 < 120.f) {
//	//							filmListPosition1 += event.mouseWheelScroll.delta * 20.f;
//	//						}
//	//					}
//	//					else if (event.mouseWheelScroll.delta < 0) {
//	//						if (productBoxes[films.size() - 1].first.getPosition().y >= 380) {
//	//							filmListPosition1 += event.mouseWheelScroll.delta * 20.f;
//	//						}
//	//					}
//	//				}
//
//	//				for (int i = 0; i < films.size(); i++)
//	//				{
//	//					productBoxes[i].first.setPosition(20.f + 377.5 * (int)(i % 4), filmListPosition1 + (int)(i / 4) * 500);
//	//					float text_X = 20.f + 377.5 * (int)(i % 4) + productBoxes[i].first.getSize().x / 2 - productBoxes[i].second.first.getLocalBounds().width / 2;
//	//					float text_Y = filmListPosition1 + (int)(i / 4) * 500 + productBoxes[i].first.getSize().y - 25;
//	//					productBoxes[i].second.first.setPosition(text_X, text_Y);
//	//				}
//				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
//					if (productBoxes[films.size() - 1].first.getPosition().y >= 380) {
//						filmListPosition1 += -delta;
//						for (int i = 0; i < films.size(); i++)
//						{
//							productBoxes[i].first.move(0, -delta);
//							productBoxes[i].second.first.move(0, -delta);
//						}
//					}
//				}
//				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
//					if (filmListPosition1 < 120.f) {
//						filmListPosition1 += delta;
//						for (int i = 0; i < films.size(); i++)
//						{
//							productBoxes[i].first.move(0, delta);
//							productBoxes[i].second.first.move(0, delta);
//						}
//					}
//				}
//				if (event.type == sf::Event::MouseMoved)
//				{
//					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
//					if (movieButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
//					{
//						movieButtonText.setFillColor(sf::Color(255, 84, 0));
//					}
//					else {
//						movieButtonText.setFillColor(sf::Color::White);
//					}
//					//if (dropdownBox.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
//					//	dropdownText.setFillColor(sf::Color(255, 84, 0));
//					//}
//					//else {
//					//	dropdownText.setFillColor(sf::Color::White);
//					//}
//					if (dropdownBox.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
//					{
//						dropdownText.setFillColor(sf::Color(255, 84, 0));
//						//isDropdownActive = !isDropdownActive;
//						isDropdownActive = true;
//					}
//					else if (isDropdownActive)
//					{
//						bool check = true;
//						for (int i = 0; i < 3; i++) {
//							{
//								//option.first.second = false;
//								if (options[i].second.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
//								{
//									options[i].first.setFillColor(sf::Color(255, 84, 0));
//									//homePageButton = false;  selectDropDownButton = true; selectAndUpdateButton = true;
//									//break;
//									check = false;
//								}
//								else {
//									options[i].first.setFillColor(sf::Color::White);
//									//isDropdownActive = false;
//								}
//							}
//						}
//						if (check) {
//							isDropdownActive = false;
//							dropdownText.setFillColor(sf::Color::White);
//						}
//					}
//					//else if (isDropdownActive)
//					//{
//					//	for (int i = 0; i < 3; i++) {
//					//		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
//					//		{
//					//			if (isMouseOver(options[i].second, window))
//					//			{
//					//				dropdownText.setString(options[i].first.getString());
//					//				indexButton = i + 1;
//					//				dropdownText.setFillColor(sf::Color::White);
//					//				isDropdownActive = false;
//					//				//isArrowDownUp = true;
//					//				homePageButton = false;  selectDropDownButton = true; selectAndUpdateButton = true;
//					//				break;
//					//			}
//					//		}
//					//	}
//					//}
//					if (createButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
//					{
//						createButtonText.setFillColor(sf::Color(255, 84, 0));
//					}
//					else {
//						createButtonText.setFillColor(sf::Color::White);
//					}
//					if (exitButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
//					{
//						exitButtonText.setFillColor(sf::Color(255, 84, 0));
//					}
//					else {
//						exitButtonText.setFillColor(sf::Color::White);
//					}
//				}
//				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
//				{
//					//if (isMouseOver(dropdownBox, window))
//					//{
//					//	dropdownBox.setFillColor(sf::Color(111, 110, 111));
//					//	isDropdownActive = !isDropdownActive;
//					//}
//					//else if (isDropdownActive)
//					//{
//					//	for (int i = 0; i < 3; i++) {
//					//		{
//					//			//option.first.second = false;
//					//			if (isMouseOver(options[i].second, window))
//					//			{
//					//				dropdownText.setString(options[i].first.getString());
//					//				indexButton = i + 1;
//					//				dropdownBox.setFillColor(sf::Color::White);
//					//				isDropdownActive = false;
//					//				//isArrowDownUp = true;
//					//				homePageButton = false;  selectDropDownButton = true; selectAndUpdateButton = true;
//					//				break;
//					//			}
//					//		}
//					//	}
//
//					//}
//					if (isDropdownActive)
//					{
//						for (int i = 0; i < 3; i++) {
//							{
//								//option.first.second = false;
//								if (isMouseOver(options[i].second, window))
//								{
//									dropdownText.setString(options[i].first.getString());
//									indexButton = i + 1;
//									dropdownText.setFillColor(sf::Color::White);
//									isDropdownActive = false;
//									//isArrowDownUp = true;
//									homePageButton = false;  selectDropDownButton = true; selectAndUpdateButton = true;
//									break;
//								}
//							}
//						}
//
//					}
//					else if (createButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
//					{
//						createFilmsWindow(window, window1, font, filmListPosition1);
//					}
//					else {
//						for (int i = 0; i < productBoxes.size(); i++)
//						{
//							if (productBoxes[i].first.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
//								//cout << films[i].title << " " << films[i].desc << " " << films[i].image << endl;
//								updateFilmsWindow(window, window2, font, i, filmListPosition1);
//							}
//						}
//					}
//				}
//			}
//			else if (selectAndUpdateButton) {
//				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
//				{
//					if (movieButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
//					{
//						homePageButton = true;
//						selectDropDownButton = false;
//						dropdownText.setString("ROOM");
//						selectAndUpdateButton = false;
//						indexButton = 0;
//					}
//					//if (isMouseOver(dropdownBox, window))
//					//{
//					//	dropdownText.setFillColor(sf::Color(255, 84, 0));
//					//	//isDropdownActive = !isDropdownActive;
//					//	isDropdownActive = true;
//					//}
//					//else if (isDropdownActive)
//					//{
//					//	for (int i = 0; i < 3; i++) {
//					//		//option.first.second = false;
//					//		if (isMouseOver(options[i].second, window))
//					//		{
//					//			dropdownText.setString(options[i].first.getString());
//					//			indexButton = i + 1;
//					//			dropdownBox.setFillColor(sf::Color::White);
//					//			isDropdownActive = false;
//					//			//isArrowDownUp = true;
//					//			homePageButton = false;  selectDropDownButton = true; selectAndUpdateButton = true;
//					//			break;
//					//		}
//					//	}
//					//}
//					if (isDropdownActive)
//					{
//						for (int i = 0; i < 3; i++) {
//							//option.first.second = false;
//							if (isMouseOver(options[i].second, window))
//							{
//								dropdownText.setString(options[i].first.getString());
//								indexButton = i + 1;
//								dropdownText.setFillColor(sf::Color::White);
//								isDropdownActive = false;
//								//isArrowDownUp = true;
//								homePageButton = false;  selectDropDownButton = true; selectAndUpdateButton = true;
//								break;
//							}
//						}
//
//					}
//
//					if (selectAndUpdateButton) {
//						if (indexButton) {
//							for (int i = 0; i < 12; i++) {
//								for (int j = 0; j < 6; j++) {
//									if (box[indexButton - 1][i][j].first.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
//										if (box[indexButton - 1][i][j].second) {
//											box[indexButton - 1][i][j].second = false;
//											box[indexButton - 1][i][j].first.setFillColor(sf::Color(238, 100, 87)); //100, 238, 87
//
//										}
//										else {
//											box[indexButton - 1][i][j].second = true;
//											box[indexButton - 1][i][j].first.setFillColor(sf::Color(100, 238, 87)); //100, 238, 87
//										}
//									}
//								}
//							}
//						}
//					}
//					if (createButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
//					{
//						createFilmsWindow(window, window1, font, filmListPosition1);
//					}
//				}
//				if (event.type == sf::Event::MouseMoved)
//				{
//					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
//					if (movieButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
//					{
//						movieButtonText.setFillColor(sf::Color(255, 84, 0));
//					}
//					else {
//						movieButtonText.setFillColor(sf::Color::White);
//					}
//					//if (dropdownBox.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
//					//	dropdownText.setFillColor(sf::Color(255, 84, 0));
//					//}
//					//else {
//					//	dropdownText.setFillColor(sf::Color::White);
//					//}
//					if (dropdownBox.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
//					{
//						dropdownText.setFillColor(sf::Color(255, 84, 0));
//						//isDropdownActive = !isDropdownActive;
//						isDropdownActive = true;
//					}
//					else if (isDropdownActive)
//					{
//						bool check = true;
//						for (int i = 0; i < 3; i++) {
//							{
//								//option.first.second = false;
//								if (options[i].second.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
//								{
//									options[i].first.setFillColor(sf::Color(255, 84, 0));
//									//homePageButton = false;  selectDropDownButton = true; selectAndUpdateButton = true;
//									//break;
//									check = false;
//								}
//								else {
//									options[i].first.setFillColor(sf::Color::White);
//								}
//							}
//						}
//						if (check) {
//							isDropdownActive = false;
//							dropdownText.setFillColor(sf::Color::White);
//						}
//					}
//					//else if (isDropdownActive)
//					//{
//					//	for (int i = 0; i < 3; i++) {
//					//		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
//					//		{
//					//			if (isMouseOver(options[i].second, window))
//					//			{
//					//				dropdownText.setString(options[i].first.getString());
//					//				indexButton = i + 1;
//					//				dropdownText.setFillColor(sf::Color::White);
//					//				isDropdownActive = false;
//					//				//isArrowDownUp = true;
//					//				homePageButton = false;  selectDropDownButton = true; selectAndUpdateButton = true;
//					//				break;
//					//			}
//					//		}
//					//	}
//					//}
//					if (createButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
//					{
//						createButtonText.setFillColor(sf::Color(255, 84, 0));
//					}
//					else {
//						createButtonText.setFillColor(sf::Color::White);
//					}
//					if (exitButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
//					{
//						exitButtonText.setFillColor(sf::Color(255, 84, 0));
//					}
//					else {
//						exitButtonText.setFillColor(sf::Color::White);
//					}
//				}
//
//			}
//		}
//
//		window.clear(sf::Color::White);
//
//		window.draw(sprite);
//
//		if (homePageButton) {
//			for (int i = 0; i < films.size(); i++)
//			{
//				sf::Texture texture;
//				if (!texture.loadFromFile(productBoxes[i].second.second)) {
//					texture.loadFromFile("404.jfif");
//				}
//				sf::Sprite sprite(texture);
//				float scalex = 317.5 / texture.getSize().x;
//				float scaley = 445.0 / texture.getSize().y;
//				sprite.setScale(scalex, scaley);
//				float x = 20.f + 377.5 * (int)(i % 4) + 5;
//				float y = filmListPosition1 + (int)(i / 4) * 500 + 5;
//				sprite.setPosition(x, y);
//				window.draw(productBoxes[i].first);
//				window.draw(sprite);
//				window.draw(productBoxes[i].second.first);
//				//window.draw(films[i].updateSprite);
//				//window.draw(films[i].deleteSprite);
//				//window.draw(films[i].updateText);
//				//window.draw(films[i].deleteText);
//				//productBox.setPosition(20.f + 377.5 * (int)(i % 4), filmListPosition1 + (int)(i / 4) * 500);
//			}
//			//productBoxes[first].first.setPosition(position, 125);
//			//float text_X = position + productBoxes[first].first.getSize().x / 2 - productBoxes[first].second.first.getLocalBounds().width / 2;
//			//productBoxes[first].second.first.setPosition(text_X, 600);
//			//sf::Texture texture;
//			//if (!texture.loadFromFile(productBoxes[first].second.second)) {
//			//	texture.loadFromFile("404.jfif");
//			//}
//			//sf::Sprite sprite(texture);
//			//float scalex = 290.0 / texture.getSize().x;
//			//float scaley = 475.0 / texture.getSize().y;
//			//sprite.setScale(scalex, scaley);
//			//float x = position + 5;
//			//float y = productBoxes[first].first.getPosition().y + 5;
//			//sprite.setPosition(x, y);
//			//window.draw(productBoxes[first].first);
//			//window.draw(sprite);
//			//window.draw(productBoxes[first].second.first);
//
//			//int cnt = 0; // co the error
//			//for (int i = first + 1; i < films.size(); i++) {
//			//	float pos = position + ++cnt * 350;
//			//	productBoxes[i].first.setPosition(pos, 125);
//			//	float text_X = pos + productBoxes[i].first.getSize().x / 2 - productBoxes[i].second.first.getLocalBounds().width / 2;
//			//	productBoxes[i].second.first.setPosition(text_X, 600);
//			//	sf::Texture texture;
//			//	if (!texture.loadFromFile(productBoxes[i].second.second)) {
//			//		texture.loadFromFile("404.jfif");
//			//	}
//			//	sf::Sprite sprite(texture);
//			//	float scalex = 290.0 / texture.getSize().x;
//			//	float scaley = 475.0 / texture.getSize().y;
//			//	sprite.setScale(scalex, scaley);
//			//	float x = pos + 5;
//			//	float y = productBoxes[i].first.getPosition().y + 5;
//			//	sprite.setPosition(x, y);
//			//	window.draw(productBoxes[i].first);
//			//	window.draw(sprite);
//			//	window.draw(productBoxes[i].second.first);
//			//}
//
//			//for (int i = 0; i < first; i++) {
//			//	float pos = position + ++cnt * 350;
//			//	productBoxes[i].first.setPosition(pos, 125);
//			//	float text_X = pos + productBoxes[i].first.getSize().x / 2 - productBoxes[i].second.first.getLocalBounds().width / 2;
//			//	productBoxes[i].second.first.setPosition(text_X, 600);
//			//	sf::Texture texture;
//			//	if (!texture.loadFromFile(productBoxes[i].second.second)) {
//			//		texture.loadFromFile("404.jfif");
//			//	}
//			//	sf::Sprite sprite(texture);
//			//	float scalex = 290.0 / texture.getSize().x;
//			//	float scaley = 475.0 / texture.getSize().y;
//			//	sprite.setScale(scalex, scaley);
//			//	float x = pos + 5;
//			//	float y = productBoxes[i].first.getPosition().y + 5;
//			//	sprite.setPosition(x, y);
//			//	window.draw(productBoxes[i].first);
//			//	window.draw(sprite);
//			//	window.draw(productBoxes[i].second.first);
//			//}
//		}
//
//		window.draw(headerBox);
//		window.draw(movieButton);
//		window.draw(movieButtonText);
//		window.draw(createButton);
//		window.draw(createButtonText);
//		window.draw(exitButton);
//		window.draw(exitButtonText);
//
//		//if (homePageAdmin) {
//
//		//}
//
//		if (selectDropDownButton) {
//			window.draw(spriteOrder);
//		}
//
//		if (selectAndUpdateButton) {
//			if (indexButton) {
//				for (int i = 0; i < 12; i++) {
//					for (int j = 0; j < 6; j++) {
//						window.draw(box[indexButton - 1][i][j].first);
//					}
//				}
//			}
//		}
//
//		window.draw(dropdownBox);
//		window.draw(dropdownText);
//		//if (isArrowDownUp) {
//		//	arrow.setPoint(0, sf::Vector2f(0, 0));
//		//	arrow.setPoint(1, sf::Vector2f(15, 0));
//		//	arrow.setPoint(2, sf::Vector2f(7.5, 7.5));
//		//	arrow.setFillColor(sf::Color::Black);
//		//	window.draw(arrow);
//		//}
//
//		if (isDropdownActive)
//		{
//			//isArrowDownUp = false;
//			//arrow.setPoint(0, sf::Vector2f(7.5, 0));
//			//arrow.setPoint(1, sf::Vector2f(0, 7.5));
//			//arrow.setPoint(2, sf::Vector2f(15, 7.5));
//			//arrow.setFillColor(sf::Color::Black);
//			//window.draw(arrow);
//
//			for (const std::pair<sf::Text, sf::RectangleShape> option : options)
//			{
//				window.draw(option.second);
//				window.draw(option.first);
//			}
//		}
//
//
//		// Vẽ danh sách bộ phim
//		//for (int i = 0; i < films.size(); i++)
//		//{
//		//    sf::Text filmText(films[i].title + " (" + films[i].director + ", " + to_string(films[i].year) + ")", font, 20);
//		//    filmText.setPosition(filmList.getPosition().x + 10.f, filmList.getPosition().y + filmListPosition + i * 30.f);
//		//    window.draw(filmText);
//		//}
//
//		window.display();
//	}
//
//	return 0;
//}

//int main() {
//	sf::RenderWindow window(sf::VideoMode(900, 900), "Login Admin");
//
//	sf::Texture texture;
//	if (!texture.loadFromFile("admin-login.jpg"))
//		return EXIT_FAILURE;
//
//	// tạo sprite sử dụng texture đã tải
//	sf::Sprite sprite(texture);
//	float scalex = 900.0 / texture.getSize().x;
//	float scaley = 900.0 / texture.getSize().y;
//	sprite.setScale(scalex, scaley);
//
//	sf::Font font;
//	if (!font.loadFromFile("SVN-Times New Roman Bold.ttf"))
//	{
//		std::cout << "Failed to load font!" << std::endl;
//		return -1;
//	}
//
//	sf::RectangleShape buttonUserName(sf::Vector2f(600, 55));
//	buttonUserName.setFillColor(sf::Color(3, 36, 86, 180));
//	buttonUserName.setPosition(160, 250);
//
//	sf::RectangleShape lineUserName(sf::Vector2f(10, 55));
//	lineUserName.setFillColor(sf::Color(18, 104, 10));
//	lineUserName.setPosition(160, 250);
//
//	sf::Text inputTextUserName;
//	inputTextUserName.setFont(font);
//	inputTextUserName.setCharacterSize(29);
//	inputTextUserName.setFillColor(sf::Color(255, 255, 255));
//	inputTextUserName.setPosition(173, 256);
//
//	//sf::RectangleShape buttonDesc(sf::Vector2f(600, 500));
//	//buttonDesc.setFillColor(sf::Color(86, 0, 172, 70));
//	//buttonDesc.setPosition(200, 200);
//
//	//sf::RectangleShape lineDesc(sf::Vector2f(5, 500));
//	//lineDesc.setFillColor(sf::Color(18, 104, 10));
//	//lineDesc.setPosition(200, 200);
//
//	//sf::Text inputTextDesc;
//	//inputTextDesc.setFont(font);
//	//inputTextDesc.setCharacterSize(27);
//	//inputTextDesc.setFillColor(sf::Color(255, 255, 255));
//	//inputTextDesc.setPosition(210, 196);
//
//	sf::RectangleShape buttonPassword(sf::Vector2f(600, 55));
//	buttonPassword.setFillColor(sf::Color(3, 36, 86, 180));
//	buttonPassword.setPosition(160, 450);
//
//	sf::RectangleShape linePassword(sf::Vector2f(10, 55));
//	linePassword.setFillColor(sf::Color(18, 104, 10));
//	linePassword.setPosition(160, 450);
//
//	sf::Text inputTextPassword;
//	inputTextPassword.setFont(font);
//	inputTextPassword.setCharacterSize(29);
//	inputTextPassword.setFillColor(sf::Color(255, 255, 255));
//	inputTextPassword.setPosition(173, 456);
//
//	sf::Texture continueTexture;
//	if (!continueTexture.loadFromFile("button-continue.png"))
//		return EXIT_FAILURE;
//
//	sf::Sprite continueSprite(continueTexture);
//	float scalex1 = 300.0 / continueTexture.getSize().x;
//	float scaley1 = 75.0 / continueTexture.getSize().y;
//	continueSprite.setScale(scalex1, scaley1);
//	continueSprite.setPosition(163, 650);
//
//	sf::Texture backTexture;
//	if (!backTexture.loadFromFile("button-back.png"))
//		return EXIT_FAILURE;
//
//	sf::Sprite backSprite(backTexture);
//	scalex1 = 300.0 / backTexture.getSize().x;
//	scaley1 = 79.0 / backTexture.getSize().y;
//	backSprite.setScale(scalex1, scaley1);
//	backSprite.setPosition(456, 650);
//
//
//	//sf::Font fontCreate;
//	//if (!fontCreate.loadFromFile("SourceSansPro-Bold.ttf"))
//	//{
//	//	std::cout << "Failed to load font!" << std::endl;
//	//	return -1;
//	//}
//
//	//sf::Text textCreate;
//	//textCreate.setFont(fontCreate);
//	//textCreate.setCharacterSize(37);
//	//textCreate.setFillColor(sf::Color(255, 255, 255));
//	//textCreate.setPosition(432, 883);
//	//textCreate.setString("CREATE");
//
//	string textDesc = "";
//
//	bool isInputTitleActive = false;
//	bool isInputDescActive = false;
//	bool isInputImageActive = false;
//
//	bool checkwindow1 = false;
//
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			//if (event.type == sf::Event::Closed)
//			//{
//			//	window1.close();
//			//}
//			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
//			{
//				if (isMouseOver(buttonUserName, event))
//				{
//					lineUserName.setFillColor(sf::Color(128, 241, 118));
//					//lineDesc.setFillColor(sf::Color(18, 104, 10));
//					linePassword.setFillColor(sf::Color(18, 104, 10));
//					isInputTitleActive = true;
//					//isInputDescActive = false;
//					isInputImageActive = false;
//				}
//				//else if (isMouseOver(buttonDesc, event))
//				//{
//				//	lineDesc.setFillColor(sf::Color(128, 241, 118));
//				//	lineUserName.setFillColor(sf::Color(18, 104, 10));
//				//	linePassword.setFillColor(sf::Color(18, 104, 10));
//				//	isInputDescActive = true;
//				//	isInputTitleActive = false;
//				//	isInputImageActive = false;
//				//}
//				else if (isMouseOver(buttonPassword, event)) {
//					linePassword.setFillColor(sf::Color(128, 241, 118));
//					//lineDesc.setFillColor(sf::Color(18, 104, 10));
//					lineUserName.setFillColor(sf::Color(18, 104, 10));
//					//isInputDescActive = false;
//					isInputTitleActive = false;
//					isInputImageActive = true;
//				}
//				else {
//					//lineDesc.setFillColor(sf::Color(18, 104, 10));
//					lineUserName.setFillColor(sf::Color(18, 104, 10));
//					linePassword.setFillColor(sf::Color(18, 104, 10));
//					isInputDescActive = false;
//					isInputTitleActive = false;
//					isInputImageActive = false;
//				}
//
//				if (continueSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
//					string currentTextUserName = inputTextUserName.getString();
//					string currentTextPassword = inputTextPassword.getString();
//					if (currentTextUserName == "" || currentTextPassword == "") {
//						if(currentTextUserName == "")
//							lineUserName.setFillColor(sf::Color(255, 0, 0));
//						if (currentTextPassword == "")
//							linePassword.setFillColor(sf::Color(255, 0, 0));
//					}
//					else if (currentTextUserName != "admin" || currentTextPassword != "password") {
//						if (currentTextUserName != "admin") {
//							lineUserName.setFillColor(sf::Color(255, 0, 0));
//						}
//						if (currentTextPassword != "password") {
//							linePassword.setFillColor(sf::Color(255, 0, 0));
//						}
//					}
//					else if (currentTextUserName == "admin" && currentTextPassword == "password") {
//						window.close();
//						return 0;
//					}
//				}
//
//				if (backSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
//					window.close();
//					return 0;
//				}
//			}
//			else if (event.type == sf::Event::TextEntered)
//			{
//				if (isInputTitleActive)
//				{
//					if (event.text.unicode < 128)
//					{
//						if (event.text.unicode == '\b')
//						{
//							if (!inputTextUserName.getString().isEmpty()) {
//								std::string currentText = inputTextUserName.getString();
//								currentText.pop_back();
//								inputTextUserName.setString(currentText);
//							}
//						}
//						else
//						{
//							float textWidth = inputTextUserName.getLocalBounds().width;
//							float buttonWidth = buttonUserName.getLocalBounds().width;
//							if (buttonWidth > textWidth + 20)
//								inputTextUserName.setString(inputTextUserName.getString() + static_cast<char>(event.text.unicode));
//						}
//					}
//				}
//				//else if (isInputDescActive)
//				//{
//				//	if (event.text.unicode < 128)
//				//	{
//				//		if (event.text.unicode == '\b')
//				//		{
//				//			if (!inputTextDesc.getString().isEmpty()) {
//				//				std::string currentText = inputTextDesc.getString();
//				//				currentText.pop_back();
//				//				textDesc.pop_back();
//				//				inputTextDesc.setString(currentText);
//				//			}
//				//		}
//				//		else if (event.text.unicode == '\r' || event.text.unicode == '\n')
//				//		{
//				//			inputTextDesc.setString(inputTextDesc.getString() + "\n");
//				//			textDesc += "\n";
//				//		}
//				//		else
//				//		{
//				//			string lastString;
//				//			stringstream ss(inputTextDesc.getString());
//				//			while (getline(ss, lastString, '\n')) {
//				//			}
//
//				//			sf::Text tempText;
//				//			tempText.setFont(font);
//				//			tempText.setCharacterSize(27);
//				//			tempText.setString(lastString);
//				//			float lineDescWidth = tempText.getLocalBounds().width;
//				//			float buttonDescWidth = buttonDesc.getLocalBounds().width;
//				//			if (lineDescWidth > buttonDescWidth - 20)
//				//			{
//				//				// Thêm ký tự xuống dòng
//				//				inputTextDesc.setString(inputTextDesc.getString() + "\n");
//				//			}
//				//			inputTextDesc.setString(inputTextDesc.getString() + static_cast<char>(event.text.unicode));
//				//			textDesc += static_cast<char>(event.text.unicode);
//				//		}
//
//				//	}
//				//}
//				else if (isInputImageActive)
//				{
//					if (event.text.unicode < 128)
//					{
//						if (event.text.unicode == '\b')
//						{
//							if (!inputTextPassword.getString().isEmpty()) {
//								std::string currentText = inputTextPassword.getString();
//								currentText.pop_back();
//								inputTextPassword.setString(currentText);
//							}
//						}
//						else
//						{
//							float textWidth = inputTextPassword.getLocalBounds().width;
//							float buttonWidth = buttonPassword.getLocalBounds().width;
//							if (buttonWidth > textWidth + 20)
//								inputTextPassword.setString(inputTextPassword.getString() + static_cast<char>(event.text.unicode));
//						}
//					}
//				}
//			}
//			//if (event.type == sf::Event::MouseMoved)
//			//{
//			//	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
//			//	if (createSprite.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
//			//	{
//			//		if (!createTexture.loadFromFile("2023-11-13_173035.png"))
//			//			return EXIT_FAILURE;
//			//		float scalex1 = 300.0 / createTexture.getSize().x;
//			//		float scaley1 = 75.0 / createTexture.getSize().y;
//			//		createSprite.setScale(scalex1, scaley1);
//			//	}
//			//	else
//			//	{
//			//		if (!createTexture.loadFromFile("2023-11-13_171327.png"))
//			//			return EXIT_FAILURE;
//			//		float scalex1 = 300.0 / createTexture.getSize().x;
//			//		float scaley1 = 75.0 / createTexture.getSize().y;
//			//		createSprite.setScale(scalex1, scaley1);
//			//	}
//			//}
//		}
//
//		window.clear();
//		window.draw(sprite);
//
//		window.draw(buttonUserName);
//		window.draw(inputTextUserName);
//		window.draw(lineUserName);
//
//		//window.draw(buttonDesc);
//		//window.draw(inputTextDesc);
//		//window.draw(lineDesc);
//
//		window.draw(buttonPassword);
//		window.draw(inputTextPassword);
//		window.draw(linePassword);
//
//		window.draw(continueSprite);
//		window.draw(backSprite);
//		//window.draw(textCreate);
//
//		window.display();
//	}
//}