
#include "mlp.h"

#include <mex.h>

// context of all symbols returned

#define CONTEXT "MATLink`Engine`"

// the maximum size for MATLAB output
#define BUFSIZE (100*1024)  // 100 kB


// preprocessor flags for various platforms
#if WINDOWS_MATHLINK // from mathlink.h
#define ENGINE_WIN  // compiling on Windows
#endif


class MatlabVariable {
    mxArray *arr;

    MatlabVariable(const MatlabVariable &);     // disallowed
    void operator = (const MatlabVariable &); // disallowed
public:
    MatlabVariable(mxArray *var) : arr(var) { }
    ~MatlabVariable() { mxDestroyArray(arr); }
};

// Note:
// When running on OS X, lots of isopen() check are necessary to avoid crashes
// if MATLAB has quit.  This may not be necessary on Windows.
class MatlabEngine {
    const char *buffer;

    MatlabEngine(const MatlabEngine &);     // disallowed
    void operator = (const MatlabEngine &); // disallowed

public:
    MatlabEngine() : buffer("All output goes to the command window.") {
        mxArray *handle = mxCreateNumericMatrix(1, 1, mxUINT64_CLASS, mxREAL);
        MatlabEngine **ptr = reinterpret_cast<MatlabEngine **>(mxMalloc(8));
        mxSetData(handle, ptr);
        *ptr = this;
        mexPutVariable("base", "MmaLinkPointer", handle);
        // mexLock();
        mexPrintf("inited\n");
    }

    ~MatlabEngine() { mexPrintf("destroyed\n"); }

    bool isopen() { return true; }

    void open() { /* always open */ }

    void close() { /* return to command prompt */ }

    // returns true on success
    // warning: because of a MATLAB Engine bug
    // engEvalString() will hang on an incomplete expression such as "x = [1"
    bool evaluate(const char *command) {
        mexEvalString(command);
        return true;
    }

    const char *getBuffer() const { return buffer; }

    mxArray *getVariable(const char *name) {
        return mexGetVariable("base", name);
    }

    bool putVariable(const char *name, mxArray *var) {
        int res = mexPutVariable("base", name, var);
        return !res;
    }

    void setVisible(bool) { /* unsupported */ }
};


extern MatlabEngine engine;

