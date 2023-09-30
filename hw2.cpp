#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

class Commodity;
class Store;
class InputHandler;


class InputHandler {
public:
    /*
     * The function is used to read a full line into a string variable.
     * It read the redundant '\n' character to prevent the problem of getline function.
     * There is an overload version which can read from the specified data stream.
     * INPUT: None, or fstream
     * RETURN: Full line input by user
     * */
    static string readWholeLine() {
        string input;
        getline(cin, input);
        return input;
    }


    static string readWholeLine(fstream& file) {
        string input;
        char t;
        t = file.get();
        getline(file, input);
        if(t != '\n'){
            return t + input;
        }else{
            return input;
        }
    }

    /*
     * This function is used to configure whether the input string is a number
     * INPUT: A string
     * RETURN: Bool. True if input string is a number, otherwise false.
     */
    static bool isNum(string& str) {
        for (int i = 0; i < str.size(); i++) {
            if (!isdigit(str[i])) {
                return false;
            }
        }
        return true;
    }

    /*
     * Check the input string is a valid number.
     * First check the input is a number or not, then identify whether it is bigger than 0
     * INPUT: string
     * RETURN: bool
     */
    static bool isValidNum(string& str) {
        if (!isNum(str) || (isNum(str) && stoi(str) <= 0))
            return false;
        return true;
    }

    /*
     * Get a number from the user. This function will check the input validation.
     * INPUT: none
     * OUTPUT: integer, the input number
     */
    static int numberInput() {
        string input;
        cin >> input;
        while (!isValidNum(input)) {
            cout << "Please input again your input is NOT an integer or is lower than or equal to 0:" << endl;
            cin >> input;
        }
        return stoi(input);
    }

    /*
     * This function is used in function getInput. Check the input range is inside the specified range
     */
    static int inputCheck(string input, int maxChoiceLen, bool noZero) {
        // Change input to the general integer
        int choice = 0;
        for (int i = 0; i < input.size(); i++) {
            if (isdigit(input[i])) {
                choice = choice * 10 + (input[i] - '0');
            } else {
                return -1;
            }
        }

        if (noZero) {
            return (choice <= maxChoiceLen && choice > 0) ? choice : -1;
        } else {
            return (choice <= maxChoiceLen && choice >= 0) ? choice : -1;
        }
    }

    /*
     * Get the input from the user, and limit the input between the range [0, maxChoiceLen].
     * If noZero is signaled. Then the range will be [1, maxChoiceLen]
     * INPUT: integer, bool(option)
     * OUTPUT: integer, the choice number
     */
    static int getInput(int maxChoiceLen, bool noZero = false) {
        string input;

        cin >> input;
        int choice = inputCheck(input, maxChoiceLen, noZero);
        while (choice == -1) {
            cout << "your input is wrong, please input again:" << endl;
            cin >> input;
            choice = inputCheck(input, maxChoiceLen, noZero);
        }

        return choice;
    }
};

/*
 * Commodity is about an item which the user can buy and the manager can add or delete.
 * ATTRIBUTE:
 *  price: The price of the commodity, an integer.
 *  description: The text which describe the commodity detail, a string.
 *  commodityName: The name of the commodity, a string.
 */
class Commodity {
protected:
    int price , no , type_num;
    string description;
    string commodityName;
    string instrument_1,instrument_2;
    string clothes_1,clothes_2;
    string drink_1,drink_2;
    Commodity *ptr;

public:
    ~Commodity() = default;
    Commodity() {
        price = 0;
        description = "";
        commodityName = "";
        instrument_1 = "";
        instrument_2 = "";
        clothes_1 = "";
        clothes_2 = "";
        drink_1 = "";
        drink_2 = "";
        ptr = NULL;
    }

    Commodity(int price, string commodityName,string description) {
        this->price = price;
        this->commodityName = commodityName;
        this->description = description;
    }

    /*
     * This method will show the full information of the commodity to user interface.
     * There is a overloading version, with an argument amount which will output the information with the amount
     * INPUT: None, or an integer specify the amount of this commodity
     * RETURN: None
     */
    virtual void detail() {
        /*cout << commodityName << endl;
        cout << "price: " << price << endl;
        cout << "description: " << description << endl;
        cout << "----------------------------" << endl;*/
    }

    virtual void detail(int amount) {
        cout << commodityName << endl;
        cout << "price: " << price << endl;
        cout << "description: " << description << endl;
        cout << "x " << amount << endl;
        cout << "----------------------------" << endl;
    }

    /*
     * Use this function to get the information data from the user, this will init the object.
     * INPUT: none
     * OUTPUT: none
     */
    virtual void userSpecifiedCommodity() {}

    /*
     * Save and load function is used to write the data to the file or read the data from the file.
     * According to the input parameter fstream, they complete the I/O on the specified file.
     * There have no definition of those method, because it is used to be override in the derived class.
     * INPUT: fstream
     * OUTPUT: none
     */
    virtual void save(fstream& file) {
    }

    virtual void load(fstream& file) {}

