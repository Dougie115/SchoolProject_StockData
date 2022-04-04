#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
using namespace std;

template <class elemType>
class listType
{ 
public:
	bool isEmpty() const;
	bool isFull() const;
	int getLength() const;
	int getMaxSize() const;
	void sort();
	void print() const;
	void insertAt(const elemType& item, int position);
	listType(int listSize = 50);
	~listType();

protected:
	int maxSize;
	int length;
	elemType* list;
};

template <class elemType>
bool listType<elemType>::isEmpty() const
{ 
	return (length == 0);
}

template <class elemType>
bool listType<elemType>::isFull() const
{ 
	return (length == maxSize);
}

template <class elemType>
int listType<elemType>::getLength() const
{ 
	return length;
}

template <class elemType>
int listType<elemType>::getMaxSize() const
{ 
	return maxSize;
}

template <class elemType>
listType<elemType>::listType(int listSize)
{ 
	maxSize = listSize;
	length = 0;
	list = new elemType[maxSize];
}

template <class elemType>
listType<elemType>::~listType()
{ 
	delete[] list;
}

template <class elemType>
void listType<elemType>::sort()
{ 
	int i, j;
	int min;
	elemType temp;

	for (i = 0; i < length; i++)
	{
		min = i;
		for (j = i; j < length; ++j)
			if (list[j] < list[min])
				min = j;
		temp = list[i];
		list[i] = list[min];
		list[min] = temp;
	}
}

template <class elemType>
void listType<elemType>::print() const
{ 
	int i;
	for (i = 0; i < length; ++i)
		cout << list[i];
	cout << endl;
}

template <class elemType>
void listType<elemType>::insertAt(const elemType & item, int position)
{ 
	assert(position >= 0 && position < maxSize);
	list[position] = item;
	length++;
}


class Stock
{
	private:
	string stock_symbol;
	double opening_price;
	double closing_price;
	double today_high;
	double today_low;
	int number_of_shares;
	double previous_close_price;
	static double total_assets;
	double percent_gain_loss;
public:
	// stock information
	void setStock(string stock_symbol, double opening_price, double closing_price,
		double today_high, double today_low, int number_of_shares, double previous_close_price)
	{
		this->stock_symbol = stock_symbol;
		this->opening_price = opening_price;
		this->closing_price = closing_price;
		this->today_high = today_high;
		this->today_low = today_low;
		this->number_of_shares = number_of_shares;
		this->previous_close_price = previous_close_price;
	}
	//stock information
	void Print()
	{
		cout << "Stock name is " << stock_symbol << endl;
	}
	//different prices
	void show_different_prices()
	{
		cout << "today's opening price was " << opening_price << ", the closing was " << closing_price << ", today's high was " <<
			today_high << ", today's low was " << today_low << " Previous closing price is " << previous_close_price << endl;
	}
	//percent gain/loss
	void calculate_gain_loss()
	{
		percent_gain_loss = (closing_price - previous_close_price) / previous_close_price * 100;
	}
	//shares
	void show_number_of_shares()
	{
		cout << "Number of share is " << number_of_shares << endl;
	}
		bool operator> (Stock & cStock)
	{
		return (this->stock_symbol.compare(cStock.stock_symbol) > 0);
	}
	bool operator>= (Stock & cStock)
	{
		return (this->stock_symbol.compare(cStock.stock_symbol) >= 0);
	}
	bool operator< (Stock & cStock)
	{
		return (this->stock_symbol.compare(cStock.stock_symbol) < 0);
	}
	bool operator<= (Stock & cStock)
	{
		return (this->stock_symbol.compare(cStock.stock_symbol) <= 0);
	}
	bool operator==(Stock & cStock)
	{
		return (this->stock_symbol.compare(cStock.stock_symbol) == 0);
	}
	friend ostream& operator<< (ostream & out, Stock & cStock);
	friend istream& operator>> (istream & in, Stock & cStock);
	static double getTotalAssets()
	{
		return total_assets;
	}
};

istream& operator>>(istream & in, Stock & cStock)
{
	in >> cStock.stock_symbol;
	in >> cStock.opening_price;
	in >> cStock.closing_price;
	in >> cStock.today_high;
	in >> cStock.today_low;
	in >> cStock.previous_close_price;
	in >> cStock.number_of_shares;
	cStock.total_assets += cStock.number_of_shares * cStock.closing_price;
	return in;
}
ostream& operator<< (ostream & out, Stock & cStock)
{
	cStock.calculate_gain_loss();
	out << setw(8) << left << cStock.stock_symbol << right << fixed << setprecision(2) << setw(8) <<
	cStock.opening_price << fixed << setprecision(2) << setw(8) <<
	cStock.closing_price << fixed << setprecision(2) << setw(8) <<
	cStock.today_high << fixed << setprecision(2) << setw(8) <<
	cStock.today_low << fixed << setprecision(2) << setw(8) <<
	cStock.previous_close_price << fixed << setprecision(2) << setw(8) <<
	cStock.percent_gain_loss << fixed << setprecision(2) << setw(12) <<
	cStock.number_of_shares << endl;
	return out;
}
double Stock::total_assets = 0.0;
int main()
{
	ifstream infile("StockData.txt");
	listType<Stock> stock_array(50);
	Stock local_stock;
	int count = 0;
	if (!infile)
	{
		cout << "Unable to open file StockData.txt. so Exiting from program ";
		return 0;
	}
	while (!infile.eof())
	{
		infile >> local_stock;
		stock_array.insertAt(local_stock, count++);
	}
	stock_array.sort();
	cout << "*********************************"<< endl;
	cout << "Douglas J Lopez" << endl;
	cout << "Long Beach City College" << endl;
	cout << "CS 12 _ Stocks" << endl;
	cout << "May 5th 2019" << endl;
	cout << "*********************************" << endl;
	cout << "*************First Investors Heaven*****************" << endl;
	cout << "*************Financial Report*****************" << endl;
	cout << "Stock Today Previous Percent " << endl;
	cout << "Symbol     Open    Close   High    Low    Close   Gain       Volume" << endl;
	cout << "------     -----   -----   -----  ----- -------- -------      ------" << endl;
	stock_array.print();
	cout << "Closing Assets: $" << fixed << setprecision(2) << Stock::getTotalAssets() << endl;
	cout << "_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*" << endl;
	system("pause");
	return 0;
}