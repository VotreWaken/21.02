#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
// Class Time
class Time
{
public:
	// Default Constructor
	Time()
	{
		time_t Times;
		time(&Times);
		struct tm* timeinfo;
		timeinfo = localtime(&Times);

		minutes_ = timeinfo->tm_min;
		hours_ = timeinfo->tm_hour;
		seconds_ = timeinfo->tm_sec;
	}
	// Int Constructor
	Time(int hour, int min, int sec) : seconds_(sec), minutes_(min), hours_(hour)
	{
		if (hour > 24 || min > 59 || sec > 59)
		{
			throw(std::domain_error("Time value out of range"));
		}
	};

	// Set Second
	void SetSeconds(int Seconds)
	{
		seconds_ = Seconds;
	}

	// Set Minutes
	void SetMinutes(int Minutes)
	{
		minutes_ = Minutes;
	}

	// Set Hours
	void SetHours(int Hours)
	{
		hours_ = Hours;
	}

	// Destructor
	~Time()
	{

	}

	// Overload Operator << 
	friend std::ostream& operator<<(std::ostream& out, const Time& t);

private:
	int seconds_;
	int minutes_;
	int hours_;
};
// Overload Operator << 
std::ostream& operator<<(std::ostream& out, const Time& t)
{
	auto oldfill = out.fill('0');
	return out << t.hours_
		<< ':' << std::setw(2) << t.minutes_
		<< ':' << std::setw(2) << t.seconds_ << std::setfill(oldfill);
}
// Class Date
class Date
{
public:

	// Constructor By Parametres
	Date(int day, int month, int year) : days_{ day }, month_{ month }, year_{ year }
	{
		if ((days_ > 31) || (month_ > 12))
		{
			throw(std::domain_error("Time value out of range"));
		}
	}

	// Default Constructor
	Date()
	{
		std::time_t t = std::time(0);
		std::tm* now = std::localtime(&t);
		days_ = now->tm_mday;
		month_ = now->tm_mon + 1;
		year_ = now->tm_year + 1900;
	}

	// Get Day
	constexpr int GetDay() const
	{
		return days_;
	}

	// Get Month
	constexpr int GetMonth() const
	{
		return month_;
	}

	// Get Year
	constexpr int GetYear() const
	{
		return year_;
	}

	// Set Day
	constexpr void SetDay(int days)
	{
		days_ = days;
	}

	// Set Month
	constexpr void SetMonth(int month)
	{
		month_ = month;
	}

	// Set Year
	constexpr void SetYear(int year)
	{
		year_ = year;
	}

	// Get Count of Days In Specific Month
	constexpr static int GetDaysInMonth(int index)
	{
		return days[index - 1];
	}

	// Overload Operator "<<"
	friend std::ostream& operator<< (std::ostream& out, const Date& Date);

	// Destructor
	~Date()
	{

	}

private:
	int days_;
	int month_;
	int year_;
	constexpr static int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
};
std::ostream& operator<< (std::ostream& out, const Date& Date)
{
	const char* Month[] =
	{ "January","February","March","April","May","June","July","August","September","October","November","December" };

	out << "Date: " << Date.GetDay() << "." << Date.GetYear() << " " << Month[Date.GetMonth() - 1] << "\n";

	return out;
}
// Class Money Storage
class Spendings
{
private:
	double amount_;
	Time curTime_;
	Date date_;
	std::string category_;
public:

	// Constructor by Parametres
	Spendings(std::string name, double amount, Time currentTime, Date date) :
		category_(name), amount_(amount), curTime_(currentTime), date_(date)
	{

	}

	// Default Constructor
	Spendings()
	{
		amount_ = 0;
	}

	// Input All
	void Input()
	{
		InputTime();
		InputDate();
		InputCategory();
		InputAmount();
	}

	// Input Time 
	void InputTime()
	{
		Time temp;
		int seconds;
		std::cout << "Enter Seconds: \n";
		std::cin >> seconds;
		temp.SetSeconds(seconds);
		std::cout << "Enter Minutes: \n";
		int minutes;
		std::cin >> minutes;
		temp.SetMinutes(minutes);
		std::cout << "Enter Hours: \n";
		int hours;
		std::cin >> hours;
		temp.SetHours(hours);
		curTime_ = temp;
	}

	// Input Date
	void InputDate()
	{
		Date temp;
		int Day;
		std::cout << "Enter Day: \n";
		std::cin >> Day;
		temp.SetDay(Day);
		std::cout << "Enter Month: \n";
		int Month;
		std::cin >> Month;
		temp.SetMonth(Month);
		std::cout << "Enter Year: \n";
		int Year;
		std::cin >> Year;
		temp.SetYear(Year);
		std::cin.ignore();
		date_ = temp;
	}

	// Input Category
	void InputCategory()
	{
		std::cout << "Enter Category: \n";
		std::string category;
		std::cin >> category;
		category_ = category;
	}