    /*
     * The getter function of commodityName
     */

    void writeName(string s){
        commodityName = s;
    }

    string getName() {
        return commodityName;
    }

    /*
     * The getter function of price
     */

    void writePrice( int a){
        price = a;
    }

    int getPrice() {
        return price;
    }

    void writeDescription(string s){
        description = s;
    }

    string getDescription(){
        return description;
    }

    void writeptr(Commodity *a){
        ptr = a;
    }

    Commodity *reaptr(){
        return ptr;
    }

    void writeno(int a){
        no=a;
    }

    int readno(){
        return no;
    }

    void writeInstrument_1(string s){
        instrument_1 = s;
    }

    string getInstrument_1(){
        return instrument_1;
    }

    void writeInstrument_2(string s){
        instrument_2 = s;
    }

    string getInstrument_2(){
        return instrument_2;
    }

    void wrieClothes_1(string s){
        clothes_1 = s;
    }

    string getClothes_1(){
        return clothes_1;
    }

    void writeClothes_2(string s){
        clothes_2 = s;
    }

    string getClothes_2(){
        return clothes_2;
    }

    void writeDrink_1(string s){
        drink_1 = s;
    }

    string getDrink_1(){
        return drink_1;
    }

    void writeDrink_2(string s){
        drink_2 = s;
    }

    string getDrink_2(){
        return drink_2;
    }

    void writeType_num(int a){
        type_num = a;
    }

    int readType_num(){
        return type_num;
    }
};



/*
 * [YOU SHOULD FINISH THREE TYPES OF DERIVED COMMODITY CLASS HERE]
 * Please try your best to complete the definition of three classes.
 * Use the knowledge you learned from this course.
 * You should follow the OOP concept.
 */
class instrument : public Commodity{
private:
public:
    void userSpecifiedCommodity(){
        cout << "Please input the instument's name:" << endl;
        cin.get();
        commodityName = InputHandler::readWholeLine();

        cout << "Please input the instrument's price:" << endl;
        price = InputHandler::numberInput();

        cout<<"Who make this instrument?"<<endl;
        cin.get();
        instrument_1 = InputHandler::readWholeLine();

        cout<<"When was this instrument be produced?"<<endl;
        //cin.get();
        instrument_2 = InputHandler::readWholeLine();

        cout << "Please input the detail of the instrument:" << endl;
        //cin.get();
        description = InputHandler::readWholeLine();
    }

    void datail(){
        cout<<commodityName<<endl;
        cout<<"Price:"<<price<<endl;
        cout<<"Producer:"<<instrument_1<<endl;
        cout<<"Produced in :"<<instrument_2<<endl;
        cout<<"Description:"<<description<<endl;
        cout<<"--------------------------------------"<<endl;
    }
};

class clothes : public Commodity{
private:
public:
    string s="S",m = "M", l = "L";
    int size_num;
    void userSpecifiedCommodity(){
        cout<<"Please input the clothes name:" << endl;
        cin.get();
        commodityName = InputHandler::readWholeLine();

        cout << "Please input the clothes price:" << endl;
        price = InputHandler::numberInput();

        cout<<"What the size of the clothes?   1.S   2.M   3.L"<<endl;
        cin>>size_num;
        while(size_num<1 || size_num>3){
            cout << "your input is wrong, please input again:" << endl;
            cin>>size_num;
        }
        if(size_num == 1){
            clothes_1 = s;
        }
        else if(size_num == 2){
            clothes_1 = m;
        }
        else if(size_num ==3){
            clothes_1 =l;
        }

        cout<<"What is the color of this clothes"<<endl;
        cin.get();
        clothes_2 = InputHandler::readWholeLine();

        cout << "Please input the detail of the clothes:" << endl;
        //cin.get();
        description = InputHandler::readWholeLine();

        type_num = 2;
    }

    void detail(){
        cout<<commodityName<<endl;
        cout<<"Price:"<<price<<endl;
        cout<<"Size:"<<clothes_1<<endl;
        cout<<"Color:"<<clothes_2<<endl;
        cout<<"Description:"<<description<<endl;

    }
};

