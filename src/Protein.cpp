#include "Protein.h"
#include <string>
using namespace std;

Protein::Protein(){
}
Protein::Protein(char* p,int len , Protein_Type type){
    /// those are the allowed characters in the protein sequence
    string Allowed="VGAEDLRPQHMIRSTKNLFWCSY";
    for(int i=0 ; i<len ; i++){
        if(Allowed.find(p[i]) == string::npos){/// this means that the char p[i] isn't in the allowed set of characters
            throw 1;
        }
    }
    this->type=type;
    sz=len;
    seq=new char[sz];
    for(int i=0 ; i<sz ; i++){
        seq[i]=p[i];
    }
}
Protein::~Protein(){
    delete seq;
}
void Protein::Print(){
    cout<<"the sequence is ";
    for(int i=0 ; i<this->sz ; i++){
        cout<<this->seq[i];
    }
    cout<<"    and it is of type : ";
    switch(type){
    case Hormon:
            cout<<"Hormon"<<endl;
            break;
    case Enzyme:
            cout<<"Enzyme"<<endl;
            break;
    case TF:
            cout<<"TF"<<endl;
            break;
    case Cellular_Function:
            cout<<"Cellular Function"<<endl;
            break;
    }
}

Protein::Protein(const Protein& rhs){
    /**
    * here in the copy constructor we copy every variable to our object but first we need to
    * initialize the pointers first before copying them
    */
    this->type=rhs.type;
    this->sz=rhs.sz;
    this->seq=new char[this->sz];
    for(int i=0 ; i <this->sz ; i++){
        this->seq[i] = rhs.seq[i];
    }
}
Protein& Protein::operator=(Protein rhs){
        /**
    * here in the copy constructor we copy every variable to our object but first we need to
    * initialize the pointers first before copying them
    */
    this->type=rhs.type;
    this->sz=rhs.sz;
    this->seq=new char[this->sz];
    for(int i=0 ; i <this->sz ; i++){
        this->seq[i] = rhs.seq[i];
    }
    return *this;
}


/// Hormon, Enzyme, TF, Cellular_Function
void saveToFile(const Protein& pro){
    /// first we update the DNA counter in its file
    ifstream in("PROcnt.txt");
    int num_of_PRO;
    in>>num_of_PRO;
    ofstream cnt("PROcnt.txt");
    cnt<<num_of_PRO+1<<endl;
    in.close();
    ofstream out("PRO.txt" , ios_base::app);
    out<<pro.sz<<" ";
    for(int i=0 ; i<pro.sz ; i++){
        out<<pro.seq[i];
    }
    out<<" "<<pro.type<<endl;
    out.close();
}

istream& operator>> (istream& in, Protein& pro){
    reading_seq:
    cout<<"Enter the sequence : ";
    string sequenc;
    in>>sequenc;
    pro.sz=sequenc.size();
    pro.seq=new char[pro.sz];
    string Allowed="VGAEDLRPQHMIRSTKNLFWCSY";
    for(int i=0 ; i<pro.sz ; i++){
        pro.seq[i] = sequenc[i];
        if(Allowed.find(pro.seq[i]) == string::npos){
            cout<<"Wrong input"<<endl;
            goto reading_seq;
        }
    }
    /// Hormon, Enzyme, TF, Cellular_Function
    reading_type:
    cout<<"Enter the type "<<endl;
    cout<<"1- Hormon"<<endl;
    cout<<"2- Enzyme"<<endl;
    cout<<"3- TF"<<endl;
    cout<<"4- Cellular function"<<endl;
    int choice;
    in>>choice;
    switch(choice){
    case 1:
        pro.type=Hormon;
        break;
    case 2:
        pro.type=Enzyme;
        break;
    case 3:
        pro.type=TF;
        break;
    case 4:
        pro.type=Cellular_Function;
    default:
        cout<<"Wrong input"<<endl;
        goto reading_type;
    }
    return in;
}
