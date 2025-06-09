#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <ctime>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <limits>

using namespace std;
// 1a. ll for airports and planes 
template <typename T>
struct ListNode {
    T data;
    ListNode* next;
    ListNode(const T& value) : data(value), next(nullptr) {}
    ~ListNode() {
   }
}; 

class Customer;
class Flight;
class Airport;
class Plane;
class Ticket;
class Offer;

bool isValidDateOfBirth(const string& dob) {
    if (dob.size() != 10 || dob[2] != '/' || dob[5] != '/') {
        return false;
    }

    string dayStr = dob.substr(0, 2);
    string monthStr = dob.substr(3, 2);
    string yearStr = dob.substr(6, 4);

    // Check if all parts are numeric
    if (!all_of(dayStr.begin(), dayStr.end(), ::isdigit) ||
        !all_of(monthStr.begin(), monthStr.end(), ::isdigit) ||
        !all_of(yearStr.begin(), yearStr.end(), ::isdigit)) {
        return false;
    }

    int day = stoi(dayStr);
    int month = stoi(monthStr);
    int year = stoi(yearStr);

    // Validate day, month, and year
    if (month < 1 || month > 12 || day < 1 || day > 31 || year < 1900 || year > 2100) {
        return false;
    }

    // Check for valid days in each month
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }
    if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > 29 || (day == 29 && !isLeapYear)) {
            return false;
        }
    }

    return true;
}

class Airport {
    private:
        string airportName;
        string country;
        string usualWeatherCondition;
        int timeFromBeirut; // in hours
        int milesFromBeirut;
    
    public:
        Airport(string name, string cntry, string weather, int time, int miles)
            : airportName(name), country(cntry), usualWeatherCondition(weather),
              timeFromBeirut(time), milesFromBeirut(miles) {}
    
        // Getters
        string getName() const { return airportName; }
        string getCountry() const { return country; }
        string getWeather() const { return usualWeatherCondition; }
        int getTimeFromBeirut() const { return timeFromBeirut; }
        int getMilesFromBeirut() const { return milesFromBeirut; }
    
        // Setters
        void setInfo(string weather, int time, int miles) {
            usualWeatherCondition = weather;
            timeFromBeirut = time;
            milesFromBeirut = miles;
        }
    
        void displayInfo() const {
            cout << "Airport: " << airportName << "\nCountry: " << country
                 << "\nWeather: " << usualWeatherCondition << "\nTime from Beirut: " 
                 << timeFromBeirut << " hours\nMiles from Beirut: " << milesFromBeirut << endl;
          
           
            
        }
    };

class Plane {
    private:
        int planeId;
        string description;
        int numberOfMilesTraveled;
        vector<int> numberOfSeatsPerClass; // [firstClass, secondClass, ...]
        //vector<bool> seatAvailability;     // true if available
    
    public:
    vector<bool> seatAvailability;     // true if available

        Plane(int id, string desc, const vector<int>& seats)
            : planeId(id), description(desc), numberOfMilesTraveled(0),
              numberOfSeatsPerClass(seats) {
            int totalSeats = 0;
            for (int seats : numberOfSeatsPerClass) {
                totalSeats += seats;
            }
            seatAvailability = vector<bool>(totalSeats, true);
        }

        // Getters
        int getPlaneId() const { return planeId; }
        string getDescription() const { return description; }
        int getNumberOfMilesTraveled() const { return numberOfMilesTraveled; }
        vector<int> getNumberOfSeatsPerClass() const { return numberOfSeatsPerClass; }
    
        bool isSeatAvailable(int seatNumber) const {
            if (seatNumber >= 0 && seatNumber < seatAvailability.size()) {
                return seatAvailability[seatNumber];
            }
            return false;
        }
    
        bool reserveSeat(int seatNumber) {
            if (isSeatAvailable(seatNumber)) {
                seatAvailability[seatNumber] = false;
                return true;
            }
            return false;
        }
    
        void freeSeat(int seatNumber) {
            if (seatNumber >= 0 && seatNumber < seatAvailability.size()) {
                seatAvailability[seatNumber] = true;
            }
        }
    
        void updateMilesTraveled(int miles) {
            numberOfMilesTraveled += miles;
        }
    
        int getAvailableSeats() const {
            return count(seatAvailability.begin(), seatAvailability.end(), true);
        }
    