class drink : public Commodity{
private:
public:
    void userSpecifiedCommodity(){
        string sugar_1 = "No sugar", sugar_2 = "Low sugar", sugar_3 = "Hlaf sugar", sugar_4 = "Stander";
        string ice_1 = "No ice" , ice_2 = "Low ice", ice_3 = "Less ice", ice_4 = "Normal";
        int sugar_num , ice_num;

        cout << "Please input the drink's name:" << endl;
        cin.get();
        commodityName = InputHandler::readWholeLine();

        cout << "Please input the drink's price:" << endl;
        price = InputHandler::numberInput();

        cout<<"How would you adjust your sugar? 1.No sugar  2.Low sugar  3.Half sugar  4.Stander"<<endl;
        cin>>sugar_num;
        while (sugar_num<1 || sugar_num>4){
            cout << "your input is wrong, please input again:" << endl;
            cin>>sugar_num;
        }
        if(sugar_num == 1){
            drink_1 = sugar_1;
        }
        else if(sugar_num == 2){
            drink_1 = sugar_2;
        }
        else if(sugar_num == 3){
            drink_1 = sugar_3;
        }
        else if(sugar_num == 4){
            drink_1 = sugar_4;
        }

        cout<<"How would you adjust your ice? 1.No ice  2.Low ice  3.Less ice  4.Normal"<<endl;
        cin>>ice_num;
        while (ice_num<1 || ice_num>4){
            cout << "your input is wrong, please input again:" << endl;
            cin>>ice_num;
        }
        if(ice_num == 1){
            drink_2 = ice_1;
        }
        else if(ice_num == 2){
            drink_2 = ice_2;
        }
        else if(ice_num == 3){
            drink_2 = ice_3;
        }
        else if(ice_num == 4){
            drink_2 = ice_4;
        }

        cout << "Please input the detail of the drink:" << endl;
        cin.get();
        description = InputHandler::readWholeLine();

        type_num = 3;
    }

    void detail(){
        cout<<commodityName<<endl;
        cout<<"Price:"<<price<<endl;
        cout<<"Sugar:"<<drink_1<<endl;
        cout<<"Ice:"<<drink_2<<endl;
        cout<<"Description:"<<description<<endl;
    }
};

/*
 * [YOU NEED TO FINISH THIS CLASS]
 * This is a list storing the existing commodity in the store.
 * There are some method which can modify the content.
 * You may use any data structure to complete this class.
 */
class CommodityList {
private:
    Commodity *instrument_head , *clothes_head , *drink_head;
    int total_amount = instrument_amount+clothes_amount+drink_amount;
public:
    Commodity *instrument_check , *clothes_check , *drink_check , *p;
    int instrument_amount = 0, clothes_amount = 0 , drink_amount = 0;

    CommodityList() {
        instrument_head = NULL;
        clothes_head = NULL;
        drink_head = NULL;
    }

    /*
     * Print the full information of the commodities inside the list
     * You must call Commodity.detail() to show the commodity information.
     * INPUT: None
     * RETURN: None
     */
    void showCommoditiesDetail() {
        int i=1;
        cout<<"Instrument:"<<endl;
        instrument_check = instrument_head;
        while (instrument_check != NULL){
            cout<<i<<". ";
            cout<<instrument_check->getName()<<endl;
            cout<<"Price:"<<instrument_check->getPrice()<<endl;
            cout<<"Producer:"<<instrument_check->getInstrument_1()<<endl;
            cout<<"Produce in:"<<instrument_check->getInstrument_2()<<endl;
            cout<<"Description:"<<instrument_check->getDescription()<<endl;
            cout<<" "<<endl;
            instrument_check = instrument_check->reaptr();
            i++;
        }
        cout<<" "<<endl;
        cout<<"--------------------------------------"<<endl;
        cout<<"Clothes:"<<endl;
        clothes_check = clothes_head;
        while (clothes_check != NULL){
            cout<<i<<". ";
            clothes_check->detail();
            cout<<" "<<endl;
            clothes_check = clothes_check->reaptr();
            i++;
        }
        cout<<" "<<endl;
        cout<<"--------------------------------------"<<endl;
        cout<<"Drink:"<<endl;
        drink_check = drink_head;
        while (drink_check != NULL){
            cout<<i<<". ";
            drink_check->detail();
            cout<<" "<<endl;
            drink_check = drink_check->reaptr();
            i++;
        }
        cout<<"--------------------------------------"<<endl;
    }

    /*
     * Print only the commodity name of the commodities inside the list
     * You don't need to use Commodity.detail() here, just call the Commodity.getName() function is ok
     * INPUT: None
     * RETURN: None
     */
    void showCommoditiesName() {
        int i=1;
        cout<<"Instrument:"<<endl;
        instrument_check = instrument_head;
        while (instrument_check != NULL){
            cout<<i<<". "<<instrument_check->getName()<<endl;
            instrument_check = instrument_check->reaptr();
            i++;
        }
        cout<<" "<<endl;
        cout<<"--------------------------------------"<<endl;
        cout<<"Clothes:"<<endl;
        clothes_check = clothes_head;
        while (clothes_check != NULL){
            cout<<i<<". "<<clothes_check->getName()<<endl;
            clothes_check = clothes_check->reaptr();
            i++;
        }
        cout<<" "<<endl;
        cout<<"--------------------------------------"<<endl;
        cout<<"Drink:"<<endl;
        drink_check = drink_head;
        while (drink_check != NULL){
            cout<<i<<". "<<drink_check->getName()<<endl;
            drink_check = drink_check->reaptr();
            i++;
        }
        cout<<"--------------------------------------"<<endl;
    }

    /*
     * Check whether the list is empty or not
     * INPUT: None
     * RETURN: Bool. True if the list is empty, otherwise false
     */
    bool empty() {
        if(instrument_head == NULL && clothes_head == NULL && drink_head == NULL)   return true;
        else return false;
    }

