/*
 * libfcgi2.h
 *
 *     Prototype Definitions for FCGX Library
 *
 *     www.coastrd.com Coast Research © 2009
 *
 * NOTES:
 * CDECL Calling Convention (same as libfcgi.DLL - see website)
 * All Strings are ANSI *NOT* Unicode (for now)
 */



#ifndef _FCGXAPP_H
#define _FCGXAPP_H
//   
//#ifdef __cplusplus // for C++ compilers
extern "C" { // (cdecl calling convention)
//#endif



// Request Method Codes for 'ReqMethod' property of the FCGX_REQUEST Structure
// Eliminates parsing strings for logical statements
#define HTTP_GET          1 // Information is appended onto the end of the request URI being requested
#define HTTP_POST         2 // Transmits all data immediately after the request URI. 
#define HTTP_HEAD         3 // Headers of a GET request - Information about a document
#define HTTP_PUT          4 // The URI in a PUT request identifies the entity enclosed with the request.
#define HTTP_DELETE       5 // delete the resource identified by the Request-URI
#define HTTP_OPTIONS      6 // enum supported Methods
#define HTTP_TRACE        7 // enum each node along the path
#define HTTP_CONNECT      8 // Request web proxy dynamically switch to a secure IP-based connection (an SSL tunnel)
#define HTTP_UNKNOWN      9 // None of the Above      
  
 


#define FCGX_NONE         0 // No Flags
#define FCGX_DEBUG        1 // Print Debug info - see comments for the flag in FCGX_InitRequest()
#define FCGX_REQP         2 // Print Debug info + Request Parameters
#define FCGX_ENVP         3 // Print Environment Parameters (only)


// Values for role component of FCGI_BeginRequestBody
#define FCGI_RESPONDER    1
#define FCGI_AUTHORIZER   2 // Not Supported
#define FCGI_FILTER       3 // Not Supported



// fcgx_stream
// this structure defines the fastcgi streams stdin, stdout & stderr
// each stream is an instance of the C++ string builder class
typedef struct FCGX_stream {   // plain C structure
    unsigned char* pData;        // POINTER to the first BYTE of the buffer
    unsigned int   LenStored;    // length of data currently contained in the buffer
    unsigned int   Capacity;     // length of the buffer
  char           Reserved[12]; // Opaque Stream Variables
} FCGX_Stream;


// FCGX_Request - One instance per Request containing Request variables
typedef struct FCGX_Request {  // plain C structure
    int                        Version;       // version number *1000 
    int                        ReqCount;      // Total Requests
    int                        Role;          // FastCGI Role
    int                        ConnFlags;     // Connection flags
    int                        ReqMethod;     // 1=GET, 2=POST, 3=HEAD etc  see above
    int                        ContLen;       // POST method CONTENT_LENGTH
    char*                    pzQuery;       // Pointer to ASCIIZ string containing QUERY_STRING
    int                        nParam;        // Total Request Params in the array
    char**                envp;          // Pointer to an array of C-Strings containing Request Params
    FCGX_Stream*    pIn;               // Pointer to input  data buffer
    FCGX_Stream*    pOut;              // Pointer to output data buffer
    FCGX_Stream*    pErr;              // Pointer to Error  data buffer
    char*                    pzLastErr;     // Pointer to ASCIIZ string containing LastError Description
    char                    Reserved[108]; // Opaque FCGI Variables 
} FCGX_REQUEST;




// Legacy Functions: (Identical to fcgiapp.h)


/*----------------------------------------------------------------------
 * FCGX_InitRequest
 *
 *    Initialize a FCGX_Request for use with FCGX_Accept_r()
 *
 * Return:
 *     0 upon success
 *      -ve if an error occurred - Call FCGX_GetErrorStr() for Error description
 *
 * Comments:
 *     Sockets not supported - 'sock' is ignored
 *     'flags' is zero or FCGX_DEBUG
 *  Create/Append to a 'Per Instance' FCGI Debug File
 *  IIS path: "C:\FCGIdebug\"  (or whatever your drive letter is)
 */
int    FCGX_InitRequest(FCGX_Request *request, int sock, int flags);


/*----------------------------------------------------------------------
 * FCGX_Accept_r
 *
 *      Accept a new request (Blocks until a Request is received)
 *
 * Return:
 *    0 for successful call, -1 for SIGTERM, <-1 Error code.
 *
 * Comments:
 *      Be sure you called FCGX_Init() (once) first.
 *      Finishes the request accepted by (and frees any
 *      storage allocated by) the previous call to FCGX_Accept.
 *      Creates input, output, and error streams and
 *      assigns them to pIn, pOut, and pErr respectively.
 *      Creates a parameters data structure to be accessed
 */
int    FCGX_Accept_r(FCGX_Request *request);


/*----------------------------------------------------------------------
 * FCGX_Finish_r
 *
 *      Complete the request
 *
 * Return:
 *    0 for successful call
 *      -ve if an error occurred - Call FCGX_GetErrorStr() for Error description
 *
 * Comments:
 *      Finishes the request accepted by the previous call
 *      Returns response and empties buffers
 */
int  FCGX_Finish_r(FCGX_Request *request);


/*----------------------------------------------------------------------
 * FCGX_GetParam
 *
 *     Obtain value of a specific FCGI ENVIRON parameter
 *
 * Return:
 *    Character array pointer to a NULL terminated string
 *
 * Comments:
 *  envp is a (misnamed) pointer to an array of C-Strings
 *  The array contains 4Byte pointers to the C-Strings
 *  (which by definition are Character array pointers)
 *  The C-Strings are in the format name=value and
 *  contain the *Request* parameters (not the Environment Params)
 *  (to see the Environ Params set FCGX_ENVP flag in FCGX_InitRequest())
 */
char*    FCGX_GetParam(const char *name, char **envp); // pArray


/*----------------------------------------------------------------------
 * FCGX_GetStr
 *
 *     Obtain n bytes from the input buffer
 *
 * Return:
 *    Number of bytes read
 *      -ve if an error occurred - Call FCGX_GetErrorStr() for Error description
 *
 * Comments:
 *    The 'LenStored' member of FCGX_stream contains the input buffer length
 *    A character array should be dimensioned to this size and a pointer
 *    to it passed in as the first parameter
 *    This prototype has been changed slightly
 *    str is declared as const char* not char*
 */
int    FCGX_GetStr(const char *str, int nbytes, FCGX_Stream *stream);


/*----------------------------------------------------------------------
 * FCGX_PutStr
 *
 *     Writes n consecutive bytes to the output buffer
 *
 * Return:
 *    Number of bytes written
 *      -ve if an error occurred - Call FCGX_GetErrorStr() for Error description
 */
int    FCGX_PutStr(const char *str, int nbytes, FCGX_Stream *stream);


/*----------------------------------------------------------------------
 * FCGX_PutS
 *
 *     Write a null-terminated character string to the output buffer
 *
 * Return:
 *    Number of bytes written
 *      -ve if an error occurred - Call FCGX_GetErrorStr() for Error description
 */
int    FCGX_PutS(const char *str, FCGX_Stream *stream);






// New Functions:

/*----------------------------------------------------------------------
 *
 * FCGX_Flush --  (not FCGX_FFlush)
 *
 *  Flushes any buffered output in the StdOut or StdErr buffers
 *  to the WebServer, emptying the buffer.
 *  This version takes the *Request* not the Stream handle as the argument
 *
 * Return:
 *      0 for success, -ve Error code.
 *      -ve if an error occurred - Call FCGX_GetErrorStr() for Error description
 */
int    FCGX_Flush(FCGX_Request *request);




/*----------------------------------------------------------------------
 * FCGX_GetBytes
 *
 *  Copies nBytes begining at src from any stream buffer to dest
 *  Uses a very fast ASM memcopy - see notes
 *  use any time after FCGX_InitRequest() has been called
 *  Unlike FCGX_GetStr() this function does not advance down the buffer
 *  with each call. It allows you to read from anywhere within the buffer
 *  Pointers are verified with IsBadReadPtr/IsBadWritePtr
 *
 *  src    is checked to ensure it is valid pointer
 *  dest   is checked to ensure it is within the buffer
 *  nBytes is checked to ensure it does exceed the buffer length
 * 
 * Return:
 *      Number of bytes read (can be less than specified)
 *      -ve if an error occurred - Call FCGX_GetErrorStr() for description
 */
int    FCGX_GetBytes(FCGX_Stream *stream, const char *src, const char *dest, int nbytes);


/*----------------------------------------------------------------------
 * FCGX_PutBytes
 *
 *  Copies nBytes begining from src to dest within any stream buffer
 *  Uses a very fast ASM memcopy - see notes
 *  use any time after FCGX_InitRequest() has been called
 *  Unlike FCGX_PutStr() this function does not append to the buffer
 *  It allows you to write anywhere within the buffer.
 *  Pointers are verified with IsBadReadPtr/IsBadWritePtr
 *
 *  src    is checked to ensure it is valid pointer
 *  dest   is checked to ensure it is within the buffer
 *  nBytes is checked to ensure it does exceed the buffer length
 * 
 * Return:
 *      exactly nBytes
 *      -ve if an error occurred - Call FCGX_GetErrorStr() for description
 */
int FCGX_PutBytes(FCGX_Stream *stream, const char *src, const char *dest, int nbytes);


/*----------------------------------------------------------------------
 * FCGX_EnsureCap
 *
 *  Use this to ensure enough capacity of any of the stream buffers
 *  The buffer is doubled in size until it is large enough
 * 
 * Return:
 *      New buffer length - Capacity
 */
unsigned int FCGX_EnsureCap(FCGX_Stream *stream, int nbytes);


/*----------------------------------------------------------------------
 * FCGX_URLDecode
 *
 *  Very fast "in place" URL decoding
 * 
 * Return:
 *      Decoded length
 */
int FCGX_URLDecode(const char *str, int nbytes);


/*----------------------------------------------------------------------
 * FCGX_PutDebug
 *
 *  Add text to the Debug file *only if*
 *  FCGX_DEBUG flag is set in FCGX_InitRequest()
 *
 * Comments:
 *     A FastCGI app may not open a console or a dialog
 *  This allows you to easily view variable values and
 *  output text for analysis in the same Debug file.
 *  Text inserted into the Debug file is clearly deliniated
 */
int FCGX_PutDebug(const char *str);





/*
 * FCGX_Read
 * FCGX_Write
 * FCGX_GetValue
 * 
 *   ANSI BSTR version of string functions for convenience in BASIC
 */



//#ifdef __cplusplus // for C++ compilers
}
//#endif


#endif    /* _FCGXAPP_H */
