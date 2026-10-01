// ============================================================
//  RAILWAY RESERVATION SYSTEM  (C++ OOP project)
//  Syllabus concepts used:
//  CO1: classes/objects, encapsulation, abstraction, inline function,
//       default arguments, reference, function returning reference,
//       pass by reference
//  CO2: constructor, destructor, access specifiers, array of objects,
//       dynamic objects, friend function
//  CO3: function overloading, inheritance, abstract base class,
//       pure virtual function, run time polymorphism, overriding
//  CO4: exception handling, STL vector
//  CO5: iostream, overloading << (inserter), file reading/writing
// ============================================================
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// ------------------------------------------------------------
// INLINE FUNCTION and DEFAULT ARGUMENT FUNCTION
// ------------------------------------------------------------
inline int calcFare(int stops, int rate)
{
    return stops * rate;
}

// chargePercent has a default value of 20
int calcRefund(int fare, int chargePercent = 20)
{
    return fare - (fare * chargePercent / 100);
}

// ------------------------------------------------------------
// ABSTRACT BASE CLASS  (Coach) + INHERITANCE + POLYMORPHISM
// Each class type decides its own fare per station.
// ------------------------------------------------------------
class Coach
{
public:
    virtual int farePerStop() = 0;      // pure virtual function
    virtual string getName() = 0;       // pure virtual function
    virtual ~Coach() {}                 // virtual destructor
};

class Sleeper : public Coach
{
public:
    int farePerStop() { return 150; }
    string getName() { return "Sleeper"; }
};

class AC3Tier : public Coach
{
public:
    int farePerStop() { return 350; }
    string getName() { return "AC 3 Tier"; }
};

class AC2Tier : public Coach
{
public:
    int farePerStop() { return 500; }
    string getName() { return "AC 2 Tier"; }
};

// ------------------------------------------------------------
// ABSTRACT BASE CLASS  (Person)  ->  Passenger
// ------------------------------------------------------------
class Person
{
protected:                              // accessible in derived class
    string name;
    int age;
    char gender;
public:
    Person(string n, int a, char g)
    {
        name = n;
        age = a;
        gender = g;
    }
    virtual void display(ostream &out) const = 0;   // pure virtual
    virtual ~Person() {}
};

class Passenger : public Person
{
public:
    Passenger(string n, int a, char g) : Person(n, a, g) {}

    // function overriding
    void display(ostream &out) const
    {
        out << name << " (Age: " << age << ", Gender: " << gender << ")";
    }
};

// ------------------------------------------------------------
// TRAIN CLASS  (encapsulation: data is private)
// ------------------------------------------------------------
class Train
{
private:
    int number;
    string name;
    string time;
    vector<string> route;               // STL vector of stations
    int seats[3];                       // 0 = Sleeper, 1 = 3A, 2 = 2A

public:
    // constructor with default arguments
    Train(int n = 0, string nm = "", string t = "",
          const vector<string> &r = vector<string>())
    {
        number = n;
        name = nm;
        time = t;
        route = r;
        for (int i = 0; i < 3; i++)
            seats[i] = 5;               // 5 seats in every class
    }

    int getNumber() const { return number; }
    string getName() const { return name; }
    string getTime() const { return time; }
    const vector<string>& getRoute() const { return route; }
    int seatsLeft(int c) const { return seats[c]; }

    // position of a station in the route (-1 if not present)
    int indexOf(const string &station) const
    {
        for (int i = 0; i < (int)route.size(); i++)
            if (route[i] == station)
                return i;
        return -1;
    }

    // does this train go from src to dst (in that order)?
    bool runs(const string &src, const string &dst) const
    {
        int a = indexOf(src);
        int b = indexOf(dst);
        return (a != -1 && b != -1 && a < b);
    }

    bool bookSeat(int c)
    {
        if (seats[c] == 0)
            return false;
        seats[c]--;
        return true;
    }

    void releaseSeat(int c) { seats[c]++; }
};

// ------------------------------------------------------------
// TICKET CLASS
// ------------------------------------------------------------
class Ticket
{
private:
    int pnr;
    Passenger p;
    int trainNo;
    string trainName;
    string source;
    string dest;
    string boarding;
    int cls;
    string className;
    string seatType;
    int seatNo;
    int fare;
    bool cancelled;

public:
    Ticket(int pn, Passenger ps, int tn, string tname, string s, string d,
           int c, string cname, string st, int sn, int f)
        : pnr(pn), p(ps), trainNo(tn), trainName(tname), source(s), dest(d),
          boarding(s), cls(c), className(cname), seatType(st), seatNo(sn),
          fare(f), cancelled(false) {}