    /*
     * Return the size(or length) of the list
     * INPUT: None
     * RETURN: Integer. List size
     */
    int size() {
        return total_amount;
    }

    /*
     * Return a commodity object at specified position
     * INPUT: Integer. The index of that commodity
     * RETURN: Commodity. The wanted commodity object
     */
    Commodity get(int index) {
        int i =1;
        instrument_check = instrument_head;
        while(instrument_check != NULL){
            instrument_check->writeno(i);
            instrument_check = instrument_check->reaptr();
            i++;
        }
        clothes_check = clothes_head;
        while (clothes_check != NULL){
            clothes_check->writeno(i);
            clothes_check = clothes_check->reaptr();
            i++;
        }
        drink_check = drink_head;
        while(drink_check != NULL){
            drink_check->writeno(i);
            drink_check = drink_check->reaptr();
            i++;
        }

        p = NULL;
        instrument_check = instrument_head;
        while (instrument_check != NULL){
            if( index+1 == instrument_check->readno()){
                return *instrument_check;
            }
            p = instrument_check;
            instrument_check = instrument_check->reaptr();
        }

        p = NULL;
        clothes_check = clothes_head;
        while (clothes_check != NULL){
            if (index+1 == clothes_check->readno()){
                return *clothes_check;
            }
            p = clothes_check;
            clothes_check = clothes_check->reaptr();
        }

        p = NULL;
        drink_check =drink_head;
        while (drink_check != NULL){
            if (index+1 == drink_check->readno()){
                return *drink_check;
            }
            p = drink_check;
            drink_check = drink_check->reaptr();
        }


    }

    /*
     * Push a new commodity object into the list
     * INPUT: Commodity. The object need to be pushed
     * RETURN: None
     */
    void add(Commodity* newCommodity, string& cat) {
        if (cat == "instrument"){
            if(instrument_head == NULL){
                instrument_head = newCommodity;
                instrument_head->writeType_num(1);
            }
            else {
                instrument_check = instrument_head;
                while (instrument_check->reaptr() != NULL){
                    instrument_check = instrument_check->reaptr();
                }
                instrument_check->writeptr(newCommodity);
                instrument_check->reaptr()->writeType_num(1);
            }
            instrument_amount++;
        }else if(cat == "clothes"){
            if(clothes_head == NULL){
                clothes_head = newCommodity;
                clothes_head->writeType_num(2);
            } else{
                clothes_check = clothes_head;
                while (clothes_check->reaptr() != NULL){
                    clothes_check = clothes_check->reaptr();
                }
                clothes_check->writeptr(newCommodity);
                clothes_check->reaptr()->writeType_num(2);
            }
            clothes_amount++;
        }else if (cat == "drink"){
            if(drink_head == NULL){
                drink_head = newCommodity;
                drink_head ->writeType_num(3);
            } else{
                drink_check =drink_head;
                while (drink_check->reaptr() != NULL){
                    drink_check = drink_check->reaptr();
                }
                drink_check->writeptr(newCommodity);
                drink_check->reaptr()->writeType_num(3);
            }
            drink_amount++;
        }
    }

    /*
     * Check the input commodity object is existing inside the list
     * If the commodity name is the same, we take those objects the same object
     * INPUT: Commodity. The object need to be checked
     * OUTPUT: Bool. True if the object existing, otherwise false
     */
    bool isExist(Commodity* commodity , string &cat) {
        if (cat == "instrument"){
            instrument_check = instrument_head;
            while(instrument_check != NULL && instrument_check->getName() != commodity->getName()){
                instrument_check = instrument_check->reaptr();
            }
            if(instrument_check == NULL)    return false;
            else return true;
        }else if(cat == "clothes"){
            clothes_check = clothes_head;
            while(clothes_check != NULL && clothes_check->getName() != commodity->getName()){
                clothes_check = clothes_check->reaptr();
            }
            if(clothes_check == NULL)   return false;
            else return true;
        }else if (cat == "drink"){
            drink_check =drink_head;
            while(drink_check != NULL && drink_check->getName() != commodity->getName()){
                drink_check =drink_check->reaptr();
            }
            if (drink_check ==NULL)     return false;
            else return true;
        }
    }

