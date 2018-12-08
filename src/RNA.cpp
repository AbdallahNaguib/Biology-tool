#include "RNA.h"
#include <Protein.h>

RNA::RNA(){
}
RNA::RNA(char* seq, RNA_Type atype, int len){
    /**
    * first we make sure that the size of the sequence is divisible by 3 to be able to convert
    * it into protein and that the characters are accepted
    */
    if(len%3 != 0){
        throw 0;
    }
    /**
    * we start by initializing the seq pointer and then we make every char in the seq parameter
    * giving by the user equals our seq
    */
    this->seq=new char[len];
    for(int i=0 ; i<len ; i++){
        this->seq[i] = seq[i];
        if(seq[i] != 'A' && seq[i] != 'U' && seq[i] != 'G' && seq[i] != 'C'){
            throw 1;
        }
    }
    this->type=atype;
    this->sz=len;
}
RNA::RNA(const RNA& rhs){
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
int RNA::getSize(){return sz;}
RNA& RNA::operator=(RNA rhs){
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
RNA::~RNA(){
    delete seq;
}
void RNA::Print(){
    cout<<"the sequence is ";

    for(int i=0 ; i<this->sz ; i++){
        cout<<this->seq[i];
    }
    cout<<"    and it is of type : ";
    switch(type){
    case mRNA:
        cout<<"mRNA"<<endl;
        break;
    case tRNA:
        cout<<"tRNA"<<endl;
        break;
    case rRNA:
        cout<<"rRNA"<<endl;
        break;
    }
}
/**
* this function returns the protein specified by this RNA
*/
Protein RNA::ConvertToProtein(){
    char* ProSeq=new char[sz/3];
    /// ind is the index of the amino acid for its iteration
    int ind=0;
    CodonsTable CT;
    for(int i=0 ; i<sz ; i+=3){
        for(int j = 0 ; j<64 ; j++){
            if(CT.codons[j].value[0] == seq[i] && CT.codons[j].value[1] == seq[i+1]
               && CT.codons[j].value[2] == seq[i+2]){
                ProSeq[ind]=CT.codons[j].AminoAcid;
                break;
               }
        }
        ind++;
    }
    Protein pr(ProSeq , sz/3 , Cellular_Function);
    return pr;
}

/**
* this function returns the DNA specified with that RNA
*/
DNA RNA::ConvertToDNA(){
    ///we first initialize a char array that will hold the sequence of the DNA strand
    char* DNAseq = new char[this->sz];
    for(int i=0 ; i<this->sz ; i++){
        if(this->seq[i] == 'U'){
            DNAseq[i]='T';
        }else{
            DNAseq[i]=this->seq[i];
        }
    }
    DNA mDNA(DNAseq , promoter , this->sz , -1 , -1);
    return mDNA;
}




void saveToFile(const RNA& rna){
    /// first we update the DNA counter in its file
    ifstream in("RNAcnt.txt");
    int num_of_RNA;
    in>>num_of_RNA;
    ofstream cnt("RNAcnt.txt");
    cnt<<num_of_RNA+1<<endl;
    in.close();
    ofstream out("RNA.txt" , ios_base::app);
    out<<rna.sz<<" ";
    for(int i=0 ; i<rna.sz ; i++){
        out<<rna.seq[i];
    }
    out<<" "<<rna.type<<endl;
    out.close();
}

istream& operator>> (istream& in, RNA& rna){
    reading_seq:
    cout<<"Enter the sequence : ";
    string sequenc;
    in>>sequenc;
    rna.sz=sequenc.size();
    if(rna.sz%3 != 0){
        cout<<"Wrong size"<<endl;
        goto reading_seq;
    }
    rna.seq=new char[rna.sz];
    for(int i=0 ; i<rna.sz ; i++){
        rna.seq[i] = sequenc[i];
        if(rna.seq[i] != 'A' && rna.seq[i] != 'U' && rna.seq[i] != 'G' && rna.seq[i] != 'C'){
            cout<<"Wrong input"<<endl;
            goto reading_seq;
        }
    }
    /// mRNA, tRNA, rRNA
    reading_type:
    cout<<"Enter the type "<<endl;
    cout<<"1- mRNA"<<endl;
    cout<<"2- tRNA"<<endl;
    cout<<"3- rRNA"<<endl;
    int choice;
    in>>choice;
    switch(choice){
    case 1:
        rna.type=mRNA;
        break;
    case 2:
        rna.type=tRNA;
        break;
    case 3:
        rna.type=rRNA;
        break;
    default:
        cout<<"Wrong input"<<endl;
        goto reading_type;
    }
    return in;
}
