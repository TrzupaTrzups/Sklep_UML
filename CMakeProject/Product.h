#include <iostream>
#include <string>

using namespace std;

class Product
{
	int id;
	string name;
	double price;
	int stock;
	string category;

public:
	Product(int id, string name, double price, int stock, string category) : id(id), name(name), price(price), stock(stock), category(category)
	{

	}

	int getId() const
	{
		return id;
	}
	
	string getName() const
	{
		return name;
	}

	double getPrice() const
	{
		return price;
	}

	int getStock() const
	{
		return stock;
	}

	string getCategory() const
	{
		return category;
	}

	void setStock(int newStock)
	{
		stock = newStock;
	}

	void setPrice(double newPrice)
	{
		price = newPrice;
	}

	void setCategory(string newCategory)
	{
		category = newCategory;
	}

	void setName(string newName)
	{
		name = newName;
	}

};