    /*
     * Remove an object specified by the position
     * INPUT: Integer. The position of the object which need to be removed
     * OUTPUT: None
     */
    void remove(int index) {
        int i =1;
        instrument_check = instrument_head;
        while(instrument_check != NULL){
            instrument_check->writeno(i);
            instrument_check = instrument_check->reaptr();
            i++;
        }
        clothes_check = clothes_head;
        while (clothes_check != NULL){
            clothes_check->writeno(i);
            clothes_check = clothes_check->reaptr();
            i++;
        }
        drink_check = drink_head;
        while(drink_check != NULL){
            drink_check->writeno(i);
            drink_check = drink_check->reaptr();
            i++;
        }

        p = NULL;
        instrument_check = instrument_head;  //delete instrument
        while (instrument_check != NULL){
            if( index+1 == instrument_check->readno()){
                if(instrument_check == instrument_head){
                    instrument_head = instrument_head->reaptr();
                    cout<<"Remove this item"<<endl;
                }
                else{
                    p->writeptr(instrument_check->reaptr());
                    cout<<"Remove this item"<<endl;
                }
                instrument_amount--;
            }
            p = instrument_check;
            instrument_check = instrument_check->reaptr();
        }

        p = NULL;
        clothes_check = clothes_head;   //delete clothes
        while (clothes_check != NULL){
            if (index+1 == clothes_check->readno()){
                if(clothes_check == clothes_head){
                    clothes_head =clothes_head->reaptr();
                    cout<<"Remove this item"<<endl;
                }
                else{
                    p->writeptr(clothes_check->reaptr());
                    cout<<"Remove this item"<<endl;
                }
                clothes_amount--;
            }
            p = clothes_check;
            clothes_check = clothes_check->reaptr();
        }

        p = NULL;
        drink_check =drink_head;    //delete drink
        while (drink_check != NULL){
            if (index+1 == drink_check->readno()){
                if (drink_check == drink_head){
                    drink_head = drink_head->reaptr();
                    cout<<"Remove this item"<<endl;
                } else{
                    p->writeptr(drink_check->reaptr());
                    cout<<"Remove this item"<<endl;
                }
                drink_amount--;
            }
            p = drink_check;
            drink_check = drink_check->reaptr();
        }
    }


    void load(){
        fstream file;
        file.open("hw2.txt" , ios_base::in);
        char con[61]={'\0'};
        int k;
        file>>instrument_amount;
        file>>clothes_amount;
        file>>drink_amount;
        for(int i=0; i<instrument_amount ; i++){
            instrument *p = new instrument;
            p->writeName(InputHandler::readWholeLine(file));
            p->writePrice(stoi(InputHandler::readWholeLine(file)));
            p->writeInstrument_1(InputHandler::readWholeLine(file));
            p->writeInstrument_2(InputHandler::readWholeLine(file));
            p->writeDescription(InputHandler::readWholeLine(file));
            p->writeptr(NULL);
            if(instrument_head == NULL){
                instrument_head = p;
                instrument_check = instrument_head;
            }else{
                instrument_check->writeptr(p);
                instrument_check = p;
            }
        }
        for(int i=0 ;i<clothes_amount ; i++){
            clothes *p = new clothes;
            p->writeName(InputHandler::readWholeLine(file));
            p->writePrice(stoi(InputHandler::readWholeLine(file)));
            p->wrieClothes_1(InputHandler::readWholeLine(file));
            p->writeClothes_2(InputHandler::readWholeLine(file));
            p->writeDescription(InputHandler::readWholeLine(file));
            if(clothes_head == NULL){
                clothes_head = p;
                clothes_check = clothes_head;
            }else{
                clothes_check->writeptr(p);
                clothes_check = p;
            }
        }
        for(int i=0 ;i<drink_amount;i++){
            drink *p = new drink;
            p->writeName(InputHandler::readWholeLine(file));
            p->writePrice(stoi(InputHandler::readWholeLine(file)));
            p->writeDrink_1(InputHandler::readWholeLine(file));
            p->writeDrink_2(InputHandler::readWholeLine(file));
            p->writeDescription(InputHandler::readWholeLine(file));
            if(drink_head == NULL){
                drink_head = p;
                drink_check = drink_head;
            }else {
                drink_check->writeptr(p);
                drink_check = p;
            }
        }
    }

    void save() {
        fstream file;
        int i = 1;
        file.open("hw2.txt" ,ios_base::trunc | ios_base::out);
        cout<<"success"<<endl;
        file<<instrument_amount<<endl;
        file<<clothes_amount<<endl;
        file<<drink_amount<<endl;
        instrument_check = instrument_head;
        while (instrument_check != NULL){
            file<<instrument_check->getName()<<endl;
            file<<instrument_check->getPrice()<<endl;
            file<<instrument_check->getInstrument_1()<<endl;
            file<<instrument_check->getInstrument_2()<<endl;
            file<<instrument_check->getDescription()<<endl;
            instrument_check = instrument_check->reaptr();
        }
        clothes_check = clothes_head;
        while (clothes_check != NULL){
            file<<clothes_check->getName()<<endl;
            file<<clothes_check->getPrice()<<endl;
            file<<clothes_check->getClothes_1()<<endl;
            file<<clothes_check->getClothes_2()<<endl;
            file<<clothes_check->getDescription()<<endl;
            clothes_check = clothes_check->reaptr();
        }

        drink_check = drink_head;
        while (drink_check != NULL){
            file<<drink_check->getName()<<endl;
            file<<drink_check->getPrice()<<endl;
            file<<drink_check->getDrink_1()<<endl;
            file<<drink_check->getDrink_2()<<endl;
            file<<drink_check->getDescription()<<endl;
            drink_check = drink_check->reaptr();
        }
    }
};

