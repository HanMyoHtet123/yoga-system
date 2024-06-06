#include<iostream>
#include<ctype.h>
#include<iomanip>

using namespace std;
int PLAN = 0;
int CUSTOMER  = 0;
int POSITION = 0;

class TrainingPlan{
    string tpName;
    int sessionPerWeek;
    float feesPerWeek;
    public:
        TrainingPlan(){
            tpName = "";
            sessionPerWeek = 0;
            feesPerWeek = 0;
        }
        TrainingPlan(string n, int s, float FPW){
            tpName = n;
            sessionPerWeek = s;
            feesPerWeek = FPW;
            PLAN++;
        }
        
        void setPlan(TrainingPlan plans[]){
            cout<<"enter TrainingPlan name : ";
            cin.get();
            getline(cin, tpName);
            cout<<"enter Sesion_per_week : ";
            cin>>sessionPerWeek;
            feeLabel:
            cout<<"enter Fees_per_week : ";
            cin>>feesPerWeek;
            cout<<"Successfully created a training plan("<<tpName<<")!\n";
            cin.get();
            PLAN++;
        }
        void updatePlan(){
            cout<<"TrainingPlan name("<<tpName<<") : \n";
            cout<<"enter sessions_per_week ("<<sessionPerWeek<<") : ";
            cin>>sessionPerWeek;
            feeLabel:
            cout<<"enter Fees_per_week ("<<feesPerWeek<<") : ";
            cin>>feesPerWeek;
            cout<<"Successfully updated the training plan("<<tpName<<")!\n";
            cin.get();
        } 
        string getPlanName() {return tpName;}
        float getFeesPerWeek() {return feesPerWeek;}
        int getSessionsPerWeek() {return sessionPerWeek;}
        void displayPlan(){
            cout<<setw(20)<<tpName
                <<setw(20)<<sessionPerWeek
                <<setw(15)<<feesPerWeek;
        }
};

