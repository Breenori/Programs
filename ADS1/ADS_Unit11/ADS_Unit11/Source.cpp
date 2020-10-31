#include<iostream>
#include<string>
using namespace std;

struct name_type {
	std::string surname;
	std::string lastname;
};

enum color_type { black, red, blue, green };

enum gender_type { female, male, other };

enum language_type { german, english, spanish };

void greet(name_type name, gender_type gender, language_type language)
{
	if (language == spanish)
	{
		cout << "Buenos dias, ";
		if (gender == male)
		{
			cout << "senor " << name.surname;
		}
		else if (gender == female)
		{
			cout << "senorita " << name.surname;
		}
		else
		{
			cout << name.surname << " " << name.lastname;
		}
		cout << "!";
	}
}

void main()
{
	name_type name;
	name.surname = "Pritz";
	name.lastname = "Sebastian";

	greet(name, male, spanish);
	
}