/*
 * [YOU NEED TO FINISH THIS CLASS]
 * The shopping cart is used to store the commodities user wanted.
 * Because the same name represents the same object, if there is a commodity which have more than one object inside
 * the cart, then it will be store as the same object and the cart must keep the amount of the object.
 * You may use any data structure to complete this class.
 */
class ShoppingCart {
private:
    ShoppingCart *next=NULL;
    int price , item_amount=1 , type_num , no;
    string instrument_1,instrument_2;
    string clothes_1,clothes_2;
    string drink_1,drink_2;
    string commodityName , description;
public:
    ShoppingCart *head=NULL, *check ,*x ,*z ;
    /*
     * Push an commodity object into the cart.
     * Be careful that if the input object is existing in the list, then keep the amount of that object rather than
     * actually push the object into the cart.
     * INPUT: Commodity. The object need to be pushed.
     * OUTPUT: None.
     */
    void push(Commodity entry) {
        x = new ShoppingCart;
        if(entry.readType_num() == 1){
            if(head == NULL){
                head = x;
                x->commodityName = entry.getName();
                x->price = entry.getPrice();
                x->instrument_1 = entry.getInstrument_1();
                x->instrument_2 = entry.getInstrument_2();
                x->description = entry.getDescription();
                x->item_amount;
                x->type_num = 1;
                cout<<"Successfully push the item into the ShopCart.1"<<endl;
                cout<<" "<<endl;
            } else{
                check = head;
                while (check){
                    if(check->commodityName == entry.getName()){
                        check->item_amount = check->item_amount+1;
                        cout<<"Successfully push the item into the ShopCart.2"<<endl;
                        cout<<" "<<endl;
                        return;
                    }else check = check->next;
                }
                check = head;
                while (check->next != NULL){
                    check = check->next;
                }
                check->next = x;
                x->commodityName = entry.getName();
                x->price = entry.getPrice();
                x->instrument_1 = entry.getInstrument_1();
                x->instrument_2 = entry.getInstrument_2();
                x->description = entry.getDescription();
                x->item_amount;
                x->type_num = 1;
                cout<<"Successfully push the item into the ShopCart.3"<<endl;
                cout<<" "<<endl;
            }
        }else if (entry.readType_num() == 2){
            if(head == NULL){
                head = x;
                x->commodityName = entry.getName();
                x->price = entry.getPrice();
                x->clothes_1 = entry.getClothes_1();
                x->clothes_2 = entry.getClothes_2();
                x->description = entry.getDescription();
                x->item_amount;
                x->type_num = 2;
                cout<<"Successfully push the item into the ShopCart.4"<<endl;
                cout<<" "<<endl;
            }else {
                check = head;
                while (check){
                    if(check->commodityName == entry.getName()){
                        check->item_amount = check->item_amount+1;
                        cout<<"Successfully push the item into the ShopCart.5"<<endl;
                        cout<<" "<<endl;
                        return;
                    }else check = check->next;
                }
                check = head;
                while (check->next != NULL){
                    check = check->next;
                }
                check->next =x;
                x->commodityName = entry.getName();
                x->price = entry.getPrice();
                x->clothes_1 = entry.getClothes_1();
                x->clothes_2 = entry.getClothes_2();
                x->description = entry.getDescription();
                x->item_amount;
                x->type_num = 2;
                cout<<"Successfully push the item into the ShopCart.6"<<endl;
                cout<<" "<<endl;
            }

        }else if (entry.readType_num() == 3){
            if (head == NULL){
                head = x;
                x->commodityName = entry.getName();
                x->price = entry.getPrice();
                x->drink_1 = entry.getDrink_1();
                x->drink_2 = entry.getDrink_2();
                x->description = entry.getDescription();
                x->item_amount;
                x->type_num = 3;
                cout<<"Successfully push the item into the ShopCart.7"<<endl;
                cout<<" "<<endl;
            }else {
                check = head;
                while (check){
                    if(check->commodityName == entry.getName()){
                        check->item_amount = check->item_amount+1;
                        cout<<"Successfully push the item into the ShopCart.8"<<endl;
                        cout<<" "<<endl;
                        return;
                    }else check = check->next;
                }
                check = head;
                while (check->next != NULL){
                    check = check->next;
                }
                check->next = x;
                x->commodityName = entry.getName();
                x->price = entry.getPrice();
                x->drink_1 = entry.getDrink_1();
                x->drink_2 = entry.getDrink_2();
                x->description = entry.getDescription();
                x->item_amount;
                x->type_num = 3;
                cout<<"Successfully push the item into the ShopCart.9"<<endl;
                cout<<" "<<endl;
            }
        }
    }

