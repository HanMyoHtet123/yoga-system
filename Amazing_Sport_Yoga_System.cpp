#include<iostream>
#include<ctype.h>
#include<iomanip>
using namespace std;
int TRAININGPLAN = 0;
int CUSTOMER_COUNT  = 0;
int YOGAPOSITION = 0;

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
            TRAININGPLAN++;
        }
        
        void setPlan(TrainingPlan plans[]){
            cout << "\033[2J\033[1;1H";
            cout<<"!Add a training plan!"<<endl;
            cout<<"\nenter TrainingPlan name : ";
            cin.get();
            getline(cin, tpName);
            cout<<"enter Sesion_per_week : ";
            cin>>sessionPerWeek;
            feeLabel:
            cout<<"enter Fees_per_week : ";
            cin>>feesPerWeek;
            cout<<"Successfully created a training plan("<<tpName<<")!\n";
            cin.get();
            TRAININGPLAN++;
        }
        void updatePlan(){
            cout<<"Training plan name("<<tpName<<") \n";
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
    string Customer_Name;
    TrainingPlan trainingPlan;
    float currentWeight;
    int privateHours[4];
    bool privateHourOnOff[4];
    int learntPosesCount;
    string learntPoses[10];
    float cost;
    public:
        Customer(){
            Customer_Name = "";
            currentWeight = 0;
            cost = 0;
            learntPosesCount = 0;
            for(int i=0; i<4; i++){
                privateHours[i] = 0;
                privateHourOnOff[i] = 0;
            }
        }
        Customer(string n, TrainingPlan tp, float w, int h[4], bool OnOff[4]){
            Customer_Name = n;
            trainingPlan = tp;
            currentWeight = w;
            cost = 0;
            for(int i=0; i<4; i++){
                privateHours[i] = h[i];
                privateHourOnOff[i] = OnOff[i];
            }
            CUSTOMER_COUNT++;
        }
        string setCustomer(TrainingPlan plans[]){
            cout << "\033[2J\033[1;1H";
            int planIndex = 0;
            cout<<"!Please Register!"<<endl;
            cout<<"\nEnter customer name : ";
            cin.get();
            getline(cin, Customer_Name);

            trainingPlanLabel:
            cout<<"enter TrainingPlan - Available plans : \n";
            for(int i=0; i<TRAININGPLAN; i++){
                cout<<"TrainingPlan : "<<i+1<<" "<<plans[i].getPlanName();
                if(i+1!=TRAININGPLAN) cout<<" ,\n";
            }
            cout<<"\nChoose the index : ";
            if(planIndex < 0 || planIndex > TRAININGPLAN) goto trainingPlanLabel;
            cin>>planIndex;
            trainingPlan = plans[planIndex-1];

            cout<<"Enter current weight(kg) : ";
            cin>>currentWeight;

            for(int i=0; i<4; i++){
                char o = '0';
                privateHourLabel:
                cout<<"Enter "<<i+1<<" th/st week private hours : ";
                cin>>privateHours[i];
                if(privateHours[i] < 0 || privateHours[i] > 5) {
                    cout<<"It exceeded 5 or less than 0\n";
                    goto privateHourLabel;
                }
                
                onlineOfflineLabel:
                cout<<"Online/Offline(0/1) : ";
                cin>>o;
                if(o=='1') privateHourOnOff[i] = 0;
                else privateHourOnOff[i] = 1;
            }
            learntPosesCount = 0;
            CUSTOMER_COUNT++;
            return trainingPlan.getPlanName();
        }
        string updateCustomer(TrainingPlan plans[]){
            int planIndex = 0;
            cout<<"Customer name("<<Customer_Name<<") : \n";

            trainingPlanLabel:
            cout<<"Enter training plan - Available plans : \n";
            for(int i=0; i<TRAININGPLAN; i++){
                cout<<"Plan : "<<i+1<<" "<<plans[i].getPlanName();
                if(i+1!=TRAININGPLAN) cout<<" ,\n";
            }
            cout<<"\nChoose the index : ";
            if(planIndex < 0 || planIndex > TRAININGPLAN) goto trainingPlanLabel;
            cin>>planIndex;
            trainingPlan = plans[planIndex-1];

            cout<<"Enter current weight(kg) : ";
            cin>>currentWeight;

            for(int i=0; i<4; i++){
                char o = '0';
                cout<<"Enter "<<i+1<<" th/st week private hours : ";
                cin>>privateHours[i];
                onlineOfflineLabel:
                cout<<"Online/Offline(0/1) : ";
                cin>>o;
                if(o=='1') privateHourOnOff[i] = 0;
                else privateHourOnOff[i] = 1;
            }
            learntPosesCount = 0;
            return trainingPlan.getPlanName();
        }

        void addLearntPoses(string poses[]){
            char learnt = 'y';
            int ind = 0;
            int learntInd = 0;
            cout<<"Already learnt poses? (y/n) : ";
            cin>>learnt;
            if(learnt=='y') {
                for(int i=0; i<10; i++){
                    cout<<"("<<i+1<<")"<<poses[i];
                    if(i+1 != 10) cout<<" , ";
                }
                while(true){
                    char more = 'y';
                    cout<<"\nEnter pose index : ";
                    cin>>ind;
                    cout<<"Got more?(y/n) : ";
                    cin>>more;
                    learntPosesCount++;
                    learntPoses[learntInd] = poses[ind-1];
                    learntInd++;
                    if(more!='y') break;
                }
            }
            cout<<endl;
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
            cout<<setw(20)<<Customer_Name
                <<setw(20)<<trainingPlan.getPlanName()
                <<setw(10)<<learntPosesCount
                <<setw(20)<<getFinalCost();
        }
        void displayCustomerDetails(){
            int online = 0, offline = 0;
            for(int i=0; i<4; i++){
                if(privateHourOnOff[i]) online += privateHours[i];
                else offline += privateHours[i];
            }
            cout<<setw(30)<<"Customer name : "<<setw(20)<<Customer_Name<<endl
                <<setw(30)<<"Weight : "<<setw(20)<<currentWeight<<endl
                <<setw(30)<<"Training plan : "<<setw(20)<<trainingPlan.getPlanName()<<endl
                <<setw(30)<<"Learnt poses counts : "<<setw(20)<<learntPosesCount<<endl
                <<setw(30)<<"Learnt poses : ";
            for(int i=0; i<learntPosesCount; i++) cout<<learntPoses[i]<<", ";
            cout<<endl<<setw(30)<<"Sessions per week : "<<setw(20)<<trainingPlan.getSessionsPerWeek()
                <<setw(20)<<trainingPlan.getFeesPerWeek()*4<<endl
                <<setw(30)<<"Private (Online-15000) : "<<setw(20)<<online<<setw(20)<<15000*online<<endl
                <<setw(30)<<"Private (Offline-17000) : "<<setw(20)<<offline<<setw(20)<<17000*offline<<endl
                <<setw(30)<<"DISCOUNT (%) : "<<setw(20)<<learntPosesCount<<setw(20)<<getCost()*learntPosesCount/100<<endl
                <<setw(30)<<"Total Cost : "<<setw(20)<<""<<setw(20)<<getFinalCost()<<endl;
            cin.get();
            cin.get();
        }
};
void merge(Customer arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Customer* L = new Customer[n1];
    Customer* R = new Customer[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].getFinalCost() <= R[j].getFinalCost()) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}