	// Input Amount
	void InputAmount()
	{
		std::cout << "Enter Amount: \n";
		int amount;
		std::cin >> amount;
		amount_ = amount;
	}

	// Output
	void Output()
	{
		std::cout << "Category: " << category_ << "\n";
		std::cout << "Amount: " << amount_ << "\n";
		std::cout << "Date: " << date_ << "\n";
		std::cout << "Time: " << curTime_ << "\n";
	}

	// Get Amount
	double GetMoney() const
	{
		return amount_;
	}

	// Get Category
	std::string GetCategory() const
	{
		return category_;
	}

	// Get Date
	const Date GetDate() const { return date_; }

	// Get Time
	const Time GetTime() const { return curTime_; }

	// Overload Operator "<<"
	friend std::ostream& operator<< (std::ostream& out, const Spendings& spend)
	{
		out << "Category: " << spend.category_ << "\n Amount: " << spend.amount_ << "\n"
			<< spend.curTime_ << spend.date_;
		return out;
	}

	// For Insert to Multiset
	bool operator<(const Spendings& rhs) const noexcept
	{
		return this->amount_ < rhs.amount_;
	}

	// Destructor
	~Spendings()
	{

	}
private:

};

class MoneyStorage
{
protected:
	int totalAmount_;
	bool creditLimit_;
	std::multiset<Spendings> spendings_;
public:
	
	// Constructor By Parametres
	MoneyStorage(int totalAmount, int LimitValue)
	{
		totalAmount_ = totalAmount;
		creditLimit_ = LimitValue;
	}

	// Initialize Spending
	void Input()
	{
		Spendings temp;
		temp.Input();
		spendings_.insert(temp);
	}

	void Output()
	{
		for (auto it = spendings_.begin(); it != spendings_.end(); it++)
		{
			std::cout << *it << " ";
		}
	}

	// Default Constructor
	MoneyStorage()
	{
		totalAmount_ = 0;
		creditLimit_ = 0;
	}

	// Destrucotr
	~MoneyStorage()
	{

	}
};
// Class Card
class Card : public MoneyStorage
{
	std::string bankName_;
public:

	Card() : MoneyStorage()
	{

	}
	Card(int num, std::string name, float credit = 0)
	{
		bankName_ = name;
		totalAmount_ = num;
		creditLimit_ = credit;
	}
	virtual void Output()
	{
		std::cout << bankName_ << "\n";
		std::cout << totalAmount_ << "\n";
		std::cout << creditLimit_ << "\n";
	}
	void Input()
	{
		MoneyStorage::Input();
	}
	~Card()
	{

	}
};

// Derived class for debit cards
class DebitCard : public Card
{
protected:

public:

	// Constructor
	DebitCard(std::string& Name, int LimitValue) : Card(LimitValue, Name)
	{

	}
	// Display Card To Screen
	virtual void print()
	{
		std::cout << "Debit Card Details\n";
		Card::Output();
	}
};

// Derived class for credit cards
class CreditCard : public Card
{
protected:
	float credit_limit;

public:
	// Constructor
	CreditCard(std::string& Name, int LimitValue, float credit_limit) : Card(LimitValue, Name, credit_limit)
	{

	}

	// Display Card To Screen
	virtual void print()
	{
		std::cout << "Credit Card Details\n";
		Card::Output();
		std::cout << "Credit Limit: $" << credit_limit << "\n";
	}
};

class Wallet
{
protected:
	// Wallet Fields
	std::vector<Card*> cards;
public:

	// Add Card To Wallet
	virtual void addCard(Card* card)
	{
		cards.push_back(card);
	}

	// Print all Cards In Wallet
	virtual void printCards()
	{
		for (Card* card : cards)
		{
			card->Output();
			std::cout << "\n";
		}
	}
};
// Derived class for online wallets
class OnlineWallet : public Wallet
{
public:
	// Add Card To Wallet
	void addCard(Card* card)
	{
		if (dynamic_cast<DebitCard*>(card))
		{
			cards.push_back(card);
		}
		else {
			std::cout << "Only debit cards can be added to an online wallet.\n";
		}
	}

	// Print all Cards In Wallet
	virtual void printCards()
	{
		std::cout << "Online Wallet Cards\n";
		Wallet::printCards();
	}
};

// Derived class for physical wallets
class PhysicalWallet : public Wallet
{
public:
	// Add Card To Wallet
	void addCard(Card* card)
	{
		if (dynamic_cast<CreditCard*>(card))
		{
			cards.push_back(card);
		}
		else
		{
			std::cout << "Only credit cards can be added to a physical wallet.\n";
		}
	}

	// Print all Cards In Wallet
	virtual void printCards()
	{
		std::cout << "Physical Wallet Cards\n";
		Wallet::printCards();
	}
};
int main()
{
	
}