    /*
     * Show the content of the cart to user interface.
     * INPUT: None.
     * OUTPUT: None.
     */
    void showCart() {
        int i = 1;
        x = head;
        while (x) {
            cout << i << ". ";
            cout << x->commodityName << endl;
            cout << "Price:" << x->price << endl;
            cout << "Producer:" << x->instrument_1 << endl;
            if(x->type_num == 1){
                cout << "Produced in :" << x->instrument_2 << endl;
                cout << "Description:" << x->description << endl;
            }else if(x->type_num == 2){
                cout<<"Size:"<<x->clothes_1<<endl;
                cout<<"Color:"<<x->clothes_2<<endl;
            }else if(x->type_num == 3){
                cout<<"Sugar:"<<x->drink_1<<endl;
                cout<<"Ice:"<<x->drink_2<<endl;
            }
            cout << "x" << x->item_amount << endl;
            cout << " " << endl;
            x = x->next;
            i++;
        }
    }

    /*
     * Return the cart size. (The same object must be seen as one entry)
     * INPUT: None.
     * OUTPUT: Integer. The cart size.
     */
    int size() {
        int i=0;
        x = head;
        while(x){
            i++;
            x=x->next;
        }
        return i;
    }

    /*
     * Remove an entry from the cart. Don't care about the amount of the commodity, just remove it.
     * INPUT: The order of the entry.
     * OUTPUT: None.
     */
    void remove(int index) {
        int i=1;
        x = head;
        while (x){
            x->no = i;
            x = x->next;
            i++;
        }

        z = NULL , x = head;
        while(x!=NULL){
            if(index+1 == x->no){
                if(x == head){
                    head = head->next;
                    cout<<"Remove this item"<<endl;
                }
                else{
                    z->next = x->next;
                    cout<<"Remove this item"<<endl;
                }
            }
            z=x;
            x=x->next;
        }

    }

    /*
     * Check the total amount of price for the user.
     * Remember to clear the list after checkout.
     * INPUT: None.
     * OUTPUT: Integer. The total price.
     */
    int checkOut() {
        int sum=0;
        x = head;
        while(x){
            sum = sum + (x->price * x->item_amount);
            x = x->next;
        }
        head = NULL;
        return sum;
    }

    /*
     * Check if the cart have nothing inside.
     * INPUT: None.
     * OUTPUT: Bool. True if the cart is empty, otherwise false.
     */
    bool empty() {
        if (head == NULL) return true;
        else return false;
    }
};

/*
 * [DO NOT MODIFY ANY CODE HERE]
 * The Store class manage the flow of control, and the interface showing to the user.
 * Store use status to choose the interface to show. As the result, status control is very important here.
 * If you can understand the code here, you will have great work on the above two class.
 * The detail of Store is in the README
 */
class Store {
private:
    enum UMode {USER, MANAGER} userStatus;
    enum SMode {OPENING, DECIDING, SHOPPING, CART_CHECKING, CHECK_OUT, MANAGING, CLOSE} storeStatus;
    CommodityList commodityList;
    ShoppingCart cart;

    void commodityInput() {
        int item_type=0;
        cout << "Which type of commodity you want to add?" << endl;
        cout<<"1. Instrument   2.Clothes   3.Drink"<<endl;
        cin>>item_type;

        while (item_type<1 || item_type>3)  {
            cout << "your input is wrong, please input again:" << endl;
            cin>>item_type;
        }
        if(item_type == 1){
            instrument *newCom = new instrument;
            newCom->userSpecifiedCommodity();
            string cat("instrument");
            if (commodityList.isExist(newCom , cat)) {
                cout << "[WARNING] " <<newCom->getName() << " is exist in the store. If you want to edit it, please delete it first" << endl;
            } else {
                commodityList.add(newCom , cat);
            }
        }
        else if(item_type == 2){
            clothes *newCom = new clothes;
            newCom->userSpecifiedCommodity();
            string cat("clothes");
            if (commodityList.isExist(newCom , cat)) {
                cout << "[WARNING] " << newCom->getName() << " is exist in the store. If you want to edit it, please delete it first" << endl;
            } else {
                commodityList.add(newCom , cat);
            }
        }
        else if(item_type == 3){
            drink *newCom = new drink;
            newCom->userSpecifiedCommodity();
            string cat("drink");
            if (commodityList.isExist(newCom , cat)) {
                cout << "[WARNING] " << newCom->getName() << " is exist in the store. If you want to edit it, please delete it first" << endl;
            } else {
                commodityList.add(newCom , cat);
            }
        }
        /*
         * You should finish this method, because you need to identify the type of commodity, and instantiate a
         * corresponding derived commodity class here.
         */
    }




    void deleteCommodity() {
        if (commodityList.empty()) {
            cout << "No commodity inside the store" << endl;
            return;
        }

        int choice;
        cout << "There are existing commodity in our store:" << endl;
        commodityList.showCommoditiesName();
        cout << "Or type 0 to regret" << endl
             << "Which one do you want to delete?" << endl;

        choice = InputHandler::getInput(commodityList.size());

        if (choice != 0) {
            commodityList.remove(choice - 1);
        }
    }

    void showCommodity() {
        if (commodityList.empty()) {
            cout << "No commodity inside the store" << endl;
            return;
        }

        cout << "Here are all commodity in our store:" << endl;
        commodityList.showCommoditiesDetail();
        cout << endl;
    }