void mergeSort(Customer arr[], int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}
class Position{
    string name;
    int poseCount;
    public:
        string poseType[10];
        string poseName[10];
        Position(){
            name = "";
            poseCount = 0;
        }
        Position(string n, string type[10], string names[10], int pc){
            name = n;
            poseCount = pc;
            for(int i=0; i<10; i++){
                poseType[i] = type[i];
                poseName[i] = names[i];
            }
            YOGAPOSITION++;
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
                cin.get();
                return;
            }
            char more = 'y';
            while(true){
                cin.get();
                if(poseCount==10) break;

                cout<<"Enter position name("<<poseCount+1<<") : ";
                getline(cin,poseName[poseCount]);
                cout<<"Enter position type("<<poseCount+1<<") : ";
                getline(cin,poseType[poseCount]);
                cout<<"Successfully added("<<poseName[poseCount]<<")\n";
                poseCount++;

                cout<<"Add more?(y/n) : ";
                cin>>more;
                if(more=='n') break;
            }
        }
        void createPosition(){
            cout << "\033[2J\033[1;1H";
            cout<<"!Add a yoga plan!";
            cout<<"\n\nEnter position name : ";
            cin.get();
            YOGAPOSITION++;
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
    Position pose1("BASIC",basicPoseType,basicPoseNames,10);
    
    string imPoseType[10] = {"Standing Pose","Standing Pose","Standing Pose","Standing Pose","Balancing Pose","Balancing Pose","Balancing Pose","Balancing Pose","Seat Pose","Backend Pose"};
    string imPoseNames[10] ={"Downward Facing Pose","Mountain Pose","Warrior Pose","Traingle Triangle","Low Lunge","Tree Pose","Plank Pose","Bridge Lunge","Staff Pose","Cobbler's Pose"};
    Position pose2("INTERMEDIATE",imPoseType,imPoseNames,10);
    
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
    cout << "\033[2J\033[1;1H";
    cout<<"\n\n\n";
    cout<<"\t\t\t\t***Welcome from Amazing Sport Yoga System***"<<endl<<"                          ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<"\n\t\t\t\t***YIU YOUTH International University***\n";
    cout<<"\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    cout<<"\n\t\t\t\t\t\t*29Batch*\n\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout<<"\n\t\t\t\t\t    !*Developed by Han Myo Htet*!";
	cin.get();
    cout << "\033[2J\033[1;1H";
	cout<<endl;
    cout<<"Please choose what admin want to fill in...(eg.1 or 2 or 0)"<<endl
        <<setw(20)<<endl<<"1. Training plan.\n\n"<<endl
        <<setw(16)<<"2. Customers.\n\n"<<endl
        <<setw(18)<<"0. Quit program.\n";
    cin>>menuCode;
    if(menuCode==1) {
        trainingPlanScreenLabel: 
         cout << "\033[2J\033[1;1H";
        int trainingMenuCode = 0;
        cout<<"1. Add a training plan.\n\n2. Show all training plans.\n\n3. Update a training plan.\n\n4. Add a yoga plan.\n\n5. Display yoga plans.\n\n6. Add yoga poses.\n\n0. Return to main screen.\n";
        cin>>trainingMenuCode;
      
        if(trainingMenuCode < 0 || trainingMenuCode > 6) goto trainingPlanScreenLabel;
        if(trainingMenuCode == 0) goto menuLabel;
        else if(trainingMenuCode == 1) plans[TRAININGPLAN].setPlan(plans);
        else if(trainingMenuCode == 2) {
            displayTrainingPlans(plans);
            cin.get();
            cin.get();
        }
        else if(trainingMenuCode == 3) {
            int index = 0;
            displayTrainingPlans(plans);
            cout<<"Enter number to update : ";
            cin>>index;
            plans[index-1].updatePlan();
        }
        else if(trainingMenuCode == 4) poses[YOGAPOSITION].createPosition();
        else if(trainingMenuCode == 5) {
            displayYogaPositions(poses);
            cin.get();
            cin.get();
        }
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
        cout << "\033[2J\033[1;1H";
        int customerScreenCode = 0;
        cout<<"1. Register a new customer.\n\n2. View all customers.\n\n3. Update customer info.\n\n4. Calculate costs for the customer.\n\n0. Return to main screen. \n";
        cin>>customerScreenCode;
        if(customerScreenCode < 0 || customerScreenCode > 4) goto customerScreenLabel;
      
        if(customerScreenCode == 0) goto menuLabel;
        else if(customerScreenCode == 1) {
            string planName = customers[CUSTOMER_COUNT].setCustomer(plans);
            if(planName == "INTERMEDIATE") customers[CUSTOMER_COUNT-1].addLearntPoses(poses[0].poseName);
            else if(planName == "ADVANCED") customers[CUSTOMER_COUNT-1].addLearntPoses(poses[1].poseName);
            cout<<"\n\n";
            customers[CUSTOMER_COUNT-1].displayCustomerDetails();
        }
        else if(customerScreenCode == 2) {
            displayCustomers(customers);
            cin.get();
            cin.get();
        }
        else if(customerScreenCode == 3) {
            int index = 0;
            displayCustomers(customers);
            cout<<"Enter number to update : ";
            cin>>index;
            string planName = customers[index-1].updateCustomer(plans);
            if(planName == "INTERMEDIATE") customers[index-1].addLearntPoses(poses[0].poseName);
            else if(planName == "ADVANCED") customers[index-1].addLearntPoses(poses[1].poseName);
            cout<<"\n\n";
            customers[index-1].displayCustomerDetails();
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
    else if(menuCode==0){
        cout<<"#Bye Bye....love you All#\n!Thank you for your time to run my system!";
        return 0;
    } 
    else goto menuLabel;
}

void displayTrainingPlans(TrainingPlan plans[]){
    cout << "\033[2J\033[1;1H";
    cout<<"Show All Training Plans\n\n";
    cout<<"*******************************************************************"<<endl;
    cout<<setw(5)<<"No"
        <<setw(20)<<"Plan name"
        <<setw(20)<<"Session per week"
        <<setw(15)<<"Fees per week"
        <<endl;
    cout<<"*******************************************************************"<<endl;
    for(int i=0; i<TRAININGPLAN; i++) {
        cout<<setw(5)<<i+1;
        plans[i].displayPlan();
        cout<<endl;
    }
    cout<<"*******************************************************************"<<endl;
}

void displayYogaPositions(Position poses[]){
    cout << "\033[2J\033[1;1H";
    cout<<"!Display Yoga Plans!\n\n";
    cout<<"*******************************************************************"<<endl;
    cout<<setw(5)<<"No"
        <<setw(20)<<"Position names"
        <<setw(20)<<"Pose type"
        <<setw(20)<<"Pose name"
        <<endl;
    cout<<"*******************************************************************"<<endl;
    for(int i=0; i<YOGAPOSITION; i++) {
        cout<<setw(5)<<i+1;
        poses[i].displayPosition();
        cout<<endl;
       if(i+1 != YOGAPOSITION) cout<<"*******************************************************************"<<endl;    
    }
    cout<<"*******************************************************************"<<endl;
}

void displayCustomers(Customer customers[]){
    cout << "\033[2J\033[1;1H";
    cout<<"View All Customers\n\n";
    cout<<"**************************************************************************************"<<endl;
    cout<<setw(5)<<"No"
        <<setw(20)<<"CustomerName"
        <<setw(20)<<"TrainingPlan"
        <<setw(20)<<"Learnt poses count"
        <<setw(20)<<"Cost(current month)"
        <<endl;
    cout<<"**************************************************************************************"<<endl;
    for(int i=0; i<CUSTOMER_COUNT; i++) {
        cout<<setw(5)<<i+1;
        customers[i].displayCustomer();
        cout<<endl;
    }
    cout<<"**************************************************************************************"<<endl;
}