        void displayInfo() const {
            cout << "Plane ID: " << planeId << "\nDescription: " << description
                 << "\nMiles Traveled: " << numberOfMilesTraveled << "\nSeats per class: ";
            for (int seats : numberOfSeatsPerClass) {
                cout << seats << " ";
            }
            cout << "\nTotal seats: " << seatAvailability.size() << endl;
        }
    };

    class Customer {
        private:
            int customerId;
            string name;
            string phone;
            string dob; 
            int numOfFlights;
            int milesTraveled;
        
        public:
            Customer(int id, string n, string ph, string birth)
                : customerId(id), name(n), phone(ph), dob(birth), numOfFlights(0), milesTraveled(0) {}
        
            // Getters
            int getCustomerId() const { return customerId; }
            string getName() const { return name; }
            string getPhone() const { return phone; }
            string getDob() const { return dob; }
            int getNumOfFlights() const { return numOfFlights; }
            int getMilesTraveled() const { return milesTraveled; }
        
            // Setters
            void setName(string n) { name = n; }
            void setPhone(string ph) { phone = ph; }
            void setDob(string birth) { dob = birth; }
        
            
            void updateNumOfFlights(int increment) { 
                numOfFlights += increment; 
            }
            void updateMilesTraveled(int miles) { milesTraveled += miles; }
        
            void displayProfile() const {
                cout << "Customer ID: " << customerId << "\nName: " << name
                     << "\nPhone: " << phone << "\nDate of Birth: " << dob
                     << "\nNumber of Flights: " << numOfFlights
                     << "\nMiles Traveled: " << milesTraveled << endl;
            }
        };

        class BST {
            private:
                struct BSTNode {
                    int key;
                    Customer data;
                    BSTNode* left;
                    BSTNode* right;
            
                    BSTNode(int k, const Customer& val) 
                        : key(k), data(val), left(nullptr), right(nullptr) {}
                };
            
                BSTNode* root;
            
                BSTNode* insertHelper(BSTNode* node, int key, const Customer& value) {
                    if (node == nullptr) {
                        return new BSTNode(key, value);
                    }
            
                    if (key < node->key) {
                        node->left = insertHelper(node->left, key, value);
                    } else if (key > node->key) {
                        node->right = insertHelper(node->right, key, value);
                    } else {
                        // key already exists, update the value
                        node->data = value;
                    }
            
                    return node;
                }
            
                BSTNode* searchHelper(BSTNode* node, int key) const {
                    if (node == nullptr || node->key == key) {
                        return node;
                    }
            
                    if (key < node->key) {
                        return searchHelper(node->left, key);
                    } else {
                        return searchHelper(node->right, key);
                    }
                }
            
                void inOrderHelper(BSTNode* node, vector<Customer>& result) const {
                    if (node == nullptr) return;
            
                    inOrderHelper(node->left, result);
                    result.push_back(node->data);
                    inOrderHelper(node->right, result);
                }
            
                BSTNode* deleteHelper(BSTNode* node, int key) {
                    if (node == nullptr) return node;
            
                    if (key < node->key) {
                        node->left = deleteHelper(node->left, key);
                    } else if (key > node->key) {
                        node->right = deleteHelper(node->right, key);
                    } else {
                        // node with only one child or no child
                        if (node->left == nullptr) {
                            BSTNode* temp = node->right;
                            delete node;
                            return temp;
                        } else if (node->right == nullptr) {
                            BSTNode* temp = node->left;
                            delete node;
                            return temp;
                        }
            
                        // node with two children: get inorder successor
                        BSTNode* temp = minValueNode(node->right);
                        node->key = temp->key;
                        node->data = temp->data;
                        node->right = deleteHelper(node->right, temp->key);
                    }
                    return node;
                }
            
                BSTNode* minValueNode(BSTNode* node) {
                    BSTNode* current = node;
                    while (current && current->left != nullptr) {
                        current = current->left;
                    }
                    return current;
                }
            
                void clearHelper(BSTNode* node) {
                    if (node == nullptr) return;
                    clearHelper(node->left);
                    clearHelper(node->right);
                    delete node;
                }
            
            public:
                BST() : root(nullptr) {}
            
                ~BST() {
                    clear();
                }
            
                void insert(int key, const Customer& value) {
                    root = insertHelper(root, key, value);
                }
            
                Customer* search(int key) {
                    BSTNode* node = searchHelper(root, key);
                    return node ? &(node->data) : nullptr;
                }
            
                void remove(int key) {
                    root = deleteHelper(root, key);
                }
            
                // get all customers in sorted order (in-order traversal)
                vector<Customer> getAllCustomers() const {
                    vector<Customer> result;
                    inOrderHelper(root, result);
                    return result;
                }
            
                bool isEmpty() const {
                    return root == nullptr;
                }
            
                void clear() {
                    clearHelper(root);
                    root = nullptr;
                }
            
                // function to save BST data to file (for customer BST)
                void saveToFileHelper(ofstream& file, BSTNode* node) const {
                    if (node == nullptr) return;
            
                    saveToFileHelper(file, node->left);
                    // write customer data to file
                    file << node->data.getCustomerId() << ","
                         << node->data.getName() << ","
                         << node->data.getPhone() << ","
                         << node->data.getDob() << ","
                         << node->data.getNumOfFlights() << ","
                         << node->data.getMilesTraveled() << "\n";
                    saveToFileHelper(file, node->right);
                }
            
                void saveToFile(const string& filename) const {
                    ofstream file(filename);
                    if (file.is_open()) {
                        saveToFileHelper(file, root);
                        file.close();
                    }
                }
            
                //  to load BST data from file (for customer BST)
                void loadFromFile(const string& filename) {
                    clear();
                    ifstream file(filename);
                    if (file.is_open()) {
                        string line;
                        while (getline(file, line)) {
                            // parse line and create Customer object
                            // like example format: 1001,John Doe,555-1234,15/05/1985,12,45000
                            size_t pos = 0;
                            string token;
                            vector<string> tokens;
                            
                            while ((pos = line.find(',')) != string::npos) {
                                token = line.substr(0, pos);
                                tokens.push_back(token);
                                line.erase(0, pos + 1);
                            }
                            tokens.push_back(line); // for ast item
                            
                            if (tokens.size() == 6) {
                                int id = stoi(tokens[0]);
                                string name = tokens[1];
                                string phone = tokens[2];
                                string dob = tokens[3];
                                int numFlights = stoi(tokens[4]);
                                int miles = stoi(tokens[5]);
                                
                                Customer customer(id, name, phone, dob);
                                customer.updateNumOfFlights(numFlights - customer.getNumOfFlights());
                                customer.updateMilesTraveled(miles - customer.getMilesTraveled());
                                
                                insert(id, customer);
                            }
                        }
                        file.close();
                    }
                }
            };


            class Flight {
                private:
                    int flightNumber;
                    int planeId;
                    int day;
                    int month;
                    int year;
                    int departureTime; // in minutes since midnight
                    string destination;
                    vector<pair<string, int>> ticketTypes; // type and price
                    BST passengers; // BST of customer objects (using customer ID as key)
                
                public:
                    Flight(int num, int pId, int d, int m, int y, int time, string dest, 
                           const vector<pair<string, int>>& tickets)
                        : flightNumber(num), planeId(pId), day(d), month(m), year(y),
                          departureTime(time), destination(dest), ticketTypes(tickets) {}
                
                    // Getters 
                    int getFlightNumber() const { return flightNumber; }
                    int getPlaneId() const { return planeId; }
                    string getDate() const { 
                        return to_string(day) + "/" + to_string(month) + "/" + to_string(year); 
                    }
                    int getDay() const { return day; }
                    int getMonth() const { return month; }
                    int getYear() const { return year; }
                    int getDepartureTimeInMinutes() const { return departureTime; }
                    string getDepartureTime() const {
                        int hours = departureTime / 60; 
                        int minutes = departureTime % 60; 
                    
                        string formattedTime = (hours < 10 ? "0" : "") + to_string(hours) + ":" +
                                               (minutes < 10 ? "0" : "") + to_string(minutes);
                        return formattedTime;
                    }
                    string getDestination() const { return destination; }
                    vector<pair<string, int>> getTicketTypes() const { return ticketTypes; }
                
                    bool hasPassenger(int customerId) {
                        return passengers.search(customerId) != nullptr;
                    }
                
                    void addPassenger(const Customer& customer) {
                        passengers.insert(customer.getCustomerId(), customer);
                    }
                
                    void removePassenger(int customerId) {
                        passengers.remove(customerId);
                    }
                
                    vector<Customer> getAllPassengers() const {
                        return passengers.getAllCustomers();
                    }
                    
                    int getMiles(ListNode<Airport>* airportsHead) const {
                        if (!airportsHead) {
                            cerr << "Error: Airports data not loaded.\n";
                            return -1;
                        }
                    
                        ListNode<Airport>* current = airportsHead;
                        while (current != nullptr) {
                            if (current->data.getName() == destination) {
                                return current->data.getMilesFromBeirut();
                            }
                            current = current->next;
                        }
                    
                        cerr << "Error: Destination airport '" << destination << "' not found in airports list.\n";
                        return -1; // Return -1 if the destination is not found
                    }
                    
                
                    // get a passenger by ID
                    Customer* getPassenger(int customerId) {
                        return passengers.search(customerId);
                    }
                
                    void displayInfo() const {
                        cout << "Flight Number: " << flightNumber << "\nPlane ID: " << planeId
                             << "\nDate: " << getDate() << "\nDeparture Time: " << getDepartureTime()
                             << "\nDestination: " << destination << "\nTicket Types:\n";
                        for (const auto& ticket : ticketTypes) {
                            cout << "  " << ticket.first << ": $" << ticket.second << endl;
                        }
                        cout << "Passengers: " << passengers.getAllCustomers().size() << endl;
                    }
                };


                class Ticket {
                    private:
                        int customerId;
                        string customerName;
                        int flightNum;
                        int ticketNumber;
                        string ticketType;
                        int costOfFlight;
                        bool discount;
                        string reasonForDiscount;
                        string dateTime;
                        int seatNumber;
                    
                    public:
                        Ticket(int cId, string cName, int fNum, int tNum, string tType, int cost,
                               bool disc, string reason, string dt, int seat)
                            : customerId(cId), customerName(cName), flightNum(fNum), ticketNumber(tNum),
                              ticketType(tType), costOfFlight(cost), discount(disc), 
                              reasonForDiscount(reason), dateTime(dt), seatNumber(seat) {}
                    
                        // Getters
                        int getCustomerId() const { return customerId; }
                        string getCustomerName() const { return customerName; }
                        int getFlightNum() const { return flightNum; }
                        int getTicketNumber() const { return ticketNumber; }
                        string getTicketType() const { return ticketType; }
                        int getCostOfFlight() const { return costOfFlight; }
                        bool hasDiscount() const { return discount; }
                        string getReasonForDiscount() const { return reasonForDiscount; }
                        string getDateTime() const { return dateTime; }
                        int getSeatNumber() const { return seatNumber; }
                    
                        bool operator==(const Ticket& other) const {
                            return customerId == other.customerId &&
                                   flightNum == other.flightNum &&
                                   ticketNumber == other.ticketNumber &&
                                   seatNumber == other.seatNumber;
                        }
                    
                        void displayTicket() const {
                            cout << "===== TICKET =====\n"
                                 << "Ticket #: " << ticketNumber << "\n"
                                 << "Passenger: " << customerName << " (ID: " << customerId << ")\n"
                                 << "Flight #: " << flightNum << "\n"
                                 << "Seat #: " << seatNumber << " (" << ticketType << ")\n"
                                 << "Date/Time: " << dateTime << "\n"
                                 << "Price: $" << costOfFlight;
                            if (discount) {
                                cout << " (Discount applied: " << reasonForDiscount << ")";
                            }
                            cout << "\n==================\n";
                        }
                    };


