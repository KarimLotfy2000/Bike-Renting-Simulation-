#include<cstdlib>
#include<iostream>
using namespace std;
class DayOfYear
{
private:
unsigned short int dayOfYear, year;
static const int days[];
public:
DayOfYear()
{
dayOfYear = 1;
year = 2021;
}
DayOfYear(int d,int m,int y)
{
dayOfYear = d + days[m-1];
year = y;
}
int get_dayOfYear()
{
return dayOfYear;
}
DayOfYear& operator++()
{
if(this->dayOfYear!=365)
{
this->dayOfYear++;
}
else
{
this->year++;
this->dayOfYear = 1;
}
}
friend istream& operator>>(istream& input, DayOfYear &o)
{
int m,d;
char c;

input>>o.year>>c>>m>>c>>d;
o.dayOfYear = d + days[m-1];
return input;
}
friend ostream& operator<<(ostream& output,DayOfYear &o)
{
int d,m;
for(m=0;m<=12;m++)
{
if(o.days[m]>=o.dayOfYear)
{
break;
}
}
d = o.dayOfYear - o.days[m-1];
return output<<o.year<<'-'<<m<<'-'<<d;
}
};
const int DayOfYear ::days[]={0,31,59,90,120,151,181,212,243,273,304,334,365};
class Vehicle
{
private:
const int no;
string model;
float price24h;
public:
Vehicle(int no1, string model1, float price24h1) : no(no1), model(model1), price24h(price24h1)
{}
int get_no()
{
return no;
}
string get_model()
{
return model;
}
double get_price(int a)
{
return (a * price24h);
}
virtual void print()=0;
};
class Bike: public Vehicle
{
public:
Bike(int bike_num, string bike_model) : Vehicle(bike_num, bike_model, 9.99) {}
void print()
{
cout<< get_no()<<" "<<get_model()<<" "<<"(Bike)"<<endl;
}
};
class EMotorVehicle: public Vehicle
{
public:
EMotorVehicle(int EMV_num, string EMV_model, float EMV_price): Vehicle(EMV_num, EMV_model, EMV_price) {}
virtual bool is_streetLegal()=0;
void print()
{
cout<< get_no()<<" "<<get_model()<<" ";
if(is_streetLegal()==false)
{
cout<<"(not street legal)";
}
}
};
class EBike : public EMotorVehicle
{
public:
EBike(int EB_num, string EB_model) : EMotorVehicle(EB_num, EB_model, 29.99) {}
bool is_streetLegal()
{
return true;
}
void print()
{
EMotorVehicle::print();
cout<<"(EBike)"<<endl;
}
};
class EScooter : public EMotorVehicle
{
private:
bool streetLegal;
public:
EScooter(int ES_num, string ES_model) : EMotorVehicle(ES_num,ES_model,19.99), streetLegal(false) {}
bool is_streetLegal()
{
return streetLegal;
}
void print()
{
EMotorVehicle::print();
cout<<"(EScooter)"<<endl;
}
};
class Rental
{
private:
const int no;
DayOfYear from;
int days;
string customer;
static int last_no;
public:
Rental(string customer1, DayOfYear from1, int days1) :customer(customer1), from(from1), days(days1), no(last_no)
{
last_no++;
}
int get_days()
{
return days;
}
DayOfYear get_from()
{
return from;
}
DayOfYear get_until()
{
DayOfYear until = from;
for(int i=0;i<days;i++)
{
++until;
}
return until;
}
void print()
{
    DayOfYear until=this->get_until();
cout<<"Rental : "<<from<<"to"<<until<<", rental no : "<<no<<" / for : "<<customer<<endl;
}
};
int Rental::last_no=1;
class Schedule
{
private:
Vehicle *vehicle;
Rental *year[365];
Schedule *next;

public:
Schedule(Vehicle* v): vehicle(v)
{
next = NULL;
for(int i=0;i<365;i++)
{
year[i] = NULL;
}
}
Vehicle *get_vehicle()
{
return vehicle;
}
Schedule *get_next()
{
return next;
}
void set_next(Schedule* nex)
{
next = nex;
}
bool isFree(DayOfYear o, int days)
{
for(int i=0;i<days;i++)
{
if(year[o.get_dayOfYear()]==NULL)
{
return true;
}
else
{
return false;
}
}
}
float book(string customer, DayOfYear start, int days)
{
Rental *a = new Rental(customer, start, days);
for(int i=(start.get_dayOfYear());i<start.get_dayOfYear()+days;i++)
{
year[start.get_dayOfYear()-1] = a;
}
return vehicle->get_price(days);
}
void print(DayOfYear o)
{
vehicle->print();
if(year[o.get_dayOfYear()-1] != NULL)
{
year[o.get_dayOfYear()-1]->print();
}
}
void print()
{
cout <<  "SCHEDULE FOR ";
vehicle->print();
for(int i=0; i<=365; i++)
{
if(year[i]!=NULL)
{
year[i]->print();
}
}
}
};

