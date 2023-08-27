#include <bits/stdc++.h>
using namespace std;
class client{
public:
    static int c_id_count;
    int cost_cnt;
    char c_type;
    virtual void check(){
        fstream fin;
        fin.open("client.csv",ios::in);
        int target_phn,phn,count=0;
        cout<<"Enter the phone number of the client to display details: ";
        cin>>target_phn;
        vector<string> row;
        string line, word;
        while(fin >> line){
            row.clear();
            stringstream s(line);
            while(getline(s,word,',')){
                row.push_back(word);
            }
            phn = atoi(row[2].c_str());
            if(target_phn == phn){
                count =1;
                cout<<"Client ID: "<< row[0]<<endl;
                cout<<"Name: "<<row[1]<<endl;
                cout<<"Phone No:"<< row[2]<<endl;
                cout<<"Address: "<< row[3]<<endl;
                cout<<"NID : "<<row[4]<<endl;
                break;
            }
        }
        if(count == 0){
            cout<<"Client is not found\n";
        }
    }
    virtual int update(){
        fstream  fout;
        fout.open("client.csv", ios::out | ios::app);
        int c_id;
        string c_name;
        string c_phone_no;
        string c_address;
        string c_nid;
        cout<<"Enter Client ID:";
        cin>>c_id;
        cout<<"\nEnter Client Name:";
        cin>>c_name;
        cout<<"\nEnter Client Phone Number:";
        cin>>c_phone_no;
        cout<<"\nEnter Client Address:";
        cin>>c_address;
        cout<<"\nEnter Client NID:";
        cin>>c_nid;
        fout << c_id<<","
                <<c_name<<","
                <<c_phone_no<<","
                <<c_address<<","
                <<c_nid<<",";
        fout.close();
    }
};

class client_hotelroom : virtual  public client{
public:
    void check(){
        ifstream inf("hotelroom.txt");
        if(!inf){
            cout<<endl<<"Unable to open the hotelroom file"<<endl;
        }
        int room_id;
        string room_type;
        string room_book;
        cout<<endl<<"Hotelrooms to book:"<<endl;
        while(!inf.eof()){
            inf>>room_id>>room_type>>room_book;
            if(room_book == "NULL"){
                cout<<room_id<<" "<<room_type;
            }
        }
        inf.close();
    }
    int update(){
        int target_room_id,c_id;
        cout<<"Please Enter the required room id:";
        cin>>target_room_id;
        cout<<"Please enter the client id:";
        cin>>c_id;
        string client_id;
        stringstream ss;
        ss<< c_id;
        client_id = ss.str();
        ifstream inf("hotelroom.txt");
        ofstream outf("hotelroom1.txt");
        if(!inf) cout<<endl<<"Unable to open hotelroom file"<<endl;
        int room_id;
        string room_type;
        string room_book;
        while(!inf.eof()){
            inf>>room_id>>room_type>>room_book;
            if(room_id == target_room_id){
                cost_cnt +=1000;
                cout<<room_id<<" "<<room_type<<endl;
                outf<<room_id<<" "<<room_type<<" "<<client_id<<endl;
            }
            else{
                outf<<room_id<<" "<<room_type<<" "<<room_book<<endl;
            }
        }
        outf.close();
        inf.close();
        remove("hotelroom.txt");
        rename("hotelroom1.txt","hotelroom.txt");
        return cost_cnt;
    }

    void checkout(){
        int c_id;
        cout<<"Please enter the client id:";
        cin>>c_id;
        string client_id;
        stringstream ss;
        ss << c_id;
        client_id = ss.str();
        ifstream inf("hotelroom.txt");
        ofstream outf("hotelroom1.txt");
        if(!inf){
            cout<<endl<<"Unable to open hotelroom file"<<endl;
        }
        int room_id;
        string room_type;
        string room_book;
        while(true){
            inf>>room_id>>room_type>>room_book;
            if(!inf.eof()){
                break;
            }
            if(room_book==client_id){
                cout<<room_id<<" "<<room_type<<endl;
                outf<<room_id<<" "<<room_type<<" "<<"NULL"<<endl;
            }
            else{
                outf<<room_id<<" "<<room_type<<" "<<room_book<<endl;
            }
        }
        outf.close();
        inf.close();
        remove("hotelroom.txt");
        rename("hotelroom1.txt","hotelroom.txt");
    }

    virtual void display_cost(){

    };
};
