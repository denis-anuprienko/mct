#include "inmost.h"

using namespace std;
using namespace INMOST;

int main(int argc, char *argv[])
{
	// INMOST is generally used for MPI-parallel computations
	// For some users errors may occur if there's no Solver::Initialize()
	Solver::Initialize(&argc, &argv);

	// Create a sparse matrix (CSR form) and load it
	Sparse::Matrix A;
	string loc = ""; // put your location here or pass in argv
	A.Load(loc + "A_tet1.mtx");
	// Create a (sparse) vector and load it
	Sparse::Vector rhs;
	rhs.Load(loc + "rhs_tet1.mtx");
	// Create solution vector
	// Initialize as rhs so they have equal size
	Sparse::Vector sol = rhs;

	// Create linear solver and set parameters
	Solver S(Solver::INNER_ILU2);
	S.SetParameter("drop_tolerance", "0.1");
	S.SetParameter("absolute_tolerance", "1e-9");
	S.SetParameter("relative_tolerance", "1e-6");
	// Set matrix AND compute preconditioner (!)
	S.SetMatrix(A);
	// Run preconditioned BiCGStab
	bool solved = S.Solve(rhs, sol);
	if(!solved){
		cout << "Linear solver failed: " << S.GetReason() << endl;
	}
	cout << "Number of iterations: " << S.Iterations() << endl;
	cout << "Residual: " << S.Residual() << endl;
	Solver::Finalize();
	return 0;
}