class Agency
{
private:
float profitPercentage;
float profit;
Schedule *head;
Schedule *last;
public:
Agency(): profitPercentage(0.2), profit(0.00), head(nullptr), last(nullptr) {}
float get_profit()
{
return profit;
}
void set_profitPercentage(float pP)
{
profitPercentage = pP;
}
void add(Vehicle *a)
{
Schedule *b = new Schedule(a);
if (head==NULL)
{
head=b;
last=b;
}
else if(head!=NULL)
{
last->set_next(b);
last=b;
}
}
protected:
Schedule *searchFor(int a)
{
Schedule *b=head;
while (b != NULL)
{
if (b->get_vehicle()->get_no() == a)
{
return b;
}
b = b->get_next();
}
return NULL;
}
public:
bool isFree(int a, DayOfYear start, int days)
{
Schedule *b =searchFor(a);
if(b != NULL)
{
return b->isFree(start, days);
}
return true;
}
float book(int a, string customer, DayOfYear start, int days)
{
Schedule *b = searchFor(a);
float price = b->book(customer,start,days);
profit = profitPercentage * price;
return price;
}
int chooseVehicle()
{
Schedule *a=head;
int b;
while(a!=NULL)
{
a->get_vehicle()->print();
a = a->get_next();
}
cout<<"choose vehicle number: ";
cin>>b;
return b;
}
void print(DayOfYear o)
{
Schedule *a = head;
while(a != NULL)
{
a->print(o);
cout << endl;
a = a->get_next();
}
}
void print()
{
Schedule *a = head;
while(a!=NULL)
{
a->print();
cout<<endl;
a = a->get_next();
}
cout<<"profit: "<<get_profit()<<" EUR"<<endl;
}
};

int main(void)
{
int vehicles = 1;
Agency vroom;
bool x = true;
DayOfYear today;
cout << "SIMPLIFIED SIMULATION OF A RENTAL AGENCY" << endl;
cout << "========================================" << endl;
while (x)
{
float profit=vroom.get_profit();
DayOfYear tomorrow = today;
++tomorrow;
cout << "MENU" << endl;
cout << "A end of simulation" << endl;
cout << "B set new simulation date" << endl;
cout << "C new rental manually" << endl;
cout << "D print rental of today " << today<<endl;
cout << "E print rental of tomorrow " << tomorrow<<endl;
cout << "F print all rentals" << endl;
cout << "G print agency profit" << endl;
cout << "H set agency profit percent" << endl;
cout << "I add bikes" << endl;
cout << "J add E-bikes" << endl;
cout << "K add E-scooters" << endl;
cout << "your choice : ";
char c;
cin >> c;
switch(c)
{
case 'A': case'a':
{
x = false;
break;
}
case 'B': case'b':
{
cout << "input date of today: ";
cin >> today;


break;
}
case 'C': case'c':
{
DayOfYear o;
int days;
int vehicle_num;
string customer;
vehicle_num = vroom.chooseVehicle();
cout << "day of rental : ";
cin >> o;
cout << "number of days : ";
cin >> days;
if (vroom.isFree(vehicle_num, o, days))
{
cout << "input data vehicle renter name : " << endl;
cin >> customer;
float price = vroom.book(vehicle_num, customer, o, days);
cout << "booked, price for this rental: " <<  price << " EUR" << endl;
}
else
{
cout << "sorry vehicle already booked" << endl;
}
break;
}
case 'D': case'd':
{
cout << "SCHEDULE FOR " << today << endl;
vroom.print(today);
break;
}
case 'E': case'e':
{
cout << "SCHEDULE FOR " << tomorrow << endl;
vroom.print(tomorrow);
break;
}
case 'F': case'f':
{
vroom.print();
break;
}
case 'G': case'g':
{
cout << "agency profit: " << vroom.get_profit() << " EUR" << endl;
break;
}
case 'H': case'h':
{
cout << "agency profit percent: ";
float percentage;
cin >> percentage;
vroom.set_profitPercentage(percentage);
break;
}
case 'I': case'i':
{

cout << "how many Bikes in this simulation? ";
int Bikes;
cin >> Bikes;
for(int i=0;i<Bikes;i++)
{
Bike *a = new Bike(vehicles++, "City");
vroom.add(a);
}
break;
}
case 'J': case'j':
{

cout << "how many EBikes in this simulation? ";
int EBikes;
cin >> EBikes;
for(int i=0;i<EBikes;i++)
{
EBike *a = new EBike(vehicles++, "Trekky");
vroom.add(a);
}
break;
}
case 'K': case'k':
{

cout << "how many EScooters in this simulation? ";
int EScooters;
cin >> EScooters;
for(int i=0;i<EScooters;i++)
{
EScooter *a = new EScooter(vehicles++, "Scooty");
vroom.add(a);
}
break;
}
}
}
return 0;
}