class Customer{
    string cName;
    TrainingPlan trainingPlan;
    float currentWeight;
    int privateHours[4];
    bool privateHourOnOff[4];
    int learntPosesCount;
    float cost;
    public:
        Customer(){
            cName = "";
            currentWeight = 0;
            cost = 0;
            learntPosesCount = 0;
            for(int i=0; i<4; i++){
                privateHours[i] = 0;
                privateHourOnOff[i] = 0;
            }
        }
        Customer(string n, TrainingPlan tp, float w, int h[4], bool OnOff[4]){
            cName = n;
            trainingPlan = tp;
            currentWeight = w;
            cost = 0;
            for(int i=0; i<4; i++){
                privateHours[i] = h[i];
                privateHourOnOff[i] = OnOff[i];
            }
            CUSTOMER++;
        }
        void setCustomer(TrainingPlan plans[]){
            int planIndex = 0;
            cout<<"Enter customer name : ";
            cin.get();
            getline(cin, cName);

            trainingPlanLabel:
            cout<<"enter TrainingPlan - Available plans : \n";
            for(int i=0; i<PLAN; i++){
                cout<<"TrainingPlan : "<<i+1<<" "<<plans[i].getPlanName();
                if(i+1!=PLAN) cout<<" ,\n";
            }
            cout<<"\nChoose the index : ";
            if(planIndex < 0 || planIndex > PLAN) goto trainingPlanLabel;
            cin>>planIndex;
            trainingPlan = plans[planIndex-1];

            cout<<"Enter current weight : ";
            cin>>currentWeight;

            for(int i=0; i<4; i++){
                char o = '0';
                privateHourLabel:
                cout<<"Enter"<<i+1<<" th/st week private hours : \n";
                cin>>privateHours[i];
                if(privateHours[i] < 0 || privateHours[i] > 5) {
                    cout<<"It exceeded 5 or less than 0\n";
                    goto privateHourLabel;
                }
                
                onlineOfflineLabel:
                cout<<"Online/Offline(0/1) : ";
                cin>>o;
                if(o!='0'||o!='1') goto onlineOfflineLabel;
                if(o=='0') privateHourOnOff[i] = 0;
                else privateHourOnOff[i] = 1;
            }
            cout<<"Enter learnt poses counts : ";
            cin>>learntPosesCount;
            CUSTOMER++;
        }
        string updateCustomer(TrainingPlan plans[]){
            int planIndex = 0;
            cout<<"Customer name("<<cName<<") : \n";

            trainingPlanLabel:
            cout<<"Enter training plan - Available plans : \n";
            for(int i=0; i<PLAN; i++){
                cout<<"Plan : "<<i+1<<" "<<plans[i].getPlanName();
                if(i+1!=PLAN) cout<<" ,\n";
            }
            cout<<"\nChoose the index : ";
            if(planIndex < 0 || planIndex > PLAN) goto trainingPlanLabel;
            cin>>planIndex;
            trainingPlan = plans[planIndex-1];

            cout<<"Enter current weight(kg) : ";
            cin>>currentWeight;

            for(int i=0; i<4; i++){
                char o = '0';
                cout<<"Enter"<<i+1<<" th/st week private hours : \n";
                cin>>privateHours[i];
                onlineOfflineLabel:
                cout<<"Online/Offline(0/1) : ";
                cin>>o;
                if(o!='0'||o!='1') goto onlineOfflineLabel;
                if(o=='0') privateHourOnOff[i] = 0;
                else privateHourOnOff[i] = 1;
            }
            return trainingPlan.getPlanName();
        }
        float getFinalCost(){
            cost = 0;
            cost += trainingPlan.getFeesPerWeek()*4;
            
            for(int i=0; i<4; i++){
                if(privateHourOnOff[i]) cost += 15000*privateHours[i];
                else cost += 17000*privateHours[i];
            }
            return cost - (cost*learntPosesCount)/100;
        }
        float getCost() {
            cost = 0;
            cost += trainingPlan.getFeesPerWeek()*4;
            
            for(int i=0; i<4; i++){
                if(privateHourOnOff[i]) cost += 15000*privateHours[i];
                else cost += 17000*privateHours[i];
            }
            return cost;
        }
        void displayCustomer(){
            cout<<setw(20)<<cName
                <<setw(20)<<trainingPlan.getPlanName()
                <<setw(10)<<learntPosesCount
                <<setw(20)<<getFinalCost();
        }
        void displayCustomerDetails(){
            int online = 0, offline = 0;
            for(int i=0; i<4; i++){
                if(privateHourOnOff[i]) online++;
                else offline++;
            }
            cout<<setw(30)<<"Customer name : "<<setw(20)<<cName<<endl
                <<setw(30)<<"Weight : "<<setw(20)<<currentWeight<<endl
                <<setw(30)<<"Training plan : "<<setw(20)<<trainingPlan.getPlanName()<<endl
                <<setw(30)<<"Learnt poses counts : "<<setw(20)<<learntPosesCount<<endl
                <<setw(30)<<"Sessions per week : "<<setw(20)<<trainingPlan.getSessionsPerWeek()
                <<setw(20)<<trainingPlan.getFeesPerWeek()*4<<endl
                <<setw(30)<<"Private (Online-15000) : "<<setw(20)<<online<<setw(20)<<15000*online<<endl
                <<setw(30)<<"Private (Offline-17000) : "<<setw(20)<<offline<<setw(20)<<17000*offline<<endl
                <<setw(30)<<"DISCOUNT (%) : "<<setw(20)<<learntPosesCount<<setw(20)<<getCost()*learntPosesCount/100<<endl
                <<setw(30)<<"Total Cost : "<<setw(20)<<""<<setw(20)<<getFinalCost()<<endl;
            cin.get();
        }
};
class Position{
    string name;
    int poseCount;
    public:
    public:
        string poseType[10];
        string poseName[10];
        Position(){
            name = "";
            poseCount = 0;
        }
        Position(string name, string type[10], string names[10]){
            name = name;
            for(int i=0; i<10; i++){
                poseType[i] = type[i];
                poseName[i] = names[i];
                poseCount++;
            }
            POSITION++;
        }
        void addPosition(){
            cout<<"Position name : "<<name<<endl;
            cout<<"Positions : \n";
            for(int i=0; i<poseCount; i++) {
                cout<<poseName[i];
                if(i+1 != poseCount) cout<<" , ";
                else cout<<endl;
            }
            if(poseCount == 10) {
                cout<<"10 poses already added\n";
                cin.get();
                return;
            }
            char more = 'y';
            while(true){
                if(poseCount==10) break;

                cout<<"Enter position name("<<poseCount+1<<") : ";
                cin.get();
                getline(cin,poseName[poseCount]);
                cout<<"Enter position type("<<poseCount+1<<") : ";
                getline(cin,poseType[poseCount]);
                cout<<"Successfully added("<<poseName[poseCount]<<")\n";
                poseCount++;

                moreLabel:
                cout<<"Add more?(y/n) : ";
                cin>>more;
                if(more=='n') break;
                if(more!='n'||more!='y') goto moreLabel;
            }
        }
        void createPosition(){
            cout<<"Enter position name : ";
            cin.get();
            getline(cin,name);
            addPosition();
        }
        void displayPosition(){
            cout<<setw(20)<<name<<endl;
            for(int i=0; i<poseCount; i++){
                cout<<setw(25)<<""
                    <<setw(20)<<poseType[i]
                    <<setw(20)<<poseName[i]
                    <<endl;
            }
        }
};
void displayTrainingPlans(TrainingPlan plans[]);
void displayYogaPositions(Position poses[]);
void displayCustomers(Customer customers[]);

