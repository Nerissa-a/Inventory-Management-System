#include<iostream>
using namespace std;
const int Low_Stock_Threshold=5;
const int Max_Products=100;
class Product
{
protected:
    int productId;
    string name,category;
    int quantity,price;
public:
    Product()
    {
        productId=0;
        name="";
        category="";
        quantity=0;
        price=0;
    }

    Product(int i,string n,string c,int q,int p)
    {
        productId=i;
        name=n;
        category=c;
        quantity=q;
        price=p;
    }
    virtual void displayProductDetails()
    {
        cout<<"Product ID:"<<productId<<"  "
            <<"Name:"<<name<<"  "
            <<"Category:"<<category<<"  "
            <<"Quantity:"<<quantity<<"  "
            <<"Price per Item:"<<price<<"  "
            <<"Total value:"<<price*quantity<<endl;
    }
    int updateStock(int change)
    {
        if(quantity+change<0)
        {
            cout<<"Stock can't be negative. Operation canceled!"<<endl;
            return 0;
        }
        else
        {
            quantity+=change;
            return 1;
        }
    }
    int isLowStock()
    {
        if(quantity<Low_Stock_Threshold)
        {
            return 1;
        }
        else
            return 0;
    }
    int getId()
    {
        return productId;
    }
};

class Inventory:public Product
{
    Product products[Max_Products];
    static int productCount;
public:
     void addProduct()
    {
        if(productCount>=Max_Products)
        {
            cout<<"Inventory full! Cannot add more products."<<endl;
                return;
        }
        int i,q,p;
        string n,c;
        cout<<"Enter Product ID:";
        cin>>i;
        cout<<"Enter Product Name:";
        cin>>n;
        cout<<"Enter Category:";
        cin>>c;
        cout<<"Enter Quantity:";
        cin>>q;
        cout<<"Enter Price per Item: ";
        cin>>p;
        products[productCount]=Product(i,n,c,q,p);
        productCount++;
        cout<<"Product added successfully."<<endl;
    }
    void updateProductStock()
    {
        if(productCount==0)
        {
            cout<<"Inventory is empty! Please add products first."<<endl;
            return;
        }
        int id,change;
        cout<<"Enter Product id to update:";
        cin>>id;
        int flag=0;
        for(int i=0;i<productCount;i++)
        {
            if(products[i].getId()==id)
            {
                cout<<"Enter quantity change(+restock,-sell):";
                cin>>change;
                products[i].updateStock(change);
                flag=1;
            }
        }
        if(flag==0)
        {
            cout<<"Product not found. Enter existing product id."<<endl;
            return;
        }
    }
    void generateInventoryReport()
    {
        if(productCount==0)
        {
            cout<<"Inventory is empty! Please add products first."<<endl;
        }
      cout<<"Inventory Report:"<<endl;
      for(int i=0;i<productCount;i++)
      {
          products[i].displayProductDetails();
      }
    }
    void checkLowStockReport()
    {
        if(productCount==0)
        {
            cout<<"Inventory is empty! Please add products first."<<endl;
            return;
        }
      cout<<"Low stock Report:"<<endl;
      int flag=0;
      for(int i=0;i<productCount;i++)
      {
          if(products[i].isLowStock())
          {
              flag=1;
              products[i].displayProductDetails();
          }
      }
      if(flag==0)
        cout<<"No product found is in low stock."<<endl;

    }
    void displayProductDetails()
    {
        cout<<"    [Inventory is not a single product,    "<<endl
            <<"   it manages the collection of products.   "<<endl;
    }
};
int Inventory::productCount;
int main()
{
    Product *ptr;
    Product p;
    Inventory inventory;
    ptr=&inventory;
    ptr->displayProductDetails();

    int choice;
    cout<<"     <-Inventory Management System->      "<<endl;
        cout<<"1.Add Product"<<endl;
        cout<<"2.Update Product Stock"<<endl;
        cout<<"3.Generate Inventory Report"<<endl;
        cout<<"4.Generate Low Stock Report"<<endl;
        cout<<"5.Exit"<<endl;
    do {
        cout<<"Enter choice:";
        cin>>choice;

        switch(choice)
        {
            case 1:
                inventory.addProduct();
                break;
            case 2:
                inventory.updateProductStock();
                break;
            case 3:
                inventory.generateInventoryReport();
                break;
            case 4:
                inventory.checkLowStockReport();
                break;
            case 5:
                cout<<"Exit"<<endl;
                break;
            default:
                cout<<"Invalid choice! Try again."<<endl;
        }
    } while(choice!=5);

    return 0;

}