class Offer {
private:
    int offerId;
    int flightNumber; // -1 for any flight
    string offerType; // "miles", "flights", etc.
    int discountAmount; // percentage or fixed amount

public:
    Offer() : offerId(0), flightNumber(-1), offerType("none"), discountAmount(0) {}

    Offer(int id, int fNum, string type, int amount)
        : offerId(id), flightNumber(fNum), offerType(type), discountAmount(amount) {}

    // Getters
    int getOfferId() const { return offerId; }
    int getFlightNumber() const { return flightNumber; }
    string getOfferType() const { return offerType; }
    int getDiscountAmount() const { return discountAmount; }

    bool qualifies(const Customer& customer) const {
        if (offerType == "miles" && customer.getMilesTraveled() >= discountAmount) {
            return true;
        }
        if (offerType == "flights" && customer.getNumOfFlights() >= discountAmount) {
            return true;
        }
        return false;
    }

    void displayOffer() const {
        cout << "Offer ID: " << offerId << "\nApplicable to: ";
        if (flightNumber == -1) {
            cout << "Any flight";
        } else {
            cout << "Flight #" << flightNumber;
        }
        cout << "\nType: " << offerType << "\nDiscount: " << discountAmount;
        if (offerType == "miles" || offerType == "flights") {
            cout << "%";
        } else {
            cout << "$";
        }
        cout << endl;
    }
};

class FlightReservationSystem {
    private:
       

        ListNode<Airport>* airportsHead;
        ListNode<Plane>* planesHead;
        // 1b. Doubly linked list for flights with BST for passengers
        struct FlightNode {
            Flight data;
            FlightNode* prev;
            FlightNode* next;
            
            FlightNode(const Flight& f) : data(f), prev(nullptr), next(nullptr) {}
        };
        FlightNode* flightsHead;
        FlightNode* flightsTail;
    
        // 1c. BST for customers
        BST customers;
    
        // 1e. queue for waiting lists (flight number -> queue of customer IDs)
        unordered_map<int, queue<int>> waitingLists;
    
        // 1f. array for offers (max 10)
        Offer offers[10];
        int offerCount = 0;
    
        // 1g. array for tickets
        vector<Ticket> tickets;
    
        // file names
        const string flightsFile = "flights.txt";
        const string customersFile = "customers.txt";
        const string planesFile = "planes.txt";
        const string offersFile = "offers.txt";
        const string ticketsFile = "tickets.txt";
    
        // functions for linked list operations
        void insertSorted(ListNode<Airport>** head, const Airport& airport) {
            ListNode<Airport>* newNode = new ListNode<Airport>(airport);
            ListNode<Airport>* current;
        
            // Special case for head
            if (*head == nullptr || (*head)->data.getName() >= newNode->data.getName()) {
                newNode->next = *head;
                *head = newNode;
            } else {
                current = *head;
                while (current->next != nullptr && 
                       current->next->data.getName() < newNode->data.getName()) {
                    current = current->next;
                }
                newNode->next = current->next;
                current->next = newNode;
            }
        }
    
        void insertSorted(ListNode<Plane>** head, const Plane& plane) {
            ListNode<Plane>* newNode = new ListNode<Plane>(plane);
            ListNode<Plane>* current;
            
            if (*head == nullptr || (*head)->data.getPlaneId() >= newNode->data.getPlaneId()) {
                newNode->next = *head;
                *head = newNode;
            } else {
                current = *head;
                while (current->next != nullptr && 
                       current->next->data.getPlaneId() < newNode->data.getPlaneId()) {
                    current = current->next;
                }
                newNode->next = current->next;
                current->next = newNode;
            }
        }



    void loadData() {
        cout << "Loading airports...\n";
        loadAirports();
        cout << "Loading planes...\n";
        loadPlanes();
        cout << "Loading customers...\n";  
        loadCustomers();
        cout << "Loading flights...\n";
        loadFlights();
        cout << "Loading tickets...\n";   
        loadTickets();
        cout << "Loading offers...\n";
        loadOffers();
        cout << "All data loaded.\n";
    }

    void saveData() {
        saveFlights();
        saveCustomers();
        savePlanes();
        saveOffers();
        saveTickets();
    }
    string getPlaneName(int planeId) const {
        ListNode<Plane>* current = planesHead;
        while (current != nullptr) {
            if (current->data.getPlaneId() == planeId) {
                return current->data.getDescription(); // return the plane's name
            }
            current = current->next;
        }
        return "Unknown Plane"; // return a default value if the plane ID is not found
    }

    int calculatePrice(const Flight& flight, const string& ticketType = "Economy") {
        int basePricePerMile = 5; // Base price per mile
        int miles = flight.getMiles(airportsHead); 
    
        if (miles == -1) {
            cerr << "Error: Unable to calculate price due to invalid distance.\n";
            return -1;
        }
    
        int price = basePricePerMile * miles;
    
        if (ticketType == "Business") {
            price *= 1.5; 
        } else if (ticketType == "FirstClass") {
            price *= 2; 
        }
    
        return price;
    }