    int getPnr() const { return pnr; }
    int getTrainNo() const { return trainNo; }
    int getClass() const { return cls; }
    int getFare() const { return fare; }
    string getSource() const { return source; }
    string getDest() const { return dest; }
    string getBoarding() const { return boarding; }
    bool isCancelled() const { return cancelled; }

    void cancel() { cancelled = true; }
    void setBoarding(const string &b) { boarding = b; }

    // friend function: overloaded inserter (<<)
    friend ostream& operator<<(ostream &out, const Ticket &t);
};

ostream& operator<<(ostream &out, const Ticket &t)
{
    out << "\n========== E-TICKET ==========\n";
    out << "PNR         : " << t.pnr << endl;
    out << "Passenger   : ";
    t.p.display(out);
    out << endl;
    out << "Train       : " << t.trainNo << " " << t.trainName << endl;
    out << "Journey     : " << t.source << " to " << t.dest << endl;
    out << "Boarding at : " << t.boarding << endl;
    out << "Class       : " << t.className << endl;
    out << "Seat        : " << t.seatNo << " - " << t.seatType << endl;
    out << "Fare        : Rs. " << t.fare << endl;
    out << "Status      : " << (t.cancelled ? "CANCELLED" : "CONFIRMED") << endl;
    out << "==============================\n";
    return out;
}

// ------------------------------------------------------------
// HELPER FUNCTIONS
// ------------------------------------------------------------

// read an integer safely, throw exception if user types a non-number
int readInt()
{
    int x;
    if (!(cin >> x))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        throw "Please enter a number only!";
    }
    return x;
}

// make "jaipur" or "JAIPUR" into "Jaipur"
string fixName(string s)
{
    for (int i = 0; i < (int)s.size(); i++)
    {
        if (i == 0 && s[i] >= 'a' && s[i] <= 'z')
            s[i] = s[i] - 32;
        else if (i != 0 && s[i] >= 'A' && s[i] <= 'Z')
            s[i] = s[i] + 32;
    }
    return s;
}

// FUNCTION OVERLOADING: same name, different parameters
void showTrains(Train t[], int n)               // show ALL trains
{
    cout << "\nNo    Train Name                  Dep.   Route\n";
    cout << "------------------------------------------------------------------\n";
    for (int i = 0; i < n; i++)
    {
        cout << t[i].getNumber() << "  " << t[i].getName();
        for (int k = t[i].getName().size(); k < 26; k++)
            cout << " ";
        cout << t[i].getTime() << "  ";
        const vector<string> &r = t[i].getRoute();
        for (int j = 0; j < (int)r.size(); j++)
        {
            cout << r[j];
            if (j != (int)r.size() - 1)
                cout << " > ";
        }
        cout << endl;
    }
}

void showTrains(Train t[], int n, string src, string dst)   // route-wise
{
    bool found = false;
    cout << "\nTrains from " << src << " to " << dst << ":\n";
    cout << "No    Train Name                  Dep.   SL  3A  2A\n";
    cout << "------------------------------------------------------\n";
    for (int i = 0; i < n; i++)
    {
        if (t[i].runs(src, dst))
        {
            found = true;
            cout << t[i].getNumber() << "  " << t[i].getName();
            for (int k = t[i].getName().size(); k < 26; k++)
                cout << " ";
            cout << t[i].getTime() << "   " << t[i].seatsLeft(0) << "   "
                 << t[i].seatsLeft(1) << "   " << t[i].seatsLeft(2) << endl;
        }
    }
    if (!found)
        throw "Sorry, no trains available on this route.";
}

// FUNCTION RETURNING REFERENCE
Train& findTrain(Train t[], int n, int number)
{
    for (int i = 0; i < n; i++)
        if (t[i].getNumber() == number)
            return t[i];
    throw "Invalid train number!";
}

Ticket& findTicket(vector<Ticket> &b, int pnr)
{
    for (int i = 0; i < (int)b.size(); i++)
        if (b[i].getPnr() == pnr)
            return b[i];
    throw "No ticket found with this PNR.";
}

// ------------------------------------------------------------
// MAIN FEATURES  (vectors and counters passed BY REFERENCE)
// ------------------------------------------------------------
void searchTrains(Train trains[], int n)
{
    string src, dst;
    cout << "Enter source station: ";
    cin >> src;
    cout << "Enter destination station: ";
    cin >> dst;
    showTrains(trains, n, fixName(src), fixName(dst));
}

