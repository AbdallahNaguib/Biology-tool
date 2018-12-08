#ifndef DNA_H
#define DNA_H
#include <Sequence.h>
#include <iostream>
#include <fstream>
using namespace std;

class RNA;

enum DNA_Type{promoter, motif, tail, noncoding};

class DNA : public Sequence{
  	private:
        DNA_Type type;
        DNA *complementary_strand;
        int startChar;
        int endChar;
    public:
 	 	// constructors and destructor
        DNA();
        DNA(char* seq, DNA_Type atype , int len , int start , int en);
        DNA(const DNA& rhs);
        DNA& operator=(DNA rhs);
        ~DNA();
 	 	// function printing DNA sequence information to user
        void Print();
        // function to convert the DNA sequence to RNA sequence
        // It starts by building the complementary_strand of the current
        // DNA sequence (starting from the startChar to the endChar, then,
        // it builds the RNA corresponding to that complementary_strand.
        RNA ConvertToRNA();
 	 	// function to build the second strand/pair of DNA sequence
	    // To build a complementary_strand, convert each A to T, each T to
        // A, each C to G, and each G to C. Then reverse the resulting
        // sequence.
        void BuildComplementaryStrand();
        int getSize();

        /// this function return all of the DNAs saved in the file as an array
        friend DNA* loadDNAFromFile();

        /// this function saves the DNA to a file
        friend void saveToFile(const DNA& dna);

        friend istream& operator>> (istream& in, DNA& dna);
  };

#endif // DNA_H