int main(){
    int menuCode;
    
    Position poses[5];
    string basicPoseType[10] = {"Standing Pose","Standing Pose","Standing Pose","Standing Pose","Balancing Pose","Balancing Pose","Balancing Pose","Balancing Pose","Seat Pose","Backend Pose"};
    string basicPoseNames[10] ={"Archer Pose","Dolphin Pose","Frog Pose","Fallen Triangle","Big Toe Pose","Lion Pose","Airplane Pose","Side Lunge","Side Reclining","Bird Dog Pose"};
    Position pose1("BASIC",basicPoseType,basicPoseNames);
    
    string imPoseType[10] = {"Standing Pose","Standing Pose","Standing Pose","Standing Pose","Balancing Pose","Balancing Pose","Balancing Pose","Balancing Pose","Seat Pose","Backend Pose"};
    string imPoseNames[10] ={"Downward Facing Pose","Mountain Pose","Warrior Pose","Traingle Triangle","Low Lunge","Tree Pose","Plank Pose","Bridge Lunge","Staff Pose","Cobbler's Pose"};
    Position pose2("INTERMEDIATE",imPoseType,imPoseNames);
    
    poses[0] = pose1;
    poses[1] = pose2;
    
    TrainingPlan plans[7];
    TrainingPlan basic("BASIC",3,25000);
    TrainingPlan inter("INTERMEDIATE",3,35000);
    TrainingPlan advan("ADVANCED",2,50000);
    plans[0] = basic;
    plans[1] = inter;
    plans[2] = advan;

    Customer customers[50];
    int c1Private[4] = {1,1,3,2};
    bool c1OnOff[4] = {true,false,true,true};
    int c2Private[4] = {1,1,3,2};
    bool c2OnOff[4] = {true,true,true,false};
    int c3Private[4] = {1,1,3,2};
    bool c3OnOff[4] = {true,true,false,true};
    int c4Private[4] = {1,1,3,2};
    bool c4OnOff[4] = {false,false,true,true};
    int c5Private[4] = {1,1,3,2};
    bool c5OnOff[4] = {true,false,false,true};
    
    Customer c1("Min Thiha Aung",plans[0],55,c1Private,c1OnOff);
    Customer c2("Nyi Nyi Aung",plans[0],55,c2Private,c2OnOff);
    Customer c3("Yunn Myat Noe Thu",plans[0],55,c3Private,c3OnOff);
    Customer c4("Myo Min Thu",plans[0],55,c4Private,c4OnOff);
    Customer c5("Mg Thiha",plans[0],55,c5Private,c5OnOff);
    customers[0] = c1;
    customers[1] = c2;
    customers[2] = c3;
    customers[3] = c4;
    customers[4] = c5;

    menuLabel:
    cout<<"\t\t\t\t***Welcome from Amazing Sport Yoga System***"<<endl<<"                          ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<"\n\t\t\t\t***YIU YOUTH International University***\n";
    cout<<"\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    cout<<"\n\t\t\t\t\t\t*29Batch*\n\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout<<"\n\t\t\t\t\t    !*Han Myo Htet*!";
	cin.get();
	cout<<endl;
    cout<<"Please choose what admin want to fill in...(eg.1 or 2 or 0)"<<endl
        <<setw(20)<<endl<<"1. Training plan.\n\n"<<endl
        <<setw(16)<<"2. Customers.\n\n"<<endl
        <<setw(18)<<"0. Quit program.\n";
    cin>>menuCode;
    if(menuCode==1) {
        trainingPlanScreenLabel:
        int trainingMenuCode = 0;
        cout<<"1. Add a training plan.\n2. Show all training plans.\n3. Update a training plan.\n4. Add a yoga plan.\n5. Display yoga plans.\n6. Add yoga poses.\n0. Return to main screen.\n";
        cin>>trainingMenuCode;
      
        if(trainingMenuCode < 0 || trainingMenuCode > 6) goto trainingPlanScreenLabel;
        if(trainingMenuCode == 0) goto menuLabel;
        else if(trainingMenuCode == 1) plans[PLAN].setPlan(plans);
        else if(trainingMenuCode == 2) displayTrainingPlans(plans);
        else if(trainingMenuCode == 3) {
            int index = 0;
            displayTrainingPlans(plans);
            cout<<"Enter number to update : ";
            cin>>index;
            plans[index-1].updatePlan();
        }
        else if(trainingMenuCode == 4) poses[POSITION].createPosition();
        else if(trainingMenuCode == 5) displayYogaPositions(poses);
        else if(trainingMenuCode == 6) {
            int index = 0;
            displayYogaPositions(poses);
            cout<<"\nEnter yoga plan index to add : ";
            cin>>index;
            poses[index-1].addPosition();
        }
        goto trainingPlanScreenLabel;
    } 
    else if(menuCode==2){
        customerScreenLabel:
        int customerScreenCode = 0;
        cout<<"1. Register a new customer.\n2. View all customers.\n3. Update customer info.\n4. Calculate costs for the customer.\n0. Return to main screen. \n";
        cin>>customerScreenCode;
        if(customerScreenCode < 0 || customerScreenCode > 4) goto customerScreenLabel;
      
        if(customerScreenCode == 0) goto menuLabel;
        else if(customerScreenCode == 1) {
            customers[CUSTOMER].setCustomer(plans);
        }
        else if(customerScreenCode == 2) displayCustomers(customers);
        else if(customerScreenCode == 3) {
            int index = 0;
            displayCustomers(customers);
            cout<<"Enter number to update : ";
            cin>>index;
            customers[index-1].updateCustomer(plans);
        }
        else if(customerScreenCode == 4) {
            int index = 0;
            displayCustomers(customers);
            cout<<"Enter number to calculate costs : ";
            cin>>index;
            customers[index-1].displayCustomerDetails();
        }
        goto customerScreenLabel;
    }
    else if(menuCode==0) return 0;
    else goto menuLabel;
}

void displayTrainingPlans(TrainingPlan plans[]){
    cout<<setw(5)<<"No"
        <<setw(20)<<"Plan name"
        <<setw(20)<<"Session per week"
        <<setw(15)<<"Fees per week"
        <<endl;
    for(int i=0; i<PLAN; i++) {
        cout<<setw(5)<<i+1;
        plans[i].displayPlan();
        cout<<endl;
    }
}

void displayYogaPositions(Position poses[]){
    cout<<setw(5)<<"No"
        <<setw(20)<<"Position names"
        <<setw(20)<<"Pose type"
        <<setw(20)<<"Pose name"
        <<endl;
    for(int i=0; i<POSITION; i++) {
        cout<<setw(5)<<i+1;
        poses[i].displayPosition();
        cout<<endl;
    }
}

void displayCustomers(Customer customers[]){
    cout<<setw(5)<<"No"
        <<setw(20)<<"Customer name"
        <<setw(20)<<"Training plan"
        <<setw(10)<<"Learnt poses count"
        <<setw(20)<<"Cost(current month"
        <<endl;
    for(int i=0; i<CUSTOMER; i++) {
        cout<<setw(5)<<i+1;
        customers[i].displayCustomer();
        cout<<endl;
    }
}
