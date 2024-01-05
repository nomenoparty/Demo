#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>
#include <thread>
#include<sstream>
#include <regex>
#include <SFML/Network.hpp>
#include<fstream>
#include "./header/admin.h"
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

//struct film {
//	string title;
//	string desc;
//	string image;
//};

struct film {
	string title; //tên phim
	string chu_de;
	string hour;
	string minute;
	string day;
	string month;
	string year;
	string so_luong; // thời lượng phim
	string desc; // mô tả
	string image; // link ảnh
};

std::vector<film> films;
std::vector<pair<sf::RectangleShape, pair<sf::Text, string>>> productBoxes;
std::vector<pair<sf::RectangleShape, string>> autoproductBoxes;
std::vector<pair<sf::RectangleShape, pair<sf::Text, string>>> adminproductBoxes;
//std::vector<pair<sf::RectangleShape, pair<sf::Text, sf::Sprite>>> productBoxes;
//std::pair<sf::RectangleShape, bool> box[3][7][11];
bool box[3][7][11];

const int rows1 = 11;
const int cols1 = 11;
const int squareSize = 75;

int first, last;
float position;

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
			position = -150;
			first = last;
			if (first == 0) last = films.size() - 1;
			else last--;
		}

		// Tạm dừng luồng trong 16ms (tương đương với 60 khung hình/giây)
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
}

void readFromFile() {
	std::ifstream inputFile("DanhSachPhim.txt");
	if (inputFile.is_open()) {
		string line;
		int cnt = 0;
		film x;
		while (getline(inputFile, line)) {
			switch (cnt % 10)
			{
			case 0:
				x.title = line;
				break;
			case 1:
				x.chu_de = line;
				break;
			case 2:
				x.hour = line;
				break;
			case 3:
				x.minute = line;
				break;
			case 4:
				x.day = line;
				break;
			case 5:
				x.month = line;
				break;
			case 6:
				x.year = line;
				break;
			case 7:
				x.so_luong = line;
				break;
			case 8:
				x.desc = line;
				break;
			case 9:
				x.image = line;
				films.push_back(x);
				break;
			default:
				break;
			}
			++cnt;
		}
	}
	else {
		cout << "Cannot open file";
	}
	inputFile.close();
}

void writeToFile() {
	ofstream fileOut;
	fileOut.open("DanhSachPhim.txt");
	for (int i = 0; i < films.size(); i++) {
		fileOut << films[i].title << "\n" << films[i].chu_de << "\n" << films[i].hour << "\n" << films[i].minute << "\n" << films[i].day << "\n" << films[i].month << "\n" << films[i].year << "\n" << films[i].so_luong << "\n" << films[i].desc << "\n" << films[i].image << "\n";
	}
	fileOut.close();
}

