#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>
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
//bool isMouseOver(sf::RectangleShape& button, sf::Event event)
//{
//	return button.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y);
//}
// 
// bool isMouseOver(sf::RectangleShape& rect, sf::RenderWindow& window)
//{
//    sf::FloatRect bounds = rect.getGlobalBounds();
//    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
//    return bounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
//}
//
//bool isMouseOver(sf::Text& option, sf::RenderWindow& window)
//{
//    sf::FloatRect bounds = option.getGlobalBounds();
//    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
//    return bounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
//}
//
//int createAdminWindow() {
//	sf::RenderWindow window(sf::VideoMode(1280, 720), "Admin");
//
//	// Tải ảnh từ file trên hệ thống
//	sf::Texture texture;
//	if (!texture.loadFromFile("image.jfif"))
//		return EXIT_FAILURE;
//
//	// Tạo sprite sử dụng texture đã tải
//	sf::Sprite sprite(texture);
//
//	// Lấy kích thước của cửa sổ
//	sf::Vector2u windowSize = window.getSize();
//
//	// Tính toán tỷ lệ giữa kích thước ảnh và kích thước cửa sổ
//	float scaleX = static_cast<float>(windowSize.x) / texture.getSize().x;
//	float scaleY = static_cast<float>(windowSize.y) / texture.getSize().y;
//
//	// Đặt tỷ lệ kích thước cho sprite
//	sprite.setScale(scaleX, scaleY);
//
//	// Đặt vị trí của sprite
//	sprite.setPosition(0, 0);
//
//	// Vòng lặp chính
//	while (window.isOpen())
//	{
//		// Xử lý các sự kiện
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//
//		// Xóa cửa sổ
//		window.clear();
//
//		// Vẽ sprite lên cửa sổ
//		window.draw(sprite);
//
//		// Hiển thị cửa sổ
//		window.display();
//	}
//}
//
//int createLoginAdminWindow() {
//
//	sf::RenderWindow window(sf::VideoMode(800, 600), "Admin");
//	
//	bool login = true;
//	bool homePageAdmin = false;
//
//	// Tạo các thành phần giao diện
//	sf::Font font;
//	if (!font.loadFromFile("ShortBaby-Mg2w.ttf"))
//	{
//		std::cout << "Failed to load font!" << std::endl;
//		return -1;
//	}
//
//	//login////////////////////////////////////////////////////////
//	sf::RectangleShape button1(sf::Vector2f(500, 50));
//	button1.setFillColor(sf::Color::White);
//	button1.setPosition(100, 100);
//
//	sf::Text inputText1;
//	inputText1.setFont(font);
//	inputText1.setCharacterSize(24);
//	inputText1.setFillColor(sf::Color::Black);
//	//inputText1.setPosition(button1.getPosition().x + button1.getSize().x / 2 - inputText1.getGlobalBounds().width / 2,
//	//    button1.getPosition().y + button1.getSize().y / 2 - inputText1.getGlobalBounds().height / 2);
//	inputText1.setPosition(100, 107);
//
//	/*sf::Text inputText1;
//	inputText1.setFont(font);
//	inputText1.setCharacterSize(24);
//	inputText1.setPosition(100, 100);
//	inputText1.setFillColor(sf::Color::White);*/
//
//	sf::RectangleShape button2(sf::Vector2f(500, 50));
//	button2.setFillColor(sf::Color::White);
//	button2.setPosition(100, 200);
//
//	sf::Text inputText2;
//	inputText2.setFont(font);
//	inputText2.setCharacterSize(24);
//	inputText2.setFillColor(sf::Color::Black);
//	//inputText2.setPosition(button2.getPosition().x + button2.getSize().x / 2 - inputText2.getGlobalBounds().width / 2,
//	//    button2.getPosition().y + button2.getSize().y / 2 - inputText2.getGlobalBounds().height / 2);
//	inputText2.setPosition(100, 207);
//
//	//sf::Text inputText2;
//	//inputText2.setFont(font);
//	//inputText2.setCharacterSize(24);
//	//inputText2.setPosition(100, 200);
//	//inputText2.setFillColor(sf::Color::White);
//
//	sf::RectangleShape loginbutton(sf::Vector2f(100, 50));
//	loginbutton.setFillColor(sf::Color::White);
//	loginbutton.setPosition(250, 300);
//	loginbutton.setFillColor(sf::Color(238, 100, 87));
//
//	sf::Text loginbuttonText;
//	loginbuttonText.setFont(font);
//	loginbuttonText.setString("Login");
//	loginbuttonText.setCharacterSize(24);
//	loginbuttonText.setPosition(250, 300);
//	loginbuttonText.setFillColor(sf::Color::Black);
//
//	bool isInput1Active = false;
//	bool isInput2Active = false;
//	//login////////////////////////////////////////////////////////
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
//			else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
//			{
//				if (loginbutton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
//				{
//					std::string currenttext1 = inputText1.getString();
//					std::string currenttext2 = inputText2.getString();
//					if (currenttext1 == "admin" && currenttext2 == "password") {
//						/*createAdminWindow();*/
//						login = false;
//						homePageAdmin = true;
//					}
//				}
//				if (isMouseOver(button1, event))
//				{
//					button1.setFillColor(sf::Color::Yellow);
//					isInput1Active = true;
//					isInput2Active = false;
//					button2.setFillColor(sf::Color::White);
//				}
//				else if (isMouseOver(button2, event))
//				{
//					button2.setFillColor(sf::Color::Yellow);
//					isInput1Active = false;
//					isInput2Active = true;
//					button1.setFillColor(sf::Color::White);
//				}
//				else {
//					button1.setFillColor(sf::Color::White);
//					button2.setFillColor(sf::Color::White);
//				}
//			}
//			else if (event.type == sf::Event::TextEntered)
//			{
//				if (isInput1Active)
//				{
//					if (event.text.unicode < 128)
//					{
//						if (event.text.unicode == '\b' && !inputText1.getString().isEmpty())
//						{
//							std::string currentText = inputText1.getString();
//							currentText.pop_back();
//							inputText1.setString(currentText);
//						}
//						else
//						{
//							inputText1.setString(inputText1.getString() + static_cast<char>(event.text.unicode));
//						}
//					}
//				}
//				else if (isInput2Active)
//				{
//					if (event.text.unicode < 128)
//					{
//						if (event.text.unicode == '\b' && !inputText2.getString().isEmpty())
//						{
//							std::string currentText = inputText2.getString();
//							currentText.pop_back();
//							inputText2.setString(currentText);
//						}
//						else
//						{
//							inputText2.setString(inputText2.getString() + static_cast<char>(event.text.unicode));
//						}
//					}
//				}
//			}
//		}
//
//		window.clear();
//		
//		//login
//		if (login) {
//			window.draw(button1);
//			window.draw(inputText1);
//			window.draw(button2);
//			window.draw(inputText2);
//			window.draw(loginbutton);
//		}
//		//login
//
//		window.display();
//	}
//}
//
//int createDashboardWindow() {
//	sf::RenderWindow window(sf::VideoMode(1280, 720), "Home");
//
//	// Tải ảnh từ file trên hệ thống
//	sf::Texture texture;
//	if (!texture.loadFromFile("image.jfif"))
//		return EXIT_FAILURE;
//
//	// Tạo sprite sử dụng texture đã tải
//	sf::Sprite sprite(texture);
//
//	// Lấy kích thước của cửa sổ
//	sf::Vector2u windowSize = window.getSize();
//
//	// Tính toán tỷ lệ giữa kích thước ảnh và kích thước cửa sổ
//	float scaleX = static_cast<float>(windowSize.x) / texture.getSize().x;
//	float scaleY = static_cast<float>(windowSize.y) / texture.getSize().y;
//
//	// Đặt tỷ lệ kích thước cho sprite
//	sprite.setScale(scaleX, scaleY);
//
//	// Đặt vị trí của sprite
//	sprite.setPosition(0, 0);
//
//	// Vòng lặp chính
//	while (window.isOpen())
//	{
//		// Xử lý các sự kiện
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//
//		// Xóa cửa sổ
//		window.clear();
//
//		// Vẽ sprite lên cửa sổ
//		window.draw(sprite);
//
//		// Hiển thị cửa sổ
//		window.display();
//	}
//
//}
//
//int main()
//{
//	// Tạo cửa sổ kích thước 800x600 pixels
//	sf::RenderWindow window(sf::VideoMode(1280, 720), "Cinema");
//
//	//TEXT CLOCK
//	sf::Font fontClock;
//	if (!fontClock.loadFromFile("Wallpoet-Regular.ttf"))
//		return EXIT_FAILURE;
//
//	// Tạo văn bản sử dụng font đã tải
//	sf::Text textClock("", fontClock, 24);
//	textClock.setPosition(0, 10);
//	//TEXT CLOCK
//
//	// tải ảnh từ file trên hệ thống
//	sf::Texture texture;
//	if (!texture.loadFromFile("movie.jpg"))
//		return EXIT_FAILURE;
//
//	// tạo sprite sử dụng texture đã tải
//	sf::Sprite sprite(texture);
//
//	// lấy kích thước của cửa sổ
//	sf::Vector2u windowsize = window.getSize();
//
//	// tính toán tỷ lệ giữa kích thước ảnh và kích thước cửa sổ
//	float scalex = static_cast<float>(windowsize.x) / texture.getSize().x;
//	float scaley = static_cast<float>(windowsize.y) / texture.getSize().y;
//
//	// đặt tỷ lệ kích thước cho sprite
//	sprite.setScale(scalex, scaley);
//
//	// đặt vị trí của sprite
//	sprite.setPosition(0, 0);
//
//
//	// Tạo nút để chuyển sang trang khác
//		//sf::RectangleShape button(sf::Vector2f(200, 50));
//		////sf::CircleShape button(50, 100);
//		//button.setFillColor(sf::Color(139, 216, 189));
//		//button.setPosition(300, 250);
//
//	sf::CircleShape button1(25);
//	button1.setFillColor(sf::Color(139, 216, 189)); // Màu xám
//	button1.setOutlineThickness(5);
//	button1.setOutlineColor(sf::Color(150, 150, 150)); // Màu xám nhạt
//	button1.setPosition(1100, 10);
//
//	sf::CircleShape button2(25);
//	button2.setFillColor(sf::Color(139, 216, 189)); // Màu xám
//	button2.setOutlineThickness(5);
//	button2.setOutlineColor(sf::Color(150, 150, 150)); // Màu xám nhạt
//	button2.setPosition(1000, 10);
//
//	sf::Texture texture1;
//	if (!texture1.loadFromFile("admin-icon-png-4.jpg"))
//	{
//		std::cout << "Failed to load icon." << std::endl;
//		return -1;
//	}
//	sf::Sprite iconSprite1(texture1);
//	iconSprite1.setScale(0.2f, 0.2f);
//	iconSprite1.setPosition(1105, 12);
//
//	sf::Texture texture2;
//	if (!texture2.loadFromFile("icon-home-removebg-preview.png"))
//	{
//		std::cout << "Failed to load icon." << std::endl;
//		return -1;
//	}
//	sf::Sprite iconSprite2(texture2);
//	iconSprite2.setScale(0.1f, 0.1f);
//	iconSprite2.setPosition(994, 12);
//
//	/*sf::Font font;
//	if (!font.loadFromFile("ShortBaby-Mg2w.ttf"))
//		return EXIT_FAILURE;
//
//	sf::Text text("Click táo!", font, 24);
//	text.setFillColor(sf::Color::Red);
//	text.setPosition(button.getPosition().x + button.getSize().x / 2 - text.getGlobalBounds().width / 2,
//		button.getPosition().y + button.getSize().y / 2 - text.getGlobalBounds().height / 2);*/
//
//		// Vòng lặp chính
//	while (window.isOpen())
//	{
//		// Xử lý các sự kiện
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//
//			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
//			{
//				// Kiểm tra xem người dùng đã ấn vào nút hay chưa
//				if (button1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
//				{
//					createLoginAdminWindow();
//				}
//				if (button2.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
//				{
//					createDashboardWindow();
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
//		std::strftime(buf, sizeof(buf), "%Y-%m-%d | %H:%M:%S", &time_info);
//
//		// Cập nhật văn bản hiển thị trên đồng hồ
//		textClock.setString(buf);
//
//		// Xóa cửa sổ
//		window.clear();
//
//		// Vẽ các đối tượng lên cửa sổ
//		window.draw(sprite);
//		window.draw(textClock);
//		window.draw(button1);
//		window.draw(button2);
//		window.draw(iconSprite1);
//		window.draw(iconSprite2);
//		//window.draw(text);
//
//		// Hiển thị cửa sổ
//		window.display();
//	}
//
//	return 0;
//}



