#ifndef PROTEIN_H
#define PROTEIN_H
#include <Sequence.h>
#include <DNA.h>

enum Protein_Type {Hormon, Enzyme, TF, Cellular_Function};

class Protein : public Sequence
{
  	private:
        Protein_Type type;
      public:
 	 	// constructors and destructor
 	 	Protein();
 	 	Protein(char* p , int len , Protein_Type type);
 	 	~Protein();
 	 	Protein(const Protein& rhs);
 	 	Protein& operator=(Protein rhs);
 	 	void Print();
 	 	friend Protein* loadProFromFile();

        /// this function saves the DNA to a file
        friend void saveToFile(const Protein& dna);

        friend istream& operator>> (istream& in, Protein& pro);
};


#endif // PROTEIN_H