    void askMode() {
        string input;

        cout << "Are you a general user or a manager?" << endl
             << "1. general user, 2. manager" << endl
             << "Or type 0 to close the store" << endl;

        int choice = InputHandler::getInput(2);

        userStatus = (choice == 2) ? UMode::MANAGER : UMode::USER;

        if (choice == 0) {
            storeStatus = SMode::CLOSE;
        } else if (userStatus == UMode::USER) {
            storeStatus = SMode::DECIDING;
        } else if (userStatus == UMode::MANAGER) {
            storeStatus = SMode::MANAGING;
        }
    }

    void decideService() {
        string input;

        cout << "Below are our service:" << endl
             << "1. Buy the commodity you want" << endl
             << "2. Check your shopping cart" << endl
             << "3. Check out" << endl
             << "Or type 0 to exit user mode" << endl
             << "You may choose what you need:" << endl;

        int choice = InputHandler::getInput(3);

        if (choice == 1) {
            storeStatus = SMode::SHOPPING;
        } else if (choice == 2) {
            storeStatus = SMode::CART_CHECKING;
        } else if (choice == 3) {
            storeStatus = SMode::CHECK_OUT;
        } else if (choice == 0) {
            storeStatus = SMode::OPENING;
        }
    }

    void chooseCommodity() {
        string input;
        showCommodity();
        cout << "Or input 0 to exit shopping" << endl;

        int choice = InputHandler::getInput(commodityList.size());

        // Push the commodity into shopping cart here
        if (choice == 0) {
            storeStatus = SMode::DECIDING;
        } else {
            // May be some bug here, test later
            cart.push(commodityList.get(choice - 1));
        }
    }

    void showCart() {
        if (cart.empty()) {
            cout << "Your shopping cart is empty" << endl;
            storeStatus = SMode::DECIDING;
            return;
        }

        int choice;
        do {
            cout << "Here is the current cart content:" << endl;
            cart.showCart();

            cout << "Do you want to delete the entry from the cart?" << endl
                 << "1. yes, 2. no" << endl;

            choice = InputHandler::getInput(2, true);

            if (choice == 1) {
                cout << "Which one do you want to delete(type the commodity index)?" << endl
                     << "Or type 0 to regret" << endl;
                int index = InputHandler::getInput(cart.size());
                // **
                if (index == 0) {
                    break;
                }
                cart.remove(index - 1);
            }
        } while (choice == 1);

        cout << "Do you want to checkout?" << endl
             << "1. yes, 2. No, I want to buy more" << endl;
        choice = InputHandler::getInput(2, true);
        if (choice == 1) {
            storeStatus = SMode::CHECK_OUT;
        } else {
            storeStatus = SMode::DECIDING;
        }
    }

    void checkOut() {
        if (cart.empty()) {
            cout << "Your shopping cart is empty, nothing can checkout" << endl;
        } else {
            cout << "Here is the current cart content:" << endl;
            cart.showCart();
            cout << "Are you sure you want to buy all of them?" << endl
                 << "1. Yes, sure, 2. No, I want to buy more" << endl;

            int choice = InputHandler::getInput(2, true);

            if (choice == 1) {
                int amount = cart.checkOut();
                cout << "Total Amount: " << amount << endl;
                cout << "Thank you for your coming!" << endl;
                cout << "------------------------------" << endl << endl;
            }
        }

        storeStatus = SMode::DECIDING;
    }

    void managerInterface() {
        cout << "Here are some manager services you can use:" << endl
             << "1. Add new commodity" << endl
             << "2. Delete commodity from the commodity list" << endl
             << "3. Show all existing commodity" << endl
             << "Or type 0 to exit manager mode" << endl
             << "Which action do you need?" << endl;

        int choice = InputHandler::getInput(3);

        if (choice == 1) {
            commodityInput();
        } else if (choice == 2) {
            deleteCommodity();
        } else if (choice == 3) {
            showCommodity();
        } else if (choice == 0) {
            storeStatus = SMode::OPENING;
        }
    }

    void userInterface() {
        if (storeStatus == SMode::OPENING) {
            askMode();
        } else if (storeStatus == SMode::DECIDING) {
            decideService();
        } else if (storeStatus == SMode::SHOPPING) {
            chooseCommodity();
        } else if (storeStatus == SMode::CART_CHECKING) {
            showCart();
        } else if (storeStatus == SMode::CHECK_OUT) {
            checkOut();
        } else if (storeStatus == SMode::MANAGING) {
            managerInterface();
        } else if (storeStatus == SMode::CLOSE) {
            return;
        }
    }

public:
    Store() {
        userStatus = UMode::USER;
        storeStatus = SMode::CLOSE;
    }

    void open() {
        commodityList.load();
        storeStatus = SMode::OPENING;
        while (storeStatus != SMode::CLOSE) {
            userInterface();
        }
        commodityList.save();
    }
};


int main() {
    Store csStore;
    csStore.open();
    return 0;
}