//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <string>
//#include <vector>
//

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

//int main()
//{
//    // Tạo cửa sổ kích thước 800x600 pixels
//    sf::RenderWindow window(sf::VideoMode(800, 600), "Dropdown");
//
//    // Tạo các thành phần giao diện
//    sf::Font font;
//    if (!font.loadFromFile("ShortBaby-Mg2w.ttf"))
//    {
//        std::cout << "Failed to load font!" << std::endl;
//        return -1;
//    }
//
//    sf::RectangleShape dropdownBox(sf::Vector2f(200, 50));
//    dropdownBox.setFillColor(sf::Color::White);
//    dropdownBox.setOutlineThickness(2);
//    dropdownBox.setOutlineColor(sf::Color::Black);
//    dropdownBox.setPosition(100, 100);
//
//    sf::Text dropdownText("Select an option", font, 24);
//    dropdownText.setFillColor(sf::Color::Black);
//    dropdownText.setPosition(110, 110);
//
//    std::vector< std::pair<sf::Text, sf::RectangleShape> > options;
//    sf::RectangleShape option1Box(sf::Vector2f(200, 50));
//    option1Box.setFillColor(sf::Color::White);
//    option1Box.setOutlineThickness(2);
//    option1Box.setOutlineColor(sf::Color::Black);
//    option1Box.setPosition(100, 150);
//
//    sf::Text option1("Option 1", font, 24);
//    option1.setPosition(110, 160);
//    option1.setFillColor(sf::Color::Black);
//    options.push_back({ option1 , option1Box });
//
//    sf::RectangleShape option2Box(sf::Vector2f(200, 50));
//    option2Box.setFillColor(sf::Color::White);
//    option2Box.setOutlineThickness(2);
//    option2Box.setOutlineColor(sf::Color::Black);
//    option2Box.setPosition(100, 200);
//
//    sf::Text option2("Option 2", font, 24);
//    option2.setPosition(110, 210);
//    option2.setFillColor(sf::Color::Black);
//    options.push_back({ option2 , option2Box });
//
//    sf::RectangleShape option3Box(sf::Vector2f(200, 50));
//    option3Box.setFillColor(sf::Color::White);
//    option3Box.setOutlineThickness(2);
//    option3Box.setOutlineColor(sf::Color::Black);
//    option3Box.setPosition(100, 250);
//
//    sf::Text option3("Option 3", font, 24);
//    option3.setPosition(110, 260);
//    option3.setFillColor(sf::Color::Black);
//    options.push_back({ option3 , option3Box });
//
//    bool isDropdownActive = false;
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//            {
//                window.close();
//            }
//            else if (event.type == sf::Event::MouseButtonPressed)
//            {
//                if (isMouseOver(dropdownBox, window))
//                {
//                    dropdownBox.setFillColor(sf::Color(111, 110, 111));
//                    isDropdownActive = !isDropdownActive;
//                }
//                else if (isDropdownActive)
//                {
//                    for (std::pair<sf::Text, sf::RectangleShape> option : options)
//                    {
//                        if (isMouseOver(option.second, window))
//                        {
//                            dropdownText.setString(option.first.getString());
//                            dropdownBox.setFillColor(sf::Color::White);
//                            isDropdownActive = false;
//                            break;
//                        }
//                    }
//                }
//            }
//        }
//
//        window.clear(sf::Color::White);
//
//        window.draw(dropdownBox);
//        window.draw(dropdownText);
//
//        if (isDropdownActive)
//        {
//            for (const std::pair<sf::Text, sf::RectangleShape> option : options)
//            {
//                window.draw(option.second);
//                window.draw(option.first);
//            }
//        }
//
//        window.display();
//    }
//
//    return 0;
//}

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
//			//productBoxes[i].second.setPosition(productBoxes[i - 1].second.getPosition());
//			productBoxes[i].second.first.setPosition(textX, 600);
//		}
//
//		productBoxes[0].first.setPosition(newPos);
//		//productBoxes[0].second.setPosition(newPos.x + 10, newPos.y + 10);
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