void bookTicket(Train trains[], int n, Coach *coaches[],
                vector<Ticket> &bookings, int &pnrCounter)
{
    string seatTypes[5] = {"Lower", "Middle", "Upper", "Side Lower", "Side Upper"};
    string src, dst, pname;
    int age, trainNo, c, s;
    char gender;

    cout << "Enter source station: ";
    cin >> src;
    cout << "Enter destination station: ";
    cin >> dst;
    src = fixName(src);
    dst = fixName(dst);

    showTrains(trains, n, src, dst);        // throws if no train

    cout << "\nEnter train number to book: ";
    trainNo = readInt();
    Train &train = findTrain(trains, n, trainNo);
    if (!train.runs(src, dst))
        throw "This train does not run on the selected route!";

    // passenger details
    cout << "Passenger name: ";
    cin >> ws;
    getline(cin, pname);
    cout << "Age: ";
    age = readInt();
    cout << "Gender (M/F/O): ";
    cin >> gender;

    // class selection
    cout << "\n1. Sleeper   2. AC 3 Tier   3. AC 2 Tier\n";
    cout << "Choose class: ";
    c = readInt();
    if (c < 1 || c > 3)
        throw "Invalid class!";
    c = c - 1;

    if (train.seatsLeft(c) == 0)
        throw "Sorry, no seats left in this class.";

    // seat type preference
    cout << "\nSeat types:\n";
    for (int i = 0; i < 5; i++)
        cout << i + 1 << ". " << seatTypes[i] << endl;
    cout << "Choose seat type: ";
    s = readInt();
    if (s < 1 || s > 5)
        throw "Invalid seat type!";

    // fare: polymorphism - coaches[c] may be Sleeper / AC3Tier / AC2Tier
    int stops = train.indexOf(dst) - train.indexOf(src);
    int fare = calcFare(stops, coaches[c]->farePerStop());
    int seatNo = 5 - train.seatsLeft(c) + 1;

    train.bookSeat(c);
    pnrCounter++;

    Passenger p(pname, age, gender);
    Ticket t(pnrCounter, p, train.getNumber(), train.getName(), src, dst,
             c, coaches[c]->getName(), seatTypes[s - 1], seatNo, fare);
    bookings.push_back(t);

    cout << "\nTicket booked successfully!";
    cout << t;

    // write the ticket into a file
    ofstream fout("tickets.txt", ios::app);
    fout << t;
    fout.close();
}

void viewTicket(vector<Ticket> &bookings)
{
    cout << "Enter PNR number: ";
    int pnr = readInt();
    Ticket &t = findTicket(bookings, pnr);
    cout << t;
}

void cancelTicket(Train trains[], int n, vector<Ticket> &bookings)
{
    cout << "Enter PNR number to cancel: ";
    int pnr = readInt();
    Ticket &t = findTicket(bookings, pnr);

    if (t.isCancelled())
        throw "This ticket is already cancelled.";

    string sure;
    cout << "Are you sure? (yes/no): ";
    cin >> sure;
    if (sure == "yes")
    {
        t.cancel();
        findTrain(trains, n, t.getTrainNo()).releaseSeat(t.getClass());
        cout << "Ticket cancelled. Refund: Rs. " << calcRefund(t.getFare()) << endl;
    }
    else
        cout << "Cancellation stopped.\n";
}

void changeBoarding(Train trains[], int n, vector<Ticket> &bookings)
{
    cout << "Enter PNR number: ";
    int pnr = readInt();
    Ticket &t = findTicket(bookings, pnr);

    if (t.isCancelled())
        throw "Cannot change boarding of a cancelled ticket.";

    Train &train = findTrain(trains, n, t.getTrainNo());
    const vector<string> &route = train.getRoute();
    int start = train.indexOf(t.getSource());
    int end = train.indexOf(t.getDest());

    cout << "Current boarding station: " << t.getBoarding() << endl;
    cout << "You can change boarding to: ";
    for (int i = start; i < end; i++)
        cout << route[i] << "  ";
    cout << endl;

    string newStation;
    cout << "Enter new boarding station: ";
    cin >> newStation;
    newStation = fixName(newStation);

    int pos = train.indexOf(newStation);
    if (pos >= start && pos < end)
    {
        t.setBoarding(newStation);
        cout << "Boarding station changed to " << newStation << endl;
    }
    else
        throw "Invalid boarding station for this ticket!";
}

