
// mex -v LDFLAGS="\$LDFLAGS -framework Foundation" main.cpp get.cpp set.cpp mengine.cpp menginetm.cpp -L'/Applications/Mathematica\\ 9.app/SystemFiles/Links/MathLink/DeveloperKit/MacOSX-x86-64/CompilerAdditions/' -I'/Applications/Mathematica 9.app/SystemFiles/Links/MathLink/DeveloperKit/MacOSX-x86-64/CompilerAdditions/' -lMLi3 -output StartMATLink

#include "mengine.h"

void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
    (void) plhs; (void) prhs;    /* unused parameters */

    /* Check for proper number of input and output arguments */
    if (nrhs !=0) {
        mexErrMsgIdAndTxt( "MATLAB:mxisclass:maxrhs",
                "No input argument required.");
    }
    if(nlhs > 1){
        mexErrMsgIdAndTxt( "MATLAB:mxisclass:maxlhs", "Too many outputs");
    }
    MLMainString("-mathlink -linkmode listen linkprotocol SharedMemory -linkname MatlabLink");
}
