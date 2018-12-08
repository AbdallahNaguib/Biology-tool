#include <iostream>
#include <fstream>
#include <cstring>
#include <DNA.h>
#include <RNA.h>
#include <Protein.h>

using namespace std;
/**
* the loading functions are here because it gets errors when putting them in the cpp files
*/
DNA* loadDNAFromFile(){
    /// we first load the number of DNAs saved in the file "DNA.txt" from "DNAcnt.txt"
    ifstream in2("DNAcnt.txt");
    int num_of_DNA;
    in2>>num_of_DNA;
    in2.close();
    ifstream in;
    in.open("DNA.txt");
    DNA* res=new DNA[num_of_DNA];
    for(int i=0 ; i<num_of_DNA ; i++){
        DNA dna;
        in>>dna.sz;
        for(int i=0 ; i<dna.sz ; i++){
            in>>dna.seq[i];
        }
        in>>dna.startChar>>dna.endChar;
        int typ;
        in>>typ;
        /// promoter, motif, tail, noncoding
        switch(typ){
        case 0:
            dna.type = promoter;
            break;
        case 1:
            dna.type = motif;
            break;
        case 2:
            dna.type = tail;
            break;
        case 3:
            dna.type = noncoding;
            break;
        }
        res[i] = dna;
    }
    in.close();
    return res;
}

RNA* loadRNAFromFile(){
    /// we first load the number of DNAs saved in the file "DNA.txt" from "DNAcnt.txt"
    ifstream in("RNAcnt.txt");
    int num_of_RNA;
    in>>num_of_RNA;
    in.close();
    in.open("RNA.txt");
    RNA* res=new RNA[num_of_RNA];
    for(int i=0 ; i<num_of_RNA ; i++){
        RNA rna;
        in>>rna.sz;
        for(int i=0 ; i<rna.sz ; i++){
            in>>rna.seq[i];
        }
        int typ;
        in>>typ;
        /// mRNA, tRNA, rRNA
        switch(typ){
        case 0:
            rna.type = mRNA;
            break;
        case 1:
            rna.type = tRNA;
            break;
        case 2:
            rna.type = rRNA;
            break;
        }
        res[i] = rna;
    }
    return res;
}

Protein* loadProFromFile(){
    /// we first load the number of DNAs saved in the file "DNA.txt" from "DNAcnt.txt"
    ifstream in("PROcnt.txt");
    int num_of_PRO;
    in>>num_of_PRO;
    in.close();
    in.open("PRO.txt");
    Protein* res=new Protein[num_of_PRO];
    for(int i=0 ; i<num_of_PRO ; i++){
        Protein pro;
        in>>pro.sz;
        for(int i=0 ; i<pro.sz ; i++){
            in>>pro.seq[i];
        }
        int typ;
        in>>typ;
        /// Hormon, Enzyme, TF, Cellular_Function
        switch(typ){
        case 0:
            pro.type = Hormon;
            break;
        case 1:
            pro.type = Enzyme;
            break;
        case 2:
            pro.type = TF;
            break;
        case 3:
            pro.type = Cellular_Function;
            break;
        }
        res[i]=pro;
    }
    return res;
}




void doOperationWithDNA(){
    /// first we read the number of DNAs sequences saved
    ifstream in("DNAcnt.txt");
    int num_of_DNA;
    in>>num_of_DNA;
    /**
    * we are checking if there is no DNA saved
    */
    if(num_of_DNA == 0){
        cout<<"No DNA sequences saved"<<endl;
        return;
    }
    DNA* arr = loadDNAFromFile();
    for(int i=0 ; i<num_of_DNA ; i++){
        cout<<i+1<<" - ";
        arr[i].Print();
    }
    cout<<"choose a sequence to work with : "<<endl;
    int choice;
    cin>>choice;
    if(choice <1 || choice>num_of_DNA){
        throw 2;
    }
    DNA currDNA=arr[choice - 1];/// cause the user will enter the index in 1-based and we need to convert it into 0-based
    cout<<"1- convert to RNA"<<endl;
    cout<<"2- convert to Protein"<<endl;
    cin>>choice;
    if(choice == 1){
        RNA rna=currDNA.ConvertToRNA();
        rna.Print();
        saveToFile(rna);
        cout<<"RNA sequence saved successfully"<<endl;
    }else if(choice == 2){
        RNA rna=currDNA.ConvertToRNA();
        Protein pro=rna.ConvertToProtein();
        pro.Print();
        saveToFile(pro);
        cout<<"Protein sequence saved successfully"<<endl;
    }else{
        throw 2;
    }
}