    int generateTicketNumber() {
        int maxTicketNumber = 1000; 
    
        // check the existing tickets for the highest ticket number
        for (const Ticket& ticket : tickets) {
            if (ticket.getTicketNumber() > maxTicketNumber) {
                maxTicketNumber = ticket.getTicketNumber();
            }
        }
    
        return maxTicketNumber + 1; // return the next available ticket number
    }
    Flight parseFlight(const string& line) {
        vector<string> tokens;
        size_t pos = 0;
        size_t prev = 0;
        
        // first parse comma-separated parts
        while ((pos = line.find(',', prev)) != string::npos) {
            tokens.push_back(line.substr(prev, pos - prev));
            prev = pos + 1;
        }
        tokens.push_back(line.substr(prev));
        
        // too ensure that we have enough tokens
        if (tokens.size() < 7) {
            throw runtime_error("Invalid flight data format");
        }
        
        // parse basic flight info
        int flightNumber = stoi(tokens[0]);
        int planeId = stoi(tokens[1]);
        int day = stoi(tokens[2]);
        int month = stoi(tokens[3]);
        int year = stoi(tokens[4]);
        int departureTime = stoi(tokens[5]);
        string destination = tokens[6];
        
        // parse ticket types
        vector<pair<string, int>> ticketTypes;
        if (tokens.size() > 7) {
            size_t ticketPos = 0;
            size_t ticketPrev = 0;
            string ticketStr = tokens[7];
            
            while ((ticketPos = ticketStr.find(',', ticketPrev)) != string::npos) {
                string typePrice = ticketStr.substr(ticketPrev, ticketPos - ticketPrev);
                size_t colonPos = typePrice.find(':');
                if (colonPos != string::npos) {
                    string type = typePrice.substr(0, colonPos);
                    int price = stoi(typePrice.substr(colonPos + 1));
                    ticketTypes.emplace_back(type, price);
                }
                ticketPrev = ticketPos + 1;
            }
            
            // last ticket type
            string typePrice = ticketStr.substr(ticketPrev);
            size_t colonPos = typePrice.find(':');
            if (colonPos != string::npos) {
                string type = typePrice.substr(0, colonPos);
                int price = stoi(typePrice.substr(colonPos + 1));
                ticketTypes.emplace_back(type, price);
            }
        }
        
        return Flight(flightNumber, planeId, day, month, year, 
                    departureTime, destination, ticketTypes);
    }
    
