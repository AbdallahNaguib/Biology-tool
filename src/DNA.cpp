#include "DNA.h"
#include <RNA.h>

DNA::DNA(){

}

DNA::DNA(char* seq, DNA_Type atype, int len , int start,int en){
    /**
    * first we make sure that the size of the sequence is divisible by 3 to be able to convert
    * it into protein and that the characters are accepted
    */
    if(len%3 != 0){
        throw 0;
    }
    if(start>en){
        throw 0;
    }
    /**
    * we start by initializing the seq pointer and then we make every char in the seq parameter
    * giving by the user equals our seq
    */
    this->seq=new char[len];
    for(int i=0 ; i<len ; i++){
        this->seq[i] = seq[i];
        if(seq[i] != 'A' && seq[i] != 'T' && seq[i] != 'G' && seq[i] != 'C'){
            throw 1;
        }
    }
    this->type=atype;
    this->startChar=start;
    this->endChar=en;
    this->sz=len;
    /**
    * if the user enters -1 and -1 as start and end indices then it means the whole sequence
    */
    if(startChar == -1 && endChar == -1){
        startChar=0;
        endChar=len - 1;
    }
}

DNA::DNA(const DNA& rhs){
    /**
    * here in the copy constructor we copy every variable to our object but first we need to
    * initialize the pointers first before copying them
    */
    this->startChar=rhs.startChar;
    this->endChar=rhs.endChar;
    this->type=rhs.type;
    this->sz=rhs.sz;
    this->seq=new char[this->sz];
    for(int i=0 ; i <this->sz ; i++){
        this->seq[i] = rhs.seq[i];
    }
    /**
    * we don't copy the complementary sequence as it is being built when we construct the RNA
    */
}
DNA& DNA::operator=(DNA rhs){
        /**
    * here in the copy constructor we copy every variable to our object but first we need to
    * initialize the pointers first before copying them
    */
    this->startChar=rhs.startChar;
    this->endChar=rhs.endChar;
    this->type=rhs.type;
    this->sz=rhs.sz;
    this->seq=new char[this->sz];
    for(int i=0 ; i <this->sz ; i++){
        this->seq[i] = rhs.seq[i];
    }
    /**
    * we don't copy the complementary sequence as it is being built when we construct the RNA
    */
    return *this;
}

DNA::~DNA(){
    delete seq;
}
int DNA::getSize(){
    return sz;
}
void DNA::Print(){
    cout<<"the sequence is ";
    for(int i=0 ; i<this->sz ; i++){
        cout<<this->seq[i];
    }
    cout<<"    and it is of type : ";
    switch(type){
    case promoter:
        cout<<"Promoter"<<endl;
        break;
    case motif:
        cout<<"Motif"<<endl;
        break;
    case tail:
        cout<<"Tail"<<endl;
        break;
    case noncoding:
        cout<<"Noncoding"<<endl;
        break;
    }
}

RNA DNA::ConvertToRNA(){
    BuildComplementaryStrand();
    /// the sz of the complementary strand is equal to endChar - startChar +1
    char* RNAseq = new char[complementary_strand->sz];
    /**
    * the RNA sequence comes from complementary strand by converting each T to U
    */
    for(int i=0 ; i<complementary_strand->sz ; i++){
        if(complementary_strand->seq[i] == 'T'){
            RNAseq[i]='U';
        }else{
            RNAseq[i]=complementary_strand->seq[i];
        }
    }
    RNA mRNA(RNAseq , RNA_Type::mRNA , complementary_strand->sz);
    return mRNA;
}

void DNA::BuildComplementaryStrand(){
    if(startChar == -1 && endChar == -1){
        startChar = 0;
        endChar = sz-1;
    }
    char* rev_seq=new char[sz];///rev_seq will contain the sequence reversed
    for(int i=0 ; i<sz ; i++){
        rev_seq[i]=seq[sz-i-1];
    }
    this->complementary_strand=new DNA;
    complementary_strand->sz = endChar - startChar + 1;
    complementary_strand->type=this->type;
    ///the size of the complementary would be the difference between their indices plus one
    complementary_strand->seq=new char[sz];
    for(int i=startChar ; i<=endChar ; i++){
        if(rev_seq[i] == 'T'){
            complementary_strand->seq[i - startChar]='A';
        }else if(rev_seq[i] == 'A'){
            complementary_strand->seq[i - startChar]='T';
        }else if(rev_seq[i] == 'C'){
            complementary_strand->seq[i - startChar]='G';
        }else if(rev_seq[i] == 'G'){
            complementary_strand->seq[i - startChar]='C';
        }
    }
}




void saveToFile(const DNA& dna){
    /// first we update the DNA counter in its file
    ifstream in("DNAcnt.txt");
    int num_of_DNA;
    in>>num_of_DNA;
    ofstream cnt("DNAcnt.txt");
    cnt<<num_of_DNA+1<<endl;
    in.close();
    ofstream out("DNA.txt" , ios_base::app);
    out<<dna.sz<<" ";
    for(int i=0 ; i<dna.sz ; i++){
        out<<dna.seq[i];
    }
    out<<" "<<dna.startChar<<" "<<dna.endChar<<" "<<dna.type<<endl;
    out.close();
}

istream& operator>> (istream& in, DNA& dna){
    reading_seq:
    cout<<"Enter the sequence : ";
    string sequenc;
    in>>sequenc;
    dna.sz=sequenc.size();
    if(dna.sz%3 != 0){
        cout<<"Wrong size"<<endl;
        goto reading_seq;
    }
    dna.seq=new char[dna.sz];
    for(int i=0 ; i<dna.sz ; i++){
        dna.seq[i] = sequenc[i];
        if(dna.seq[i] != 'A' && dna.seq[i] != 'T' && dna.seq[i] != 'G' && dna.seq[i] != 'C'){
            cout<<"Wrong input"<<endl;
            goto reading_seq;
        }
    }
    reading_type:
    cout<<"Enter the type "<<endl;
    cout<<"1- promoter"<<endl;
    cout<<"2- motif"<<endl;
    cout<<"3- tail"<<endl;
    cout<<"4- noncoding"<<endl;
    int choice;
    in>>choice;
    switch(choice){
    case 1:
        dna.type=promoter;
        break;
    case 2:
        dna.type=motif;
        break;
    case 3:
        dna.type=tail;
        break;
    case 4:
        dna.type=noncoding;
        break;
    default:
        cout<<"Wrong input"<<endl;
        goto reading_type;
    }
    cout<<"Enter start index and end index : ";
    Char:
    in>>dna.startChar>>dna.endChar;
    if(dna.startChar == -1 && dna.endChar == -1){
        dna.startChar = 0;
        dna.endChar = dna.sz-1;
    }
    /// if the size of the complemetary strand isn't divisible by 3 then alert an error
    if( (dna.endChar - dna.startChar + 1)%3 != 0){
        cout<<"the size of the complementary should be divisible by 3"<<endl;
        goto Char;
    }
    return in;
}