void showFacilities()
{
    cout << "\n------- TRAIN FACILITIES -------\n";
    cout << "* Drinking water in every coach\n";
    cout << "* Clean washrooms and wash basins\n";
    cout << "* Pantry car (food and beverages)\n";
    cout << "* Charging points near seats\n";
    cout << "* Bedroll (blanket, pillow) in AC classes\n";
    cout << "* CCTV and security in coaches\n";
    cout << "* Medical first-aid box\n";
    cout << "* Railway helpline number: 139\n";
}

// read the saved tickets back from the file
void showSavedTickets()
{
    ifstream fin("tickets.txt");
    if (!fin)
        throw "No saved tickets found yet.";
    string line;
    cout << "\n----- Tickets saved in file -----\n";
    while (getline(fin, line))
        cout << line << endl;
    fin.close();
}

// ------------------------------------------------------------
// MAIN
// ------------------------------------------------------------
int main()
{
    // ARRAY OF OBJECTS (10 trains)
    Train trains[10] = {
        Train(101, "Delhi-Mumbai Rajdhani",   "16:00", vector<string>{"Delhi", "Jaipur", "Kota", "Mumbai"}),
        Train(102, "Jaipur-Indore Express",   "18:30", vector<string>{"Jaipur", "Kota", "Ujjain", "Indore"}),
        Train(103, "Bhopal-Delhi Shatabdi",   "06:00", vector<string>{"Bhopal", "Kota", "Jaipur", "Delhi"}),
        Train(104, "Indore-Mumbai Express",   "20:15", vector<string>{"Indore", "Ujjain", "Mumbai"}),
        Train(105, "Mumbai-Delhi Garib Rath", "11:45", vector<string>{"Mumbai", "Kota", "Jaipur", "Delhi"}),
        Train(106, "Delhi-Indore Express",    "21:00", vector<string>{"Delhi", "Jaipur", "Kota", "Ujjain", "Indore"}),
        Train(107, "Bhopal-Mumbai Express",   "07:30", vector<string>{"Bhopal", "Indore", "Mumbai"}),
        Train(108, "Jaipur-Bhopal Intercity", "13:20", vector<string>{"Jaipur", "Kota", "Bhopal"}),
        Train(109, "Indore-Delhi Express",    "09:10", vector<string>{"Indore", "Ujjain", "Kota", "Jaipur", "Delhi"}),
        Train(110, "Mumbai-Bhopal Superfast", "22:40", vector<string>{"Mumbai", "Indore", "Bhopal"})
    };
    int n = 10;

    // DYNAMIC OBJECTS stored in base class pointers (run time polymorphism)
    Coach *coaches[3];
    coaches[0] = new Sleeper();
    coaches[1] = new AC3Tier();
    coaches[2] = new AC2Tier();

    vector<Ticket> bookings;            // STL vector to store all tickets
    int pnrCounter = 1000;
    int choice;

    cout << "=============================================\n";
    cout << "     WELCOME TO RAILWAY RESERVATION SYSTEM\n";
    cout << "=============================================\n";

    do
    {
        cout << "\n1. Show all trains";
        cout << "\n2. Search trains (route wise)";
        cout << "\n3. Book ticket";
        cout << "\n4. View ticket";
        cout << "\n5. Cancel ticket";
        cout << "\n6. Change boarding station";
        cout << "\n7. Train facilities";
        cout << "\n8. Show tickets saved in file";
        cout << "\n9. Exit";
        cout << "\nEnter your choice: ";

        try     // EXCEPTION HANDLING
        {
            choice = readInt();
            switch (choice)
            {
            case 1: showTrains(trains, n); break;
            case 2: searchTrains(trains, n); break;
            case 3: bookTicket(trains, n, coaches, bookings, pnrCounter); break;
            case 4: viewTicket(bookings); break;
            case 5: cancelTicket(trains, n, bookings); break;
            case 6: changeBoarding(trains, n, bookings); break;
            case 7: showFacilities(); break;
            case 8: showSavedTickets(); break;
            case 9: cout << "Thank you! Happy Journey!\n"; break;
            default: cout << "Invalid choice, try again.\n";
            }
        }
        catch (const char *msg)
        {
            cout << "Error: " << msg << endl;
            choice = 0;                 // keep the menu running
        }

    } while (choice != 9);

    // free the dynamically created objects
    for (int i = 0; i < 3; i++)
        delete coaches[i];

    return 0;
}