void doOperationWithRNA(){
    /// first we read the number of RNAs sequences saved
    ifstream in("RNAcnt.txt");
    int num_of_RNA;
    in>>num_of_RNA;
    if(num_of_RNA == 0){
        cout<<"No RNA sequences saved"<<endl;
        return;
    }
    cout<<endl;/// deleting this line would crash this function
    RNA* arr = loadRNAFromFile();
    for(int i=0 ; i<num_of_RNA ; i++){
        cout<<i+1<<" - ";
        arr[i].Print();
    }
    cout<<"choose a sequence to work with : "<<endl;
    int choice;
    cin>>choice;
    if(choice <1 || choice>num_of_RNA){
        throw 2;
    }
    RNA currRNA=arr[choice - 1];/// cause the user will enter the index in 1-based and we need to convert it into 0-based
    cout<<"1- convert to DNA"<<endl;
    cout<<"2- convert to Protein"<<endl;
    cin>>choice;
    if(choice == 1){
        DNA dna=currRNA.ConvertToDNA();
        dna.Print();
        saveToFile(dna);
        cout<<"DNA sequence saved successfully"<<endl;
    }else if(choice == 2){
        Protein pro=currRNA.ConvertToProtein();
        pro.Print();
        saveToFile(pro);
        cout<<"Protein sequence saved successfully"<<endl;
    }else{
        throw 2;
    }
}

void showProteins(){
    /// first we read the number of RNAs sequences saved
    ifstream in("PROcnt.txt");
    int num_of_PRO;
    in>>num_of_PRO;
    if(num_of_PRO == 0){
        cout<<"No Protein sequences saved"<<endl;
        return;
    }
    cout<<endl; /// deleting this line would crash this function
    Protein* arr = loadProFromFile();
    for(int i=0 ; i<num_of_PRO; i++){
        cout<<i<<" - ";
        arr[i].Print();
    }
}
/**
* this function does not work, fix it .
*/
void doAlign(){
    DNA dna;
    RNA rna;
    Protein pro;
    cout<<"1- DNA"<<endl;
    cout<<"2- RNA"<<endl;
    cout<<"3- Protein"<<endl;
    Sequence *seq1,*seq2;
    first:
    cout<<"Enter the type of the first sequence : ";
    int choice;
    cin>>choice;
    if(choice == 1){
        cin>>dna;
        seq1=&dna;
    }else if(choice == 2){
        cin>>rna;
        seq1=&rna;
    }else if(choice == 3){
        cin>>pro;
        seq1=&pro;
    }else{
        cout<<"wrong input"<<endl;
        goto first;
    }
    second:
    cout<<"Enter the type of the second sequence : ";
    cin>>choice;
    if(choice == 1){
        DNA dna;
        cin>>dna;
        seq2=&dna;
    }else if(choice == 2){
        RNA rna;
        cin>>rna;
        seq2=&rna;
    }else if(choice == 3){
        Protein pro;
        cin>>pro;
        seq2=&pro;
    }else{
        cout<<"wrong input"<<endl;
        goto second;
    }
    cout<<"the longest common subsequence is "<<Align(seq1 , seq2)<<endl;
}

int main(){
    while(true){
        cout<<"            welcome"<<endl;
        cout<<"1- adding a new DNA sequence "<<endl;
        cout<<"2- adding a new RNA sequence "<<endl;
        cout<<"3- adding a new Protein sequence "<<endl;
        cout<<"4- load previous DNA sequence "<<endl;
        cout<<"5- load previous RNA sequence "<<endl;
        cout<<"6- load previous Protein sequence "<<endl;
        cout<<"7- align two sequences"<<endl;
        cout<<"Enter your choice : ";
        int choice;
        cin>>choice;
        switch(choice){
        case 1:
            try{
            DNA dna;
            cin>>dna;
            saveToFile(dna);
            break;
            }catch(int x){
                  cout<<"wrong input"<<endl;
            }
        case 2:
            try{
                RNA rna;
                cin>>rna;
                saveToFile(rna);
                break;
              }catch(int x){
                  cout<<"wrong input"<<endl;
              }
        case 3:
            try{
                Protein pro;
                cin>>pro;
                saveToFile(pro);
                break;
            }catch(int x){
                  cout<<"wrong input"<<endl;
                  break;
            }
        case 4:
            while(true){
                try{
                    doOperationWithDNA();
                    break;/// it won't reach here unless everything is fine
                }catch(int x){
                    cout<<"you entered invalid data"<<endl;
                }
            }
            break;
        case 5:
            while(true){
                try{
                    doOperationWithRNA();
                    break;/// it won't reach here unless everything is fine
                }catch(...){
                    cout<<"you entered invalid data"<<endl;
                }
            }
            break;
        case 6:
            showProteins();
            break;
        case 7:
            doAlign();
        }
    }
    return 0;
}