int stringTointeger(string str)
{
	int temp = 0;
	for (int i = 0; i < str.length(); i++) {

		// Since ASCII value of character from '0'
		// to '9' are contiguous. So if we subtract
		// '0' from ASCII value of a digit, we get 
		// the integer value of the digit.
		temp = temp * 10 + (str[i] - '0');
	}
	return temp;
}

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

	sf::Text nameTitle;
	nameTitle.setFont(font);
	nameTitle.setCharacterSize(25);
	nameTitle.setFillColor(sf::Color(255, 130, 4));
	nameTitle.setPosition(145, 18);
	nameTitle.setString("Title");

	sf::RectangleShape buttonTitle(sf::Vector2f(600, 45));
	buttonTitle.setFillColor(sf::Color(86, 0, 172, 70));
	buttonTitle.setPosition(200, 15);

	sf::RectangleShape lineTitle(sf::Vector2f(5, 45));
	lineTitle.setFillColor(sf::Color(18, 104, 10));
	lineTitle.setPosition(200, 15);

	sf::Text inputTextTitle;
	inputTextTitle.setFont(font);
	inputTextTitle.setCharacterSize(27);
	inputTextTitle.setFillColor(sf::Color(255, 255, 255));
	inputTextTitle.setPosition(210, 18);

	sf::Text nameType;
	nameType.setFont(font);
	nameType.setCharacterSize(25);
	nameType.setFillColor(sf::Color(255, 130, 4));
	nameType.setPosition(138, 83);
	nameType.setString("Type");

	sf::RectangleShape buttonType(sf::Vector2f(600, 45));
	buttonType.setFillColor(sf::Color(86, 0, 172, 70));
	buttonType.setPosition(200, 80);

	sf::RectangleShape lineType(sf::Vector2f(5, 45));
	lineType.setFillColor(sf::Color(18, 104, 10));
	lineType.setPosition(200, 80);

	sf::Text inputTextType;
	inputTextType.setFont(font);
	inputTextType.setCharacterSize(27);
	inputTextType.setFillColor(sf::Color(255, 255, 255));
	inputTextType.setPosition(210, 83);

	sf::Text nameDesc;
	nameDesc.setFont(font);
	nameDesc.setCharacterSize(25);
	nameDesc.setFillColor(sf::Color(255, 130, 4));
	nameDesc.setPosition(67, 145);
	nameDesc.setString("Description");

	sf::RectangleShape buttonDesc(sf::Vector2f(600, 500));
	buttonDesc.setFillColor(sf::Color(86, 0, 172, 70));
	buttonDesc.setPosition(200, 145);

	sf::RectangleShape lineDesc(sf::Vector2f(5, 500));
	lineDesc.setFillColor(sf::Color(18, 104, 10));
	lineDesc.setPosition(200, 145);

	sf::Text inputTextDesc;
	inputTextDesc.setFont(font);
	inputTextDesc.setCharacterSize(27);
	inputTextDesc.setFillColor(sf::Color(255, 255, 255));
	inputTextDesc.setPosition(210, 141);

	sf::Text nameImage;
	nameImage.setFont(font);
	nameImage.setCharacterSize(25);
	nameImage.setFillColor(sf::Color(255, 130, 4));
	nameImage.setPosition(122, 668);
	nameImage.setString("Image");

	sf::RectangleShape buttonImage(sf::Vector2f(600, 45));
	buttonImage.setFillColor(sf::Color(86, 0, 172, 70));
	buttonImage.setPosition(200, 665);

	sf::RectangleShape lineImage(sf::Vector2f(5, 45));
	lineImage.setFillColor(sf::Color(18, 104, 10));
	lineImage.setPosition(200, 665);

	sf::Text inputTextImage;
	inputTextImage.setFont(font);
	inputTextImage.setCharacterSize(27);
	inputTextImage.setFillColor(sf::Color(255, 255, 255));
	inputTextImage.setPosition(210, 668);

	sf::Text nameTime;
	nameTime.setFont(font);
	nameTime.setCharacterSize(25);
	nameTime.setFillColor(sf::Color(255, 130, 4));
	nameTime.setPosition(40, 733);
	nameTime.setString("DD-MM-YYYY");

	sf::RectangleShape buttonDay(sf::Vector2f(50, 45));
	buttonDay.setFillColor(sf::Color(86, 0, 172, 70));
	buttonDay.setPosition(200, 730);

	sf::RectangleShape lineDay(sf::Vector2f(5, 45));
	lineDay.setFillColor(sf::Color(18, 104, 10));
	lineDay.setPosition(200, 730);

	sf::Text inputTextDay;
	inputTextDay.setFont(font);
	inputTextDay.setCharacterSize(27);
	inputTextDay.setFillColor(sf::Color(255, 255, 255));
	inputTextDay.setPosition(210, 733);

	sf::RectangleShape buttonMonth(sf::Vector2f(50, 45));
	buttonMonth.setFillColor(sf::Color(86, 0, 172, 70));
	buttonMonth.setPosition(280, 730);

	sf::RectangleShape lineMonth(sf::Vector2f(5, 45));
	lineMonth.setFillColor(sf::Color(18, 104, 10));
	lineMonth.setPosition(280, 730);

	sf::Text inputTextMonth;
	inputTextMonth.setFont(font);
	inputTextMonth.setCharacterSize(27);
	inputTextMonth.setFillColor(sf::Color(255, 255, 255));
	inputTextMonth.setPosition(290, 733);

	sf::RectangleShape buttonYear(sf::Vector2f(100, 45));
	buttonYear.setFillColor(sf::Color(86, 0, 172, 70));
	buttonYear.setPosition(360, 730);

	sf::RectangleShape lineYear(sf::Vector2f(5, 45));
	lineYear.setFillColor(sf::Color(18, 104, 10));
	lineYear.setPosition(360, 730);

	sf::Text inputTextYear;
	inputTextYear.setFont(font);
	inputTextYear.setCharacterSize(27);
	inputTextYear.setFillColor(sf::Color(255, 255, 255));
	inputTextYear.setPosition(370, 733);

	sf::Text nameHour;
	nameHour.setFont(font);
	nameHour.setCharacterSize(25);
	nameHour.setFillColor(sf::Color(255, 130, 4));
	nameHour.setPosition(530, 733);
	nameHour.setString("HH-MM");

	sf::RectangleShape buttonHour(sf::Vector2f(50, 45));
	buttonHour.setFillColor(sf::Color(86, 0, 172, 70));
	buttonHour.setPosition(660, 730);

	sf::RectangleShape lineHour(sf::Vector2f(5, 45));
	lineHour.setFillColor(sf::Color(18, 104, 10));
	lineHour.setPosition(660, 730);

	sf::Text inputTextHour;
	inputTextHour.setFont(font);
	inputTextHour.setCharacterSize(27);
	inputTextHour.setFillColor(sf::Color(255, 255, 255));
	inputTextHour.setPosition(670, 733);

	sf::RectangleShape buttonMinute(sf::Vector2f(50, 45));
	buttonMinute.setFillColor(sf::Color(86, 0, 172, 70));
	buttonMinute.setPosition(740, 730);

	sf::RectangleShape lineMinute(sf::Vector2f(5, 45));
	lineMinute.setFillColor(sf::Color(18, 104, 10));
	lineMinute.setPosition(740, 730);

	sf::Text inputTextMinute;
	inputTextMinute.setFont(font);
	inputTextMinute.setCharacterSize(27);
	inputTextMinute.setFillColor(sf::Color(255, 255, 255));
	inputTextMinute.setPosition(750, 733);

	sf::Text nameDuration;
	nameDuration.setFont(font);
	nameDuration.setCharacterSize(25);
	nameDuration.setFillColor(sf::Color(255, 130, 4));
	nameDuration.setPosition(95, 813);
	nameDuration.setString("Duration");

	sf::RectangleShape buttonDuration(sf::Vector2f(100, 45));
	buttonDuration.setFillColor(sf::Color(86, 0, 172, 70));
	buttonDuration.setPosition(200, 810);

	sf::RectangleShape lineDuration(sf::Vector2f(5, 45));
	lineDuration.setFillColor(sf::Color(18, 104, 10));
	lineDuration.setPosition(200, 810);

	sf::Text inputTextDuration;
	inputTextDuration.setFont(font);
	inputTextDuration.setCharacterSize(27);
	inputTextDuration.setFillColor(sf::Color(255, 255, 255));
	inputTextDuration.setPosition(210, 813);

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
	bool isInputTypeActive = false;
	bool isInputDescActive = false;
	bool isInputImageActive = false;
	bool isInputDayActive = false;
	bool isInputMonthActive = false;
	bool isInputYearActive = false;
	bool isInputHourActive = false;
	bool isInputMinuteActive = false;
	bool isInputDurationActive = false;

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
					lineType.setFillColor(sf::Color(18, 104, 10));
					lineDesc.setFillColor(sf::Color(18, 104, 10));
					lineImage.setFillColor(sf::Color(18, 104, 10));
					lineDay.setFillColor(sf::Color(18, 104, 10));
					lineMonth.setFillColor(sf::Color(18, 104, 10));
					lineYear.setFillColor(sf::Color(18, 104, 10));
					lineHour.setFillColor(sf::Color(18, 104, 10));
					lineMinute.setFillColor(sf::Color(18, 104, 10));
					lineDuration.setFillColor(sf::Color(18, 104, 10));

					isInputTitleActive = true;
					isInputTypeActive = false;
					isInputDescActive = false;
					isInputImageActive = false;
					isInputDayActive = false;
					isInputMonthActive = false;
					isInputYearActive = false;
					isInputHourActive = false;
					isInputMinuteActive = false;
					isInputDurationActive = false;
				}
				else if (isMouseOver(buttonType, event))
				{
					lineTitle.setFillColor(sf::Color(18, 104, 10));
					lineType.setFillColor(sf::Color(128, 241, 118));
					lineDesc.setFillColor(sf::Color(18, 104, 10));
					lineImage.setFillColor(sf::Color(18, 104, 10));
					lineDay.setFillColor(sf::Color(18, 104, 10));
					lineMonth.setFillColor(sf::Color(18, 104, 10));
					lineYear.setFillColor(sf::Color(18, 104, 10));
					lineHour.setFillColor(sf::Color(18, 104, 10));
					lineMinute.setFillColor(sf::Color(18, 104, 10));
					lineDuration.setFillColor(sf::Color(18, 104, 10));

					isInputTitleActive = false;
					isInputTypeActive = true;
					isInputDescActive = false;
					isInputImageActive = false;
					isInputDayActive = false;
					isInputMonthActive = false;
					isInputYearActive = false;
					isInputHourActive = false;
					isInputMinuteActive = false;
					isInputDurationActive = false;
				}
				else if (isMouseOver(buttonDesc, event))
				{
					lineTitle.setFillColor(sf::Color(18, 104, 10));
					lineType.setFillColor(sf::Color(18, 104, 10));
					lineDesc.setFillColor(sf::Color(128, 241, 118));
					lineImage.setFillColor(sf::Color(18, 104, 10));
					lineDay.setFillColor(sf::Color(18, 104, 10));
					lineMonth.setFillColor(sf::Color(18, 104, 10));
					lineYear.setFillColor(sf::Color(18, 104, 10));
					lineHour.setFillColor(sf::Color(18, 104, 10));
					lineMinute.setFillColor(sf::Color(18, 104, 10));
					lineDuration.setFillColor(sf::Color(18, 104, 10));

					isInputTitleActive = false;
					isInputTypeActive = false;
					isInputDescActive = true;
					isInputImageActive = false;
					isInputDayActive = false;
					isInputMonthActive = false;
					isInputYearActive = false;
					isInputHourActive = false;
					isInputMinuteActive = false;
					isInputDurationActive = false;
				}
				else if (isMouseOver(buttonImage, event)) {
					lineTitle.setFillColor(sf::Color(18, 104, 10));
					lineType.setFillColor(sf::Color(18, 104, 10));
					lineDesc.setFillColor(sf::Color(18, 104, 10));
					lineImage.setFillColor(sf::Color(128, 241, 118));
					lineDay.setFillColor(sf::Color(18, 104, 10));
					lineMonth.setFillColor(sf::Color(18, 104, 10));
					lineYear.setFillColor(sf::Color(18, 104, 10));
					lineHour.setFillColor(sf::Color(18, 104, 10));
					lineMinute.setFillColor(sf::Color(18, 104, 10));
					lineDuration.setFillColor(sf::Color(18, 104, 10));

					isInputTitleActive = false;
					isInputTypeActive = false;
					isInputDescActive = false;
					isInputImageActive = true;
					isInputDayActive = false;
					isInputMonthActive = false;
					isInputYearActive = false;
					isInputHourActive = false;
					isInputMinuteActive = false;
					isInputDurationActive = false;
				}
				else if (isMouseOver(buttonDay, event))
				{
					lineTitle.setFillColor(sf::Color(18, 104, 10));
					lineType.setFillColor(sf::Color(18, 104, 10));
					lineDesc.setFillColor(sf::Color(18, 104, 10));
					lineImage.setFillColor(sf::Color(18, 104, 10));
					lineDay.setFillColor(sf::Color(128, 241, 118));
					lineMonth.setFillColor(sf::Color(18, 104, 10));
					lineYear.setFillColor(sf::Color(18, 104, 10));
					lineHour.setFillColor(sf::Color(18, 104, 10));
					lineMinute.setFillColor(sf::Color(18, 104, 10));
					lineDuration.setFillColor(sf::Color(18, 104, 10));

					isInputTitleActive = false;
					isInputTypeActive = false;
					isInputDescActive = false;
					isInputImageActive = false;
					isInputDayActive = true;
					isInputMonthActive = false;
					isInputYearActive = false;
					isInputHourActive = false;
					isInputMinuteActive = false;
					isInputDurationActive = false;
				}
				else if (isMouseOver(buttonMonth, event))
				{
					lineTitle.setFillColor(sf::Color(18, 104, 10));
					lineType.setFillColor(sf::Color(18, 104, 10));
					lineDesc.setFillColor(sf::Color(18, 104, 10));
					lineImage.setFillColor(sf::Color(18, 104, 10));
					lineDay.setFillColor(sf::Color(18, 104, 10));
					lineMonth.setFillColor(sf::Color(128, 241, 118));
					lineYear.setFillColor(sf::Color(18, 104, 10));
					lineHour.setFillColor(sf::Color(18, 104, 10));
					lineMinute.setFillColor(sf::Color(18, 104, 10));
					lineDuration.setFillColor(sf::Color(18, 104, 10));

					isInputTitleActive = false;
					isInputTypeActive = false;
					isInputDescActive = false;
					isInputImageActive = false;
					isInputDayActive = false;
					isInputMonthActive = true;
					isInputYearActive = false;
					isInputHourActive = false;
					isInputMinuteActive = false;
					isInputDurationActive = false;
				}
				else if (isMouseOver(buttonYear, event))
				{
					lineTitle.setFillColor(sf::Color(18, 104, 10));
					lineType.setFillColor(sf::Color(18, 104, 10));
					lineDesc.setFillColor(sf::Color(18, 104, 10));
					lineImage.setFillColor(sf::Color(18, 104, 10));
					lineDay.setFillColor(sf::Color(18, 104, 10));
					lineMonth.setFillColor(sf::Color(18, 104, 10));
					lineYear.setFillColor(sf::Color(128, 241, 118));
					lineHour.setFillColor(sf::Color(18, 104, 10));
					lineMinute.setFillColor(sf::Color(18, 104, 10));
					lineDuration.setFillColor(sf::Color(18, 104, 10));

					isInputTitleActive = false;
					isInputTypeActive = false;
					isInputDescActive = false;
					isInputImageActive = false;
					isInputDayActive = false;
					isInputMonthActive = false;
					isInputYearActive = true;
					isInputHourActive = false;
					isInputMinuteActive = false;
					isInputDurationActive = false;
				}
				else if (isMouseOver(buttonHour, event))
				{
					lineTitle.setFillColor(sf::Color(18, 104, 10));
					lineType.setFillColor(sf::Color(18, 104, 10));
					lineDesc.setFillColor(sf::Color(18, 104, 10));
					lineImage.setFillColor(sf::Color(18, 104, 10));
					lineDay.setFillColor(sf::Color(18, 104, 10));
					lineMonth.setFillColor(sf::Color(18, 104, 10));
					lineYear.setFillColor(sf::Color(18, 104, 10));
					lineHour.setFillColor(sf::Color(128, 241, 118));
					lineMinute.setFillColor(sf::Color(18, 104, 10));
					lineDuration.setFillColor(sf::Color(18, 104, 10));

					isInputTitleActive = false;
					isInputTypeActive = false;
					isInputDescActive = false;
					isInputImageActive = false;
					isInputDayActive = false;
					isInputMonthActive = false;
					isInputYearActive = false;
					isInputHourActive = true;
					isInputMinuteActive = false;
					isInputDurationActive = false;
				}
				else if (isMouseOver(buttonMinute, event))
				{
					lineTitle.setFillColor(sf::Color(18, 104, 10));
					lineType.setFillColor(sf::Color(18, 104, 10));
					lineDesc.setFillColor(sf::Color(18, 104, 10));
					lineImage.setFillColor(sf::Color(18, 104, 10));
					lineDay.setFillColor(sf::Color(18, 104, 10));
					lineMonth.setFillColor(sf::Color(18, 104, 10));
					lineYear.setFillColor(sf::Color(18, 104, 10));
					lineHour.setFillColor(sf::Color(18, 104, 10));
					lineMinute.setFillColor(sf::Color(128, 241, 118));
					lineDuration.setFillColor(sf::Color(18, 104, 10));

					isInputTitleActive = false;
					isInputTypeActive = false;
					isInputDescActive = false;
					isInputImageActive = false;
					isInputDayActive = false;
					isInputMonthActive = false;
					isInputYearActive = false;
					isInputHourActive = false;
					isInputMinuteActive = true;
					isInputDurationActive = false;
				}
				else if (isMouseOver(buttonDuration, event))
				{
					lineTitle.setFillColor(sf::Color(18, 104, 10));
					lineType.setFillColor(sf::Color(18, 104, 10));
					lineDesc.setFillColor(sf::Color(18, 104, 10));
					lineImage.setFillColor(sf::Color(18, 104, 10));
					lineDay.setFillColor(sf::Color(18, 104, 10));
					lineMonth.setFillColor(sf::Color(18, 104, 10));
					lineYear.setFillColor(sf::Color(18, 104, 10));
					lineHour.setFillColor(sf::Color(18, 104, 10));
					lineMinute.setFillColor(sf::Color(18, 104, 10));
					lineDuration.setFillColor(sf::Color(128, 241, 118));

					isInputTitleActive = false;
					isInputTypeActive = false;
					isInputDescActive = false;
					isInputImageActive = false;
					isInputDayActive = false;
					isInputMonthActive = false;
					isInputYearActive = false;
					isInputHourActive = false;
					isInputMinuteActive = false;
					isInputDurationActive = true;
				}
				else {
					lineTitle.setFillColor(sf::Color(18, 104, 10));
					lineType.setFillColor(sf::Color(18, 104, 10));
					lineDesc.setFillColor(sf::Color(18, 104, 10));
					lineImage.setFillColor(sf::Color(18, 104, 10));
					lineDay.setFillColor(sf::Color(18, 104, 10));
					lineMonth.setFillColor(sf::Color(18, 104, 10));
					lineYear.setFillColor(sf::Color(18, 104, 10));
					lineHour.setFillColor(sf::Color(18, 104, 10));
					lineMinute.setFillColor(sf::Color(18, 104, 10));
					lineDuration.setFillColor(sf::Color(18, 104, 10));

					isInputTitleActive = false;
					isInputTypeActive = false;
					isInputDescActive = false;
					isInputImageActive = false;
					isInputDayActive = false;
					isInputMonthActive = false;
					isInputYearActive = false;
					isInputHourActive = false;
					isInputMinuteActive = false;
					isInputDurationActive = false;
				}

				if (createSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
					string currentTextTitle = inputTextTitle.getString();
					string currentTextType = inputTextType.getString();
					int currentTextDay= stringTointeger(inputTextDay.getString().toAnsiString());
					cout << currentTextDay << endl;
					int currentTextMonth = stringTointeger(inputTextMonth.getString().toAnsiString());
					int currentTextYear = stringTointeger(inputTextYear.getString().toAnsiString());
					int currentTextHour = stringTointeger(inputTextHour.getString().toAnsiString());
					int currentTextMinute = stringTointeger(inputTextMinute.getString().toAnsiString());
					int currentTextDuration = stringTointeger(inputTextDuration.getString().toAnsiString());
					cout << "11111";
					string currentTextDesc = textDesc;
					string currentTextImage = inputTextImage.getString();

					cout << "222222";

					sf::Texture texTureTest;
					if (currentTextTitle == "") {
						lineTitle.setFillColor(sf::Color(126, 0, 33));
					}
					if (currentTextType == "") {
						lineType.setFillColor(sf::Color(126, 0, 33));
					}
					if (currentTextDay < 1 || currentTextDay > 31) {
						lineDay.setFillColor(sf::Color(126, 0, 33));
					}
					if (currentTextMonth < 1 || currentTextMonth > 12) {
						lineMonth.setFillColor(sf::Color(126, 0, 33));
					}
					if (currentTextYear != 2024) {
						lineYear.setFillColor(sf::Color(126, 0, 33));
					}
					if (currentTextHour < 0 || currentTextHour > 23) {
						lineHour.setFillColor(sf::Color(126, 0, 33));
					}
					if (currentTextMinute < 0 || currentTextMinute > 59) {
						lineMinute.setFillColor(sf::Color(126, 0, 33));
					}
					if (currentTextDuration < 1 || currentTextMinute > 500) {
						lineDuration.setFillColor(sf::Color(126, 0, 33));
					}
					if (currentTextDesc == "") {
						lineDesc.setFillColor(sf::Color(126, 0, 33));
					}
					if (currentTextImage == "" || !texTureTest.loadFromFile(currentTextImage)) {
						lineImage.setFillColor(sf::Color(126, 0, 33));
					}
					cout << "33333";
					if (currentTextTitle != "" && currentTextType != "" && (currentTextDay >= 1 && currentTextDay <= 31) && (currentTextMonth >= 1 && currentTextMonth <= 12) && 
						currentTextYear == 2024 && (currentTextHour >= 0 && currentTextHour <= 23) && (currentTextMinute >= 0 && currentTextMinute <= 59) && 
						(currentTextDuration >= 1 && currentTextDuration <= 500) &&
						currentTextDesc != "" && 
						currentTextImage != "" && texTureTest.loadFromFile(currentTextImage)) {
						//for (int i = 0; i < films.size(); i++)
						//{
						//	productBoxes[i].first.setPosition(20 + i * 350, 125);

						//	productBoxes[i].second.first.setString(films[i].title);
						//	float textX = productBoxes[i].first.getPosition().x + productBoxes[i].first.getSize().x / 2 - productBoxes[i].second.first.getLocalBounds().width / 2;
						//	productBoxes[i].second.first.setPosition(textX, 600);
						//	productBoxes[i].second.second = films[i].image;
						//}
						film x;
						x.title = currentTextTitle;
						x.chu_de = currentTextType;
						x.hour = to_string(currentTextHour);
						x.minute = to_string(currentTextMinute);
						x.day = to_string(currentTextDay);
						x.month = to_string(currentTextMonth);
						x.year = to_string(currentTextYear);
						x.so_luong = to_string(currentTextDuration);
						x.desc = currentTextDesc;
						x.image = currentTextImage;
						films.push_back(x);
						std::thread writeThread(writeToFile);
						writeThread.join();
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

						sf::RectangleShape autoproductBox(sf::Vector2f(150, 200));
						autoproductBox.setFillColor(sf::Color::White);
						autoproductBox.setOutlineThickness(2);
						autoproductBox.setOutlineColor(sf::Color::Black);

						autoproductBoxes.push_back({ autoproductBox , currentTextImage });

						sf::RectangleShape adminproductBox(sf::Vector2f(327.5f, 470.f));
						adminproductBox.setPosition(20.f + 377.5 * (int)((films.size() - 1) % 4), filmListPosition1 + (int)((films.size() - 1) / 4) * 500);
						adminproductBox.setFillColor(sf::Color::White);
						adminproductBox.setOutlineThickness(2);
						adminproductBox.setOutlineColor(sf::Color::Black);

						sf::Text adminproductText(currentTextTitle, font, 24);
						adminproductText.setFillColor(sf::Color::Black);

						text_X = 20.f + 377.5 * (int)((films.size() - 1) % 4) + adminproductBox.getSize().x / 2 - adminproductText.getLocalBounds().width / 2;
						text_Y = filmListPosition1 + (int)((films.size() - 1) / 4) * 500 + adminproductBox.getSize().y - 25;
						adminproductText.setPosition(text_X, text_Y);

						adminproductBoxes.push_back({ adminproductBox , {adminproductText, currentTextImage} });

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
						//else if (event.text.unicode == '\r' || event.text.unicode == '\n')
						//{
						//	inputTextTitle.setString(inputTextTitle.getString() + "\n");
						//}
						else
						{
							inputTextTitle.setString(inputTextTitle.getString() + static_cast<char>(event.text.unicode));
						}
					}
				}
				else if (isInputTypeActive)
				{
					if (event.text.unicode < 128)
					{
						if (event.text.unicode == '\b')
						{
							if (!inputTextType.getString().isEmpty()) {
								std::string currentText = inputTextType.getString();
								currentText.pop_back();
								inputTextType.setString(currentText);
							}
						}
						//else if (event.text.unicode == '\r' || event.text.unicode == '\n')
						//{
						//	inputTextImage.setString(inputTextImage.getString() + "\n");
						//}
						else
						{
							inputTextType.setString(inputTextType.getString() + static_cast<char>(event.text.unicode));
						}
					}
				}
				else if (isInputHourActive)
				{
					if ((event.text.unicode >= 48 && event.text.unicode <= 57) || event.text.unicode == '\b')
					{
						if (event.text.unicode == '\b')
						{
							if (!inputTextHour.getString().isEmpty()) {
								std::string currentText = inputTextHour.getString();
								currentText.pop_back();
								inputTextHour.setString(currentText);
							}
						}
						//else if (event.text.unicode == '\r' || event.text.unicode == '\n')
						//{
						//	inputTextImage.setString(inputTextImage.getString() + "\n");
						//}
						else
						{
							std::string currentText = inputTextHour.getString();
							cout << currentText.size() << endl;
							if(currentText.size() < 2)
								inputTextHour.setString(inputTextHour.getString() + static_cast<char>(event.text.unicode));
						}
					}
				}
				else if (isInputMinuteActive)
				{
					if (event.text.unicode >= 48 && event.text.unicode <= 57 || event.text.unicode == '\b')
					{
						if (event.text.unicode == '\b')
						{
							if (!inputTextMinute.getString().isEmpty()) {
								std::string currentText = inputTextMinute.getString();
								currentText.pop_back();
								inputTextMinute.setString(currentText);
							}
						}
						//else if (event.text.unicode == '\r' || event.text.unicode == '\n')
						//{
						//	inputTextImage.setString(inputTextImage.getString() + "\n");
						//}
						else
						{
							std::string currentText = inputTextMinute.getString();
							if (currentText.size() < 2)
								inputTextMinute.setString(inputTextMinute.getString() + static_cast<char>(event.text.unicode));
						}
					}
				}
				else if (isInputDayActive)
				{
					if (event.text.unicode >= 48 && event.text.unicode <= 57 || event.text.unicode == '\b')
					{
						if (event.text.unicode == '\b')
						{
							if (!inputTextDay.getString().isEmpty()) {
								std::string currentText = inputTextDay.getString();
								currentText.pop_back();
								inputTextDay.setString(currentText);
							}
						}
						//else if (event.text.unicode == '\r' || event.text.unicode == '\n')
						//{
						//	inputTextImage.setString(inputTextImage.getString() + "\n");
						//}
						else
						{
							std::string currentText = inputTextDay.getString();
							if (currentText.size() < 2)
								inputTextDay.setString(inputTextDay.getString() + static_cast<char>(event.text.unicode));
						}
					}
				}
				else if (isInputMonthActive)
				{
					if (event.text.unicode >= 48 && event.text.unicode <= 57 || event.text.unicode == '\b')
					{
						if (event.text.unicode == '\b')
						{
							if (!inputTextMonth.getString().isEmpty()) {
								std::string currentText = inputTextMonth.getString();
								currentText.pop_back();
								inputTextMonth.setString(currentText);
							}
						}
						//else if (event.text.unicode == '\r' || event.text.unicode == '\n')
						//{
						//	inputTextImage.setString(inputTextImage.getString() + "\n");
						//}
						else
						{
							std::string currentText = inputTextMonth.getString();
							if (currentText.size() < 2)
								inputTextMonth.setString(inputTextMonth.getString() + static_cast<char>(event.text.unicode));
						}
					}
				}
				else if (isInputYearActive)
				{
					if (event.text.unicode >= 48 && event.text.unicode <= 57 || event.text.unicode == '\b')
					{
						if (event.text.unicode == '\b')
						{
							if (!inputTextYear.getString().isEmpty()) {
								std::string currentText = inputTextYear.getString();
								currentText.pop_back();
								inputTextYear.setString(currentText);
							}
						}
						//else if (event.text.unicode == '\r' || event.text.unicode == '\n')
						//{
						//	inputTextImage.setString(inputTextImage.getString() + "\n");
						//}
						else
						{
							std::string currentText = inputTextYear.getString();
							if (currentText.size() < 4)
								inputTextYear.setString(inputTextYear.getString() + static_cast<char>(event.text.unicode));
						}
					}
				}
				else if (isInputDurationActive)
				{
					if (event.text.unicode >= 48 && event.text.unicode <= 57 || event.text.unicode == '\b')
					{
						if (event.text.unicode == '\b')
						{
							if (!inputTextDuration.getString().isEmpty()) {
								std::string currentText = inputTextDuration.getString();
								currentText.pop_back();
								inputTextDuration.setString(currentText);
							}
						}
						//else if (event.text.unicode == '\r' || event.text.unicode == '\n')
						//{
						//	inputTextImage.setString(inputTextImage.getString() + "\n");
						//}
						else
						{
							std::string currentText = inputTextDuration.getString();
							if (currentText.size() < 3)
								inputTextDuration.setString(inputTextDuration.getString() + static_cast<char>(event.text.unicode));
						}
					}
				}
				else if (isInputDescActive)
				{
					if (event.text.unicode < 128)
					{
						cout << (event.text.unicode) << " " << static_cast<char>(event.text.unicode) << endl;
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
						//else if (event.text.unicode == '\r' || event.text.unicode == '\n')
						//{
						//	inputTextImage.setString(inputTextImage.getString() + "\n");
						//}
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

		window1.draw(nameTitle);
		window1.draw(buttonTitle);
		window1.draw(inputTextTitle);
		window1.draw(lineTitle);

		window1.draw(nameType);
		window1.draw(buttonType);
		window1.draw(inputTextType);
		window1.draw(lineType);

		window1.draw(nameDesc);
		window1.draw(buttonDesc);
		window1.draw(inputTextDesc);
		window1.draw(lineDesc);

		window1.draw(nameImage);
		window1.draw(buttonImage);
		window1.draw(inputTextImage);
		window1.draw(lineImage);

		window1.draw(nameTime);
		window1.draw(buttonDay);
		window1.draw(inputTextDay);
		window1.draw(lineDay);
		window1.draw(buttonMonth);
		window1.draw(inputTextMonth);
		window1.draw(lineMonth);
		window1.draw(buttonYear);
		window1.draw(inputTextYear);
		window1.draw(lineYear);

		window1.draw(nameHour);
		window1.draw(buttonHour);
		window1.draw(inputTextHour);
		window1.draw(lineHour);
		window1.draw(buttonMinute);
		window1.draw(inputTextMinute);
		window1.draw(lineMinute);

		window1.draw(nameDuration);
		window1.draw(buttonDuration);
		window1.draw(inputTextDuration);
		window1.draw(lineDuration);

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

	sf::Text tmpText("", font, 24);
	string tmpString = inputTextDesc.getString().toAnsiString();
	inputTextDesc.setString("");
	for (char c : tmpString) {
		if (tmpText.getLocalBounds().width <= 520) {
			tmpText.setString(tmpText.getString().toAnsiString() + c);
		}
		else {
			inputTextDesc.setString(tmpText.getString() + "\n" + c);
			tmpText.setString("");
		}
	}

	inputTextDesc.setString(inputTextDesc.getString().toAnsiString() + tmpText.getString().toAnsiString());
	//cout << detailDescripton.getString().toAnsiString() << endl;

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

						cout << "update";
						films[index].title = currentTextTitle;
						films[index].desc = currentTextDesc;
						films[index].image = currentTextImage;

						cout << "update1";

						//productBoxes[index].second.first.setString(currentTextTitle);
						//productBoxes[index].second.second = currentTextImage;

						cout << "update2";

						//float text_X = 20.f + 377.5 * (int)(index % 4) + productBoxes[index].first.getSize().x / 2 - productBoxes[index].second.first.getLocalBounds().width / 2;
						//float text_Y = filmListPosition1 + (int)(index / 4) * 500 + productBoxes[index].first.getSize().y - 25;
						//productBoxes[index].second.first.setPosition(text_X, text_Y);

						autoproductBoxes[index].second = currentTextImage;

						adminproductBoxes[index].second.first.setString(currentTextTitle);
						adminproductBoxes[index].second.second = currentTextImage;

						float text_X = 20.f + 377.5 * (int)(index % 4) + adminproductBoxes[index].first.getSize().x / 2 - adminproductBoxes[index].second.first.getLocalBounds().width / 2;
						float text_Y = filmListPosition1 + (int)(index / 4) * 500 + adminproductBoxes[index].first.getSize().y - 25;
						adminproductBoxes[index].second.first.setPosition(text_X, text_Y);

						window1.setVisible(false);
						window1.setActive(false);
						window.setVisible(true);
						window.setActive(true);
						return 0;
					}
				}

				if (deleteSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
					auto it1 = films.begin() + index;
					//std::vector<pair<sf::RectangleShape, pair<sf::Text, string>>>::iterator it2 = productBoxes.begin() + index;
					std::vector<pair<sf::RectangleShape, string>>::iterator it3 = autoproductBoxes.begin() + index;
					std::vector<pair<sf::RectangleShape, pair<sf::Text, string>>>::iterator it4 = adminproductBoxes.begin() + index;
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
					films.erase(it1);
					//productBoxes.erase(it2);
					autoproductBoxes.erase(it3);
					adminproductBoxes.erase(it4);

					//for (int i = 0; i < films.size(); i++)
					//{
					//	productBoxes[i].first.setPosition(20.f + 377.5 * (int)(i % 4), filmListPosition1 + (int)(i / 4) * 500);
					//	productBoxes[i].first.setFillColor(sf::Color::White);
					//	productBoxes[i].first.setOutlineThickness(2);
					//	productBoxes[i].first.setOutlineColor(sf::Color::Black);

					//	float text_X = 20.f + 377.5 * (int)(i % 4) + productBoxes[i].first.getSize().x / 2 - productBoxes[i].second.first.getLocalBounds().width / 2;
					//	float text_Y = filmListPosition1 + (int)(i / 4) * 500 + productBoxes[i].first.getSize().y - 25;
					//	productBoxes[i].second.first.setPosition(text_X, text_Y);
					//}

					for (int i = 0; i < films.size(); i++)
					{
						adminproductBoxes[i].first.setPosition(20.f + 377.5 * (int)(i % 4), filmListPosition1 + (int)(i / 4) * 500);
						adminproductBoxes[i].first.setFillColor(sf::Color::White);
						adminproductBoxes[i].first.setOutlineThickness(2);
						adminproductBoxes[i].first.setOutlineColor(sf::Color::Black);

						float text_X = 20.f + 377.5 * (int)(i % 4) + adminproductBoxes[i].first.getSize().x / 2 - adminproductBoxes[i].second.first.getLocalBounds().width / 2;
						float text_Y = filmListPosition1 + (int)(i / 4) * 500 + adminproductBoxes[i].first.getSize().y - 25;
						adminproductBoxes[i].second.first.setPosition(text_X, text_Y);
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
						//else if (event.text.unicode == '\r' || event.text.unicode == '\n')
						//{
						//	inputTextTitle.setString(inputTextTitle.getString() + "\n");
						//}
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
						//else if (event.text.unicode == '\r' || event.text.unicode == '\n')
						//{
						//	inputTextImage.setString(inputTextImage.getString() + "\n");
						//}
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

string normalizeString(const string& str) {
	string normalized = str;
	string res = "";
	string tmp;
	stringstream ss(normalized);
	while (ss >> tmp) {
		res += tmp;
	}
	normalized = res;

	transform(normalized.begin(), normalized.end(), normalized.begin(), ::tolower);
	return normalized;
}

#include <mutex>
#include <condition_variable>
#include <atomic>

std::atomic<bool> isPaused(false);

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

	//for (int i = 0; i < films.size(); i++)
	//{
	//	sf::RectangleShape productBox(sf::Vector2f(300, 500));
	//	productBox.setFillColor(sf::Color::White);
	//	productBox.setOutlineThickness(2);
	//	productBox.setOutlineColor(sf::Color::Black);

	//	sf::Text productText(films[i].title, font, 24);
	//	productText.setFillColor(sf::Color::Black);

	//	adminproductBoxes.push_back({ productBox , {productText, films[i].image} });
	//}

	sf::RectangleShape headerBox(sf::Vector2f(1500, 100));
	headerBox.setFillColor(sf::Color(3, 19, 39)); //205, 156, 124, 150
	headerBox.setPosition(0, 0);

	//////////////////////Movie//////////////////

	//std::vector<pair<string, string>> films;



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
		adminproductBoxes[i].first.setPosition(20.f + 377.5 * (int)(i % 4), filmListPosition1 + (int)(i / 4) * 500);

		float text_X = 20.f + 377.5 * (int)(i % 4) + adminproductBoxes[i].first.getSize().x / 2 - adminproductBoxes[i].second.first.getLocalBounds().width / 2;
		float text_Y = filmListPosition1 + (int)(i / 4) * 500 + adminproductBoxes[i].first.getSize().y - 25;
		adminproductBoxes[i].second.first.setPosition(text_X, text_Y);
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
	//sf::Texture textureOrder;
	//if (!textureOrder.loadFromFile("order(1500-800).png"))
	//	return EXIT_FAILURE;

	//// tạo sprite sử dụng texture đã tải
	//sf::Sprite spriteOrder(textureOrder);
	//float scale_x = 1500.0 / textureOrder.getSize().x;
	//float scale_y = 800.0 / textureOrder.getSize().y;
	//spriteOrder.setScale(scale_x, scale_y);
	//spriteOrder.setPosition(0, 100);

	//std::pair<sf::RectangleShape, bool> box[3][12][6];
	//vector< std::pair<sf::RectangleShape, bool>> box[12][6];

	int tmpGio;
	now tmpRightNow;
	if (tmpRightNow.getgio() % 2 == 1 && tmpRightNow.getgio() <= 21 && tmpRightNow.getgio() >= 7) {
		tmpGio = tmpRightNow.getgio();
		if (tmpRightNow.getphut() >= 45) {
			tmpGio += 2;
		}
		tmpGio = tmpGio / 2 - 2;
	}
	else if (tmpRightNow.getgio() % 2 == 0 && tmpRightNow.getgio() <= 21 && tmpRightNow.getgio() >= 7) {
		tmpGio = tmpRightNow.getgio();
		tmpGio += 1;
		tmpGio = tmpGio / 2 - 2;
	}
	else {
		tmpGio = 0;
	}

	string tmpIdPhong = "01" + to_string(tmpGio);

	std::string file_path = "DanhSachPhong.txt";


	std::ifstream file(file_path);

	// Kiểm tra xem tệp tin có mở thành công hay không
	if (!file.is_open()) {
		std::cerr << "cant open" << std::endl;
		return 1;
	}
	//bool mang3Chieu[3][7][11];
	int m = 0, n = 0;
	bool daTimThayPhong = 0;
	int demLineDaNhap = 0;
	cout << tmpIdPhong << endl;
	// Đọc từng dòng của tệp tin
	std::string tmpLine;
	while (getline(file, tmpLine)) {
		// Kiểm tra xem chuỗi xác định có xuất hiện trong dòng hay không
		if (tmpLine == tmpIdPhong) {
			daTimThayPhong = 1;
		}
		if (daTimThayPhong && tmpLine.length() > 3) {
			for (int k = 0; k < 11; k++) {
				box[m][n][k] = tmpLine[k] - '0';
				cout << tmpLine[k] - '0';
			}
			cout << endl;
			n++;
			demLineDaNhap++;

		}

		if (demLineDaNhap == 7) {
			demLineDaNhap = 0;
			m++;
			n = 0;
			tmpIdPhong[1] += 1;
			cout << tmpIdPhong << endl;;
			daTimThayPhong = 0;
		}
		if (tmpIdPhong[1] == '4') {
			break;
		}

	}
	// Đóng tệp tin khi kết thúc
	file.close();

	const int rows = 7, cols = 11;
	const float borderSize = 2.f;
	sf::Font lora;
	if (!lora.loadFromFile("Lora-VariableFont_wght.ttf")) {
		// X? l� l?i n?u kh�ng t?i ???c font
		return EXIT_FAILURE;
	}

	sf::RectangleShape gheNgoi[rows][cols];
	sf::Text textGheNgoi[rows][cols];

	sf::RectangleShape loaiGheNgoi[3];
	sf::Text textLoaiGhe[3];
	bool daLoadGheNgoi = 0;
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
					if (adminproductBoxes[films.size() - 1].first.getPosition().y >= 380) {
						filmListPosition1 += -delta;
						for (int i = 0; i < films.size(); i++)
						{
							adminproductBoxes[i].first.move(0, -delta);
							adminproductBoxes[i].second.first.move(0, -delta);
						}
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					if (filmListPosition1 < 120.f) {
						filmListPosition1 += delta;
						for (int i = 0; i < films.size(); i++)
						{
							adminproductBoxes[i].first.move(0, delta);
							adminproductBoxes[i].second.first.move(0, delta);
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
						if (selectAndUpdateButton) {
							if (indexButton) {
								//for (int i = 0; i < 12; i++) {
								//	for (int j = 0; j < 6; j++) {
								//		if (box[indexButton - 1][i][j].first.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
								//			if (box[indexButton - 1][i][j].second) {
								//				box[indexButton - 1][i][j].second = false;
								//				box[indexButton - 1][i][j].first.setFillColor(sf::Color(238, 100, 87)); //100, 238, 87

								//			}
								//			else {
								//				box[indexButton - 1][i][j].second = true;
								//				box[indexButton - 1][i][j].first.setFillColor(sf::Color(100, 238, 87)); //100, 238, 87
								//			}
								//		}
								//	}
								//}

								for (int i = 0; i < 3; i++) {
									loaiGheNgoi[i].setSize(sf::Vector2f(squareSize, squareSize));
									loaiGheNgoi[i].setPosition(200, 200 + 70 * i);
									loaiGheNgoi[i].setOutlineThickness(1);
									textLoaiGhe[i].setPosition(loaiGheNgoi[i].getPosition().x + 95, 20 + loaiGheNgoi[i].getPosition().y);
									textLoaiGhe[i].setFillColor(sf::Color::Black); // M u v?n b?n
									textLoaiGhe[i].setFont(lora);
									textLoaiGhe[i].setCharacterSize(18); // K ch th??c font
									textLoaiGhe[i].setStyle(sf::Text::Bold); // 
								}
								loaiGheNgoi[0].setOutlineColor(sf::Color::Green);
								loaiGheNgoi[1].setOutlineColor(sf::Color::Blue);
								loaiGheNgoi[2].setOutlineColor(sf::Color::Magenta);
								textLoaiGhe[0].setString("GHE THUONG");
								textLoaiGhe[1].setString("GHE VIP");
								textLoaiGhe[2].setString("GHE COUP");


								for (int i = 0; i < rows; ++i)
								{
									for (int j = 0; j < cols; ++j)
									{
										string tmp = "";
										tmp += i + 48 + 17;
										tmp += to_string(j);
										textGheNgoi[i][j].setString(tmp);
										textGheNgoi[i][j].setFillColor(sf::Color::Black); // M u v?n b?n
										textGheNgoi[i][j].setFont(lora);
										textGheNgoi[i][j].setCharacterSize(18); // K ch th??c font
										textGheNgoi[i][j].setPosition(500 + j * (squareSize + borderSize + 5) + 5, 10 + 200 + i * (squareSize + borderSize + 5));
										gheNgoi[i][j].setSize(sf::Vector2f(squareSize, squareSize));
										gheNgoi[i][j].setOutlineThickness(1);
										gheNgoi[i][j].setPosition(500 + j * (squareSize + borderSize + 5), 200 + i * (squareSize + borderSize + 5));
										gheNgoi[i][j].setOutlineColor(sf::Color::Black);
									}
								}

								for (int i = 0; i < rows; i++) {
									for (int j = 0; j < cols; j++) {
										if (box[indexButton - 1][i][j]) {
											gheNgoi[i][j].setFillColor(sf::Color::Red);
										}
									}
								}
							}
						}
					}
					else if (createButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						createFilmsWindow(window, window1, font, filmListPosition1);
					}
					else {
						for (int i = 0; i < adminproductBoxes.size(); i++)
						{
							if (adminproductBoxes[i].first.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
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
					if (exitButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
						window.close();
						return 0;
					}
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
							//for (int i = 0; i < 12; i++) {
							//	for (int j = 0; j < 6; j++) {
							//		if (box[indexButton - 1][i][j].first.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
							//			if (box[indexButton - 1][i][j].second) {
							//				box[indexButton - 1][i][j].second = false;
							//				box[indexButton - 1][i][j].first.setFillColor(sf::Color(238, 100, 87)); //100, 238, 87

							//			}
							//			else {
							//				box[indexButton - 1][i][j].second = true;
							//				box[indexButton - 1][i][j].first.setFillColor(sf::Color(100, 238, 87)); //100, 238, 87
							//			}
							//		}
							//	}
							//}

							for (int i = 0; i < 3; i++) {
								loaiGheNgoi[i].setSize(sf::Vector2f(squareSize, squareSize));
								loaiGheNgoi[i].setPosition(200, 200 + 70 * i);
								loaiGheNgoi[i].setOutlineThickness(1);
								textLoaiGhe[i].setPosition(loaiGheNgoi[i].getPosition().x + 95, 20 + loaiGheNgoi[i].getPosition().y);
								textLoaiGhe[i].setFillColor(sf::Color::Black); // M u v?n b?n
								textLoaiGhe[i].setFont(lora);
								textLoaiGhe[i].setCharacterSize(18); // K ch th??c font
								textLoaiGhe[i].setStyle(sf::Text::Bold); // 
							}
							loaiGheNgoi[0].setOutlineColor(sf::Color::Green);
							loaiGheNgoi[1].setOutlineColor(sf::Color::Blue);
							loaiGheNgoi[2].setOutlineColor(sf::Color::Magenta);
							textLoaiGhe[0].setString("GHE THUONG");
							textLoaiGhe[1].setString("GHE VIP");
							textLoaiGhe[2].setString("GHE COUP");


							for (int i = 0; i < rows; ++i)
							{
								for (int j = 0; j < cols; ++j)
								{
									string tmp = "";
									tmp += i + 48 + 17;
									tmp += to_string(j);
									textGheNgoi[i][j].setString(tmp);
									textGheNgoi[i][j].setFillColor(sf::Color::Black); // M u v?n b?n
									textGheNgoi[i][j].setFont(lora);
									textGheNgoi[i][j].setCharacterSize(18); // K ch th??c font
									textGheNgoi[i][j].setPosition(500 + j * (squareSize + borderSize + 5) + 5, 10 + 200 + i * (squareSize + borderSize + 5));
									gheNgoi[i][j].setSize(sf::Vector2f(squareSize, squareSize));
									gheNgoi[i][j].setOutlineThickness(1);
									gheNgoi[i][j].setPosition(500 + j * (squareSize + borderSize + 5), 200 + i * (squareSize + borderSize + 5));
									gheNgoi[i][j].setOutlineColor(sf::Color::Black);
								}
							}

							for (int i = 0; i < rows; i++) {
								for (int j = 0; j < cols; j++) {
									if (box[indexButton - 1][i][j]) {
										gheNgoi[i][j].setFillColor(sf::Color::Red);
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
					for (int i = 0; i < 3; ++i) {
						if (loaiGheNgoi[i].getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
							daLoadGheNgoi = 1;
							if (i == 0) {
								for (int k = 0; k < 11; k++) {
									gheNgoi[0][k].setFillColor(sf::Color::Green);
									gheNgoi[1][k].setFillColor(sf::Color::Green);
									gheNgoi[5][k].setFillColor(sf::Color::Green);
									gheNgoi[6][k].setFillColor(sf::Color::Green);
								}

							}
							else if (i == 1) {
								for (int k = 0; k < 11; k++) {
									gheNgoi[2][k].setFillColor(sf::Color::Blue);
									gheNgoi[3][k].setFillColor(sf::Color::Blue);

								}
							}
							else if (i == 2) {
								for (int k = 0; k < 11; k++) {
									gheNgoi[4][k].setFillColor(sf::Color::Magenta);

								}
							}
						}
						else {
							if (i == 0) {
								for (int k = 0; k < 11; k++) {
									gheNgoi[0][k].setFillColor(sf::Color::White);
									gheNgoi[1][k].setFillColor(sf::Color::White);
									gheNgoi[5][k].setFillColor(sf::Color::White);
									gheNgoi[6][k].setFillColor(sf::Color::White);
								}

							}
							else if (i == 1) {
								for (int k = 0; k < 11; k++) {
									gheNgoi[2][k].setFillColor(sf::Color::White);
									gheNgoi[3][k].setFillColor(sf::Color::White);

								}
							}
							else if (i == 2) {
								for (int k = 0; k < 11; k++) {
									gheNgoi[4][k].setFillColor(sf::Color::White);

								}
							}
							for (int i = 0; i < rows; i++) {
								for (int j = 0; j < cols; j++) {
									if (box[indexButton - 1][i][j]) {
										gheNgoi[i][j].setFillColor(sf::Color::Red);
									}
								}
							}
						}
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
				if (!texture.loadFromFile(adminproductBoxes[i].second.second)) {
					texture.loadFromFile("404.jfif");
				}
				sf::Sprite sprite(texture);
				float scalex = 317.5 / texture.getSize().x;
				float scaley = 445.0 / texture.getSize().y;
				sprite.setScale(scalex, scaley);
				float x = 20.f + 377.5 * (int)(i % 4) + 5;
				float y = filmListPosition1 + (int)(i / 4) * 500 + 5;
				sprite.setPosition(x, y);
				window.draw(adminproductBoxes[i].first);
				window.draw(sprite);
				window.draw(adminproductBoxes[i].second.first);
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

		//if (selectDropDownButton) {
		//	window.draw(spriteOrder);
		//}

		if (selectAndUpdateButton) {
			if (indexButton) {
				//for (int i = 0; i < 12; i++) {
				//	for (int j = 0; j < 6; j++) {
				//		window.draw(box[indexButton - 1][i][j].first);
				//	}
				//}
				for (int i = 0; i < rows; i++) {
					for (int j = 0; j < cols; j++) {
						if (i == 4 && j == 10) {

						}
						else {
							window.draw(gheNgoi[i][j]);
							window.draw(textGheNgoi[i][j]);
						}
					}
				}
				for (int i = 0; i < 3; i++) {
					window.draw(loaiGheNgoi[i]);
					window.draw(textLoaiGhe[i]);
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

void drawQRCode(sf::RenderWindow& window, const int array2D[rows1][cols1]) {
	for (int i = 0; i < rows1; ++i) {
		for (int j = 0; j < cols1; ++j) {
			// Sá»­ dá»¥ng giÃ¡ trá»‹ tá»« máº£ng Ä‘á»ƒ xÃ¡c Ä‘á»‹nh mÃ u cho Ã´ vuÃ´ng

			sf::Color color = array2D[i][j] % 2 == 0 ? sf::Color::Black : sf::Color::White;

			// Váº½ Ã´ vuÃ´ng
			sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
			square.setPosition(640 + j * squareSize, 70 + i * squareSize);
			square.setFillColor(color);

			window.draw(square);
		}
	}
}
string chinhSuaText(string tmpText, int textDistance[], int n, bool name) {
	int MAX_STRING_LENGTH;
	int MIN_DISPLAY_LENTH;
	int FirstLetter;
	int SecondLetter;

	if (name) {
		MAX_STRING_LENGTH = 40;
		MIN_DISPLAY_LENTH = 20;
		FirstLetter = 14;
	}
	else {
		MAX_STRING_LENGTH = 50;
		MIN_DISPLAY_LENTH = 30;
		FirstLetter = 25;
	}
	if (n == 18) {
		MAX_STRING_LENGTH = 200;
		MIN_DISPLAY_LENTH = 60;
		FirstLetter = 93;
		SecondLetter = 196;

	}
	if (tmpText.size() >= MIN_DISPLAY_LENTH && tmpText.size() <= MAX_STRING_LENGTH) {

		string tmp1, tmp2;
		for (int i = FirstLetter; i < tmpText.size(); i++) {
			if (tmpText[i] == ' ') {
				for (int j = 0; j < i; j++) {
					tmp1 += tmpText[j];
				}
				for (int j = i + 1; j < tmpText.size(); j++) {
					tmp2 += tmpText[j];
				}
				textDistance[n] += 7;
				break;
			}
		}
		return (tmp1 + "\n" + tmp2);
	}
	else if (tmpText.size() > MAX_STRING_LENGTH) {
		string tmp1, tmp2, tmp3;
		for (int i = FirstLetter; i < tmpText.size(); i++) {
			if (tmpText[i] == ' ') {
				for (int j = 0; j < i; j++) {
					tmp1 += tmpText[j];
				}
				for (int j = SecondLetter; j <= MAX_STRING_LENGTH; j++) {
					if (tmpText[j] == ' ') {
						for (int k = i + 1; k < j; k++) {
							tmp2 += tmpText[k];
						}
						for (int k = j; k < tmpText.size(); k++) {
							tmp3 += tmpText[k];
						}
						textDistance[n] += 14;
						break;
					}
				}
				break;
			}
		}



		return (tmp1 + "\n" + tmp2 + "\n" + tmp3);
	}
	else {

		return (tmpText);
	}
}
std::vector<std::string> splitString(const std::string& input) {
	std::vector<std::string> result;
	std::string word;
	std::size_t startPos = input.find_first_not_of(" ,"); // TÃ¬m vá»‹ trÃ­ cá»§a kÃ½ tá»± Ä‘áº§u tiÃªn khÃ´ng pháº£i lÃ  khoáº£ng tráº¯ng hoáº·c dáº¥u pháº©y

	while (startPos != std::string::npos) {
		std::size_t endPos = input.find_first_of(" ,", startPos); // TÃ¬m vá»‹ trÃ­ cá»§a kÃ½ tá»± Ä‘áº§u tiÃªn lÃ  khoáº£ng tráº¯ng hoáº·c dáº¥u pháº©y
		word = input.substr(startPos, (endPos != std::string::npos) ? (endPos - startPos) : std::string::npos);
		result.push_back(word);

		startPos = input.find_first_not_of(" ,", endPos); // TÃ¬m vá»‹ trÃ­ cá»§a kÃ½ tá»± Ä‘áº§u tiÃªn khÃ´ng pháº£i lÃ  khoáº£ng tráº¯ng hoáº·c dáº¥u pháº©y
	}

	return result;
}

// Function to check if there is at least one common genre between two strings
bool areGenresMatching(const std::string& genres1, const std::string& genres2) {
	std::vector<std::string> words1 = splitString(genres1);
	std::vector<std::string> words2 = splitString(genres2);

	for (const auto& word : words1) {
		if (std::find(words2.begin(), words2.end(), word) != words2.end()) {
			return true;
		}
	}

	return false;
}

int main() {
	admin admin1;
	admin1.themphim("DanhSachPhim.txt");
	admin1.nhaprap();
	admin1.nhapsuatchieu("DanhSachSuatChieu.txt");
	admin1.nhapphongchieu("DanhSachPhong.txt");
	admin1.quanlychieuphim();
	admin1.xoaSuatChieu();
	admin1.nhapsuatchieu("DanhSachSuatChieu.txt");
	admin1.nhapphongchieu("DanhSachPhong.txt");
	const int soPhim = admin1.getsophim();
	sf::RenderWindow window(sf::VideoMode(1480, 832), "Dat Ve");
	sf::Font Freck;
	if (!Freck.loadFromFile("FrederickatheGreat-Regular.ttf")) {
		// X? lï¿½ l?i n?u khï¿½ng t?i ???c font
		return EXIT_FAILURE;
	}

	sf::Font arial;
	if (!arial.loadFromFile("arial.ttf")) {
		// X? lï¿½ l?i n?u khï¿½ng t?i ???c font
		return EXIT_FAILURE;
	}
	sf::Font tech;
	if (!tech.loadFromFile("Judge-2OaRe.ttf")) {
		// X? lï¿½ l?i n?u khï¿½ng t?i ???c font
		return EXIT_FAILURE;
	}
	sf::Font funny;
	//if (!funny.loadFromFile("Ghostmeat.ttf")) {
	//    // X? lï¿½ l?i n?u khï¿½ng t?i ???c font
	//    return EXIT_FAILURE;
	//}
	sf::Font lora;
	if (!lora.loadFromFile("Lora-VariableFont_wght.ttf")) {
		// X? lï¿½ l?i n?u khï¿½ng t?i ???c font
		return EXIT_FAILURE;
	}
	sf::Font horror;
	if (!horror.loadFromFile("Melted Monster.ttf")) {
		// X? lï¿½ l?i n?u khï¿½ng t?i ???c font
		return EXIT_FAILURE;
	}

	sf::Font love;
	if (!love.loadFromFile("Love.ttf")) {
		// X? lï¿½ l?i n?u khï¿½ng t?i ???c font
		return EXIT_FAILURE;
	}
	sf::Font cinema;
	if (!cinema.loadFromFile("VOLACROME.ttf")) {
		// X? lï¿½ l?i n?u khï¿½ng t?i ???c font
		return EXIT_FAILURE;
	}
	sf::Font action;
	//if (!action.loadFromFile("PatrioticsDemoRegular.ttf")) {
	//    // X? lï¿½ l?i n?u khï¿½ng t?i ???c font
	//    return EXIT_FAILURE;
	//}
	// T?o ??i t??ng sf::Text
	int row;
	if ((float)admin1.getsophim() - admin1.getsophim() == 0) {
		row = admin1.getsophim() / 3;
	}
	else {
		row = admin1.getsophim() / 3 + 1;
	}
	int column = 3;
	sf::Text CGV;
	CGV.setFont(cinema);
	CGV.setCharacterSize(70); // Kï¿½ch th??c font
	CGV.setFillColor(sf::Color::Black); // Mï¿½u v?n b?n
	CGV.setString("CGV DN"); // N?i dung v?n b?n
	CGV.setPosition((window.getSize().x - CGV.getGlobalBounds().width) / 2, 20);
	bool daloadmenuphim = 0;
	sf::Text phimdangchieu;
	phimdangchieu.setFont(lora);
	phimdangchieu.setCharacterSize(52); // Kï¿½ch th??c font
	phimdangchieu.setFillColor(sf::Color::Black); // Mï¿½u v?n b?n
	phimdangchieu.setString("Phim Dang Chieu"); // N?i dung v?n b?n
	phimdangchieu.setPosition(167.5, 221 + 50);
	std::vector<sf::RectangleShape> borderPosterPhim;
	string truycapphim = "";
	float scalex, scaley;
	sf::Sprite* posterPhim = new sf::Sprite[soPhim];
	sf::Texture* texturePhim = new sf::Texture[soPhim];
	for (int i = 0; i < admin1.getsophim(); i++) {
		sf::Texture* tmptexture = new sf::Texture;
		sf::Sprite* tmpSprite = new sf::Sprite;

		sf::RectangleShape rectangle(sf::Vector2f(270, 385.2));

		// ??t v? trï¿½ vï¿½ mï¿½u s?c cho ch? nh?t
		rectangle.setFillColor(sf::Color::Transparent);  // ??t mï¿½u n?n lï¿½ trong su?t
		rectangle.setOutlineThickness(5);  // ??t ?? r?ng ???ng vi?n
		rectangle.setOutlineColor(sf::Color::Black);  // ??t mï¿½u ???ng vi?n
		borderPosterPhim.push_back(rectangle);
		posterPhim[i] = (*tmpSprite);
		texturePhim[i] = (*tmptexture);

	}
	int columnnow;
	int rownow;
	vector <int> countTheLoai;
	int viTriSearchBar = 20;
	sf::Texture searchBarTexture;
	if (!searchBarTexture.loadFromFile("searchBar.png")) {
		// Xá»­ lÃ½ lá»—i náº¿u khÃ´ng táº£i Ä‘Æ°á»£c hÃ¬nh áº£nh
		return -1;
	}

	// Táº¡o sprite vÃ  Ä‘áº·t texture cho sprite
	sf::Sprite searchBar(searchBarTexture);

	searchBar.setPosition((window.getSize().x - searchBar.getGlobalBounds().width) / 2, 20);
	sf::Text searchBoxText;
	//searchBoxText.setFillColor(sf::Color::Black);
	searchBoxText.setFillColor(sf::Color(104, 104, 104));
	searchBoxText.setFont(lora);
	searchBoxText.setCharacterSize(25);
	searchBoxText.setPosition(searchBar.getPosition().x + 5, 35);
	searchBoxText.setString("Search...");

	sf::Texture backButtonTexture;
	if (!backButtonTexture.loadFromFile("previousButton.png")) {
		// Xá»­ lÃ½ lá»—i náº¿u khÃ´ng táº£i Ä‘Æ°á»£c hÃ¬nh áº£nh
		return -1;
	}

	// Táº¡o sprite vÃ  Ä‘áº·t texture cho sprite
	sf::Sprite backButton(backButtonTexture);
	sf::Vector2f newSize(52.9774127312, 43);
	scalex = newSize.x / backButton.getGlobalBounds().width;
	scaley = newSize.y / backButton.getGlobalBounds().height;
	backButton.setScale(scalex, scaley);
	backButton.setPosition(0, 0);
	sf::Text thongtinphim1Tmp;
	thongtinphim1Tmp.setFont(lora);
	thongtinphim1Tmp.setCharacterSize(20);
	thongtinphim1Tmp.setFillColor(sf::Color::Black);


	// T?i hï¿½nh ?nh t? file vï¿½ thï¿½m vï¿½o vector
	std::vector <sf::Text>  tenphim(admin1.getsophim());
	std::vector<std::pair<std::string, sf::Text>> thongtinphim1(admin1.getsophim());
	std::vector <sf::Text> thongtinphim2(admin1.getsophim());
	std::vector <sf::Text>  thongtinphim3(admin1.getsophim());
	string selectedMovie;
	int countPage = 1;
	sf::Cursor handPointer;
	sf::Cursor arrowPointer;
	sf::Image handImage;
	sf::Image arrowImage;
	if (!handImage.loadFromFile("handpointer.png")) {
		// Handle loading error
		return -1;
	}

	if (!handPointer.loadFromPixels(handImage.getPixelsPtr(), handImage.getSize(), { 0, 0 })) {
		// Handle loading error
		return -1;
	}
	if (!arrowImage.loadFromFile("arrowPointer.png")) {
		// Handle loading error
		return -1;
	}

	if (!arrowPointer.loadFromPixels(arrowImage.getPixelsPtr(), arrowImage.getSize(), { 0, 0 })) {
		// Handle loading error
		return -1;
	}
	bool isHovered = false;
	sf::Vector2f startPoint(phimdangchieu.getPosition().x, phimdangchieu.getPosition().y + 60);
	sf::Vector2f endPoint(posterPhim[2].getPosition().x + posterPhim[2].getGlobalBounds().width + 500, phimdangchieu.getPosition().y + 60);

	sf::Vector2f direction = endPoint - startPoint;
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	sf::RectangleShape line(sf::Vector2f(length, 2)); // Äá»™ dÃ y cá»§a Ä‘Æ°á»ng tháº³ng lÃ  5 pixels
	line.setPosition(startPoint);
	line.setFillColor(sf::Color::Black);


	// page 2
	int selectedPhimNumber;
	sf::Text noiDungPhim;
	noiDungPhim.setFont(lora);
	noiDungPhim.setCharacterSize(52); // Kï¿½ch th??c font
	noiDungPhim.setFillColor(sf::Color::Black); // Mï¿½u v?n b?n
	noiDungPhim.setString("Noi Dung Phim"); // N?i dung v?n b?n
	noiDungPhim.setPosition(110, 0 + 90 + 30); // V? trï¿½ c?a v?n b?n trï¿½n c?a s?

	sf::Text coTheBanCungThich;
	coTheBanCungThich.setFont(lora);
	coTheBanCungThich.setCharacterSize(52); // Kï¿½ch th??c font
	coTheBanCungThich.setFillColor(sf::Color::Black); // Mï¿½u v?n b?n
	coTheBanCungThich.setString("Co The Ban Cung Thich"); // N?i dung v?n b?n
	coTheBanCungThich.setPosition((window.getSize().x - coTheBanCungThich.getGlobalBounds().width) / 2, 700); // V? trï¿½ c?a v?n b?n trï¿½n c?a s?

	sf::Texture orderButtonTextture;
	if (!orderButtonTextture.loadFromFile("orderButton.png")) {
		// Xá»­ lÃ½ lá»—i náº¿u khÃ´ng táº£i Ä‘Æ°á»£c hÃ¬nh áº£nh
		return -1;
	}

	// Táº¡o sprite vÃ  Ä‘áº·t texture cho sprite
	sf::Sprite orderButton(orderButtonTextture);
	orderButton.setPosition(100 + 60, 400 + (static_cast<float>(window.getSize().y) - static_cast<float>(borderPosterPhim[0].getSize().y)) / 2 + 50);

	sf::Text contentText[2];
	phim selectedPhim;
	bool daloadtheloai = 0;
	bool daloadphimchieu = 0;
	//// page 3
	int selectedNgay;
	bool clickedSuatChieu = 0;
	sf::Text thuNgay[10];
	sf::Text ngayThang[10];
	sf::Text MENU;
	MENU.setFont(cinema);
	MENU.setCharacterSize(70); // Kï¿½ch th??c font
	MENU.setFillColor(sf::Color::Black); // Mï¿½u v?n b?n
	MENU.setString("MENU"); // N?i dung v?n b?n
	MENU.setPosition((window.getSize().x - MENU.getGlobalBounds().width) / 2 - 120, 250);
	int countSuatChieu = 0;
	for (int i = 0; i < 10; i++) {
		ngayThang[i].setFont(lora);
		ngayThang[i].setCharacterSize(20);
		ngayThang[i].setFillColor(sf::Color::Black);
		ngayThang[i].setString(to_string(admin1.getsuat(i, 0, 0).getthoigianchieu().getngay()) + " " + to_string(admin1.getsuat(i, 0, 0).getthoigianchieu().getthang()));
		if (admin1.getsuat(i, 0, 0).getthoigianchieu().getngay() < 10 || admin1.getsuat(i, 0, 0).getthoigianchieu().getthang()) {
			if (admin1.getsuat(i, 0, 0).getthoigianchieu().getngay() < 10) {
				if (admin1.getsuat(i, 0, 0).getthoigianchieu().getthang() < 10) {
					ngayThang[i].setString("0" + to_string(admin1.getsuat(i, 0, 0).getthoigianchieu().getngay()) + " " + "0" + to_string(admin1.getsuat(i, 0, 0).getthoigianchieu().getthang()));
				}
				else {
					ngayThang[i].setString("0" + to_string(admin1.getsuat(i, 0, 0).getthoigianchieu().getngay()) + " " + to_string(admin1.getsuat(i, 0, 0).getthoigianchieu().getthang()));
				}
			}
			else if (admin1.getsuat(i, 0, 0).getthoigianchieu().getthang() < 10) {
				ngayThang[i].setString(to_string(admin1.getsuat(i, 0, 0).getthoigianchieu().getngay()) + " " + "0" + to_string(admin1.getsuat(i, 0, 0).getthoigianchieu().getthang()));

			}
		}
		thuNgay[i].setFont(lora);
		thuNgay[i].setCharacterSize(20);
		thuNgay[i].setFillColor(sf::Color::Black);

		switch (admin1.getsuat(i, 0, 0).getthoigianchieu().getthungay()) {
		case 0:
			thuNgay[i].setString("SUN");
			break;
		case 1:

			thuNgay[i].setString("MON");
			break;
		case 2:
			thuNgay[i].setString("TUES");
			break;
		case 3:
			thuNgay[i].setString("WED");
			break;
		case 4:
			thuNgay[i].setString("THURS");
			break;
		case 5:
			thuNgay[i].setString("FRI");
			break;
		case 6:
			thuNgay[i].setString("SAT");
			break;
		default:
			// Xá»­ lÃ½ trÆ°á»ng há»£p khÃ´ng náº±m trong cÃ¡c giÃ¡ trá»‹ trÃªn (náº¿u cáº§n)
			break;
		}
	}

	const int numRectangles = 10;
	std::vector<sf::RectangleShape> thuNgayBorder(numRectangles);
	// Initialize rectangles and texts
	for (int i = 0; i < numRectangles; ++i) {
		// Create rectangle for the border
		thuNgayBorder[i].setSize(sf::Vector2f(133, thuNgay[i].getGlobalBounds().height + ngayThang[i].getGlobalBounds().height + 18));
		thuNgayBorder[i].setFillColor(sf::Color::Transparent);
		thuNgayBorder[i].setOutlineColor(sf::Color::White);
		thuNgayBorder[i].setOutlineThickness(2.0f);
	}
	for (int i = 0; i < 6; i++) {
		thuNgay[i].setPosition(i * 150 + 50 + 60, 50);
		ngayThang[i].setPosition(i * 150 + 50, 50);
		thuNgayBorder[i].setPosition(ngayThang[i].getPosition().x, ngayThang[i].getPosition().y - 10);
	}
	for (int i = 6; i < 10; i++) {
		thuNgay[i].setPosition((i - 6) * 150 + 50 + 60, 50 + thuNgayBorder[0].getSize().y);
		ngayThang[i].setPosition((i - 6) * 150 + 50, 50 + thuNgayBorder[0].getSize().y);
		thuNgayBorder[i].setPosition(ngayThang[i].getPosition().x, ngayThang[i].getPosition().y - 10);
	}
	std::vector<sf::RectangleShape> suatChieuBorder;
	std::vector<sf::Text> suatChieu;
	const int buttonCount = 3;
	int quantities[buttonCount][buttonCount] = { 0 };

	sf::Text quantityTexts[buttonCount];
	sf::RectangleShape buttons[2 * buttonCount];
	sf::Text buttonTexts[2 * buttonCount];


	int sizeQuantities[buttonCount] = { 0 };
	int gioHangMenu[9] = { 0 };
	sf::Text sizeText[buttonCount];
	sf::RectangleShape increaseButtons[buttonCount];
	sf::RectangleShape decreaseButtons[buttonCount];
	sf::Text increaseTexts[buttonCount]; // Add array for increaseText
	sf::Text decreaseTexts[buttonCount]; // Add array for decreaseText
	const int spriteCount = 3;
	std::vector<sf::Sprite> coCaCoLa;
	std::vector<sf::Sprite> pepSi;
	std::vector<sf::Sprite> popCorn;

	for (int j = 0; j < spriteCount; j++) {
		for (int i = 0; i < spriteCount; ++i)
		{
			sf::Texture* tmptexture = new sf::Texture;
			if (!(*tmptexture).loadFromFile(to_string(i + j * 3) + ".png")) {
				if (!(*tmptexture).loadFromFile(to_string(i + j * 3) + ".jpg")) {
					return -1;
				}
			}
			sf::Sprite* tmpSprite = new sf::Sprite;
			(*tmpSprite).setTexture(*tmptexture);
			(*tmpSprite).setPosition(j * 300.f + 150, MENU.getPosition().y + 100);
			if (j == 0) {
				coCaCoLa.push_back(*tmpSprite);
			}
			else if (j == 1) {
				pepSi.push_back(*tmpSprite);

			}
			else {
				popCorn.push_back(*tmpSprite);
			}
		}
	}
	for (int i = 0; i < buttonCount; ++i)
	{
		sizeText[i].setFont(lora);
		sizeText[i].setCharacterSize(24);
		sizeText[i].setFillColor(sf::Color::Black);

		if (i == 0) {
			sizeText[i].setPosition(coCaCoLa[0].getPosition().x + 40, coCaCoLa[0].getPosition().y + 220);
		}
		else if (i == 1) {
			sizeText[i].setPosition(pepSi[0].getPosition().x + 40, pepSi[0].getPosition().y + 220);

		}
		else {
			sizeText[i].setPosition(popCorn[0].getPosition().x + 40, popCorn[0].getPosition().y + 220);

		}



		increaseButtons[i].setSize(sf::Vector2f(50, 50));
		increaseButtons[i].setFillColor(sf::Color::Transparent);
		increaseButtons[i].setOutlineColor(sf::Color::Black);

		increaseButtons[i].setPosition(sizeText[i].getPosition().x + 90, sizeText[i].getPosition().y);
		increaseButtons[i].setOutlineThickness(1.0f);

		// Set text for increase button
		increaseTexts[i].setFont(lora);
		increaseTexts[i].setCharacterSize(30);
		increaseTexts[i].setFillColor(sf::Color::Black);
		increaseTexts[i].setString(">");

		decreaseButtons[i].setSize(sf::Vector2f(50, 50));
		decreaseButtons[i].setFillColor(sf::Color::Transparent);
		decreaseButtons[i].setPosition(sizeText[i].getPosition().x - 70, sizeText[i].getPosition().y);
		decreaseButtons[i].setOutlineColor(sf::Color::Black);
		decreaseButtons[i].setOutlineThickness(1.0f);

		// Set text for decrease button
		decreaseTexts[i].setFont(lora);
		decreaseTexts[i].setCharacterSize(30);
		decreaseTexts[i].setPosition(decreaseButtons[i].getPosition().x + 15, decreaseButtons[i].getPosition().y);
		increaseTexts[i].setPosition(increaseButtons[i].getPosition().x + 15., decreaseTexts[i].getPosition().y);
		decreaseTexts[i].setFillColor(sf::Color::Black);
		decreaseTexts[i].setString("<");
	}

	for (int i = 0; i < buttonCount; ++i)
	{
		quantityTexts[i].setFillColor(sf::Color::Black);
		quantityTexts[i].setFont(lora);
		quantityTexts[i].setCharacterSize(24);
		quantityTexts[i].setPosition(sizeText[i].getPosition().x + 20, sizeText[i].getPosition().y + 70);

		for (int j = 0; j < 2; ++j)
		{
			buttons[i * 2 + j].setSize(sf::Vector2f(50, 50));
			buttons[i * 2 + j].setFillColor(j == 0 ? sf::Color::Green : sf::Color::Red);
			if (j % 2 == 0) {
				buttons[i * 2 + j].setPosition(increaseButtons[i].getPosition().x, quantityTexts[i].getPosition().y);

			}
			else {
				buttons[i * 2 + j].setPosition(decreaseButtons[i].getPosition().x, quantityTexts[i].getPosition().y);
			}
			buttonTexts[i * 2 + j].setFont(lora);
			buttonTexts[i * 2 + j].setCharacterSize(30);
			buttonTexts[i * 2 + j].setPosition(buttons[i * 2 + j].getPosition().x + 10, buttons[i & 2 + j].getPosition().y);
			buttonTexts[i * 2 + j].setFillColor(sf::Color::Black);
			// Dáº¥u "+" vÃ  "-"
			if (j == 0)
				buttonTexts[i * 2 + j].setString("+");
			else
				buttonTexts[i * 2 + j].setString("-");
		}
	}

	sf::Texture confirmTexture;
	if (!confirmTexture.loadFromFile("confirmButton.png")) {
		std::cerr << "Error loading confirm button texture!" << std::endl;
		return -1;
	}

	sf::Sprite confirmButton;
	confirmButton.setTexture(confirmTexture);
	confirmButton.setPosition(1000, 600);

	sf::Texture xacnhanTexture;
	if (!xacnhanTexture.loadFromFile("xacnhanButton.png")) {
		std::cerr << "Error loading xacnhan button texture!" << std::endl;
		return -1;
	}
	sf::Texture menuQuanTexture;
	if (!menuQuanTexture.loadFromFile("menuQuan.png")) {
		// Xá»­ lÃ½ lá»—i náº¿u khÃ´ng táº£i Ä‘Æ°á»£c hÃ¬nh áº£nh
		return -1;
	}

	// Táº¡o sprite vÃ  Ä‘áº·t texture cho sprite
	sf::Sprite menuQuan(menuQuanTexture);

	menuQuan.setPosition(1100, 50);
	menuQuan.setScale(0.65, 0.65);

	sf::Sprite xacnhanButton;
	xacnhanButton.setTexture(xacnhanTexture);
	xacnhanButton.setPosition(600, 735);
	bool clickedSuatChieu2 = 0;
	const int rows = 7;
	int suatChieuDaClicked = -1;
	int thuNgayDaClicked = -1;
	const int cols = 11;
	const float squareSize = 50;
	const float borderSize = 2.f;
	bool datGheNgoi[cols] = { 0 };
	int hangDatGhe = 18;
	string gheNgoiDaDat = "";
	int tongTienGheNgoi = 0;
	sf::RectangleShape gheNgoi[rows][cols];
	sf::Text textLoaiGhe[3];

	sf::RectangleShape loaiGheNgoi[3];
	for (int i = 0; i < 3; i++) {
		loaiGheNgoi[i].setSize(sf::Vector2f(squareSize, squareSize));
		loaiGheNgoi[i].setPosition(200, 200 + 70 * i);
		loaiGheNgoi[i].setOutlineThickness(1);
		textLoaiGhe[i].setPosition(loaiGheNgoi[i].getPosition().x + 70, 10 + loaiGheNgoi[i].getPosition().y);
		textLoaiGhe[i].setFillColor(sf::Color::Black); // Mï¿½u v?n b?n
		textLoaiGhe[i].setFont(lora);
		textLoaiGhe[i].setCharacterSize(18); // Kï¿½ch th??c font
		textLoaiGhe[i].setStyle(sf::Text::Bold); // 
	}
	loaiGheNgoi[0].setOutlineColor(sf::Color::Green);
	loaiGheNgoi[1].setOutlineColor(sf::Color::Blue);
	loaiGheNgoi[2].setOutlineColor(sf::Color::Magenta);
	textLoaiGhe[0].setString("GHE THUONG");
	textLoaiGhe[1].setString("GHE VIP");
	textLoaiGhe[2].setString("GHE COUP");

	bool daLoadGheNgoi = 0;

	sf::Text textGheNgoi[rows][cols];
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			string tmp = "";
			tmp += i + 48 + 17;
			tmp += to_string(j);
			textGheNgoi[i][j].setString(tmp);
			textGheNgoi[i][j].setFillColor(sf::Color::Black); // Mï¿½u v?n b?n
			textGheNgoi[i][j].setFont(lora);
			textGheNgoi[i][j].setCharacterSize(18); // Kï¿½ch th??c font
			textGheNgoi[i][j].setPosition(500 + j * (squareSize + borderSize + 5) + 5, 10 + 200 + i * (squareSize + borderSize + 5));
			gheNgoi[i][j].setSize(sf::Vector2f(squareSize, squareSize));
			gheNgoi[i][j].setOutlineThickness(1);
			gheNgoi[i][j].setPosition(500 + j * (squareSize + borderSize + 5), 200 + i * (squareSize + borderSize + 5));
			gheNgoi[i][j].setOutlineColor(sf::Color::Black);
		}
	}
	string selectedPhong = "";
	sf::Texture nextTexture;
	if (!nextTexture.loadFromFile("nextButton.png")) {
		std::cerr << "Error loading xacnhan button texture!" << std::endl;
		return -1;
	}

	sf::Sprite nextButton;
	nextButton.setTexture(nextTexture);
	nextButton.setPosition(400.f, 400.f);

	sf::Texture xacNhanDatVeTexture;
	if (!xacNhanDatVeTexture.loadFromFile("xacNhanDatVe.png")) {
		std::cerr << "Error loading xacnhan button texture!" << std::endl;
		return -1;
	}

	sf::Sprite xacNhanDatVeButton;
	xacNhanDatVeButton.setTexture(xacNhanDatVeTexture);
	xacNhanDatVeButton.setPosition(loaiGheNgoi[2].getPosition().x, gheNgoi[6][0].getPosition().y);
	bool datinhtienthungay = 0;

	bool Hover = 0;
	// count Page == 6 
	int giaVe = 0;
	now ngayDat;
	string bapNuoc = "";
	string tenPhim = "";
	Time ngayChieu;
	string gheNgoiVe = "";
	string loaiGhe = "";
	bool daThemVe = 0;
	bool gheTrongFull = 1;
	int array2D[rows1][cols1];
	int arrayK = 0, arrayO = 0;
	bool daVeQR = 0;

	sf::Sprite enlargedSprite; // Use the same texture for the enlarged sprite

	sf::RectangleShape enlargedArea(sf::Vector2f(100.f, 100.f)); // Set the initial size of the enlarged area
	enlargedArea.setOutlineColor(sf::Color::Red);
	enlargedArea.setOutlineThickness(2.f);

	sf::Texture movieSpriteTexture;
	if (!movieSpriteTexture.loadFromFile("movieSprite.png")) {
		std::cerr << "Error loading movieSpriteTexture texture!" << std::endl;
		return -1;
	}
	sf::Sprite movieSprite;
	movieSprite.setTexture(movieSpriteTexture);
	movieSprite.setScale(1, 0.675);
	movieSprite.setPosition(0, 680);

	sf::RectangleShape khungVe(sf::Vector2f(600, 1200));
	khungVe.setPosition(((window.getSize().x - khungVe.getGlobalBounds().getSize().x) / 2), 20);

	// Thiáº¿t láº­p mÃ u ná»n lÃ  tráº¯ng
	khungVe.setFillColor(sf::Color::White);

	// Thiáº¿t láº­p mÃ u viá»n lÃ  Ä‘en
	khungVe.setOutlineColor(sf::Color::Black);

	// Thiáº¿t láº­p Ä‘á»™ dÃ y cá»§a Ä‘Æ°á»ng viá»n
	khungVe.setOutlineThickness(2.0f);




	sf::Text contentSprite[9];

	for (int i = 0; i < 5; i++) {
		contentSprite[i].setFont(lora);
		contentSprite[i].setCharacterSize(28); // Kï¿½ch th??c font
		contentSprite[i].setFillColor(sf::Color::White); // Mï¿½u v?n b?n
		contentSprite[i].setPosition(370 * i + 300, movieSprite.getPosition().y);
	}



	for (int i = 5; i < 7; i++) {
		contentSprite[i].setFont(lora);
		contentSprite[i].setCharacterSize(28); // Kï¿½ch th??c font
		contentSprite[i].setFillColor(sf::Color::White); // Mï¿½u v?n b?n
		contentSprite[i].setPosition(370 * (i - 5) + 300, 40 + movieSprite.getPosition().y);
	}

	contentSprite[6].setPosition(370 * (6 - 5) + 130, 40 + movieSprite.getPosition().y);
	contentSprite[1].setPosition(370 * (6 - 5) + 130, 80 + movieSprite.getPosition().y);
	contentSprite[2].setPosition(370 * 2 + 300 + 150, movieSprite.getPosition().y);
	contentSprite[3].setPosition(370 * (6 - 5) + 130, 120 + movieSprite.getPosition().y);
	contentSprite[4].setPosition(370 * 2 + 300 + 150, movieSprite.getPosition().y + 40);
	contentSprite[0].setStyle(sf::Text::Bold);

	sf::Texture texturePhimPage6;

	sf::Sprite spritePhimPage6;

	int selectedSuatChieu = 0;


	sf::Text contentVe[9];

	for (int i = 0; i < 4; i++) {
		contentVe[i].setFont(Freck);
		contentVe[i].setCharacterSize(32); // Kï¿½ch th??c font
		contentVe[i].setFillColor(sf::Color::Black); // Mï¿½u v?n b?n
		contentVe[i].setPosition((window.getSize().x - contentVe[i].getGlobalBounds().getSize().x) / 2 - 150, i * 50 + khungVe.getPosition().y + 285);
	}
	for (int i = 4; i < 9; i++) {
		contentVe[i].setFont(Freck);
		contentVe[i].setCharacterSize(32); // Kï¿½ch th??c font
		contentVe[i].setFillColor(sf::Color::Black); // Mï¿½u v?n b?n
		contentVe[i].setPosition((window.getSize().x - contentVe[i].getGlobalBounds().getSize().x) / 2 - 150, 3 * 50 + khungVe.getPosition().y + 215 + i * 50);
	}
	contentVe[0].setCharacterSize(33); // Kï¿½ch th??c font

	contentVe[0].setStyle(sf::Text::Bold);


	while (window.isOpen()) {
		now rightNow;
		sf::Event event;
		//admin1.nhapphongchieu("DanhSachPhong.txt");
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					// Láº¥y vá»‹ trÃ­ cá»§a chuá»™t khi nháº¥n
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
					if (backButton.getGlobalBounds().contains(sf::Vector2f(mousePosition))) {
						if (countPage != 1) {
							if (countPage == 2) {
								searchBar.setPosition(searchBar.getPosition().x, 20);
								phimdangchieu.setPosition(phimdangchieu.getPosition().x, 221 + 50);
							}
							countPage--;
						}

					}
				}
			}
			if (countPage == 1) {

				clickedSuatChieu = 0;
				daloadphimchieu = 0;
				backButton.setPosition(5, searchBar.getPosition().y);
				if (!daloadmenuphim) {
					columnnow = 1;
					rownow = 1;
					string tmp = "000";
					for (int i = 0; i < admin1.getsophim(); i++) {
						if (!(texturePhim[i]).loadFromFile(admin1.getdanhsachphim()[i].getlinkanh())) {

						}
						tmp = admin::increaseString(tmp);
						posterPhim[i].setPosition(167.5 * columnnow + (columnnow - 1) * 270, 385.2 * (rownow - 1) + phimdangchieu.getPosition().y + 100 + (rownow - 1) * 200);
						borderPosterPhim[i].setPosition(167.5 * columnnow + (columnnow - 1) * 270, 385.2 * (rownow - 1) + phimdangchieu.getPosition().y + 100 + (rownow - 1) * 200);
						posterPhim[i].setTexture(texturePhim[i]);
						float scaleX = 270 / (posterPhim[i]).getLocalBounds().width;
						float scaleY = 385.2 / (posterPhim[i]).getLocalBounds().height;
						(posterPhim[i]).setScale(scaleX, scaleY);
						columnnow++;


						if (columnnow > 3) {
							columnnow = 1;
							rownow++;
						}
						daloadmenuphim = 1;
						daloadtheloai = 0;
					}
					for (int i = 0; i < admin1.getsophim(); i++) {
						int textDistance[4];
						for (int p = 0; p < 4; p++) {
							textDistance[p] = 0;
						}
						std::string tmpText;
						tmpText = admin1.getdanhsachphim()[i].gettenphim();
						tenphim[i].setString(chinhSuaText(tmpText, textDistance, 0, 1));
						tenphim[i].setFont(lora);
						tenphim[i].setCharacterSize(20);
						tenphim[i].setStyle(sf::Text::Bold);
						tenphim[i].setFillColor(sf::Color::Black);
						tenphim[i].setPosition(posterPhim[i].getPosition().x + (posterPhim[i].getGlobalBounds().width - tenphim[i].getGlobalBounds().width) / 2, 385.2 + posterPhim[i].getPosition().y + 15);

						tmpText = admin1.getdanhsachphim()[i].gettheloai();
						tmpText = "The loai : " + tmpText;
						thongtinphim1[i].second.setString(chinhSuaText(tmpText, textDistance, 1, 0));
						thongtinphim1[i].second.setFont(lora);
						thongtinphim1[i].second.setCharacterSize(20);
						thongtinphim1[i].second.setFillColor(sf::Color::Black);
						thongtinphim1[i].second.setPosition(posterPhim[i].getPosition().x + (posterPhim[i].getGlobalBounds().width - thongtinphim1[i].second.getGlobalBounds().width) / 2, textDistance[0] * 4 + tenphim[i].getPosition().y + 20);

						tmpText = to_string(admin1.getdanhsachphim()[i].getthoiluong());
						tmpText = "Thoi luong : " + tmpText + " phut";
						thongtinphim2[i].setString(chinhSuaText(tmpText, textDistance, 2, 0));
						thongtinphim2[i].setFont(lora);
						thongtinphim2[i].setCharacterSize(20);
						thongtinphim2[i].setFillColor(sf::Color::Black);
						thongtinphim2[i].setPosition(posterPhim[i].getPosition().x + (posterPhim[i].getGlobalBounds().width - thongtinphim2[i].getGlobalBounds().width) / 2, textDistance[1] * 4 + thongtinphim1[i].second.getPosition().y + 20);

						tmpText = "Khoi Chieu : " + to_string(admin1.getdanhsachphim()[i].getkhoichieu().getngay()) + "-" + to_string(admin1.getdanhsachphim()[i].getkhoichieu().getthang()) + "-" + to_string(admin1.getdanhsachphim()[i].getkhoichieu().getnam());
						thongtinphim3[i].setString(chinhSuaText(tmpText, textDistance, 3, 0));
						thongtinphim3[i].setFont(lora);
						thongtinphim3[i].setCharacterSize(20);
						thongtinphim3[i].setFillColor(sf::Color::Black);
						thongtinphim3[i].setPosition(posterPhim[i].getPosition().x + (posterPhim[i].getGlobalBounds().width - thongtinphim3[i].getGlobalBounds().width) / 2, textDistance[2] * 4 + thongtinphim2[i].getPosition().y + 20);
						int tongDistance = textDistance[0] + textDistance[1] + textDistance[2] + textDistance[3];
						if (tongDistance != 0) {
							int rowGan = i + (3 - (i % 3));
							for (int o = rowGan; o < soPhim; o++) {
								borderPosterPhim[o].setPosition(borderPosterPhim[o].getPosition().x, borderPosterPhim[o].getPosition().y + tongDistance);
								posterPhim[o].setPosition(posterPhim[o].getPosition().x, posterPhim[o].getPosition().y + tongDistance);
							}
						}
					}

				}

				if (event.type == sf::Event::MouseWheelScrolled) {
					if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
						if (event.mouseWheelScroll.delta > 0) {


							if (searchBar.getPosition().y != 20)
							{
								phimdangchieu.move(0, 80);
								for (int i = 0; i < soPhim; i++) {
									posterPhim[i].move(0, 80);
									borderPosterPhim[i].move(0, 80);
									tenphim[i].move(0, 80);
									thongtinphim1[i].second.move(0, 80);
									thongtinphim2[i].move(0, 80);
									thongtinphim3[i].move(0, 80);
								}
								viTriSearchBar += 80;
								searchBar.move(0, 80);
								searchBoxText.move(0, 80);
								line.move(0, 80);
							}

						}
						else if (event.mouseWheelScroll.delta < 0) {
							phimdangchieu.move(0, -80);

							for (int i = 0; i < soPhim; i++) {
								posterPhim[i].move(0, -80);
								borderPosterPhim[i].move(0, -80);
								tenphim[i].move(0, -80);
								thongtinphim1[i].second.move(0, -80);
								thongtinphim2[i].move(0, -80);
								thongtinphim3[i].move(0, -80);
							}
							viTriSearchBar -= 80;
							searchBar.move(0, -80);
							searchBoxText.move(0, -80);
							line.move(0, -80);
						}
					}
				}
				else if (event.type == sf::Event::MouseMoved) {
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
					isHovered = false;
					// Kiá»ƒm tra tá»«ng sprite trong máº£ng
					for (int i = 0; i < soPhim; ++i) {
						if (posterPhim[i].getGlobalBounds().contains(sf::Vector2f(mousePosition)) || thongtinphim1[i].second.getGlobalBounds().contains(sf::Vector2f(mousePosition)) || thongtinphim1[i].second.getGlobalBounds().contains(sf::Vector2f(mousePosition)) || thongtinphim2[i].getGlobalBounds().contains(sf::Vector2f(mousePosition)) || thongtinphim3[i].getGlobalBounds().contains(sf::Vector2f(mousePosition))) {
							// Náº¿u con trá» chuá»™t hover vÃ o sprite thá»© i
							// Thá»±c hiá»‡n cÃ¡c hÃ nh Ä‘á»™ng mong muá»‘n, vÃ­ dá»¥: thay Ä‘á»•i mÃ u sprite
							posterPhim[i].setColor(sf::Color(200, 200, 200));
							isHovered = true;
						}
						else {
							posterPhim[i].setColor(sf::Color(255, 255, 255));
						}
						if (isHovered) {
							window.setMouseCursor(handPointer);
						}
						else {
							window.setMouseCursor(arrowPointer);

						}
					}
				}
				else if (event.type == sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						// Láº¥y vá»‹ trÃ­ cá»§a chuá»™t khi nháº¥n
						sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

						// Kiá»ƒm tra xem vá»‹ trÃ­ chuá»™t cÃ³ náº±m trong pháº¡m vi cá»§a sprite khÃ´ng
						for (int i = 0; i < soPhim; ++i) {
							coTheBanCungThich.setPosition((window.getSize().x - coTheBanCungThich.getGlobalBounds().width) / 2, 700);
							noiDungPhim.setPosition(110, 0 + 90 + 30);
							if (borderPosterPhim[i].getGlobalBounds().contains(sf::Vector2f(mousePosition)) || thongtinphim1[i].second.getGlobalBounds().contains(sf::Vector2f(mousePosition)) || thongtinphim2[i].getGlobalBounds().contains(sf::Vector2f(mousePosition)) || thongtinphim3[i].getGlobalBounds().contains(sf::Vector2f(mousePosition))) {
								selectedMovie = (*(admin1.getdanhsachphim() + i)).getid();
								selectedPhimNumber = i;
								window.setMouseCursor(arrowPointer);
								selectedPhim = admin1.getdanhsachphim()[admin1.getphimtuid(selectedMovie)];

								for (int m = 0; m < 2; m++) {
									contentText[m].setFont(lora);
									contentText[m].setCharacterSize(20);
									contentText[m].setFillColor(sf::Color::Black);
									contentText[m].setPosition(500, 50 * m + CGV.getPosition().y + 350);
								}

								int A[2];
								contentText[0].setString("Khoi Chieu Den : " + to_string(selectedPhim.gethankhoichieu().getngay()) + "-" + to_string(selectedPhim.gethankhoichieu().getthang()) + "-" + to_string(selectedPhim.gethankhoichieu().getnam()));
								contentText[1].setString(chinhSuaText(selectedPhim.getgioithieuphim(), A, 18, 0));

								countPage = 2;
							}
						}
					}
				}
			}
			else if (countPage == 2) {
				clickedSuatChieu = 0;
				if (areGenresMatching("Kinh Di", selectedPhim.gettheloai())) {
					noiDungPhim.setFont(horror);
				}
				else if (areGenresMatching("Khoa Hoc", selectedPhim.gettheloai())) {
					noiDungPhim.setFont(tech);

				}

				else if (areGenresMatching("Tinh Cam", selectedPhim.gettheloai())) {
					noiDungPhim.setFont(love);

				}

				else {
					noiDungPhim.setFont(lora);

				}
				backButton.setPosition(5, CGV.getPosition().y);
				if (!daloadphimchieu) {
					borderPosterPhim[selectedPhimNumber].setPosition(100, 50 + noiDungPhim.getPosition().y + 50);
					posterPhim[selectedPhimNumber].setPosition(100, 50 + noiDungPhim.getPosition().y + 50);
					tenphim[selectedPhimNumber].setPosition(500, 50 + noiDungPhim.getPosition().y + 50);
					thongtinphim1Tmp.setString("The Loai : " + admin1.getdanhsachphim()[selectedPhimNumber].gettheloai());
					thongtinphim1Tmp.setPosition(500, 50 + noiDungPhim.getPosition().y + 50 + 50);
					thongtinphim2[selectedPhimNumber].setPosition(500, 50 + noiDungPhim.getPosition().y + 50 + 85);

					thongtinphim3[selectedPhimNumber].setPosition(500, 50 + noiDungPhim.getPosition().y + 50 + 120);
					daloadphimchieu = 1;
				}
				if (!daloadtheloai) {
					columnnow = 1;
					rownow = 1;
					for (int i = 0; i < admin1.getsophim(); i++) {
						if (areGenresMatching(admin1.getdanhsachphim()[i].gettheloai(), selectedPhim.gettheloai()) && i != selectedPhimNumber) {
							countTheLoai.push_back(i);
							if (!(texturePhim[i]).loadFromFile(admin1.getdanhsachphim()[i].getlinkanh())) {

							}
							posterPhim[i].setPosition(167.5 * columnnow + (columnnow - 1) * 270, coTheBanCungThich.getPosition().y + 100 + 385.2 * (rownow - 1) + (rownow - 1) * 200);
							borderPosterPhim[i].setPosition(167.5 * columnnow + (columnnow - 1) * 270, 385.2 * (rownow - 1) + coTheBanCungThich.getPosition().y + 100 + (rownow - 1) * 200);
							posterPhim[i].setTexture(texturePhim[i]);
							float scaleX = 270.0 / (posterPhim[i]).getLocalBounds().width;
							float scaleY = 385.2 / (posterPhim[i]).getLocalBounds().height;
							(posterPhim[i]).setScale(scaleX, scaleY);
							columnnow++;
							if (columnnow > 3) {
								columnnow = 1;
								rownow++;
							}
							int textDistance[4];
							for (int p = 0; p < 4; p++) {
								textDistance[p] = 0;
							}
							std::string tmpText;
							tmpText = admin1.getdanhsachphim()[i].gettenphim();
							tenphim[i].setString(chinhSuaText(tmpText, textDistance, 0, 1));
							tenphim[i].setFont(lora);
							tenphim[i].setCharacterSize(20);
							tenphim[i].setStyle(sf::Text::Bold);
							tenphim[i].setFillColor(sf::Color::Black);
							tenphim[i].setPosition(posterPhim[i].getPosition().x + (posterPhim[i].getGlobalBounds().width - tenphim[i].getGlobalBounds().width) / 2, 385.2 + posterPhim[i].getPosition().y + 15);

							tmpText = admin1.getdanhsachphim()[i].gettheloai();
							tmpText = "The loai : " + tmpText;
							thongtinphim1[i].second.setString(chinhSuaText(tmpText, textDistance, 1, 0));
							thongtinphim1[i].second.setFont(lora);
							thongtinphim1[i].second.setCharacterSize(20);
							thongtinphim1[i].second.setFillColor(sf::Color::Black);
							thongtinphim1[i].second.setPosition(posterPhim[i].getPosition().x + (posterPhim[i].getGlobalBounds().width - thongtinphim1[i].second.getGlobalBounds().width) / 2, textDistance[0] * 4 + tenphim[i].getPosition().y + 20);

							tmpText = to_string(admin1.getdanhsachphim()[i].getthoiluong());
							tmpText = "Thoi luong : " + tmpText + " phut";
							thongtinphim2[i].setString(chinhSuaText(tmpText, textDistance, 2, 0));
							thongtinphim2[i].setFont(lora);
							thongtinphim2[i].setCharacterSize(20);
							thongtinphim2[i].setFillColor(sf::Color::Black);
							thongtinphim2[i].setPosition(posterPhim[i].getPosition().x + (posterPhim[i].getGlobalBounds().width - thongtinphim2[i].getGlobalBounds().width) / 2, textDistance[1] * 4 + thongtinphim1[i].second.getPosition().y + 20);

							tmpText = "Khoi Chieu : " + to_string(admin1.getdanhsachphim()[i].getkhoichieu().getngay()) + "-" + to_string(admin1.getdanhsachphim()[i].getkhoichieu().getthang()) + "-" + to_string(admin1.getdanhsachphim()[i].getkhoichieu().getnam());
							thongtinphim3[i].setString(chinhSuaText(tmpText, textDistance, 3, 0));
							thongtinphim3[i].setFont(lora);
							thongtinphim3[i].setCharacterSize(20);
							thongtinphim3[i].setFillColor(sf::Color::Black);
							thongtinphim3[i].setPosition(posterPhim[i].getPosition().x + (posterPhim[i].getGlobalBounds().width - thongtinphim3[i].getGlobalBounds().width) / 2, textDistance[2] * 4 + thongtinphim2[i].getPosition().y + 20);
							int tongDistance = textDistance[0] + textDistance[1] + textDistance[2] + textDistance[3];
							if (tongDistance != 0) {
								int rowGan = i + (3 - (i % 3));
								for (int o = rowGan; o < soPhim; o++) {
									borderPosterPhim[o].setPosition(borderPosterPhim[o].getPosition().x, borderPosterPhim[o].getPosition().y + tongDistance);
									posterPhim[o].setPosition(posterPhim[o].getPosition().x, posterPhim[o].getPosition().y + tongDistance);
								}
							}

						}
						daloadtheloai = 1;
						daloadmenuphim = 0;
					}
				}
				enlargedSprite.setTexture((texturePhim[selectedPhimNumber]));



				if (event.type == sf::Event::MouseWheelScrolled) {



					if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
						if (event.mouseWheelScroll.delta > 0) {
							if (CGV.getPosition().y != 20)
							{
								noiDungPhim.move(0, 80);
								thongtinphim1Tmp.move(0, 80);
								for (int i = 0; i < countTheLoai.size(); i++) {
									posterPhim[countTheLoai[i]].move(0, 80);
									borderPosterPhim[countTheLoai[i]].move(0, 80);
									tenphim[countTheLoai[i]].move(0, 80);
									thongtinphim1[countTheLoai[i]].second.move(0, 80);
									thongtinphim2[countTheLoai[i]].move(0, 80);
									thongtinphim3[countTheLoai[i]].move(0, 80);
								}
								posterPhim[selectedPhimNumber].move(0, 80);
								borderPosterPhim[selectedPhimNumber].move(0, 80);
								tenphim[selectedPhimNumber].move(0, 80);
								thongtinphim1[selectedPhimNumber].second.move(0, 80);
								thongtinphim2[selectedPhimNumber].move(0, 80);
								thongtinphim3[selectedPhimNumber].move(0, 80);
								coTheBanCungThich.move(0, 80);
								orderButton.move(0, 80);
								for (int k = 0; k < 2; k++) {
									contentText[k].move(0, 80);

								}

								CGV.move(0, 80);
								backButton.move(0, 80);
							}

						}
						else if (event.mouseWheelScroll.delta < 0) {
							phimdangchieu.move(0, -80);
							CGV.move(0, -80);
							thongtinphim1Tmp.move(0, -80);
							for (int i = 0; i < countTheLoai.size(); i++) {
								posterPhim[countTheLoai[i]].move(0, -80);
								borderPosterPhim[countTheLoai[i]].move(0, -80);
								tenphim[countTheLoai[i]].move(0, -80);
								thongtinphim1[countTheLoai[i]].second.move(0, -80);
								thongtinphim2[countTheLoai[i]].move(0, -80);
								thongtinphim3[countTheLoai[i]].move(0, -80);
							}
							posterPhim[selectedPhimNumber].move(0, -80);
							borderPosterPhim[selectedPhimNumber].move(0, -80);
							tenphim[selectedPhimNumber].move(0, -80);
							thongtinphim1[selectedPhimNumber].second.move(0, -80);
							thongtinphim2[selectedPhimNumber].move(0, -80);
							thongtinphim3[selectedPhimNumber].move(0, -80);
							backButton.move(0, -80);
							coTheBanCungThich.move(0, -80);
							orderButton.move(0, -80);
							noiDungPhim.move(0, -80);
							for (int k = 0; k < 2; k++) {
								contentText[k].move(0, -80);
							}

						}
					}
				}
				else if (event.type == sf::Event::MouseMoved) {
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

					enlargedArea.setPosition(mousePosition.x - enlargedArea.getSize().x / 2, mousePosition.y - enlargedArea.getSize().y / 2);
					enlargedArea.setFillColor(sf::Color::Transparent);
					// Check if the mouse is over the sprite
					if (posterPhim[selectedPhimNumber].getGlobalBounds().contains(sf::Vector2f(mousePosition))) {

						enlargedArea.setScale(1, 1);

						enlargedSprite.setScale(1.5, 1.5);
						enlargedSprite.setTextureRect(sf::IntRect(((enlargedArea.getGlobalBounds().getPosition().x - posterPhim[selectedPhimNumber].getGlobalBounds().getPosition().x) / posterPhim[selectedPhimNumber].getGlobalBounds().width) * enlargedSprite.getGlobalBounds().width + enlargedArea.getPosition().x / 3, ((enlargedArea.getGlobalBounds().getPosition().y - posterPhim[selectedPhimNumber].getGlobalBounds().getPosition().y) / posterPhim[selectedPhimNumber].getGlobalBounds().height) * enlargedSprite.getGlobalBounds().height + enlargedArea.getPosition().y / 2, 1.2 * posterPhim[selectedPhimNumber].getGlobalBounds().width, 1.2 * posterPhim[selectedPhimNumber].getGlobalBounds().height));

						enlargedSprite.setPosition(posterPhim[selectedPhimNumber].getPosition().x + posterPhim[selectedPhimNumber].getGlobalBounds().width, posterPhim[selectedPhimNumber].getPosition().y);
						enlargedArea.setScale(1.2, 1.85);
						Hover = 1;
					}
					else {
						// If not, hide the enlarged sprite
						enlargedSprite.setScale(0.f, 0.f);
						Hover = 0;
					}
					isHovered = false;
					// Kiá»ƒm tra tá»«ng sprite trong máº£ng
					for (int i = 0; i < countTheLoai.size(); ++i) {
						if (posterPhim[countTheLoai[i]].getGlobalBounds().contains(sf::Vector2f(mousePosition)) || thongtinphim1[countTheLoai[i]].second.getGlobalBounds().contains(sf::Vector2f(mousePosition)) || thongtinphim1[countTheLoai[i]].second.getGlobalBounds().contains(sf::Vector2f(mousePosition)) || thongtinphim2[countTheLoai[i]].getGlobalBounds().contains(sf::Vector2f(mousePosition)) || thongtinphim3[countTheLoai[i]].getGlobalBounds().contains(sf::Vector2f(mousePosition))) {
							// Náº¿u con trá» chuá»™t hover vÃ o sprite thá»© i
							// Thá»±c hiá»‡n cÃ¡c hÃ nh Ä‘á»™ng mong muá»‘n, vÃ­ dá»¥: thay Ä‘á»•i mÃ u sprite
							posterPhim[countTheLoai[i]].setColor(sf::Color(200, 200, 200));
							isHovered = true;
						}
						else {
							posterPhim[countTheLoai[i]].setColor(sf::Color(255, 255, 255));
						}
						if (isHovered) {
							window.setMouseCursor(handPointer);
						}
						else {
							window.setMouseCursor(arrowPointer);

						}
					}
				}
				else if (event.type == sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						// Láº¥y vá»‹ trÃ­ cá»§a chuá»™t khi nháº¥n
						sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
						daloadphimchieu = 0;
						// Kiá»ƒm tra xem vá»‹ trÃ­ chuá»™t cÃ³ náº±m trong pháº¡m vi cá»§a sprite khÃ´ng
						for (int i = 0; i < countTheLoai.size(); ++i) {
							if (borderPosterPhim[countTheLoai[i]].getGlobalBounds().contains(sf::Vector2f(mousePosition)) || thongtinphim1[countTheLoai[i]].second.getGlobalBounds().contains(sf::Vector2f(mousePosition)) || thongtinphim2[countTheLoai[i]].getGlobalBounds().contains(sf::Vector2f(mousePosition)) || thongtinphim3[countTheLoai[i]].getGlobalBounds().contains(sf::Vector2f(mousePosition))) {
								daloadtheloai = 0;
								daloadphimchieu = 0;
								daloadmenuphim = 0;
								selectedMovie = (*(admin1.getdanhsachphim() + countTheLoai[i])).getid();
								selectedPhimNumber = countTheLoai[i];
								window.setMouseCursor(arrowPointer);
								selectedPhim = admin1.getdanhsachphim()[admin1.getphimtuid(selectedMovie)];
								contentText[0].setString("Khoi Chieu Den : " + to_string(selectedPhim.gethankhoichieu().getngay()) + "-" + to_string(selectedPhim.gethankhoichieu().getthang()) + "-" + to_string(selectedPhim.gethankhoichieu().getnam()));
								int A[2];
								contentText[1].setString(chinhSuaText(selectedPhim.getgioithieuphim(), A, 18, 0));

								for (int k = 0; k < 2; k++) {
									contentText[k].setFont(lora);
									contentText[k].setCharacterSize(20);
									contentText[k].setFillColor(sf::Color::Black);
									contentText[k].setPosition(500, 50 * k + CGV.getPosition().y + 350);
								}
								countTheLoai.clear();
								break;
							}


						}
						if (orderButton.getGlobalBounds().contains(sf::Vector2f(mousePosition))) {
							// Thá»±c hiá»‡n hÃ nh Ä‘á»™ng khi orderButton Ä‘Æ°á»£c nháº¥n
							countPage++;
							// Äáº·t hÃ nh Ä‘á»™ng báº¡n muá»‘n thá»±c hiá»‡n khi orderButton Ä‘Æ°á»£c nháº¥n
						}
					}

				}


			}
			else if (countPage == 3) {
				hangDatGhe = 18;
				for (int i = 0; i < 11; i++) {
					datGheNgoi[i] = 0;
				}

				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
					// Kiá»ƒm tra click
					for (int i = 0; i < numRectangles; i++) {
						if (thuNgayBorder[i].getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
							// Xá»­ lÃ½ sá»± kiá»‡n khi click vÃ o Ä‘Ã¢y
							selectedNgay = i;
							clickedSuatChieu = 1;
							suatChieu.clear();
							if (thuNgayDaClicked != -1) {
								thuNgayBorder[thuNgayDaClicked].setFillColor(sf::Color::Transparent);

								thuNgayDaClicked = i;
								thuNgayBorder[thuNgayDaClicked].setFillColor(sf::Color(200, 200, 200));

							}
							else {
								thuNgayDaClicked = i;
								thuNgayBorder[thuNgayDaClicked].setFillColor(sf::Color(200, 200, 200));
							}
							for (int k = 0; k < selectedPhim.getsosuatchieu(); k++) {
								{
									if (selectedPhim.getdanhsachsuatchieu()[k].getthoigianchieu() == admin1.getsuat(selectedNgay, 0, 0).getthoigianchieu()) {
										sf::Text suatchieuTmp;
										suatchieuTmp.setFont(lora);
										suatchieuTmp.setCharacterSize(30);
										suatchieuTmp.setFillColor(sf::Color::Black);
										if (selectedPhim.getdanhsachsuatchieu()[k].getthoigianchieu().getgio() < 10) {
											if (selectedPhim.getdanhsachsuatchieu()[k].getthoigianchieu().getphut() < 10) {
												suatchieuTmp.setString("0" + to_string(selectedPhim.getdanhsachsuatchieu()[k].getthoigianchieu().getgio()) + ":" + "0" + to_string(selectedPhim.getdanhsachsuatchieu()[k].getthoigianchieu().getphut()));
											}
											else {
												suatchieuTmp.setString("0" + to_string(selectedPhim.getdanhsachsuatchieu()[k].getthoigianchieu().getgio()) + ":" + to_string(selectedPhim.getdanhsachsuatchieu()[k].getthoigianchieu().getphut()));
											}
										}
										else {
											suatchieuTmp.setString(to_string(selectedPhim.getdanhsachsuatchieu()[k].getthoigianchieu().getgio()) + ":" + to_string(selectedPhim.getdanhsachsuatchieu()[k].getthoigianchieu().getphut()));
										}
										suatchieuTmp.setPosition(0, 100);
										suatChieu.push_back(suatchieuTmp);

									}

								}
							}


						}


					}

					for (int r = 0; r < suatChieu.size(); r++) {
						// Create rectangle for the border
						sf::RectangleShape tmpSuatChieuBorder;
						suatChieu[r].setPosition(120 * r + thuNgayBorder[0].getPosition().x, thuNgayBorder[6].getPosition().y + 100);
						tmpSuatChieuBorder.setSize(sf::Vector2f(suatChieu[r].getGlobalBounds().width + 20, suatChieu[r].getGlobalBounds().height + 20));
						tmpSuatChieuBorder.setPosition(suatChieu[r].getPosition().x, suatChieu[r].getPosition().y);
						tmpSuatChieuBorder.setFillColor(sf::Color::Transparent);
						tmpSuatChieuBorder.setOutlineColor(sf::Color::White);
						tmpSuatChieuBorder.setOutlineThickness(2.0f);
						suatChieuBorder.push_back(tmpSuatChieuBorder);
					}
					for (int i = 0; i < buttonCount; ++i)
					{
						for (int j = 0; j < 2; ++j)
						{
							if (buttons[i * 2 + j].getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
							{
								quantities[i][sizeQuantities[i]] += (j == 0) ? 1 : -1;
							}
						}
						if (increaseButtons[i].getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
						{
							if (sizeQuantities[i] < 2) {
								for (int k = 0; k < 3; k++) {
									quantities[i][k] = 0;
								}
								sizeQuantities[i]++;
							}

						}
						else if (decreaseButtons[i].getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
						{
							if (sizeQuantities[i] > 0) {
								sizeQuantities[i]--;
								for (int k = 0; k < 3; k++) {
									quantities[i][k] = 0;
								}
							}
						}
					}
					for (int i = 0; i < suatChieuBorder.size(); i++) {
						if (suatChieuBorder[i].getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
							if (suatChieuDaClicked != -1) {
								suatChieuBorder[suatChieuDaClicked].setFillColor(sf::Color::Transparent);

								suatChieuDaClicked = i;
								suatChieuBorder[suatChieuDaClicked].setFillColor(sf::Color(200, 200, 200));

							}
							else {
								suatChieuDaClicked = i;
								suatChieuBorder[suatChieuDaClicked].setFillColor(sf::Color(200, 200, 200));
							}
							string tmp1 = "";
							for (int n = 0; n < 2; n++) {
								tmp1 += suatChieu[i].getString()[n];
							}
							string tmp2 = "";
							for (int n = 3; n < 5; n++) {
								tmp2 += suatChieu[i].getString()[n];
							}
							clickedSuatChieu2 = 1;

							for (int j = 0; j < selectedPhim.getsosuatchieu(); j++) {
								if (selectedNgay == (selectedPhim.getdanhsachsuatchieu()[j].getthoigianchieu().getngay() - rightNow.getngay()) && selectedPhim.getdanhsachsuatchieu()[j].getthoigianchieu().getgio() == stoi(tmp1) && selectedPhim.getdanhsachsuatchieu()[j].getthoigianchieu().getphut() == stoi(tmp2)) {
									selectedPhong = selectedPhim.getdanhsachsuatchieu()[j].getidphong();
									ngayChieu = selectedPhim.getdanhsachsuatchieu()[j].getthoigianchieu();
									selectedSuatChieu = j;
								}
							}
							break;
						}
					}

					if (clickedSuatChieu2) {
						if (confirmButton.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
						{
							for (int i = 0; i < 3; i++) {
								for (int j = 0; j < 3; j++) {
									gioHangMenu[i * 3 + j] += quantities[i][j];
									quantities[i][j] = 0;
								}
							}
						}
						if (xacnhanButton.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
						{
							countPage++;
						}
					}
				}
				if (event.type == sf::Event::MouseMoved) {
					// Kiá»ƒm tra hover
					for (int i = 0; i < numRectangles; ++i) {
						if (thuNgayBorder[i].getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
							thuNgayBorder[i].setOutlineColor(sf::Color::Black);
						}
						else {
							thuNgayBorder[i].setOutlineColor(sf::Color::White);
						}
					}

					if (clickedSuatChieu) {
						for (int i = 0; i < suatChieuBorder.size(); i++) {
							if (suatChieuBorder[i].getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
								suatChieuBorder[i].setOutlineColor(sf::Color::Black);
							}
							else {
								suatChieuBorder[i].setOutlineColor(sf::Color::White);
							}
						}

					}

				}


			}
			else if (countPage == 4) {
				daVeQR = 0;
				datinhtienthungay = 0;
				phong selectedPhong2 = admin1.getphong(selectedPhong);
				contentSprite[3].setString("Phong Chieu " + to_string(selectedPhong[1] - 48));
				for (int i = 0; i < rows; i++) {
					for (int j = 0; j < cols; j++) {
						if (selectedPhong2.getghengoi(i, j)) {
							gheNgoi[i][j].setFillColor(sf::Color::Red);
						}
					}
				}
				if (event.type == sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						// Láº¥y vá»‹ trÃ­ cá»§a chuá»™t khi nháº¥n
						sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

						// Kiá»ƒm tra xem vá»‹ trÃ­ chuá»™t cÃ³ náº±m trong pháº¡m vi cá»§a sprite khÃ´ng
						for (int i = 0; i < rows; ++i) {
							for (int j = 0; j < cols; j++)
							{
								if (gheNgoi[i][j].getGlobalBounds().contains(sf::Vector2f(mousePosition))) {

									gheTrongFull = 0;
									for (int l = 0; l < 11; l++) {
										if (datGheNgoi[l]) {
											gheTrongFull = 1;
										}
									}
									if (!gheTrongFull) {
										hangDatGhe = 18;
									}
									if (!selectedPhong2.getghengoi(i, j)) {
										if ((!datGheNgoi[j] && hangDatGhe == 18) || (!datGheNgoi[j] && (hangDatGhe == i))) {
											hangDatGhe = i;
											if (i == 0 || i == 1 || i == 5 || i == 6) {

												gheNgoi[i][j].setFillColor(sf::Color::Green);
												datGheNgoi[j] = 1;
												if (gheNgoiDaDat == "") {
													gheNgoiDaDat += i + 48 + 17;
													gheNgoiDaDat += to_string(j);
												}
												else {
													gheNgoiDaDat += ", ";
													gheNgoiDaDat += i + 48 + 17;
													gheNgoiDaDat += to_string(j);
												}

											}
											else if (i == 2 || i == 3) {

												gheNgoi[i][j].setFillColor(sf::Color::Blue);
												datGheNgoi[j] = 1;
												if (gheNgoiDaDat == "") {
													gheNgoiDaDat += i + 48 + 17;
													gheNgoiDaDat += to_string(j);
												}
												else {
													gheNgoiDaDat += ", ";
													gheNgoiDaDat += i + 48 + 17;
													gheNgoiDaDat += to_string(j);
												}
											}
											else if (i == 4 && j != 10) {

												if (j % 2 == 1) {
													datGheNgoi[j] = 1;
													datGheNgoi[j - 1] = 1;
													gheNgoi[i][j].setFillColor(sf::Color::Magenta);
													gheNgoi[i][j - 1].setFillColor(sf::Color::Magenta);
													if (gheNgoiDaDat == "") {
														gheNgoiDaDat += i + 48 + 17;
														gheNgoiDaDat += to_string(j);
														gheNgoiDaDat += ', ';
														gheNgoiDaDat += i + 48 + 17;
														gheNgoiDaDat += to_string(j - 1);
													}
													else {
														gheNgoiDaDat += ", ";
														gheNgoiDaDat += i + 48 + 17;
														gheNgoiDaDat += to_string(j);
														gheNgoiDaDat += ', ';
														gheNgoiDaDat += i + 48 + 17;
														gheNgoiDaDat += to_string(j - 1);
													}


												}
												else {
													datGheNgoi[j] = 1;
													datGheNgoi[j + 1] = 1;
													gheNgoi[i][j].setFillColor(sf::Color::Magenta);
													gheNgoi[i][j + 1].setFillColor(sf::Color::Magenta);
													if (gheNgoiDaDat == "") {
														gheNgoiDaDat += i + 48 + 17;
														gheNgoiDaDat += to_string(j);
														gheNgoiDaDat += ', ';
														gheNgoiDaDat += i + 48 + 17;
														gheNgoiDaDat += to_string(j + 1);
													}
													else {
														gheNgoiDaDat += ", ";
														gheNgoiDaDat += i + 48 + 17;
														gheNgoiDaDat += to_string(j);
														gheNgoiDaDat += ', ';
														gheNgoiDaDat += i + 48 + 17;
														gheNgoiDaDat += to_string(j + 1);
													}


												}


											}
											gheTrongFull = 1;


										}
										else if (datGheNgoi[j] && hangDatGhe == 18 || datGheNgoi[j] && (hangDatGhe == i)) {
											if (i == 4 && j != 10) {

												int Tong = 0;
												for (int m = 0; m < 11; m++) {
													Tong += datGheNgoi[m];
												}
												if (Tong == 2) {
													gheNgoiDaDat = "";
												}
												else {
													gheNgoiDaDat = gheNgoiDaDat.substr(0, gheNgoiDaDat.length() - 7);

												}


												if (j % 2 == 1) {
													gheNgoi[i][j].setFillColor(sf::Color::White);
													datGheNgoi[j - 1] = 0;
													gheNgoi[i][j - 1].setFillColor(sf::Color::White);
													datGheNgoi[j] = 0;


												}
												else {
													gheNgoi[i][j].setFillColor(sf::Color::White);
													datGheNgoi[j + 1] = 0;
													gheNgoi[i][j + 1].setFillColor(sf::Color::White);
													datGheNgoi[j] = 0;

												}

											}
											else {

												int Tong = 0;
												for (int m = 0; m < 11; m++) {
													Tong += datGheNgoi[m];
												}
												if (Tong == 1) {
													gheNgoiDaDat = "";
												}
												else {
													gheNgoiDaDat = gheNgoiDaDat.substr(0, gheNgoiDaDat.length() - 4);

												}

												gheNgoi[i][j].setFillColor(sf::Color::White);
												datGheNgoi[j] = 0;
											}
											for (int m = 0; m < 11; m++) {
												if (datGheNgoi[m]) {
													gheTrongFull = 0;
												}
											}


										}
									}
								}
							}

						}
						if (xacNhanDatVeButton.getGlobalBounds().contains(sf::Vector2f(mousePosition))) {

							admin1.xacnhandatve((selectedPhong[0] - 48), (selectedPhong[1] - 48) - 1, (selectedPhong[2] - 48) - 1, hangDatGhe, datGheNgoi, "DanhSachPhong.txt");
							giaVe = 0;
							for (int n = 0; n < 3; n++) {
								int FirstGia;

								for (int m = 0; m < 3; m++)
								{

									if (gioHangMenu[n * 3 + m]) {
										if (n == 0) {
											FirstGia = 15;
										}
										else if (n == 1) {
											FirstGia = 20;
										}
										else {
											FirstGia = 40;
										}
										FirstGia += m * 5;
										giaVe += FirstGia * gioHangMenu[n * 3 + m];
									}
								}
							}
							for (int j = 0; j < 11; j++) {

								if (datGheNgoi[j]) {
									if (hangDatGhe == 0 || hangDatGhe == 1 || hangDatGhe == 5 || hangDatGhe == 6) {
										giaVe += 60;
										loaiGhe = "NOR";
									}
									else if (hangDatGhe == 2 || hangDatGhe == 3) {
										giaVe += 100;
										loaiGhe = "VIP";
									}
									else {
										if (j == 10) {
											giaVe += 60;
											loaiGhe = "NOR";
										}
										else {
											giaVe += 80;
											loaiGhe = "COUP";
										}
									}

								}
							}

							countPage++;

						}
					}


				}

				else  if (event.type == sf::Event::MouseMoved) {
					// Kiá»ƒm tra hover
					daLoadGheNgoi = 0;
					if (!daLoadGheNgoi) {
						for (int j = 0; j < 7; j++) {
							for (int k = 0; k < 11; k++) {

								if (selectedPhong2.getghengoi(j, k)) {
									gheNgoi[j][k].setFillColor(sf::Color::Red);
								}
								else {
									gheNgoi[j][k].setFillColor(sf::Color::White);

								}


							}
						}

						if (hangDatGhe == 0 || hangDatGhe == 1 || hangDatGhe == 5 || hangDatGhe == 6) {
							for (int j = 0; j < 11; j++) {
								if (datGheNgoi[j]) {
									gheNgoi[hangDatGhe][j].setFillColor(sf::Color::Green);
								}
							}
						}
						else if (hangDatGhe == 4) {
							for (int j = 0; j < 11; j++) {
								if (datGheNgoi[j]) {
									gheNgoi[hangDatGhe][j].setFillColor(sf::Color::Magenta);
								}
							}
						}
						else if (hangDatGhe == 2 || hangDatGhe == 3) {
							for (int j = 0; j < 11; j++) {
								if (datGheNgoi[j]) {
									gheNgoi[hangDatGhe][j].setFillColor(sf::Color::Blue);
								}
							}
						}

						daLoadGheNgoi = 1;
					}

					for (int i = 0; i < 3; ++i) {
						if (loaiGheNgoi[i].getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
							daLoadGheNgoi = 1;
							if (i == 0) {
								for (int k = 0; k < 11; k++) {
									gheNgoi[0][k].setFillColor(sf::Color::Green);
									gheNgoi[1][k].setFillColor(sf::Color::Green);
									gheNgoi[5][k].setFillColor(sf::Color::Green);
									gheNgoi[6][k].setFillColor(sf::Color::Green);
								}

							}
							else if (i == 1) {
								for (int k = 0; k < 11; k++) {
									gheNgoi[2][k].setFillColor(sf::Color::Blue);
									gheNgoi[3][k].setFillColor(sf::Color::Blue);

								}
							}
							else if (i == 2) {
								for (int k = 0; k < 11; k++) {
									gheNgoi[4][k].setFillColor(sf::Color::Magenta);

								}
							}
						}



					}


				}



				if (!texturePhimPage6.loadFromFile(admin1.getdanhsachphim()[selectedPhimNumber].getlinkanh())) {
					std::cerr << "Error loading movieSpriteTexture texture!" << std::endl;
					return -1;


				}
				spritePhimPage6.setTexture(texturePhimPage6);
				spritePhimPage6.setPosition(100, movieSprite.getPosition().y);
				spritePhimPage6.setScale(0.18, 0.18);
				contentSprite[0].setString(selectedPhim.gettenphim());
				int tmpShit = 0;
				string tmpBapNuoc = "";
				for (int i = 0; i < 3; i++) {
					tmpShit = 0;
					for (int j = 0; j < 3; j++) {
						tmpShit += gioHangMenu[i * 3 + j];
					}
					if (i == 0) {
						tmpBapNuoc += to_string(tmpShit) + " Coca\n";

					}
					else if (i == 1) {
						tmpBapNuoc += to_string(tmpShit) + " Coffe\n";

					}
					else {
						tmpBapNuoc += to_string(tmpShit) + " PopCorn";

					}
				}

				contentSprite[5].setString(tmpBapNuoc);

				contentSprite[6].setString("Ghe Ngoi : " + gheNgoiDaDat);


				if (selectedPhim.getdanhsachsuatchieu()[selectedSuatChieu].getthoigianchieu().getgio() < 10 || selectedPhim.getdanhsachsuatchieu()[selectedSuatChieu].getthoigianchieu().getphut() < 10) {
					if (selectedPhim.getdanhsachsuatchieu()[selectedSuatChieu].getthoigianchieu().getgio() < 10) {
						contentSprite[1].setString("Suat Chieu 0" + to_string(selectedPhim.getdanhsachsuatchieu()[selectedSuatChieu].getthoigianchieu().getgio()) + ":" + to_string(selectedPhim.getdanhsachsuatchieu()[selectedSuatChieu].getthoigianchieu().getphut()));

					}
					else if (selectedPhim.getdanhsachsuatchieu()[selectedSuatChieu].getthoigianchieu().getphut() < 10) {
						contentSprite[1].setString("Suat Chieu " + to_string(selectedPhim.getdanhsachsuatchieu()[selectedSuatChieu].getthoigianchieu().getgio()) + ":0" + to_string(selectedPhim.getdanhsachsuatchieu()[selectedSuatChieu].getthoigianchieu().getphut()));

					}
				}
				else {
					contentSprite[1].setString("Suat Chieu " + to_string(selectedPhim.getdanhsachsuatchieu()[selectedSuatChieu].getthoigianchieu().getgio()) + ":" + to_string(selectedPhim.getdanhsachsuatchieu()[selectedSuatChieu].getthoigianchieu().getphut()));

				}
				if (selectedPhim.getdanhsachsuatchieu()[selectedSuatChieu].getthoigianchieu().getngay() < 10 || selectedPhim.getdanhsachsuatchieu()[selectedSuatChieu].getthoigianchieu().getthang() < 10) {
					if (selectedPhim.getdanhsachsuatchieu()[selectedSuatChieu].getthoigianchieu().getngay() < 10) {
						contentSprite[2].setString(to_string(selectedPhim.getdanhsachsuatchieu()[selectedSuatChieu].getthoigianchieu().getngay()) + "/" + to_string(selectedPhim.getdanhsachsuatchieu()[selectedSuatChieu].getthoigianchieu().getthang()) + "/" + to_string(selectedPhim.getdanhsachsuatchieu()[selectedSuatChieu].getthoigianchieu().getnam()));

					}
					else if (selectedPhim.getdanhsachsuatchieu()[selectedSuatChieu].getthoigianchieu().getthang() < 10) {
						contentSprite[2].setString(to_string(selectedPhim.getdanhsachsuatchieu()[selectedSuatChieu].getthoigianchieu().getngay()) + "/0" + to_string(selectedPhim.getdanhsachsuatchieu()[selectedSuatChieu].getthoigianchieu().getthang()) + "/" + to_string(selectedPhim.getdanhsachsuatchieu()[selectedSuatChieu].getthoigianchieu().getnam()));

					}
				}
				else {
					contentSprite[2].setString(to_string(selectedPhim.getdanhsachsuatchieu()[selectedSuatChieu].getthoigianchieu().getngay()) + "/" + to_string(selectedPhim.getdanhsachsuatchieu()[selectedSuatChieu].getthoigianchieu().getthang()) + "/" + to_string(selectedPhim.getdanhsachsuatchieu()[selectedSuatChieu].getthoigianchieu().getnam()));

				}
				giaVe = 0;
				for (int n = 0; n < 3; n++) {
					int FirstGia;

					for (int m = 0; m < 3; m++)
					{

						if (gioHangMenu[n * 3 + m]) {
							if (n == 0) {
								FirstGia = 15;
							}
							else if (n == 1) {
								FirstGia = 20;
							}
							else {
								FirstGia = 40;
							}
							FirstGia += m * 5;
							giaVe += FirstGia * gioHangMenu[n * 3 + m];
						}
					}
				}
				for (int j = 0; j < 11; j++) {

					if (datGheNgoi[j]) {
						if (hangDatGhe == 0 || hangDatGhe == 1 || hangDatGhe == 5 || hangDatGhe == 6) {
							giaVe += 60;
							loaiGhe = "NOR";
						}
						else if (hangDatGhe == 2 || hangDatGhe == 3) {
							giaVe += 100;
							loaiGhe = "VIP";
						}
						else {
							if (j == 10) {
								giaVe += 60;
								loaiGhe = "NOR";
							}
							else {
								giaVe += 80;
								loaiGhe = "COUP";
							}
						}

					}
				}

				contentSprite[4].setString("Tong : " + to_string(giaVe) + ".000 vnd");

			}
			else if (countPage == 5) {

				ve tmpVe(giaVe, rightNow, bapNuoc, selectedPhim.gettenphim(), ngayChieu, gheNgoiDaDat, loaiGhe);
				contentVe[0].setString(selectedPhim.gettenphim());
				contentVe[1].setString("Ghe Ngoi " + gheNgoiDaDat);
				contentVe[2].setString("Ghe " + loaiGhe);
				contentVe[7].setString(contentSprite[1].getString());
				contentVe[8].setString(contentSprite[3].getString());


				int tmpShit = 0;
				string tmpBapNuoc = "";
				for (int i = 0; i < 3; i++) {
					tmpShit = 0;
					for (int j = 0; j < 3; j++) {
						tmpShit += gioHangMenu[i * 3 + j];
					}
					if (i == 0) {
						tmpBapNuoc += to_string(tmpShit) + " Coca\n";

					}
					else if (i == 1) {
						tmpBapNuoc += to_string(tmpShit) + " Coffe\n";

					}
					else {
						tmpBapNuoc += to_string(tmpShit) + " PopCorn";

					}
				}





				contentVe[3].setString(tmpBapNuoc);
				contentVe[4].setString("Ngay Chieu " + to_string(ngayChieu.getngay()) + "/" + to_string(ngayChieu.getthang()) + "/" + to_string(ngayChieu.getnam()));
				contentVe[5].setString("Ngay Dat Ve " + to_string(rightNow.getngay()) + "/" + to_string(rightNow.getthang()) + "/" + to_string(rightNow.getnam()));
				contentVe[6].setString(to_string(giaVe) + ".000 vnd");

				if (!datinhtienthungay) {
					if (ngayChieu.getthungay() == 0 || ngayChieu.getthungay() == 6) {
						for (int j = 0; j < 11; j++) {
							if (datGheNgoi[j]) {
								giaVe += 15;
							}
						}

					}
					datinhtienthungay = 1;
				}

				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						bapNuoc += to_string(gioHangMenu[i * 3 + j]);
					}
				}
				if (!daThemVe) {
					admin1.themve(giaVe, rightNow, bapNuoc, selectedPhim.gettenphim(), ngayChieu, gheNgoiDaDat, loaiGhe);
					daThemVe = 1;
				}
				if (!daVeQR) {
					arrayK = 0;
					arrayO = 0;

					string tmp = tmpVe.getid() + "RAPCGVDANANGPBL2202318012004PHAMNHATBANGHUYNHHUUHOANG";



					for (int i = 0; i < rows1; ++i) {
						for (int j = 0; j < cols1; ++j) {
							if (arrayO >= tmp.size()) {
								arrayO = 0;
								arrayK++;
							}
							if (tmp[arrayK * cols1 + arrayO] > 100) {
								array2D[i][j] = tmp[arrayK * cols1 + arrayO] - 30;
							}
							else {
								array2D[i][j] = tmp[arrayK * cols1 + arrayO];
							}

							arrayO++;
						}

					}
					daVeQR = 1;
				}
			}
			if (countPage == 1) {
				window.clear(sf::Color(253, 252, 240));
				sf::Vector2f startPoint(phimdangchieu.getPosition().x, phimdangchieu.getPosition().y + 65);

				line.setPosition(startPoint);
				for (int i = 0; i < soPhim; i++) {
					window.draw(borderPosterPhim[i]);
					window.draw(posterPhim[i]);
					window.draw(tenphim[i]);
					window.draw(thongtinphim1[i].second);
					window.draw(thongtinphim2[i]);
					window.draw(thongtinphim3[i]);

				}
				window.draw(line);
				window.draw(phimdangchieu);
				window.draw(searchBar);
				window.draw(searchBoxText);
				if (isHovered) {
					window.setMouseCursor(handPointer);
				}
				else {
					window.setMouseCursor(arrowPointer);
				}

			}
			else if (countPage == 2) {
				window.clear(sf::Color(253, 252, 240));
				window.draw(coTheBanCungThich);
				for (int i = 0; i < countTheLoai.size(); i++) {

					window.draw(borderPosterPhim[countTheLoai[i]]);
					window.draw(posterPhim[countTheLoai[i]]);
					window.draw(tenphim[countTheLoai[i]]);
					window.draw(thongtinphim1[countTheLoai[i]].second);
					window.draw(thongtinphim2[countTheLoai[i]]);
					window.draw(thongtinphim3[countTheLoai[i]]);
				}
				window.draw(thongtinphim1Tmp);
				window.draw(CGV);
				window.draw(noiDungPhim);
				sf::Vector2f startPoint(noiDungPhim.getPosition().x, noiDungPhim.getPosition().y + 65);

				line.setPosition(startPoint);
				window.draw(line);

				window.draw(borderPosterPhim[selectedPhimNumber]);
				window.draw(posterPhim[selectedPhimNumber]);
				window.draw(tenphim[selectedPhimNumber]);
				window.draw(thongtinphim2[selectedPhimNumber]);
				window.draw(thongtinphim3[selectedPhimNumber]);
				for (int k = 0; k < 2; k++) {
					window.draw(contentText[k]);
				}
				window.draw(orderButton);
				// Draw the enlarged sprite (if needed)
				if (Hover) {
					window.draw(enlargedArea);

				}
				window.draw(enlargedSprite);

			}
			else if (countPage == 3) {
				window.clear(sf::Color(253, 252, 240));

				for (int i = 0; i < buttonCount; ++i)
				{
					quantityTexts[i].setString(std::to_string(quantities[i][sizeQuantities[i]]));
				}
				for (int i = 0; i < 10; i++) {
					window.draw(thuNgayBorder[i]);
					window.draw(thuNgay[i]);
					window.draw(ngayThang[i]);
				}
				if (clickedSuatChieu) {
					for (int i = 0; i < suatChieu.size(); i++) {
						window.draw(suatChieuBorder[i]);
						window.draw(suatChieu[i]);
					}
				}
				if (clickedSuatChieu2) {
					window.draw(MENU);
					window.draw(menuQuan);
					for (int i = 0; i < buttonCount; ++i)
					{
						if (sizeQuantities[i] == 0) {
							sizeText[i].setString("Size S");
						}
						else if (sizeQuantities[i] == 1) {
							sizeText[i].setString("Size M");
						}
						else if (sizeQuantities[i] == 2) {
							sizeText[i].setString("Size L");
						}
					}

					for (int i = 0; i < buttonCount; ++i)
					{
						window.draw(increaseButtons[i]);
						window.draw(decreaseButtons[i]);
						window.draw(sizeText[i]);
						window.draw(increaseTexts[i]); // Draw increaseText
						window.draw(decreaseTexts[i]); // Draw decreaseText
					}
					window.draw(coCaCoLa[sizeQuantities[0]]);
					window.draw(pepSi[sizeQuantities[1]]);
					window.draw(popCorn[sizeQuantities[2]]);
					window.draw(confirmButton);
					window.draw(xacnhanButton);
					for (int i = 0; i < buttonCount; ++i)
					{
						for (int j = 0; j < 2; ++j)
						{
							window.draw(buttons[i * 2 + j]);
							window.draw(buttonTexts[i * 2 + j]);
						}
						window.draw(quantityTexts[i]);
					}
				}


			}
			else if (countPage == 4) {
				window.clear(sf::Color(253, 252, 240));

				window.draw(movieSprite);
				for (int i = 0; i < 3; i++) {
					window.draw(loaiGheNgoi[i]);
					window.draw(textLoaiGhe[i]);

				}
				for (int i = 0; i < rows; i++) {
					for (int j = 0; j < cols; j++) {
						if (i == 4 && j == 10) {

						}
						else {
							window.draw(gheNgoi[i][j]);
							window.draw(textGheNgoi[i][j]);
						}
					}
				}
				window.draw(xacNhanDatVeButton);
				window.draw(spritePhimPage6);
				for (int i = 0; i < 7; i++) {
					window.draw(contentSprite[i]);
				}
			}
			else if (countPage == 5) {
				window.clear(sf::Color(253, 252, 240));
				window.draw(khungVe);

				drawQRCode(window, array2D);
				for (int i = 0; i < 4; i++) {
					contentVe[i].setPosition((window.getSize().x - contentVe[i].getGlobalBounds().getSize().x) / 2, i * 50 + khungVe.getPosition().y + 285);
				}
				for (int i = 4; i < 9; i++) {
					contentVe[i].setPosition((window.getSize().x - contentVe[i].getGlobalBounds().getSize().x) / 2, 3 * 50 + khungVe.getPosition().y + 215 + i * 50);
				}


				for (int i = 0; i < 9; i++) {
					window.draw(contentVe[i]);
				}


			}
			if (countPage != 5) {
				window.draw(backButton);
			}
			window.display();
		}
	}
	return 0;
}



//int main()
//{
//	cout << "concac";
//	// Tạo cửa sổ kích thước 800x600 pixels
//	sf::RenderWindow window(sf::VideoMode(1500, 844), "Cinema");
//
//	sf::RenderWindow windowLoginAdmin(sf::VideoMode(900, 900), "Login Admin", sf::Style::None);
//	windowLoginAdmin.setActive(false);
//	windowLoginAdmin.setVisible(false);
//
//	//sf::RenderWindow windowAdmin(sf::VideoMode(1500, 900), "Admin");
//	//windowAdmin.setActive(false);
//	//windowAdmin.setVisible(false);
//
//	sf::Font font;
//	if (!font.loadFromFile("Roboto-Bold.ttf"))
//	{
//		std::cout << "Failed to load font!" << std::endl;
//		return -1;
//	}
//
//	///////////////////////////
//
//		//std::vector<pair<string, string>> films;
//
//	//string title = "My nhan dao chich";
//	//string desc = "";
//	//string linkImage = "mynhandaochich.jpg";
//	//films.push_back({ title, desc, linkImage });
//
//	//title = "Am hon do thi";
//	//desc = "";
//	//linkImage = "amhondothi.jpg";
//	//films.push_back({ title, desc, linkImage });
//
//	//title = "Nguoi vo cuoi cung";
//	//desc = "";
//	//linkImage = "nguoivocuoicung.jpg";
//	//films.push_back({ title, desc, linkImage });
//
//	//title = "Nam dem kinh hoang";
//	//desc = "";
//	//linkImage = "5demkinhhoang.jpg";
//	//films.push_back({ title, desc, linkImage });
//
//	//title = "Quy mon quan";
//	//desc = "";
//	//linkImage = "quymonquan.jpg";
//	//films.push_back({ title, desc, linkImage });
//
//	//title = "Wolfoo";
//	//desc = "";
//	//linkImage = "wolfoo.jpg";
//	//films.push_back({ title, desc, linkImage });
//
//	//title = "Dat rung phuong nam";
//	//desc = "";
//	//linkImage = "marvel.jpg";
//	//films.push_back({ title, desc, linkImage });
//
//	//title = "Biet doi Marvel";
//	//desc = "";
//	//linkImage = "marvel.jpg";
//	//films.push_back({ title, desc, linkImage });
//
//	//title = "Hai ke doi tra";
//	//desc = "";
//	//linkImage = "haikedoitra.png";
//	//films.push_back({ title, desc, linkImage });
//
//	std::thread readThread(readFromFile);
//	readThread.join();
//
//	for (int i = 0;i < films.size(); i++) {
//		cout << films[i].title << endl;
//	}
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
//	for (int i = 0; i < films.size(); i++)
//	{
//		sf::RectangleShape productBox(sf::Vector2f(150, 200));
//		productBox.setFillColor(sf::Color::White);
//		productBox.setOutlineThickness(2);
//		productBox.setOutlineColor(sf::Color::Black);
//
//		autoproductBoxes.push_back({ productBox , films[i].image });
//	}
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
//		adminproductBoxes.push_back({ productBox , {productText, films[i].image} });
//	}
//
//	//double x_0 = 196, y_0 = 345;
//	//double delta_x = 93.5, delta_y = 88.5;
//
//	//for (int k = 0; k < 3; k++) {
//	//	for (int i = 0; i < 12; i++) {
//	//		for (int j = 0; j < 6; j++) {
//	//			double x = x_0 + i * delta_x, y = y_0 + j * delta_y;
//	//			box[k][i][j].second = false;
//	//			box[k][i][j].first.setSize(sf::Vector2f(76, 74.5));
//	//			box[k][i][j].first.setFillColor(sf::Color(238, 100, 87)); //100, 238, 87
//	//			box[k][i][j].first.setOutlineThickness(2);
//	//			box[k][i][j].first.setOutlineColor(sf::Color::Black);
//	//			box[k][i][j].first.setPosition(x, y);
//	//		}
//	//	}
//	//}
//
//
//
//	//for (int i = 0; i < 3; i++) {
//	//	for (int j = 0; j < 7; j++) {
//	//		for (int k = 0; k < 11; k++) cout << mang3Chieu[i][j][k] << ' ';
//	//		cout << endl;
//	//	}
//	//}
//
//	//////////////////////////
//
//
//	sf::Texture texture;
//	if (!texture.loadFromFile("moviee.png"))
//		return EXIT_FAILURE;
//
//	sf::Sprite sprite(texture);
//	float scalex = 1500.0 / texture.getSize().x;
//	float scaley = 844.0 / texture.getSize().y;
//	sprite.setScale(scalex, scaley);
//	sprite.setPosition(0, 0);
//
//	////////////////////// Header
//
//	sf::RectangleShape headerBox(sf::Vector2f(1500, 100));
//	headerBox.setFillColor(sf::Color(3, 19, 39)); //205, 156, 124, 150
//	headerBox.setPosition(0, 0);
//
//	/////////////////////////
//
//
//	//TEXT CLOCK
//	sf::Font fontClock;
//	if (!fontClock.loadFromFile("Wallpoet-Regular.ttf"))
//		return EXIT_FAILURE;
//
//	sf::Texture clockTexture;
//	clockTexture.loadFromFile("clock.png");
//
//	sf::Sprite clockSprite(clockTexture);
//	clockSprite.setPosition(0, 5);
//	scalex = 158.0 / clockTexture.getSize().x;
//	scaley = 100.0 / clockTexture.getSize().y;
//	clockSprite.setScale(scalex, scaley);
//
//	// Tạo văn bản sử dụng font đã tải
//	//sf::Text textClockDay("", fontClock, 24);
//	//textClockDay.setPosition(0, 100);
//
//	sf::Text textClockTime("", fontClock, 13);
//	textClockTime.setPosition(43, 49);
//	//TEXT CLOCK
//
//	bool homePageButton = true;
//	bool selectDropDownButton = false;
//	bool selectAndUpdateButton = false; int indexButton = 0;
//	bool orderButtonActive = false;
//
//	//sf::RectangleShape movieButton(sf::Vector2f(250, 100));
//	//movieButton.setFillColor(sf::Color(3, 22, 46));
//	//movieButton.setPosition(650, 0);
//
//	//sf::Text movieButtonText("MOVIE", font, 30);
//	//movieButtonText.setFillColor(sf::Color::White);
//	//movieButtonText.setPosition(725, 35);
//
//	//sf::RectangleShape orderButton(sf::Vector2f(250, 100));
//	//orderButton.setFillColor(sf::Color(3, 22, 46));
//	//orderButton.setPosition(900, 0);
//
//	//sf::Text orderButtonText("ORDER", font, 30);
//	//orderButtonText.setFillColor(sf::Color::White);
//	//orderButtonText.setPosition(975, 35);
//
//	//sf::RectangleShape adminButton(sf::Vector2f(250, 100));
//	//adminButton.setFillColor(sf::Color(3, 22, 46));
//	//adminButton.setPosition(1150, 0);
//
//	//sf::Text adminButtonText("ADMIN", font, 30);
//	//adminButtonText.setFillColor(sf::Color::White);
//	//adminButtonText.setPosition(1225, 35);
//
//	sf::RectangleShape movieButton(sf::Vector2f(200, 100));
//	movieButton.setFillColor(sf::Color(3, 22, 46));
//	movieButton.setPosition(800, 0);
//
//	sf::Text movieButtonText("MOVIE", font, 30);
//	movieButtonText.setFillColor(sf::Color::White);
//	movieButtonText.setPosition(853, 35);
//
//	sf::RectangleShape orderButton(sf::Vector2f(200, 100));
//	orderButton.setFillColor(sf::Color(3, 22, 46));
//	orderButton.setPosition(1000, 0);
//
//	sf::Text orderButtonText("ORDER", font, 30);
//	orderButtonText.setFillColor(sf::Color::White);
//	orderButtonText.setPosition(1053, 35);
//
//	sf::RectangleShape adminButton(sf::Vector2f(200, 100));
//	adminButton.setFillColor(sf::Color(3, 22, 46));
//	adminButton.setPosition(1200, 0);
//
//	sf::Text adminButtonText("ADMIN", font, 30);
//	adminButtonText.setFillColor(sf::Color::White);
//	adminButtonText.setPosition(1253, 35);
//
//	sf::RectangleShape searchBox(sf::Vector2f(500, 60));
//	searchBox.setFillColor(sf::Color::White);
//	searchBox.setPosition(180, 20);
//
//	sf::Text searchBoxText;
//	//searchBoxText.setFillColor(sf::Color::Black);
//	searchBoxText.setFillColor(sf::Color(104, 104, 104));
//	searchBoxText.setFont(font);
//	searchBoxText.setCharacterSize(25);
//	searchBoxText.setPosition(185, 35);
//	searchBoxText.setString("Search...");
//
//
//	sf::Texture lookupTexture;
//	lookupTexture.loadFromFile("lookup.png");
//	sf::Sprite lookupSprite(lookupTexture);
//	lookupSprite.setPosition(680, 20);
//	scalex = 60.0 / lookupTexture.getSize().x;
//	scaley = 60.0 / lookupTexture.getSize().y;
//	lookupSprite.setScale(scalex, scaley);
//
//	vector< pair<sf::Text, sf::RectangleShape>> search;
//
//	sf::RectangleShape box1(sf::Vector2f(560, 60));
//	box1.setFillColor(sf::Color(239, 200, 152));
//	box1.setPosition(180, 80);
//
//	sf::Text text1;
//	//searchBoxText.setFillColor(sf::Color::Black);
//	text1.setFillColor(sf::Color(104, 104, 104));
//	text1.setFont(font);
//	text1.setCharacterSize(25);
//	text1.setPosition(185, 95);
//	text1.setString("");
//	search.push_back({ text1, box1 });
//
//	sf::RectangleShape box2(sf::Vector2f(560, 60));
//	box2.setFillColor(sf::Color(222, 143, 48));
//	box2.setPosition(180, 140);
//
//	sf::Text text2;
//	//searchBoxText.setFillColor(sf::Color::Black);
//	text2.setFillColor(sf::Color(104, 104, 104));
//	text2.setFont(font);
//	text2.setCharacterSize(25);
//	text2.setPosition(185, 155);
//	text2.setString("");
//	search.push_back({ text2, box2 });
//
//	sf::RectangleShape box3(sf::Vector2f(560, 60));
//	box3.setFillColor(sf::Color(239, 200, 152));
//	box3.setPosition(180, 200);
//
//	sf::Text text3;
//	//searchBoxText.setFillColor(sf::Color::Black);
//	text3.setFillColor(sf::Color(104, 104, 104));
//	text3.setFont(font);
//	text3.setCharacterSize(25);
//	text3.setPosition(185, 215);
//	text3.setString("");
//	search.push_back({ text3, box3 });
//
//	bool isSearchActive = false;
//	bool isSearchResultActive = false;
//	int indexChoose = -1;
//
//	sf::RectangleShape boxDetail(sf::Vector2f(1300, 700));
//	boxDetail.setFillColor(sf::Color::White);
//	boxDetail.setPosition(100, 144);
//
//	sf::Texture detailTexture;
//	detailTexture.loadFromFile("amhondothi.jpg");
//	sf::Sprite detailSprite(detailTexture);
//	detailSprite.setPosition(200, 150);
//	scalex = 150.0 / detailTexture.getSize().x;
//	scaley = 200.0 / detailTexture.getSize().y;
//	detailSprite.setScale(scalex, scaley);
//
//	sf::Text detailText;
//	detailText.setFont(font);
//	detailText.setCharacterSize(27);
//	detailText.setFillColor(sf::Color::Black);
//	detailText.setPosition(500, 230);
//	//detailText.setString("AM HON DO THI");
//
//	sf::Text textDescription;
//	textDescription.setFont(font);
//	textDescription.setCharacterSize(20);
//	textDescription.setFillColor(sf::Color(27, 156, 16));
//	textDescription.setPosition(200, 375);
//	textDescription.setString("Description: ");
//
//	sf::Text detailDescripton("", font, 24);
//	detailDescripton.setFillColor(sf::Color::Black);
//	detailDescripton.setPosition(170, 400);
//	//sf::Text tmpText("", font, 24);
//	//tmpText.setFillColor(sf::Color::Black);
//	//tmpText.setPosition(170, 400);
//	//string tmpString = detailDescripton.getString().toAnsiString();
//	//detailDescripton.setString("");
//	//for (char c : tmpString) {
//	//	if (tmpText.getLocalBounds().width <= 1160) {
//	//		tmpText.setString(tmpText.getString().toAnsiString() + c);
//	//	}
//	//	else {
//	//		detailDescripton.setString(tmpText.getString() + "\n" + c);
//	//		tmpText.setString("");
//	//	}
//	//}
//
//	//detailDescripton.setString(detailDescripton.getString().toAnsiString() + tmpText.getString().toAnsiString());
//	//cout << detailDescripton.getString().toAnsiString() << endl;
//
//	position = 50.0f;
//	first = 0, last = films.size() - 1;
//	std::thread thread(updateFilmPosition, std::ref(position), std::ref(first), std::ref(last));
//
//	while (window.isOpen())
//	{
//		// Xử lý các sự kiện
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed) {
//				window.close();
//				thread.detach();
//				//std::thread writeThread(writeToFile);
//				//writeThread.join();
//				cout << "oke";
//			}
//
//			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
//			{
//				if (searchBox.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
//				{
//					//isDropdownActive = !isDropdownActive;
//					isSearchActive = true;
//				}
//				//else {
//				//	isSearchActive = false;
//				//}
//				else if (isSearchActive)
//				{
//					bool checkClickSearchButton = true;
//					for (int i = 0; i < search.size(); i++)
//					{
//						if (search[i].first.getString().toAnsiString() != "" && search[i].first.getString().toAnsiString() != "Not found") {
//							if (search[i].second.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
//								cout << i << ' ' << search[i].first.getString().toAnsiString() << endl;
//								isSearchActive = false;
//								homePageButton = false;
//								isSearchResultActive = true;
//								checkClickSearchButton = false;
//
//								for (int j = 0; j < films.size(); j++) {
//									if (search[i].first.getString().toAnsiString() == films[j].title) {
//										indexChoose = j;
//									}
//								}
//
//								detailText.setString(films[indexChoose].title);
//								detailTexture.loadFromFile(films[indexChoose].image);
//
//								detailDescripton.setString(films[indexChoose].desc);
//
//								sf::Text tmpText("", font, 24);
//								tmpText.setFillColor(sf::Color::Black);
//								tmpText.setPosition(170, 400);
//								string tmpString = detailDescripton.getString().toAnsiString();
//								detailDescripton.setString("");
//								for (char c : tmpString) {
//									if (tmpText.getLocalBounds().width <= 1160) {
//										tmpText.setString(tmpText.getString().toAnsiString() + c);
//									}
//									else {
//										detailDescripton.setString(tmpText.getString() + "\n" + c);
//										tmpText.setString("");
//									}
//								}
//
//								detailDescripton.setString(detailDescripton.getString().toAnsiString() + tmpText.getString().toAnsiString());
//
//							}
//						}
//					}
//					if (checkClickSearchButton) {
//						isSearchActive = false;
//					}
//				}
//				//if (isSearchActive)
//				//{
//				//	for (int i = 0; i < 3; i++) {
//				//		if (isMouseOver(search[i].second, window))
//				//		{
//				//			isSearchActive = false;
//				//			homePageButton = false;
//				//			isSearchResultActive = true;
//				//			indexChoose = i;
//				//			break;
//				//		}
//				//	}
//
//				//}
//			}
//			if (event.type == sf::Event::TextEntered)
//			{
//				if (isSearchActive)
//				{
//					if (event.text.unicode < 128)
//					{
//						if (event.text.unicode == '\b')
//						{
//							if (searchBoxText.getString() != "Search...") {
//								std::string currentText = searchBoxText.getString();
//								currentText.pop_back();
//								if (currentText == "") searchBoxText.setString("Search...");
//								else searchBoxText.setString(currentText);
//
//							}
//						}
//						else
//						{
//							float textWidth = searchBoxText.getLocalBounds().width;
//							float buttonWidth = searchBox.getLocalBounds().width;
//							if (buttonWidth > textWidth + 20) {
//								if (searchBoxText.getString() == "Search...") searchBoxText.setString("");
//								searchBoxText.setString(searchBoxText.getString() + static_cast<char>(event.text.unicode));
//							}
//						}
//
//						regex pattern(normalizeString(searchBoxText.getString().toAnsiString()));
//
//						for (std::pair<sf::Text, sf::RectangleShape>& option : search)
//						{
//							option.first.setString("");
//						}
//
//						int cnt = 0;
//
//						for (int i = 0; i < films.size(); i++) {
//							if (regex_search(normalizeString(films[i].title), pattern)) {
//								search[cnt].first.setString(films[i].title);
//								++cnt;
//								cout << films[i].title << " matches the pattern" << std::endl;
//								if (cnt >= 3) {
//									break;
//								}
//							}
//						}
//						if (cnt == 0) {
//							search[cnt].first.setString("Not found");
//						}
//					}
//				}
//			}
//
//			if (event.type == sf::Event::MouseMoved)
//			{
//				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
//				if (movieButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
//				{
//					movieButtonText.setFillColor(sf::Color(255, 84, 0));
//				}
//				else {
//					movieButtonText.setFillColor(sf::Color::White);
//				}
//				if (orderButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
//				{
//					orderButtonText.setFillColor(sf::Color(255, 84, 0));
//				}
//				else {
//					orderButtonText.setFillColor(sf::Color::White);
//				}
//				if (adminButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
//				{
//					adminButtonText.setFillColor(sf::Color(255, 84, 0));
//				}
//				else {
//					adminButtonText.setFillColor(sf::Color::White);
//				}
//			}
//
//			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
//				if (movieButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
//					homePageButton = true;
//					isSearchActive = false;
//					isSearchResultActive = false;
//				}
//				if (orderButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
//					window.setActive(false);
//					window.setVisible(false);
//					order();
//					window.setActive(true);
//					window.setVisible(true);
//				}
//				if (adminButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
//					window.setActive(false);
//					window.setVisible(false);
//					loginAdminWindow(window, windowLoginAdmin);
//					position = 50.0f;
//					first = 0, last = films.size() - 1;
//					window.setActive(true);
//					window.setVisible(true);
//				}
//			}
//
//			if (homePageButton) {
//				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
//				{
//					//for (int i = 0; i < productBoxes.size(); i++)
//					//{
//					//	if (productBoxes[i].first.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
//					//		cout << productBoxes[i].second.first.getString().toAnsiString() << endl;
//					//		isSearchActive = false;
//					//		homePageButton = false;
//					//		isSearchResultActive = true;
//
//					//		detailText.setString(films[i].title);
//					//		detailTexture.loadFromFile(films[i].image);
//
//					//		detailDescripton.setString(films[i].desc);
//
//					//		sf::Text tmpText("", font, 24);
//					//		tmpText.setFillColor(sf::Color::Black);
//					//		tmpText.setPosition(170, 400);
//					//		string tmpString = detailDescripton.getString().toAnsiString();
//					//		detailDescripton.setString("");
//					//		for (char c : tmpString) {
//					//			if (tmpText.getLocalBounds().width <= 1160) {
//					//				tmpText.setString(tmpText.getString().toAnsiString() + c);
//					//			}
//					//			else {
//					//				detailDescripton.setString(tmpText.getString() + "\n" + c);
//					//				tmpText.setString("");
//					//			}
//					//		}
//
//					//		detailDescripton.setString(detailDescripton.getString().toAnsiString() + tmpText.getString().toAnsiString());
//					//	}
//					//}
//					for (int i = 0; i < autoproductBoxes.size(); i++)
//					{
//						if (autoproductBoxes[i].first.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
//							isSearchActive = false;
//							homePageButton = false;
//							isSearchResultActive = true;
//
//							detailText.setString(films[i].title);
//							detailTexture.loadFromFile(films[i].image);
//
//							detailDescripton.setString(films[i].desc);
//
//							sf::Text tmpText("", font, 24);
//							tmpText.setFillColor(sf::Color::Black);
//							tmpText.setPosition(170, 400);
//							string tmpString = detailDescripton.getString().toAnsiString();
//							detailDescripton.setString("");
//							for (char c : tmpString) {
//								if (tmpText.getLocalBounds().width <= 1160) {
//									tmpText.setString(tmpText.getString().toAnsiString() + c);
//								}
//								else {
//									detailDescripton.setString(tmpText.getString() + "\n" + c);
//									tmpText.setString("");
//								}
//							}
//
//							detailDescripton.setString(detailDescripton.getString().toAnsiString() + tmpText.getString().toAnsiString());
//						}
//					}
//				}
//			}
//		}
//
//		auto now = std::chrono::system_clock::now();
//		std::time_t now_time = std::chrono::system_clock::to_time_t(now);
//
//		// Chuyển đổi std::time_t sang đối tượng std::tm
//		std::tm time_info;
//		localtime_s(&time_info, &now_time);
//
//		// Chuyển đổi std::tm sang chuỗi có thể đọc được
//		char buf[100];
//		//std::strftime(buf, sizeof(buf), "%Y-%m-%d", &time_info);
//		//textClockDay.setString(buf);
//
//		std::strftime(buf, sizeof(buf), "%H:%M:%S", &time_info);
//		textClockTime.setString(buf);
//
//		// Xóa cửa sổ
//		window.clear();
//
//		// Vẽ các đối tượng lên cửa sổ
//		window.draw(sprite);
//
//		window.draw(headerBox);
//
//		window.draw(clockSprite);
//		window.draw(textClockTime);
//
//		window.draw(movieButton);
//		window.draw(movieButtonText);
//		window.draw(orderButton);
//		window.draw(orderButtonText);
//		window.draw(adminButton);
//		window.draw(adminButtonText);
//
//		window.draw(searchBox);
//		window.draw(searchBoxText);
//		window.draw(lookupSprite);
//
//		if (homePageButton && films.size() > 0) {
//			autoproductBoxes[first].first.setPosition(position, 125);
//			sf::Texture texture;
//			if (!texture.loadFromFile(autoproductBoxes[first].second)) {
//				texture.loadFromFile("404.jfif");
//			}
//			sf::Sprite sprite(texture);
//			float scalex = 140.0 / texture.getSize().x;
//			float scaley = 190.0 / texture.getSize().y;
//			sprite.setScale(scalex, scaley);
//			float x = position + 5;
//			float y = autoproductBoxes[first].first.getPosition().y + 5;
//			sprite.setPosition(x, y);
//			window.draw(autoproductBoxes[first].first);
//			window.draw(sprite);
//
//
//			int cnt = 0; // co the error
//			for (int i = first + 1; i < films.size(); i++) {
//				float pos = position + ++cnt * 200;
//				autoproductBoxes[i].first.setPosition(pos, 125);
//				sf::Texture texture;
//				if (!texture.loadFromFile(autoproductBoxes[i].second)) {
//					texture.loadFromFile("404.jfif");
//				}
//				sf::Sprite sprite(texture);
//				float scalex = 140.0 / texture.getSize().x;
//				float scaley = 190.0 / texture.getSize().y;
//				sprite.setScale(scalex, scaley);
//				float x = pos + 5;
//				float y = autoproductBoxes[i].first.getPosition().y + 5;
//				sprite.setPosition(x, y);
//				window.draw(autoproductBoxes[i].first);
//				window.draw(sprite);
//			}
//
//			for (int i = 0; i < first; i++) {
//				float pos = position + ++cnt * 200;
//				autoproductBoxes[i].first.setPosition(pos, 125);
//				sf::Texture texture;
//				if (!texture.loadFromFile(autoproductBoxes[i].second)) {
//					texture.loadFromFile("404.jfif");
//				}
//				sf::Sprite sprite(texture);
//				float scalex = 140.0 / texture.getSize().x;
//				float scaley = 190.0 / texture.getSize().y;
//				sprite.setScale(scalex, scaley);
//				float x = pos + 5;
//				float y = autoproductBoxes[i].first.getPosition().y + 5;
//				sprite.setPosition(x, y);
//				window.draw(autoproductBoxes[i].first);
//				window.draw(sprite);
//			}
//		}
//
//		if (isSearchResultActive) {
//			window.draw(boxDetail);
//			window.draw(detailSprite);
//			window.draw(detailText);
//			window.draw(textDescription);
//			window.draw(detailDescripton);
//		}
//
//		if (isSearchActive) {
//			for (std::pair<sf::Text, sf::RectangleShape> option : search)
//			{
//				if (option.first.getString() != "") {
//					window.draw(option.second);
//					window.draw(option.first);
//				}
//			}
//		}
//
//		// Hiển thị cửa sổ
//		window.display();
//	}
//
//	return 0;
//}