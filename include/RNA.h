#ifndef RNA_H
#define RNA_H
#include <string>
#include <Sequence.h>
#include <DNA.h>
#include <fstream>
using namespace std;
class Protein;

// struct representing a codon of 3 DNA/RNA characters and ‘\0’
struct Codon
{
  	char value[4];    	    // 4th location for null character
    char AminoAcid;  	    // corresponding AminoAcid according to Table
};

// need to create one object of that class to load the AminoAcids table
// into memory
class CodonsTable
{
  	private:
        Codon codons[64];
   	public:
 	 	/// constructors and destructor
        CodonsTable(){
            /// we load the the codons from the file in the constructor
            LoadCodonsFromFile("RNA_codon_table.txt");
        }
        ~CodonsTable(){
        }
 	 	/// function to load all codons from the given text file
        void LoadCodonsFromFile(string codonsFileName){
            int i=0;
            ifstream in(codonsFileName);
            char aminoAcid;
            /**
            * we read the data from the file and if the value is UAA or UAG or UGA it doesn't have
            * an aminoAcid char so we put it empty
            */
            while(in>>codons[i].value){
                if(codons[i].value == "UAA" || codons[i].value == "UAG" || codons[i].value == "UGA"){
                    codons[i].AminoAcid=' ';
                }else{
                    in>>codons[i].AminoAcid;
                }
                i++;
            }
        }
        char getAminoAcid(char* value){
            for(int i=0 ; i < 64 ; i++){
                if(codons[i].value[0] == value[0] && codons[i].value[1] == value[1] &&
                   codons[i].value[2] == value[2]){
                    return codons[i].AminoAcid;
                   }
            }
        }
        friend class RNA;/// to be able to access the value array in the convert to Protein function
};

enum RNA_Type {mRNA, tRNA, rRNA};

class RNA : public Sequence{
  	private:
        RNA_Type type;
  	public:
 	 	// constructors and destructor
        RNA();
        RNA(char* seq, RNA_Type atype , int len);
        RNA(const RNA& rhs);
        RNA& operator=(RNA rhs);
        ~RNA();
 	 	// function to be overridden to print all the RNA information
        void Print();
 	 	// function to convert the RNA sequence into protein sequence
        // using the codonsTable object
        Protein ConvertToProtein();
 	 	// function to convert the RNA sequence back to DNA
        DNA ConvertToDNA();
        int getSize();
        friend RNA* loadRNAFromFile();

        /// this function saves the DNA to a file
        friend void saveToFile(const RNA& rna);

        friend istream& operator>> (istream& in, RNA& rna);
};

#endif // RNA_H
