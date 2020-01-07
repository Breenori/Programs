#include<iostream>
#include<bitset>
#include<string>
#include<time.h>
using std::cout;
using std::cin;

int main()
{
	time_t tim = time(0);
	char const c('A');
	int const i(c);
	cout << "char: '" << c << "'" << std::endl;
	cout << "ASCII code (dec): " << i << std::endl;
	cout << "ASCII code (hex): 0x" << std::hex << i << std::endl;
	cout << "ASCII code (oct): 0" << std::oct << i << std::endl;
	cout << "ASCII code (bin): b" << std::bitset<8>(i) << std::endl;
	std::dec;

	std::string s("hello");
	std::string t("hagenberg");
	std::string u("\"" + s + " " + t + "\"");
	
	u[9] = 'x';
	cout << u;

	cout << std::endl;
	std::string in("");

	std::getline(std::cin, in);

	for (int i(0); i < in.length(); i++)
	{
		if ((in[i] >= 'A' && in[i] <= 'Z') || (in[i] >= 'a' && in[i] <= 'z'))
			cout << (char)(in[i] ^ (1 << 5)) << " ";
		else
			cout << in[i] << " "; 
	}
	cout << std::endl;

	in.insert(5, "xyz");
	in.replace(4, 3, "blabla");
	int pos = in.find("berg", 7);

	cout << in << " has berg at pos: " << pos << std::endl;

	t = in.substr(7, 5);
	
	cout << t << std::endl;

	srand((int)tim);
	int r = rand()%6;
	cout << r;
}