    void loadAirports() {
        ifstream file("airports.txt");
        if (!file) {
            cerr << "Error opening airports file!" << endl;
            return;
        }
    
        string line;
        while (getline(file, line)) {
            vector<string> tokens;
            size_t pos = 0;
            while ((pos = line.find(',')) != string::npos) {
                tokens.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            tokens.push_back(line); // last token
    
            if (tokens.size() == 5) {
                string name = tokens[0];
                string country = tokens[1];
                string weather = tokens[2];
                int timeFromBeirut = stoi(tokens[3]);
                int milesFromBeirut = stoi(tokens[4]);
    
                Airport airport(name, country, weather, timeFromBeirut, milesFromBeirut);
                insertSorted(&airportsHead, airport);
                cout << "Loaded airport: " << name << endl; // Debug statement
            } else {
                cerr << "Invalid line in airports file: " << line << endl;
            }
        }
        file.close();
    }

    void loadFlights() {
        ifstream file(flightsFile);
        if (!file) {
            cerr << "Error opening flights file!" << endl;
            return;
        }
    
        string line;
        while (getline(file, line)) {
            vector<string> tokens;
            size_t pos = 0;
            while ((pos = line.find(',')) != string::npos) {
                tokens.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            tokens.push_back(line); // last token
    
            if (tokens.size() >= 7) {
                int flightNumber = stoi(tokens[0]);
                int planeId = stoi(tokens[1]);
                int day = stoi(tokens[2]);
                int month = stoi(tokens[3]);
                int year = stoi(tokens[4]);
    
                // parse departure time in HH:MM format
                string timeStr = tokens[5];
                size_t colonPos = timeStr.find(':');
                int hours = stoi(timeStr.substr(0, colonPos));
                int minutes = stoi(timeStr.substr(colonPos + 1));
                int departureTime = hours * 60 + minutes; // Convert to minutes since midnight
    
                string destination = tokens[6];
    
                // Parse ticket types
                vector<pair<string, int>> ticketTypes;
                for (size_t i = 7; i < tokens.size(); ++i) {
                    size_t colonPos = tokens[i].find(':');
                    if (colonPos != string::npos) {
                        string type = tokens[i].substr(0, colonPos);
                        int price = stoi(tokens[i].substr(colonPos + 1));
                        ticketTypes.push_back({type, price});
                    }
                }
    
                //  the flight object
                Flight flight(flightNumber, planeId, day, month, year, departureTime, destination, ticketTypes);
    
                // add the flight to the doubly linked list
                FlightNode* newNode = new FlightNode(flight);
                if (flightsHead == nullptr) {
                    flightsHead = flightsTail = newNode;
                } else {
                    flightsTail->next = newNode;
                    newNode->prev = flightsTail;
                    flightsTail = newNode;
                }
            }
        }
    
        file.close();
        cout << "Flights loaded successfully.\n";
    }
    
    void saveFlights() {
        ofstream file(flightsFile, ios::trunc);
        FlightNode* current = flightsHead;
        while (current != nullptr) {
            const Flight& flight = current->data;
    
            // convert departure time to HH:MM format
            int hours = flight.getDepartureTimeInMinutes() / 60;
            int minutes = flight.getDepartureTimeInMinutes() % 60;
            string timeStr = (hours < 10 ? "0" : "") + to_string(hours) + ":" +
                             (minutes < 10 ? "0" : "") + to_string(minutes);
    
            // write basic flight info
            file << flight.getFlightNumber() << ","
                 << flight.getPlaneId() << ","
                 << flight.getDay() << ","
                 << flight.getMonth() << ","
                 << flight.getYear() << ","
                 << timeStr << ","
                 << flight.getDestination();
    
            // write ticket types
            const auto& ticketTypes = flight.getTicketTypes();
            for (size_t i = 0; i < ticketTypes.size(); ++i) {
                file << (i == 0 ? "," : ",");
                file << ticketTypes[i].first << ":" << ticketTypes[i].second;
            }
    
            file << "\n";
            current = current->next;
        }
        file.close();
    }
    void loadCustomers() {
        ifstream file(customersFile);
        if (!file) {
            cerr << "Error opening customers file!" << endl;
            return;
        }
    
        string line;
        while (getline(file, line)) {
            vector<string> tokens;
            size_t pos = 0;
            while ((pos = line.find(',')) != string::npos) {
                tokens.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            tokens.push_back(line); // Last token
    
            if (tokens.size() == 6) {
                int id = stoi(tokens[0]);
                string name = tokens[1];
                string phone = tokens[2];
                string dob = tokens[3];
                int numFlights = stoi(tokens[4]);
                int miles = stoi(tokens[5]);
    
                Customer customer(id, name, phone, dob);
                customer.updateNumOfFlights(numFlights);
                customer.updateMilesTraveled(miles);
    
                customers.insert(id, customer);
            }
        }
        file.close();
    }
    void saveCustomers() {
        ofstream file(customersFile);
        if (!file) {
            cerr << "Error opening customers file for writing!" << endl;
            return;
        }
    
        vector<Customer> allCustomers = customers.getAllCustomers();
        for (const Customer& customer : allCustomers) {
            file << customer.getCustomerId() << ","
                 << customer.getName() << ","
                 << customer.getPhone() << ","
                 << customer.getDob() << ","
                 << customer.getNumOfFlights() << ","
                 << customer.getMilesTraveled() << "\n";
        }
        file.close();
    }
    void loadPlanes() {
        ifstream file(planesFile);
        if (!file) {
            cerr << "Error opening planes file!" << endl;
            return;
        }
    
        string line;
        while (getline(file, line)) {
            vector<string> tokens;
            size_t pos = 0;
            while ((pos = line.find(',')) != string::npos) {
                tokens.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            tokens.push_back(line); // Last token
    
            if (tokens.size() >= 3) {
                int planeId = stoi(tokens[0]);
                string description = tokens[1];
                vector<int> seatsPerClass;
    
                for (size_t i = 2; i < tokens.size(); ++i) {
                    seatsPerClass.push_back(stoi(tokens[i]));
                }
    
                Plane plane(planeId, description, seatsPerClass);
                insertSorted(&planesHead, plane);
            }
        }
        file.close();
    }
    void savePlanes() {
        ofstream file(planesFile,ios::trunc);
        if (!file) {
            cerr << "Error opening planes file for writing!" << endl;
            return;
        }
    
        ListNode<Plane>* current = planesHead;
        while (current != nullptr) {
            const Plane& plane = current->data;
            file << plane.getPlaneId() << ","
                 << plane.getDescription();
    
            for (int seats : plane.getNumberOfSeatsPerClass()) {
                file << "," << seats;
            }
            file << "\n";
            current = current->next;
        }
        file.close();
    }
    void loadOffers() {
        ifstream file(offersFile);
        if (!file) {
            cerr << "Error opening offers file!" << endl;
            return;
        }
    
        string line;
        offerCount = 0;
        while (getline(file, line) && offerCount < 10) {
            vector<string> tokens;
            size_t pos = 0;
            while ((pos = line.find(',')) != string::npos) {
                tokens.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            tokens.push_back(line); // Last token
    
            if (tokens.size() == 4) {
                int offerId = stoi(tokens[0]);
                int flightNumber = stoi(tokens[1]);
                string offerType = tokens[2];
                int discountAmount = stoi(tokens[3]);
    
                offers[offerCount++] = Offer(offerId, flightNumber, offerType, discountAmount);
            }
        }
        file.close();
    }
    void saveOffers() {
        ofstream file(offersFile);
        if (!file) {
            cerr << "Error opening offers file for writing!" << endl;
            return;
        }
    
        for (int i = 0; i < offerCount; ++i) {
            const Offer& offer = offers[i];
            file << offer.getOfferId() << ","
                 << offer.getFlightNumber() << ","
                 << offer.getOfferType() << ","
                 << offer.getDiscountAmount() << "\n";
        }
        file.close();
    }

    void loadTickets() {
        ifstream file(ticketsFile);
        if (!file) {
            cerr << "Error opening tickets file!" << endl;
            return;
        }
    
        string line;
        while (getline(file, line)) {
            try {
                vector<string> tokens;
                size_t pos = 0;
                while ((pos = line.find(',')) != string::npos) {
                    tokens.push_back(line.substr(0, pos));
                    line.erase(0, pos + 1);
                }
                tokens.push_back(line);
    
                if (tokens.size() >= 10) {
                    int customerId = stoi(tokens[0]);
                    string customerName = tokens[1];
                    int flightNum = stoi(tokens[2]);
                    int ticketNumber = stoi(tokens[3]);
                    string ticketType = tokens[4];
                    int costOfFlight = stoi(tokens[5]);
                    bool discount = (tokens[6] == "1" || tokens[6] == "true");
                    string reason = tokens[7];
                    string dateTime = tokens[8];
                    int seatNumber = stoi(tokens[9]);
    
                    // ceate ticket
                    tickets.emplace_back(customerId, customerName, flightNum, ticketNumber,
                                       ticketType, costOfFlight, discount, reason, dateTime, seatNumber);
    
                     // add passenger to flight's BST 
                FlightNode* flightNode = findFlight(flightNum);
                if (flightNode) {
                    Customer* customer = customers.search(customerId);
                    if (customer && !flightNode->data.hasPassenger(customerId)) {
                        flightNode->data.addPassenger(*customer);
                    }
                }
                }
            } catch (const exception& e) {
                cerr << "Error processing ticket: " << e.what() << endl;
            }
        }
        file.close();
    }
    void saveTickets() {
        ofstream file(ticketsFile);
        if (!file) {
            cerr << "Error opening tickets file for writing!" << endl;
            return;
        }
    
        for (const Ticket& ticket : tickets) {
            file << ticket.getCustomerId() << ","
                 << ticket.getCustomerName() << ","
                 << ticket.getFlightNum() << ","
                 << ticket.getTicketNumber() << ","
                 << ticket.getTicketType() << ","
                 << ticket.getCostOfFlight() << ","
                 << (ticket.hasDiscount() ? "1" : "0") << ","
                 << ticket.getReasonForDiscount() << ","
                 << ticket.getDateTime() << ","
                 << ticket.getSeatNumber() << "\n";
        }
        file.close();
    }


public:
FlightReservationSystem() : airportsHead(nullptr), planesHead(nullptr), 
                          flightsHead(nullptr), flightsTail(nullptr) {
    cout << "Loading data...\n";
    loadData();
    cout << "Data loaded successfully.\n";
}
~FlightReservationSystem() {
    saveData();
    // Clean up linked lists
    ListNode<Airport>* airportCurrent = airportsHead;
    while (airportCurrent != nullptr) {
        ListNode<Airport>* next = airportCurrent->next;
        delete airportCurrent;
        airportCurrent = next;
    }

    ListNode<Plane>* planeCurrent = planesHead;
    while (planeCurrent != nullptr) {
        ListNode<Plane>* next = planeCurrent->next;
        delete planeCurrent;
        planeCurrent = next;
    }

    FlightNode* flightCurrent = flightsHead;
    while (flightCurrent != nullptr) {
        FlightNode* next = flightCurrent->next;
        delete flightCurrent;
        flightCurrent = next;
    }
}

    void displayMenu() {

            string title = "ABHINANDAN Flight Reservation System";
    int width = 50; // Total width for the box
    string border = "*";  // Character for border
    
    // Display top border
    cout << string(width, border[0]) << endl;
    
    // Display the title centered with borders on each side
    cout << border << setw((width + title.length()) / 2) << title 
         << setw(width - (width + title.length()) / 2 - 1) << border << endl;
    
    // Display bottom border
    cout << string(width, border[0]) << endl;

            cout << "1. Flight Reservation\n"
             << "2. Customer Management\n"
             << "3. Flight Management\n"
             << "4. Setup System Data\n"
             << "5. Save Data\n"
             << "6. Exit\n"
             << "Enter your choice: ";
    }

    void flightReservationMenu() {
        cout << "\nFlight Reservation \n"
             << "1. Search for flights\n"
             << "2. Reserve a flight\n"
             << "3. Cancel reservation\n"
             << "4. Change reservation\n"
             << "5. Back to main menu\n"
             << "Enter your choice: ";
    }

    void customerManagementMenu() {
        cout << "\nCustomer Management\n"
             << "1. Add customer\n"
             << "2. Update customer info\n"
             << "3. Delete customer\n"
             << "4. View customer profile\n"
             << "5. Back to main menu\n"
             << "Enter your choice: ";
    }

    void flightManagementMenu() {
        cout << "\nFlight Management\n"
             << "1. Add flight\n"
             << "2. Update flight\n"
             << "3. Delete flight\n"
             << "4. View flights\n"
             << "5. Back to main menu\n"
             << "Enter your choice: ";
    }

    
    void searchFlights(const string& destination) {
    cout << "\nFlights to " << destination << ":\n";
    bool found = false;
    FlightNode* current = flightsHead;

    while (current != nullptr) {
        if (current->data.getDestination() == destination) {
            current->data.displayInfo();

            // get the plane associated with the flight
            Plane* plane = findPlane(current->data.getPlaneId());
            if (plane) {
                cout << "Available seats: " << plane->getAvailableSeats() << endl;
            } else {
                cout << "Plane information not found.\n";
            }

            cout << "------------------------\n";
            found = true;
        }
        current = current->next;
    }

    if (!found) {
        cout << "No flights found to " << destination << endl;
    }
}

    FlightNode* findFlight(int flightNumber) {
        FlightNode* current = flightsHead;
        while (current != nullptr) {
            if (current->data.getFlightNumber() == flightNumber) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    Plane* findPlane(int planeId) {
        ListNode<Plane>* current = planesHead;
        while (current != nullptr) {
            if (current->data.getPlaneId() == planeId) {
                return &(current->data);
            }
            current = current->next;
        }
        return nullptr;
    }

   
    void reserveFlight(int customerId, int flightNumber) {
        // Find the flight
        FlightNode* flightNode = findFlight(flightNumber);
        if (!flightNode) {
            cout << "Flight not found!\n";
            return;
        }
    
        // Check if customer exists
        Customer* customer = customers.search(customerId);
        if (!customer) {
            cout << "Customer not found! Please register first.\n";
            return;
        }
    
        // Check available seats
        Plane* plane = findPlane(flightNode->data.getPlaneId());
        if (!plane) {
            cout << "Plane not found for this flight.\n";
            return;
        }
    
        // Get the plane name
        string planeName = getPlaneName(flightNode->data.getPlaneId());
        cout << "Plane Name: " << planeName << endl;
    
        if (plane->getAvailableSeats() == 0) {
            cout << "Flight is full. Would you like to be added to the waiting list? (y/n): ";
            char choice;
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                waitingLists[flightNumber].push(customerId);
                cout << "Added to waiting list for flight " << flightNumber << endl;
            }
            return;
        }
    
        // prompt the user to select a ticket type
        const auto& ticketTypes = flightNode->data.getTicketTypes();
        cout << "Available ticket types for this flight:\n";
        for (size_t i = 0; i < ticketTypes.size(); ++i) {
            cout << i + 1 << ". " << ticketTypes[i].first << " - $" << ticketTypes[i].second << endl;
        }
    
        int ticketTypeChoice;
        cout << "Select a ticket type (1-" << ticketTypes.size() << "): ";
        cin >> ticketTypeChoice;
    
        if (ticketTypeChoice < 1 || ticketTypeChoice > static_cast<int>(ticketTypes.size())) {
            cout << "Invalid ticket type selection. Reservation failed.\n";
            return;
        }
    
        string selectedTicketType = ticketTypes[ticketTypeChoice - 1].first;
        int ticketPrice = ticketTypes[ticketTypeChoice - 1].second;
    
        // check for applicable offers
        int discount = 0;
        string discountReason = "";
        for (int i = 0; i < offerCount; ++i) {
            const Offer& offer = offers[i];
            if ((offer.getFlightNumber() == -1 || offer.getFlightNumber() == flightNumber) &&
                offer.qualifies(*customer)) {
                discount = offer.getDiscountAmount();
                discountReason = offer.getOfferType();
                break;
            }
        }
    
        // apply discount
        if (discount > 0) {
            if (discountReason == "miles" || discountReason == "flights") {
                ticketPrice -= (ticketPrice * discount) / 100; // Percentage discount
            } else {
                ticketPrice -= discount; // Fixed amount discount
            }
            ticketPrice = max(ticketPrice, 0); // Ensure price is not negative
        }

        // cllect all assigned seat numbers for this flight
        unordered_set<int> assignedSeats;
        for (const Ticket& ticket : tickets) {
            if (ticket.getFlightNum() == flightNumber) {
                assignedSeats.insert(ticket.getSeatNumber());
            }
        }
    
        // F=find the first available seat number
        int seatNumber = -1;
        for (int i = 0; i < plane->seatAvailability.size(); ++i) {
            if (assignedSeats.find(i) == assignedSeats.end() && plane->isSeatAvailable(i)) {
                seatNumber = i;
                break;
            }
        }
    
        if (seatNumber == -1) {
            cout << "Failed to reserve seat! No available seats.\n";
            return;
        }
    
        // reserve the seat in the plane
        plane->reserveSeat(seatNumber);
    
        // create ticket
        Ticket ticket(customerId, customer->getName(), flightNumber, 
                      generateTicketNumber(), selectedTicketType, ticketPrice,
                      false, "", flightNode->data.getDate() + " " + flightNode->data.getDepartureTime(),
                      seatNumber);
        tickets.push_back(ticket);
    
        // =add passenger to flight's BST
        flightNode->data.addPassenger(*customer);
    
        // update customer info
        customer->updateNumOfFlights(1);
        customer->updateMilesTraveled(flightNode->data.getMiles(airportsHead));
    
        cout << "Reservation successful! Ticket number: " << ticket.getTicketNumber() << endl;
        cout << "Ticket Type: " << selectedTicketType << "\nPrice: $" << ticketPrice << endl;
        cout << "Assigned Seat Number: " << seatNumber << endl;
        if (discount > 0) {
            cout << "Discount applied: " << discountReason << " (" << discount << (discountReason == "miles" || discountReason == "flights" ? "%" : "$") << ")\n";
        }
    }

    void cancelReservation(int customerId, int flightNumber) {
        // Find the flight
        FlightNode* flightNode = findFlight(flightNumber);
        if (!flightNode) {
            cout << "Flight not found!\n";
            return;
        }
    
        // check if the customer exists in the flight's passenger list
        Customer* customer = flightNode->data.getPassenger(customerId);
        if (!customer) {
            cout << "Customer not found on this flight!\n";
            return;
        }
    
        // find the plane associated with the flight
        Plane* plane = findPlane(flightNode->data.getPlaneId());
        if (!plane) {
            cout << "Plane not found for this flight.\n";
            return;
        }
    
        // free the seat
        for (Ticket& ticket : tickets) {
            if (ticket.getCustomerId() == customerId && ticket.getFlightNum() == flightNumber) {
                plane->freeSeat(ticket.getSeatNumber());
                cout << "Seat " << ticket.getSeatNumber() << " freed for customer " << customerId << ".\n";
    
                // remove the ticket from the tickets list
                auto it = find(tickets.begin(), tickets.end(), ticket);
                if (it != tickets.end()) {
                    tickets.erase(it);
                } else {
                    cerr << "Error: Ticket not found for customer " << customerId << " on flight " << flightNumber << ".\n";
                }
                break;
            }
        }
    
        // remove the customer from the flight's passenger list
        flightNode->data.removePassenger(customerId);
    
        // ceck the waiting list for this flight
        if (!waitingLists[flightNumber].empty()) {
            int nextCustomerId = waitingLists[flightNumber].front();
            waitingLists[flightNumber].pop();
    
            // reserve the seat for the next customer in the waiting list
            reserveFlight(nextCustomerId, flightNumber);
            cout << "Seat assigned to customer " << nextCustomerId << " from the waiting list.\n";
        }
    
        cout << "Reservation canceled successfully for customer " << customerId << " on flight " << flightNumber << ".\n";
    }
    void changeReservation(int customerId, int oldFlightNumber, int newFlightNumber) {
        // cancel the old reservation
        cancelReservation(customerId, oldFlightNumber);
    
        // reserve a seat on the new flight
        reserveFlight(customerId, newFlightNumber);
    
        cout << "Reservation changed successfully for customer " << customerId
             << " from flight " << oldFlightNumber << " to flight " << newFlightNumber << ".\n";
    }

    void addCustomer(const Customer& customer) {
        if (customers.search(customer.getCustomerId())) {
            cout << "Error: Customer ID " << customer.getCustomerId() << " already exists.\n";
            return;
        }
        customers.insert(customer.getCustomerId(), customer);
        cout << "Customer added successfully.\n";
    }



void welcomeScreen() {
    ifstream file("welcome2.txt");
    string line;
   if (!file) {
       cerr << "Error opening file." << endl;
        return ;
   }

   while (getline(file, line)) {
   cout<< line << endl;
   }
   file.close();
}



    void run() {
        int choice;
       
        do {
             welcomeScreen();
            displayMenu();
            cin >> choice;
            if (cin.fail()) {
                cin.clear(); // clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }
            cin.ignore(); // clear newline

            switch (choice) {
                case 1: 
                    handleFlightReservation();
                    break;
                case 2: 
                    handleCustomerManagement();
                    break;
                case 3: 
                    handleFlightManagement();
                    break;
                case 4: 
                    loadData();
                    cout << "System data loaded successfully.\n";
                    break;
                case 5: 
                    saveData();
                    cout << "Data saved successfully.\n";
                    break;
                case 6:
                    cout << "Exiting system...\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 6);
    }

    // submenu handlers
    void handleFlightReservation() {
        int choice;
        do {
            flightReservationMenu();
            cin >> choice;
            if (cin.fail()) {
                cin.clear(); // clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }
            cin.ignore(); // clear newline
    
            switch (choice) {
                case 1: { // search for flights
                    string destination;
                    cout << "Enter destination: ";
                    getline(cin, destination);
                    searchFlights(destination);
                    break;
                }
                case 2: { // reserve flight
                    int custId, flightNum;
                    cout << "Enter customer ID: ";
                    cin >> custId;
                    cout << "Enter flight number: ";
                    cin >> flightNum;
                    reserveFlight(custId, flightNum);
                    break;
                }
                case 3: { // cancel reservation
                    int custId, flightNum;
                    cout << "Enter customer ID: ";
                    cin >> custId;
                    cout << "Enter flight number: ";
                    cin >> flightNum;
                    cancelReservation(custId, flightNum);
                    break;
                }
                case 4: { // change reservation
                    int custId, oldFlight, newFlight;
                    cout << "Enter customer ID: ";
                    cin >> custId;
                    cout << "Enter current flight number: ";
                    cin >> oldFlight;
                    cout << "Enter new flight number: ";
                    cin >> newFlight;
                    changeReservation(custId, oldFlight, newFlight);
                    break;
                }
                case 5: // back to main menu
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 5);
    }

    void handleCustomerManagement() {
        int choice;
        do {
            customerManagementMenu();
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1: { // add customer
                    int id;
                    string name, phone, dob;
                
                    cout << "Enter customer ID: ";
                    cin >> id;
                
                    // check for duplicate customer ID
                    if (customers.search(id)) {
                        cout << "Error: Customer ID " << id << " already exists.\n";
                        break;
                    }
                
                    cin.ignore(); // clear newline
                    cout << "Enter name: ";
                    getline(cin, name);
                    cout << "Enter phone: ";
                    getline(cin, phone);
                
                    // validate date of birth
                    do {
                        cout << "Enter date of birth (DD/MM/YYYY): ";
                        getline(cin, dob);
                        if (!isValidDateOfBirth(dob)) {
                            cout << "Invalid date of birth format. Please enter in the format DD/MM/YYYY (e.g., 08/10/2005).\n";
                        }
                    } while (!isValidDateOfBirth(dob));
                
                    addCustomer(Customer(id, name, phone, dob));
                    break;
                }
                case 2: { // update customer info
                    int id;
                    cout << "Enter customer ID to update: ";
                    cin >> id;
                
                    Customer* customer = customers.search(id);
                    if (!customer) {
                        cout << "Customer not found!\n";
                        break;
                    }
                
                    int updateChoice;
                    cout << "What would you like to update?\n"
                         << "1. Name\n"
                         << "2. Phone\n"
                         << "3. Date of Birth\n"
                         << "Enter your choice: ";
                    cin >> updateChoice;
                    cin.ignore(); // Clear newline
                
                    switch (updateChoice) {
                        case 1: {
                            string newName;
                            cout << "Enter new name: ";
                            getline(cin, newName);
                            customer->setName(newName);
                            cout << "Name updated successfully.\n";
                            break;
                        }
                        case 2: {
                            string newPhone;
                            cout << "Enter new phone: ";
                            getline(cin, newPhone);
                            customer->setPhone(newPhone);
                            cout << "Phone updated successfully.\n";
                            break;
                        }
                        case 3: {
                            string newDob;
                            cout << "Enter new date of birth (DD/MM/YYYY): ";
                            getline(cin, newDob);
                            customer->setDob(newDob);
                            cout << "Date of birth updated successfully.\n";
                            break;
                        }
                        default:
                            cout << "Invalid choice. Please try again.\n";
                    }
                    break;
                }
                case 3: { // delete customer
                    int id;
                    cout << "Enter customer ID to delete: ";
                    cin >> id;
                
                    Customer* customer = customers.search(id);
                    if (!customer) {
                        cout << "Customer not found!\n";
                        break;
                    }
                
                    // remove the customer from the BST
                    customers.remove(id);
                
                    // remove the customer from all flights they are associated with
                    for (FlightNode* fnode = flightsHead; fnode != nullptr; fnode = fnode->next) {
                        if (fnode->data.hasPassenger(id)) {
                            fnode->data.removePassenger(id);
                
                            // free the seat associated with the customer
                            for (Ticket& ticket : tickets) {
                                if (ticket.getCustomerId() == id && ticket.getFlightNum() == fnode->data.getFlightNumber()) {
                                    Plane* plane = findPlane(fnode->data.getPlaneId());
                                    if (plane) {
                                        plane->freeSeat(ticket.getSeatNumber());
                                    }
                                    tickets.erase(remove(tickets.begin(), tickets.end(), ticket), tickets.end());
                                    break;
                                }
                            }
                        }
                    }
                
                    cout << "Customer deleted successfully.\n";
                    break;
                }
                case 4: { // view customer profile
                    int id;
                    cout << "Enter customer ID: ";
                    cin >> id;
                
                    Customer* customer = customers.search(id);
                    if (customer) {
                        customer->displayProfile();
                
                        // Show flight history
                        cout << "\nFlight History:\n";
                        for (FlightNode* fnode = flightsHead; fnode != nullptr; fnode = fnode->next) {
                            if (fnode->data.hasPassenger(id)) {
                                cout << "- Flight " << fnode->data.getFlightNumber()
                                     << " to " << fnode->data.getDestination()
                                     << " on " << fnode->data.getDate() << endl;
                            }
                        }
                    } else {
                        cout << "Customer not found.\n";
                    }
                    break;
                }
                case 5: // back to main menu
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 5);
    }

    void handleFlightManagement() {
        int choice;
        do {
            flightManagementMenu();
            cin >> choice;
            if (cin.fail()) {
                cin.clear(); // clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }
            cin.ignore(); // clear newline
    
            switch (choice) {
                case 1: { // add flight
                    int flightNumber, planeId, day, month, year, departureTime;
                    string destination;
                    vector<pair<string, int>> ticketTypes;
    
                    cout << "Enter flight number: ";
                    cin >> flightNumber;

                      // check for duplicate flight number
                     if (findFlight(flightNumber)) {
                    cout << "Error: Flight number " << flightNumber << " already exists.\n";
                    break;
                }
                    cout << "Enter plane ID: ";
                    cin >> planeId;
                    cout << "Enter departure date (day month year): ";
                    cin >> day >> month >> year;
                    cout << "Enter departure time (in minutes since midnight): ";
                    cin >> departureTime;
                    cin.ignore(); // clear newline
                    cout << "Enter destination: ";
                    getline(cin, destination);
    
                    int numTicketTypes;
                    cout << "Enter number of ticket types: ";
                    cin >> numTicketTypes;
                    cin.ignore();
                    for (int i = 0; i < numTicketTypes; ++i) {
                        string type;
                        int price;
                        cout << "Enter ticket type (e.g., Economy, Business): ";
                        getline(cin, type);
                        cout << "Enter price for " << type << ": ";
                        cin >> price;
                        cin.ignore();
                        ticketTypes.push_back({type, price});
                    }
    
                    // create the flight object
                    Flight newFlight(flightNumber, planeId, day, month, year, departureTime, destination, ticketTypes);
    
                    // Add the flight to the doubly linked list
                    FlightNode* newNode = new FlightNode(newFlight);
                    if (flightsHead == nullptr) {
                        flightsHead = flightsTail = newNode;
                    } else {
                        flightsTail->next = newNode;
                        newNode->prev = flightsTail;
                        flightsTail = newNode;
                    }
    
                    cout << "Flight added successfully.\n";
                    break;
                }
                case 2: { // update flight
                    int flightNumber;
                    cout << "Enter flight number to update: ";
                    cin >> flightNumber;
    
                    FlightNode* flightNode = findFlight(flightNumber);
                    if (!flightNode) {
                        cout << "Flight not found!\n";
                        break;
                    }
    
                    int updateChoice;
                    cout << "What would you like to update?\n"
                         << "1. Plane ID\n"
                         << "2. Departure Date\n"
                         << "3. Departure Time\n"
                         << "4. Destination\n"
                         << "5. Ticket Types\n"
                         << "Enter your choice: ";
                    cin >> updateChoice;
                    cin.ignore(); // clear newline
    
                    switch (updateChoice) {
                        case 1: {
                            int newPlaneId;
                            cout << "Enter new plane ID: ";
                            cin >> newPlaneId;
                            flightNode->data = Flight(flightNode->data.getFlightNumber(), newPlaneId,
                                                      flightNode->data.getDay(), flightNode->data.getMonth(),
                                                      flightNode->data.getYear(), flightNode->data.getDepartureTimeInMinutes(),
                                                      flightNode->data.getDestination(), flightNode->data.getTicketTypes());
                            cout << "Plane ID updated successfully.\n";
                            break;
                        }
                        case 2: {
                            int newDay, newMonth, newYear;
                            cout << "Enter new departure date (day month year): ";
                            cin >> newDay >> newMonth >> newYear;
                            flightNode->data = Flight(flightNode->data.getFlightNumber(), flightNode->data.getPlaneId(),
                                                      newDay, newMonth, newYear, flightNode->data.getDepartureTimeInMinutes(),
                                                      flightNode->data.getDestination(), flightNode->data.getTicketTypes());
                            cout << "Departure date updated successfully.\n";
                            break;
                        }
                        case 3: {
                            int newDepartureTime;
                            cout << "Enter new departure time (in minutes since midnight): ";
                            cin >> newDepartureTime;
                            flightNode->data = Flight(flightNode->data.getFlightNumber(), flightNode->data.getPlaneId(),
                                                      flightNode->data.getDay(), flightNode->data.getMonth(),
                                                      flightNode->data.getYear(), newDepartureTime,
                                                      flightNode->data.getDestination(), flightNode->data.getTicketTypes());
                            cout << "Departure time updated successfully.\n";
                            break;
                        }
                        case 4: {
                            string newDestination;
                            cout << "Enter new destination: ";
                            cin.ignore(); // Clear newline
                            getline(cin, newDestination);
                            flightNode->data = Flight(flightNode->data.getFlightNumber(), flightNode->data.getPlaneId(),
                                                      flightNode->data.getDay(), flightNode->data.getMonth(),
                                                      flightNode->data.getYear(), flightNode->data.getDepartureTimeInMinutes(),
                                                      newDestination, flightNode->data.getTicketTypes());
                            cout << "Destination updated successfully.\n";
                            break;
                        }
                        case 5: {
                            int numTicketTypes;
                            cout << "Enter number of ticket types: ";
                            cin >> numTicketTypes;
                            cin.ignore();
    
                            vector<pair<string, int>> newTicketTypes;
                            for (int i = 0; i < numTicketTypes; ++i) {
                                string type;
                                int price;
                                cout << "Enter ticket type (e.g., Economy, Business): ";
                                getline(cin, type);
                                cout << "Enter price for " << type << ": ";
                                cin >> price;
                                cin.ignore();
                                newTicketTypes.push_back({type, price});
                            }
    
                            flightNode->data = Flight(flightNode->data.getFlightNumber(), flightNode->data.getPlaneId(),
                                                      flightNode->data.getDay(), flightNode->data.getMonth(),
                                                      flightNode->data.getYear(), flightNode->data.getDepartureTimeInMinutes(),
                                                      flightNode->data.getDestination(), newTicketTypes);
                            cout << "Ticket types updated successfully.\n";
                            break;
                        }
                        default:
                            cout << "Invalid choice. Please try again.\n";
                    }
                    break;
                }
                case 3: { // delete flight
                    int flightNumber;
                    cout << "Enter flight number to delete: ";
                    cin >> flightNumber;
                
                    FlightNode* flightNode = findFlight(flightNumber);
                    if (!flightNode) {
                        cout << "Flight not found!\n";
                        break;
                    }
                
                    // cancel reservations for all passengers on this flight
                    vector<Customer> passengers = flightNode->data.getAllPassengers(); // Get all passengers
                    for (const Customer& customer : passengers) {
                        cancelReservation(customer.getCustomerId(), flightNode->data.getFlightNumber());
                    }
                
                    // remove the flight from the linked list
                    if (flightNode->prev) {
                        flightNode->prev->next = flightNode->next;
                    } else {
                        flightsHead = flightNode->next;
                    }
                
                    if (flightNode->next) {
                        flightNode->next->prev = flightNode->prev;
                    } else {
                        flightsTail = flightNode->prev;
                    }
                
                    delete flightNode;
                    cout << "Flight deleted successfully.\n";
                    break;
                }
                case 4: { // view flights
                    FlightNode* current = flightsHead;
                    while (current != nullptr) {
                        current->data.displayInfo();
                        cout << "------------------------\n";
                        current = current->next;
                    }
                    if (flightsHead == nullptr) {
                        cout << "No flights available.\n";
                    }
                    break;
                }
                case 5: // back to main menu
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 5);
    }
};




int main() {
    cout << "Starting Flight Reservation System...\n";
    FlightReservationSystem system;
    cout << "System initialized. Entering main loop...\n";
    system.run();
    cout << "System shutdown complete.\n";
    return 0;
}

//ASSUMPTIONS

//PLANE CAPACITY IS ASSUMED FROM PLANES.TXT