int main()
{
	// Tạo cửa sổ kích thước 800x600 pixels
	sf::RenderWindow window(sf::VideoMode(1195, 672), "Drawing Line");

	sf::RectangleShape thickLine(sf::Vector2f(1195, 3));
	thickLine.setFillColor(sf::Color::Red);
	thickLine.setPosition(0, 100);


	//////////////////////Order//////////////////
	sf::Texture texture;
	if (!texture.loadFromFile("order.jpg"))
		return EXIT_FAILURE;

	// tạo sprite sử dụng texture đã tải
	sf::Sprite sprite(texture);
	sf::Vector2u windowsize = window.getSize();
	float scalex = 1195.0 / texture.getSize().x;
	float scaley = 572.0 / texture.getSize().y;
	sprite.setScale(scalex, scaley);
	sprite.setPosition(0, 100);

	std::pair<sf::RectangleShape, bool> box[3][12][6];
	//vector< std::pair<sf::RectangleShape, bool>> box[12][6];

	double x_0 = 157, y_0 = 277;
	double delta_x = 74.5, delta_y = 64;

	for (int k = 0; k < 3; k++) {
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 6; j++) {
				double x = x_0 + i * delta_x, y = y_0 + j * delta_y;
				box[k][i][j].second = false;
				box[k][i][j].first.setSize(sf::Vector2f(59, 52));
				box[k][i][j].first.setFillColor(sf::Color(238, 100, 87)); //100, 238, 87
				box[k][i][j].first.setOutlineThickness(2);
				box[k][i][j].first.setOutlineColor(sf::Color::Black);
				box[k][i][j].first.setPosition(x, y);
			}
		}
	}


	//////////////////////Order//////////////////

	///////////////////////////////////

	sf::Font font;
	if (!font.loadFromFile("SVN-Times New Roman Bold.ttf"))
	{
		std::cout << "Failed to load font!" << std::endl;
		return -1;
	}

	//bool selectButton[3]; memset(selectButton, false, 3);
	bool homePageButton = true;
	bool selectDropDownButton = false;
	bool selectAndUpdateButton = false; int indexButton = 0;
	bool createButtonActive = false;

	sf::Text homePageText("HomePage", font, 24);
	homePageText.setFillColor(sf::Color::Black);
	homePageText.setPosition(500, 500);

	sf::CircleShape button1(25);
	button1.setFillColor(sf::Color(139, 216, 189)); // Màu xám
	button1.setOutlineThickness(5);
	button1.setOutlineColor(sf::Color(150, 150, 150)); // Màu xám nhạt
	button1.setPosition(100, 25);

	sf::Texture texture1;
	if (!texture1.loadFromFile("icon-home-removebg-preview.png"))
	{
		std::cout << "Failed to load icon." << std::endl;
		return -1;
	}
	sf::Sprite iconSprite1(texture1);
	iconSprite1.setScale(0.1f, 0.1f);
	iconSprite1.setPosition(94, 28);
	///////////////////////////////////

	//////////////////dropdown/////////////////////////

	sf::RectangleShape dropdownBox(sf::Vector2f(125, 50));
	dropdownBox.setFillColor(sf::Color::White);
	dropdownBox.setOutlineThickness(2);
	dropdownBox.setOutlineColor(sf::Color::Black);
	dropdownBox.setPosition(300, 25);

	sf::Text dropdownText("Room", font, 24);
	dropdownText.setFillColor(sf::Color::Black);
	dropdownText.setPosition(320, 35);

	std::vector< std::pair<sf::Text, sf::RectangleShape> > options;
	sf::RectangleShape option1Box(sf::Vector2f(125, 50));
	option1Box.setFillColor(sf::Color::White);
	option1Box.setOutlineThickness(2);
	option1Box.setOutlineColor(sf::Color::Black);
	option1Box.setPosition(300, 75);

	sf::Text option1("Room 1", font, 24);
	option1.setPosition(323, 85);
	option1.setFillColor(sf::Color::Black);
	options.push_back({ {option1} , option1Box });

	sf::RectangleShape option2Box(sf::Vector2f(125, 50));
	option2Box.setFillColor(sf::Color::White);
	option2Box.setOutlineThickness(2);
	option2Box.setOutlineColor(sf::Color::Black);
	option2Box.setPosition(300, 125);

	sf::Text option2("Room 2", font, 24);
	option2.setPosition(323, 135);
	option2.setFillColor(sf::Color::Black);
	options.push_back({ {option2} , option2Box });

	sf::RectangleShape option3Box(sf::Vector2f(125, 50));
	option3Box.setFillColor(sf::Color::White);
	option3Box.setOutlineThickness(2);
	option3Box.setOutlineColor(sf::Color::Black);
	option3Box.setPosition(300, 175);

	sf::Text option3("Room 3", font, 24);
	option3.setPosition(323, 185);
	option3.setFillColor(sf::Color::Black);
	options.push_back({ {option3} , option3Box });

	bool isDropdownActive = false;

	sf::ConvexShape arrow(3);
	arrow.setPoint(0, sf::Vector2f(0, 0));
	arrow.setPoint(1, sf::Vector2f(15, 0));
	arrow.setPoint(2, sf::Vector2f(7.5, 7.5));
	arrow.setFillColor(sf::Color::Black);
	arrow.setPosition(405, 47);
	bool isArrowDownUp = true;

	//////////////////dropdown/////////////////////////

	/////////////////create////////////////////////////

	sf::RectangleShape createButton(sf::Vector2f(125, 50));
	createButton.setFillColor(sf::Color::White);
	createButton.setOutlineThickness(2);
	createButton.setOutlineColor(sf::Color::Black);
	createButton.setPosition(600, 25);

	sf::Text createButtonText("Create", font, 24);
	createButtonText.setFillColor(sf::Color::Black);
	createButtonText.setPosition(630, 35);

	/////////////////create////////////////////////////


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				// Kiểm tra xem người dùng đã ấn vào nút hay chưa
				if (button1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					homePageButton = true;
					selectDropDownButton = false;
					selectAndUpdateButton = false;
					indexButton = 0;
				}
				if (isMouseOver(dropdownBox, window))
				{
					dropdownBox.setFillColor(sf::Color(111, 110, 111));
					isDropdownActive = !isDropdownActive;
				}
				else if (isDropdownActive)
				{
					for (int i = 0; i < 3; i++) {
						{
							//option.first.second = false;
							if (isMouseOver(options[i].second, window))
							{
								dropdownText.setString(options[i].first.getString());
								indexButton = i + 1;
								cout << i << indexButton << endl;
								dropdownBox.setFillColor(sf::Color::White);
								isDropdownActive = false;
								isArrowDownUp = true;
								homePageButton = false;  selectDropDownButton = true; selectAndUpdateButton = true;
								break;
							}
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
			}

		}
		window.clear(sf::Color::White);

		//if (homePageAdmin) {
		window.draw(button1);
		window.draw(iconSprite1);
		//}

		if (homePageButton) {
			window.draw(homePageText);
		}

		if (selectDropDownButton) {
			window.draw(sprite);
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

		window.draw(thickLine);

		window.draw(dropdownBox);
		window.draw(dropdownText);
		if (isArrowDownUp) {
			arrow.setPoint(0, sf::Vector2f(0, 0));
			arrow.setPoint(1, sf::Vector2f(15, 0));
			arrow.setPoint(2, sf::Vector2f(7.5, 7.5));
			arrow.setFillColor(sf::Color::Black);
			window.draw(arrow);
		}

		if (isDropdownActive)
		{
			isArrowDownUp = false;
			arrow.setPoint(0, sf::Vector2f(7.5, 0));
			arrow.setPoint(1, sf::Vector2f(0, 7.5));
			arrow.setPoint(2, sf::Vector2f(15, 7.5));
			arrow.setFillColor(sf::Color::Black);
			window.draw(arrow);

			for (const std::pair<sf::Text, sf::RectangleShape> option : options)
			{
				window.draw(option.second);
				window.draw(option.first);
			}
		}

		window.draw(createButton);
		window.draw(createButtonText);

		window.display();
	}
}